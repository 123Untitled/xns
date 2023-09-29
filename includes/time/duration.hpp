#ifndef DURATION_HEADER
#define DURATION_HEADER

#include "macros.hpp"
#include "types.hpp"
#include "move.hpp"
#include "is_arithmetic.hpp"
#include "ratio.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* forward declaration */
	template <xns::is_arithmetic, xns::is_ratio>
	class duration;


	// -- I S  D U R A T I O N ------------------------------------------------

	/* is duration concept */
	template <class T>
	concept is_duration = xns::is_same<T, xns::duration<typename T::arithmetic_type,
														typename T::ratio_type>>;


	// -- D U R A T I O N  C L A S S --------------------------------------------

	template <xns::is_arithmetic T, xns::is_ratio R>
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
			using self = xns::duration<T, R>;

			/* arithmetic type */
			using arithmetic_type = T;

			/* ratio type */
			using ratio_type = R;


			// -- public constructors -----------------------------------------

			/* default constructor */
			constexpr duration(void)
			: _ticks{0} {}

			/* copy constructor */
			constexpr duration(const self& other)
			: _ticks{other._ticks} {}

			/* copy constructor from different duration */
			template <xns::is_duration U>
			constexpr duration(const U& other)
			: _ticks{other._ticks * xns::ratio_conversion_factor<ratio_type,
														typename U::ratio_type>()} {}
			//: duration{duration_cast<self>(other)} {}

			/* move constructor */
			constexpr duration(self&& other)
			: _ticks{xns::move(other._ticks)} {}

			/* constructor from arithmetic type */
			constexpr duration(const arithmetic_type& value)
			: _ticks{value} {}

			/* destructor */
			~duration(void) {}


			// -- public accessors --------------------------------------------

			/* count */
			constexpr inline arithmetic_type count(void) const {
				// return ticks
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
	using nanoseconds  = xns::duration<xns::umax, xns::ratio<1, 1'000'000'000>>;

	/* microseconds */
	using microseconds = xns::duration<xns::umax, xns::ratio<1, 1'000'000>>;

	/* milliseconds */
	using milliseconds = xns::duration<xns::umax, xns::ratio<1, 1'000>>;

	/* seconds */
	using seconds      = xns::duration<xns::umax, xns::ratio<1, 1>>;

	/* minutes */
	using minutes      = xns::duration<xns::umax, xns::ratio<60, 1>>;

	/* hours */
	using hours        = xns::duration<xns::umax, xns::ratio<3600, 1>>;

	/* days */
	using days         = xns::duration<xns::umax, xns::ratio<86400, 1>>;

	/* weeks */
	using weeks        = xns::duration<xns::umax, xns::ratio<604800, 1>>;

	/* months */
	using months       = xns::duration<xns::umax, xns::ratio<2629746, 1>>;

	/* years */
	using years        = xns::duration<xns::umax, xns::ratio<31556952, 1>>;



}

#endif
