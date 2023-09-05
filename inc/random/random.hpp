#ifndef RANDOM_HEADER
#define RANDOM_HEADER

#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "types.hpp"
#include "macro.hpp"
#include "is_integral.hpp"
#include "is_signed.hpp"
#include "is_unsigned.hpp"
#include "make_signed.hpp"
#include "make_unsigned.hpp"
#include "numeric_limits.hpp"

#include "xorshift.hpp"

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
					rnd %= (xns::limits::max<
							xns::make_unsigned<type>>());// + 1);

					if constexpr (xns::is_signed<type>) {
						return reinterpret_cast<type&>(rnd);
					}
					else {
						return static_cast<type>(rnd);
					}
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
