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

#ifndef XNS_STACK_HEADER
#define XNS_STACK_HEADER

#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"
#include "xns/type_traits/type_operations/forward.hpp"
#include "xns/utility/swap.hpp"

#include <deque>

#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_destructible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S T A C K -----------------------------------------------------------

	template <typename ___type,
			  typename ___container = std::deque<___type>>
	class stack final {


		// -- assertions ------------------------------------------------------

		/* check ___type is same as container value type */
		static_assert(xns::is_same<___type, typename ___container::value_type>,
					  "stack: type must be the same as container value type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self            = xns::stack<___type, ___container>;

			/* container type */
			using container_type  = ___container;

			/* value type */
			using value_type      = typename container_type::value_type;

			/* size type */
			using size_type       = typename container_type::size_type;

			/* reference type */
			using reference       = typename container_type::reference;

			/* const reference type */
			using const_reference = typename container_type::const_reference;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			stack(void) noexcept(xns::is_nothrow_default_constructible<container_type>)
			: _container{} {
			}

			/* copy constructor */
			stack(const self&) noexcept(xns::is_nothrow_copy_constructible<container_type>) = default;

			/* move constructor */
			stack(self&&) noexcept(xns::is_nothrow_move_constructible<container_type>) = default;

			/* destructor */
			~stack(void) noexcept(xns::is_nothrow_destructible<container_type>) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept(xns::is_nothrow_copy_assignable<container_type>) -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept(xns::is_nothrow_move_assignable<container_type>) -> self& = default;


			// -- public accessors --------------------------------------------

			/* top */
			auto top(void) noexcept(
					noexcept(___container{}.back())
				) -> reference {
				return _container.back();
			}

			/* const top */
			auto top(void) const noexcept(
					noexcept(___container{}.back())
				) -> const_reference {
				return _container.back();
			}

			/* empty */
			auto empty(void) const noexcept(
					noexcept(___container{}.empty())
				) -> bool {
				return _container.empty();
			}

			/* size */
			auto size(void) const noexcept(
					noexcept(___container{}.size())
				) -> size_type {
				return _container.size();
			}


			// -- public modifiers --------------------------------------------

			/* push */
			template <typename ___tp>
			auto push(___tp&& ___vl) noexcept(
					noexcept(___container{}.push_back(xns::forward<___tp>(___vl)))
				) -> void {
				_container.push_back(xns::forward<___tp>(___vl));
			}

			/* emplace */
			template <typename... ___params>
			auto emplace(___params&&... ___args) noexcept(
					noexcept(___container{}.emplace_back(xns::forward<___params>(___args)...))
				) -> void {
				_container.emplace_back(xns::forward<___params>(___args)...);
			}

			/* pop */
			auto pop(void) noexcept(
					noexcept(___container{}.pop_back())
				) -> void {
				_container.pop_back();
			}

			/* swap */
			auto swap(self& ___ot) noexcept(
					noexcept(xns::swap(___container{}, ___ot._container))
				) -> void {
				xns::swap(_container, ___ot._container);
			}


		private:

			// -- private members ---------------------------------------------

			/* container */
			container_type _container;

	}; // class stack


	// -- non-member functions ------------------------------------------------

	/* swap */
	template <typename ___type, typename ___container>
	auto swap(xns::stack<___type, ___container>& ___lhs,
			  xns::stack<___type, ___container>& ___rhs) noexcept(noexcept(___lhs.swap(___rhs))) -> void {
		___lhs.swap(___rhs);
	}

} // namespace xns

#endif // XNS_STACK_HEADER
