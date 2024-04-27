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

#ifndef XNS_ALLOCATOR_HEADER
#define XNS_ALLOCATOR_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"
#include "xns/diagnostics/exceptions.hpp"
#include "xns/memory/malloc.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L L O C A T O R ---------------------------------------------------

	template <typename ___type>
	class allocator final {

		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::allocator<___type>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;

			/* pointer type */
			using pointer   = value_type*;

			/* size type */
			using size_type  = xns::size_t;

			/* difference type */
			using difference_type = xns::ptrdiff_t;

			/* rebind type */
			template <typename ___other>
			using rebind = xns::allocator<___other>;



			// -- public lifecycle --------------------------------------------

			/* default constructor */
			allocator(void) noexcept = default;

			/* copy constructor */
			allocator(const ___self&) noexcept = default;

			/* move constructor */
			allocator(___self&&) noexcept = default;

			/* destructor */
			~allocator(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public methods ----------------------------------------------

			/* allocate */
			auto allocate(const size_type ___sz = 1) noexcept(false) -> pointer {
				// allocate memory
				const pointer ___ptr = xns::malloc<value_type>(___sz);

				// check failed allocation
				if (___ptr == nullptr)
					throw xns::exception("allocator, failed to allocate memory", -2);

				return ___ptr;
			}


			/* allocate hint */
			auto allocate(const size_type ___sz, const void*) noexcept(false) -> pointer {
				return allocate(___sz);
			}

			/* reallocate */
			auto reallocate(const pointer ___addr, const size_type ___sz) noexcept(false) -> pointer {

				// reallocate memory
				pointer ___p = xns::realloc<value_type>(___addr, ___sz);

				// check failed reallocation
				if (___p == nullptr)
					throw xns::exception("allocator, failed to reallocate memory", -2);

				return ___p;
			}

			/* deallocate */
			auto deallocate(const pointer ___addrs) noexcept -> void {
				xns::free<value_type>(___addrs);
			}

			/* deallocate */
			auto deallocate(const pointer ___addrs, const size_type) noexcept -> void {
				xns::free<value_type>(___addrs);
			}



	}; // class allocator

} // namespace xns

#endif // XNS_ALLOCATOR_HEADER
