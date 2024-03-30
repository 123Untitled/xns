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

#ifndef XNS_DURATION_HEADER
#define XNS_DURATION_HEADER

#include "xns/config/macros.hpp"
#include "xns/type_traits/types.hpp"
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_categories/is_arithmetic.hpp"
#include "xns/math/ratio.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* forward declaration */
	template <xns::is_arithmetic, xns::is_ratio>
	class duration;


	// -- I S  D U R A T I O N ------------------------------------------------

	/* is duration */
	template <typename ___type>
	concept is_duration = xns::is_same<___type, xns::duration<typename ___type::arithmetic_type,
															  typename ___type::ratio_type>>;


	// -- D U R A T I O N -----------------------------------------------------

	template <xns::is_arithmetic ___type, xns::is_ratio ___ratio>
	class duration final {


		// -- friends ---------------------------------------------------------

		/* duration cast as friend */
		template <class U, class V>
		friend constexpr U duration_cast(const V&);

		/* other duration as friend */
		template <xns::is_arithmetic U, xns::is_ratio V>
		friend class xns::duration;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::duration<___type, ___ratio>;

			/* arithmetic type */
			using arithmetic_type = ___type;

			/* ratio type */
			using ratio_type = ___ratio;


			// -- public constructors -----------------------------------------

			/* default constructor */
			constexpr duration(void) noexcept
			: _ticks{static_cast<arithmetic_type>(0)} {
			}

			/* copy constructor */
			constexpr duration(const self&) noexcept = default;

			/* copy constructor from different duration */
			template <xns::is_duration ___dur>
			constexpr duration(const ___dur& other) noexcept
			: _ticks{other._ticks * xns::ratio_conversion_factor<ratio_type,
												typename ___dur::ratio_type>()} {

			}
			//: duration{duration_cast<self>(other)} {}

			/* move constructor */
			constexpr duration(self&&) noexcept = default;

			/* arithmetic constructor */
			constexpr duration(const arithmetic_type& _vl)
			: _ticks{_vl} {
			}

			/* destructor */
			~duration(void) noexcept = default;


			// -- public accessors --------------------------------------------

			/* count */
			inline constexpr auto count(void) const noexcept -> arithmetic_type {
				return _ticks;
			}


			// -- public incrementation operators -----------------------------

			/* pre-incrementation operator */
			constexpr inline self& operator++(void) {
				// increment ticks
				++_ticks;
				// return self reference
				return *this;
			}

			/* post-incrementation operator */
			constexpr inline self operator++(int) {
				// copy this and increment ticks
				return self{_ticks++};
			}

			/* pre-decrementation operator */
			constexpr inline self& operator--(void) {
				// decrement ticks
				--_ticks;
				// return self reference
				return *this;
			}

			/* post-decrementation operator */
			constexpr inline self operator--(int) {
				// copy this and decrement ticks
				return self{_ticks--};
			}


		private:

			// -- private members ---------------------------------------------

			/* ticks */
			arithmetic_type _ticks;

	};



	template <class T, class F>
	constexpr T duration_cast(const F& other) {

		// check if T and U are durations
		static_assert(xns::is_duration<T> && xns::is_duration<F>,
					"): TEMPLATE TYPES MUST BE DURATIONS :(");

		constexpr double factor = xns::ratio_conversion_factor<typename T::ratio_type,
															 typename F::ratio_type>();

		// NEED TO CHECK MULTIPLICATION OVERFLOW ----------------------V
		return T{static_cast<typename T::arithmetic_type>(
				other._ticks * (typename T::arithmetic_type)factor
		)};

	}


	// -- D U R A T I O N  A L I A S E S --------------------------------------

	/* nanoseconds */
	using nanoseconds  = xns::duration<xns::size_t, xns::ratio<1, 1'000'000'000>>;

	/* microseconds */
	using microseconds = xns::duration<xns::size_t, xns::ratio<1, 1'000'000>>;

	/* milliseconds */
	using milliseconds = xns::duration<xns::size_t, xns::ratio<1, 1'000>>;

	/* seconds */
	using seconds      = xns::duration<xns::size_t, xns::ratio<1, 1>>;

	/* minutes */
	using minutes      = xns::duration<xns::size_t, xns::ratio<60, 1>>;

	/* hours */
	using hours        = xns::duration<xns::size_t, xns::ratio<3600, 1>>;

	/* days */
	using days         = xns::duration<xns::size_t, xns::ratio<86400, 1>>;

	/* weeks */
	using weeks        = xns::duration<xns::size_t, xns::ratio<604800, 1>>;

	/* months */
	using months       = xns::duration<xns::size_t, xns::ratio<2629746, 1>>;

	/* years */
	using years        = xns::duration<xns::size_t, xns::ratio<31556952, 1>>;


	/* bpm */
	using bpm          = xns::duration<xns::size_t, xns::ratio<1, 60>>;



} // namespace xns

#endif // XNS_DURATION_HEADER
