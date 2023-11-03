#ifndef XNS_STACK_HEADER
#define XNS_STACK_HEADER

// local headers
#include "types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "memory.hpp"
#include "swap.hpp"
#include "allocator.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S T A C K  C L A S S ------------------------------------------------

	template <class T>
	class stack final {


		public:

			// -- public types ------------------------------------------------

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

			// -- forward declarations ----------------------------------------

			/* node class */
			class node;


			// -- private types -----------------------------------------------

			/* node pointer type */
			using node_pointer = node*;

			/* allocator type */
			using allocator = xns::memory::pool<node>;
			//using allocator = xns::allocator<node>;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline explicit stack(void) noexcept
			: _top{nullptr}, _size{0} {}

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
			inline stack(self&& other) noexcept
			: _top{other._top}, _size{other._size} {
				// invalidate other
				other.init();
			}

			/* destructor */
			inline ~stack(void) noexcept {
				// deallocate stack
				free_stack();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) -> self& {
				// check self assignment
				if (this != &other) {
					free_stack();
					init();
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

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				// check self assignment
				if (this != &other) {
					// free stack
					free_stack();
					// move members
					_top = other._top;
					_size = other._size;
					// invalidate other
					other.init();
				} // return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* top */
			inline auto top(void) noexcept -> reference {
				// return top value reference
				return _top->_value;
			}

			/* const top */
			inline auto top(void) const noexcept -> const_reference {
				// return top value const reference
				return _top->_value;
			}

			/* size */
			inline auto size(void) const noexcept -> size_type {
				// return size
				return _size;
			}

			/* empty */
			inline auto empty(void) const noexcept -> bool {
				// return if size is zero
				return _size == 0;
			}



			// -- public modifiers --------------------------------------------

			/* push */
			template <typename U>
			auto push(U&& value) -> void {
				// allocate and link node
				node_pointer node = allocator::allocate();
				allocator::construct(node, xns::forward<U>(value));
				node->_next = _top;
				_top = node;
				// increment size
				++_size;
			}

			/* emplace */
			template <typename... A>
			auto emplace(A&&... args) -> void {
				// allocate and link node
				node_pointer node = allocator::allocate();
				allocator::construct(node, xns::forward<A>(args)...);
				node->_next = _top;
				_top = node;
				// increment size
				++_size;
			}

			/* pop */
			auto pop(void) noexcept -> void {
				// check for non-empty stack
				if (_top) {
					// get top node
					node_pointer node = _top;
					_top = _top->_next;
					// destroy node
					allocator::destroy(node);
					// deallocate node
					allocator::deallocate(node);
					// decrement size
					--_size;
				}
			}

			/* swap */
			auto swap(self& other) noexcept -> void {
				// swap members
				xns::swap(_top, other._top);
				xns::swap(_size, other._size);
			}

			/* clear */
			auto clear(void) noexcept -> void {
				// deallocate stack
				free_stack();
				// initialize members
				init();
			}

			/* print stack */
			auto print(void) noexcept -> void {
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

			// -- private modifiers -------------------------------------------

			/* init members */
			inline auto init(void) noexcept -> void {
				// initialize members
				_top  = nullptr;
				_size = 0;
			}

			/* free stack */
			auto free_stack(void) noexcept -> void {
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
				}
			}


			// -- private members ---------------------------------------------

			/* top */
			node_pointer _top;

			/* size */
			size_type _size;

	};


	// -- N O D E  C L A S S --------------------------------------------------

	template <typename T>
	class xns::stack<T>::node final {

		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline node(void) noexcept
			: _next{nullptr} {}

			/* non-assignable class */
			unassignable(node);

			/* value copy constructor */
			inline explicit node(stack<T>::const_reference value)
			: _value{value}, _next{nullptr} {}

			/* value move constructor */
			inline explicit node(stack<T>::move_reference value) noexcept
			: _value{xns::move(value)}, _next{nullptr} {}

			/* value emplace constructor */
			template <typename... A>
			inline explicit node(A&&... args)
			: _value{xns::forward<A>(args)...}, _next{nullptr} {}

			/* destructor */
			inline ~node(void) noexcept = default;


			// -- public members ----------------------------------------------

			/* value */
			stack<T>::value_type _value;

			/* next */
			stack<T>::node_pointer _next;

	};


}

#endif
