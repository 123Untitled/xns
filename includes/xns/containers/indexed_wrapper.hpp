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

#ifndef XNS_INDEXED_WRAPPER_HEADER
#define XNS_INDEXED_WRAPPER_HEADER

//#include "xns/is_empty_base.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N D E X E D  W R A P P E R ----------------------------------------

	template <decltype(sizeof(0)), typename, bool = false>
	class indexed_wrapper;

	/* indexed wrapper */
	template <decltype(sizeof(0)) __idx, typename __type>
	class indexed_wrapper<__idx, __type, false> final {

		public:

			// -- public types ------------------------------------------------

			/* default constructor */
			inline constexpr indexed_wrapper(void) noexcept;

		private:

			/* value */
			__type _value;

	}; // indexed_wrapper

	/* indexed wrapper */
	template <decltype(sizeof(0)) __idx, typename __type>
	class indexed_wrapper<__idx, __type, true> final : public __type {

		public:

	}; // indexed_wrapper


} // namespace xns

#endif // XNS_INDEXED_WRAPPER_HEADER
