#ifndef XNS_IS_ENUM_HEADER
#define XNS_IS_ENUM_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  E N U M --------------------------------------------------------

	/* is enum */
	template <class T>
	concept is_enum = __is_enum(T);


}

#endif
