#ifndef LIST_HEADER
#define LIST_HEADER

#include "types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include <iostream>
#include "macro.hpp"
#include "allocator.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- L I S T  C L A S S ----------------------------------------------------

	template <class T>
	class List final {

		public:

			// -- A L I A S E S -----------------------------------------------


			/* value type */
			using Value = T;

			/* self type */
			using Self = List<Value>;

			/* size type */
			using Size = SizeT;

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

			/* allocator type */
			using Allocator = xns::allocator<Value>;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			List(void)
			// initializations
			: _head{nullptr}, _tail{nullptr}, _size{0} { }

			/* copy constructor */
			List(const Self& other)
			// initializations
			: List{} {
				// assign other
				this->operator=(other);
			}

			/* move constructor */
			List(Self&& other) noexcept
			// initializations
			: _head{other._head}, _tail{other._tail}, _size{other._size} {
				// invalidate other list
				other.initialize_members();
			}

			/* destructor */
			~List(void) {
				// clear list
				clear();
			}


			// -- A S S I G N M E N T -----------------------------------------

			/* fill assignment */
			void assign(Size count, ConstReference value) {
				// clear list
				clear();
				// iterate over count
				for (Size x = 0; x < count; ++x) {
					// push back value
					push_back(value);
				}
			}


			// -- O P E R A T O R S -------------------------------------------

			/* assignment operator */
			List& operator=(const List& other) {
				// check for self assignment
				if (this != &other) {
					// clear list
					clear();
					// get other head
					Node* node = other._head;
					// iterate over other list
					while (node) {
						// push back value by copy
						push_back(node->_value);
						// get next node
						node = node->_next; }
				} // return self reference
				return *this;
			}

			/* move operator */
			List& operator=(List&& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// clear list
					clear();
					// assign head
					_head = other._head;
					// assign tail
					_tail = other._tail;
					// assign size
					_size = other._size;
					// invalidate other list
					other.initialize_members();
				} // return self reference
				return *this;
			}

			// WARNING: This is a very slow operation
			/* subscript operator */
			Reference operator[](Size index) {
				// get head
				NodePointer node = _head;
				// loop through list
				for (Size x = 0; x < index; ++x) {
					// get next node
					node = node->_next;
				} // return value
				return node->_value;
			}

			// WARNING: This is a very slow operation
			/* const subscript operator */
			ConstReference operator[](Size index) const {
				// get head
				NodePointer node = _head;
				// loop through list
				for (Size x = 0; x < index; ++x) {
					// get next node
					node = node->_next;
				} // return value
				return node->_value;
			}


			// -- E L E M E N T  A C C E S S ----------------------------------

			/* front element access */
			Reference front(void) {
				// return front element
				return _head->_value;
			}

			/* front element access */
			ConstReference front(void) const {
				// return front element
				return _head->_value;
			}

			/* back element access */
			Reference back(void) {
				// return back element
				return _tail->_value;
			}

			/* back element access */
			ConstReference back(void) const {
				// return back element
				return _tail->_value;
			}


			// -- A C C E S S O R S -------------------------------------------

			/* list size */
			Size size(void) const noexcept {
				// return list size
				return _size;
			}

			/* list empty */
			bool empty(void) const noexcept {
				// return list empty
				return _size == 0;
			}


			// -- M O D I F I E R S -------------------------------------------

			/* clear list */
			void clear(void) noexcept {
				// clear list
				NodePointer node = _head;
				// loop through list
				while (node) {
					// get next node
					NodePointer next = node->_next;
					// delete node
					delete node;
					// set next node
					node = next;
				} // initialize members
				initialize_members();
			}

			/* push front */
			void push_front(ConstReference value) {
				// allocate new node and link to front
				frontLink(new Node(value));
			}

			/* push front */
			void push_front(MoveReference value) noexcept {
				// allocate new node and link to front
				frontLink(new Node(xns::move(value)));
			}

			/* emplace front */
			template <typename... Args>
			void emplace_front(Args&&... args) {
				// allocate new node and link to front
				frontLink(new Node(xns::forward<Args>(args)...));
			}


			/* push back */
			void push_back(ConstReference value) {
				// allocate new node and link to back
				backLink(new Node(value));
			}

			/* push back */
			void push_back(MoveReference value) noexcept {
				// allocate new node and link to back
				backLink(new Node(xns::move(value)));
			}

			/* emplace back */
			template <typename... Args>
			void emplace_back(Args&&... args) {
				// allocate new node and link to back
				backLink(new Node(xns::forward<Args>(args)...));
			}

			/* pop front */
			void pop_front(void) {
				// check if list is empty
				if (!_head) { return; }
				// get head node
				NodePointer node = _head;
				// set new head node
				_head = _head->_next;
				// delete node
				delete node;
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
				NodePointer node = _tail;
				// set new tail node
				_tail = _tail->_prev;
				// delete node
				_free = node;
				//delete node;
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

			/* swap lists */
			void swap(List& other) noexcept {
				// declare variables
				NodePointer node;
				Size        size;
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

			void print_list(void) {
				NodePointer node = _head;
				while (node) {
					std::cout << node->_value << std::endl;
					node = node->_next;
				}
			}





		private:

			/* forward declaration */
			class Node;

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* node pointer type */
			using NodePointer = Node*;


			// -- P R I V A T E  M E T H O D S --------------------------------

			/* initialize members */
			void initialize_members(void) noexcept {
				// initialize pointers
				_head = _tail = nullptr;
				// initialize size
				_size = 0;
			}

			/* link node to front */
			void frontLink(NodePointer add) {
				// check allocation
				if (!add) { return; }
				// check if list is empty
				if (!_head) {
					// set tail node
					_tail = add;
				// list is not empty
				} else {
					// set head's previous node
					_head->_prev = add;
					// set new node's next node
					add->_next = _head;
				} // in any case, set new head
				_head = add;
				// increment list size
				++_size;
			}

			/* link node to back */
			void backLink(NodePointer add) {
				// check allocation
				if (!add) { return; }
				// check if list is empty
				if (!_tail) {
					// set head node
					_head = add;
				// list is not empty
				} else {
					// set tail's next node
					_tail->_next = add;
					// set new node's previous node
					add->_prev = _tail;
				} // in any case, set new tail
				_tail = add;
				// increment list size
				++_size;
			}





			// -- P R I V A T E  M E M B E R S --------------------------------

			/* head node */
			NodePointer _head;

			/* tail node */
			NodePointer _tail;

			/* list size */
			Size        _size;


			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			/* free node list */
			inline static Node* _free = nullptr;

	};


	// -- P R I V A T E  N O D E  C L A S S -----------------------------------

	template <typename T>
	class List<T>::Node final {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Node(void) noexcept
			// initializations
			: _value{}, _next{nullptr}, _prev{nullptr} { }

			/* copy constructor */
			Node(const Node& other)
			// initializations
			: _value{other._value}, _next{other._next}, _prev{other._prev} { }

			/* move constructor */
			Node(Node&& other) noexcept
			// initializations
			: _value{xns::move(other._value)}, _next{other._next}, _prev{other._prev} { }

			/* value copy constructor */
			Node(ConstReference value)
			// initializations
			: _value{value}, _next{nullptr}, _prev{nullptr} { }

			/* value move constructor */
			Node(MoveReference value) noexcept
			// initializations
			: _value{xns::move(value)}, _next{nullptr}, _prev{nullptr} { }

			/* value emplace constructor */
			template <typename... A>
			Node(A&&... args)
			// initializations
			: _value{xns::forward<A>(args)...}, _next{nullptr}, _prev{nullptr} { }

			/* destructor */
			~Node(void) {
				// clear node
			}


			// -- O P E R A T O R S -------------------------------------------

			/* deleted operators */
			NO_OPERATOR(Node, ==);


			// -- P U B L I C  M E M B E R S ----------------------------------

			/* value */
			Value   _value;

			/* next node */
			NodePointer _next;

			/* previous node */
			NodePointer _prev;

	};


	// -- N O N - M E M B E R  F U N C T I O N S ------------------------------

	/* swap */
	template <typename T>
	void swap(List<T>& lhs, List<T>& rhs) noexcept {
		// swap lists
		lhs.swap(rhs);
	}


};


#endif
