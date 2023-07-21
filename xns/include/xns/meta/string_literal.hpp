#ifndef STRING_LITERAL_HEADER
#define STRING_LITERAL_HEADER

#include "is_char.hpp"
#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S T R I N G  L I T E R A L ------------------------------------------

	template<xns::is_char T, xns::size_t N>
	class string_literal {

		// -- assertions ------------------------------------------------------

		/* check for null size */
		static_assert(N > 0, "STRING LITERAL MUST HAVE SIZE > 0");

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = string_literal<T, N>;

			/* character type */
			using char_t = T;

			/* const pointer type */
			using const_pointer = const char_t*;


			// -- public members ----------------------------------------------

			/* array of characters */
			char_t _data[N];



			// -- public constructors -----------------------------------------

			/* deleted default constructor */
			string_literal(void) = delete;

			/* array constructor */
			consteval string_literal(const char_t (&str)[N]) noexcept {

				for (xns::size_t x = 0; x < N; ++x) {
					_data[x] = str[x];
				}
				// force null termination
				if (_data[N - 1] != '\0') {
					_data[N - 1] = '\0';
				}
			}

			/* copy constructor */
			consteval string_literal(const self&) noexcept = default;

			/* move constructor */
			consteval string_literal(self&&)      noexcept = default;

			/* destructor */
			~string_literal(void)                 noexcept = default;


			// -- public accessors --------------------------------------------

			/* get data */
			consteval const_pointer data(void) const noexcept {
				return _data;
			}

			/* get runtime data */
			const_pointer runtime_data(void) const noexcept {
				return _data;
			}

			/* get size */
			consteval xns::size_t size(void) const noexcept {
				return N - 1;
			}

			/* empty */
			consteval bool empty(void) const noexcept {
				return N == 0;
			}


			// -- public subscript operator -----------------------------------

			/* subscript operator */
			consteval char_t operator[](xns::size_t index) const noexcept {
				return _data[index];
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			template <xns::is_char U, xns::size_t M>
			consteval bool operator==(const U (&other)[M]) const noexcept {
				// check size
				if (N != M) { return false; }
				// compare characters
				return compare<0>(other);
			}

			/* inequality operator */
			template <xns::is_char U, xns::size_t M>
			consteval bool operator!=(const U (&other)[M]) const noexcept {
				return not (*this == other);
			}

			/* equality operator */
			template <xns::is_char U, xns::size_t M>
			consteval bool operator==(const string_literal<U, M>& other) const noexcept {
				return *this == other._data;
			}

			/* inequality operator */
			template <xns::is_char U, xns::size_t M>
			consteval bool operator!=(const string_literal<U, M>& other) const noexcept {
				return not (*this == other._data);
			}


		private:

			// -- comparison utility ------------------------------------------

			/* compare */
			template <xns::size_t I, xns::is_char U, xns::size_t M>
			consteval bool compare(const U (&other)[M]) const noexcept requires (I < N) {
				// compare current character and recurse
				return _data[I] == other[I] ? compare<I + 1>(other) : false;
			}

			/* compare, end of recursion */
			template <xns::size_t I, xns::is_char U, xns::size_t M>
			consteval bool compare(const U (&other)[M]) const noexcept requires (I == N) {
				// end of recursion
				return true;
			}

	};


}

#endif
