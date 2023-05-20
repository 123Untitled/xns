#ifndef LITERAL_HEADER
#define LITERAL_HEADER

#include "types.hpp"
#include "string_traits.hpp"
#include "macro.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I T E R A L  C L A S S --------------------------------------------

	/* embedded compile-time string literal */
	template <class T, T... A>
	class literal {


		// -- A S S E R T I O N S ---------------------------------------------

		/* require character type */
		static_assert(Xf::is_char_c<T>, "LITERAL TYPE MUST BE A CHARACTER TYPE");

		/* require non-empty string */
		static_assert(sizeof...(A) > 0, "LITERAL MUST NOT BE EMPTY");


		private:

			// -- C O N S T A N T S -------------------------------------------

			static constexpr xns::size_t size_v = sizeof...(A);


		public:

			// -- T Y P E S ---------------------------------------------------

			/* chararacter type */
			using char_t = T;

			/* self type */
			using self = literal<char_t, A...>;

			/* array type */
			using array = char_t[size_v + 1];

			/* const pointer type */
			using const_pointer = const char_t*;

			/* size type */
			using size_type = xns::size_t;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			consteval literal(void) = default;

			/* non-assignable class */
			NON_ASSIGNABLE(literal);

			/* destructor */
			constexpr ~literal(void) = default;


			// -- A C C E S S O R S -------------------------------------------

			/* size */
			static consteval size_type size(void) {
				// return size
				return size_v;
			}

			/* underlying array */
			static consteval const_pointer data(void) {
				// return data
				return _data;
			}


		private:

			// -- S T A T I C  D A T A ----------------------------------------

			static constexpr const array _data = {A..., '\0'};

	};


	// -- I S  L I T E R A L --------------------------------------------------

	/* literal false type */
	template <class T>
	struct is_literal_s : public xns::false_t {};

	/* literal true type */
	template <class T, T... A>
	struct is_literal_s<xns::literal<T, A...>> : public xns::true_t {};

	/* literal concept */
	template <class T>
	concept is_literal = is_literal_s<T>::value;




}


/* literal helper, need to be defined in global namespace */

/* literal operator "" */ // WARNING: this is a GNU extension
template<class T, T... A>
consteval xns::literal<T, A...> operator ""_to_literal(void) {
	// magic happens here
	return xns::literal<T, A...>{};
}

/* macro helper to instantiate a literal */
#define make_literal(text) text##_to_literal

/* macro helper to get a literal type */
#define literal(text) decltype(make_literal(text))



#endif
