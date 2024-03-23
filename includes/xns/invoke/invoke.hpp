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

#ifndef XNS_INVOKE_HPP
#define XNS_INVOKE_HPP

#include <type_traits> // temporary

#include "xns/type_traits/type_operations/forward.hpp"
#include "xns/type_traits/type_categories/is_member_pointer.hpp"
#include "xns/type_traits/type_categories/is_function.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_base_of.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- forward declarations ------------------------------------------------

	template <typename>
	class reference_wrapper;


	namespace impl {

		template <typename>
		constexpr bool is_reference_wrapper = false;

		template <typename U>
		constexpr bool is_reference_wrapper<xns::reference_wrapper<U>> = true;

	} // namespace impl

	template <typename T>
	concept is_reference_wrapper = impl::is_reference_wrapper<T>;


	// -- detail --------------------------------------------------------------

	namespace impl {


		/* invoke (member function) */
		template <typename C, typename F, typename T, typename... A>
		constexpr auto invoke(F C::* func, T&& obj, A&&... args) -> decltype(auto) {

			// only works with member functions
			static_assert(xns::is_function<F>, "invoke only works with functions");

			// base of / derived from
			if constexpr (xns::is_base_of<C, std::decay_t<T>>)
				return (xns::forward<T>(obj).*func)(xns::forward<A>(args)...);

			// reference wrapper
			else if constexpr (xns::is_reference_wrapper<std::decay_t<T>>)
				return (obj.get().*func)(xns::forward<A>(args)...);

			// pointer
			else
				return ((*xns::forward<T>(obj)).*func)(xns::forward<A>(args)...);
		}

	} // namespace impl


	/* invoke */
	template <typename F, typename... A>
	constexpr auto invoke(F&& func, A&&... args) noexcept(/* is no throw invokable */ true) -> auto { // invoke_result ...
		if constexpr (xns::is_member_pointer<std::decay_t<F>>)
			return impl::invoke(func, xns::forward<A>(args)...);
		else
			return xns::forward<F>(func)(xns::forward<A>(args)...);
	}


} // namespace xns

#endif // XNS_INVOKE_HPP
