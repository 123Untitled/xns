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

#include "xns/type_traits/types.hpp"

#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

#include "xns/type_traits/relationships_and_property_queries/is_nothrow_invocable.hpp"

#include "xns/config/macros.hpp"
#include "xns/memory/allocator.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I S T -------------------------------------------------------------

	template <typename ___type,
			  typename ___alloc = xns::allocator<___type>>
	class list final {


		private:

			// -- private forward declarations --------------------------------

			/* node */
			class node;

			/* iterator */
			template <bool>
			class list_iterator;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self           = xns::list<___type, ___alloc>;

			/* value type */
			using value_type     = ___type;

			/* size type */
			using size_type      = xns::size_t;

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

			/* allocator type */
			using allocator_type = ___alloc;


		private:

			// -- private types -----------------------------------------------

			/* node type */
			using node_type = node;

			/* node pointer type */
			using node_ptr  = node_type*;

			/* allocator type */
			using ___allocator = typename ___alloc::template
													rebind<node_type>::other;


			// -- private members ---------------------------------------------

			/* head */
			node_ptr _head;

			/* tail */
			node_ptr _tail;

			/* size */
			size_type _size;

			/* allocator */
			//[[no_unique_address]]
			//___allocator _alloc;


		public:

			// -- public constructors -----------------------------------------

			/* default constructor */
			list(void) noexcept
			: _head{nullptr}, _tail{nullptr}, _size{0U} {
			}

			/* copy constructor */
			list(const self& other) noexcept(xns::is_nothrow_copy_constructible<value_type>
										  && xns::is_nothrow_invocable<decltype(___allocator::allocate)>)
			: _head{nullptr}, _tail{nullptr}, _size{other._size} {

				// declare node pointer
				node_ptr    ptr  = other._head;
				node_ptr    prev = nullptr;
				node_type** addr = &_head;


				// todo: need to increment size for each node if throw !


				// loop over other list
				while (ptr != nullptr) {

					// nothrow allocate
					if constexpr (xns::is_nothrow_invocable<decltype(___allocator::allocate)>) {
						// allocate
						*addr = ___allocator::allocate();
						if (not *addr) {
							_tail = prev;
							return;
						}
					}
					else {
						// try to allocate
						try { *addr = ___allocator::allocate(); }
						catch (...) {
							_tail = prev;
							throw; }
					}

					// nothrow copy constructible
					if constexpr (xns::is_nothrow_copy_constructible<value_type>) {
						// copy construct
						___allocator::construct(*addr, ptr->_value);
					}
					// throw copy constructible
					else {
						// try to construct
						try { ___allocator::construct(*addr, ptr->_value); }
						catch (...) {
							___allocator::deallocate(*addr);
							// init pointer
							*addr = nullptr;
							// set tail
							_tail = prev;
							throw; }
					}

					// todo: need to free node if construct throws !!!

					 prev = *addr;
					 addr = &(*addr)->_next;
					 ptr  = ptr->_next;
				}
				// set tail
				_tail = prev;
			}


			/* move constructor */
			list(self&& other) noexcept
			: _head{other._head}, _tail{other._tail}, _size{other._size} {
				other._init();
			}

			/* destructor */
			~list(void) noexcept {
				this->_free();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) -> self& {

				// check for self assignment
				if (this == &other)
					return;

				// deallocate list
				this->_free();

				_init();

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

				return *this;
			}

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {

				// check for self assignment
				if (this == &other)
					return;

				// deallocate list
				this->_free();

				// move other members
				_copy(other);

				// invalidate other
				other._init();

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


			// -- public iterator accessors -----------------------------------

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
			auto clear(void) noexcept -> void {
				_free(); _init();
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





		private:

			// -- private methods ---------------------------------------------

			/* new node */
			template <typename... A>
			inline auto new_node(A&&... args) -> node_ptr {
				auto ptr = ___allocator::allocate();
				___allocator::construct(ptr, xns::forward<A>(args)...);
				return ptr;
			}

			/* delete node */
			inline void store_node(node_ptr ptr) noexcept {
				___allocator::destroy(ptr);
				___allocator::deallocate(ptr);
			}


			/* link node to front */
			auto front_link(node_ptr ptr) noexcept -> void {
				// check if list is empty
				not _head ? _tail = ptr
					// list is not empty
					: _head->_prev = ptr, ptr->_next = _head;
				// in any case, set new head
				_head = ptr;
			}

			/* link node to back */
			auto back_link(node_ptr ptr) noexcept -> void {
				// check if list is empty
				not _tail ? _head = ptr
					// list is not empty
					: _tail->_next = ptr, ptr->_prev = _tail;
				// in any case, set new tail
				_tail = ptr;
			}

			/* init */
			auto _init(void) noexcept -> void {
				_head = _tail = nullptr;
				_size = 0;
			}

			/* copy */
			auto _copy(const self& __ot) noexcept -> void {
				_head = __ot._head;
				_tail = __ot._tail;
				_size = __ot._size;
			}

			/* free */
			auto _free(void) noexcept -> void {
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



	}; // class list




	// -- N O D E -------------------------------------------------------------

	template <typename __type, typename __alloc>
	class list<__type, __alloc>::node final {


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			node(void) = delete;

			/* not assignable */
			XNS_NOT_ASSIGNABLE(node);

			/* value copy constructor (with previous node) */
			node(const_ref value, node_ptr prev = nullptr) noexcept(xns::is_nothrow_copy_constructible<__type>)
			: _next{nullptr}, _prev{prev}, _value{value} {
			}

			/* value move constructor */
			inline node(move_ref value) noexcept(xns::is_nothrow_move_constructible<__type>)
			: _next{nullptr}, _prev{nullptr}, _value{xns::move(value)} {
			}

			/* value forward constructor */
			template <typename... __params> requires (xns::is_constructible<__type, __params...>)
			inline node(__params&&... args) noexcept(xns::is_nothrow_constructible<__type, __params...>)
			: _next{nullptr}, _prev{nullptr}, _value{xns::forward<__params>(args)...} {
			}

			/* destructor */
			~node(void) noexcept = default;


			// -- public members ----------------------------------------------

			/* next node */
			node_ptr _next;

			/* previous node */
			node_ptr _prev;

			/* value */
			value_type _value;

	}; // class node


	// -- non-member functions ------------------------------------------------

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

	template <typename __type, typename __alloc>
	template <bool ___const>
	class list<__type, __alloc>::list_iterator final {


		// -- friends ---------------------------------------------------------

		/* other iterator as friend */
		template <bool>
		friend class list_iterator;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self     = xns::list<__type, __alloc>::list_iterator<___const>;

			/* reference type */
			using cond_ref = typename xns::conditional<___const, const_ref, mut_ref>;

			/* pointer type */
			using cond_ptr = typename xns::conditional<___const, const_ptr, mut_ptr>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			list_iterator(void) noexcept
			: _node{nullptr} {
			}

			/* node constructor */
			list_iterator(node_ptr __node) noexcept
			: _node{__node} {
			}

			/* copy constructor */
			list_iterator(const self&) noexcept = default;

			/* move constructor */
			list_iterator(self&&) noexcept = default;

			/* copy constructor */
			list_iterator(const list_iterator<not ___const>& other) noexcept
			: _node{other._node} {
				static_assert(___const == true, "iterator: cannot convert const_iterator to iterator");
			}

			/* move constructor */
			list_iterator(list_iterator<not ___const>&& other) noexcept
			: _node{other._node} {
				static_assert(___const == true, "iterator: cannot convert const_iterator to iterator");
			}

			/* destructor */
			~list_iterator(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;

			/* copy assignment operator */
			auto operator=(const list_iterator<not ___const>& other) noexcept -> self& {
				static_assert(___const == true, "iterator: cannot convert const iterator to non-const iterator");
				_node = other._node;
				return *this;
			}

			/* move assignment operator */
			auto operator=(list_iterator<not ___const>&& other) noexcept -> self& {
				static_assert(___const == true, "iterator: cannot convert const iterator to non-const iterator");
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
			auto operator++(void) noexcept -> self& {
				_node = _node->_next;
				return *this;
			}

			/* post-incrementation operator */
			auto operator++(int) noexcept -> self {
				self tmp{*this};
				_node = _node->_next;
				return tmp;
			}

			/* pre-decrementation operator */
			auto operator--(void) noexcept -> self& {
				_node = _node->_prev;
				return *this;
			}

			/* post-decrementation operator */
			auto operator--(int) noexcept -> self {
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
