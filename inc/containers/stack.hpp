#ifndef STACK_HEADER
#define STACK_HEADER

#include "types.hpp"
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
			using Size = xns::size_t;

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
			using Allocator = xns::allocator<Xf::Stack<T>::Node>;


		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			explicit Stack(void) noexcept
			: _top{nullptr}, _storage{nullptr}, _size{0} {
				// code here...
			}

			/* copy constructor */
			Stack(const Stack& other)
			: Stack{} {
				// get other top
				NodePointer node = other._top;
				// loop through other
				while (node) {
					// push node value
					push(node->_value);
					// get next node
					node = node->_next;
				}
			}

			/* move constructor */
			Stack(Stack&& other) noexcept
			: _top{other._top}, _storage{other._storage}, _size{other._size} {
				// invalidate other
				other.initialize_members();
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
					Allocator::deallocate(node);
					// set node to next
					node = next;
				} // get storage node
				node = _storage;
				// loop through storage
				while (node) {
					// get next node
					NodePointer next = node->_next;
					// deallocate node
					Allocator::deallocate(node);
					// set node to next
					node = next;
				}
			}


			// -- O P E R A T O R S -------------------------------------------

			/* copy operator */
			Stack& operator=(const Stack& other) {
				// check self assignment
				if (this != &other) {
					// clear self (keep own storage)
					clear();
					// get other top
					NodePointer node = other._top;
					// loop through other stack
					while (node) {
						// push node value
						push(node->_value);
						// get next node
						node = node->_next;
					} // return self reference
				} return *this;
			}

			/* move operator */ // WARNING: doesn't move storage
			Stack& operator=(Stack&& other) noexcept {
				// check self assignment
				if (this != &other) {
					// clear self (keep own storage)
					clear();
					// move only top
					_top = other._top;
					// assign size
					_size = other._size;
					// invalidate other top
					other._top = nullptr;
					// reset other size
					other._size = 0;
				} // return self reference
				return *this;
			}


			// -- A C C E S S O R S -------------------------------------------

			/* top */
			Reference top(void) {
				// return top value reference
				return _top->_value;
			}

			/* const top */
			ConstReference top(void) const {
				// return top value const reference
				return _top->_value;
			}

			/* size */
			Size size(void) const {
				// return size
				return _size;
			}

			/* empty */
			bool empty(void) const {
				// return if size is zero
				return _size == 0;
			}



			// -- M E T H O D S -----------------------------------------------

			/* push */
			void push(ConstReference value) {
				// node pointer
				NodePointer node = new_node();
				// check if pointer is valid
				if (!node) { return; }
				// construct node
				Allocator::construct(node, value);
				// link node
				link(node);
				// increment size
				++_size;
			}

			/* move push */
			void push(MoveReference value) {
				// node pointer
				NodePointer node = new_node();
				// check if pointer is valid
				if (!node) { return; }
				// construct node
				Allocator::construct(node, xns::move(value));
				// link node
				link(node);
				// increment size
				++_size;
			}

			/* emplace */
			template <typename... A>
			void emplace(A&&... arguments) {
				// node pointer
				NodePointer node = new_node();
				// check if pointer is valid
				if (!node) { return; }
				// construct node
				Allocator::construct(node, xns::forward<A>(arguments)...);
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


			/* shrink */
			void shrink(void) {
				// node pointer
				NodePointer node;
				// loop through storage
				while ((node = unlink_storage())) {
					// deallocate node
					Allocator::deallocate(node);
				}
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
				} // reset size
				_size = 0;
			}

			/* print stack */
			void print(void) {
				std::cout << "size: " << _size << std::endl;
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

			/* new node */
			NodePointer new_node(void) {
				// check if free nodes are available
				if (_storage) { return unlink_storage(); }
				// else allocate new node
				return Allocator::allocate();
			}


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

			/* link storage */
			void link_storage(NodePointer node) {
				// link node's next pointer to storage
				node->_next = _storage;
				// set storage
				_storage = node;
			}

			/* unlink storage */
			NodePointer unlink_storage(void) {
				// get storage node
				NodePointer node = _storage;
				// check if pointer is valid
				if (_storage) { _storage = _storage->_next; }
				// return unlinked node
				return node;
			}

			void initialize_members(void) {
				// initialize top
				_top = nullptr;
				// initialize storage
				_storage = nullptr;
				// initialize size
				_size = 0;
			}


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* top */
			NodePointer _top;

			/* storage */
			NodePointer _storage;

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
			//Node(Node& other)
			Node(const Node& other) = delete;
			/*Node(const Node& other)
			: _value(other._value), _next(other._next) {
				// code here...
			}*/

			/* move constructor */
			Node(Node&& other)
			: _value(xns::move(other._value)), _next(xns::move(other._next)) {
				// code here...
			}

			/* value copy constructor */
			Node(ConstReference value)
			: _value(value), _next(nullptr) {
				// code here...
			}

			/* value move constructor */
			Node(MoveReference value) noexcept
			: _value(xns::move(value)), _next(nullptr) {
				// code here...
			}

			/* value emplace constructor */
			template <typename... A>
			Node(A&&... arguments)
			: _value(xns::forward<A>(arguments)...), _next(nullptr) {
				// code here...
			}

			/* destructor */
			~Node(void) {
				// initialize next
				_next = nullptr;
			}

			Node& operator=(const Node& other) = delete;


			// -- M E M B E R S -----------------------------------------------

			/* value */
			Value _value;

			/* next */
			NodePointer _next;


	};


};

#endif
