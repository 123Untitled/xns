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

#ifndef XNS_RANDOM_HEADER
#define XNS_RANDOM_HEADER

#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "type_traits/types.hpp"
#include "config/macros.hpp"
#include "type_traits/type_categories/is_integral.hpp"
#include "type_traits/type_properties/is_signed.hpp"
#include "type_traits/type_properties/is_unsigned.hpp"
#include "type_traits/type_modifications/make_signed.hpp"
#include "type_traits/type_modifications/make_unsigned.hpp"
#include "utility/numeric_limits.hpp"

#include "random/xorshift.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R A N D O M  C L A S S ----------------------------------------------

	class random final {

		public:

			// -- T Y P E S ---------------------------------------------------

			/* size type */
			using size_type = xns::size_t;


			// -- S T A T I C  M E T H O D S ----------------------------------

			/* random integer */
			static size_type random_gen(const size_type range);

			/* random boolean */
			static bool random_bool(void);


			/* random integer */
			template <typename T>
			static auto integral(void) -> xns::remove_cvr<T> {

				// remove const and reference
				using type = xns::remove_cvr<T>;

				// check for integral type
				static_assert(xns::is_integral<type>,
						"): RANDOM: INTEGRAL TYPE REQUIRED :(");

				// get random number
				xns::size_t rnd = xns::xorshift::next64();

				// handle boolean type
				if constexpr (xns::is_same<type, bool>) {
					return rnd % 2;
				}

				else {
					rnd %= (xns::limits<xns::make_unsigned<type>>::max());// + 1);

					return static_cast<type>(rnd);
				}
			}


		private:

			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			random(void);

			/* non-assignable class */
			NON_ASSIGNABLE(random);

			/* destructor */
			~random(void);


			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* instance */
			static random _instance;


	};

}


#endif
