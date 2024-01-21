#ifndef XNS_IS_UNION_HEADER
#define XNS_IS_UNION_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  U N I O N ------------------------------------------------------

	#if __has_builtin(__is_union)

		/* is union */
		template <typename T>
		concept is_union = __is_union(T);

	#else

		#error "Compiler does not support __is_union"

	#endif

}

#endif
