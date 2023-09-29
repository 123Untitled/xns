#ifndef XNS_TO_REFERENCE_HEADER
#define XNS_TO_REFERENCE_HEADER

#include "remove.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T O  L V A L U E  R E F E R E N C E ---------------------------------

	/* forward lvalue helper */
	template <class T>
	using to_lvalue = xns::remove_reference<T>&;


	// -- T O  R V A L U E  R E F E R E N C E ---------------------------------

	/* forward rvalue helper */
	template <class T>
	using to_rvalue = xns::remove_reference<T>&&;



}

#endif
