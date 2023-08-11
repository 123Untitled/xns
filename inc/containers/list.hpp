#ifndef LIST_HEADER
#define LIST_HEADER

#include "types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include <iostream>
#include "macro.hpp"
#include "allocator.hpp"
#include "common_type.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I S T -------------------------------------------------------------

	template <class T>
	class list final {


		private:

			// -- private forward declarations --------------------------------

			/* node */
			struct node;

			/* iterator */
			template <bool>
			class list_iterator;


			// -- private types -----------------------------------------------

			/* node pointer type */
			using node_pointer    = node*;

			/* allocator type */
			using allocator       = xns::allocator<node>;


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
			list(void) noexcept
			: _head{nullptr}, _tail{nullptr}, _storage{nullptr}, _size{0} {}

			/* copy constructor */
			list(const self& other)
			: list{} {
				// declare node pointer
				node_pointer node = other._head;
				// loop over other list
				while (node) {
					// push back value by copy
					push_back(node->_value);
					// get next node
					node = node->_next;
				}
			}

			/* move constructor */
			list(self&& other) noexcept
			: _head{other._head}, _tail{other._tail}, _storage{other._storage}, _size{other._size} {
				// invalidate other list
				other._init();
				// invalidate other storage
				other._storage = nullptr;
			}

			/* destructor */
			~list(void) noexcept {
				// destroy and deallocate list
				_free_list();
				// deallocate storage
				_free_storage();
			}


			// -- public assignment methods -----------------------------------

			/* INFO: optimization possible by copying storage
			 * implement custom method for copying storage
			 * update size only at the end
			 */

			/* copy assignment */
			void assign(const self& other) {
				// check for self assignment
				if (this != &other) {
					// destroy self list
					_destroy_list();
					// get other head
					node_pointer node = other._head;
					// loop over other list
					while (node) {
						// push back value by copy
						push_back(node->_value);
						// move to next node
						node = node->_next; }
				}
			}

			/* INFO: storage is not moved!
			 * (simple linked list reason)
			 */

			/* move assignment */
			void assign(self&& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// destroy self list
					_destroy_list();
					// move other
					_head = other._head;
					_tail = other._tail;
					_size = other._size;
					// invalidate other list
					other._init();
				}
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			list& operator=(const self& other) {
				// call copy assignment
				assign(other);
				// return self reference
				return *this;
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// call move assignment
				assign(xns::move(other));
				// return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			size_type size(void) const noexcept {
				// return list size
				return _size;
			}

			/* empty */
			bool empty(void) const noexcept {
				// return list empty
				return _size == 0;
			}

			/* front */
			mut_reference front(void) noexcept {
				// return front element
				return _head->_value;
			}

			/* const front */
			const_reference front(void) const {
				// return front element
				return _head->_value;
			}

			/* back */
			mut_reference back(void) noexcept {
				// return back element
				return _tail->_value;
			}

			/* const back */
			const_reference back(void) const {
				// return back element
				return _tail->_value;
			}


			// -- public modifiers --------------------------------------------


			/* push front */
			void push_front(const_reference value) {
				// allocate new node
				node_pointer node = new_node();
				// construct node
				allocator::construct(node, value);
				// link node to front
				front_link(node);
			}

			/* push front */
			void push_front(move_reference value) noexcept {
				// allocate new node
				node_pointer node = new_node();
				// construct node
				allocator::construct(node, xns::move(value));
				// link node to front
				front_link(node);
			}

			/* emplace front */
			template <typename... A>
			void emplace_front(A&&... args) {
				// allocate new node
				node_pointer node = new_node();
				// construct node
				allocator::construct(node, xns::forward<A>(args)...);
				// link node to front
				front_link(node);
			}


			/* push back */
			void push_back(const_reference value) {
				// allocate new node
				node_pointer node = new_node();
				// construct node
				allocator::construct(node, value);
				// link node to back
				back_link(node);
			}

			/* push back */
			void push_back(move_reference value) noexcept {
				// allocate new node
				node_pointer node = new_node();
				// construct node
				allocator::construct(node, xns::move(value));
				// link node to back
				back_link(node);
			}

			/* emplace back */
			template <typename... A>
			void emplace_back(A&&... args) {
				// allocate new node
				node_pointer node = new_node();
				// construct node
				allocator::construct(node, xns::forward<A>(args)...);
				// link node to back
				back_link(node);
			}

			/* pop front */
			void pop_front(void) {
				// check if list is empty
				if (!_head) { return; }
				// get head node
				node_pointer node = _head;
				// set new head node
				_head = _head->_next;
				// link to storage
				_store(node);
				// check if list is empty
				if (!_head) {
					// set tail node
					_tail = nullptr;
				} else {
					// set head's previous node
					_head->_prev = nullptr;
				} // decrement size
				--_size;
			}

			/* pop back */
			void pop_back(void) {
				// check if list is empty
				if (!_tail) { return; }
				// get tail node
				node_pointer node = _tail;
				// set new tail node
				_tail = _tail->_prev;
				// link to storage
				_store(node);
				// check if list is empty
				if (!_tail) {
					// set head node
					_head = nullptr;
				} else {
					// set tail's next node
					_tail->_next = nullptr;
				} // decrement size
				--_size;
			}

			/* clear list */
			void clear(void) noexcept {
				// destroy list
				_destroy_list();
				// initialize members
				_init();
			}


			// -- public swap -------------------------------------------------

			/* swap lists */
			void swap(self& other) noexcept {
				// declare temporary variables
				node_pointer node;
				size_type    size;
				// swap head
				node        = _head;
				_head       = other._head;
				other._head = node;
				// swap tail
				node        = _tail;
				_tail       = other._tail;
				other._tail = node;
				// swap size
				size        = _size;
				_size       = other._size;
				other._size = size;
			}

			void print(void) {
				// get head node
				node_pointer node = _head;
				// loop over list
				while (node) {
					std::cout << node->_value << std::endl;
					node = node->_next;
				}
			}


			// -- public iterator methods -------------------------------------

			/* begin */
			iterator begin(void) noexcept {
				// return iterator
				return iterator(_head);
			}

			/* begin */
			const_iterator begin(void) const noexcept {
				// return const iterator
				return const_iterator(_head);
			}

			/* end */
			xns::null end(void) const noexcept {
				// return null
				return nullptr;
			}


		private:

			// -- private members ---------------------------------------------

			/* new node */
			node_pointer new_node(void) {
				// check if free node is available
				if (_storage) {
					// get free node
					node_pointer node = _storage;
					// set storage node
					_storage = _storage->_next;
					// return free node
					return node;
				} // else allocate new node
				return allocator::allocate();
			}

			/* link storage */
			void _store(node_pointer node) {
				// destroy node
				allocator::destroy(node);
				// set node's next node
				node->_next = _storage;
				// set storage node
				_storage = node;
			}

			/* link node to front */
			void front_link(node_pointer node) {
				// check if list is empty
				if (!_head) {
					// set tail node
					_tail = node;
				// list is not empty
				} else {
					// set head's previous node
					_head->_prev = node;
					// set new node's next node
					node->_next = _head;
				} // in any case, set new head
				_head = node;
				// increment list size
				++_size;
			}

			/* link node to back */
			void back_link(node_pointer node) {
				// check if list is empty
				if (!_tail) {
					// set head node
					_head = node;
				// list is not empty
				} else {
					// set tail's next node
					_tail->_next = node;
					// set new node's previous node
					node->_prev = _tail;
				} // in any case, set new tail
				_tail = node;
				// increment list size
				++_size;
			}

			/* initialize members */
			void _init(void) noexcept {
				// initialize pointers
				_head = _tail = nullptr;
				// initialize size
				_size = 0;
			}

			/* free list */ // INFO: this only used in destructor
			inline void _free_list(void) noexcept {
				// get head node
				node_pointer node = nullptr;
				// loop over list
				while (_head) {
					 // unlink node
					 node = _head;
					_head = _head->_next;
					// destroy node
					allocator::destroy(node);
					// deallocate node
					allocator::deallocate(node);
				}
			}

			/* free storage */ // INFO: this only used in destructor
			inline void _free_storage(void) noexcept {
				// get storage node
				node_pointer node = nullptr;
				// loop over storage
				while (_storage) {
					    // unlink node
					    node = _storage;
					_storage = _storage->_next;
					// deallocate node
					allocator::deallocate(node);
				}
			}

			/* destroy list */
			inline void _destroy_list(void) noexcept {
				// declare node
				node_pointer node = nullptr;
				// loop over list
				while (_head) {
					 // unlink node
					 node = _head;
					_head = _head->_next;
					// store node (object destroyed in store method)
					_store(node);
				} // reset tail and size
				_tail = nullptr;
				_size = 0;
			}



			// -- private members ---------------------------------------------

			/* head node */
			node_pointer _head;

			/* tail node */
			node_pointer _tail;

			/* storage */
			node_pointer _storage;

			/* list size */
			size_type   _size;


	};


	// -- N O D E -------------------------------------------------------------

	template <class T>
	struct list<T>::node final {


		// -- constructors ----------------------------------------------------

		/* default constructor */
		node(void) noexcept
		: _value{}, _next{nullptr}, _prev{nullptr} {}

		/* non-assignable struct */
		NON_ASSIGNABLE(node);

		/* value copy constructor */
		node(const_reference value)
		: _value{value}, _next{nullptr}, _prev{nullptr} {}

		/* value move constructor */
		node(move_reference value) noexcept
		: _value{xns::move(value)}, _next{nullptr}, _prev{nullptr} {}

		/* value emplace constructor */
		template <typename... A>
		node(A&&... args)
		: _value{xns::forward<A>(args)...}, _next{nullptr}, _prev{nullptr} { }

		/* destructor */
		~node(void) noexcept = default;


		// -- members ---------------------------------------------------------

		/* value */
		value_type  _value;

		/* next node */
		node_pointer _next;

		/* previous node */
		node_pointer _prev;

	};


	// -- non-member functions ------------------------------------------------

	/* swap */
	template <class T>
	void swap(xns::list<T>& lhs, xns::list<T>& rhs) noexcept {
		// swap lists
		lhs.swap(rhs);
	}

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
			list_iterator(list_type::node_pointer node) noexcept
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
			xns::list<T>::node_pointer _node;

	};


}


#endif
