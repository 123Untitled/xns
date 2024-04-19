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

#ifndef XNS_ACCESS_HEADER
#define XNS_ACCESS_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- forward declarations ------------------------------------------------

	/* basic string */
	template <typename ___char>
	class basic_string;

	/* string */
	using string = xns::basic_string<char>;


	// -- A C C E S S ---------------------------------------------------------

	namespace access {


		/* x ok */
		static auto x_ok(const xns::string&) noexcept -> bool;

		/* r ok */
		static auto r_ok(const xns::string&) noexcept -> bool;

		/* w ok */
		static auto w_ok(const xns::string&) noexcept -> bool;

		/* f ok */
		static auto f_ok(const xns::string&) noexcept -> bool;

		/* sys x ok */
		static auto sys_x_ok(xns::string&) -> bool;

	} // namespace access

} // namespace xns

#endif // XNS_ACCESS_HEADER
