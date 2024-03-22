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

#ifndef XNS_IS_LVALUE_REFERENCE_HEADER
#define XNS_IS_LVALUE_REFERENCE_HEADER

#include "type_traits/type_trait_constants/integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {

		/* is lvalue reference */
		template <class T>
		struct is_lvalue_reference      : public xns::false_type {};

		/* specialisation */
		template <class T>
		struct is_lvalue_reference<T&>  : public xns::true_type  {};

		/* is rvalue reference */
		template <class T>
		struct is_rvalue_reference      : public xns::false_type {};

		/* specialisation */
		template <class T>
		struct is_rvalue_reference<T&&> : public xns::true_type  {};

	}


	// -- I S  L V A L U E  R E F E R E N C E ---------------------------------

	/* is lvalue concept */
	template <class T>
	concept is_lvalue = impl::is_lvalue_reference<T>::value;


	// -- I S  R V A L U E  R E F E R E N C E ---------------------------------

	/* is rvalue concept */
	template <class T>
	concept is_rvalue = impl::is_rvalue_reference<T>::value;


	// -- I S  R E F E R E N C E ----------------------------------------------

	/* is reference concept */
	template <class T>
	concept is_reference = is_lvalue<T> || is_rvalue<T>;


}


#endif
