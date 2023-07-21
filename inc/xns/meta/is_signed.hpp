#ifndef IS_SIGNED_HEADER
#define IS_SIGNED_HEADER

#include "is_integral.hpp"
#include "is_arithmetic.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace xns {


	// -- I S  S I G N E D ----------------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {


		/* is signed */
		template <class T>
		struct is_signed {


			// -- assertions --------------------------------------------------

			// check if T is an arithmetic type
			static_assert(xns::is_arithmetic<T>, "): IS_SIGNED REQUIRES AN ARITHMETIC TYPE :(");


			// -- constants ---------------------------------------------------

			/* signed */
			static constexpr bool value = static_cast<T>(-1) < static_cast<T>(0);


		};

	}

	/* is signed */
	template <class T>
	concept is_signed = impl::is_signed<T>::value;

		/*
	template <class T>
	concept is_signed = requires {
		// check if T is arithmetic
		requires xns::is_arithmetic<T>;
		// check if T is signed
		requires T(-1) < T(0);
	};*/


	// -- I S  S I G N E D  I N T E G R A L -----------------------------------

	/* is signed integral */
	template <class T>
	concept is_signed_integral = requires {
		// check if T is integral
		requires xns::is_integral<T>;
		// check if T is signed
		requires T(-1) < T(0);
	};


}

#endif
