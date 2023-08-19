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
				return value == endian::LITTLE;
			}

			/* is big endian */
			static consteval auto is_big(void) noexcept -> bool {
				return value == endian::BIG;
			}

			/* is unknown endian */
			static consteval auto is_unknown(void) noexcept -> bool {
				return value == endian::UNKNOWN;
			}


		private:

			// -- private enums -----------------------------------------------

			enum endian : xns::u32 {
				LITTLE  = 0x00'00'00'01,
				BIG     = 0x01'00'00'00,
				UNKNOWN = 0xFF'FF'FF'FF
			};


			// -- implementation ----------------------------------------------

			/* forward declaration */
			template <xns::u32>
			struct impl;

			/* little specialization */
			template <>
			struct impl<endian::LITTLE> {
				static constexpr auto value = endian::LITTLE;
			};

			/* big specialization */
			template <>
			struct impl<endian::BIG> {
				static constexpr auto value = endian::BIG;
			};


			// -- private static constants ------------------------------------

			/* value */
			static constexpr endian value = impl<(0xFFFFFFFF & 1)>::value;


			// -- assertions --------------------------------------------------

			/* endianness is either little or big */
			static_assert(value != endian::UNKNOWN, "): ENDIANNESS: unknown endianness! :(");

	};

}

#endif // ENDIANNESS_HEADER
