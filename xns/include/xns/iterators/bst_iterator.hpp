#ifndef DFS_ITERATOR_HEADER
#define DFS_ITERATOR_HEADER

#include "stack.hpp"
#include "queue.hpp"
#include "conditional.hpp"





// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* forward declaration */
	template <class>
	class tree;



	// -- traversal traits ----------------------------------------------------


	/* in-order traversal */
	struct in_order   final {};

	/* pre-order traversal */
	struct pre_order  final {};

	/* post-order traversal */
	struct post_order final {};

	/* breadth-first traversal */
	struct bfs_order  final {};


	/* traversal order concept */
	template <class T>
	concept traversal_order = xns::is_one_of<T, pre_order, in_order, post_order, bfs_order>;


	// -- tree iterator traits ------------------------------------------------

	/* forward declaration */
	template <class, traversal_order, bool>
	class bst_iterator;

	/* is tree iterator */
	template <class T>
	concept is_bst_iterator = xns::is_same<T, xns::bst_iterator<typename T::value_type,
																typename T::order_type,
																T::_const>>;


	// -- B S T  I T E R A T O R ----------------------------------------------

	template <class T, traversal_order O, bool C>
	class bst_iterator final {


		// -- friends ---------------------------------------------------------

		/* tree as friend */
		template <class>
		friend class tree;

		/* self type as friend */
		template <class, traversal_order, bool>
		friend class bst_iterator;


		private:

			// -- constants ---------------------------------------------------

			/* const iterator */
			static constexpr const bool _const = C;


		public:

			// -- public types ------------------------------------------------


			/* order type */
			using order_type      = O;

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = bst_iterator<T, O, C>;

			/* size type */
			using size_type       = typename xns::tree<T>::size_type;

			/* node pointer type */
			using node_pointer    = typename xns::tree<T>::node_pointer;

			/* pointer type */
			using pointer         = xns::conditional<_const, const value_type*,
																   value_type*>;

			/* reference type */
			using reference       = xns::conditional<_const, const value_type&,
																   value_type&>;

			/* container type */
			using container       = xns::conditional<
								  xns::is_same<order_type, bfs_order>,
								  xns::queue<node_pointer>,
								  xns::stack<node_pointer>>;


			// -- constructors ------------------------------------------------

			/* default constructor */
			bst_iterator(void) noexcept
			: _node{nullptr}, _container{} {
				// nothing to do...
			}

			/* const copy constructor */
			bst_iterator(const bst_iterator<T, O, true>& other) noexcept
			: _node{other._node}, _container{other._container} {
				// assert invalid conversion
				static_assert(_const, "): CAN'T COPY CONST BTS ITERATOR TO NON-CONST :(");
			}

			/* non-const copy constructor */
			bst_iterator(const bst_iterator<T, O, false>& other) noexcept
			: _node{other._node}, _container{other._container} {
				// nothing to do...
			}

			/* const move constructor */
			bst_iterator(bst_iterator<T, O, true>&& other) noexcept
			: _node{other._node}, _container{xns::move(other._container)} {
				// assert invalid conversion
				static_assert(_const, "): CAN'T MOVE CONST BTS ITERATOR TO NON-CONST :(");
			}

			/* non-const move constructor */
			bst_iterator(bst_iterator<T, O, false>&& other) noexcept
			: _node{other._node}, _container{xns::move(other._container)} {
				// nothing to do...
			}



			/* node pre-order constructor */
			bst_iterator(node_pointer node) noexcept requires(xns::is_same<order_type, pre_order>)
			: _node{node}, _container{} {
				// stack nodes
				if (_node) {
					if (_node->_right != nullptr) {
						_container.push(_node->_right);
					}
					if (_node->_left != nullptr) {
						_container.push(_node->_left);
					}
				}
			}

			/* node in-order constructor */
			bst_iterator(node_pointer node) noexcept requires(xns::is_same<order_type, in_order>)
			: _node{node}, _container{} {

				// check for null node
				if (_node == nullptr) return;

				// stack nodes
				while (_node != nullptr) {
					_container.push(_node);
					_node = _node->_left;
				}
				_node = _container.top();
				_container.pop();

				node_pointer tmp = _node->_right;
				while (tmp != nullptr) {
					_container.push(tmp);
					tmp = tmp->_left;
				}


			}

			/* node post-order constructor */
			bst_iterator(node_pointer node) noexcept requires(xns::is_same<order_type, post_order>)
			: _node{node}, _container{} {

				// check for null node
				if (_node == nullptr) return;

				while (_node != nullptr) {
					_container.push(_node);

					if (_node->_left != nullptr)
						_node = _node->_left;
					else
						_node = _node->_right;
				}

				_node = _container.top();
				_container.pop();
			}

			/* node breadth-first constructor */
			bst_iterator(node_pointer node) noexcept requires(xns::is_same<order_type, bfs_order>)
			: _node{node}, _container{} {
				// enqueue nodes
				if (_node) {
					if (_node->_left != nullptr) {
						_node->_left->_level = _node->_level + 1;
						_container.enqueue(_node->_left);
					}
					if (_node->_right != nullptr) {
						_node->_right->_level = _node->_level + 1;
						_container.enqueue(_node->_right);
					}
				}
			}

			/* destructor */
			~bst_iterator(void) noexcept = default;


			// -- assignment operators ----------------------------------------

			/* copy assignment operator */
			self& operator=(const self& other) noexcept {
				// check for self-assignment
				if (this != &other) {
					// copy data
					 _node = other._node;
					_container = other._container;
				} // return self reference
				return *this;
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// check for self-assignment
				if (this != &other) {
					// move data
					 _node = other._node;
					_container = xns::move(other._container);
				} // return self reference
				return *this;
			}


			// -- increment operators -----------------------------------------

			/* pre-increment pre-order operator */
			self& operator++(void) noexcept requires(xns::is_same<order_type, pre_order>) {

				// check if stack is empty
				if (_container.empty()) { _node = nullptr; }
				else {
					// get top node
					_node = _container.top();
					// pop node
					_container.pop();

					// push right child
					if (_node->_right != nullptr) {
						_container.push(_node->_right);
					}
					// push left child
					if (_node->_left != nullptr) {
						_container.push(_node->_left);
					}
				}
				return *this;
			}


			/* pre-increment in-order operator */
			self& operator++(void) noexcept requires(xns::is_same<order_type, in_order>) {

				// check if stack is empty
				if (_container.empty()) { _node = nullptr; }
				else {
					// get top node
					_node = _container.top();
					// pop node
					_container.pop();

					node_pointer node = _node->_right;

					while (node != nullptr) {
						_container.push(node);
						node = node->_left;
					}
				}
				return *this;
			}


			/* pre-increment post-order operator */
			self& operator++(void) noexcept requires(xns::is_same<order_type, post_order>) {

				// check if stack is empty
				if (_container.empty()) { _node = nullptr; }
				else {

					if (_node == _container.top()->_left) {

						node_pointer node = _container.top()->_right;

						while (node != nullptr) {

							_container.push(node);

							if (node->_left != nullptr)
								node = node->_left;
							else
								node = node->_right;
						}
						//_node = _container.top();
						//_container.pop();
					}
					//else {
						_node = _container.top();
						_container.pop();
					//}
				}

				return *this;
			}


			/* post-increment breadth operator */
			self& operator++(void) noexcept requires(xns::is_same<order_type, bfs_order>) {
				// check if queue is empty
				if (_container.empty()) { _node = nullptr; }
				else {
					// get next node
					_node = _container.next();
					// dequeue node
					_container.dequeue();

					// enqueue left
					if (_node->_left != nullptr) {
						_node->_left->_level = _node->_level + 1;
						_container.enqueue(_node->_left);
					}
					// enqueue right
					if (_node->_right != nullptr) {
						_node->_right->_level = _node->_level + 1;
						_container.enqueue(_node->_right);
					}
				} // return self reference
				return *this;
			}



			/* post-increment operator */
			self operator++(int) noexcept {
				// copy iterator (also copies stack)
				self tmp{*this};
				// increment this
				operator++();
				// return copy
				return tmp;
			}


			// -- self compare operators --------------------------------------

			/* equality operator */
			bool operator==(const self& other) const noexcept {
				// compare nodes
				return _node == other._node;
			}

			/* inequality operator */
			bool operator!=(const self& other) const noexcept {
				// compare nodes
				return _node != other._node;
			}


			// -- null pointer compare operators ------------------------------

			/* null pointer equality */
			bool operator==(xns::null) const noexcept {
				// compare node
				return _node == nullptr;
			}

			/* null pointer inequality */
			bool operator!=(xns::null) const noexcept {
				// compare node
				return _node != nullptr;
			}


			// -- boolean operators -------------------------------------------

			/* boolean operator */
			operator bool(void) const noexcept {
				// return node
				return _node != nullptr;
			}

			/* not operator */
			bool operator!(void) const noexcept {
				// return node
				return _node == nullptr;
			}


			// -- dereference operators ---------------------------------------

			/* dereference operator */
			reference operator*(void) const noexcept {
				// return value reference
				return _node->_value;
			}

			/* dereference operator */
			pointer operator->(void) const noexcept {
				// return value pointer
				return &_node->_value;
			}


			// -- node methods ------------------------------------------------

			/* has left child */
			inline bool has_left(void) const noexcept {
				// return if node has left child
				return _node->_left != nullptr;
			}

			/* has right child */
			inline bool has_right(void) const noexcept {
				// return if node has right child
				return _node->_right != nullptr;
			}

			/* has children */
			inline bool has_child(void) const noexcept {
				// return if node has children
				return _node->_left != nullptr || _node->_right != nullptr;
			}

			/* has parent */
			inline bool has_parent(void) const noexcept {
				// return if node has parent
				return _node->_parent != nullptr;
			}

			/* is left child */
			inline bool is_left(void) const noexcept {
				// return if node is left child
				return _node->_parent != nullptr && _node->_parent->_left == _node;
			}

			/* is right child */
			inline bool is_right(void) const noexcept {
				// return if node is right child
				return _node->_parent != nullptr && _node->_parent->_right == _node;
			}

			/* is root */
			inline bool is_root(void) const noexcept {
				// return if node has no parent
				return _node->_parent == nullptr;
			}

			/* is disconnected */
			inline bool is_disconnected(void) const noexcept {
				// return if node is disconnected
				return _node->_parent == nullptr && _node->_left == nullptr && _node->_right == nullptr;
			}

			/* is leaf */
			inline bool is_leaf(void) const noexcept {
				// return if node has no children
				return _node->_left == nullptr && _node->_right == nullptr;
			}

			/* is unary */
			inline bool is_unary(void) const noexcept {
				// return if only one child is null
				return (_node->_left == nullptr) != (_node->_right == nullptr);
			}

			/* is binary */
			inline bool is_binary(void) const noexcept {
				// return if node has two children
				return _node->_left != nullptr && _node->_right != nullptr;
			}

			/* is endpoint */
			inline bool is_endpoint(void) const noexcept {
				// return if node is in extremity
				return is_leaf() || is_unary();
			}



			// -- node access -------------------------------------------------

			/* address of node */
			inline node_pointer addrs(void) const noexcept {
				// return node
				return _node;
			}

			/* parent node */
			inline node_pointer parent(void) const noexcept {
				// return node
				return _node->_parent;
			}

			/* left node */
			inline node_pointer left(void) const noexcept {
				// return node
				return _node->_left;
			}

			/* right node */
			inline node_pointer right(void) const noexcept {
				// return node
				return _node->_right;
			}

			/* depth */
			inline size_type depth(void) const noexcept {
				// return depth
				return _node->_depth;
			}

			/* level */
			inline size_type level(void) const noexcept {
				// return level
				return _node->_level;
			}

			/* x position */
			inline xns::s64 xpos(void) const noexcept {
				// return position
				return _node->_pos;
			}





		private:

			// -- private members ---------------------------------------------

			/* node */
			node_pointer _node;

			/* container */
			container _container;


	};


}

#endif