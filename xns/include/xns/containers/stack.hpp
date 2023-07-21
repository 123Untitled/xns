#ifndef STACK_HEADER
#define STACK_HEADER

#include "types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "allocator.hpp"
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S T A C K  C L A S S ------------------------------------------------

	template <class T>
	class stack final {


		public:

			// -- T Y P E S ---------------------------------------------------

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = xns::stack<T>;

			/* size type */
			using size_type       = xns::size_t;

			/* reference type */
			using reference       = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* move reference type */
			using move_reference  = value_type&&;

			/* pointer type */
			using mutable_pointer = value_type*;

			/* const pointer type */
			using const_pointer   = const value_type*;


		private:

			/* forward declaration */
			struct node;


			// -- P R I V A T E  A L I A S E S --------------------------------

			/* node pointer type */
			using node_pointer = node*;

			/* allocator type */
			using allocator = xns::allocator<xns::stack<T>::node>;


		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			explicit stack(void) noexcept
			: _top{nullptr}, _storage{nullptr}, _size{0} {
				// code here...
			}

			/* copy constructor */
			stack(const self& other)
			: stack{} {
				// get other top
				node_pointer node = other._top;
				// loop through other
				while (node) {
					// push node value
					push(node->_value);
					// get next node
					node = node->_next;
				}
			}

			/* move constructor */
			stack(self&& other) noexcept
			: _top{other._top}, _storage{other._storage}, _size{other._size} {
				// invalidate other
				other.initialize_members();
			}

			/* destructor */
			~stack(void) {
				// get top node
				node_pointer node = _top;
				// loop through stack
				while (node) {
					// get next node
					node_pointer next = node->_next;
					// destroy node
					allocator::destroy(node);
					// deallocate node
					allocator::deallocate(node);
					// set node to next
					node = next;
				} // get storage node
				node = _storage;
				// loop through storage
				while (node) {
					// get next node
					node_pointer next = node->_next;
					// deallocate node
					allocator::deallocate(node);
					// set node to next
					node = next;
				}
			}


			// -- O P E R A T O R S -------------------------------------------

			/* copy operator */
			self& operator=(const self& other) {
				// check self assignment
				if (this != &other) {
					// clear self (keep own storage)
					clear();
					// get other top
					node_pointer node = other._top;
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
			self& operator=(self&& other) noexcept {
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
			reference top(void) {
				// return top value reference
				return _top->_value;
			}

			/* const top */
			const_reference top(void) const {
				// return top value const reference
				return _top->_value;
			}

			/* size */
			size_type size(void) const {
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
			void push(const_reference value) {
				// node pointer
				node_pointer node = new_node();
				// check if pointer is valid
				if (!node) { return; }
				// construct node
				allocator::construct(node, value);
				// link node
				link(node);
				// increment size
				++_size;
			}

			/* move push */
			void push(move_reference value) {
				// node pointer
				node_pointer node = new_node();
				// check if pointer is valid
				if (!node) { return; }
				// construct node
				allocator::construct(node, xns::move(value));
				// link node
				link(node);
				// increment size
				++_size;
			}

			/* emplace */
			template <typename... A>
			void emplace(A&&... arguments) {
				// node pointer
				node_pointer node = new_node();
				// check if pointer is valid
				if (!node) { return; }
				// construct node
				allocator::construct(node, xns::forward<A>(arguments)...);
				// link node
				link(node);
				// increment size
				++_size;
			}

			/* pop */
			void pop(void) {
				// unlink node
				node_pointer node = unlink();
				// check if pointer is valid
				if (!node) { return; }
				// destroy node
				allocator::destroy(node);
				// link node to storage
				link_storage(node);
				// decrement size
				--_size;
			}


			/* shrink */
			void shrink(void) {
				// node pointer
				node_pointer node;
				// loop through storage
				while ((node = unlink_storage())) {
					// deallocate node
					allocator::deallocate(node);
				}
				// reset storage
				_storage = nullptr;
			}

			/* clear */
			void clear(void) {
				// node pointer
				node_pointer node;
				// loop through stack
				while ((node = unlink())) {
					// destroy node
					allocator::destroy(node);
					// link node to storage
					link_storage(node);
				} // reset size
				_size = 0;
			}

			/* print stack */
			void print(void) {
				std::cout << "size: " << _size << std::endl;
				// get top node
				node_pointer node = _top;
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
			node_pointer new_node(void) {
				// check if free node is available
				if (_storage) { return unlink_storage(); }
				// else allocate new node
				return allocator::allocate();
			}


			void link(node_pointer node) {
				// link node's next pointer to top node
				node->_next = _top;
				// set top node
				_top = node;
			}

			node_pointer unlink(void) {
				// get top node
				node_pointer node = _top;
				// check if pointer is valid
				if (_top) { _top = _top->_next; }
				// return unlinked node
				return node;
			}

			/* link storage */
			void link_storage(node_pointer node) {
				// set node's next node
				node->_next = _storage;
				// set storage node
				_storage = node;
			}

			/* unlink storage */
			node_pointer unlink_storage(void) {
				// get storage node
				node_pointer node = _storage;
				// check if pointer is valid
				if (_storage) { _storage = _storage->_next; }
				// return unlinked node
				return node;
			}

			/* initialize members */
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
			node_pointer _top;

			/* storage */
			node_pointer _storage;

			/* size */
			size_type _size;


	};


	// -- N O D E  C L A S S --------------------------------------------------

	template <class T>
	struct stack<T>::node final {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			node(void)
			: _next(nullptr) {
				// code here...
			}

			/* copy constructor */
			//Node(Node& other)
			node(const node& other) = delete;
			/*Node(const Node& other)
			: _value(other._value), _next(other._next) {
				// code here...
			}*/

			/* move constructor */
			node(node&& other)
			: _value(xns::move(other._value)), _next(xns::move(other._next)) {
				// code here...
			}

			/* value copy constructor */
			node(stack<T>::const_reference value)
			: _value(value), _next(nullptr) {
				// code here...
			}

			/* value move constructor */
			node(stack<T>::move_reference value) noexcept
			: _value(xns::move(value)), _next(nullptr) {
				// code here...
			}

			/* value emplace constructor */
			template <typename... A>
			node(A&&... arguments)
			: _value(xns::forward<A>(arguments)...), _next(nullptr) {
				// code here...
			}

			/* destructor */
			~node(void) {
				// initialize next
				_next = nullptr;
			}

			node& operator=(const node& other) = delete;


			// -- M E M B E R S -----------------------------------------------

			/* value */
			stack<T>::value_type _value;

			/* next */
			stack<T>::node_pointer _next;


	};


};

#endif
