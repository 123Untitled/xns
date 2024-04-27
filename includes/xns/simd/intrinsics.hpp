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

#ifndef XNS_INTRINSICS_HEADER
#define XNS_INTRINSICS_HEADER

// check architecture and include appropriate header
//#if defined(__x86_64__) || defined(_M_X64) || defined(__i386) || defined(_M_IX86)
//#	include <x86intrin.h>

#if defined(__aarch64__)
#include <arm_neon.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N T R I N S I C S ---------------------------------------------------

	/* intrinsic */
	template <typename ___type>
	class intrinsic final {


		public:

		private:

	};


} // namespace xns

#endif // ARM NEON

#endif // XNS_INTRINSICS_HEADER
