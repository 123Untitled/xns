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

#ifndef XNS_THREAD_HEADER
#define XNS_THREAD_HEADER

// local headers
#include "xns/config/macros.hpp"
#include "xns/containers/tuple.hpp"
#include "xns/utility/apply.hpp"

#include "xns/type_traits/type_categories/is_function.hpp"
#include "xns/type_traits/sequences/integer_sequence.hpp"
#include "xns/memory/unique_ptr.hpp"
#include "xns/functional/invoke.hpp"

#include <pthread.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T H R E A D ---------------------------------------------------------

	class thread final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::thread;

			/* thread type */
			using thread_type = ::pthread_t;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			thread(void) noexcept;

			/* function constructor */
			template <typename F, typename... A>
			explicit thread(F&& func, A&&... args)
			: _thread{} {

				// declare tuple type
				using tuple_type = xns::tuple<std::decay_t<F>,
											  std::decay_t<A>...>;

				// allocate tuple
				auto unique = xns::make_unique<tuple_type>(xns::forward<F>(func),
														   xns::forward<A>(args)...);
				// create thread
				if (::pthread_create(&_thread,
									 nullptr,
									 thread_proxy<tuple_type>,
									 unique.get()) != 0) {
					throw;
				}

				unique.release();
			}

			/* deleted copy constructor */
			thread(const self&) = delete;

			/* move constructor */
			thread(self&&) noexcept;

			/* destructor */
			~thread(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public methods ----------------------------------------------

			/* join */
			auto join(void) noexcept -> void;

			/* detach */
			auto detach(void) noexcept -> void;

			/* swap */
			auto swap(self&) noexcept -> void;

			// -- public accessors --------------------------------------------

			/* joinable */
			auto joinable(void) const noexcept -> bool;

			/* native handle */
			auto native_handle(void) const noexcept -> const thread_type&;


			// -- public static methods ---------------------------------------

			/* hardware_concurrency */
			static auto hardware_concurrency(void) noexcept -> unsigned int;


		private:

			// -- private static methods --------------------------------------

			template <typename F, typename... A, auto... I>
			static inline auto thread_execute(xns::tuple<F, A...>& tuple,
									   xns::index_sequence<I...>) -> void {
				xns::invoke(std::move(xns::get<0>(tuple)),
							std::move(xns::get<I>(tuple))...);
			}

			/* thread proxy */
			template <typename T>
			static auto thread_proxy(void* arg) -> void* {
				// reconstruct unique pointer
				xns::unique_ptr<T> unique{static_cast<T*>(arg)};
				// execute thread
				self::thread_execute(*unique,
									// make index sequence
									xns::make_index_range<1, xns::tuple_size<T>>{});
				return nullptr;
			}


			// -- private members ---------------------------------------------

			/* thread */
			thread_type _thread;

	}; // class thread

} // namespace xns

#endif // XNS_THREAD_HEADER
