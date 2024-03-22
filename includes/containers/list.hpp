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

#ifndef XNS_LIST_HEADER
#define XNS_LIST_HEADER

#include "type_traits/type_operations/move.hpp"
#include "type_traits/type_operations/forward.hpp"
#include "utility/macros.hpp"
#include "memory/allocator.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I S T -------------------------------------------------------------

	template <typename T>
	class list final {


		private:

			// -- private forward declarations --------------------------------

			/* node */
			class node;

			/* iterator */
			template <bool>
			class list_iterator;


			// -- private types -----------------------------------------------

			/* node type */
			using node_type   = node;

			/* node pointer type */
			using node_ptr    = node_type*;

			/* allocator type */
			using allocator   = xns::allocator<node>;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self           = xns::list<T>;

			/* value type */
			using value_type     = T;

			/* size type */
			using size_type      = decltype(sizeof(0));

			/* reference type */
			using mut_ref        = value_type&;

			/* const reference type */
			using const_ref      = const value_type&;

			/* move reference type */
			using move_ref       = xns::remove_const<value_type>&&;

			/* pointer type */
			using mut_ptr        = value_type*;

			/* const pointer type */
			using const_ptr      = const value_type*;

			/* iterator type */
			using iterator       = list_iterator<false>;

			/* const iterator type */
			using const_iterator = list_iterator<true>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			inline list(void) noexcept
			: _head{nullptr}, _tail{nullptr}, _size{0} {
			}

			/* copy constructor */
			list(const self& other)
			: _head{nullptr}, _tail{nullptr}, _size{other._size} {
				// declare node pointer
				node_ptr ptr = other._head;
				node_ptr prev = nullptr;
				node_type** addr = &_head;

				// loop over other list
				while (ptr) {
					*addr = new_node(ptr->_value, prev);
					 prev = *addr;
					 addr = &(*addr)->_next;
					  ptr = ptr->_next;
				} // set tail
				_tail = prev;
			}


			/* move constructor */
			inline list(self&& other) noexcept
			: _head{other._head}, _tail{other._tail}, _size{other._size} {
				other.init();
			}

			/* destructor */
			inline ~list(void) noexcept {
				free_list();
			}


			// -- public assignment methods -----------------------------------

			/* copy assignment */ // INFO: not optimized !
			auto assign(const self& other) -> void {

				// check for self assignment
				if (this == &other)
					return;

				// deallocate list
				free_list();
				init();

				// get other head
				node_ptr ptr = other._head;
				// loop over other list
				while (ptr) {
					// push node copy
					back_link(new_node(ptr->_value));
					// move to next node
					ptr = ptr->_next; }
				// set list size
				_size = other._size;
			}

			/* move assignment */
			auto assign(self&& other) noexcept -> void {

				// check for self assignment
				if (this == &other)
					return;

				// deallocate list
				free_list();
				// move other members
				_head = other._head;
				_tail = other._tail;
				_size = other._size;
				// invalidate other
				other.init();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) -> self& {
				assign(other);
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				assign(xns::move(other));
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			inline auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* empty */
			inline auto empty(void) const noexcept -> bool {
				return _size == 0;
			}

			/* front */
			inline auto front(void) noexcept -> mut_ref {
				return _head->_value;
			}

			/* const front */
			inline auto front(void) const -> const_ref {
				return _head->_value;
			}

			/* back */
			inline auto back(void) noexcept -> mut_ref {
				return _tail->_value;
			}

			/* const back */
			inline auto back(void) const noexcept -> const_ref {
				return _tail->_value;
			}


			// -- public modifiers --------------------------------------------

			/* push front */
			inline auto push_front(const_ref value) -> void {
				// allocate new node
				node_ptr ptr = new_node(value);
				// link node to front
				front_link(ptr);
				// increment list size
				++_size;
			}

			/* push front */
			inline auto push_front(move_ref value) noexcept -> void {
				// allocate new node
				node_ptr ptr = new_node(xns::move(value));
				// link node to front
				front_link(ptr);
				// increment list size
				++_size;
			}

			/* emplace front */
			template <typename... A>
			inline auto emplace_front(A&&... args) -> void {
				// allocate new node
				node_ptr ptr = new_node(xns::forward<A>(args)...);
				// link node to front
				front_link(ptr);
				// increment list size
				++_size;
			}


			/* push back */
			inline auto push_back(const_ref value) -> void {
				// allocate new node
				node_ptr ptr = new_node(value);
				// link node to back
				back_link(ptr);
				// increment list size
				++_size;
			}

			/* push back */
			inline auto push_back(move_ref value) noexcept -> void {
				// allocate new node
				node_ptr ptr = new_node(xns::move(value));
				// link node to back
				back_link(ptr);
				// increment list size
				++_size;
			}

			/* emplace back */
			template <typename... A>
			inline auto emplace_back(A&&... args) -> void {
				// allocate new node
				node_ptr ptr = new_node(xns::forward<A>(args)...);
				// link node to back
				back_link(ptr);
				// increment list size
				++_size;
			}

			/* pop front */
			auto pop_front(void) noexcept -> void {
				// check if list is empty
				if (not _head) { return; }
				// get head node
				node_ptr ptr = _head;
				// set new head node
				_head = _head->_next;
				// delete node
				store_node(ptr);
				// check if list is empty
				not _head ? _tail = nullptr : _head->_prev = nullptr;
				// decrement size
				--_size;
			}

			/* pop back */
			auto pop_back(void) noexcept -> void {
				// check if list is empty
				if (not _tail) { return; }
				// get tail node
				node_ptr ptr = _tail;
				// set new tail node
				_tail = _tail->_prev;
				// delete node
				store_node(ptr);
				// check if list is empty
				not _tail ? _head = nullptr : _tail->_next = nullptr;
				// decrement size
				--_size;
			}

			/* insert */
			auto insert(const_iterator pos, const_ref value) -> iterator {
				// not implemented
				return end();
			}

			/* insert */
			auto insert(const_iterator pos, move_ref value) noexcept -> iterator {
				// not implemented
				return end();
			}


			/* reverse */
			auto reverse(void) noexcept -> void {
				// initialize pointers
				node_ptr ptr  = _head;
				node_ptr prev = nullptr;
				node_ptr next = nullptr;

				// loop over list
				while (ptr != nullptr) {
					next = ptr->_next;
					ptr->_next = prev;
					ptr->_prev = next;
					prev = ptr;
					ptr = next;
				}

				// swap head and tail
				ptr = _head;
				_head = _tail;
				_tail = ptr;
			}



			/* clear list */
			void clear(void) noexcept {
				// deallocate list
				free_list();
				// initialize members
				init();
			}


			/* swap */
			auto swap(self& other) noexcept -> void {

				const node_ptr tmp = _head;
							 _head = other._head;
					   other._head = tmp;

							   tmp = _tail;
							 _tail = other._tail;
					   other._tail = tmp;

				const size_type size = _size;
							   _size = other._size;
						 other._size = size;
			}



			// -- public iterator methods -------------------------------------

			/* begin */
			inline auto begin(void) noexcept -> iterator {
				return iterator{_head};
			}

			/* begin */
			inline auto begin(void) const noexcept -> const_iterator {
				return const_iterator{_head};
			}

			/* end */
			inline auto end(void) const noexcept -> xns::null {
				return nullptr;
			}


		private:

			// -- private methods ---------------------------------------------

			/* new node */
			template <typename... A>
			inline auto new_node(A&&... args) -> node_ptr {
				auto ptr = allocator::allocate();
				allocator::construct(ptr, xns::forward<A>(args)...);
				return ptr;
			}

			/* delete node */
			inline void store_node(node_ptr ptr) noexcept {
				allocator::destroy(ptr);
				allocator::deallocate(ptr);
			}


			/* link node to front */
			auto front_link(node_ptr ptr) noexcept -> void {
				// check if list is empty
				not _head ?
					_tail = ptr
					// list is not empty
					: _head->_prev = ptr,
					   ptr->_next = _head;
				// in any case, set new head
				_head = ptr;
			}

			/* link node to back */
			auto back_link(node_ptr ptr) noexcept -> void {
				// check if list is empty
				not _tail ?
					_head = ptr
					// list is not empty
					: _tail->_next = ptr,
					   ptr->_prev = _tail;
				// in any case, set new tail
				_tail = ptr;
			}

			/* init */
			void init(void) noexcept {
				// initialize members
				_head = _tail = nullptr;
				_size = 0;
			}

			/* free list */
			inline void free_list(void) noexcept {
				// get head node
				node_ptr ptr = nullptr;
				// loop over list
				while (_head) {
					 // unlink node
					  ptr = _head;
					_head = _head->_next;
					// delete node
					store_node(ptr);
				}
			}


			// -- private members ---------------------------------------------

			/* head node */
			node_ptr _head;

			/* tail node */
			node_ptr _tail;

			/* list size */
			size_type _size;


	};




	// -- N O D E -------------------------------------------------------------

	template <class T>
	class list<T>::node final {


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline node(void) noexcept(xns::is_nothrow_default_constructible<T>)
			: _next{nullptr}, _prev{nullptr}, _value{} {
			}

			/* not assignable */
			XNS_NOT_ASSIGNABLE(node);

			/* value copy constructor (with previous node) */
			inline node(const_ref value, node_ptr prev) noexcept(xns::is_nothrow_copy_constructible<T>)
			: _next{nullptr}, _prev{prev}, _value{value} {
			}

			/* value copy constructor */
			inline node(const_ref value) noexcept(xns::is_nothrow_copy_constructible<T>)
			: _next{nullptr}, _prev{nullptr}, _value{value} {
			}

			/* value move constructor */
			inline node(move_ref value) noexcept(xns::is_nothrow_move_constructible<T>)
			: _next{nullptr}, _prev{nullptr}, _value{xns::move(value)} {
			}

			/* value forward constructor */
			template <typename... A> requires (xns::is_constructible<T, A...>)
			inline node(A&&... args) noexcept(xns::is_nothrow_constructible<T, A...>)
			: _next{nullptr}, _prev{nullptr}, _value{xns::forward<A>(args)...} {
			}

			/* destructor */
			inline ~node(void) noexcept = default;


			// -- public members ----------------------------------------------

			/* next node */
			node_ptr _next;

			/* previous node */
			node_ptr _prev;

			/* value */
			value_type _value;

	}; // class node


	// -- friend functions ----------------------------------------------------

	/* swap */
	template <typename T>
	auto swap(xns::list<T>& lhs, xns::list<T>& rhs) noexcept -> void {
		lhs.swap(rhs);
	}


	// -- non-member functions ------------------------------------------------

	/* make list */
	//template <class... A>
	//auto make_list(A&&... args) -> xns::list<xns::common_type<A...>> {
	//
	//	xns::list<xns::common_type<A...>> list;
	//	// emplace back
	//	((list.push_back(xns::forward<A>(args))), ...);
	//
	//	return list;
	//}


	// -- I T E R A T O R -----------------------------------------------------

	template <typename T>
	template <bool C>
	class list<T>::list_iterator final {


		// -- friends ---------------------------------------------------------

		/* other iterator as friend */
		template <bool>
		friend class list_iterator;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self     = xns::list<T>::list_iterator<C>;

			/* reference type */
			using cond_ref = typename xns::conditional<C, const_ref, mut_ref>;

			/* pointer type */
			using cond_ptr = typename xns::conditional<C, const_ptr, mut_ptr>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			list_iterator(void) noexcept
			: _node{nullptr} {
			}

			/* node constructor */
			list_iterator(node_ptr node) noexcept
			: _node{node} {
			}

			/* copy constructor */
			list_iterator(const self&) noexcept = default;

			/* copy constructor */
			list_iterator(const list_iterator<not C>& other) noexcept
			: _node{other._node} {
				static_assert(C, "iterator: cannot convert const_iterator to iterator");
			}

			/* move constructor */
			list_iterator(self&&) noexcept = default;

			/* move constructor */
			list_iterator(list_iterator<not C>&& other) noexcept
			: _node{other._node} {
				static_assert(C, "iterator: cannot convert const_iterator to iterator");
			}

			/* destructor */
			~list_iterator(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* copy assignment operator */
			auto operator=(const list_iterator<not C>& other) noexcept -> self& {
				static_assert(C, "iterator: cannot convert const_iterator to iterator");
				_node = other._node;
				return *this;
			}

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(list_iterator<not C>&& other) noexcept -> self& {
				static_assert(C, "iterator: cannot convert const_iterator to iterator");
				_node = other._node;
				return *this;
			}



			// -- public accessor operators -----------------------------------

			/* de-referencement operator */
			inline auto operator*(void) const noexcept -> cond_ref {
				return _node->_value;
			}

			/* pointer operator */
			inline auto operator->(void) const noexcept -> cond_ptr {
				return &_node->_value;
			}


			// -- public arithmetic operators ---------------------------------

			/* pre-incrementation operator */
			inline auto operator++(void) noexcept -> self& {
				_node = _node->_next;
				return *this;
			}

			/* post-incrementation operator */
			inline auto operator++(int) noexcept -> self {
				self tmp{*this};
				_node = _node->_next;
				return tmp;
			}

			/* pre-decrementation operator */
			inline auto operator--(void) noexcept -> self& {
				_node = _node->_prev;
				return *this;
			}

			/* post-decrementation operator */
			inline auto operator--(int) noexcept -> self {
				self tmp{*this};
				_node = _node->_prev;
				return tmp;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			template <bool D>
			inline auto operator==(const list_iterator<D>& other) const noexcept -> bool {
				return _node == other._node;
			}

			/* inequality operator */
			template <bool D>
			inline auto operator!=(const list_iterator<D>& other) const noexcept -> bool {
				return _node != other._node;
			}

			/* nullptr equality operator */
			inline auto operator==(decltype(nullptr)) const noexcept -> bool {
				return _node == nullptr;
			}

			/* nullptr inequality operator */
			inline auto operator!=(decltype(nullptr)) const noexcept -> bool {
				return _node != nullptr;
			}


			// -- public conversion operators ---------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
				return _node != nullptr;
			}


			// -- public not operator -----------------------------------------

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
				return _node == nullptr;
			}


		private:

			// -- private members ---------------------------------------------

			/* node pointer */
			node_ptr _node;

	}; // list_iterator

} // namespace xns

#endif // XNS_LIST_HEADER
