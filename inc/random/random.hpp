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
			template <xns::is_arithmetic T>
			static auto random_int(void) -> T {


				// get random number
				xns::u64 rnd = xns::xorshift::next64();

				if constexpr (xns::is_floating<T>) {
					T res = static_cast<T>(rnd) / static_cast<T>(xns::limits::max<xns::u64>());
					return (T)(rnd % 10) + res;
					//return static_cast<T>(rnd);
				}

				if constexpr (xns::is_same<T, decltype(rnd)>) { return rnd; }


				if constexpr (xns::is_unsigned<T>) {
					return static_cast<T>(rnd % (xns::limits::max<T>() + 1));
				}


				/*
				using unsigned_type = xns::make_unsigned<T>;

				xns::u64 red = rnd % (xns::max<unsigned_type>() + 1);
				xns::s64 sgn = red - xns::min<T>();


				return static_cast<T>(sgn);
				*/
				return static_cast<T>(rnd);
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
