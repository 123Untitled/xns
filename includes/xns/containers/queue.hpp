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

#ifndef XNS_QUEUE_HEADER
#define XNS_QUEUE_HEADER

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

#include "xns/containers/list.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- Q U E U E -----------------------------------------------------------

	template <typename ___type,
			  typename ___container = std::deque<___type>>
	class queue final {


		// -- assertions ------------------------------------------------------

		/* check ___type is same as container value type */
		static_assert(xns::is_same<___type, typename ___container::value_type>,
					  "queue: type must be the same as container value type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self            = xns::queue<___type, ___container>;

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
			queue(void) noexcept(xns::is_nothrow_default_constructible<container_type>)
			: _container{} {
			}

			/* copy constructor */
			queue(const self&) noexcept(xns::is_nothrow_copy_constructible<container_type>) = default;

			/* move constructor */
			queue(self&&) noexcept(xns::is_nothrow_move_constructible<container_type>) = default;

			/* destructor */
			~queue(void) noexcept(xns::is_nothrow_destructible<container_type>) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept(xns::is_nothrow_copy_assignable<container_type>) -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept(xns::is_nothrow_move_assignable<container_type>) -> self& = default;


			// -- public accessors --------------------------------------------

			/* next */
			auto next(void) noexcept(
					noexcept(___container{}.front())
				) -> reference {
				return _container.front();
			}

			/* const next */
			auto next(void) const noexcept(
					noexcept(___container{}.front())
				) -> const_reference {
				return _container.front();
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

			/* enqueue */
			template <typename ___tp>
			auto enqueue(___tp&& ___vl) noexcept(
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

			/* dequeue */
			auto dequeue(void) noexcept(
					noexcept(___container{}.pop_front())
				) -> void {
				_container.pop_front();
			}

			/* swap */
			auto swap(self& ___ot) noexcept(
					noexcept(xns::swap(___container{}, ___ot._container))
				) -> void {
				xns::swap(_container, ___ot._container);
			}


		private:

			// -- private members --------------------------------------------

			/* container */
			container_type _container;

	}; // class queue


	// -- non-member functions ------------------------------------------------

	/* swap */
	template <typename ___type, typename ___container>
	auto swap(xns::queue<___type, ___container>& ___lhs,
			  xns::queue<___type, ___container>& ___rhs) noexcept(noexcept(___lhs.swap(___rhs))) -> void {
		___lhs.swap(___rhs);
	}

} // namespace xns

#endif // XNS_QUEUE_HEADER
