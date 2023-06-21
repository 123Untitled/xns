#ifndef TIME_HEADER
#define TIME_HEADER

#include "macro.hpp"
#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T I M E  C L A S S --------------------------------------------------

	class time final {

		public:

			// -- public constructors -----------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(time);


			// -- public static methods ---------------------------------------

			/* get current time */
			static void now(void);


		private:

			// -- private static members --------------------------------------

			/* hours */
			static xns::u8 _h;

			/* minutes */
			static xns::u8 _m;

			/* seconds */
			static xns::u8 _s;

			/* milliseconds */
			static xns::u16 _ms;

			/* microseconds */
			static xns::u16 _us;

			/* nanoseconds */
			static xns::u16 _ns;


	};

}

#endif
