#ifndef XNS_TIME_HEADER
#define XNS_TIME_HEADER

// local headers
#include "types.hpp"
#include "macros.hpp"
#include "os.hpp"


// operating system headers
#if defined(XNS_APPLE)
# include <mach/mach_time.h>
#elif defined(XNS_LINUX) || defined(XNS_BSD)
# include <sys/time.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T I M E  C L A S S --------------------------------------------------

	class time final {


		public:


			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::time;

			/* size type */
			using size_type = xns::size_t;


			// -- public static methods ---------------------------------------

			#if defined(XNS_APPLE)

			/* get current time */
			static auto now(void) -> xns::size_t {
				return ::mach_absolute_time()
					* shared()._abs_to_nano;
			}


			#elif defined(XNS_LINUX) || defined(XNS_BSD)

			/* get current time */
			static auto now(void) -> xns::size_t {

				struct ::timespec ts;
				::clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
				return (static_cast<xns::size_t>(ts.tv_sec) * 1'000'000'000U)
					+ ts.tv_nsec;
			}

			#endif


		private:

			// -- private lifecycle -------------------------------------------

			#if defined(XNS_APPLE)

			/* default constructor */
			inline time(void) noexcept
			: _abs_to_nano{0.0}, _nano_to_abs{0.0} {

				// declare timebase info
				::mach_timebase_info_data_t timebase;
				// get timebase info
				::mach_timebase_info(&timebase);

				// absolute clock to nanoseconds
				_abs_to_nano = static_cast<xns::f64>(timebase.numer)
							/ static_cast<xns::f64>(timebase.denom);

				// nanoseconds to absolute clock
				_nano_to_abs = static_cast<xns::f64>(timebase.denom)
							/ static_cast<xns::f64>(timebase.numer);

			}

			#elif defined(XNS_LINUX) || defined(XNS_BSD)

			/* default constructor */
			inline time(void) noexcept = default;

			#endif

			/* non-assignable class */
			NON_ASSIGNABLE(time);

			/* destructor */
			inline ~time(void) noexcept = default;


			// -- private static methods --------------------------------------

			/* get instance */
			static inline auto shared(void) noexcept -> self& {
				static xns::time instance;
				return instance;
			}


			// -- private members ---------------------------------------------

			#if defined(XNS_APPLE)

			/* absolute clock to nanoseconds */
			xns::f64 _abs_to_nano;

			/* nanoseconds to absolute clock */
			xns::f64 _nano_to_abs;


			#endif

	};

}

#endif
