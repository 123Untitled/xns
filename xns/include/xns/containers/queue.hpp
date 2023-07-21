#ifndef QUEUE_HEADER
#define QUEUE_HEADER

// -- imports ----------------------------------------------------------------

#include <iostream>
#include "types.hpp"
#include "allocator.hpp"
#include "move.hpp"
#include "forward.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- Q U E U E -----------------------------------------------------------

	template <class T>
	class queue final {


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = queue<value_type>;

			/* reference type */
			using reference       = value_type&;

			/* move reference type */
			using move_reference  = value_type&&;

			/* const reference type */
			using const_reference = const value_type&;

			/* pointer type */
			using mutable_pointer = value_type*;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* size type */
			using size_type       = xns::size_t;


		private:

			// -- forwared declarations ---------------------------------------

			/* node type */
			struct node;


			// -- private types -----------------------------------------------

			/* node type */
			using node_type       = queue<value_type>::node;

			/* allocator type */
			using allocator       = xns::allocator<node_type>;

			/* node pointer type */
			using node_pointer    = typename allocator::mutable_pointer;


			// -- private members ---------------------------------------------

			/* head pointer */
			node_pointer _head;

			/* tail pointer */
			node_pointer _tail;

			/* storage */
			node_pointer _storage;

			/* size */
			size_type _size;


		public:

			// -- public constructors -----------------------------------------

			/* default constructor */
			queue(void) noexcept
			: _head{nullptr}, _tail{nullptr}, _storage{nullptr}, _size{0} {
				// nothing to do...
			}

			/* copy constructor */
			queue(const self& other) noexcept
			: _head{nullptr}, _tail{nullptr}, _storage{nullptr}, _size{0} {
				// declare node
				node_pointer node = other._head;
				// loop over other queue
				while (node != nullptr) {
					// enqueue copy of value
					enqueue(node->value);
					// move to next node
					node = node->next;
				}
				// INFO: optimization possible by copying storage
				// implement custom method for copying storage
				// update size only at the end
			}

			/* move constructor */
			queue(self&& other) noexcept
			: _head{other._head}, _tail{other._tail}, _storage{other._storage}, _size{other._size} {
				// invalidate other
				other._init();
				// invalidate storage
				other._storage = nullptr;
			}

			/* destructor */
			~queue(void) noexcept {
				// destroy and deallocate queue
				 _free_queue();
				// deallocate storage
				_free_storage();
			}


			// -- assignments -------------------------------------------------

			/* INFO: optimization possible by copying storage
			 * implement custom method for copying storage
			 * update size only at the end
			 */

			/* copy assignment */
			void assign(const self& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// destroy self queue
					_destroy_queue();
					// get other head
					node_pointer node = other._head;
					// loop over other queue
					while (node != nullptr) {
						// enqueue value by copy
						enqueue(node->value);
						// move to next node
						node = node->next; }
				}
			}

			/* INFO: storage is not moved!
			 * (simple linked list reason)
			 */

			/* move assignment */
			void assign(self&& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// destroy self queue
					_destroy_queue();
					// move other
					_head = other._head;
					_tail = other._tail;
					_size = other._size;
					// invalidate other queue
					other._init();
				}
			}


			// -- assignment operators ----------------------------------------

			/* copy assignment operator */
			self& operator=(const self& other) {
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


			// -- accessors ---------------------------------------------------

			/* get size */
			size_type size(void) const noexcept {
				// return size
				return _size;
			}

			/* is empty */
			bool empty(void) const noexcept {
				// return empty
				return _size == 0;
			}

			/* get first enqueued element */
			reference next(void) noexcept {
				// return front
				return _head->value;
			}

			/* get first enqueued const element */
			const_reference next(void) const noexcept {
				// return front
				return _head->value;
			}


			// -- modifiers ---------------------------------------------------

			/* enqueue copied element */
			void enqueue(const_reference value) noexcept {
				// create new node
				node_pointer node = _new_node();
				// check pointer
				if (node == nullptr) { return; }
				// construct node
				allocator::construct(node, value);
				// link node to queue
				_link(node);
				// update size
				++_size;
			}

			/* enqueue moved element */
			void enqueue(move_reference value) noexcept {
				// create new node
				node_pointer node = _new_node();
				// check pointer
				if (node == nullptr) { return; }
				// construct node
				allocator::construct(node, xns::move(value));
				// link node to queue
				_link(node);
				// update size
				++_size;
			}

			/* enqueue in-place constructed element */
			template <class... A>
			void enqueue(A&&... args) noexcept {
				// create new node
				node_pointer node = _new_node();
				// check pointer
				if (node == nullptr) { return; }
				// construct node
				allocator::construct(node, xns::forward<A>(args)...);
				// link node to queue
				_link(node);
				// update size
				++_size;
			}

			/* dequeue element */
			void dequeue(void) noexcept {
				// check size
				if (_size == 0) { return; }
				// get first enqueued node
				node_pointer node = _head;
				// unlink node
				_head = _head->next;
				// check for empty queue
				if (!_head) { _tail = nullptr; }
				// store node (object destroyed in store method)
				_store(node);
				// decrement size
				--_size;
			}

			/* clear queue */
			void clear(void) noexcept {
				// destroy queue
				_destroy_queue();
				// initialize members
				_init();
			}


		private:

			/* new node */
			inline node_pointer _new_node(void) noexcept {
				// declare node
				node_pointer node = nullptr;
				// check storage
				if (_storage) {
					// unlink from storage
						node = _storage;
					_storage = node->next;
				// else allocate new node
				} else { node = allocator::allocate(); }
				// return node
				return node;
			}

			/* link node */
			inline void _link(node_pointer node) noexcept {
				// check tail
				if (_tail != nullptr) {
					// link to tail
					_tail->next = node;
				// else link to head
				} else { _head = node; }
				// update tail
				_tail = node;
			}

			/* add to storage */
			inline void _store(node_pointer node) noexcept {
				// destroy node
				allocator::destroy(node);
				// link to storage
				node->next = _storage;
				  _storage = node;
			}

			/* initialize members */
			inline void _init(void) noexcept {
				// initialize members
				_head = nullptr;
				_tail = nullptr;
				_size = 0;
			}

			/* free queue */ // INFO: this is only used in destructor
			inline void _free_queue(void) noexcept {
				// declare node
				node_pointer node = nullptr;
				// loop over queue
				while (_head) {
					// unlink node
					node = _head;
					// set head to next node
					_head = node->next;
					// destroy node
					allocator::destroy(node);
					// deallocate node
					allocator::deallocate(node);
				}
			}

			/* free storage */ // INFO: this only used in destructor
			inline void _free_storage(void) noexcept {
				// declare node
				node_pointer node = nullptr;
				// loop over storage
				while (_storage) {
					// unlink node
					    node = _storage;
					_storage = node->next;
					// deallocate node
					allocator::deallocate(node);
				}
			}

			/* destroy queue */
			inline void _destroy_queue(void) noexcept {
				// declare node
				node_pointer node = nullptr;
				// loop over queue
				while (_head) {
					// unlink node
					 node = _head;
					_head = node->next;
					// store node (object destroyed in store method)
					_store(node);
				}
			}






	};


	// -- N O D E -------------------------------------------------------------

	template <class T>
	struct queue<T>::node {

		// -- members ---------------------------------------------------------

		/* value */
		value_type   value;

		/* next pointer */
		node_pointer next;


		// -- constructors ----------------------------------------------------

		/* default constructor */
		node(void) noexcept : value{}, next{nullptr} {
			// nothing to do...
		}

		/* copy value constructor */
		node(const_reference value) noexcept
		: value{value}, next{nullptr} {
			// nothing to do...
		}

		/* move value constructor */
		node(move_reference value) noexcept
		: value{xns::move(value)}, next{nullptr} {
			// nothing to do...
		}

		/* forward value constructor */
		template <class... A>
		node(A&&... args) noexcept
		: value{xns::forward<A>(args)...}, next{nullptr} {
			// nothing to do...
		}

		/* non-assignable struct */
		NON_ASSIGNABLE(node);

		/* destructor */
		~node(void) noexcept {
			// reset next pointer (for storage)
			next = nullptr;
		}


	};






}

#endif
