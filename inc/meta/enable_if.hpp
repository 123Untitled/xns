#ifndef ENABLE_IF_HEADER
#define ENABLE_IF_HEADER

#include "integral_constant.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- E N A B L E  I F ----------------------------------------------------

	/* enable if */
	template <bool B, typename T = void>
	struct enable_if { /* empty */ };

	/* enable if for true */
	template <typename T>
	struct enable_if<true, T> { using type = T; };

	/* enable if for false */
	template <typename T>
	struct enable_if<false, T> { /* empty */ };

	/* enable if type */
	template <bool B, typename T = void>
	using enable_if_t = typename enable_if<B, T>::type;



//	/* enable if condition_t */
//	template <typename B, typename T = void>
//	struct enable_if_b { /* empty */ };
//
//	/* enable if condition_t is true */
//	template <typename T>
//	struct enable_if_b<true_t, T> { using type = T; };
//
//	/* enable if condition_t is false */
//	template <typename T>
//	struct enable_if_b<false_t, T> { /* empty */ };
//
//	/* enable if bool type */
//	template <typename B, typename T = void>
//	using enable_if_b_t = typename enable_if_b<B, T>::type;

}

#endif
