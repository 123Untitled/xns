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

#include "xns/config/macros.hpp"
#include "xns/type_traits/types.hpp"

#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

#include "xns/type_traits/relationships_and_property_queries/is_nothrow_invocable.hpp"

#include "xns/memory/allocator.hpp"
#include "xns/memory/allocator_traits.hpp"
#include "xns/memory/lifecycle.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I S T -------------------------------------------------------------

	template <typename ___type,
			  typename ___alloc = xns::allocator<___type>>
	class list final {


		// -- assertions ------------------------------------------------------

		/* check if type is nothrow destructible */
		static_assert(xns::is_nothrow_destructible<___type>,
					  "list: value type must be nothrow destructible");


		private:

			// -- forward declarations ----------------------------------------

			/* node */
			struct ___node;

			/* iterator */
			template <bool>
			class ___iterator;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self            = xns::list<___type, ___alloc>;

			/* value type */
			using value_type      = ___type;

			/* allocator type */
			using allocator_type  = ___alloc;

			/* size type */
			using size_type       = xns::size_t;

			/* difference type */
			using difference_type = xns::ptrdiff_t;

			/* reference type */
			using reference       = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* move reference type */
			using move_reference  = xns::remove_const<value_type>&&;

			/* pointer type */
			using pointer         = typename xns::allocator_traits<allocator_type>::pointer;

			/* const pointer type */
			using const_pointer   = typename xns::allocator_traits<allocator_type>::const_pointer;

			/* iterator type */
			using iterator        = ___iterator<false>;

			/* const iterator type */
			using const_iterator  = ___iterator<true>;

			/* reverse iterator type */
			// using reverse_iterator =

			/* const reverse iterator type */
			// using const_reverse_iterator =


		private:

			// -- private types -----------------------------------------------

			/* node pointer type */
			using ___node_ptr     = ___node*;

			/* allocator type */
			using ___allocator    = typename ___alloc::template rebind<___node>;

			/* allocator traits */
			using ___alloc_traits = xns::allocator_traits<___allocator>;

			/* lifecycle type */
			using ___lifecycle    = xns::lifecycle<___node>;


			// -- private members ---------------------------------------------

			/* head */
			___node_ptr _head;

			/* tail */
			___node_ptr _tail;

			/* size */
			size_type _size;

			/* allocator */
			[[no_unique_address]] ___allocator _alloc;


		public:

			// -- public constructors -----------------------------------------

			/* default constructor */
			list(void) noexcept
			: _head{nullptr}, _tail{nullptr}, _size{0}, _alloc{} {
			}

			/* copy constructor */
			list(const self& other) noexcept(xns::is_nothrow_copy_constructible<value_type>
										  && noexcept(___allocator{}.allocate()))
			: _head{nullptr}, _tail{nullptr}, _size{other._size}, _alloc{other._alloc} {

				// declare node pointer
				___node_ptr    ptr  = other._head;
				___node_ptr    prev = nullptr;
				___node** addr = &_head;


				// todo: need to increment size for each node if throw !


				// loop over other list
				while (ptr != nullptr) {

					// nothrow allocate
					if constexpr (noexcept(___allocator{}.allocate())) {
						// allocate
						*addr = ___alloc_traits::allocate(_alloc);
						if (not *addr) {
							_tail = prev;
							return;
						}
					}
					else {
						// try to allocate
						try { *addr = ___alloc_traits::allocate(_alloc); }
						catch (...) {
							_tail = prev;
							throw; }
					}

					// nothrow copy constructible
					if constexpr (xns::is_nothrow_copy_constructible<value_type>) {
						// copy construct
						___lifecycle::construct(*addr, ptr->_value);
					}

					// throw copy constructible
					else {
						// try to construct
						try {
							___lifecycle::construct(*addr, ptr->_value);
						}
						catch (...) {
							___alloc_traits::deallocate(_alloc, *addr);
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
			list(self&& other) noexcept(xns::is_nothrow_move_constructible<___allocator>)
			: _head{other._head}, _tail{other._tail}, _size{other._size}, _alloc{xns::move(other._alloc)} {
				other._init();
			}

			/* destructor */
			~list(void) noexcept {
				_free();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) -> self& {

				// check for self assignment
				if (this == &other)
					return *this;

				// deallocate list
				_free();

				// implement copy with keep node allocation

				_init();

				// get other head
				___node_ptr ptr = other._head;
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
					return *this;

				// deallocate list
				_free();

				// move other members
				_copy(other);

				// invalidate other
				other._init();

				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* empty */
			auto empty(void) const noexcept -> bool {
				return _size == 0U;
			}

			/* front */
			auto front(void) noexcept -> reference {
				return _head->_value;
			}

			/* const front */
			auto front(void) const noexcept -> const_reference {
				return _head->_value;
			}

			/* back */
			auto back(void) noexcept -> reference {
				return _tail->_value;
			}

			/* const back */
			auto back(void) const noexcept -> const_reference {
				return _tail->_value;
			}


			// -- public iterator accessors -----------------------------------

			/* begin */
			auto begin(void) noexcept -> iterator {
				return iterator{_head};
			}

			/* end */
			auto end(void) noexcept -> iterator {
				return iterator{nullptr};
			}

			/* const begin */
			auto begin(void) const noexcept -> const_iterator {
				return const_iterator{_head};
			}

			/* const end */
			auto end(void) const noexcept -> const_iterator {
				return const_iterator{nullptr};
			}


			// -- public modifiers --------------------------------------------

			/* push front */
			auto push_front(const_reference ___vl) noexcept(
					noexcept(_new_node(___vl))
				) -> void {
				_front_link(_new_node(___vl));
				++_size;
			}

			/* push front */
			auto push_front(move_reference ___vl) noexcept(
					noexcept(_new_node(xns::move(___vl)))
				) -> void {
				_front_link(_new_node(xns::move(___vl)));
				++_size;
			}

			/* emplace front */
			template <typename... ___params>
			auto emplace_front(___params&&... ___args) noexcept(
					noexcept(_new_node(xns::forward<___params>(___args)...))
				) -> void {
				_front_link(_new_node(xns::forward<___params>(___args)...));
				++_size;
			}

			/* push back */
			auto push_back(const_reference __vl) noexcept(
					noexcept(_new_node(__vl))
				) -> void {
				_back_link(_new_node(__vl));
				++_size;
			}

			/* push back */
			auto push_back(move_reference __vl) noexcept(
					noexcept(_new_node(xns::move(__vl)))
				) -> void {
				_back_link(_new_node(xns::move(__vl)));
				++_size;
			}

			/* emplace back */
			template <typename... ___params>
			auto emplace_back(___params&&... ___args) noexcept(
					noexcept(_new_node(xns::forward<___params>(___args)...))
				) -> void {
				_back_link(_new_node(xns::forward<___params>(___args)...));
				++_size;
			}




			/* pop front */
			auto pop_front(void) noexcept -> void {
				// check if list is empty
				if (not _head) { return; }
				// get head node
				___node_ptr ptr = _head;
				// set new head node
				_head = _head->_next;
				// delete node
				_free_node(ptr);
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
				___node_ptr ptr = _tail;
				// set new tail node
				_tail = _tail->_prev;
				// delete node
				_free_node(ptr);
				// check if list is empty
				not _tail ? _head = nullptr : _tail->_next = nullptr;
				// decrement size
				--_size;
			}


			/* reverse */
			auto reverse(void) noexcept -> void {
				// initialize pointers
				___node_ptr ptr  = _head;
				___node_ptr prev = nullptr;
				___node_ptr next = nullptr;

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

				{ const ___node_ptr tmp = _head;
					_head = other._head;
					other._head = tmp;

					tmp = _tail;
					_tail = other._tail;
					other._tail = tmp; }

				const size_type size = _size;
				_size = other._size;
				other._size = size;
			}





		private:

			// -- private methods ---------------------------------------------

			/* new node */
			template <typename... ___params>
			auto _new_node(___params&&... args) noexcept(false &&
															xns::is_nothrow_constructible<value_type, ___params...>
				) -> ___node_ptr {

				auto ___ptr = ___alloc_traits::allocate(_alloc);


				if constexpr (xns::is_nothrow_constructible<value_type, ___params...>) {
					___lifecycle::construct(___ptr, xns::forward<___params>(args)...);
					return ___ptr;
				}

				else {
					try {
						___lifecycle::construct(___ptr, xns::forward<___params>(args)...);
						return ___ptr;
					}
					catch (...) {
						___alloc_traits::deallocate(_alloc, ___ptr);
						throw;
					}
				}
			}



			/* free node */
			auto _free_node(___node_ptr ___ptr) noexcept -> void {

				// not trivially destructible
				if constexpr (not xns::is_trivially_destructible<value_type>)
					___lifecycle::destroy(___ptr);

				___alloc_traits::deallocate(_alloc, ___ptr);
			}


			/* link node to front */
			auto _front_link(___node_ptr ptr) noexcept -> void {
				// check if list is empty
				not _head ? _tail = ptr
					// list is not empty
					: _head->_prev = ptr, ptr->_next = _head;
				// in any case, set new head
				_head = ptr;
			}

			/* link node to back */
			auto _back_link(___node_ptr ptr) noexcept -> void {
				// check if list is empty
				not _tail ? _head = ptr
					// list is not empty
					: _tail->_next = ptr, ptr->_prev = _tail;
				// in any case, set new tail
				_tail = ptr;
			}

			/* init */
			auto _init(void) noexcept -> void {
				_head = nullptr;
				_tail = nullptr;
				_size = 0U;
			}

			/* copy */
			auto _copy(const self& ___ot) noexcept -> void {
				_head = ___ot._head;
				_tail = ___ot._tail;
				_size = ___ot._size;
			}

			/* free */
			auto _free(void) noexcept -> void {

				// loop over list
				while (_head) {
					 // unlink node
					auto ___ptr = _head;
					_head = _head->_next;

					// free node
					_free_node(___ptr); }
			}



	}; // class list




	// -- N O D E -------------------------------------------------------------

	template <typename __type, typename __alloc>
	struct list<__type, __alloc>::___node final {



			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			___node(void) = delete;

			/* not assignable class */
			___xns_not_assignable(___node);

			/* value copy constructor */
			//___node(___node_ptr ___nx, ___node_ptr ___pv, const_reference value) noexcept(xns::is_nothrow_copy_constructible<__type>)
			//: _next{___nx}, _prev{___pv}, _value{value} {
			//}
			//
			///* value move constructor */
			//___node(___node_ptr ___nx, ___node_ptr ___pv, move_reference value) noexcept(xns::is_nothrow_move_constructible<__type>)
			//: _next{___nx}, _prev{___pv}, _value{xns::move(value)} {
			//}

			/* value forward constructor */
			template <typename... __params> //requires (xns::is_constructible<__type, __params...>)
			___node(__params&&... args) noexcept(xns::is_nothrow_constructible<__type, __params...>)
			: _next{nullptr}, _prev{nullptr}, _value{xns::forward<__params>(args)...} {
			}

			/* destructor */
			~___node(void) noexcept = default;


			// -- public members ----------------------------------------------

			/* next node */
			___node_ptr _next;

			/* previous node */
			___node_ptr _prev;

			/* value */
			value_type _value;

	}; // class node


	// -- non-member functions ------------------------------------------------

	/* swap */
	template <typename ___type>
	auto swap(xns::list<___type>& lhs, xns::list<___type>& rhs) noexcept -> void {
		lhs.swap(rhs);
	}


	// -- I T E R A T O R -----------------------------------------------------

	template <typename ___type, typename ___alloc>
	template <bool ___const>
	class list<___type, ___alloc>::___iterator final {


		// -- friends ---------------------------------------------------------

		/* other iterator as friend */
		template <bool>
		friend class ___iterator;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self     = xns::list<___type, ___alloc>::___iterator<___const>;

			/* reference type */
			using cond_ref = typename xns::conditional<___const, const_reference, reference>;

			/* pointer type */
			using cond_ptr = typename xns::conditional<___const, const_pointer, pointer>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			___iterator(void) noexcept
			: _node{nullptr} {
			}

			/* node constructor */
			___iterator(___node_ptr __node) noexcept
			: _node{__node} {
			}

			/* copy constructor */
			___iterator(const self&) noexcept = default;

			/* move constructor */
			___iterator(self&&) noexcept = default;

			/* copy constructor */
			___iterator(const ___iterator<not ___const>& other) noexcept
			: _node{other._node} {
				static_assert(___const == true, "iterator: cannot convert const_iterator to iterator");
			}

			/* move constructor */
			___iterator(___iterator<not ___const>&& other) noexcept
			: _node{other._node} {
				static_assert(___const == true, "iterator: cannot convert const_iterator to iterator");
			}

			/* destructor */
			~___iterator(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;

			/* copy assignment operator */
			auto operator=(const ___iterator<not ___const>& other) noexcept -> self& {
				static_assert(___const == true, "iterator: cannot convert const iterator to non-const iterator");
				_node = other._node;
				return *this;
			}

			/* move assignment operator */
			auto operator=(___iterator<not ___const>&& other) noexcept -> self& {
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
			inline auto operator==(const ___iterator<D>& other) const noexcept -> bool {
				return _node == other._node;
			}

			/* inequality operator */
			template <bool D>
			inline auto operator!=(const ___iterator<D>& other) const noexcept -> bool {
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
			___node_ptr _node;

	}; // list_iterator

} // namespace xns

#endif // XNS_LIST_HEADER
