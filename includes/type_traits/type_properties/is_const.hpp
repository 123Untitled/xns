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

#ifndef XNS_IS_CONST_HEADER
#define XNS_IS_CONST_HEADER

#include "config/macros.hpp"
#include "type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O N S T ------------------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* is const */
		template <typename T>
		struct is_const final {
			constexpr static bool value = false;
			non_instanciable(is_const);
		};

		/* true specialization */
		template <typename T>
		struct is_const<const T> final {
			constexpr static bool value = true;
			non_instanciable(is_const);
		};

	}


	/* is const concept */
	template <typename T>
	concept is_const = impl::is_const<xns::remove_reference<T>>::value;


}

#endif // XNS_IS_CONST_HEADER
