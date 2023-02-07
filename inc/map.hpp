#ifndef MAP_HEADER
#define MAP_HEADER

#include "Types.hpp"
#include "allocator.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- M A P  C L A S S ----------------------------------------------------

	template <typename K, typename V>
	class Map final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* key type */
			using Key = K;

			/* value type */
			using Value = V;

			/* size type */
			using Size = UInt64;

			/* reference type */
			using Reference = Value&;

			/* const reference type */
			using ConstReference = const Value&;

			/* move reference type */
			using MoveReference = Value&&;

			/* pointer type */
			using Pointer = Value*;

			/* const pointer type */
			using ConstPointer = const Value*;

			/* allocator type */
			using Allocator = Xf::Allocator<Value>;


	};

};

#endif
