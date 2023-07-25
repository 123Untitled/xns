#ifndef MAP_HEADER
#define MAP_HEADER

#include "types.hpp"
#include "allocator.hpp"
#include "unique_ptr.hpp"
#include "weak_ptr.hpp"
#include "tree.hpp"
#include "literal_map.hpp"
#include "tuple.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- is convertible ------------------------------------------------------

	template <class T, class U>
	concept is_convertible = requires(T a) {
		{ static_cast<U>(a) };
	};

	// -- is comparable -------------------------------------------------------

	template <class T>
	concept is_comparable = requires(T a, T b) {
		{ a == b } -> is_convertible<bool>;
		{ a != b } -> is_convertible<bool>;
		{ a < b } -> is_convertible<bool>;
		{ a > b } -> is_convertible<bool>;
		{ a <= b } -> is_convertible<bool>;
		{ a >= b } -> is_convertible<bool>;
	};



	// -- M A P ---------------------------------------------------------------

	template <class K, class V>
	class map final {

		static_assert(is_comparable<K>, "K must be comparable");

		public:

			// -- public types ------------------------------------------------

			/* key type */
			using key_type = K;

			/* value type */
			using value_type = V;

			/* size type */
			using size_type = xns::size_t;

			/* reference type */
			using reference = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* move reference type */
			using move_reference = value_type&&;

			/* pointer type */
			using mutable_pointer = value_type*;

			/* const pointer type */
			using const_pointer = const value_type*;


			/* pair type */
			using pair_type = xns::pair<key_type, value_type>;

			/* tree type */
			using tree_type = xns::tree<pair_type>;

			/* node pointer type */
			using node_pointer = typename tree_type::node_pointer;



		private:

			// -- private members ---------------------------------------------

			/* tree */
			tree_type _tree;


		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			map(void)
			: _tree{} {
				// nothing to do...
			}


			// -- I N S E R T -------------------------------------------------


			/* copy insert */
			void insert(const key_type& key, const value_type& value) {

				node_pointer node = _tree.root();

				//node_pointer nde  = &_root;
				node_pointer parent  = nullptr;

				// loop until node is null
				while (node) {
					// keep track of parent
					// less compare
					pair_type& pair = node->value();

					if      (key < pair._first) {
						parent = node;
						node = node->left();
					}
					// greater compare
					else if (key > pair._first) {
						parent = node;
						node = node->right();
					}
					// equal compare, replace value ?
					else                         {
						//node->_value = value;
						return;
					}
				}

				// create new node
				node = _tree.new_node(pair_type{key, value});
				std::cout << "new node..." << std::endl;
				std::cout << "key: " << node->value()._first << std::endl;

				if (parent == nullptr) {
					_tree.root(node);
				}
				else if (key < parent->value()._first) {
					parent->set_left(node);
				}
				else {
					parent->set_right(node);
				}

			}


			/* move insert */
			void move_insert(const key_type& key, move_reference value) {
				// code here...
			}

			/* emplace insert */
			template <class... A>
			void emplace_insert(const key_type& key, A&&... args) {
				// code here...
			}

			static xns::string vcall(const pair_type& pair) {
				return pair._first;
			}

			static xns::size_t scall(const pair_type& pair) {
				return pair._first.size();
			}

		void print(void) {
			_tree.print(scall, vcall);
		}




		private:



	};

};

#endif
