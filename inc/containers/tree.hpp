#ifndef TREE_HEADER
#define TREE_HEADER

#include "string.hpp"
#include "stack.hpp"
#include "types.hpp"
#include "tuple.hpp"
#include "allocator.hpp"
#include "safe_enum.hpp"
#include "iterators/bst_iterator.hpp"
#include "output.hpp"
#include "escape.hpp"
#include "terminal.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T R E E -------------------------------------------------------------

	template <class T>
	class tree {


		private:

			/* forward declaration */
			class printer;


			// -- friends -----------------------------------------------------

			/* bst iterator as friend */
			template <class, xns::traversal_order, bool>
			friend class bst_iterator;

			/* print as friend */
			friend class printer;


		public:

			/* forward declaration */
			class node;


			// -- private types -----------------------------------------------

			/* node type */
			using node_type    = tree<T>::node;

			/* allocator type */
			using allocator    = allocator<node_type>;

			/* node pointer */
			using node_pointer = typename allocator::mutable_pointer;


		public:


			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = tree<value_type>;

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
			template <class O>
			using iterator = xns::bst_iterator<value_type, O, false>;

			/* const iterator type */
			template <class O>
			using const_iterator = xns::bst_iterator<value_type, O, true>;


			/* pre-order iterator */
			using pre_order_iterator        = iterator<xns::pre_order>;

			/* in-order iterator */
			using in_order_iterator         = iterator<xns::in_order>;

			/* post-order iterator */
			using post_order_iterator       = iterator<xns::post_order>;

			/* bfs iterator */
			using bfs_iterator              = iterator<xns::bfs_order>;

			/* const pre-order iterator */
			using const_pre_order_iterator  = const_iterator<xns::pre_order>;

			/* const in-order iterator */
			using const_in_order_iterator   = const_iterator<xns::in_order>;

			/* const post-order iterator */
			using const_post_order_iterator = const_iterator<xns::post_order>;

			/* const bfs iterator */
			using const_bfs_iterator        = const_iterator<xns::bfs_order>;


			// -- constructors ------------------------------------------------

			/* default constructor */
			tree(void) noexcept
			: _root{nullptr}, _storage{nullptr}, _size{0} {
				// do nothing...
			}

			/* copy constructor */
			tree(const self& other)
			: _root{nullptr}, _storage{nullptr}, _size{0} {
				// copy other tree
				//_copy_tree(other);
			}

			/* move constructor */
			tree(self&& other) noexcept
			: _root{other._root}, _storage{other._storage}, _size{other._size} {
				// reset other tree
				other._root    = nullptr;
				other._storage = nullptr;
				other._size    = 0;
			}

			/* destructor */
			~tree(void) noexcept {
				// destroy and deallocate tree
				 _free_tree();
				// deallocate storage
				_free_storage();
			}



			// -- iterators ---------------------------------------------------

			/* pre-order iterator begin */
			auto pre_order_begin(void) noexcept -> pre_order_iterator {
				// return iterator to root
				return pre_order_iterator{_root};
			}

			/* in-order iterator begin */
			auto in_order_begin(void) noexcept -> in_order_iterator {
				// return iterator to root
				return in_order_iterator{_root};
			}

			/* post-order iterator begin */
			auto post_order_begin(void) noexcept -> post_order_iterator {
				// return iterator to root
				return post_order_iterator{_root};
			}

			/* bfs iterator begin */
			auto bfs_begin(void) noexcept -> bfs_iterator {
				// return iterator to root
				return bfs_iterator{_root};
			}

			/* const pre-order iterator begin */
			auto pre_order_begin(void) const noexcept -> const_pre_order_iterator {
				// return iterator to root
				return const_pre_order_iterator{_root};
			}

			/* const in-order iterator begin */
			auto in_order_begin(void) const noexcept -> const_in_order_iterator {
				// return iterator to root
				return const_in_order_iterator{_root};
			}

			/* const post-order iterator begin */
			auto post_order_begin(void) const noexcept -> const_post_order_iterator {
				// return iterator to root
				return const_post_order_iterator{_root};
			}

			/* const bfs iterator begin */
			auto bfs_begin(void) const noexcept -> const_bfs_iterator {
				// return iterator to root
				return const_bfs_iterator{_root};
			}

			/* iterator end */
			auto end(void) noexcept -> xns::null {
				// return iterator to null
				return nullptr;
			}

			/* const iterator end */
			auto end(void) const noexcept -> xns::null {
				// return iterator to null
				return nullptr;
			}


			// -- accessors ---------------------------------------------------

			/* size */
			size_type size(void) const noexcept {
				// return size of tree
				return _size;
			}

			/* empty */
			bool empty(void) const noexcept {
				// return if tree is empty
				return _size == 0;
			}

			/* depth */
			size_type depth(void) const noexcept {
				// return depth of tree
				return _root ? _root->_depth : 0;
			}

			/* iterator depth */
			template <is_bst_iterator I>
			size_type depth(const I& it) const noexcept {
				// return depth of iterator
				return it._node->_depth;
			}

			/* node depth */
			size_type depth(const node_pointer& node) const noexcept {
				// return depth of node
				return node->_depth;
			}

			/* iterator level */
			template <is_bst_iterator I>
			size_type level(const I& it) const noexcept {
				// return level of iterator
				return it._node->_level;
			}

			/* node level */
			size_type level(const node_pointer& node) const noexcept {
				// return level of node
				return node->_level;
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
			node_pointer new_node(const_reference value) {
				// declare node
				node_pointer node = _new_node();
				// check pointer
				if (!node) { return nullptr; }
				// construct node
				allocator::construct(node, value);
				// update size
				++_size;
				// return node
				return node;
			}

			/* new node by moved value */
			node_pointer new_node(move_reference value) {
				// declare node
				node_pointer node = _new_node();
				// check pointer
				if (!node) { return nullptr; }
				// construct node
				allocator::construct(node, xns::move(value));
				// update size
				++_size;
				// return node
				return node;
			}

			/* new node by construct in place */
			template <class... A>
			node_pointer new_node(A&&... args) {
				// declare node
				node_pointer node = _new_node();
				// check pointer
				if (!node) { return nullptr; }
				// construct node
				allocator::construct(node, xns::forward<A>(args)...);
				// update size
				++_size;
				// return node
				return node;
			}


			// -- insertion ---------------------------------------------------

			/* insert left */
			void insert_left(node_pointer node, node_pointer child) {
				   // insert child
				   node->_left = child;
				// set parent
				child->_parent = node;
				// update depth
				_update_depth(node);
			}

			/* insert right */
			void insert_right(node_pointer node, node_pointer child) {
				  // insert child
				  node->_right = child;
				// set parent
				child->_parent = node;
				// update depth
				_update_depth(node);
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
				for (const_bfs_iterator it{pos._node}; it; ++it) {
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
				for (const_bfs_iterator it{node}; it; ++it) {
					// check if node is endpoint
					count += it.is_endpoint();
				} // return count
				return count;
			}



			template <class U>
			xns::tree<U> clone_as(void) {
				return {};
			}




			// -- display -----------------------------------------------------

			/* print tree */
			void print(typename printer::scallback scall,
					   typename printer::vcallback vcall) noexcept {
				// instantiate printer
				class printer p{*this, scall, vcall};
				// display tree
				p.display();
			}




			/* clear tree */
			void clear(void) noexcept {
				// destroy tree
				_destroy_tree();
				// initialize members
				_init();
			}



		private:




			// -- depth -------------------------------------------------------

			/* update depth */
			static void _update_depth(node_pointer node) noexcept {
				// loop until back to root
				while (node) {
					// get left and right depth
					const size_type left  = node->_left  ? node->_left->_depth  : 0;
					const size_type right = node->_right ? node->_right->_depth : 0;
					// update depth
					node->_depth = (left > right) ? left + 1 : right + 1;
					// move up
					node = node->_parent;
				}
			}

			/* update level */
			static void _update_level(node_pointer node) noexcept {
			}


			/* initialize members */
			inline void _init(void) noexcept {
				// initialize members
				_root = nullptr;
				_size = 0;
			}

			// -- memory management -------------------------------------------

			/* new node */
			inline node_pointer _new_node(void) noexcept {
				// declare node
				node_pointer node = nullptr;
				// check storage
				if (_storage) {
						 // unlink from storage
						 node = _storage;
					 _storage = node->_left;
				// else allocate new node
				} else { node = allocator::allocate(); }
				// return node
				return node;
			}

			/* add to storage */
			inline void _store(node_pointer node) noexcept {
				// destroy node
				allocator::destroy(node); // INFO: null is not checked
				// link to storage
				node->_left = _storage;
				  _storage  = node;
			}

			/* free tree */ // INFO: this is only used in destructor
			inline void _free_tree(void) noexcept {
				// declare post-order iterator
				post_order_iterator it{_root};
				// loop until end
				while (it) {
					// get node
					node_pointer node = it._node;
					// increment iterator
					++it;
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
					_storage = node->_left;
					// deallocate node
					allocator::deallocate(node);
				}
			}

			/* destroy tree */ // INFO: used for clear method
			inline void _destroy_tree(void) noexcept {
				// declare post-order iterator
				post_order_iterator it{_root};
				// loop until end
				while (it) {
					// get node
					node_pointer node = it._node;
					// increment iterator
					++it;
					// store node
					_store(node);
				}
			}



			// -- private members ---------------------------------------------

			/* root node */
			node_pointer _root;

			/* storage */
			node_pointer _storage;

			/* size */
			size_type    _size;


	};


	// -- N O D E -------------------------------------------------------------

	template <class T>
	class tree<T>::node {

		// -- friends ---------------------------------------------------------

		/* tree as friend */
		template <class>
		friend class tree;

		/* allocator as friend */
		template <class>
		friend class xns::allocator;

		/* bst iterator as friend */
		template <class, xns::traversal_order, bool>
		friend class xns::bst_iterator;


		private:

			// -- private constructors ----------------------------------------

			/* default constructor */
			node(void) noexcept
			:  _value{ },
			    _left{nullptr},
			   _right{nullptr},
			  _parent{nullptr},
			   _depth{0},
			   _level{0},
			     _pos{0} {
				// do nothing...
			}

			/* copy constructor */
			node(const node& other) noexcept
			:  _value{other._value},
				_left{other._left},
			   _right{other._right},
			  _parent{other._parent},
			   _depth{other._depth},
			   _level{other._level},
			     _pos{other._pos} {
				// do nothing...
			}

			/* move constructor */
			node(node&& other) noexcept
			:  _value{xns::move(other._value)},
			    _left{other._left},
			   _right{other._right},
			  _parent{other._parent},
			   _depth{other._depth},
			   _level{other._level},
			     _pos{other._pos} {
				// invalidate other
				other._init();
			}

			/* value copy constructor */
			node(const value_type& value) noexcept
			:  _value{value},
			    _left{nullptr},
			   _right{nullptr},
			  _parent{nullptr},
			   _depth{0},
			   _level{0},
			     _pos{0} {
				// do nothing...
			}

			/* value move constructor */
			node(value_type&& value) noexcept
			:  _value{xns::move(value)},
			    _left{nullptr},
			   _right{nullptr},
			  _parent{nullptr},
			   _depth{0},
			   _level{0},
			     _pos{0} {
				// do nothing...
			}

			/* value emplace constructor */
			template <class... A>
			node(A&&... args) noexcept
			:  _value{xns::forward<A>(args)...},
				_left{nullptr},
			   _right{nullptr},
			  _parent{nullptr},
			   _depth{0},
			   _level{0},
			     _pos{0} {
				// do nothing...
			}

			/* destructor */
			~node(void) noexcept {
				// reset left pointer (for storage)
				_left = nullptr;
			}


		public:

			// -- accessors ---------------------------------------------------

			/* get value */
			inline reference value(void) noexcept {
				// return value
				return _value;
			}

			/* get const value */
			inline const_reference value(void) const noexcept {
				// return value
				return _value;
			}

			/* get left child */
			inline node_pointer left(void) noexcept {
				// return left
				return _left;
			}

			/* get left address */
			inline node_pointer* left_addr(void) noexcept {
				// return left address
				return &_left;
			}

			/* get right child */
			inline node_pointer right(void) noexcept {
				// return right
				return _right;
			}

			/* get right address */
			inline node_pointer* right_addr(void) noexcept {
				// return right address
				return &_right;
			}


			/* get parent */
			inline node_pointer parent(void) noexcept {
				// return parent
				return _parent;
			}

			/* get depth */
			inline xns::size_t depth(void) const noexcept {
				// return depth
				return _depth;
			}

			/* get level */
			inline xns::size_t level(void) const noexcept {
				// return level
				return _level;
			}

			/* get position */
			inline xns::s64 xpos(void) const noexcept {
				// return position
				return _pos;
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
				// update depth
				_update_depth(this);
			}

			/* set right child */
			inline void set_right(node_pointer node) noexcept {
				// set right
				_right = node;
				// set parent
				node->_parent = this;
				// update depth
				_update_depth(this);
			}

			/* set right to new left and set new to right */
			inline void right_to_left(node_pointer node) noexcept {
				// move right
				node->_left = _right;
				// re-set parent
				_right->_parent = node;
				// set right
				_right = node;
				// set parent
				node->_parent = this;
				// update depth
				_update_depth(this);
			}


		private:

			// -- private methods ---------------------------------------------

			/* initialization */
			void _init(void) noexcept {
				// set links
				_left   = nullptr;
				_right  = nullptr;
				_parent = nullptr;
				// set depth
				_depth = 0;
				// set positions
				_level = 0;
				_pos   = 0;

			}

			// -- private members ---------------------------------------------

			/* value */
			value_type   _value;

			/* links */
			node_pointer _left, _right, _parent;

			/* utility */
			xns::size_t  _depth, _level;

			/* position */
			xns::s64     _pos;


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


		public:

			// -- public types ------------------------------------------------

			/* tree type */
			using tree_type = xns::tree<T>;

			/* size callback */
			using scallback = xns::function<xns::size_t(const_reference)>;

			/* value callback */
			using vcallback = xns::function<xns::string(const_reference)>;


			// -- constructors ------------------------------------------------

			/* deleted default constructor */
			printer(void) = delete;

			/* tree constructor */
			printer(xns::tree<T>& tree, scallback size, vcallback value)
			: _tree{tree}, _scall{size}, _vcall{value} {
				// do nothing...
			}

			/* non-assignable class */
			NON_ASSIGNABLE(printer);

			/* destructor */
			~printer(void) noexcept = default;


			void display(void) {


				// check root
				if (_tree._root == nullptr) { return; }


				using pos = decltype(_tree._root->_pos);


				// parent pos
				pos p_pos = 0; // THIS AVOID IMPLICIT CONVERSION ERROR BUT NOT TESTED

				// max endpoint width
				size_type width = 0;

				xns::s64 smin = 0, smax = 0;

				xns::size_t level = 0;

				_tree._root->_pos = 0;

				// bfs node constructor
				const_bfs_iterator it{_tree._root};

				// loop over tree (skip root)
				for (++it; it != nullptr; ++it) {

					// get parent position
					p_pos = it.parent()->_pos;

					// check node is left child
					if (it.is_left()) {
						width = _tree.endpoints(it.right());
						// AVOID IMPLICIT CONVERSION ERROR BUT NOT TESTED
						it._node->_pos = p_pos - static_cast<pos>(width + 1);
					}
					// else node is right child
					else {
						width = _tree.endpoints(it.left());
						// AVOID IMPLICIT CONVERSION ERROR BUT NOT TESTED
						it._node->_pos = p_pos + static_cast<pos>(width + 1);
					}

					// update min position
					if (it._node->_pos < smin) {
						smin = it._node->_pos;
					}
					// update max position
					if (it._node->_pos > smax) {
						smax = it._node->_pos;
					}
					level = it._node->_level;

				}





				// compensate for negative min
				smin *= -1;
				xns::size_t max =
					static_cast<xns::u64>(smax) +
					static_cast<xns::u64>(smin);

				// matrix
				xns::string32 unicode;

				xns::vector<xns::string32> matrix;

				// root start at level 0, so add 1
				++level;

				++max;


				// multipliers
				enum : size_type {
					Y_OFFSET = 4,
					X_OFFSET = 4
				};

				level *= Y_OFFSET;
				max *= X_OFFSET;

				//std::cout << "level: " << level << "\n";
				//std::cout << "max: " << max << "\n";


				level -= (Y_OFFSET - 1);

				matrix.reserve(level);

				// fill matrix with spaces
				for (size_type y = 0; y < level; ++y) {
					matrix.emplace_back(U' ', max);
				}

				const_bfs_iterator it4{_tree._root};

				// declare all positions
				size_type x = 0, y = 0, lx = 0, ly = 0, rx = 0, ry = 0;

				for (; it4 != nullptr; ++it4) {

					// get node position
					x = static_cast<size_type>((it4.xpos() + smin)) * X_OFFSET;
					y = it4.level()         * Y_OFFSET;

					// check if left
					if (it4.has_left()) {

						// get left position
						lx = static_cast<size_type>((it4.left()->xpos() + smin)) * X_OFFSET;
						ly = it4.left()->level()         * Y_OFFSET;

						// draw horizontal line
						for (size_type i = lx + 1; i < x + 1; ++i) {
							matrix[y + 1][i] = _branch[HL];
						}
						// draw vertical line
						for (size_type i = y + 2; i < ly; ++i) {
							matrix[i][lx] = _branch[VL];
						}
						// draw left corner
						matrix[y + 1][lx] = _branch[TL];
					}

					if (it4.has_right()) {

						// get right position
						rx = static_cast<size_type>((it4.right()->xpos() + smin)) * X_OFFSET;
						ry = it4.right()->level()         * Y_OFFSET;

						// draw horizontal line
						for (size_type i = x + 1; i < rx; ++i) {
							matrix[y + 1][i] = _branch[HL];
						}
						// draw vertical line
						for (size_type i = y + 2; i < ry; ++i) {
							matrix[i][rx] = _branch[VL];
						}
						// draw right corner
						matrix[y + 1][rx] = _branch[TR];
					}

					if (it4.has_child()) {

						if (it4.is_binary()) {
							matrix[y + 1][x] = _branch[BB];
						}
						else if (it4.has_left()) {
							matrix[y + 1][x] = _branch[BR];
						}
						else if (it4.has_right()) {
							matrix[y + 1][x] = _branch[BL];
						}
					}


					xns::string value = _vcall.call(it4._node->_value);

					if (value.size()) {
						size_type size = value.size();
						size_type offset = size / 2;

						if (x > offset) {
							for (size_type i = 0; i < size; ++i) {
								matrix[y][x - offset + i] = static_cast<char32_t>(value[i]);
							}
						}
						else {
							for (size_type i = 0; i < size; ++i) {
								matrix[y][i] = static_cast<char32_t>(value[i]);
							}
						}

					}
					else {
						matrix[y][x] = '_';
					}
				}





				// print matrix
				for (xns::vector<xns::string>::size_type _ = 0; _ < matrix.size(); ++_) {
					xns::out::write(matrix[_]);
					xns::out::newline();
				}
				xns::out::flush();

				return;

			}


		private:

			// -- private members ---------------------------------------------

			/* tree reference */
			xns::tree<T>& _tree;

			/* size callback */
			scallback _scall;

			/* value callback */
			vcallback _vcall;


	};


}


#endif
