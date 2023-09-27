#ifndef FIXED_HPP_INCLUDED
#define FIXED_HPP_INCLUDED

#include "move.hpp"
#include "is_integral.hpp"
#include "is_floating.hpp"
#include "types.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I X E D -----------------------------------------------------------

	template <class T, xns::ubyte N>
	class fixed final {

		// -- assertions ------------------------------------------------------

		// check T is an integral type
		static_assert(xns::is_integral<T>, "): T MUST BE AN INTEGRAL TYPE :(");


		private:

			// -- private constants -------------------------------------------

			/* fractional bits */
			static constexpr xns::ubyte _fractional_bits = N;

			/* integral bits */
			static constexpr xns::ubyte _integral_bits = sizeof(T) * 8 - _fractional_bits;


		public:

			// -- public types ------------------------------------------------

			/* integral type */
			using value_type = T;

			/* self type */
			using self = fixed<T, N>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			constexpr fixed(void) noexcept
			: _data{0} {}

			/* copy constructor */
			constexpr fixed(const self& other) noexcept
			: _data{other._data} {}

			/* move constructor */
			constexpr fixed(self&& other) noexcept
			: _data{xns::move(other._data)} {}

			/* integral constructor */
			template <xns::is_integral U>
			constexpr fixed(const U& value) noexcept
			: _data{static_cast<value_type>(value << _fractional_bits)} {
				// check if the integral bits are enough to store the value
				static_assert(_check_integral_size<U>(), "): VALUE IS TOO LARGE :(");
			}

			/* floating point constructor */
			/*template <xns::is_floating U>
			constexpr fixed(const U& value) noexcept
			{
				value_type integral = static_cast<value_type>(value);
				U val = value - integral;
				std::cout << "integral: " << integral << std::endl;
				std::cout << "fractional: " << val << std::endl;

				value_type fractional = static_cast<value_type>(val * (1 << _fractional_bits));

				_data = (integral << _fractional_bits) | fractional;
			}*/



			// -- public conversion operators ---------------------------------

			/* integral conversion operator */
			/*
			template <xns::is_integral U>
			constexpr operator U(void) const noexcept {
				// return the integral value
				return static_cast<U>(_data >> _fractional_bits);
			}*/


			friend std::ostream& operator<<(std::ostream& os, const self& fixed) {
				T integral = fixed._data >> _fractional_bits;
				T fractional = fixed._data & ((1 << _fractional_bits) - 1);

				os << integral << "." << fractional;
				// return the stream
				return os;
			}



		private:


			// -- private static methods --------------------------------------

			/* check integral size */
			template <xns::is_integral U>
			static consteval bool _check_integral_size(void) noexcept {
				// check if the integral bits are enough to store the value
				return ((sizeof(U) * 8) - _fractional_bits) <= _integral_bits;
			}


			// -- private members ---------------------------------------------

			/* data */
			value_type _data;



	};

}

#endif

