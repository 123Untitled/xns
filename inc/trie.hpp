#ifndef TRIE_HEADER
#define TRIE_HEADER

#include "Types.hpp"
#include "vector.hpp"
#include "pair.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- T R I E  C L A S S ----------------------------------------------------

	template <typename K, typename V>
	class Trie final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using Value = V;

			/* value reference type */
			using ValueRef = Value&;

			/* value const reference type */
			using ValueConstRef = const Value&;

			/* value move reference type */
			using ValueMoveRef = Value&&;

			/* value pointer type */
			using ValuePointer = Value*;

			/* value const pointer type */
			using ValueConstPointer = const Value*;

			/* key type */
			using Key = K;

			/* key reference type */
			using KeyRef = Key&;

			/* key const reference type */
			using KeyConstRef = const Key&;

			/* key move reference type */
			using KeyMoveRef = Key&&;

			/* key pointer type */
			using KeyPointer = Key*;

			/* key const pointer type */
			using KeyConstPointer = const Key*;

			/* size type */
			using Size = UInt64;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Trie(void)
			// initializations
			: _root{nullptr} { }

			/* destructor */
			~Trie(void) {
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* insert */
			void insert(KeyConstPointer key, Size size, ValueConstPointer value) {
			}

		private:

			// -- P R I V A T E  N E S T E D  C L A S S E S -------------------

			/* forward declaration */
			class Node;


			// -- P R I V A T E  A L I A S E S --------------------------------

			/* node pointer type */
			using NodePointer = Node*;

			/* pair type */
			using Pair = Xf::Pair<Key, NodePointer>;

			/* children type */
			using Children = Xf::Vector<Pair>;


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* root children */
			Children _root;
	};


	// -- N O D E  P R I V A T E  N E S T E D  C L A S S ----------------------

	template <typename K, typename V>
	class Trie<K, V>::Node final {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Node(void)
			// initializations
			: _children{}, _value{nullptr} { }

			/* value constructor */
			Node(ValuePointer value)
			// initializations
			: _children{}, _value{value} { }

			/* destructor */
			~Node(void) {
				// delete children
			}


			// -- P U B L I C  M E M B E R S ----------------------------------

			/* children */
			Children _children;

			/* value pointer */
			ValuePointer _value;



	};

};

#endif
