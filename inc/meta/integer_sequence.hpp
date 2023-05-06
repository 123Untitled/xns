#ifndef INTEGER_SEQUENCE_HEADER
#define INTEGER_SEQUENCE_HEADER

#include <iostream>
#include "type_traits.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I N T E G E R  S E Q U E N C E --------------------------------------

	template <class T, T... N>
	struct IntegerSeq final {

		/* check if T is an integral type */
		static_assert(Xf::is_integral<T>::value, "not integral type");

		/* size type */
		using Size = T;

		/* self type */
		using Self  = IntegerSeq<Size, N...>;

		/* size accessor */
		static inline constexpr Size size(void) noexcept {
			return sizeof...(N);
		}

	};

	/* alias to integer_sequence of type size_t */
	template <size_t... N>
	using IndexSeq = IntegerSeq<size_t, N...>;


	// -- M A K E  I N T E G E R  S E Q U E N C E -----------------------------

	template <class IntType, IntType BEGIN, IntType END, IntType STEP = 1>
	class MakeIntegerSeq {

		/* check if range is valid */
		static_assert(BEGIN <= END, "!YOU WILL LOOP UNTIL THE END OF WORLD!");

		private:

			// -- P R I V A T E  I M P L E M E N T A T I O N ----------------------

			/* forward declaration */
			template <IntType... SEQUENCE>
			struct implementation;

			/* specialization for N == B, which means we have to stop the recursion */
			template <IntType NUMBER, IntType... SEQUENCE> requires (NUMBER == BEGIN)
			struct implementation<NUMBER, SEQUENCE...> {

				/* type of the integer sequence */
				using type = IntegerSeq<IntType, SEQUENCE...>;
			};

			/* specialization for N != B, which means we have to continue the recursion */
			template <IntType NUMBER, IntType... SEQUENCE> requires (NUMBER != BEGIN)
			struct implementation<NUMBER, SEQUENCE...> {

				/* recursive call of type */
				using type = typename implementation<NUMBER - STEP, NUMBER - STEP, SEQUENCE...>::type;
			};

		public:

			// -- P U B L I C  I N T E R F A C E ----------------------------------

			using Type = typename implementation<END>::type;

	};

	/* alias to make an integer sequence of type T with length N */
	template <class T, T N>
	using make_integer_sequence = typename MakeIntegerSeq<T, 0, N>::Type;

	/* alias to make an integer sequence of type T starting from B and ending at E */
	template <class T, T B, T E>
	using make_integer_range    = typename MakeIntegerSeq<T, B, E>::Type;

	/* alias to make an index sequence of length N */
	template <size_t N>
	using make_index_sequence   = make_integer_sequence<size_t, N>;

	/* alias to make an index sequence starting from B and ending at E */
	template <size_t BEGIN, size_t END>
	using make_index_range      = make_integer_range<size_t, BEGIN, END>;

	/* alias to make an index range with a step */
	template <size_t BEGIN, size_t END, size_t STEP>
	using make_index_range_step = typename MakeIntegerSeq<size_t, BEGIN, END, STEP>::Type;

	/* alias to transform a parameter pack into an index sequence */
	template <class... Types>
	using IndexSeqFor    = make_index_sequence<sizeof...(Types)>;


	// -- D E B U G -----------------------------------------------------------


	/* debug function */
	template<class T, T... ints>
	void debug_sequence(IntegerSeq<T, ints...> int_seq) {
		std::cout << "The sequence of size " << int_seq.size() << ": ";
		((std::cout << ints << ' '), ...);
		std::cout << '\n';
	}

}


#endif
