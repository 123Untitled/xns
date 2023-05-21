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

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- T R I E  C L A S S ----------------------------------------------------

	// this class implements a trie data structure
	// WARNING: this class stores pointers in a ascii lookup table
	// size of the lookup table is only printable ascii characters (95)
	// class do not check if the key is a printable ascii character !

	template <class T>
	class Trie final {

		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using Value = T;

			/* self type */
			using Self = Trie<Value>;

			/* weak value type */
			using WeakValue = xns::weak_ptr<Value>;

			/* size type */
			using Size = SizeT;



		private:




			// -- P R I V A T E  E N U M S ------------------------------------

			/* lookup table size */
			enum : Size {
				OFFSET = 32,
				LOOKUP_SIZE = 95
			};


			/* forward declaration */
			struct Node;


			// -- P R I V A T E  A L I A S E S --------------------------------

			/* unique node type */
			using UniqueNode = xns::unique_ptr<Node>;

			/* lookup table type */
			using Table = xns::array<UniqueNode, LOOKUP_SIZE>;

			/* node pointer type */
			using WeakNode = xns::weak_ptr<Node>;

			/* value pointer type */
			using Shared = xns::shared_ptr<Value>;



			// -- N O D E  S T R U C T ----------------------------------------

			struct Node final {

				// -- M E M B E R S -------------------------------------------

				/* childs */
				Table _table;

				/* value */
				Shared _value;


				// -- C O N S T R U C T O R S ---------------------------------

				/* default constructor */
				Node(void)
				: _table{}, _value{} {
					// code here...
				}

				/* value constructor */
				Node(Value* value)
				: _table{}, _value{value} {
					// code here...
				}

				/* destructor */
				~Node(void) {
					// code here...
				}

			};




		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Trie(void)
			: _root{ } {
				// code here...
			}

			/* destructor */
			~Trie(void) {
				// code here...
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* default insert */
			void insert(const xns::cstring& key) {
				// insert key
				Node* node = _insert(key);
				// allocate default value
				node->_value = xns::make_shared_pointer<Value>();
			}

			/* copy insert */
			void insert(const xns::cstring& key, const Value& value) {
				// insert key
				Node* node = _insert(key);
				// allocate copied value
				node->_value = xns::make_shared_pointer<Value>(value);
			}

			/* move insert */
			void insert(const xns::cstring& key, Value&& value) {
				// insert key
				Node* node = _insert(key);
				// allocate moved value
				node->_value = xns::make_shared_pointer<Value>(Xf::move(value));
			}

			/* variadic insert */
			template <class... A>
			void insert(const xns::cstring& key, A&&... args) {
				// insert key
				Node* node = _insert(key);
				// allocate value
				node->_value = xns::make_shared_pointer<Value>(Xf::forward<A>(args)...);
			}

			/* derived default insert */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			void insert(const xns::cstring& key) {
				// insert key
				Node* node = _insert(key);
				// allocate default value
				node->_value = xns::make_shared_pointer<D>();
			}

			/* derived copy insert */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			void insert(const xns::cstring& key, const D& value) {
				// insert key
				Node* node = _insert(key);
				// allocate copied value
				node->_value = xns::make_shared_pointer<D>(value);
			}

			/* derived move insert */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			void insert(const xns::cstring& key, D&& value) {
				// insert key
				Node* node = _insert(key);
				// allocate moved value
				node->_value = xns::make_shared_pointer<D>(Xf::move(value));
			}

			/* derived variadic insert */
			template <class D, class... A> requires (Xf::is_base_of_c<T, D>)
			void insert(const xns::cstring& key, A&&... args) {
				// insert key
				Node* node = _insert(key);
				// allocate value
				node->_value = xns::make_shared_pointer<D>(Xf::forward<A>(args)...);
			}

			using KeyVector = xns::vector<xns::cstring>;


			/* derived multi insert */
			template <class D, class... A> requires (Xf::is_base_of_c<T, D>)
			void insert(const KeyVector& alias, A&&... args) {
				// instanciate value
				Shared value = xns::make_shared_pointer<D>(Xf::forward<A>(args)...);
				// loop through alias
				for (KeyVector::size x = 0; x < alias.length(); ++x) {
					// insert key
					Node* node = _insert(alias[x]);
					// allocate value
					node->_value = value;
				}
			}

			/* variadic multi insert */
			template <class... A>
			void insert(const KeyVector& alias, A&&... args) {
				// instanciate value
				Shared value = xns::make_shared_pointer<Value>(Xf::forward<A>(args)...);
				// loop through alias
				for (KeyVector::size x = 0; x < alias.length(); ++x) {
					// insert key
					Node* node = _insert(alias[x]);
					// allocate value
					node->_value = value;
				}
			}

			/* find */
			WeakValue find(const xns::cstring& str) {
				// get root node
				Node* node = &_root;
				// loop through string
				for (xns::cstring::size_type x = 0; x < str.size(); ++x) {
					const Size index = to_index(str[x]);
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
			Node* _insert(const xns::cstring& str) {
				// get root node
				Node* node = &_root;
				// loop through string
				for (xns::cstring::size_type x = 0; x < str.size(); ++x) {
					// get character index
					const Size index = to_index(str[x]);
					// check indexed node validity
					if (node->_table.at(index) == nullptr) {
						// make new node
						node->_table.at(index) = xns::make_unique_pointer<Node>();
					} // move to node
					node = &(*node->_table.at(index));
				} // return node
				return node;
			}

			/* to index */
			template <class C>
			Size to_index(const C c) const {
				static_assert(sizeof(C) == 1, "C must be a char type");
				return (static_cast<Size>(c)) - OFFSET;
			}


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* root children */
			Node _root;

	};



};

#endif
