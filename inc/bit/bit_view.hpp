#ifndef BITSET_HPP
#define BITSET_HPP

#include "types.hpp"
#include "array.hpp"
#include <iostream>


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


			// -- public constructors -----------------------------------------

			/* deleted default constructor */
			constexpr bit_view(void) = delete;

			/* value constructor */
			constexpr bit_view(mutable_reference value) noexcept
			: _data(value) {}

			/* copy constructor */
			constexpr bit_view(const self& other) noexcept = default;

			/* move constructor */
			constexpr bit_view(self&& other) noexcept = default;

			/* destructor */
			constexpr ~bit_view(void) noexcept = default;


			// -- public modifiers --------------------------------------------

			/* set bit */
			void set(const size_type nth) noexcept {
				// set nth bit to 1
				_data |= (1 << nth);
			}

			/* toggle bit */
			void toggle(const size_type nth) noexcept {
				// toggle nth bit
				_data ^= (1 << nth);
			}


			// -- public accessors --------------------------------------------

			/* get bit count */
			constexpr size_type count(void) const noexcept {
				// return number of bits
				return _bits;
			}

			/* get bit */
			constexpr int get(const size_type nth) const noexcept {
				// get nth bit
				return (_data >> nth) & 1;
			}


			// -- public methods ----------------------------------------------

			/* print bits */
			void print(void) const noexcept {

				xns::array<char, _bits + sizeof(value_type) - 1> buffer;

				// loop over bits
				for (size_type b = 0, o = 0; b < _bits; ++b) {

					// add space every 8 bits (except first)
					if (b % 8 == 0 && b != 0) {
						buffer[b+o] = ' ';
						++o;
					}
					// get bit
					buffer[b+o] = (char)(get(b) + '0');
				}

				write(1, buffer.data(), buffer.size());
				write(1, "\n", 1);
			}


		private:

			// -- private constants -------------------------------------------

			/* number of bits in value type */
			static constexpr size_type _bits = sizeof(value_type) * 8;


			// -- private members ---------------------------------------------

			/* value pointer */
			mutable_reference _data;


	};

}

#endif
