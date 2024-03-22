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

#ifndef XNS_POLICY_HEADER
#define XNS_POLICY_HEADER

#include "type_traits/type_operations/move.hpp"
#include "type_traits/type_operations/forward.hpp"
#include "type_traits/relationships_and_property_queries/is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E S T R I C T  C O N C E P T --------------------------------------

	/* locked policy */
	struct locked_t {};

	/* moveable policy */
	struct moveable_t {};

	/* copyable policy */
	struct copyable_t {};

	/* assignable policy */
	struct assignable_t {};


	/* restrict concept */
	template <class T>
	concept restrict = xns::is_same<T, assignable_t>
					|| xns::is_same<T, copyable_t>
					|| xns::is_same<T, moveable_t>
					|| xns::is_same<T, locked_t>;

	/* copyable concept */
	template <class T>
	concept copyable = xns::is_same<T, copyable_t>
					|| xns::is_same<T, assignable_t>;

	/* moveable concept */
	template <class T>
	concept moveable = xns::is_same<T, moveable_t>
					|| xns::is_same<T, assignable_t>;


	// -- S T A T I C  A S S E R T --------------------------------------------

	#define ASSERT_COPYABLE(TYPE) \
		static_assert(xns::copyable<TYPE>, "TYPE MUST BE A COPYABLE TYPE")

	#define ASSERT_MOVEABLE(TYPE) \
		static_assert(xns::moveable<TYPE>, "TYPE MUST BE A MOVEABLE TYPE")

	#define ASSERT_RESTRICT(TYPE) \
		static_assert(xns::restrict<TYPE>, "TYPE MUST BE A RESTRICT TYPE")





}


#endif
