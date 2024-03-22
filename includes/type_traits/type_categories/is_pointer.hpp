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

#ifndef XNS_IS_POINTER_HEADER
#define XNS_IS_POINTER_HEADER

#include "type_traits/type_trait_constants/integral_constant.hpp"
#include "type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  P O I N T E R --------------------------------------------------


	namespace __impl {

		/* is pointer */
		template <typename __type>
		struct is_pointer          : public xns::false_type {};

		/* specialisation */
		template <typename __type>
		struct is_pointer<__type*> : public xns::true_type {};

		/* helper */
		template<typename __type>
		struct is_pointer_helper   : public __impl::is_pointer<xns::remove_cv<__type>> {};

	}

	/* is pointer */
	template<typename __type>
	concept is_pointer = xns::__impl::is_pointer_helper<__type>::value;

} // namespace xns

#endif // XNS_IS_POINTER_HEADER
