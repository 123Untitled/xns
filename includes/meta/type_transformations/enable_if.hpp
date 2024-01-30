/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_ENABLE_IF_HPP
#define XNS_ENABLE_IF_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E N A B L E  I F ----------------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		/* enable if */
		template <bool, typename>
		struct enable_if;

		/* true specialization */
		template <typename T>
		struct enable_if<true, T> final { using type = T; };

		/* false specialization */
		template <typename T>
		struct enable_if<false, T> final {};

	} // namespace impl


	/* enable if type */
	template <bool B, typename T = void>
	using enable_if = typename impl::enable_if<B, T>::type;


} // namespace xns

#endif // XNS_ENABLE_IF_HPP
