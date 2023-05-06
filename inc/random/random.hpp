#ifndef RANDOM_HEADER
#define RANDOM_HEADER

#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "types.hpp"
#include "macro.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- R A N D O M  C L A S S ----------------------------------------------

	class Random final {

		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* size type */
			using Size = SizeT;


			// -- P U B L I C  S T A T I C  M E M B E R S ---------------------

			/* random integer */
			static Size random(const Size range);



		private:

			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			Random(void);

			/* non-assignable class */
			NON_ASSIGNABLE(Random);

			/* destructor */
			~Random(void);


			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* instance */
			static Random _instance;


	};

}


#endif
