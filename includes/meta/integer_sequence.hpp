#ifndef XNS_INTEGER_SEQUENCE_HEADER
#define XNS_INTEGER_SEQUENCE_HEADER

#include "is_integral.hpp"

//#include "output.hpp"

//#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N T E G E R  S E Q U E N C E --------------------------------------

	template <class T, T... N>
	struct integer_seq final {


		// -- A S S E R T I O N S ---------------------------------------------

		/* check if T is an integral type */
		static_assert(xns::is_integral<T>, "N MUST BE AN INTEGRAL TYPE");


		// -- T Y P E S -------------------------------------------------------

		/* size type */
		using type = T;

		/* self type */
		using self  = integer_seq<type, N...>;


		// -- A C C E S S O R S -----------------------------------------------

		/* size accessor */
		static inline consteval type size(void) noexcept {
			return sizeof...(N);
		}


	};


	/* integer_sequence of size_t */
	template <xns::size_t... N>
	using index_seq = integer_seq<xns::size_t, N...>;


	// -- M A K E  I N T E G E R  S E Q U E N C E -----------------------------

	template <class int_type, int_type BEGIN, int_type END, int_type STEP = 1>
	class _make_integer_seq {


		// -- A S S E R T I O N S ---------------------------------------------

		/* check if range is valid */
		static_assert(BEGIN <= END, "!YOU WILL LOOP UNTIL THE END OF WORLD!");


		private:

			// -- P R I V A T E  I M P L E M E N T A T I O N ------------------

			/* forward declaration */
			template <int_type... SEQUENCE>
			struct impl;

			/* specialization for N == B, which means we have to stop the recursion */
			template <int_type NUMBER, int_type... SEQUENCE> requires (NUMBER == BEGIN)
			struct impl<NUMBER, SEQUENCE...> {

				/* type of the integer sequence */
				using type = integer_seq<int_type, SEQUENCE...>;
			};

			/* specialization for N != B, which means we have to continue the recursion */
			template <int_type NUMBER, int_type... SEQUENCE> requires (NUMBER != BEGIN)
			struct impl<NUMBER, SEQUENCE...> {

				/* recursive call of type */
				using type = typename impl<NUMBER - STEP, NUMBER - STEP, SEQUENCE...>::type;
			};


		public:

			// -- R E C U R S I V E  T Y P E ----------------------------------

			using type = typename impl<END>::type;

	};


	/* alias to make an integer sequence of type T with length N */
	template <class T, T N>
	using make_integer_sequence = typename _make_integer_seq<T, 0, N>::type;

	/* alias to make an integer sequence of type T starting from B and ending at E */
	template <class T, T B, T E>
	using make_integer_range    = typename _make_integer_seq<T, B, E>::type;


	/* alias to make an index sequence of length N */
	template <xns::size_t N>
	using make_index_sequence   = make_integer_sequence<xns::size_t, N>;

	/* alias to make an index sequence starting from B and ending at E */
	template <xns::size_t B, xns::size_t E>
	using make_index_range      = make_integer_range<size_t, B, E>;


	/* alias to make an index range with a step */
	template <xns::size_t B, xns::size_t E, xns::size_t S>
	using make_index_range_step = typename _make_integer_seq<xns::size_t, B, E, S>::type;


	/* alias to transform a parameter pack into an index sequence */
	template <class... A>
	using index_seq_for    = make_index_sequence<sizeof...(A)>;



	// -- D E B U G -----------------------------------------------------------


	/* debug function */
	template<class T, T... ints>
	void debug_sequence(integer_seq<T, ints...> int_seq) {
		/*
		xns::output::write("The sequence of size ");
		std::cout << "The sequence of size " << int_seq.size() << ": ";
		((std::cout << ints << ' '), ...);
		std::cout << '\n';
		*/
	}

}


#endif
