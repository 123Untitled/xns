/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_INTEGER_SEQUENCE_HEADER
#define XNS_INTEGER_SEQUENCE_HEADER

#include "is_integral.hpp"
#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N T E G E R  S E Q U E N C E --------------------------------------

	template <typename T, T... N>
	class integer_sequence final {


		// -- assertions ------------------------------------------------------

		/* check if T is an integral type */
		static_assert(xns::is_integral<T>, "integer_sequence: T must be an integral type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self  = xns::integer_sequence<T, N...>;

			/* size type */
			using type = T;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr integer_sequence(void) noexcept = default;

			/* copy constructor */
			constexpr integer_sequence(const self&) noexcept = default;

			/* move constructor */
			constexpr integer_sequence(self&&) noexcept = default;

			/* destructor */
			~integer_sequence(void) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto constexpr operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto constexpr operator=(self&&) noexcept -> self& = default;


			// -- public static functions -------------------------------------

			/* size */
			static consteval auto size(void) noexcept -> type {
				return sizeof...(N);
			}

	}; // class integer_sequence


	/* integer_sequence of size_t */
	template <xns::size_t... N>
	using index_sequence = xns::integer_sequence<xns::size_t, N...>;


	// -- M A K E  I N T E G E R  S E Q U E N C E -----------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {



		template <typename int_type, int_type BEGIN, int_type END, int_type STEP = 1>
		class make_integer_sequence final {


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
					using type = xns::integer_sequence<int_type, SEQUENCE...>;
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

	} // namespace impl

	/* alias to make an integer sequence of type T with length N */
	template <typename T, T N>
	using make_integer_sequence = typename impl::make_integer_sequence<T, 0, N>::type;

	/* alias to make an integer sequence of type T starting from B and ending at E */
	template <class T, T B, T E>
	using make_integer_range    = typename impl::make_integer_sequence<T, B, E>::type;


	/* alias to make an index sequence of length N */
	template <xns::size_t N>
	using make_index_sequence   = make_integer_sequence<xns::size_t, N>;

	/* alias to make an index sequence starting from B and ending at E */
	template <xns::size_t B, xns::size_t E>
	using make_index_range      = make_integer_range<size_t, B, E>;


	/* alias to make an index range with a step */
	template <xns::size_t B, xns::size_t E, xns::size_t S>
	using make_index_range_step = typename impl::make_integer_sequence<xns::size_t, B, E, S>::type;


	/* alias to transform a parameter pack into an index sequence */
	template <class... A>
	using index_sequence_for    = make_index_sequence<sizeof...(A)>;

}

#endif // XNS_INTEGER_SEQUENCE_HEADER
