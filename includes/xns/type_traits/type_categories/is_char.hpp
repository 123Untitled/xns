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

#ifndef XNS_IS_CHAR_HEADER
#define XNS_IS_CHAR_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/type_traits/type_modifications/remove_cv.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C H A R  -------------------------------------------------------

	namespace ___impl {


		/* is char */
		template <typename>
		struct ___is_char : public xns::false_type {
			___xns_not_instantiable(___is_char);
		};

		/* char specialisation */
		template <>
		struct ___is_char<char> : public xns::true_type {
			___xns_not_instantiable(___is_char);
		};

		/* char8_t specialisation */
		template <>
		struct ___is_char<char8_t> : public xns::true_type {
			___xns_not_instantiable(___is_char);
		};

		/* char16_t specialisation */
		template <>
		struct ___is_char<char16_t> : public xns::true_type {
			___xns_not_instantiable(___is_char);
		};

		/* char32_t specialisation */
		template <>
		struct ___is_char<char32_t> : public xns::true_type {
			___xns_not_instantiable(___is_char);
		};

		/* wchar_t specialisation */
		template <>
		struct ___is_char<wchar_t> : public xns::true_type {
			___xns_not_instantiable(___is_char);
		};

		/* helper */
		template<typename ___type>
		struct ___is_char_helper final : public ___impl::___is_char<xns::remove_cv<___type>> {
			___xns_not_instantiable(___is_char_helper);
		};

	} // namespace ___impl


	/* is char */
	template <typename ___type>
	concept is_char = ___impl::___is_char_helper<___type>::value;


} // namespace xns

#endif // XNS_IS_CHAR_HEADER
