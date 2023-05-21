#ifndef RANDOM_HEADER
#define RANDOM_HEADER

#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "types.hpp"
#include "macro.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R A N D O M  C L A S S ----------------------------------------------

	class random final {

		public:

			// -- T Y P E S ---------------------------------------------------

			/* size type */
			using size_type = xns::size_t;


			// -- S T A T I C  M E T H O D S ----------------------------------

			/* random integer */
			static size_type random_gen(const size_type range);


		private:

			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			random(void);

			/* non-assignable class */
			NON_ASSIGNABLE(random);

			/* destructor */
			~random(void);


			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* instance */
			static random _instance;


	};

}


#endif
