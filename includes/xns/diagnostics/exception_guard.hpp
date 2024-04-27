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

#ifndef XNS_EXCEPTION_GUARD_HEADER
#define XNS_EXCEPTION_GUARD_HEADER

#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <typename ___rollback>
	class exception_guard {


		// -- assertions ------------------------------------------------------

		/* require nothrow move constructible */
		static_assert(xns::is_nothrow_move_constructible<___rollback>,
			"rollback must be nothrow move constructible");


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::exception_guard<___rollback>;


		public:



			// -- public types ------------------------------------------------


			/* deleted default constructor */
			exception_guard(void) = delete;


			/* rollback constructor */
			#if XNS_HAS_EXCEPTIONS
			constexpr explicit exception_guard(___rollback&& ___roll) noexcept
			: _rollback{xns::move(___roll)}, _completed{false} {
			}

			#else
			constexpr explicit exception_guard(___rollback) noexcept {
			}
			//: _completed{false} {}
			#endif


			/* deleted copy constructor */
			exception_guard(const ___self&) = delete;


			/* move constructor */
			#if XNS_HAS_EXCEPTIONS
			constexpr exception_guard(___self&& ___ot) noexcept
			: _rollback{xns::move(___ot._rollback)}, _completed{___ot._completed} {
				___ot._completed = true;
			}
			#else
			constexpr exception_guard(___self&& ___ot) noexcept
			: _completed{___ot._completed} {
				___ot._completed = true;
			}
			#endif

			/* destructor */
			#if XNS_HAS_EXCEPTIONS
			constexpr ~exception_guard(void) noexcept {
				if (not _completed)
					_rollback(); }
			#else
			constexpr ~exception_guard(void) noexcept {
				static_assert(_completed, "exception_guard not completed with exceptions disabled");
			}
			#endif


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment */
			auto operator=(___self&&) -> ___self& = delete;


			// -- public methods ----------------------------------------------

			/* complete */
			constexpr auto complete(void) noexcept -> void {
				_completed = true;
			}


		private:

			// -- private members ---------------------------------------------

			/* rollback */
			#if XNS_HAS_EXCEPTIONS
			___rollback _rollback;
			#endif

			/* completed */
			bool _completed;

	}; // class exception_guard


	// -- non-member functions ------------------------------------------------

	/* make exception guard */
	template <typename ___rollback>
	constexpr auto make_exception_guard(___rollback&& ___roll) noexcept -> xns::exception_guard<___rollback> {
		return xns::exception_guard<___rollback>{xns::move(___roll)};
	}

} // namespace xns

#endif // XNS_EXCEPTION_GUARD_HEADER

