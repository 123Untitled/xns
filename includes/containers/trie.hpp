#ifndef XNS_TRIE_HEADER
#define XNS_TRIE_HEADER

#include "types.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "tuple.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"
#include "string.hpp"


#include "string_literal.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T R I E  C L A S S --------------------------------------------------

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
			enum : size_type { LOOKUP_SIZE = (1 << xns::bits_per_byte) };


			/* forward declaration */
			struct node;


			// -- private types -----------------------------------------------

			/* value pointer type */
			using type_ptr = type*;

			/* node pointer type */
			using node_ptr = self::node*;

			/* lookup table type */
			using table = xns::array<node_ptr, LOOKUP_SIZE>;

			/* node pointer type */
			using weak_node = xns::weak_ptr<self::node>;

			/* node address type */
			using node_addr = self::node**;

			/* allocator type */
			using allocator = xns::allocator<self::node>;



			// -- private structs ---------------------------------------------

			/* node */
			struct node {


				// -- members -------------------------------------------------

				/* childs */
				table _table;

				/* value */
				type_ptr _value;


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				inline node(void) noexcept
				: _table{}, _value{nullptr} {}

				/* non-assignable class */
				non_assignable(node);

				/* destructor */
				inline ~node(void) noexcept = default;

			};



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline trie(void) noexcept
			: _root{}, _size{0} {}

			/* destructor */
			inline ~trie(void) noexcept = default;


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* insert */
			//template <typename... A>
			//void insert(const xns::string& key, A&&... value) {
			//	// insert key
			//	node_ptr node = insert_impl(key);
			//	// allocate default value
			//	node->_value = xns::memory::pool<type>::allocate();
			//	// construct value
			//	xns::memory::pool<type>::construct(node->_value, xns::forward<A>(value)...);
			//	// increment size
			//	++_size;
			//}


			/* contains */
			auto find(const xns::string& str) -> bool {
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
					// else return false
					else return false;
				} // return true if node has value
				return node->_value != nullptr;
			}


			/* size */
			inline auto size(void) const noexcept -> size_type {
				return _size;
			}


		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* _insert */
			auto insert_impl(const xns::string& str) -> node_ptr {
				// get root node
				node_ptr node = &_root;
				// loop through string
				for (typename xns::string::size_type x = 0; x < str.size(); ++x) {
					// get index
					const auto idx = to_idx(str[x]);
					// check indexed node validity
					if (node->_table[idx] == nullptr) {
						// make new node
						node->_table[idx] = allocator::allocate();
						// construct new node
						allocator::construct(node->_table[idx]);
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

			/* size */
			size_type _size;

	};



	// compile time compressed prefix tree (hard to implement, but possible)
	// words known at compile time are stored in a trie
	// search is done at runtime, but trie is built at compile time



	template <xns::basic_string_literal... L>
	class compile_time_trie final {

		public:

			using size_type = decltype(sizeof(0));

			inline auto search(void) noexcept -> bool {
				/* not implemented */
				return false;
			}


		private:


			static consteval auto get_number_of_nodes(void) noexcept -> size_type {





				return 0;
			}



	};


	// hard to implement.
	// alternative: use a hash table with a perfect hash function
	// complexity: O(1) + comparison of one string O(n)
	// where n is the length of the string
	// so it's same as a trie, but with a hash table instead of a tree


};

#endif
