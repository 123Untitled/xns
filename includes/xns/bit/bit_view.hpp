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

// local headers
#include "xns/type_traits/types.hpp"
#include "xns/bit/endianness.hpp"

#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B I T  V I E W ------------------------------------------------------

	template <typename T>
	class bit_view final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = bit_view<T>;

			/* value type */
			using type = T;

			/* reference type */
			using mut_ref = type&;

			/* storage type */
			using storage = xns::ubyte*;

			/* size type */
			using size_type = xns::size_t;


		private:

			// -- private constants -------------------------------------------

			/* number of bits in value type */
			static constexpr size_type _bits = sizeof(type) * xns::bits_per_byte;


		public:

			// -- public constructors -----------------------------------------

			/* deleted default constructor */
			constexpr bit_view(void) = delete;

			/* reference constructor */
			constexpr bit_view(mut_ref value) noexcept
			: _data{reinterpret_cast<storage>(&value)} {}

			/* copy constructor */
			constexpr bit_view(const self& other) noexcept = default;

			/* move constructor */
			constexpr bit_view(self&& other) noexcept = default;

			/* destructor */
			constexpr ~bit_view(void) noexcept = default;


			// -- public modifiers --------------------------------------------

			/* set bit */
			template <size_type N>
			inline constexpr auto set(void) noexcept -> void {
				// check if N is in range
				static_assert(N < _bits, "): BIT_VIEW: N is out of range! :(");
				// set nth bit to 1
				_data[byte_index<N>()] |= (1 << bit_index<N>());
			}

			/* toggle bit */
			template <size_type N>
			inline constexpr auto toggle(void) noexcept -> void {
				// check if N is in range
				static_assert(N < _bits, "): BIT_VIEW: N is out of range! :(");
				// toggle nth bit
				_data[byte_index<N>()] ^= (1 << bit_index<N>());
			}

			/* reset bit */
			template <size_type N>
			inline constexpr auto reset(void) noexcept -> void {
				// check if N is in range
				static_assert(N < _bits, "): BIT_VIEW: N is out of range! :(");
				// reset nth bit
				_data[byte_index<N>()] &= ~(1 << bit_index<N>());
			}



			// -- public accessors --------------------------------------------

			/* get bit count */
			static consteval size_type bits(void) noexcept {
				// return number of bits
				return _bits;
			}

			/* get bit */
			template <size_type N>
			constexpr int get(void) const noexcept {
				// check if N is in range
				static_assert(N < _bits, "): BIT_VIEW: N is out of range! :(");
				// return bit
				return (_data[byte_index<N>()] >> bit_index<N>()) & 1;
			}



			// -- public methods ----------------------------------------------

			/* print bits */
			void print(void) const noexcept {
				print_impl<_bits - 1>();
			}

			template <xns::size_t N> requires (N > 0)
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


			/* get byte index (little endian) */
			template <size_type N> requires (xns::endianness::is_little())
			static consteval auto byte_index(void) noexcept -> size_type {
				// return byte index
				return sizeof(type) - 1 - (N / xns::bits_per_byte);
			}

			/* get byte index (big endian) */
			template <size_type N> requires (xns::endianness::is_big())
			static consteval auto byte_index(void) noexcept -> size_type {
				// return byte index
				return N / xns::bits_per_byte;
			}

			/* get bit index (within byte) (little endian) */
			template <size_type N> requires (xns::endianness::is_little())
			static consteval auto bit_index(void) noexcept -> size_type {
				// return bit index
				return N % xns::bits_per_byte;
			}

			/* get bit index (within byte) (big endian) */
			template <size_type N> requires (xns::endianness::is_big())
			static consteval auto bit_index(void) noexcept -> size_type {
				// return bit index
				return xns::bits_per_byte - 1 - (N % xns::bits_per_byte);
			}




			// -- private members ---------------------------------------------

			/* storage pointer */
			storage _data;


	};


}

#endif
