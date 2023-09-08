#ifndef TREE_HEADER
#define TREE_HEADER

#include "string.hpp"
#include "stack.hpp"
#include "types.hpp"
#include "tuple.hpp"
#include "safe_enum.hpp"
#include "bst_iterator.hpp"
#include "output.hpp"
#include "escape.hpp"
#include "terminal.hpp"
#include "math.hpp"
#include "memory.hpp"
#include "swap.hpp"
#include "conversions.hpp"

#include "is_convertible.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	/* has arithmetic operators concept */
	template <typename T>
	concept has_arithmetic_operators = requires(T a, T b) {
		{ a + b } -> xns::is_convertible<T>;
		{ a - b } -> xns::is_convertible<T>;
		{ a * b } -> xns::is_convertible<T>;
		{ a / b } -> xns::is_convertible<T>;
		{ a % b } -> xns::is_convertible<T>;
	};





	// -- T R E E -------------------------------------------------------------

	template <typename T>
	class tree {


		private:

			/* forward declaration */
			class printer;


			// -- friends -----------------------------------------------------

			/* bst iterator as friend */
			template <typename, xns::traversal_order, bool>
			friend class bst_iterator;

			/* print as friend */
			friend class printer;



		public:

			/* forward declaration */
			class node;


			// -- public types ------------------------------------------------

			/* self type */
			using self            = xns::tree<T>;

			/* value type */
			using value_type      = T;

			/* node type */
			using node_type       = self::node;

			/* allocator type */
			using allocator       = xns::memory::pool<node_type>;

			/* node pointer */
			using node_pointer    = node_type*;

			/* reference type */
			using reference       = value_type&;

			/* move reference type */
			using move_reference  = value_type&&;

			/* pointer type */
			using mutable_pointer = value_type*;

			/* const reference type */
			using const_reference = const value_type&;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* size type */
			using size_type       = xns::size_t;


			// -- iterators types ---------------------------------------------

			/* iterator type */
			template <typename O>
			using iterator = xns::bst_iterator<value_type, O, false>;

			/* const iterator type */
			template <typename O>
			using const_iterator = xns::bst_iterator<value_type, O, true>;


			/* pre-order iterator */
			using pre_order_iterator        = iterator<xns::pre_order>;

			/* in-order iterator */
			using in_order_iterator         = iterator<xns::in_order>;

			/* reverse in-order iterator */
			using reverse_in_order_iterator = iterator<xns::rev_in_order>;

			/* post-order iterator */
			using post_order_iterator       = iterator<xns::post_order>;

			/* bfs iterator */
			using bfs_iterator              = iterator<xns::bfs_order>;

			/* const pre-order iterator */
			using const_pre_order_iterator  = const_iterator<xns::pre_order>;

			/* const in-order iterator */
			using const_in_order_iterator   = const_iterator<xns::in_order>;

			/* const reverse in-order iterator */
			using const_reverse_in_order_iterator = const_iterator<xns::rev_in_order>;

			/* const post-order iterator */
			using const_post_order_iterator = const_iterator<xns::post_order>;

			/* const bfs iterator */
			using const_bfs_iterator        = const_iterator<xns::bfs_order>;


		private:

			// -- private members ---------------------------------------------

			/* root node */
			node_pointer _root;

			/* lower node */
			node_pointer _lower;

			/* upper node */
			node_pointer _upper;

			/* size */
			size_type    _size;


			// -- private enums -----------------------------------------------

			/* balance factor */
			enum : xns::s64 {
				   BALANCED =  0,
				 LEFT_HEAVY = +1,
				RIGHT_HEAVY = -1
			};



		public:

			// -- constructors ------------------------------------------------

			/* default constructor */
			inline tree(void) noexcept
			: _root{nullptr}, _lower{nullptr}, _upper{nullptr}, _size{0} {}

			/* copy constructor */
			tree(const self& other)
			: tree{} {

				for (auto it = other.bfs_begin(); it != nullptr; ++it) {
					insert(*it);
				}
			}

			/* move constructor */
			inline tree(self&& other) noexcept
			: _root{other._root}, _lower{other._lower}, _upper{other._upper}, _size{other._size} {
				// invalidate other
				other.init();
			}

			/* destructor */
			~tree(void) noexcept {
				// free tree
				free_tree();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) -> self& {
				// check for self-assignment
				if (this != &other) {
					free_tree();
					init();
					for (auto it = other.bfs_begin(); it != nullptr; ++it) {
						insert(*it);
					}
				} // return self reference
				return *this;
			}

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				// check for self-assignment
				if (this != &other) {
					// deallocate tree
					free_tree();
					// move other members
					_root    = other._root;
					_upper   = other._upper;
					_lower   = other._lower;
					_size    = other._size;
					// reset other tree
					other.init();
				} // return self reference
				return *this;
			}


			// -- public iterators --------------------------------------------

			/* pre-order iterator begin */
			inline auto pre_order_begin(void) noexcept -> pre_order_iterator {
				// return iterator to root
				return pre_order_iterator{_root};
			}

			/* in-order iterator begin */
			inline auto in_order_begin(void) noexcept -> in_order_iterator {
				// return iterator to root
				return in_order_iterator{_root};
			}

			/* reverse in-order iterator begin */
			inline auto reverse_in_order_begin(void) noexcept -> reverse_in_order_iterator {
				// return iterator to root
				return reverse_in_order_iterator{_root};
			}

			/* post-order iterator begin */
			inline auto post_order_begin(void) noexcept -> post_order_iterator {
				// return iterator to root
				return post_order_iterator{_root};
			}

			/* bfs iterator begin */
			inline auto bfs_begin(void) noexcept -> bfs_iterator {
				// return iterator to root
				return bfs_iterator{_root};
			}

			/* const pre-order iterator begin */
			inline auto pre_order_begin(void) const noexcept -> const_pre_order_iterator {
				// return iterator to root
				return const_pre_order_iterator{_root};
			}

			/* const in-order iterator begin */
			inline auto in_order_begin(void) const noexcept -> const_in_order_iterator {
				// return iterator to root
				return const_in_order_iterator{_root};
			}

			/* const reverse in-order iterator begin */
			inline auto reverse_in_order_begin(void) const noexcept -> const_reverse_in_order_iterator {
				// return iterator to root
				return const_reverse_in_order_iterator{_root};
			}

			/* const post-order iterator begin */
			inline auto post_order_begin(void) const noexcept -> const_post_order_iterator {
				// return iterator to root
				return const_post_order_iterator{_root};
			}

			/* const bfs iterator begin */
			inline auto bfs_begin(void) const noexcept -> const_bfs_iterator {
				// return iterator to root
				return const_bfs_iterator{_root};
			}

			/* iterator end */
			inline auto end(void) noexcept -> xns::null {
				// return iterator to null
				return nullptr;
			}

			/* const iterator end */
			inline auto end(void) const noexcept -> xns::null {
				// return iterator to null
				return nullptr;
			}


			// -- public accessors --------------------------------------------

			/* size */
			inline auto size(void) const noexcept -> size_type {
				// return size of tree
				return _size;
			}

			/* empty */
			inline auto empty(void) const noexcept -> bool {
				// return if tree is empty
				return _size == 0;
			}

			/* depth */
			inline auto depth(void) const noexcept -> size_type {
				// return depth of tree
				return _root ? _root->_depth : 0;
			}

			/* contains */
			inline auto contains(const value_type& value) const noexcept -> bool {

				/*
				if (not _root
					|| value < _lower->_value
					|| value > _upper->_value

						) { return false; }
						*/


				// get root node
				node_pointer node = _root;
				// loop over tree
				while (node != nullptr) {
					// less compare
					if      (value < node->_value) { node = node->_left;  }
					// greater compare
					else if (value > node->_value) { node = node->_right; }
					// value found
					else                           { return true; }
				} // return false
				return false;
			}





			/* find */
			template <typename K>
			auto find(const K& value) noexcept -> node_pointer {
				// assert K is comparable to T
				static_assert(xns::is_comparable<K, T>,
					"): TREE: K must be comparable to T :(");
				// get root node
				node_pointer node = _root;
				// loop over tree
				while (node != nullptr) {
					// less compare
					if      (value < node->_value) { node = node->_left;  }
					// greater compare
					else if (value > node->_value) { node = node->_right; }
					// value found
					else                           { break; }
				} // return node
				return node;
			}

			/* const find */
			//template <typename K>
			//auto find(const K& value) const noexcept -> const node_pointer {
			//	// assert K is comparable to T
			//	static_assert(xns::is_comparable<K, T>,
			//		"): TREE: K must be comparable to T :(");
			//	// get root node
			//	node_pointer node = _root;
			//	// loop over tree
			//	while (node != nullptr) {
			//		// less compare
			//		if      (value < node->_value) { node = node->_left;  }
			//		// greater compare
			//		else if (value > node->_value) { node = node->_right; }
			//		// value found
			//		else                           { break; }
			//	} // return node
			//	return node;
			//}




		public:

			// -- public modifiers --------------------------------------------

			/* insert */
			template <typename U = T>
			auto insert(U&& value) -> void {

				// assert U is same as T
				static_assert(xns::is_same<xns::remove_cvr<U>, T>,
					"): TREE: BAD INSERT TYPE :(");


				if (_root) {

					if (value < _lower->_value) {
						_lower->_left = new_node(_lower, xns::forward<U>(value));
						balance(_lower);
						_lower = _lower->_left;
						return;
					}
					else if (value > _upper->_value) {
						_upper->_right = new_node(_upper, xns::forward<U>(value));
						balance(_upper);
						_upper = _upper->_right;
						return;
					}

					// get root address
					node_type** node = &_root;
					node_type* parent = nullptr;
					// loop over tree
					while (*node != nullptr) {
						// set parent
						parent = *node;
						// less compare
						if      (value < (*node)->_value) { node = &(*node)->_left;  }
						// greater compare
						else if (value > (*node)->_value) { node = &(*node)->_right; }
						// else equal
						else { return; }
					}
					*node = new_node(parent, xns::forward<U>(value));
					balance(parent);
				}
				else {

					_root = new_node(nullptr, xns::forward<U>(value));
					_lower = _root;
					_upper = _root;
				}

			}





			// -- public subscript operator -----------------------------------

			/* subscript operator */
			template <typename K>
			auto operator[](const K& value) noexcept -> reference {
				static value_type dummy;
				return dummy;
				// assert K is comparable to T
				//static_assert(xns::is_comparable<K, T>,
				//	"): TREE: K must be comparable to T :(");
				//// get root address
				//node_type** node = &_root;
				//node_type* parent = nullptr;
				//// loop over tree
				//while (*node != nullptr) {
				//	// set parent
				//	parent = *node;
				//	// less compare
				//	if      (value < (*node)->_value) { node = &(*node)->_left;  }
				//	// greater compare
				//	else if (value > (*node)->_value) { node = &(*node)->_right; }
				//	// else equal
				//	else { return (*node)->_value; }
				//}

				//*node = new_node();
				//(*node)->_parent = parent;

				//++_size;
				//if (parent && parent->is_binary()) {
				//	return (*node)->_value;
				//}
				//balance(parent);

				//// return reference to new value
				//return (*node)->_value;
			}



			//template <typename... A>
			//auto emplace(A&&... args) -> void {
			//	// assert T is constructible from A
			//	static_assert(xns::is_constructible<T, A...>,
			//		"): TREE: T must be constructible from A... :(");
			//	// construct node
			//	node_pointer add = new_node(xns::forward<A>(args)...);
			//	// get root address
			//	node_type** node = &_root;
			//	node_type* parent = nullptr;

			//	while (*node != nullptr) {
			//		// set parent
			//		parent = *node;
			//		// get value
			//		value_type& _value = (*node)->_value;
			//		// less compare
			//		if      (add->_value < _value) { node = &(*node)->_left;  }
			//		// greater compare
			//		else if (add->_value > _value) { node = &(*node)->_right; }
			//		// else equal
			//		else {
			//			_store(add);
			//			return;
			//		}
			//	}
			//	add->_parent = parent;
			//	*node = add;
			//	balance(add);
			//	++_size;
			//}


			/* erase */
			template <typename K>
			inline auto erase(const K& value) noexcept -> void {
				// assert K is comparable to T
				static_assert(xns::is_comparable<K, T>,
					"): TREE: K must be comparable to T :(");
				// search for erase node
				erase(this->find(value));
			}

			/* erase from iterator */
			template <typename O>
			inline auto erase(const_iterator<O> it) noexcept -> void {
				// erase node
				erase(it._node);
			}

			auto erase(node_pointer node) -> void {
				// check pointer validity
				if (node == nullptr) { return; }

				node_pointer parent = node->_parent;


				// optimized way to check children (minimum number of conditions)

				if (node->has_left()) {
					return;
					// two children case
					if (node->has_right()) {
						return;
						std::cout << "two children case" << std::endl;
						node_pointer lhigh = node->_left;

						if (lhigh->_right) {
							lhigh = lhigh->_right;

							while (lhigh->_right) {
								lhigh = lhigh->_right;
							}
							lhigh->_parent->_right = lhigh->_left;

							if (lhigh->_left) {
								lhigh->_left->_parent = lhigh->_parent;
							}


							*get_side(node) = lhigh;

							lhigh->_left = node->_left;
							node->_left->_parent = lhigh;

							lhigh->_right = node->_right;
							node->_right->_parent = lhigh;

							lhigh->_parent = node->_parent;

						}
						else {
							*get_side(node) = lhigh;

							lhigh->_right = node->_right;
							node->_right->_parent = lhigh;

							lhigh->_parent = node->_parent;


						}




						/*
						// get parent's side
						*get_side(node) = node->_right;

						// set right child's parent to parent
						node->_right->_parent = node->_parent;

						node_pointer min = node->_right;
						// get minimum node
						while (min->_left) {
							min = min->_left;
						}

						min->_left = node->_left;
						node->_left->_parent = min;
						*/

					}
					// only left child case
					else {
						return;
						std::cout << "only left child case" << std::endl;
						// get parent's side
						*get_side(node) = node->_left;
						// set left child's parent to parent
						node->_left->_parent = node->_parent;
						erase_balance(parent);
					}
				}
				else {
					// only right child case
					if (node->has_right()) {
						return;
						std::cout << "only right child case" << std::endl;
						// get parent's side
						*get_side(node) = node->_right;
						// set right child's parent to parent
						node->_right->_parent = node->_parent;
						erase_balance(parent);
						print();
						check_tree(*this);
					}
					// no children case
					else {
						std::cout << "no children case" << std::endl;
						*get_side(node) = nullptr;
						erase_balance(parent);
						try {
							check_tree(*this);
						}
						catch (const std::exception& e) {
							std::cout << e.what() << std::endl;
							print();
							exit(1);
						}
						print();

					}
				}

				allocator::store(node);
				--_size;
				// print();
				// throw std::runtime_error("test");
				std::cout << "\x1b[32mEND OF ERASE\x1b[0m" << std::endl;
			}






			/* get root */
			node_pointer root(void) noexcept {
				return _root;
			}

			/* set root */
			void root(node_pointer node) noexcept {
				_root = node;
			}


			// -- node creation -----------------------------------------------

			/* new node by copied value */
			/*node_pointer new_node(const_reference value) {
				// declare node
				node_pointer node = _new_node();
				// construct node
				allocator::construct(node, value);
				++_size;
				// return node
				return node;
			}*/

			/* new node by moved value */
			/*node_pointer new_node(move_reference value) {
				// declare node
				node_pointer node = _new_node();
				// construct node
				allocator::construct(node, xns::move(value));
				++_size;
				// return node
				return node;
			}*/

			/* new node by construct in place */
			template <class... A>
			node_pointer new_node(node_pointer parent, A&&... args) {
				++_size; // increment size
				return allocator::make(parent, xns::forward<A>(args)...);
			}


			/* balance tree */
			auto balance(node_pointer node) noexcept -> void {

				// number of iterations does not depend on this condition
				if (node->is_binary()) { return; } // here for avoid unnecessary checks

				xns::s64 prev = 0;

				// move up the tree
				while (node != nullptr) {

					const auto ld = node->left_depth();
					const auto rd = node->right_depth();

					// update depth
					node->_depth = xns::max(ld, rd) + 1;

					// get balance factor
					const xns::s64 balance =
						static_cast<xns::s64>(ld) -
						static_cast<xns::s64>(rd);

					// exit if balanced
					if (balance == BALANCED) { break; }

					 // check for left heavy
					else if (balance > LEFT_HEAVY) {
						if (prev !=  1) { lr_rotate(node); }
						else           { rr_rotate(node); }
						return;
					}

					 // check for right heavy
					else if (balance < RIGHT_HEAVY) {
						if (prev != -1) { rl_rotate(node); }
						else           { ll_rotate(node); }
						return;
					}

					node = node->_parent;
					prev = balance;
				}
			}

			/* erase balance */
			auto erase_balance(node_pointer node) noexcept -> bool {


				xns::s64 prev = 0;

				// move up the tree
				while (node != nullptr) {

					const auto ld = node->left_depth();
					const auto rd = node->right_depth();

					// update depth
					node->_depth = xns::max(ld, rd) + 1;

					std::cout << "new depth: " << node->_depth << " [" << node->_value << "]" << std::endl;

					// get balance factor
					const xns::s64 balance =
						static_cast<xns::s64>(ld) -
						static_cast<xns::s64>(rd);

					std::cout << "new balance: " << balance << " [" << node->_value << "]" << std::endl;

					// std::cout << "balance: " << balance << " | " << node->_value << std::endl;

					// exit if balanced
					if (balance == BALANCED) { break; }

					 // check for left heavy
					else if (balance > LEFT_HEAVY) {
						// rr_rotate(node);
						// break;
						// if (node->_left->_right) {
						// 	lr_rotate(node);
						// }
						// else {
						// 	ll_rotate(node);
						// }



						if (prev !=  1) { lr_rotate(node); }
						else           { rr_rotate(node); }
					}

					 // check for right heavy
					else if (balance < RIGHT_HEAVY) {
						// ll_rotate(node);
						// break;
						// if (node->_right->_left) {
						// 	rl_rotate(node);
						// }
						// else {
						// 	rr_rotate(node);
						// }

						if (prev != -1) { rl_rotate(node); }
						else           { ll_rotate(node); }
					}

					node = node->_parent;
					prev = balance;
				}

				return true;
			}

			auto full_balance(void) -> void {

				for (auto it = post_order_begin(); it != nullptr; ++it) {
					balance(it._node);
				}
			}





			// -- subwidth ----------------------------------------------------

			// INFO: requires levels to be set

			/* get subtree maximum width from iterator */
			template <is_bst_iterator I>
			size_type max_width(const I& pos) const noexcept {
				// get node to construct bfs iterator
				const_bfs_iterator it{pos._node};
				// return max width
				return _max_width(it);
			}

			/* get subtree maximum width from node */
			size_type max_width(const node_pointer& node) const noexcept {
				// bfs node constructor
				const_bfs_iterator it{node};
				// return max width
				return _max_width(it);
			}

			/* get subtree maximum width impl */
			template <class I>
			inline size_type _max_width(I& it) const noexcept {
				// check iterator
				if (it == nullptr) { return 0; }
				// declare size
				size_type max = 0, count = 0;
				// declare level
				size_type level = it._node->_level;
				// loop until end
				while (it != nullptr) {
					// check level change
					if (level < it._node->_level) {
						level = it._node->_level;
						// compare count to max
						if (count > max) { max = count; }
						count = 0;
					} // increment count
					++count;
					// increment iterator
					++it;
				}
				// need to check last count
				if (count > max) { max = count; }
				// return max
				return max;
			}

			// INFO: requires levels to be set

			/* get level width */
			size_type level_width(const size_type level) const noexcept {
				// declare bst iterator
				const_bfs_iterator it{_root};
				// declare size
				size_type count = 0;
				// loop until end
				while (it != nullptr) {
					// check level overflow
					if (level > it._node->_level) { break; }
					// increment count if level matches
					count += (level == it._node->_level);
					// increment iterator
					++it;
				} // return count
				return count;
			}

			/* get endpoints number */
			template <is_bst_iterator I>
			size_type endpoints(const I& pos) const noexcept {
				// declare size
				size_type count = 0;
				// loop until end
				for (const_pre_order_iterator it{pos._node}; it; ++it) {
				//for (const_bfs_iterator it{pos._node}; it; ++it) {
					// check if node is endpoint
					count += it.is_endpoint();
				} // return count
				return count;
			}

			/* get endpoints number */
			size_type endpoints(const node_pointer& node) const noexcept {
				// declare size
				size_type count = 0;
				// loop until end
				for (const_pre_order_iterator it{node}; it; ++it) {
				//for (const_bfs_iterator it{node}; it; ++it) {
					// check if node is endpoint
					count += it.is_endpoint();
				} // return count
				return count;
			}

			/* get subtree size */
			auto subsize(const node_pointer& node) const noexcept -> size_type {
				// declare size
				size_type count = 0;
				// loop until end
				for (const_pre_order_iterator it{node}; it; ++it) {
					// increment count
					++count;
				} // return count
				return count;
			}



			// -- display -----------------------------------------------------

			/* print tree */
			inline auto print(void) -> void {
				// instantiate printer
				printer{*this}.display();
			}

			/* clear */
			void clear(void) noexcept {
				// free tree
				free_tree();
				// initialize members
				init();
			}

			/* swap */
			void swap(self& other) noexcept {
				// swap members
				xns::swap(_root,  other._root);
				xns::swap(_lower, other._lower);
				xns::swap(_upper, other._upper);
				xns::swap(_size,  other._size);
			}





		private:


			/* get side test */
			auto get_side(node_pointer node) noexcept -> node_type** {
				// return parent field address
				return node->_parent != nullptr ?
					(node->_parent->_left == node ?
					&node->_parent->_left : &node->_parent->_right)
					: &_root;
			}


			// -- depth -------------------------------------------------------

			/* update depth */
			static inline void update_depth(node_pointer node) noexcept {
				// get max depth
				node->_depth = xns::max(node->left_depth(),
										node->right_depth()) + 1;
			}

			/* update depth to root */
			static void update_depth_to_root(node_pointer node) noexcept {
				// loop until back to root
				for (node; node != nullptr; node = node->_parent) {
					// update depth
					update_depth(node);
				}
			}


			/* initialize members */
			inline void init(void) noexcept {
				// initialize members
				_root = _lower = _upper = nullptr;
				_size = 0;
			}


			// -- memory management -------------------------------------------

			/* free tree */ // INFO: this is only used in destructor
			inline void free_tree(void) noexcept {
				// declare post-order iterator
				post_order_iterator it{_root};
				// loop until end
				while (it) {
					// get node
					node_pointer node = it._node;
					// increment iterator
					++it;
					// deallocate node
					allocator::store(node);
				}
			}



			// -- R O T A T I O N S -------------------------------------------

			/* right rotation */
			auto rr_rotate(node_pointer node) noexcept -> void {
				// std::cout << "\x1b[32mRR ROTATION\x1b[0m" << std::endl;

				// left is new root
				auto root = node->_left;

				// connect to parent
				root->_parent = node->_parent;
				*get_side(node) = root;

				// handle root right
				if (root->_right) {
					root->_right->_parent = node;
				}   node->_left = root->_right;

				// handle node
				root->_right = node;
				node->_parent = root;

				// update depth
				node->_depth -= 2;
			}

			/* left rotation */
			auto ll_rotate(node_pointer node) noexcept -> void {
				// std::cout << "\x1b[32mLL ROTATION\x1b[0m" << std::endl;

				// right is new root
				auto root = node->_right;

				// connect to parent
				root->_parent = node->_parent;
				*get_side(node) = root;

				// handle root left
				if (root->_left) {
					root->_left->_parent = node;
				}   node->_right = root->_left;

				// handle node
				root->_left = node;
				node->_parent = root;

				// update depth
				node->_depth -= 2;
			}

			/* left right rotation */
			auto lr_rotate(node_pointer node) noexcept -> void {
				// std::cout << "\x1b[31mLR ROTATION\x1b[0m" << std::endl;


				auto lnode = node->_left;

				// left right is new root
				auto root = lnode->_right;

				if (root->_left) {
					root->_left->_parent = lnode;
				}   lnode->_right = root->_left;

				root->_left = lnode;
				lnode->_parent = root;


				root->_parent = node->_parent;
				*get_side(node) = root;

				if (root->_right) {
					root->_right->_parent = node;
				}   node->_left = root->_right;


				root->_right = node;
				node->_parent = root;

				--lnode->_depth;
				++root->_depth;
				node->_depth -= 2;


			}


			/* right left rotation */
			auto rl_rotate(node_pointer node) noexcept -> void {
				// std::cout << "\x1b[31mRL ROTATION\x1b[0m" << std::endl;

				auto rnode = node->_right;

				// right left is new root
				auto root = rnode->_left;

				if (root->_right) {
					root->_right->_parent = rnode;
				}   rnode->_left = root->_right;

				root->_right = rnode;
				rnode->_parent = root;


				root->_parent = node->_parent;
				*get_side(node) = root;

				if (root->_left) {
					root->_left->_parent = node;
				}   node->_right = root->_left;


				root->_left = node;
				node->_parent = root;

				--rnode->_depth;
				++root->_depth;
				node->_depth -= 2;

			}



	};


	// -- N O D E -------------------------------------------------------------

	template <typename T>
	class tree<T>::node {

		// -- friends ---------------------------------------------------------

		/* tree as friend */
		template <typename>
		friend class tree;

		/* pool allocator as friend */
		friend class xns::memory::pool<node>;

		/* bst iterator as friend */
		template <typename, xns::traversal_order, bool>
		friend class xns::bst_iterator;


		private:

			// -- private constructors ----------------------------------------

			/* deleted default constructor */
			node(void) = delete;

			/* non-assignable class */
			NON_ASSIGNABLE(node);

			/* value copy constructor */
			inline node(node* parent, const value_type& value)
			: _left{nullptr}, _right{nullptr}, _parent{parent},
			_depth{1}, _value{value} {}

			/* value move constructor */
			inline node(node* parent, value_type&& value) noexcept
			: _left{nullptr}, _right{nullptr}, _parent{parent},
			_depth{1}, _value{xns::move(value)} {}

			/* value emplace constructor */
			template <class... A>
			inline node(node* parent, A&&... args)
			: _left{nullptr}, _right{nullptr}, _parent{parent},
			_depth{1}, _value{xns::forward<A>(args)...} {}

			/* destructor */
			inline ~node(void) noexcept = default;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::tree<T>::node;

			/* size type */
			using size_type = xns::size_t;


			// -- accessors ---------------------------------------------------

			/* has left child */
			inline auto has_left(void) const noexcept -> bool {
				// return if node has left child
				return _left != nullptr;
			}

			/* has right child */
			inline auto has_right(void) const noexcept -> bool {
				// return if node has right child
				return _right != nullptr;
			}

			/* has children */
			inline auto has_child(void) const noexcept -> bool {
				// return if node has children
				return has_left() || has_right();
			}

			/* has parent */
			inline auto has_parent(void) const noexcept -> bool {
				// return if node has parent
				return _parent != nullptr;
			}

			/* is left child */
			inline auto is_left(void) const noexcept -> bool {
				// return if node is left child
				return _parent != nullptr && _parent->_left == this;
			}

			/* is right child */
			inline auto is_right(void) const noexcept -> bool {
				// return if node is right child
				return _parent != nullptr && _parent->_right == this;
			}

			/* is root */
			inline auto is_root(void) const noexcept -> bool {
				// return if node has no parent
				return _parent == nullptr;
			}

			/* is disconnected */
			inline auto is_disconnected(void) const noexcept -> bool {
				// return if node is disconnected
				return _parent == nullptr
						&& _left == nullptr
						&& _right == nullptr;
			}

			/* is leaf */
			inline auto is_leaf(void) const noexcept -> bool {
				// return if node has no children
				return has_child() == false;
			}

			/* is unary */
			inline auto is_unary(void) const noexcept -> bool {
				// return if only one child is null
				return has_left() != has_right();
			}

			/* is binary */
			inline bool is_binary(void) const noexcept {
				// return if node has two children
				return has_left() && has_right();
			}

			/* is endpoint */
			inline bool is_endpoint(void) const noexcept {
				// return if node is in extremity
				return is_leaf() || is_unary();
			}


			/* get value */
			inline auto value(void) noexcept -> reference {
				// return value
				return _value;
			}

			/* get const value */
			inline auto value(void) const noexcept -> const_reference {
				// return value
				return _value;
			}

			/* get left child */
			inline auto left(void) noexcept -> node_pointer {
				// return left
				return _left;
			}

			/* get right child */
			inline auto right(void) noexcept -> node_pointer {
				// return right
				return _right;
			}

			/* get left address */
			inline auto left_addr(void) noexcept -> node_pointer* {
				// return left address
				return &_left;
			}

			/* get right address */
			inline auto right_addr(void) noexcept -> node_pointer* {
				// return right address
				return &_right;
			}


			/* get parent */
			inline auto parent(void) noexcept -> node_pointer {
				// return parent
				return _parent;
			}

			/* get depth */
			inline xns::size_t depth(void) const noexcept {
				// return depth
				return _depth;
			}


			/* get left depth */
			inline auto left_depth(void) const noexcept -> size_type {
				// return left depth
				return _left ? _left->_depth : 0;
			}

			/* get right depth */
			inline auto right_depth(void) const noexcept -> size_type {
				// return right depth
				return _right ? _right->_depth : 0;
			}

			/* get balance factor */
			inline auto balance_factor(void) const noexcept -> xns::s64 {
				// return balance factor
				return static_cast<xns::s64>(left_depth()) -
					   static_cast<xns::s64>(right_depth());
			}

			/* update depth */
			inline auto update_depth(void) noexcept -> void {
				// get max depth
				_depth = xns::max(left_depth(), right_depth()) + 1;
			}

			// -- setters -----------------------------------------------------

			/* copy value */
			inline void set_value(const_reference value) noexcept {
				// set value
				_value = value;
			}

			/* move value */
			inline void set_value(value_type&& value) noexcept {
				// set value
				_value = xns::move(value);
			}

			/* set left child */
			inline void set_left(node_pointer node) noexcept {
				// set left
				_left = node;
				// set parent
				node->_parent = this;
			}

			/* set right child */
			inline void set_right(node_pointer node) noexcept {
				// set right
				_right = node;
				// set parent
				node->_parent = this;
			}

			/* get side */
			auto get_side(void) noexcept -> self** {
				// return parent field address
				return _parent != nullptr ?
					(_parent->_left == this ?
					&_parent->_left : &_parent->_right)
					: nullptr;
			}



		private:

			// -- private methods ---------------------------------------------

			/* initialization */
			void init(void) noexcept {
				// set links
				_left   = nullptr;
				_right  = nullptr;
				_parent = nullptr;
				// set depth
				_depth = 0;
			}

			// -- private members ---------------------------------------------


			/* links */
			node_pointer _left, _right, _parent;

			/* utility */
			xns::size_t _depth;

			/* value */
			value_type   _value;

	};


	// -- P R I N T -----------------------------------------------------------

	template <class T>
	class xns::tree<T>::printer final {

		private:

			// -- private constants -------------------------------------------

			/* unicode box enum */
			enum : xns::u8 { HL, VL, TL, TR, BL, BR, BB, MAX };

			/* unicode box array */
			static constexpr const xns::array<char32_t, MAX> _branch = {
				U'\u2500', // HL
				U'\u2502', // VL
				U'\u256D', // TL
				U'\u256E', // TR
				U'\u2570', // BL
				U'\u256F', // BR
				U'\u2534'  // BB
			};

			// multipliers
			enum : xns::size_t {
				Y_OFFSET = 3,
				X_OFFSET = 3
			};


		public:

			// -- public types ------------------------------------------------

			/* tree type */
			using tree_type = xns::tree<T>;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			printer(void) = delete;

			/* tree constructor */
			inline printer(xns::tree<T>& tree) noexcept
			: _tree{tree}, _nodes{}, _matrix{} {}

			/* non-assignable class */
			NON_ASSIGNABLE(printer);

			/* destructor */
			inline ~printer(void) noexcept = default;


			// -- public methods ----------------------------------------------

			/* display tree */
			void display(void) {

				std::cout << "START OF PRINT" << std::endl;
				// check root
				if (_tree._root == nullptr) { return; }

				_nodes.reserve(_tree.size());


				xns::s64 p_min = 0;
				xns::s64 p_max = 0;

				xns::size_t levels = 0;

				xns::queue<xns::tuple<node_pointer, node_info*>> queue;

				_nodes.emplace_back();

				queue.emplace(_tree._root, &_nodes.back());


				while (not queue.empty()) {

					auto tuple = queue.next();
					queue.dequeue();

					auto node = xns::get<node_pointer>(tuple);
					auto info = xns::get<node_info*>(tuple);

					info->value = xns::to_string(node->_value);
					info->depth = node->_depth;



					if (node->_left) {
						auto width = _tree.subsize(node->_left->_right) + 1;
						auto pos = info->pos - static_cast<xns::s64>(width);
						_nodes.emplace_back( info, // parent
											nullptr, // left
											nullptr, // right
											info->level + 1, // level
											pos, // position
											0U, // depth
											xns::string{});

						queue.emplace(node->_left, &_nodes.back());
						info->left = &_nodes.back();
					}

					if (node->_right) {
						auto width = _tree.subsize(node->_right->_left) + 1;
						auto pos = info->pos + static_cast<xns::s64>(width);
						_nodes.emplace_back( info, // parent
											nullptr, // left
											nullptr, // right
											info->level + 1, // level
											pos, // position
											0U, // depth
											xns::string{});

						queue.emplace(node->_right, &_nodes.back());
						info->right = &_nodes.back();

					}



					if      (info->pos < p_min) { p_min = info->pos; }
					else if (info->pos > p_max) { p_max = info->pos; }

					levels = info->level;
				}



				p_min *= -1;
				// compute width
				xns::size_t width = static_cast<xns::u64>(p_max)
									+ static_cast<xns::u64>(p_min);


				// compute positions
				for (auto& node : _nodes) {
					node.pos += p_min;
					node.pos *= X_OFFSET;
					//node.level *= Y_OFFSET;
					node.level = (levels + 1 - node.depth) * Y_OFFSET;
				}


				levels *= Y_OFFSET;
				width  *= X_OFFSET;
				++width;
				++levels;

				_matrix.reserve(levels);

				// fill matrix with spaces
				for (size_type y = 0; y < levels; ++y) {
					_matrix.emplace_back(U' ', width);
				}


				fill_matrix();
				render();
				std::cout << "END OF PRINT" << std::endl;
			}


			/* fill matrix */
			auto fill_matrix(void) -> void {


				// loop over nodes
				for (auto& node : _nodes) {

					size_type x = node.pos;
					size_type y = node.level;

					// check if left
					if (node.left != nullptr) {

						size_type lx = node.left->pos;
						size_type ly = node.left->level;

						// draw horizontal line
						for (size_type i = lx + 1; i < x + 1; ++i) {
							_matrix[y + 1][i] = _branch[HL];
						}
						// draw vertical line
						for (size_type i = y + 2; i < ly; ++i) {
							_matrix[i][lx] = _branch[VL];
						}
						// draw left corner
						_matrix[y + 1][lx] = _branch[TL];
					}


					if (node.right != nullptr) {

						size_type rx = node.right->pos;
						size_type ry = node.right->level;

						// draw horizontal line
						for (size_type i = x + 1; i < rx; ++i) {
							_matrix[y + 1][i] = _branch[HL];
						}
						// draw vertical line
						for (size_type i = y + 2; i < ry; ++i) {
							_matrix[i][rx] = _branch[VL];
						}
						// draw right corner
						_matrix[y + 1][rx] = _branch[TR];
					}


					if (node.left != nullptr || node.right != nullptr) {

						if (node.left != nullptr && node.right != nullptr) {
							_matrix[y + 1][x] = _branch[BB];
						}
						else if (node.left != nullptr) {
							_matrix[y + 1][x] = _branch[BR];
						}
						else if (node.right != nullptr) {
							_matrix[y + 1][x] = _branch[BL];
						}
					}

					auto& value = node.value;

					if (value.empty() == true) {
						_matrix[y][x] = '?';
						continue;
					}


					size_type size = value.size();
					size_type offset = size / 2;

					if (x > offset) {
						for (size_type i = 0; i < size; ++i) {
							_matrix[y][x - offset + i] = static_cast<char32_t>(value[i]);
						}
					}
					else {
						for (size_type i = 0; i < size; ++i) {
							_matrix[y][i] = static_cast<char32_t>(value[i]);
						}
					}
				}
			}



			/* render */
			inline auto render(void) -> void {
				// print matrix
				for (const xns::u32string& line : _matrix) {
					xns::print(line, '\n');
				} // render
				xns::out::render();
			}



		private:


			// -- private structs ---------------------------------------------

			/* node info */
			struct node_info final {

				// -- public lifecycle ------------------------------------

				/* default constructor */
				node_info(void) noexcept
				: parent{nullptr}, left{nullptr}, right{nullptr},
				level{0}, pos{0}, depth{0}, value{} {}

				/* members constructor */
				node_info(node_info* parent, node_info* left, node_info* right,
							xns::size_t level, xns::s64 pos, xns::size_t depth, xns::string value)
				: parent{parent}, left{left}, right{right},
				level{level}, pos{pos}, depth{depth}, value{value} {}

				/* move constructor */
				node_info(node_info&& other) noexcept = default;

				/* non-copyable struct */
				NON_COPYABLE(node_info);

				/* destructor */
				~node_info(void) noexcept = default;


				// -- public members --------------------------------------

				node_info* parent;
				node_info* left;
				node_info* right;

				xns::size_t level;
				xns::s64 pos;
				xns::size_t depth;
				xns::string value;

			};


			// -- private members ---------------------------------------------

			/* tree reference */
			xns::tree<T>& _tree;

			/* nodes */
			xns::vector<node_info> _nodes;

			/* matrix */
			xns::vector<xns::u32string> _matrix;

	};


	template <typename T>
	auto check_tree(const xns::tree<T>& tree) -> void {
		std::cout << "check tree\n";
		// check balance factor
		for (auto it = tree.pre_order_begin(); it != nullptr; ++it) {
			if (it.balance_factor() > 1
				|| it.balance_factor() < -1)
				throw std::runtime_error("tree is not balanced");
		}
		// check sorted
		const T* last = nullptr;
		auto it = tree.in_order_begin();
		if (it) { last = &*it; ++it; }
		while (it) {
			if (*last > *it)
				throw std::runtime_error("tree is not sorted");
			last = &*it;
			++it;
		}
	}


}


#endif




