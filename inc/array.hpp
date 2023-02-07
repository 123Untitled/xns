#ifndef ARRAY_HEADER
#define ARRAY_HEADER

#include "Types.hpp"
#include "move.hpp"
#include "forward.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- A R R A Y  C L A S S ------------------------------------------------

	template <typename T, UInt64 N>
	class Array final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using Value = T;

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


			// -- P U B L I C  M E M B E R S ----------------------------------

			/* array */
			Value _array[N];


			// -- O P E R A T O R S -------------------------------------------

			/* subscript */
			Reference operator[](const Size index) {
				// return reference
				return _array[index];
			}

			/* const subscript */
			ConstReference operator[](const Size index) const {
				// return reference
				return _array[index];
			}


			// -- E L E M E N T  A C C E S S ----------------------------------

			/* front */
			Reference front(void) {
				// return reference
				return _array[0];
			}

			/* const front */
			ConstReference front(void) const {
				// return reference
				return _array[0];
			}

			/* back */
			Reference back(void) {
				// return reference
				return _array[N - 1];
			}

			/* const back */
			ConstReference back(void) const {
				// return reference
				return _array[N - 1];
			}

			/* data */
			Pointer data(void) {
				// return pointer
				return _array;
			}

			/* const data */
			ConstPointer data(void) const {
				// return pointer
				return _array;
			}


			// -- A C C E S S O R S -------------------------------------------

			/* size */
			constexpr Size size(void) const {
				// return fixed size
				return N;
			}

			/* empty */
			constexpr bool empty(void) const {
				// return fixed size
				return N == 0;
			}


			// -- M O D I F I E R S -------------------------------------------

			/* fill */
			void fill(const Value& value) {
				// fill array
				for (Size i = 0; i < N; ++i) {
					// assign value
					_array[i] = value;
				}
			}


	};

};

#endif



