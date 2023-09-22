#ifndef LIST_HEADER
#define LIST_HEADER

// local headers
#include "types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "macros.hpp"
#include "allocator.hpp"
#include "common_type.hpp"
#include "swap.hpp"
#include "memory.hpp"

// c++ standard library headers
#include <iostream>
#include <memory>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I S T  C L A S S --------------------------------------------------

	template <typename T>
	class alignas(sizeof(xns::addr_t)) list final {


		private:

			// -- private forward declarations --------------------------------

			/* node */
			class node;

			/* iterator */
			template <bool>
			class list_iterator;


			// -- private types -----------------------------------------------

			/* node type */
			using node_type   = xns::list<T>::node;

			/* node pointer type */
			using node_ptr    = node_type*;

			/* allocator type */
			using allocator   = xns::memory::pool<node>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = list<value_type>;

			/* size type */
			using size_type       = xns::size_t;

			/* reference type */
			using mut_reference   = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* move reference type */
			using move_reference  = value_type&&;

			/* pointer type */
			using mut_pointer     = value_type*;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* iterator type */
			using iterator        = list_iterator<false>;

			/* const iterator type */
			using const_iterator  = list_iterator<true>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			inline list(void) noexcept
			: _head{nullptr}, _tail{nullptr}, _size{0} {}

			/* copy constructor */
			list(const self& other)
			: _head{nullptr}, _tail{nullptr}, _size{other._size} {
				// declare node pointer
				node_ptr node = other._head;
				node_ptr prev = nullptr;
				node_type** addr = &_head;

				// loop over other list
				while (node) {
					*addr = new_node(node->_value, prev);
					prev = *addr;
					addr = &(*addr)->_next;
					node = node->_next;
				} // set tail
				_tail = prev;
			}


			/* move constructor */
			inline list(self&& other) noexcept
			: _head{other._head}, _tail{other._tail}, _size{other._size} {
				// invalidate other
				other.init();
			}

			/* destructor */
			inline ~list(void) noexcept {
				// deallocate list
				free_list();
			}


			// -- public assignment methods -----------------------------------

			/* copy assignment */ // INFO: not optimized !
			auto assign(const self& other) -> void {
				// check for self assignment
				if (this != &other) {
					// deallocate list
					free_list();
					init();
					// get other head
					node_ptr node = other._head;
					// loop over other list
					while (node) {
						// push node copy
						back_link(new_node(node->_value));
						// move to next node
						node = node->_next; }
					// set list size
					_size = other._size;
				}
			}

			/* move assignment */
			auto assign(self&& other) noexcept -> void {
				// check for self assignment
				if (this != &other) {
					// deallocate list
					free_list();
					// move other members
					_head = other._head;
					_tail = other._tail;
					_size = other._size;
					// invalidate other
					other.init();
				}
			}


			// -- public assignment operators ---------------------------------

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

			/* size */
			inline auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* empty */
			inline auto empty(void) const noexcept -> bool {
				return _size == 0;
			}

			/* front */
			inline auto front(void) noexcept -> mut_reference {
				return _head->_value;
			}

			/* const front */
			inline auto front(void) const -> const_reference {
				return _head->_value;
			}

			/* back */
			inline auto back(void) noexcept -> mut_reference {
				return _tail->_value;
			}

			/* const back */
			inline auto back(void) const noexcept -> const_reference {
				return _tail->_value;
			}


			// -- public modifiers --------------------------------------------

			/* push front */
			inline auto push_front(const_reference value) -> void {
				// allocate new node
				node_ptr node = new_node(value);
				// link node to front
				front_link(node);
				// increment list size
				++_size;
			}

			/* push front */
			inline auto push_front(move_reference value) noexcept -> void {
				// allocate new node
				node_ptr node = new_node(xns::move(value));
				// link node to front
				front_link(node);
				// increment list size
				++_size;
			}

			/* emplace front */
			template <typename... A>
			inline auto emplace_front(A&&... args) -> void {
				// allocate new node
				node_ptr node = new_node(xns::forward<A>(args)...);
				// link node to front
				front_link(node);
				// increment list size
				++_size;
			}


			/* push back */
			inline auto push_back(const_reference value) -> void {
				// allocate new node
				node_ptr node = new_node(value);
				// link node to back
				back_link(node);
				// increment list size
				++_size;
			}

			/* push back */
			inline auto push_back(move_reference value) noexcept -> void {
				// allocate new node
				node_ptr node = new_node(xns::move(value));
				// link node to back
				back_link(node);
				// increment list size
				++_size;
			}

			/* emplace back */
			template <typename... A>
			inline auto emplace_back(A&&... args) -> void {
				// allocate new node
				node_ptr node = new_node(xns::forward<A>(args)...);
				// link node to back
				back_link(node);
				// increment list size
				++_size;
			}

			/* pop front */
			auto pop_front(void) noexcept -> void {
				// check if list is empty
				if (not _head) { return; }
				// get head node
				node_ptr node = _head;
				// set new head node
				_head = _head->_next;
				// delete node
				delete_node(node);
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
				node_ptr node = _tail;
				// set new tail node
				_tail = _tail->_prev;
				// delete node
				delete_node(node);
				// check if list is empty
				not _tail ? _head = nullptr : _tail->_next = nullptr;
				// decrement size
				--_size;
			}

			/* insert */
			auto insert(const_iterator pos, const_reference value) -> iterator {
				// not implemented
				return end();
			}

			/* insert */
			auto insert(const_iterator pos, move_reference value) noexcept -> iterator {
				// not implemented
				return end();
			}


			/* reverse */
			auto reverse(void) noexcept -> void {
				// initialize pointers
				node_ptr node = _head;
				node_ptr prev = nullptr;
				node_ptr next = nullptr;

				// loop over list
				while (node != nullptr) {
					next = node->_next;
					node->_next = prev;
					node->_prev = next;
					prev = node;
					node = next;
				} // swap head and tail
				xns::swap(_head, _tail);
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
				// swap members
				xns::swap(_head, other._head);
				xns::swap(_tail, other._tail);
				xns::swap(_size, other._size);
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
				return allocator::make(xns::forward<A>(args)...);

				/* using allocator_traits = std::allocator_traits<std::allocator<node_type>>;
				typename allocator_traits::allocator_type a;
				node_ptr node = allocator_traits::allocate(a, 1);
				allocator_traits::construct(a, node, xns::forward<A>(args)...);
				return node; */
			}

			/* delete node */
			inline void delete_node(node_ptr node) noexcept {
				allocator::store(node);

				/* using allocator_traits = std::allocator_traits<std::allocator<node_type>>;
				typename allocator_traits::allocator_type a;
				allocator_traits::destroy(a, node);
				allocator_traits::deallocate(a, node, 1); */
			}


			/* link node to front */
			auto front_link(node_ptr node) noexcept -> void {
				// check if list is empty
				not _head ?
					_tail = node
					// list is not empty
					: _head->_prev = node,
					   node->_next = _head;
				// in any case, set new head
				_head = node;
			}

			/* link node to back */
			auto back_link(node_ptr node) noexcept -> void {
				// check if list is empty
				not _tail ?
					_head = node
					// list is not empty
					: _tail->_next = node,
					   node->_prev = _tail;
				// in any case, set new tail
				_tail = node;
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
				node_ptr node = nullptr;
				// loop over list
				while (_head) {
					 // unlink node
					 node = _head;
					_head = _head->_next;
					// delete node
					delete_node(node);
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
	class alignas(sizeof(xns::addr_t)) list<T>::node final {


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline node(void) noexcept
			: _next{nullptr}, _prev{nullptr}, _value{} {}

			/* non-assignable struct */
			NON_ASSIGNABLE(node);

			/* value copy constructor (with previous node) */
			inline node(const_reference value, node_ptr prev)
			: _next{nullptr}, _prev{prev}, _value{value} {}

			/* value copy constructor */
			inline node(const_reference value)
			: _next{nullptr}, _prev{nullptr}, _value{value} {}

			/* value move constructor */
			inline node(move_reference value) noexcept
			: _next{nullptr}, _prev{nullptr}, _value{xns::move(value)} {}

			/* value forward constructor */
			template <typename... A>
			inline node(A&&... args) requires (xns::is_constructible<T, A...>)
			: _next{nullptr}, _prev{nullptr}, _value{xns::forward<A>(args)...} {}

			/* destructor */
			inline ~node(void) noexcept = default;


			// -- public members ----------------------------------------------

			/* next node */
			node_ptr _next;

			/* previous node */
			node_ptr _prev;

			/* value */
			value_type  _value;

	};


	// -- non-member functions ------------------------------------------------

	/* make list */
	template <class... A>
	auto make_list(A&&... args) -> xns::list<xns::common_type<A...>> {

		xns::list<xns::common_type<A...>> list;
		// emplace back
		((list.push_back(xns::forward<A>(args))), ...);

		return list;
	}


	// -- I T E R A T O R -----------------------------------------------------

	template <class T> template <bool C>
	class list<T>::list_iterator final {


		// -- friends ---------------------------------------------------------

		/* other iterator as friend */
		template <bool D>
		friend class list_iterator;


		private:

			// -- private constants -------------------------------------------

			/* iterator is const */
			static constexpr bool _const = C;


		public:

			// -- public types ------------------------------------------------

			/* list type */
			using list_type = xns::list<T>;

			/* value type */
			using value_type = typename list_type::value_type;

			/* self type */
			using self = list_type::list_iterator<C>;



			/* reference type */
			using reference = typename xns::conditional<C, list_type::const_reference,
														   list_type::mut_reference>;

			/* pointer type */
			using pointer   = typename xns::conditional<C, list_type::const_pointer,
														   list_type::mut_pointer>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			list_iterator(void) noexcept
			: _node{nullptr} {}

			/* node constructor */
			list_iterator(list_type::node_ptr node) noexcept
			: _node{node} {}

			/* copy constructor (non-const) */
			list_iterator(const list_type::iterator& other) noexcept
			: _node{other._node} {}

			/* copy constructor (const) */
			list_iterator(const list_type::const_iterator& other) noexcept
			: _node{other._node} {
				// assert invalid conversion
				static_assert(_const, "): CANNOT CONVERT CONST TO NON-CONST LIST ITERATOR");
			}

			/* move constructor (non-const) */
			list_iterator(list_type::iterator&& other) noexcept
			: _node{xns::move(other._node)} {
				// invalidate other
				other._node = nullptr;
			}

			/* move constructor (const) */
			list_iterator(list_type::const_iterator&& other) noexcept
			: _node{xns::move(other._node)} {
				// assert invalid conversion
				static_assert(_const, "): CANNOT CONVERT CONST TO NON-CONST LIST ITERATOR");
				// invalidate other
				other._node = nullptr;
			}

			/* destructor */
			~list_iterator(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator (non-const) */
			self& operator=(const list_type::iterator& other) noexcept {
				// copy node
				_node = other._node;
				// return self reference
				return *this;
			}

			/* copy assignment operator (const) */
			self& operator=(const list_type::const_iterator& other) noexcept {
				// assert invalid conversion
				static_assert(_const, "): CANNOT CONVERT CONST TO NON-CONST LIST ITERATOR");
				// copy node
				_node = other._node;
				// return self reference
				return *this;
			}

			/* move assignment operator */
			self& operator=(list_type::iterator&& other) noexcept {
				// move node
				_node = xns::move(other._node);
				// invalidate other
				other._node = this != &other ? nullptr : _node;
				// return self reference
				return *this;
			}

			/* move assignment operator (const) */
			self& operator=(list_type::const_iterator&& other) noexcept {
				// assert invalid conversion
				static_assert(_const, "): CANNOT CONVERT CONST TO NON-CONST LIST ITERATOR");
				// move node
				_node = xns::move(other._node);
				// invalidate other
				other._node = this != &other ? nullptr : _node;
				// return self reference
				return *this;
			}


			// -- public accessor operators -----------------------------------

			/* dereference operator */
			reference operator*(void) const noexcept {
				// return node value
				return _node->_value;
			}

			/* arrow operator */
			pointer operator->(void) const noexcept {
				// return node pointer
				return &_node->_value;
			}


			// -- public increment operators ----------------------------------

			/* pre-increment operator */
			self& operator++(void) noexcept {
				// increment node
				_node = _node->_next;
				// return self reference
				return *this;
			}

			/* post-increment operator */
			self operator++(int) noexcept {
				// copy self
				self tmp{*this};
				// increment node
				_node = _node->_next;
				// return copy
				return tmp;
			}


			// -- public decrement operators ----------------------------------

			/* pre-decrement operator */
			self& operator--(void) noexcept {
				// decrement node
				_node = _node->_prev;
				// return self reference
				return *this;
			}

			/* post-decrement operator */
			self operator--(int) noexcept {
				// copy self
				self tmp{*this};
				// decrement node
				_node = _node->_prev;
				// return copy
				return tmp;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			template <bool D>
			bool operator==(const list_iterator<D>& other) const noexcept {
				// return node equality
				return _node == other._node;
			}

			/* inequality operator */
			template <bool D>
			bool operator!=(const list_iterator<D>& other) const noexcept {
				// return node inequality
				return _node != other._node;
			}

			/* null equality operator */
			bool operator==(std::nullptr_t) const noexcept {
				// return pointer invalidity
				return _node == nullptr;
			}

			/* null inequality operator */
			bool operator!=(std::nullptr_t) const noexcept {
				// return pointer validity
				return _node != nullptr;
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			explicit operator bool(void) const noexcept {
				// return node boolean
				return _node != nullptr;
			}

			/* not operator */
			bool operator!(void) const noexcept {
				// return node not
				return _node == nullptr;
			}


		private:

			// -- private members ---------------------------------------------

			/* node pointer */
			xns::list<T>::node_ptr _node;

	};


}


#endif


