#ifndef TRIE_HEADER
#define TRIE_HEADER

#include "types.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "tuple.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"
#include "string.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- T R I E  C L A S S --------------------------------------------------

	/* this class implements a trie data structure
	 * WARNING: this class stores pointers in a ascii lookup table
	 * size of the lookup table is only printable ascii characters (95)
	 * class do not check if the key is only printable ascii characters
	 */

	/* update: this class now uses a 256 lookup table
	 * no need to check if the key is only printable ascii characters
	 */

	template <typename T>
	class trie final {


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using type = T;

			/* self type */
			using self = trie<type>;

			/* reference type */
			using mut_ref = type&;

			/* move reference type */
			using move_ref = type&&;

			/* const reference type */
			using const_ref = const type&;

			/* weak value type */
			using weak_value = xns::weak_ptr<type>;

			/* size type */
			using size_type = xns::size_t;


		private:

			// -- private enum ------------------------------------------------

			/* lookup table size */
			enum : xns::size_t { LOOKUP_SIZE = 256, };


			/* forward declaration */
			struct node;


			// -- P R I V A T E  A L I A S E S --------------------------------

			/* unique node type */
			using unique_node = xns::unique_ptr<node>;

			/* lookup table type */
			using table = xns::array<unique_node, LOOKUP_SIZE>;

			/* node pointer type */
			using weak_node = xns::weak_ptr<node>;

			/* node pointer type */
			using node_ptr = node*;

			/* node address type */
			using node_addr = node**;



			// -- private structs ---------------------------------------------

			/* node */
			struct node {


				// -- members -------------------------------------------------

				/* childs */
				table _table;


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				inline node(void) noexcept
				: _table{} {}

				/* non-assignable class */
				NON_ASSIGNABLE(node);

				/* destructor */
				virtual inline ~node(void) noexcept = default;


				// -- interface -----------------------------------------------

				/* has value */
				virtual inline consteval auto has_value(void) const noexcept -> bool {
					return false;
				}

				/* get value */
				[[noreturn]]
				virtual inline consteval auto value(void) -> mut_ref {
					throw;
				}


			};


			/* value node */
			struct value_node final : public node {


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				inline value_node(void) noexcept
				: node{} {}


				// -- members -------------------------------------------------

				/* value */
				type _value;


				// -- overrides -----------------------------------------------

				/* has value */
				inline consteval auto has_value(void) const noexcept -> bool override {
					return true;
				}

				/* get value */
				inline consteval auto value(void) -> mut_ref override {
					return _value;
				}


			};



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline trie(void) noexcept
			: _root{} {}

			/* destructor */
			inline ~trie(void) noexcept = default;


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* insert */
			template <typename U>
			void insert(const xns::string& key, U&& value) {
				// insert key
				node_ptr node = insert_impl(key);
				// allocate default value
				// node->_value = xns::make_shared<value_type>(xns::forward<U>(value));
			}

			/* emplace insert */
			//template <class... A>
			//void emplace_insert(const xns::string& key, A&&... args) {
			//	// insert key
			//	node_ptr node = insert_impl(key);
			//	// allocate value
			//	// node->_value = xns::make_shared<value_type>(xns::forward<A>(args)...);
			//}

			/* derived default insert */
			//template <class D> requires (xns::is_derived_from<D, value_type>)
			//void insert(const xns::string& key) {
			//	// insert key
			//	node_ptr node = insert_impl(key);
			//	// allocate default value
			//	node->_value = xns::make_shared<D>();
			//}

			// /* derived copy insert */
			// template <class D> requires (xns::is_derived_from<D, value_type>)
			// void insert(const xns::string& key, const D& value) {
			// 	// insert key
			// 	node* node = insert_impl(key);
			// 	// allocate copied value
			// 	node->_value = xns::make_shared<D>(value);
			// }
			//
			// /* derived move insert */
			// template <class D> requires (xns::is_derived_from<D, value_type>)
			// void insert(const xns::string& key, D&& value) {
			// 	// insert key
			// 	node* node = insert_impl(key);
			// 	// allocate moved value
			// 	node->_value = xns::make_shared<D>(xns::move(value));
			// }
			//
			// /* derived variadic insert */
			// template <class D, class... A> requires (xns::is_derived_from<D, value_type>)
			// void insert(const xns::string& key, A&&... args) {
			// 	// insert key
			// 	node* node = insert_impl(key);
			// 	// allocate value
			// 	node->_value = xns::make_shared<D>(xns::forward<A>(args)...);
			// }
			//
			//
			//
			// /* derived multi insert */
			// template <xns::is_string S, class D, class... A> requires (xns::is_derived_from<D, value_type>)
			// void insert(const xns::vector<S>& alias, A&&... args) {
			// 	// instanciate value
			// 	shared_value value = xns::make_shared<D>(xns::forward<A>(args)...);
			// 	// loop through alias
			// 	for (typename xns::vector<S>::size_type x = 0; x < alias.size(); ++x) {
			// 		// insert key
			// 		node* node = _insert(alias[x]);
			// 		// allocate value
			// 		node->_value = value;
			// 	}
			// }
			//
			// /* variadic multi insert */
			// template <xns::is_string S, class... A>
			// void insert(const xns::vector<S>& alias, A&&... args) {
			// 	// instanciate value
			// 	shared_value value = xns::make_shared<value_type>(xns::forward<A>(args)...);
			// 	// loop through alias
			// 	for (typename xns::vector<S>::size_type x = 0; x < alias.size(); ++x) {
			// 		// insert key
			// 		node* node = insert_impl(alias[x]);
			// 		// allocate value
			// 		node->_value = value;
			// 	}
			// }
			//

			/* find */
			auto find(const xns::string& str) -> weak_value {
				// get root node
				node_ptr node = &_root;
				// loop through string
				for (xns::string::size_type x = 0; x < str.size(); ++x) {
					// get index
					const size_type idx = to_idx(str[x]);
					// check indexed node validity
					if (node->_table[idx] != nullptr)
						// enter in node
						node = &(*node->_table[idx]);
					// else return nullptr
					else return nullptr;
				} // return value
				return weak_value{node->_value};
			}

			/* find */
			auto find(const xns::string_view& str) -> weak_value {
				// get root node
				node_ptr node = &_root;
				// loop through string
				for (xns::string_view::size_type x = 0; x < str.size(); ++x) {
					// get index
					const auto idx = to_idx(str[x]);
					// check indexed node validity
					if (node->_table[idx] != nullptr)
						// enter in node
						node = &(*node->_table[idx]);
					// else return nullptr
					else return nullptr;
				} // return value
				return weak_value{node->_value};
			}






		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* _insert */
			template <xns::is_string S>
			auto insert_impl(const S& str) -> node_addr {
				// get root node
				node_ptr node = &_root;
				// loop through string
				for (typename S::size_type x = 0; x < str.size(); ++x) {
					// get index
					const auto idx = to_idx(str[x]);
					// check indexed node validity
					if (node->_table[idx] == nullptr) {
						// make new node
						node->_table[idx] = xns::make_unique<self::node>();
					} // move to node
					node = &(*node->_table[idx]);
				} // return node
				return node;
			}

			/* to index */
			template <typename C>
			inline static auto to_idx(const C c) -> xns::ubyte {
				static_assert(sizeof(C) == 1, "): TYPE C MUST BE SINGLE BYTE :(");
				return static_cast<xns::ubyte>(c);
			}


			// -- private members ---------------------------------------------

			/* root children */
			node _root;

	};



};

#endif
