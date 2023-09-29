#ifndef XNS_STRING_LITERAL_HEADER
#define XNS_STRING_LITERAL_HEADER

#include "is_char.hpp"
#include "types.hpp"
#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	// -- B A S I C  S T R I N G  L I T E R A L -------------------------------

	template<typename T, xns::size_t N>
	class basic_string_literal {


		// -- assertions ------------------------------------------------------

		/* check character type */
		static_assert(xns::is_char<T>,
				"): STRING_LITERAL: MUST BE OF CHARACTER TYPE :(");

		/* check for null size */
		static_assert(N > 0, "): STRING_LITERAL: MUST HAVE SIZE > 0 :(");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = basic_string_literal<T, N>;

			/* character type */
			using char_t = T;

			/* const pointer type */
			using const_pointer = const char_t*;

			/* size type */
			using size_type = decltype(N);


			// -- public members ----------------------------------------------

			/* array of characters */
			char_t _data[N];


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			basic_string_literal(void) = delete;

			/* array constructor */
			template <typename U, xns::size_t M>
			consteval basic_string_literal(const U (&str)[M]) noexcept
			: _data{} {

				for (xns::size_t x = 0; x < N; ++x) {
					_data[x] = str[x];
				}
			}

			/* copy constructor */
			inline consteval basic_string_literal(const self&) noexcept = default;

			/* move constructor */
			inline consteval basic_string_literal(self&&) noexcept = default;

			/* destructor */
			inline ~basic_string_literal(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline consteval auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			inline consteval auto operator=(self&&) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* get data */
			inline consteval auto data(void) const noexcept -> const_pointer {
				return _data;
			}

			/* get runtime data */
			inline auto runtime_data(void) const noexcept -> const_pointer {
				return _data;
			}

			/* get size */
			inline consteval auto size(void) const noexcept -> size_type {
				return N - 1;
			}

			/* empty */
			inline consteval auto empty(void) const noexcept -> bool {
				return N == 0;
			}


			// -- public subscript operator -----------------------------------

			/* subscript operator */
			inline consteval auto operator[](const size_type index) const noexcept -> char_t {
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
			template <typename U, xns::size_t M>
			consteval bool operator==(const basic_string_literal<U, M>& other) const noexcept {
				return *this == other._data;
			}

			/* inequality operator */
			template <typename U, xns::size_t M>
			consteval bool operator!=(const basic_string_literal<U, M>& other) const noexcept {
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


	// -- deduction guides ----------------------------------------------------

	template <typename T, xns::size_t N>
	basic_string_literal(const T (&)[N]) -> basic_string_literal<T, N>;


	//// -- S T R I N G  L I T E R A L ------------------------------------------

	//template <xns::size_t N>
	//class string_literal final : public basic_string_literal<char, N> {


	//	// -- assertions ------------------------------------------------------

	//	/* check for 'char' type */
	//	//static_assert(xns::is_same<T, char>,
	//	//		"): STRING_LITERAL: MUST BE 'char' TYPE :(");


	//	public:

	//		// -- public lifecycle --------------------------------------------

	//		/* array constructor override */
	//		template <xns::size_t M>
	//		inline consteval string_literal(const char (&str)[M]) noexcept
	//		: basic_string_literal<char, M>{str} {}


	//};

	//// -- deduction guides ----------------------------------------------------

	//template <xns::size_t N>
	//string_literal(const char (&)[N]) -> xns::string_literal<N>;




	//// -- W S T R I N G  L I T E R A L ----------------------------------------

	//template <typename T, xns::size_t N>
	//class wstring_literal final : public basic_string_literal<T, N> {


	//	// -- assertions ------------------------------------------------------

	//	/* check for 'wchar_t' type */
	//	static_assert(xns::is_same<T, wchar_t>,
	//			"): WSTRING_LITERAL: MUST BE 'wchar_t' TYPE :(");


	//	public:

	//		// -- public lifecycle --------------------------------------------

	//		/* array constructor override */
	//		template <typename U, xns::size_t M>
	//		inline consteval wstring_literal(const U (&str)[M]) noexcept
	//		: basic_string_literal<U, M>(str) {}

	//};

	//// -- deduction guides ----------------------------------------------------

	//template <typename T, xns::size_t N>
	//wstring_literal(const T (&)[N]) -> wstring_literal<T, N>;




	//// -- U 8 S T R I N G  L I T E R A L --------------------------------------

	//template <typename T, xns::size_t N>
	//class u8string_literal final : public basic_string_literal<T, N> {


	//	// -- assertions ------------------------------------------------------

	//	/* check for 'char8_t' type */
	//	static_assert(xns::is_same<T, char8_t>,
	//			"): U8STRING_LITERAL: MUST BE 'char8_t' TYPE :(");


	//	public:

	//		// -- public lifecycle --------------------------------------------

	//		/* array constructor override */
	//		template <typename U, xns::size_t M>
	//		inline consteval u8string_literal(const U (&str)[M]) noexcept
	//		: basic_string_literal<U, M>(str) {}

	//};

	//// -- deduction guides ----------------------------------------------------

	//template <typename T, xns::size_t N>
	//u8string_literal(const T (&)[N]) -> u8string_literal<T, N>;




	//// -- U 1 6 S T R I N G  L I T E R A L ------------------------------------

	//template <typename T, xns::size_t N>
	//class u16string_literal final : public basic_string_literal<T, N> {


	//	// -- assertions ------------------------------------------------------

	//	/* check for 'char16_t' type */
	//	static_assert(xns::is_same<T, char16_t>,
	//			"): U8STRING_LITERAL: MUST BE 'char16_t' TYPE :(");


	//	public:

	//		// -- public lifecycle --------------------------------------------

	//		/* array constructor override */
	//		template <typename U, xns::size_t M>
	//		inline consteval u16string_literal(const U (&str)[M]) noexcept
	//		: basic_string_literal<U, M>(str) {}

	//};

	//// -- deduction guides ----------------------------------------------------

	//template <typename T, xns::size_t N>
	//u16string_literal(const T (&)[N]) -> u16string_literal<T, N>;




	//// -- U 3 2 S T R I N G  L I T E R A L ------------------------------------

	//template <typename T, xns::size_t N>
	//class u32string_literal final : public basic_string_literal<T, N> {


	//	// -- assertions ------------------------------------------------------

	//	/* check for 'char32_t' type */
	//	static_assert(xns::is_same<T, char32_t>,
	//			"): U8STRING_LITERAL: MUST BE 'char32_t' TYPE :(");


	//	public:

	//		// -- public lifecycle --------------------------------------------

	//		/* array constructor override */
	//		template <typename U, xns::size_t M>
	//		inline consteval u32string_literal(const U (&str)[M]) noexcept
	//		: basic_string_literal<U, M>(str) {}

	//};

	//// -- deduction guides ----------------------------------------------------

	//template <typename T, xns::size_t N>
	//u32string_literal(const T (&)[N]) -> u32string_literal<T, N>;










}

#endif
