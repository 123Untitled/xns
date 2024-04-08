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

#ifndef XNS_TYPE_IDENTITY_HEADER
#define XNS_TYPE_IDENTITY_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T Y P E  I D E N T I T Y --------------------------------------------

	namespace ___impl {


		/* type identity */
		template <typename ___type>
		struct ___type_identity {
			using type = ___type;
		};

	} // namespace ___impl


	/* type identity */
	template <typename ___type>
	using identity = typename xns::___impl::___type_identity<___type>::type;

} // namespace xns

#endif // XNS_TYPE_IDENTITY_HEADER
