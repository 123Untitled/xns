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

#ifndef XNS_INTEGER_HEADER
#define XNS_INTEGER_HEADER

// local headers
#include "xns/type_traits/types.hpp"
#include "xns/utility/numeric_limits.hpp"
#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/type_properties/is_signed.hpp"
#include "xns/type_traits/type_properties/is_unsigned.hpp"

#include "xns/integer/integer_conversion.hpp"
#include "xns/integer/integer_comparaison.hpp"
#include "xns/integer/integer_arithmetic.hpp"


#include "xns/string/string.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	// these traits need to be placed in a separate file

	template <typename T, typename U>
	using smaller = xns::conditional<(sizeof(T) < sizeof(U)), T, U>;

	template <typename T, typename U>
	using larger = xns::conditional<(sizeof(T) > sizeof(U)), T, U>;




	// -- I N T E G E R -------------------------------------------------------

	template <xns::size_t __bits, bool is_signed>
	class integer final {


		// -- friends ---------------------------------------------------------

		/* other integers as friends */
		template <xns::size_t, bool>
		friend class integer;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::integer<__bits, is_signed>;

			/* underlying type */
			using underlying = xns::conditional<is_signed, xns::sint<__bits>,
														   xns::uint<__bits>>;

			enum : underlying {
				MIN = xns::limits<underlying>::min(),
				MAX = xns::limits<underlying>::max()
			};


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr integer(void) noexcept
			: _value{static_cast<underlying>(0)} {
			}

			/* copy constructor */
			constexpr integer(const self&) noexcept = default;

			/* move constructor */
			constexpr integer(self&&) noexcept = default;

			/* natif integer constructor */
			template <xns::is_integral T>
			inline explicit constexpr integer(const T& value) noexcept
			: _value{xns::conversion<underlying>(value)} {
			}

			/* other integer constructor */
			template <xns::size_t B, bool S>
			inline explicit constexpr integer(const integer<B, S>& other) noexcept
			: _value{xns::conversion<integer<B, S>::underlying>(other._value)} {}

			/* destructor */
			~integer(void) noexcept = default;


			// -- public conversion operators ---------------------------------

			/* conversion to underlying type */
			inline constexpr explicit operator underlying(void) const noexcept {
				return _value;
			}


			// -- public accessors --------------------------------------------

			/* get value */
			inline constexpr auto get(void) const noexcept -> underlying {
				return _value;
			}

			auto print(void) const noexcept -> void {
				xns::string str = xns::to_string(_value);
				std::cout << (is_signed ? "sint" : "uint") << __bits << ": " <<
					str.data() << std::endl;
			}


			// -- public modifiers --------------------------------------------

			/* reset */
			inline constexpr auto reset(void) noexcept -> void {
				_value = static_cast<underlying>(0);
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			/* copy assignment operator */
			template <xns::size_t B, bool S> requires (B != __bits || S != is_signed)
			inline constexpr auto operator=(const xns::integer<B, S>& other) noexcept -> self& {
				_value = xns::conversion<underlying>(other._value);
				return *this;
			}

			/* move assignment operator */
			template <xns::size_t B, bool S> requires (B != __bits || S != is_signed)
			inline constexpr auto operator=(xns::integer<B, S>&& other) noexcept -> self& {
				return operator=(other);
			}

			/* natif integer assignment operator */
			template <xns::is_integral T>
			inline constexpr auto operator=(const T& value) noexcept -> self& {
				_value = xns::conversion<underlying>(value);
				return *this;
			}



			inline constexpr auto operator++(void) noexcept -> self& {
				_value += _value < MAX;
				return *this;
			}

			inline constexpr auto operator--(void) noexcept -> self& {
				_value -= _value > MIN;
				return *this;
			}

			inline constexpr auto operator++(int) noexcept -> self {
				auto tmp{*this};
				operator++();
				return tmp;
			}

			inline constexpr auto operator--(int) noexcept -> self {
				auto tmp{*this};
				operator--();
				return tmp;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			template <xns::size_t B, bool S>
			inline constexpr auto operator==(const integer<B, S>& other) const noexcept -> bool {
				return equality(_value, other._value);
			}

			/* inequality operator */
			template <xns::size_t B, bool S>
			inline constexpr auto operator!=(const integer<B, S>& other) const noexcept -> bool {
				return not equality(_value, other._value);
			}

			/* less than operator */
			template <xns::size_t B, bool S>
			inline constexpr auto operator<(const integer<B, S>& other) const noexcept -> bool {
				return less_than(_value, other._value);
			}

			/* greater than operator */
			template <xns::size_t B, bool S>
			inline constexpr auto operator>(const integer<B, S>& other) const noexcept -> bool {
				return less_than(other._value, _value);
			}

			/* less than or equal operator */
			template <xns::size_t B, bool S>
			inline constexpr auto operator<=(const integer<B, S>& other) const noexcept -> bool {
				return not less_than(other._value, _value);
			}

			/* greater than or equal operator */
			template <xns::size_t B, bool S>
			inline constexpr auto operator>=(const integer<B, S>& other) const noexcept -> bool {
				return not less_than(_value, other._value);
			}



			// -- public arithmetic operators ---------------------------------

			/* addition operator */
			template <xns::size_t B, bool S>
			inline constexpr auto operator+=(const integer<B, S>& other) const noexcept -> auto {
				return add(_value, other._value);
			}



		private:

			/******************************************************************
			 *                                                                *
			 *  E Q U A L I T Y                                               *
			 *                                                                *
			 ******************************************************************/




			/******************************************************************
			 *                                                                *
			 *  A D D I T I O N                                               *
			 *                                                                *
			 ******************************************************************/

			// -- same sign addition ------------------------------------------

			/* addition */
			template <xns::is_integral T,
					  xns::is_unsigned_integral L,
					  xns::is_unsigned_integral R>
			static inline constexpr auto add(const L& left, const R& right) noexcept -> T {
				return left > (xns::limits<T>::max() - right) ? xns::limits<T>::max()
					: left + right;
			}


		private:

			// -- private static methods --------------------------------------



			// -- private data members ----------------------------------------

			/* integer value */
			underlying _value;

	};




	// -- integer type aliases ------------------------------------------------

	using i8 = xns::integer<8, true>;
	using i16 = xns::integer<16, true>;
	using i32 = xns::integer<32, true>;
	using i64 = xns::integer<64, true>;

	using ui08 = xns::integer<8, false>;
	using ui16 = xns::integer<16, false>;
	using ui32 = xns::integer<32, false>;
	using ui64 = xns::integer<64, false>;







	// -- deduction guides ----------------------------------------------------

	//template <xns::is_integral T>
	//integer(const T&) -> integer<sizeof(T), xns::is_signed<T>>;





} // namespace xns

#endif // XNS_INTEGER_HEADER
