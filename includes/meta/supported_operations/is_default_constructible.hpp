/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#ifndef IS_DEFAULT_CONSTRUCTIBLE_HPP
#define IS_DEFAULT_CONSTRUCTIBLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E F A U L T  C O N S T R U C T I B L E -----------------------

	/* is default constructible */
	template <typename T>
	concept is_default_constructible = __is_constructible(T);

	/* are default constructible */
	template <typename... T>
	concept are_default_constructible = (xns::is_default_constructible<T> && ...);

} // namespace xns

#endif // IS_DEFAULT_CONSTRUCTIBLE_HPP

