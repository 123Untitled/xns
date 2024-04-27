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

#ifndef XNS_BIT_VIEW_HEADER
#define XNS_BIT_VIEW_HEADER

#include "xns/bit/endianness.hpp"
#include "xns/type_traits/types.hpp"
#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B I T  V I E W ------------------------------------------------------

	template <typename ___type>
	class bit_view final {


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;

			/* reference type */
			using reference = value_type&;

			/* size type */
			using size_type = decltype(sizeof(0));


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::bit_view<___type>;

			/* storage type */
			using ___storage = unsigned char*;


			// -- private constants -------------------------------------------

			/* number of bits in value type */
			enum : size_type {
				_bits = sizeof(value_type) * xns::bits_per_byte
			};


		public:

			// -- public constructors -----------------------------------------

			/* deleted default constructor */
			constexpr bit_view(void) = delete;

			/* reference constructor */
			constexpr bit_view(reference ___vl) noexcept
			: _data{reinterpret_cast<___storage>(&___vl)} {
			}

			/* copy constructor */
			constexpr bit_view(const ___self&) noexcept = default;

			/* move constructor */
			constexpr bit_view(___self&&) noexcept = default;

			/* destructor */
			constexpr ~bit_view(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			constexpr auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public modifiers --------------------------------------------

			/* set */
			template <size_type ___bit>
			constexpr auto set(void) noexcept -> void {

				// check if bit is in range
				static_assert(___bit < _bits, "bit_view: bit is out of range.");

				// set nth bit to 1
				_data[___self::_byte_index<___bit>()] |= (1U << ___self::_bit_index<___bit>());
			}

			/* toggle */
			template <size_type ___bit>
			constexpr auto toggle(void) noexcept -> void {

				// check if bit is in range
				static_assert(___bit < _bits, "bit_view: bit is out of range.");

				// toggle nth bit
				_data[___self::_byte_index<___bit>()] ^= (1U << ___self::_bit_index<___bit>());
			}

			/* reset */
			template <size_type ___bit>
			constexpr auto reset(void) noexcept -> void {

				// check if bit is in range
				static_assert(___bit < _bits, "bit_view: bit is out of range.");

				// reset nth bit
				_data[___self::_byte_index<___bit>()] &=
					static_cast<ubyte>(~(1U << ___self::_bit_index<___bit>()));
			}


			// -- public accessors --------------------------------------------

			/* get bit count */
			static consteval size_type bits(void) noexcept {
				return _bits;
			}

			/* get */
			template <size_type ___bit>
			constexpr auto get(void) const noexcept -> ubyte {

				// check if bit is in range
				static_assert(___bit < _bits, "bit_view: bit is out of range.");

				// return bit
				return 1U & (_data[_byte_index<___bit>()] >> _bit_index<___bit>());
			}



			// -- public methods ----------------------------------------------

			/* print bits */
			void print(void) const noexcept {
				print_impl<_bits - 1>();
			}


			template <size_type N> requires (N > 0)
			void print_impl(void) const noexcept {


				if (get<N>()) {
					::write(1, "\x1b[34m1\x1b[0m", 10);
				} else {
					::write(1, "0", 1);
				}

				if constexpr ((N % xns::bits_per_byte == 0) && (N != 0)) {
					write(1, " ", 1);
				}

				if constexpr ((N % (xns::bits_per_byte * sizeof(void*)) == 0) && (N != 0)) {
					write(1, "\n", 1);
				}

				print_impl<N - 1>();
			}


			template <xns::size_t N> requires (N == 0)
			void print_impl(void) const noexcept {
				if (get<0>()) {
					::write(1, "\x1b[34m1\x1b[0m\n", 11);
					return; }
				::write(1, "0\n", 2);
			}



		private:

			// -- private methods ---------------------------------------------

			/* byte index */
			template <size_type ___bit>
			static consteval auto _byte_index(void) noexcept -> size_type {

				// little endian
				if      constexpr (xns::endianness::is_little())
					return (sizeof(value_type) - 1U) - (___bit / xns::bits_per_byte);

				// big endian
				else if constexpr (xns::endianness::is_big())
					return ___bit / xns::bits_per_byte;
			}

			/* bit index */
			template <size_type ___bit>
			static consteval auto _bit_index(void) noexcept -> size_type {

				// big endian
				if      constexpr (xns::endianness::is_big())
					return (xns::bits_per_byte - 1U) - ___bit;

				// little endian
				else if constexpr (xns::endianness::is_little())
					return ___bit;
			}


			// -- private members ---------------------------------------------

			/* storage pointer */
			___storage _data;

	}; // class bit_view

} // namespace xns

#endif // XNS_BIT_VIEW_HEADER
