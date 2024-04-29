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

#ifndef XNS_TREE_HEADER
#define XNS_TREE_HEADER

#include "xns/string/string.hpp"

#include "xns/containers/stack.hpp"
#include "xns/containers/queue.hpp"

#include "xns/type_traits/types.hpp"

#include "xns/terminal/output.hpp"

#include "xns/memory/fragmentation.hpp"

#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_comparable.hpp"

#include "xns/memory/allocator_traits.hpp"


#include <vector>
#include <queue>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T R E E -------------------------------------------------------------

	template <typename ___type,
			  typename ___alloc = xns::allocator<___type>>
	class tree {


		// -- assertions ------------------------------------------------------

		/* assert ___type is comparable */
		static_assert(xns::is_comparable<___type>,
				"tree: template type must be comparable");


		// -- friends ---------------------------------------------------------

		/* swap as friend */
		template <typename ___tp>
		friend auto swap(xns::tree<___tp>&, xns::tree<___tp>&) noexcept -> void;


		private:

			// -- forward declarations ----------------------------------------

			/* printer */
			class printer;

			/* printer as friend */
			friend class printer;

			/* ___node */
			class ___node;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self        = xns::tree<___type, ___alloc>;

			/* value type */
			using value_type  = ___type;

			/* node type */
			using node_type   = ___node;

			/* node pointer */
			using node_ptr    = node_type*;

			/* const node pointer */
			using const_node_ptr = const node_type*;

			/* reference type */
			using mut_ref     = value_type&;

			/* const reference type */
			using const_ref   = const value_type&;

			/* pointer type */
			using mut_ptr     = value_type*;

			/* const pointer type */
			using const_ptr   = const value_type*;

			/* size type */
			using size_type   = xns::size_t;

			/* signed type */
			using signed_type = xns::s64;

			/* allocator type */
			using allocator_type = ___alloc;


		private:

			// -- private types -----------------------------------------------

			/* node allocator type */
			//using ___allocator = typename ___alloc::template rebind<node_type>;
			using ___allocator = typename xns::allocator_traits<___alloc>::template rebind_alloc<node_type>;

			/* allocator traits type */
			using ___alloc_traits = xns::allocator_traits<___allocator>;

			/* lifecycle type */
			using ___lifecycle = xns::lifecycle<node_type>;



			/* traversal type */
			enum traversal_type : size_type {
				IN_ORDER, PRE_ORDER, POST_ORDER, BFS_ORDER
			};

			/* forward declaration */
			template <bool, traversal_type>
			class iterator;


		public:

			// -- iterator types ----------------------------------------------

			/* pre-order iterator */
			using pre_order_iterator        = iterator<false, PRE_ORDER>;

			/* in-order iterator */
			using in_order_iterator         = iterator<false, IN_ORDER>;

			/* post-order iterator */
			using post_order_iterator       = iterator<false, POST_ORDER>;

			/* bfs iterator */
			using bfs_iterator              = iterator<false, BFS_ORDER>;


			// -- const iterator types ----------------------------------------

			/* const pre-order iterator */
			using const_pre_order_iterator  = iterator<true, PRE_ORDER>;

			/* const in-order iterator */
			using const_in_order_iterator   = iterator<true, IN_ORDER>;

			/* const post-order iterator */
			using const_post_order_iterator = iterator<true, POST_ORDER>;

			/* const bfs iterator */
			using const_bfs_iterator        = iterator<true, BFS_ORDER>;


			/* reverse in-order iterator */
			//using reverse_in_order_iterator = iterator<xns::rev_in_order>;

			/* const reverse in-order iterator */
			//using const_reverse_in_order_iterator = const_iterator<xns::rev_in_order>;




		private:

			// -- private members ---------------------------------------------

			/* root node */
			node_ptr _root;

			/* lower */
			node_ptr _lower;

			/* upper */
			node_ptr _upper;

			/* size */
			size_type _size;


			// -- private enums -----------------------------------------------

			/* balance factor */
			enum : signed_type {
				BALANCED    =  0,
				LEFT_HEAVY  = +1,
				RIGHT_HEAVY = -1
			};



		public:

			// -- constructors ------------------------------------------------

			/* default constructor */
			tree(void) noexcept
			: _root{nullptr}, _lower{nullptr}, _upper{nullptr}, _size{0U} {
			}


			/* copy constructor */
			tree(const self& other)
			: tree{} {

				for (auto it = other.in_order_begin(); it != nullptr; ++it)
					insert(*it);
			}

			/* move constructor */
			tree(self&& other) noexcept
			: _root{other._root}, _lower{other._lower}, _upper{other._upper}, _size{other._size} {
				other.init();
			}

			/* destructor */
			~tree(void) noexcept {
				free_tree();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) -> self& {
				// check for self-assignment
				if (this == &other)
					return *this;
				free_tree();
				init();
				for (auto it = other.bfs_begin(); it != nullptr; ++it)
					insert(*it);
				// return self reference
				return *this;
			}

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				// check for self-assignment
				if (this == &other)
					return *this;
				// deallocate tree
				free_tree();
				// move other members
				 _root = other._root;
				_lower = other._lower;
				_upper = other._upper;
				 _size = other._size;
				 // reset other tree
				 other.init();
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			inline auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* size in bytes */
			inline auto size_in_bytes(void) const noexcept -> size_type {
				return _size * sizeof(node_type);
			}

			/* empty */
			inline auto empty(void) const noexcept -> bool {
				return _size == 0;
			}

			/* depth */
			inline auto depth(void) const noexcept -> size_type {
				return _root ? static_cast<size_type>(_root->_depth) : 0U;
			}


			/* contains */
			inline auto contains(const value_type& value) const noexcept -> bool {
				// get root node
				const_node_ptr node = _root;
				// loop over tree
				while (node != nullptr) {
					// equality
					if (value == node->_value)
						return true;
					// ternary compare
					node = (value < node->_value) ? node->_left : node->_right;
				} // return false
				return false;
			}


			/* apply if exists */
			template <typename K, typename F>
			auto apply_if_exists(K&& value, F&& func) noexcept -> int {
				// assert K is comparable to T
				static_assert(xns::is_comparable<K, ___type>,
					"): TREE: K must be comparable to T :(");
				// get root node
				node_ptr node = _root;
				// loop over tree
				while (node != nullptr) {
					// equality
					if (value == node->_value) { func(node->_value); return 0; }
					// ternary compare
					node = (value < node->_value) ? node->_left : node->_right;
				}
				return -1;
			}



		public:

			// -- public modifiers --------------------------------------------


			/* merge */
			auto merge(const self& other) noexcept -> void {
				for (auto it = other.bfs_begin(); it != nullptr; ++it) {
					insert(*it);
				}
			}

			/* merge */
			auto merge(self&& other) -> void {
				for (auto it = other.bfs_begin(); it != nullptr; ++it) {
					insert(*it);
					other.erase(*it);
				}
			}

			/* defragment (slow operation) */
			auto defragment(void) -> void {

				xns::allocator<value_type> a;

				mut_ptr vec = xns::allocator_traits<xns::allocator<value_type>>::allocate(a, _size);
				//mut_ptr vec = xns::allocator<value_type>::allocate(_size);

				auto ptr = vec;

				// iterate over tree (in-order traversal)
				// and move sorted values to vector
				for (auto it = begin(); it; ++it, ++ptr) {
					// move value
					*ptr = xns::move(*it);
				}

				// move root
				node_ptr tmp = _root;
				_root = nullptr;

				// loop over tmp tree
				for (auto it = bfs_begin(tmp); it; ++it) {

					// insert node by comparing pointers

					// get root address
					node_type** node = &_root;
					node_ptr parent = nullptr;

					while (*node != nullptr) {
						// set parent
						parent = *node;
						// get next node
						node = &(it._node < *node ? (**node)._left : (**node)._right);
					}

					// manually construct node
					// value is already constructed

					it._node->_parent = parent;
					it._node->_left = nullptr;
					it._node->_right = nullptr;
					it._node->_depth = 1;
					*node = it._node;
					balance(parent);
				}

				_lower = nullptr;
				_upper = nullptr;

				ptr = vec;
				// loop over tree (in-order traversal) and sorted vector
				for (auto it = in_order_begin(); it; ++it, ++ptr) {
					// move value
					*it = xns::move(*ptr);

					if (_lower == nullptr) {
						_lower = _upper = it._node;
					}
					else {
						if (*it < _lower->_value) {
							_lower = it._node;
						}
						else if (*it > _upper->_value) {
							_upper = it._node;
						}
					}
				}

				xns::allocator_traits<xns::allocator<value_type>>::deallocate(a, vec);
				//xns::allocator<value_type>::deallocate2(vec);
			}


			auto fragmentation(void) const -> void {

				std::vector<void*> vec;
				vec.reserve(_size);

				for (auto it = begin(); it != nullptr; ++it)
					vec.push_back(it._node);

				xns::fragmentation::display(vec);
			}




			/* insert */
			template <typename U>
			auto insert(U&& value) -> void {
				// assert T is constructible from U
				static_assert(xns::is_constructible<___type, U>,
					"): TREE: BAD INSERT TYPE :(");

				return    _root == nullptr ? insert_root(xns::forward<U>(value))  :
					value < _lower->_value ? insert_lower(xns::forward<U>(value)) :
					value > _upper->_value ? insert_upper(xns::forward<U>(value)) :
											insert_global(xns::forward<U>(value));
			}

			/* emplace insert */
			template <typename... A>
			auto emplace(A&&... args) -> void {

				// assert T is constructible from A
				static_assert(xns::is_constructible<___type, A...>,
					"): TREE: BAD INSERT TYPE :(");

			}

			template <typename U>
			auto insert_global(U&& value) -> void {
				// get root address
				node_type** node = &_root;
				node_ptr parent = nullptr;

				while (*node != nullptr) {

					// set parent
					parent = *node;

					// equal compare
					if (value == (**node)._value)
						return;

					// get next node
					node = &(value < (**node)._value ? (**node)._left : (**node)._right);
				}

				*node = make_node(parent, xns::forward<U>(value));
				balance(parent);


				//auto nd = *node;
				//// experimental swap node
				//	if ((*node)->_right) {
				//		if (*node < (*node)->_right) {
				//			auto rt = (*node)->_right;
				//			swap_right(nd, rt);
				//			*node = rt;
				//		}
				//	}
			}

			template <typename U>
			auto insert_root(U&& value) -> void {
				_root = make_node(nullptr, xns::forward<U>(value));
				_lower = _upper = _root;
			}

			template <typename U>
			auto insert_lower(U&& value) -> void {
				_lower->_left = make_node(_lower, xns::forward<U>(value));
				_lower = _lower->_left;
				balance(_lower->_parent);
			}

			template <typename U>
			auto insert_upper(U&& value) -> void {
				_upper->_right = make_node(_upper, xns::forward<U>(value));
				_upper = _upper->_right;
				balance(_upper->_parent);
			}



			/* balance tree */
			auto balance(node_ptr node) noexcept -> void {

				signed_type prev = 0;

				//size_type i = 0;
				signed_type ld, rd, depth, balance;

				if (node == nullptr) return;

				{
					ld    = node->left_depth();
					rd    = node->right_depth();
					depth = xns::max(ld, rd) + 1;

					if (depth == node->_depth) { return; }
					// update depth
					node->_depth = depth;

					node = node->_parent;
					prev = ld - rd;
				}

				if (node == nullptr) return;

				{

					ld    = node->left_depth();
					rd    = node->right_depth();
					depth = xns::max(ld, rd) + 1;

					if (depth == node->_depth) { return; }
					// update depth
					node->_depth = depth;
					// get balance factor
					balance = ld - rd;

					// check for left heavy
					if (balance > LEFT_HEAVY) {
						return prev != LEFT_HEAVY ?
							lr_rotate(node) : rr_rotate(node);
					}

					// check for right heavy
					else if (balance < RIGHT_HEAVY) {
						return prev != RIGHT_HEAVY ?
							rl_rotate(node) : ll_rotate(node);
					}

					node = node->_parent;
					prev = balance;
				}

				// move up the tree
				while (node != nullptr) {

					ld    = node->_left->_depth;
					rd    = node->_right->_depth;
					depth = xns::max(ld, rd) + 1;

					if (depth == node->_depth) {
						//std::cout << "depth unchanged: " << i << std::endl;
						return;
					}

					// update depth
					node->_depth = depth;

					// get balance factor
					balance = ld - rd;

					// if balance == BALANCED (no need to check if depth is unchanged (same as balanced))

					// check for left heavy
					if (balance > LEFT_HEAVY) {
						return prev != LEFT_HEAVY ?
							lr_rotate(node) : rr_rotate(node);
					}

					// check for right heavy
					else if (balance < RIGHT_HEAVY) {
						return prev != RIGHT_HEAVY ?
							rl_rotate(node) : ll_rotate(node);
					}

					node = node->_parent;
					prev = balance;
					//++i;
				}
				//std::cout << "back to root: " << i << std::endl;
			}




			/* erase */
			template <typename K>
			auto erase(const K& value) noexcept -> void {

				// assert K is comparable to T
				static_assert(xns::is_comparable<K, ___type>,
						"tree: K must be comparable to T");

				// get root address
				node_type**  node = &_root;
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
					else { goto erase; }
				}

				return;

				erase:
				// optimized way to check children (minimum number of conditions)

				if (node->has_left()) {
					return;
					// two children case
					if (node->has_right()) {
						return;
						std::cout << "two children case" << std::endl;
						node_ptr lhigh = node->_left;

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

						node_ptr min = node->_right;
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
						int ret = check_tree(*this);
						if (ret == -1) {
							std::cout << "tree is unbalanced" << std::endl;
							exit(1);
						}
						else if (ret == -2) {
							std::cout << "three is not sorted" << std::endl;
							exit(1);
						}
						print();
					}
				}

				//allocator::store(node);
				--_size;
				// print();
				// throw std::runtime_error("test");
				std::cout << "\x1b[32mEND OF ERASE\x1b[0m" << std::endl;
			}





			// -- node creation -----------------------------------------------

			/* new node by construct in place */
			template <typename... A>
			inline auto make_node(node_ptr parent, A&&... args) -> node_ptr {
				// allocate and construct node
				___allocator a{};
				node_ptr node = ___alloc_traits::allocate(a);
				___lifecycle::construct(node, parent, xns::forward<A>(args)...);
				// increment size
				++_size;
				return node;
			}


			/* erase balance */
			auto erase_balance(node_ptr node) noexcept -> bool {


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


			/* get subtree size */
			auto subsize(const node_ptr& node) const noexcept -> size_type {
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
			inline auto clear(void) noexcept -> void {
				free_tree();
				init();
			}

			/* swap */
			inline auto swap(self& other) noexcept -> void {
				xns::swap(*this, other);
			}


		private:


			/* replace node */
			inline auto replace(node_ptr node, node_ptr child) noexcept -> void {
				(node->_parent ?
				(node->_parent->_left == node ? node->_parent->_left
											: node->_parent->_right)
											: _root) = child;
			}


			// -- depth -------------------------------------------------------

			/* update depth */
			static inline void update_depth(node_ptr node) noexcept {
				// get max depth
				node->_depth = xns::max(node->left_depth(),
										node->right_depth()) + 1;
			}

			/* update depth to root */
			static void update_depth_to_root(node_ptr node) noexcept {
				// loop until back to root
				for (node; node != nullptr; node = node->_parent) {
					// update depth
					update_depth(node);
				}
			}


			/* initialize members */
			inline void init(void) noexcept {
				// initialize members
				_root = nullptr;
				_lower = nullptr;
				_upper = nullptr;
				_size = 0;
			}


			// -- memory management -------------------------------------------

			/* free tree */ // INFO: this is only used in destructor
			void free_tree(void) noexcept {
				// declare post-order iterator
				self::post_order_iterator it{_root};
				// loop until end
				while (it) {
					// get node
					node_ptr node = it._node;
					// increment iterator
					++it;
					// destroy node
					___lifecycle::destroy(node);
					___allocator a{};
					// deallocate node
					___alloc_traits::deallocate(a, node);
					//allocator::deallocate2(node);
				}
			}


			// -- update depth of all nodes -----------------------------------

			/* update depth of all nodes */
			inline void update_depth(void) noexcept {
				// declare post-order iterator
				post_order_iterator it{_root};
				// loop until end
				while (it) {
					// update depth
					it._node->update_depth();
					// increment iterator
					++it;
				}
			}


			// -- R O T A T I O N S -------------------------------------------

			/* right rotation */
			auto rr_rotate(node_ptr node) noexcept -> void {
				//std::cout << "\x1b[32mRR ROTATION\x1b[0m" << std::endl;

				// left is new root
				const auto root = node->_left;
				// connect root
				replace(node, root);

				/*
				 *       N
				 *      /
				 *     R
				 *    /
				 *   C
				 */

				// update root parent
				root->_parent = node->_parent;
				// update node parent
				node->_parent = root;

				/*
				 *       N
				 *      /
				 *     R
				 *    / \
				 *   C   ?
				 */

				// handle root right
				if (root->_right) {
					root->_right->_parent = node;
				} node->_left = root->_right;

				// connect node
				root->_right = node;

				/*
				 *     R
				 *    / \
				 *   C   N
				 *      /
				 *     ?
				 */

				// update depth
				node->_depth -= 2;
			}

			/* left rotation */
			auto ll_rotate(node_ptr node) noexcept -> void {
				//std::cout << "\x1b[32mLL ROTATION\x1b[0m" << std::endl;

				// right is new root
				const auto root = node->_right;
				// connect root
				replace(node, root);

				/*
				 *   N
				 *    \
				 *     R
				 *      \
				 *       C
				 */

				// update root parent
				root->_parent = node->_parent;
				// update node parent
				node->_parent = root;

				/*
				 *   N
				 *    \
				 *     R
				 *    / \
				 *   ?   C
				 */

				// handle root left
				if (root->_left) {
					root->_left->_parent = node;
				}   node->_right = root->_left;

				// connect node
				root->_left = node;

				/*
				 *     R
				 *    / \
				 *   N   C
				 *    \
				 *     ?
				 */

				// update depth
				node->_depth -= 2;
			}


			/* left right rotation */
			auto lr_rotate(node_ptr node) noexcept -> void {
				//std::cout << "\x1b[31mLR ROTATION\x1b[0m" << std::endl;

				const auto left = node->_left;

				// left right is new root
				const auto root = left->_right;

				// connect root
				replace(node, root);

				/*
				 *     N
				 *    /
				 *   L
				 *    \
				 *     R
				 *    / \
				 *   ?1 ?2
				 */

				// handle root left
				if (root->_left) {
					root->_left->_parent = left;
				} left->_right = root->_left;

				/*
				 *     N
				 *    /
				 *   L
				 *    \
				 *    ?1
				 */

				// connect root
				root->_left = left;
				left->_parent = root;

				/*
				 *     R
				 *    / \
				 *   L  ?2
				 *    \
				 *    ?1
				 */

				// update root parent
				root->_parent = node->_parent;
				// update node parent
				node->_parent = root;

				// handle root right
				if (root->_right) {
					root->_right->_parent = node;
				} node->_left = root->_right;

				// connect node
				root->_right = node;

				/*
				 *      R
				 *    /   \
				 *   L     N
				 *    \   /
				 *    ?1 ?2
				 */

				left->_depth -= 1;
				root->_depth += 1;
				node->_depth -= 2;
			}


			/* right left rotation */
			auto rl_rotate(node_ptr node) noexcept -> void {
				//std::cout << "\x1b[31mRL ROTATION\x1b[0m" << std::endl;

				auto rnode = node->_right;

				// right left is new root
				auto root = rnode->_left;

				if (root->_right) {
					root->_right->_parent = rnode;
				}   rnode->_left = root->_right;

				root->_right = rnode;
				rnode->_parent = root;


				root->_parent = node->_parent;
				replace(node, root);

				if (root->_left) {
					root->_left->_parent = node;
				}   node->_right = root->_left;


				root->_left = node;
				node->_parent = root;

				--rnode->_depth;
				++root->_depth;
				node->_depth -= 2;

			}

		public:

			// -- public iterators --------------------------------------------

			/* begin */
			inline auto begin(void) noexcept -> in_order_iterator {
				return in_order_iterator{_root};
			}

			/* const begin */
			inline auto begin(void) const noexcept -> const_in_order_iterator {
				return const_in_order_iterator{_root};
			}


			// -- pre-order iterators -----------------------------------------

			/* pre-order iterator begin */
			inline auto pre_order_begin(void) noexcept -> pre_order_iterator {
				return pre_order_iterator{_root};
			}

			/* pre-order iterator begin */
			inline auto pre_order_begin(node_ptr node) noexcept -> pre_order_iterator {
				return pre_order_iterator{node};
			}


			// -- in-order iterators ------------------------------------------

			/* in-order iterator begin */
			inline auto in_order_begin(void) noexcept -> in_order_iterator {
				return in_order_iterator{_root};
			}

			/* const in-order iterator begin */
			inline auto in_order_begin(void) const noexcept -> const_in_order_iterator {
				return const_in_order_iterator{_root};
			}

			/* reverse in-order iterator begin */
			//inline auto reverse_in_order_begin(void) noexcept -> reverse_in_order_iterator {
			//	return reverse_in_order_iterator{_root};
			//}

			/* const reverse in-order iterator begin */
			//inline auto reverse_in_order_begin(void) const noexcept -> const_reverse_in_order_iterator {
			//	return const_reverse_in_order_iterator{_root};
			//}


			// -- post-order iterators ----------------------------------------

			/* post-order iterator begin */
			inline auto post_order_begin(void) noexcept -> post_order_iterator {
				return post_order_iterator{_root};
			}


			/* bfs iterator begin */
			inline auto bfs_begin(void) noexcept -> bfs_iterator {
				return bfs_iterator{_root};
			}

			/* bfs iterator begin */
			inline auto bfs_begin(node_ptr node) noexcept -> bfs_iterator {
				return bfs_iterator{node};
			}

			/* const bfs iterator begin */
			inline auto bfs_begin(void) const noexcept -> const_bfs_iterator {
				return const_bfs_iterator{_root};
			}


			/* const pre-order iterator begin */
			inline auto pre_order_begin(void) const noexcept -> const_pre_order_iterator {
				return const_pre_order_iterator{_root};
			}



			/* const post-order iterator begin */
			inline auto post_order_begin(void) const noexcept -> const_post_order_iterator {
				return const_post_order_iterator{_root};
			}


			/* iterator end */
			inline auto end(void) const noexcept -> decltype(nullptr) {
				return nullptr;
			}

	}; // class tree


	// -- friend functions ----------------------------------------------------

	/* swap */
	template <typename T>
	inline auto swap(xns::tree<T>& lhs, xns::tree<T>& rhs) noexcept -> void {

		typename xns::tree<T>::node_ptr ptr;

		ptr = lhs._root;
		lhs._root = rhs._root;
		rhs._root = ptr;

		ptr = lhs._lower;
		lhs._lower = rhs._lower;
		rhs._lower = ptr;

		ptr = lhs._upper;
		lhs._upper = rhs._upper;
		rhs._upper = ptr;

		const auto size = lhs._size;
			  lhs._size = rhs._size;
			  rhs._size = size;
	}



	// -- N O D E -------------------------------------------------------------

	template <typename ___type, typename ___alloc>
	class xns::tree<___type, ___alloc>::___node final {


		// -- friends ---------------------------------------------------------

		/* tree as friend */
		template <typename, typename>
		friend class tree;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::tree<___type, ___alloc>::___node;


		private:

			// -- private members ---------------------------------------------

			/* value */
			value_type _value;

			/* links */
			node_ptr _left, _right, _parent;

			/* utility */
			signed_type _depth;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			___node(void) = delete;

			/* not assignable class */
			___xns_not_assignable(___node);

			/* varidic constructor */
			template <class... A>
			___node(node_ptr parent, A&&... args)
			: _value{xns::forward<A>(args)...}, _left{nullptr}, _right{nullptr}, _parent{parent}, _depth{1} {
			}

			/* destructor */
			~___node(void) noexcept = default;



		public:

			// -- accessors ---------------------------------------------------

			/* has left */
			auto has_left(void) const noexcept -> bool {
				return _left != nullptr;
			}

			/* has right */
			auto has_right(void) const noexcept -> bool {
				return _right != nullptr;
			}

			/* has child */
			auto has_child(void) const noexcept -> bool {
				return has_left() || has_right();
				//return _left != nullptr || _right != nullptr;
			}

			/* has parent */
			auto has_parent(void) const noexcept -> bool {
				return _parent != nullptr;
			}

			/* is left */
			auto is_left(void) const noexcept -> bool {
				return _parent != nullptr && _parent->_left == this;
			}

			/* is right */
			auto is_right(void) const noexcept -> bool {
				return _parent != nullptr && _parent->_right == this;
			}

			/* is root */
			auto is_root(void) const noexcept -> bool {
				return _parent == nullptr;
			}

			/* is disconnected */
			auto is_disconnected(void) const noexcept -> bool {
				return _parent == nullptr
					  && _left == nullptr
					 && _right == nullptr;
			}

			/* is leaf */
			auto is_leaf(void) const noexcept -> bool {
				return !has_child();
				//return _left == nullptr && _right == nullptr;
			}

			/* is unary */
			auto is_unary(void) const noexcept -> bool {
				return has_left() != has_right();
				//return (_left != nullptr) != (_right != nullptr);
			}

			/* is binary */
			auto is_binary(void) const noexcept -> bool {
				return has_left() && has_right();
				//return _left != nullptr && _right != nullptr;
			}


			/* is endpoint */
			auto is_endpoint(void) const noexcept -> bool {
				return is_leaf() || is_unary();
			}


			/* get value */
			auto value(void) noexcept -> mut_ref {
				return _value;
			}

			/* get const value */
			auto value(void) const noexcept -> const_ref {
				return _value;
			}

			/* get left child */
			auto left(void) noexcept -> node_ptr {
				return _left;
			}

			/* get right child */
			auto right(void) noexcept -> node_ptr {
				return _right;
			}

			/* get left address */
			auto left_addr(void) noexcept -> node_ptr* {
				return &_left;
			}

			/* get right address */
			auto right_addr(void) noexcept -> node_ptr* {
				return &_right;
			}


			/* get parent */
			auto parent(void) noexcept -> node_ptr {
				return _parent;
			}

			/* get depth */
			auto depth(void) const noexcept -> signed_type {
				return _depth;
			}


			/* get left depth */
			auto left_depth(void) const noexcept -> signed_type {
				return _left ? _left->_depth : 0;
			}

			/* get right depth */
			auto right_depth(void) const noexcept -> signed_type {
				return _right ? _right->_depth : 0;
			}

			/* get balance factor */
			auto balance_factor(void) const noexcept -> signed_type {
				return left_depth() - right_depth();
			}

			/* update depth */
			auto update_depth(void) noexcept -> void {
				_depth = xns::max(left_depth(), right_depth()) + 1;
			}



			/* copy value */
			inline auto value(const_ref value) -> void {
				// set value
				_value = value;
			}

			/* move value */
			inline auto value(value_type&& value) noexcept -> void {
				// set value
				_value = xns::move(value);
			}

			/* set left child */
			inline void left(node_ptr node) noexcept {
				_left = node;
				if (node != nullptr)
					node->_parent = this;
			}

			/* set right child */
			inline void right(node_ptr node) noexcept {
				_right = node;
				if (node != nullptr)
					node->_parent = this;
			}

	}; // class ___node




	// -- I T E R A T O R -----------------------------------------------------

	template <typename ___type, typename ___alloc>
	template <bool C, typename xns::tree<___type, ___alloc>::traversal_type O>
	class xns::tree<___type, ___alloc>::iterator final {


		// -- friends ---------------------------------------------------------

		/* tree as friend */
		friend class xns::tree<___type, ___alloc>;

		/* self type as friend */
		template <bool, xns::tree<___type, ___alloc>::traversal_type>
		friend class xns::tree<___type, ___alloc>::iterator;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self            = xns::tree<___type, ___alloc>::iterator<C, O>;

			/* pointer type */
			using conditional_ptr = xns::conditional<C, const_ptr, mut_ptr>;

			/* reference type */
			using conditional_ref = xns::conditional<C, const_ref, mut_ref>;

			/* container type */
			using container       = xns::conditional<O == BFS_ORDER,
													xns::queue<node_ptr>,
													xns::vector<node_ptr>>;


			// -- constructors ------------------------------------------------

			/* default constructor */
			iterator(void) noexcept
			: _node{nullptr}, _container{} {}

			/* const copy constructor */
			iterator(const xns::tree<___type, ___alloc>::iterator<true, O>& other)
			: _node{other._node}, _container{other._container} {
				// assert invalid conversion
				static_assert(C, "): tree::iterator: can't copy CONST iterator to NON-CONST :(");
			}

			/* non-const copy constructor */
			iterator(const xns::tree<___type, ___alloc>::iterator<false, O>& other)
			: _node{other._node}, _container{other._container} {}

			/* const move constructor */
			iterator(xns::tree<___type, ___alloc>::iterator<true, O>&& other) noexcept
			: _node{other._node}, _container{xns::move(other._container)} {
				// assert invalid conversion
				static_assert(C, "): tree::iterator: can't move CONST iterator to NON-CONST :(");
			}

			/* non-const move constructor */
			iterator(xns::tree<___type, ___alloc>::iterator<false, O>&& other) noexcept
			: _node{other._node}, _container{xns::move(other._container)} {}


			/* pre-order constructor */
			iterator(node_ptr ptr) requires(O == PRE_ORDER)
			: _node{ptr}, _container{} {
				// check for null node
				if (_node == nullptr) return;
				// push right
				if (_node->_right != nullptr) { _container.push_back(_node->_right); }
				// push left
				if (_node->_left != nullptr)  { _container.push_back(_node->_left);  }
			}

			/* in-order constructor */
			iterator(node_ptr ptr) requires(O == IN_ORDER)
			: _node{ptr}, _container{} {

				// check for null node
				if (_node == nullptr) return;

				_container.reserve(static_cast<size_type>(_node->_depth));

				// stack nodes
				do {
					_container.push_back(_node);
					_node = _node->_left;
				} while (_node != nullptr);

				_node = _container.back();
				_container.pop_back();

				node_ptr tmp = _node->_right;
				loop:
				if (tmp == nullptr)
					return;
				_container.push_back(tmp);
				tmp = tmp->_left;
				goto loop;
			}

			/* post-order constructor */
			iterator(node_ptr node) requires(O == POST_ORDER)
			: _node{node}, _container{} {

				// check for null node
				if (_node == nullptr) return;

				while (_node != nullptr) {
					_container.push_back(_node);

					if (_node->_left != nullptr)
						_node = _node->_left;
					else
						_node = _node->_right;
				}

				_node = _container.back();
				_container.pop_back();
			}

			/* breadth-first constructor */
			iterator(node_ptr node) requires(O == BFS_ORDER)
			: _node{node}, _container{} {
				// check for null node
				if (_node == nullptr) return;
				// enqueue left
				if (_node->_left != nullptr)  { _container.enqueue(_node->_left);  }
				// enqueue right
				if (_node->_right != nullptr) { _container.enqueue(_node->_right); }
			}


			/* reverse in-order constructor */
			//iterator(node_ptr node) requires(xns::is_same<order_type, rev_in_order>)
			//: _node{node}, _container{} {
			//
			//	// check for null node
			//	if (_node == nullptr) return;
			//
			//	// stack nodes
			//	while (_node != nullptr) {
			//		_container.push_back(_node);
			//		_node = _node->_right;
			//	}
			//	_node = _container.back();
			//	_container.pop_back();
			//
			//	node_ptr tmp = _node->_left;
			//	while (tmp != nullptr) {
			//		_container.push_back(tmp);
			//		tmp = tmp->_right;
			//	}
			//}


			/* destructor */
			inline ~iterator(void) noexcept = default;



			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) -> self& {
				// copy data
				_node = other._node;
				_container = other._container;
				// return self reference
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// move data
				_node = other._node;
				_container = xns::move(other._container);
				// return self reference
				return *this;
			}


			// -- increment operators -----------------------------------------

			/* pre-increment pre-order operator */
			auto operator++(void) -> self& requires(O == PRE_ORDER) {

				// check if stack is not empty
				if (not _container.empty()) {
					// get top node
					_node = _container.back();
					// pop node
					_container.pop_back();

					// push right child
					if (_node->_right != nullptr) { _container.push_back(_node->_right); }
					// push left child
					if (_node->_left != nullptr)  { _container.push_back(_node->_left);  }
				}
				else _node = nullptr;
				// return self reference
				return *this;
			}


			/* pre-increment in-order operator */
			auto operator++(void) -> self& requires(O == IN_ORDER) {

				// check if stack is empty
				if (_container.empty()) {
					_node = nullptr;
					return *this;
				}

				// get top node
				_node = _container.back();
				_container.pop_back();

				node_ptr node = _node->_right;

				loop:
				if (node == nullptr)
					return *this;

				_container.push_back(node);
				node = node->_left;
				goto loop;

				return *this;
			}


			/* pre-increment post-order operator */
			auto operator++(void) -> self& requires(O == POST_ORDER) {

				// check if stack is empty
				if (_container.empty()) { _node = nullptr; }
				else {

					if (_node == _container.back()->_left) {

						node_ptr node = _container.back()->_right;

						while (node != nullptr) {

							_container.push_back(node);

							if (node->_left != nullptr)
								node = node->_left;
							else
								node = node->_right;
						}
					}
					_node = _container.back();
					_container.pop_back();
				}

				return *this;
			}


			/* pre-increment breadth-first operator */
			auto operator++(void) -> self& requires(O == BFS_ORDER) {

				// check if queue not empty
				if (not _container.empty()) {

					// get next node
					_node = _container.next();
					// dequeue node
					_container.dequeue();

					// enqueue left
					if (_node->_left != nullptr)  { _container.enqueue(_node->_left); }
					// enqueue right
					if (_node->_right != nullptr) { _container.enqueue(_node->_right); }

				}
				else _node = nullptr;
				// return self reference
				return *this;
			}


			/* pre-increment reverse in-order operator */
			//auto operator++(void) -> self&
			//	requires(xns::is_same<order_type, rev_in_order>) {
			//
			//	// check if stack is empty
			//	if (_container.empty()) { _node = nullptr; }
			//	else {
			//		// get top node
			//		_node = _container.back();
			//		// pop node
			//		_container.pop_back();
			//
			//		node_ptr node = _node->_left;
			//
			//		while (node != nullptr) {
			//			_container.push_back(node);
			//			node = node->_right;
			//		}
			//	}
			//	return *this;
			//}


			/* delete post-increment operator (forbid) */
			auto operator++(int) -> self = delete;


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline auto operator==(const self& other) const noexcept -> bool {
				return _node == other._node;
			}

			/* inequality operator */
			inline auto operator!=(const self& other) const noexcept -> bool {
				return _node != other._node;
			}

			/* nullptr equality */
			inline auto operator==(decltype(nullptr)) const noexcept -> bool {
				return _node == nullptr;
			}

			/* nullptr inequality */
			inline auto operator!=(decltype(nullptr)) const noexcept -> bool {
				return _node != nullptr;
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			explicit inline operator bool(void) const noexcept {
				return _node != nullptr;
			}

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
				return _node == nullptr;
			}


			// -- dereference operators ---------------------------------------

			/* dereference operator */
			inline auto operator*(void) const noexcept -> conditional_ref {
				return _node->_value;
			}

			/* dereference operator */
			inline auto operator->(void) const noexcept -> conditional_ptr {
				return &(_node->_value);
			}



			/* balance factor */
			inline auto balance_factor(void) const noexcept -> auto {
				// return balance factor
				return _node->balance_factor();
			}

			/* address as integer */
			inline auto address(void) const noexcept -> xns::uintptr_t {
				return reinterpret_cast<xns::uintptr_t>(_node);
			}


		private:

			// -- private members ---------------------------------------------

			/* node */
			node_ptr _node;

			/* container */
			container _container;

	};


	// -- P R I N T -----------------------------------------------------------

	template <typename ___type, typename ___alloc>
	class xns::tree<___type, ___alloc>::printer final {


		private:

			// -- private constants -------------------------------------------

			/* unicode box enum */
			enum : unsigned { HL, VL, TL, TR, BL, BR, BB, MAX };

			/* unicode box array */
			static constexpr const xns::array<char32_t, MAX> _branch{
				U'\u2500', // HL
				U'\u2502', // VL
				U'\u256D', // TL
				U'\u256E', // TR
				U'\u2570', // BL
				U'\u256F', // BR
				U'\u2534'  // BB
			};

			/* multipliers */
			enum : xns::s64 {
				Y_OFFSET = 3U,
				X_OFFSET = 3U
			};


		public:

			// -- public types ------------------------------------------------

			/* tree type */
			using tree_type = xns::tree<___type, ___alloc>;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			printer(void) = delete;

			/* tree constructor */
			printer(tree_type& tree) noexcept
			: _tree{tree}, _nodes{}, _matrix{} {
			}

			/* non-assignable class */
			___xns_not_assignable(printer);

			/* destructor */
			~printer(void) noexcept = default;


			// -- public methods ----------------------------------------------

			/* display tree */
			void display(void) {

				// check root
				if (_tree._root == nullptr)
					return;

				_nodes.reserve(_tree.size());


				xns::s64 p_min = 0;
				xns::s64 p_max = 0;

				xns::size_t levels = 0;

				using pair_type = std::pair<node_ptr, node_info*>;
				using queue_type = std::queue<pair_type>;

				queue_type queue;

				_nodes.emplace_back();

				queue.emplace(_tree._root, &_nodes.back());


				while (not queue.empty()) {

					pair_type& tuple = queue.front();
					//auto tuple = queue.next();
					queue.pop();
					//queue.dequeue();

					node_ptr node = std::get<node_ptr>(tuple);
					auto info = std::get<node_info*>(tuple);

					if constexpr (xns::is_same<___type, std::string>) {
						info->value = node->_value;
					}
					else {
						info->value = std::to_string(node->_value);
					}
					info->depth = node->_depth;



					if (node->_left) {
						auto width = _tree.subsize(node->_left->_right) + 1;
						auto pos = info->pos - static_cast<xns::s64>(width);
						_nodes.emplace_back( info, // parent
											nullptr, // left
											nullptr, // right
											info->level + 1, // level
											pos, // position
											0, // depth
											std::string{});

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
											0, // depth
											std::string{});

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
					node.level = (levels + 1 - static_cast<xns::size_t>(node.depth)) * Y_OFFSET; // segfault when unbalanced tree
				}


				levels *= Y_OFFSET;
				width  *= X_OFFSET;
				++width;
				++levels;

				_matrix.reserve(levels);

				// fill matrix with spaces
				for (size_type y = 0; y < levels; ++y) {
					_matrix.emplace_back(width, U' ');
				}


				fill_matrix();
				render();
			}


			/* fill matrix */
			auto fill_matrix(void) -> void {


				// loop over nodes
				for (auto& node : _nodes) {

					size_type x = static_cast<size_type>(node.pos);
					size_type y = node.level;

					// check if left
					if (node.left != nullptr) {


						size_type lx = static_cast<size_type>(node.left->pos);
						size_type ly = node.left->level;

						// draw horizontal line
						for (size_type i = lx + 1; i < x + 1; ++i)
							_matrix[y + 1][i] = _branch[HL];

						// draw vertical line
						for (size_type i = y + 2; i < ly; ++i)
							_matrix[i][lx] = _branch[VL];

						// draw left corner
						_matrix[y + 1][lx] = _branch[TL];
					}


					if (node.right != nullptr) {


						size_type rx = static_cast<size_type>(node.right->pos);
						size_type ry = node.right->level;

						// draw horizontal line
						for (size_type i = x + 1; i < rx; ++i)
							_matrix[y + 1][i] = _branch[HL];

						// draw vertical line
						for (size_type i = y + 2; i < ry; ++i)
							_matrix[i][rx] = _branch[VL];

						// draw right corner
						_matrix[y + 1][rx] = _branch[TR];
					}


					if (node.left != nullptr || node.right != nullptr) {

						if (node.left != nullptr && node.right != nullptr)
							_matrix[y + 1][x] = _branch[BB];

						else if (node.left != nullptr)
							_matrix[y + 1][x] = _branch[BR];

						else if (node.right != nullptr)
							_matrix[y + 1][x] = _branch[BL];
					}

					auto& value = node.value;

					if (value.empty() == true) {
						_matrix[y][x] = '?';
						continue;
					}


					size_type size = value.size();
					size_type offset = size / 2;

					if (x > offset) {
						for (size_type i = 0; i < size; ++i)
							_matrix[y][x - offset + i] = static_cast<char32_t>(value[i]);
					}
					else {
						for (size_type i = 0; i < size; ++i)
							_matrix[y][i] = static_cast<char32_t>(value[i]);
					}
				}
			}



			/* render */
			auto render(void) -> void {
				// print matrix
				for (const std::u32string& line : _matrix) {
					std::cout << xns::stdchar32_to(line) << std::endl;
					//xns::print(line, '\n');
				} // render
				//xns::out::render();
			}



		private:


			// -- private structs ---------------------------------------------

			/* node info */
			struct node_info final {


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				node_info(void) noexcept
				: parent{nullptr},
					left{nullptr},
				   right{nullptr},
				   level{0},
					 pos{0},
				   depth{0},
				   value{} {
				}

				/* members constructor */
				node_info(node_info*   pa, node_info* le, node_info* ri,
						  xns::size_t lev, xns::s64   po, xns::s64   de, std::string va) noexcept
				: parent{pa},
					left{le},
				   right{ri},
				   level{lev},
				     pos{po},
				   depth{de},
				   value{va} {
				}

				/* non-copyable struct */
				___xns_not_copyable(node_info);

				/* move constructor */
				node_info(node_info&&) noexcept = default;

				/* move assignment operator */
				auto operator=(node_info&&) noexcept -> node_info& = default;

				/* destructor */
				~node_info(void) noexcept = default;


				// -- public members ------------------------------------------

				node_info* parent;
				node_info* left;
				node_info* right;

				xns::size_t level;
				xns::s64 pos;
				xns::s64 depth;
				std::string value;

			};


			// -- private members ---------------------------------------------

			/* tree reference */
			tree_type& _tree;

			/* nodes */
			std::vector<node_info> _nodes;

			/* matrix */
			std::vector<std::u32string> _matrix;

	}; // class printer




	template <typename T>
	auto check_tree(const xns::tree<T>& tree) -> int {
		// check balance factor
		for (auto it = tree.pre_order_begin(); it != nullptr; ++it) {
			if (it.balance_factor() > 1
				|| it.balance_factor() < -1)
				return -1;
		}
		// check sorted
		const T* last = nullptr;
		auto it = tree.in_order_begin();
		if (it) { last = &*it; ++it; }
		while (it) {
			if (*last > *it)
				return -2;
			last = &*it;
			++it;
		}
		xns::println("check tree: \x1b[32mOK\x1b[0m");
		return 0;
	}


}

#endif // XNS_TREE_HEADER
