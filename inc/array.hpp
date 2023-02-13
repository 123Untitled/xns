#ifndef ARRAY_HEADER
#define ARRAY_HEADER

#include "types.hpp"
#include "move.hpp"
#include "forward.hpp"
#include <iostream>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- A R R A Y  C L A S S ------------------------------------------------

	template <typename T, UInt64 N>
	struct Array final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using Value = T;

			/* size type */
			using Size = decltype(N);

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


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			//constexpr Array(void) = default;

			/* initializer list constructor */
			//template <typename... A>
			//constexpr Array(A&&... args)
			//: _array{Xf::forward<A>(args)...} {
			//	// code here...
			//}

			/* copy constructor */
			// implicitly declared

			/* move constructor */
			// implicitly declared


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

			/* idx */
			template <typename I>
			Reference idx(const I index) {
				// return reference with static cast
				return _array[static_cast<Size>(index)];
			}

			/* const idx */
			template <typename I>
			ConstReference idx(const I index) const {
				// return const reference with static cast
				return _array[static_cast<Size>(index)];
			}

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
				for (Size x = 0; x < N; ++x) {
					// assign value
					_array[x] = value;
				}
			}


		//private:

			/* array */
			Value _array[N];

	};

	// deduction guide
	template <class T, class... A>
	Array(T, A...) -> Array<T, 1 + sizeof...(A)>;

	// deduction guide for const char*
	template <UInt64 N>
	Array(const char(&)[N]) -> Array<char, N>;



	// << operator
	template <typename T, UInt64 N>
	std::ostream& operator<<(std::ostream& os, const Array<T, N>& array) {
		// print array
		for (UInt64 x = 0; x < N; ++x) {
			// print value
			os << array[x] << " ";
		}
		// return stream
		return os;
	}


};

#endif

