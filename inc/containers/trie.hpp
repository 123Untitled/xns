#ifndef TRIE_HEADER
#define TRIE_HEADER

#include "types.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "tuple.hpp"
#include "unique_pointer.hpp"
#include "shared_pointer.hpp"
#include "weak_pointer.hpp"
#include "string.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- T R I E  C L A S S --------------------------------------------------

	// this class implements a trie data structure
	// WARNING: this class stores pointers in a ascii lookup table
	// size of the lookup table is only printable ascii characters (95)
	// class do not check if the key is a printable ascii character !

	template <class T>
	class trie final {

		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using value_type = T;

			/* self type */
			using self = trie<value_type>;

			/* weak value type */
			using weak_value = xns::weak_ptr<value_type>;

			/* size type */
			using size_type = xns::size_t;


		private:

			// -- P R I V A T E  E N U M S ------------------------------------

			/* lookup table size */
			enum : size_type {
				OFFSET = 32,
				LOOKUP_SIZE = 95
			};


			/* forward declaration */
			struct node;


			// -- P R I V A T E  A L I A S E S --------------------------------

			/* unique node type */
			using unique_node = xns::unique_ptr<node>;

			/* lookup table type */
			using table = xns::array<unique_node, LOOKUP_SIZE>;

			/* node pointer type */
			using weak_node = xns::weak_ptr<node>;

			/* value pointer type */
			using shared_value = xns::shared_ptr<value_type>;



			// -- N O D E  S T R U C T ----------------------------------------

			struct node final {

				// -- M E M B E R S -------------------------------------------

				/* childs */
				table _table;

				/* value */
				shared_value _value;


				// -- C O N S T R U C T O R S ---------------------------------

				/* default constructor */
				node(void)
				: _table{}, _value{} {
					// code here...
				}

				/* value constructor */
				node(value_type* value)
				: _table{}, _value{value} {
					// code here...
				}

				/* destructor */
				~node(void) {
					// code here...
				}

			};




		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			trie(void)
			: _root{ } {
				// code here...
			}

			/* destructor */
			~trie(void) {
				// code here...
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* default insert */
			void insert(const xns::cstring& key) {
				// insert key
				node* node = _insert(key);
				// allocate default value
				node->_value = xns::make_shared_pointer<value_type>();
			}

			/* copy insert */
			void insert(const xns::cstring& key, const value_type& value) {
				// insert key
				node* node = _insert(key);
				// allocate copied value
				node->_value = xns::make_shared_pointer<value_type>(value);
			}

			/* move insert */
			void insert(const xns::cstring& key, value_type&& value) {
				// insert key
				node* node = _insert(key);
				// allocate moved value
				node->_value = xns::make_shared_pointer<value_type>(xns::move(value));
			}

			/* variadic insert */
			template <class... A>
			void insert(const xns::cstring& key, A&&... args) {
				// insert key
				node* node = _insert(key);
				// allocate value
				node->_value = xns::make_shared_pointer<value_type>(xns::forward<A>(args)...);
			}

			/* derived default insert */
			template <class D> requires (xns::is_derived_from<D, value_type>)
			void insert(const xns::cstring& key) {
				// insert key
				node* node = _insert(key);
				// allocate default value
				node->_value = xns::make_shared_pointer<D>();
			}

			/* derived copy insert */
			template <class D> requires (xns::is_derived_from<D, value_type>)
			void insert(const xns::cstring& key, const D& value) {
				// insert key
				node* node = _insert(key);
				// allocate copied value
				node->_value = xns::make_shared_pointer<D>(value);
			}

			/* derived move insert */
			template <class D> requires (xns::is_derived_from<D, value_type>)
			void insert(const xns::cstring& key, D&& value) {
				// insert key
				node* node = _insert(key);
				// allocate moved value
				node->_value = xns::make_shared_pointer<D>(xns::move(value));
			}

			/* derived variadic insert */
			template <class D, class... A> requires (xns::is_derived_from<D, value_type>)
			void insert(const xns::cstring& key, A&&... args) {
				// insert key
				node* node = _insert(key);
				// allocate value
				node->_value = xns::make_shared_pointer<D>(xns::forward<A>(args)...);
			}

			using KeyVector = xns::vector<xns::cstring>;


			/* derived multi insert */
			template <xns::is_string S, class D, class... A> requires (xns::is_derived_from<D, value_type>)
			void insert(const xns::vector<S>& alias, A&&... args) {
				// instanciate value
				shared_value value = xns::make_shared_pointer<D>(xns::forward<A>(args)...);
				// loop through alias
				for (typename xns::vector<S>::size_type x = 0; x < alias.size(); ++x) {
					// insert key
					node* node = _insert(alias[x]);
					// allocate value
					node->_value = value;
				}
			}

			/* variadic multi insert */
			template <xns::is_string S, class... A>
			void insert(const xns::vector<S>& alias, A&&... args) {
				// instanciate value
				shared_value value = xns::make_shared_pointer<value_type>(xns::forward<A>(args)...);
				// loop through alias
				for (typename xns::vector<S>::size_type x = 0; x < alias.size(); ++x) {
					// insert key
					node* node = _insert(alias[x]);
					// allocate value
					node->_value = value;
				}
			}

			/*template <class D, class... A> requires (xns::is_base_of_c<T, D>)
			void insert(const KeyVector& alias, A&&... args) {
				// instanciate value
				shared_value value = xns::make_shared_pointer<D>(xns::forward<A>(args)...);
				// loop through alias
				for (KeyVector::size_type x = 0; x < alias.size(); ++x) {
					// insert key
					node* node = _insert(alias[x]);
					// allocate value
					node->_value = value;
				}
			}*/

			/* variadic multi insert */
			/*template <class... A>
			void insert(const KeyVector& alias, A&&... args) {
				// instanciate value
				shared_value value = xns::make_shared_pointer<value_type>(xns::forward<A>(args)...);
				// loop through alias
				for (KeyVector::size_type x = 0; x < alias.size(); ++x) {
					// insert key
					node* node = _insert(alias[x]);
					// allocate value
					node->_value = value;
				}
			}*/

			/* find */
			weak_value find(const xns::cstring& str) {
				// get root node
				node* node = &_root;
				// loop through string
				for (xns::cstring::size_type x = 0; x < str.size(); ++x) {
					const size_type index = to_index(str[x]);
					if (node->_table.at(index) != nullptr) {
						// enter in node
						node = &(*node->_table.at(index));
					}
					// else return nullptr
					else { return nullptr; }
				}
				// return value
				return node->_value;
			}

			/* find */
			weak_value find(const xns::string_view& str) {
				// get root node
				node* node = &_root;
				// loop through string
				for (xns::string_view::size_type x = 0; x < str.size(); ++x) {
					const size_type index = to_index(str[x]);
					if (node->_table.at(index) != nullptr) {
						// enter in node
						node = &(*node->_table.at(index));
					}
					// else return nullptr
					else { return nullptr; }
				}
				// return value
				return node->_value;
			}






		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* _insert */
			template <xns::is_string S>
			node* _insert(const S& str) {
				// get root node
				node* nde = &_root;
				// loop through string
				for (typename S::size_type x = 0; x < str.size(); ++x) {
					// get character index
					const size_type index = to_index(str[x]);
					// check indexed node validity
					if (nde->_table.at(index) == nullptr) {
						// make new node
						nde->_table.at(index) = xns::make_unique_pointer<node>();
					} // move to node
					nde = &(*nde->_table.at(index));
				} // return node
				return nde;
			}

			/* to index */
			template <class C>
			size_type to_index(const C c) const {
				static_assert(sizeof(C) == 1, "C must be a char type");
				return (static_cast<size_type>(c)) - OFFSET;
			}


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* root children */
			node _root;

	};



};

#endif
