#ifndef STACK_HEADER
#define STACK_HEADER

#include "Types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "allocator.hpp"
#include <iostream>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- S T A C K  C L A S S ------------------------------------------------

	template <typename T>
	class Stack final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using Value = T;

			/* size type */
			using Size = UInt64;

			/* reference type */
			using Reference = Value&;

			/* const reference type */
			using ConstReference = const Value&;

			/* move reference type */
			using MoveReference = Value&&;

			/* pointer type */
			using Pointer = Value*;

			/* const pointer type */
			using ConstPointer = const Value*;


		private:

			/* forward declaration */
			struct Node;


			// -- P R I V A T E  A L I A S E S --------------------------------

			/* node pointer type */
			using NodePointer = Node*;

			/* allocator type */
			using Allocator = Xf::Allocator<Xf::Stack<T>::Node>;


		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Stack(void)
			: _top{nullptr}, _storage{nullptr}, _capacity{0}, _size{0} {
				// code here...
			}

			/* destructor */
			~Stack(void) {
				// get top node
				NodePointer node = _top;
				// loop through stack
				while (node) {
					// get next node
					NodePointer next = node->_next;
					// destroy node
					Allocator::destroy(node);
					// deallocate node
					Allocator::deallocate(node, 1);
					// set node to next
					node = next;
				}
				// get storage node
				node = _storage;
				// loop through storage
				while (node) {
					// get next node
					NodePointer next = node->_next;
					// deallocate node
					Allocator::deallocate(node, 1);
					// set node to next
					node = next;
				}
			}


			// -- M E T H O D S -----------------------------------------------

			/* push */
			void push(ConstReference value) {
				// get new node
				NodePointer node = make_node();
				// check allocation
				if (!node) { return; }
				// construct node
				Allocator::construct(node, value);
				// link node
				link(node);
				// increment size
				++_size;
			}

			/* pop */
			void pop(void) {
				// unlink node
				NodePointer node = unlink();
				// check if pointer is valid
				if (!node) { return; }
				// destroy node
				Allocator::destroy(node);
				// link node to storage
				link_storage(node);
				// decrement size
				--_size;
			}

			/* top */
			Reference top(void) {
				// return top value reference
				return _top->_value;
			}

			/* clear */
			void clear(void) {
				// node pointer
				NodePointer node;
				// loop through stack
				while ((node = unlink())) {
					// destroy node
					Allocator::destroy(node);
					// link node to storage
					link_storage(node);
					// decrement size
					--_size;
				}
			}

			/* print stack */
			void print(void) {
				std::cout << "size: " << _size << std::endl;
				std::cout << "capacity: " << _capacity << std::endl;
				// get top node
				NodePointer node = _top;
				// loop through stack
				while (node) {
					// print value
					std::cout << node->_value << std::endl;
					// get next node
					node = node->_next;
				}
			}

		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			void link(NodePointer node) {
				// link node's next pointer to top node
				node->_next = _top;
				// set top node
				_top = node;
			}

			NodePointer unlink(void) {
				// get top node
				NodePointer node = _top;
				// check if pointer is valid
				if (_top) { _top = _top->_next; }
				// return unlinked node
				return node;
			}

			void link_storage(NodePointer node) {
				// link node's next pointer to storage
				node->_next = _storage;
				// set storage
				_storage = node;
			}

			NodePointer unlink_storage(void) {
				// get storage node
				NodePointer node = _storage;
				// check if pointer is valid
				if (_storage) { _storage = _storage->_next; }
				// return unlinked node
				return node;
			}


			NodePointer make_node(void) {
				// check if free nodes are available
				if (_storage) { return unlink_storage(); }
				// allocate new node
				NodePointer node = Allocator::allocate(1);
				// check allocation
				if (node) { ++_capacity; }
				// return node
				return node;
			}



			// -- P R I V A T E  M E M B E R S --------------------------------

			/* top */
			NodePointer _top;

			/* storage */
			NodePointer _storage;

			/* capacity */
			Size _capacity;

			/* size */
			Size _size;


	};


	// -- N O D E  C L A S S --------------------------------------------------

	template <typename T>
	struct Stack<T>::Node final {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Node(void)
			: _next(nullptr) {
				// code here...
			}

			/* copy constructor */
			Node(Node& other)
			: _value(other._value), _next(other._next) {
				// code here...
			}

			/* move constructor */
			Node(Node&& other)
			: _value(Xf::move(other._value)), _next(Xf::move(other._next)) {
				// code here...
			}

			/* value copy constructor */
			Node(ConstReference value)
			: _value(value), _next(nullptr) {
				// code here...
			}

			/* value move constructor */
			Node(MoveReference value) noexcept
			: _value(Xf::move(value)), _next(nullptr) {
				// code here...
			}

			/* value emplace constructor */
			template <typename... A>
			Node(A&&... args)
			: _value(Xf::forward<A>(args)...), _next(nullptr) {
				// code here...
			}

			/* destructor */
			~Node(void) {
				// initialize next
				_next = nullptr;
			}


			// -- M E M B E R S -----------------------------------------------

			/* value */
			Value _value;

			/* next */
			NodePointer _next;


	};


};

#endif
