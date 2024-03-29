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

#ifndef XNS_QUEUE_HEADER
#define XNS_QUEUE_HEADER

// local headers
#include "xns/type_traits/types.hpp"
#include "xns/memory/allocator.hpp"
#include "xns/memory/memory.hpp"
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

// c++ standard library headers
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- Q U E U E -----------------------------------------------------------

	template <typename T>
	class queue final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self            = xns::queue<T>;

			/* value type */
			using value_type      = T;

			/* reference type */
			using mut_ref       = value_type&;

			/* move reference type */
			using move_ref  = value_type&&;

			/* const reference type */
			using const_ref = const value_type&;

			/* pointer type */
			using mut_ptr = value_type*;

			/* const pointer type */
			using const_ptr   = const value_type*;

			/* size type */
			using size_type       = xns::size_t;


		private:

			// -- forwared declarations ---------------------------------------

			/* internal_node class */
			class internal_node;


			// -- private types -----------------------------------------------

			/* node type */
			using node_type       = self::internal_node;

			/* allocator type */
			using allocator       = xns::allocator<node_type>;

			/* node pointer type */
			using node_ptr    = node_type*;


			// -- private members ---------------------------------------------

			/* head pointer */
			node_ptr _head;

			/* tail pointer */
			node_ptr _tail;

			/* size */
			size_type _size;


		public:

			// -- public constructors -----------------------------------------

			/* default constructor */
			inline queue(void) noexcept
			: _head{nullptr}, _tail{nullptr}, _size{0} {}

			/* copy constructor */
			queue(const self& other)
			: _head{nullptr}, _tail{nullptr}, _size{0} {
				// declare node
				node_ptr node = other._head;
				// loop over other queue
				while (node != nullptr) {
					// enqueue copy of value
					enqueue(node->_value);
					// move to next node
					node = node->_next;
				}
				// update size only at the end (optimization)
			}

			/* move constructor */
			inline queue(self&& other) noexcept
			: _head{other._head}, _tail{other._tail}, _size{other._size} {
				// invalidate other
				other.init();
			}

			/* destructor */
			inline ~queue(void) noexcept {
				// deallocate queue
				free_queue();
			}


			// -- public assignment -------------------------------------------

			/* copy assignment */
			auto assign(const self& other) -> void {
				// check for self assignment
				if (this != &other) {
					// deallocate queue
					free_queue();
					init();
					// get other head
					node_ptr node = other._head;
					// loop over other queue
					while (node != nullptr) {
						// enqueue value by copy
						enqueue(node->_value);
						// move to next node
						node = node->_next;
					}
				}
			}

			/* move assignment */
			auto assign(self&& other) noexcept -> void {
				// check for self assignment
				if (this != &other) {
					// deallocate queue
					free_queue();
					// move other members
					_head = other._head;
					_tail = other._tail;
					_size = other._size;
					// invalidate other
					other.init();
				}
			}


			// -- assignment operators ----------------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) -> self& {
				// call copy assignment
				assign(other);
				// return self reference
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// call move assignment
				assign(xns::move(other));
				// return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* get size */
			inline auto size(void) const noexcept -> size_type {
				// return size
				return _size;
			}

			/* is empty */
			inline auto empty(void) const noexcept -> bool {
				// return empty
				return _size == 0;
			}

			/* get first enqueued element */
			inline auto next(void) noexcept -> mut_ref {
				// return front
				return _head->_value;
			}

			/* get first enqueued const element */
			inline auto next(void) const noexcept -> const_ref {
				// return front
				return _head->_value;
			}


			// -- public modifiers --------------------------------------------

			/* enqueue */
			template <typename U>
			auto enqueue(U&& value) -> void {
				// assert that T is convertible from U
				//static_assert(xns::is_same<xns::remove_cvr<U>, value_type>, // TODO: replace with is_convertible ?
				//		"): QUEUE: U MUST BE SAME AS T :(");
				// allocate node
				node_ptr node = allocator::allocate();
				allocator::construct(node, xns::forward<U>(value));
				// link node
				link(node);
			}

			/* emplace */
			template <class... A>
			auto emplace(A&&... args) -> void {
				// assert that T is constructible from A
				static_assert(xns::is_constructible<value_type, A...>,
						"): QUEUE: T MUST BE CONSTRUCTIBLE FROM A... :(");
				// allocate node
				node_ptr node = allocator::allocate();
				allocator::construct(node, xns::forward<A>(args)...);
				// link node
				link(node);
			}

			/* dequeue */
			void dequeue(void) noexcept {
				// check for non-empty queue
				if (_head != nullptr) {
					// get first enqueued node
					node_ptr node = _head;
					// unlink node
					_head = _head->_next;
					// destroy node
					allocator::destroy(node);
					// deallocate node
					allocator::deallocate(node);
					// decrement size
					--_size;
				}
			}

			/* clear queue */
			inline auto clear(void) noexcept -> void {
				// deallocate queue
				free_queue();
				// initialize members
				init();
			}


		private:

			// -- private modifiers -------------------------------------------

			/* link node */
			inline void link(node_ptr node) noexcept {
				// check head
				_head != nullptr ?
					// link to tail
					_tail->_next = node
					// else link to head
					: _head = node;
				// update tail
				_tail = node;
				// update size
				++_size;
			}

			/* init members */
			inline auto init(void) noexcept -> void {
				// initialize members
				_head = _tail = nullptr;
				_size = 0;
			}

			/* free queue */
			auto free_queue(void) noexcept -> void {
				// get head node
				node_ptr node = _head;
				// loop over queue
				while (node) {
					// get next node
					node_ptr next = node->_next;
					// destroy node
					allocator::destroy(node);
					// deallocate node
					allocator::deallocate(node);
					// set node to next
					node = next;
				}
			}

	};


	// -- N O D E  C L A S S --------------------------------------------------

	template <class T>
	class xns::queue<T>::internal_node final {

		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline internal_node(void) noexcept
			: _next{nullptr} {}

			/* not assignable */
			XNS_NOT_ASSIGNABLE(internal_node);

			/* value copy constructor */
			inline explicit internal_node(const_ref value)
			: _value{value}, _next{nullptr} {}

			/* value move constructor */
			inline explicit internal_node(move_ref value) noexcept
			: _value{xns::move(value)}, _next{nullptr} {}

			/* value emplace constructor */
			template <typename... A>
			inline explicit internal_node(A&&... args)
			: _value{xns::forward<A>(args)...}, _next{nullptr} {}

			/* destructor */
			inline ~internal_node(void) noexcept = default;


			// -- public members ----------------------------------------------

			/* value */
			value_type _value;

			/* next */
			node_ptr _next;

	};






}

#endif
