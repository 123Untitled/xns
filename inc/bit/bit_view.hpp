#ifndef BITSET_HPP
#define BITSET_HPP

// local headers
#include "types.hpp"
#include "array.hpp"
#include "endianness.hpp"
#include "integer_sequence.hpp"

#include <iostream>
#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B I T  V I E W ------------------------------------------------------

	template <class T>
	class bit_view final {



		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = bit_view<T>;

			/* value type */
			using value_type = T;

			/* storage type */
			using storage = xns::ubyte*;

			/* pointer type */
			using mutable_pointer = value_type*;

			/* reference type */
			using mutable_reference = value_type&;

			/* const pointer type */
			using const_pointer = const value_type*;

			/* const reference type */
			using const_reference = const value_type&;

			/* size type */
			using size_type = xns::size_t;


		private:

			// -- private constants -------------------------------------------

			/* number of bits in value type */
			static constexpr size_type _bits = sizeof(value_type) * XNS_CHAR_BIT;


		public:

			// -- public constructors -----------------------------------------

			/* deleted default constructor */
			constexpr bit_view(void) = delete;

			/* reference constructor */
			constexpr bit_view(mutable_reference value) noexcept
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
			consteval size_type bits(void) const noexcept {
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
				if constexpr ((N % XNS_CHAR_BIT == 0) && (N != 0)) {
					write(1, " ", 1);
				}

				int bit = get<N>();
				if (bit) {
					write(1, "1", 1);
				} else {
					write(1, "0", 1);
				}

				print_impl<N - 1>();
			}

			template <xns::size_t N> requires (N == 0)
			void print_impl(void) const noexcept {
				int bit = get<0>();
				if (bit) {
					write(1, "1", 1);
				} else {
					write(1, "0", 1);
				}

				write(1, "\n", 1);
			}






		private:

			// -- private methods ---------------------------------------------


			/* get byte index (little endian) */
			template <size_type N> requires (xns::endianness::is_little())
			static consteval auto byte_index(void) noexcept -> size_type {
				return sizeof(value_type) - 1 - (N / XNS_CHAR_BIT);
				// return byte index
				return N / XNS_CHAR_BIT;
			}

			/* get bit index (within byte) (little endian) */
			template <size_type N> requires (xns::endianness::is_little())
			static consteval auto bit_index(void) noexcept -> size_type {
				return XNS_CHAR_BIT - 1 - (N % XNS_CHAR_BIT);
				// return bit index
				return N % XNS_CHAR_BIT;
			}

			/* get byte index (big endian) */
			template <size_type N> requires (xns::endianness::is_big())
			static consteval auto byte_index(void) noexcept -> size_type {
				// return byte index
				return sizeof(value_type) - 1 - (N / XNS_CHAR_BIT);
			}

			/* get bit index (within byte) (big endian) */
			template <size_type N> requires (xns::endianness::is_big())
			static consteval auto bit_index(void) noexcept -> size_type {
				// return bit index
				return XNS_CHAR_BIT - 1 - (N % XNS_CHAR_BIT);
			}




			// -- private members ---------------------------------------------

			/* storage pointer */
			storage _data;


	};


}

#endif
