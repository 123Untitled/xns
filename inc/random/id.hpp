#ifndef ID_HEADER
#define ID_HEADER

#include "types.hpp"
#include "macro.hpp"
#include "string.hpp"
#include "array.hpp"

#include <string>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I D  C L A S S ------------------------------------------------------

	class Id final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* string type */
			using String = std::string;


			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(Id);


			// -- M E T H O D S -----------------------------------------------

			static String generate(void);


		private:

			// -- A L I A S E S -----------------------------------------------

			/* character type */
			using Char = char;

			/* array type */
			template <UInt64 N>
			using Array = Xf::Array<const Char*, N>;



			// -- E N U M S ---------------------------------------------------

			enum {
				IDNBR      = 4,
				ALPHA_COMB = 650,
				DIGIT_COMB = 100
			};


			// -- M E M B E R S -----------------------------------------------

			/* alpha combinations */
			static constinit Array<ALPHA_COMB> _alpha;

			/* digit combinations */
			static constinit Array<DIGIT_COMB> _digit;

			/* alpha combinations */
			//static constexpr Char* _alpha[ALPHA_COMB];

			/* digit combinations */
			//static const Char* _digit[DIGIT_COMB];

	};

};

#endif
