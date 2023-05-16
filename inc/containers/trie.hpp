#ifndef TRIE_HEADER
#define TRIE_HEADER

#include "types.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "tuple.hpp"
#include "unique_pointer.hpp"
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

			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using Value = T;

			/* value pointer type */
			using ValuePtr = Xf::UniquePointer<Value>;

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

			/* children type */
			using Childs = Xf::Array<Xf::UniquePointer<Node>, LOOKUP_SIZE>;



			// -- N O D E  S T R U C T ----------------------------------------

			struct Node final {

				// -- M E M B E R S -------------------------------------------

				/* childs */
				Childs _childs;

				/* value */
				ValuePtr _value;


				// -- C O N S T R U C T O R S ---------------------------------

				/* default constructor */
				Node(void)
				: _childs{}, _value{} {
					// code here...
				}

				/* value constructor */
				Node(Value* value)
				: _childs{}, _value{value} {
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
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* default insert */
			void insert(const Xf::CString& key) {
				// insert key
				Node* node = _insert(key);
				// allocate default value
				node->_value = Xf::make_unique_pointer<Value>();
			}

			/* copy insert */
			void insert(const Xf::CString& key, const Value& value) {
				// insert key
				Node* node = _insert(key);
				// allocate copied value
				node->_value = Xf::make_unique_pointer<Value>(value);
			}

			/* move insert */
			void insert(const Xf::CString& key, Value&& value) {
				// insert key
				Node* node = _insert(key);
				// allocate moved value
				node->_value = Xf::make_unique_pointer<Value>(Xf::move(value));
			}

			/* variadic insert */
			template <class... A>
			void insert(const Xf::CString& key, A&&... args) {
				// insert key
				Node* node = _insert(key);
				// allocate value
				node->_value = Xf::make_unique_pointer<Value>(Xf::forward<A>(args)...);
			}


			/* derived default insert */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			void insert(const Xf::CString& key) {
				// insert key
				Node* node = _insert(key);
				// allocate default value
				node->_value = Xf::make_unique_pointer<D>();
			}

			/* derived copy insert */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			void insert(const Xf::CString& key, const D& value) {
				// insert key
				Node* node = _insert(key);
				// allocate copied value
				node->_value = Xf::make_unique_pointer<D>(value);
			}

			/* derived move insert */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			void insert(const Xf::CString& key, D&& value) {
				// insert key
				Node* node = _insert(key);
				// allocate moved value
				node->_value = Xf::make_unique_pointer<D>(Xf::move(value));
			}





			/* find */
			Xf::WeakPointer<Value> find(const Xf::CString& str) {
				// get root node
				Node* node = &_root;
				// loop through string
				for (Xf::CString::Size x = 0; x < str.size(); ++x) {
					// get character
					const Size index = to_index(str[x]);

					if (node->_childs.at(index) == nullptr) {
						// return weak null pointer
						return nullptr;
					}

					// enter in node
					node = &(*node->_childs.at(index));

				}

				// return value
				return node->_value;

			}


		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* _insert */
			Node* _insert(const Xf::CString& str) {
				// get root node
				Node* node = &_root;
				// loop through string
				for (Xf::CString::Size x = 0; x < str.size(); ++x) {
					// get character index
					const Size index = to_index(str[x]);
					// check indexed node validity
					if (node->_childs.at(index) == nullptr) {
						// make new node
						node->_childs.at(index) = Xf::make_unique_pointer<Node>();
					} // move to node
					node = &(*node->_childs.at(index));
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
