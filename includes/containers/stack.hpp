/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_STACK_HEADER
#define XNS_STACK_HEADER

// local headers
#include "type_traits/types.hpp"
#include "type_traits/type_operations/move.hpp"
#include "type_traits/type_operations/forward.hpp"
#include "utility/swap.hpp"
#include "memory/allocator.hpp"


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

			/* mutable reference type */
			using mut_ref         = value_type&;

			/* const reference type */
			using const_ref       = const value_type&;

			/* move reference type */
			using move_ref        = value_type&&;

			/* mutable pointer type */
			using mutable_ptr     = value_type*;

			/* const pointer type */
			using const_ptr       = const value_type*;


		private:

			// -- forward declarations ----------------------------------------

			/* node class */
			class node;


			// -- private types -----------------------------------------------

			/* node pointer type */
			using node_ptr = node*;

			/* allocator type */
			using allocator = xns::allocator<node>;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline explicit stack(void) noexcept
			: _top{nullptr}, _size{0} {}

			/* copy constructor */
			stack(const self& other)
			: stack{} {
				// get other top
				node_ptr it = other._top;
				// loop through other
				while (it) {
					// push node value
					this->push(it->_value);
					// get next node
					it = it->_next;
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
					node_ptr it = other._top;
					// loop through other stack
					while (it) {
						// push node value
						this->push(it->_value);
						// get next node
						it = it->_next;
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
					_top  = other._top;
					_size = other._size;
					// invalidate other
					other.init();
				} // return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* top */
			inline auto top(void) noexcept -> mut_ref {
				// return top value reference
				return _top->_value;
			}

			/* const top */
			inline auto top(void) const noexcept -> const_ref {
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
				node_ptr ptr = allocator::allocate();
				allocator::construct(ptr, xns::forward<U>(value));
				ptr->_next = _top;
				_top = ptr;
				// increment size
				++_size;
			}

			/* emplace */
			template <typename... A>
			auto emplace(A&&... args) -> void {
				// allocate and link node
				node_ptr ptr = allocator::allocate();
				allocator::construct(ptr, xns::forward<A>(args)...);
				ptr->_next = _top;
				_top = ptr;
				// increment size
				++_size;
			}

			/* pop */
			auto pop(void) noexcept -> void {
				// check for non-empty stack
				if (_top == nullptr)
					return;
				// get top node
				node_ptr ptr = _top;
				_top = _top->_next;
				// destroy node
				allocator::destroy(ptr);
				// deallocate node
				allocator::deallocate(ptr);
				// decrement size
				--_size;
			}

			/* swap */
			auto swap(self& other) noexcept -> void {
				// swap members
				xns::swap(_top,  other._top);
				xns::swap(_size, other._size);
			}

			/* clear */
			auto clear(void) noexcept -> void {
				// deallocate stack
				free_stack();
				// initialize members
				init();
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
				node_ptr it = _top;
				// loop through stack
				while (it) {
					// get next node
					node_ptr next = it->_next;
					// destroy node
					allocator::destroy(it);
					// deallocate node
					allocator::deallocate(it);
					// set node to next
					it = next;
				}
			}


			// -- private members ---------------------------------------------

			/* top */
			node_ptr _top;

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
			inline explicit node(const_ref value)
			: _value{value}, _next{nullptr} {}

			/* value move constructor */
			inline explicit node(move_ref value) noexcept
			: _value{xns::move(value)}, _next{nullptr} {}

			/* value emplace constructor */
			template <typename... A>
			inline explicit node(A&&... args)
			: _value{xns::forward<A>(args)...}, _next{nullptr} {}

			/* destructor */
			inline ~node(void) noexcept = default;


			// -- public members ----------------------------------------------

			/* value */
			value_type _value;

			/* next */
			node_ptr _next;

	};

}

#endif // XNS_STACK_HPP
