#ifndef MAP_HEADER
#define MAP_HEADER

#include "types.hpp"
#include "allocator.hpp"
#include "unique_pointer.hpp"
#include "weak_pointer.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M A P  C L A S S ----------------------------------------------------

//	template <class K, class V>
//	class map final {
//
//		public:
//
//			// -- T Y P E S ---------------------------------------------------
//
//			/* key type */
//			using key = K;
//
//			/* value type */
//			using value_type = V;
//
//			/* size type */
//			using size_type = xns::size_t;
//
//			/* reference type */
//			using reference = value_type&;
//
//			/* const reference type */
//			using const_reference = const value_type&;
//
//			/* move reference type */
//			using move_reference = value_type&&;
//
//			/* pointer type */
//			using mutable_pointer = value_type*;
//
//			/* const pointer type */
//			using const_pointer = const value_type*;
//
//			/* allocator type */
//			using allocator = xns::allocator<value_type>;
//
//
//		private:
//
//			/* forward declaration */
//			struct node;
//
//
//			// -- P R I V A T E  T Y P E S ------------------------------------
//
//			/* node pointer type */
//			using node_pointer = node*;
//
//			/* weak node pointer type */
//			using weak_node = xns::weak_ptr<node>;
//
//			/* unique node pointer type */
//			using unique_node = xns::unique_ptr<node>;
//
//
//
//			// -- P R I V A T E  M E M B E R S --------------------------------
//
//			/* root node */
//			unique_node _root;
//
//			/* storage */
//			unique_node _storage;
//
//			/* size */
//			size_type _size;
//
//
//		public:
//
//			// -- C O N S T R U C T O R S -------------------------------------
//
//			/* default constructor */
//			map(void)
//			: _root {nullptr}, _storage {nullptr}, _size {0} {
//				// code here...
//			}
//
//
//			// -- I N S E R T -------------------------------------------------
//
//
//			/* copy insert */
//			void copy_insert(const key& key, const_reference value) {
//
//				unique_node* nde  = &_root;
//				weak_node parent  = nullptr;
//
//				// loop until node is null
//				while (*nde) {
//					// keep track of parent
//					parent = *nde;
//					// less compare
//					if      (key < (*nde)->_value) { nde = &(*nde)->_left; }
//					// greater compare
//					else if (key > (*nde)->_value) { nde = &(*nde)->_right; }
//					// equal compare, replace value ?
//					else                         {
//						//node->_value = value;
//						return;
//					}
//				}
//
//				// create new node
//				//*nde = xns::make_unique_pointer<node>(value, parent);
//
//
//			}
//
//			/* move insert */
//			void move_insert(const key& key, move_reference value) {
//				// code here...
//			}
//
//			/* emplace insert */
//			template <class... A>
//			void emplace_insert(const key& key, A&&... args) {
//				// code here...
//			}
//
//
//
//
//
//		private:
//
//			// -- N O D E  S T R U C T ----------------------------------------
//
//			struct node final {
//
//
//				// -- M E M B E R S -------------------------------------------
//
//				/* value */
//				value_type _value;
//
//				/* left node */
//				unique_node _left;
//
//				/* right node */
//				unique_node _right;
//
//				/* parent node */
//				weak_node _parent;
//
//				/* depth */
//				size_type _depth;
//
//
//			};
//
//
//
//	};

};

#endif
