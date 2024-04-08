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

// local headers
#include "xns/type_traits/types.hpp"
#include "xns/config/macros.hpp"
#include "xns/diagnostics/exceptions.hpp"

#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

#include "xns/type_traits/type_transformations/remove_cvref.hpp"

#include "xns/utility/numeric_limits.hpp"

#include "xns/type_traits/type_properties/is_trivially_copyable.hpp"

#include "xns/type_traits/supported_operations/is_constructible.hpp"
#include "xns/type_traits/supported_operations/is_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_destructible.hpp"
#include "xns/type_traits/supported_operations/is_trivially_destructible.hpp"
#include "xns/type_traits/supported_operations/is_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_move_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_destructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_assignable.hpp"


#include "xns/memory/addressof.hpp"

#include "xns/config/config.hpp"

// standard headers
#include <cstdlib>
#include <new>


#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L L O C A T O R ---------------------------------------------------

	template <typename T>
	class allocator final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::allocator<T>;

			/* value type */
			using value_type = T;

			/* size type */
			using size_type = xns::size_t;

			/* reference type */
			using mut_ref   = value_type&;

			/* const reference type */
			using const_ref = const value_type&;

			/* move reference type */
			using move_ref  = value_type&&;

			/* pointer type */
			using mut_ptr   = value_type*;

			/* const pointer type */
			using const_ptr = const value_type*;

			/* rebind */
			template <typename ___new>
			using rebind = xns::allocator<___new>;


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			//non_instanciable(allocator);


			// -- public static methods ---------------------------------------

			/* allocate */
			static auto allocate(const size_type size = 1) noexcept(xns::has_noexcept) -> mut_ptr {

				#if (XNS_HAS_NOEXCEPT)
					return static_cast<mut_ptr>(::malloc(size * sizeof(type)));
				#else

					// allocate memory
					mut_ptr ptr = static_cast<mut_ptr>(::malloc(size * sizeof(value_type)));

					// check failed allocation
					if (ptr == nullptr)
						throw xns::exception("allocator, failed to allocate memory", -2);

					return ptr;
				#endif
			}


			static auto allocate(const size_type size, const void*hint)
				noexcept(true)
				//noexcept(false)
				-> mut_ptr {
				return nullptr;
			}

			/* realloc */
			static auto realloc(mut_ptr addrs, const size_type size = 1) noexcept(xns::has_noexcept) -> mut_ptr {

				// check type is trivially copyable
				static_assert(xns::is_trivially_copyable<value_type>, "allocator, type is not trivially copyable");

				#if (XNS_HAS_NOEXCEPT)
					return static_cast<mut_ptr>(::realloc(addrs, size * sizeof(value_type)));
				#else

					// reallocate memory
					mut_ptr ptr = static_cast<mut_ptr>(::realloc(addrs, size * sizeof(value_type)));

					// check failed reallocation
					if (ptr == nullptr)
						throw xns::exception("allocator, failed to reallocate memory", -2);

					return ptr;
				#endif
			}

			/* deallocate */
			static auto deallocate(mut_ptr pointer) noexcept -> void {
				::free(pointer);
			}

			/* max size */
			static auto max_size(void) noexcept -> size_type {
				return size_type(~0) / sizeof(value_type);
			}


			// -- public construct methods ------------------------------------

			/* default construct */
			static auto construct(mut_ptr addrs) noexcept(xns::is_nothrow_default_constructible<value_type>) -> void {
				// assert type is default constructible
				//static_assert(xns::is_default_constructible<value_type>, "allocator, type is not default constructible");
				::new(self::voidify(*addrs)) value_type{};
			}

			/* copy construct */
			static auto construct(mut_ptr addrs, const_ref value) noexcept(xns::is_nothrow_copy_constructible<value_type>) -> void {
				// assert type is copy constructible
				//static_assert(xns::is_copy_constructible<value_type>, "allocator, type is not copy constructible");
				::new(self::voidify(*addrs)) value_type{value};
			}

			/* move construct */
			static auto construct(mut_ptr addrs, move_ref value) noexcept(xns::is_nothrow_move_constructible<value_type>) -> void {
				// assert type is move constructible
				//static_assert(xns::is_move_constructible<value_type>, "allocator, type is not move constructible");
				::new(self::voidify(*addrs)) value_type{xns::move(value)};
			}

			/* forward construct */
			template <typename... A> requires (sizeof...(A) > 1 || xns::are_not_same<value_type, xns::remove_cvref<A>...>)
			static auto construct(mut_ptr addrs, A&&... args) noexcept(xns::is_nothrow_constructible<value_type, A...>) -> void {
				// assert type is constructible
				//static_assert(xns::is_constructible<value_type, A...>, "allocator, type is not constructible with given arguments");
				::new(self::voidify(*addrs)) value_type(xns::forward<A>(args)...);
			}


			// -- public destroy methods --------------------------------------

			/* destroy */
			static auto destroy(mut_ptr addrs) noexcept(xns::is_nothrow_destructible<value_type>) -> void {
				// check type is trivially destructible
				if constexpr (xns::is_trivially_destructible<value_type> == false) {
					// check type is destructible
					static_assert(xns::is_destructible<value_type>, "allocator, type is not destructible");
					// call object destructor
					addrs->~value_type();
				}
			}


			// -- public assign methods ---------------------------------------

			/* copy assign */
			static auto assign(mut_ref dst, const_ref src) noexcept(xns::is_nothrow_copy_assignable<value_type>) -> void {
				// assert type is copy assignable
				static_assert(xns::is_copy_assignable<value_type>, "allocator, type is not copy assignable");
				dst = src;
			}

			/* move assign */
			static auto assign(mut_ref dst, move_ref src) noexcept(xns::is_nothrow_move_assignable<value_type>) -> void {
				// assert type is move assignable
				static_assert(xns::is_move_assignable<value_type>, "allocator, type is not move assignable");
				dst = xns::move(src);
			}


		private:

			// -- private static methods --------------------------------------

			/* voidify */
			template <typename U>
			static constexpr auto voidify(U& value) noexcept -> void* {
				return const_cast<void*>(static_cast<const volatile void*>(xns::addressof(value)));
			}


	}; // class allocator

} // namespace xns

#endif // XNS_ALLOCATOR_HPP
