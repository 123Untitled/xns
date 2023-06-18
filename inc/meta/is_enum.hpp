#ifndef IS_ENUM_HPP
#define IS_ENUM_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  E N U M --------------------------------------------------------

	/* is enum */
	template <class T>
	concept is_enum = __is_enum(T);


}

#endif
