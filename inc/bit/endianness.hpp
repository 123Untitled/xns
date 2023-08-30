#ifndef ENDIANNESS_HEADER
#define ENDIANNESS_HEADER

// local headers
#include "types.hpp"
#include "macro.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E N D I A N N E S S -------------------------------------------------

	class endianness final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = endianness;


			// -- public lifecycle --------------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(endianness);


			// -- public static accessors -------------------------------------

			/* is little endian */
			static consteval auto is_little(void) noexcept -> bool {
				return value == LITTLE;
			}

			/* is big endian */
			static consteval auto is_big(void) noexcept -> bool {
				return value == BIG;
			}


		private:

			// -- private enums -----------------------------------------------

			enum : xns::u32 {
				LITTLE  = 0x00'00'00'01,
				BIG     = 0x01'00'00'00,
			};

			// -- private static constants ------------------------------------

			/* value */
			static constexpr xns::u32 value = (0xFFFFFFFF & 1);


			// -- assertions --------------------------------------------------

			/* endianness is either little or big */
			static_assert(value == LITTLE || value == BIG,
					"): ENDIANNESS: unknown endianness! :(");

	};

}

#endif // ENDIANNESS_HEADER
