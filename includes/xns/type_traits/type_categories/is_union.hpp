/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_IS_UNION_HEADER
#define XNS_IS_UNION_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  U N I O N ------------------------------------------------------

	#if __has_builtin(__is_union)

		/* is union */
		template <typename ___type>
		concept is_union = __is_union(___type);

	#else

		#error "Compiler does not support __is_union"

	#endif

} // namespace xns

#endif // XNS_IS_UNION_HEADER
