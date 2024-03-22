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
#include "type_traits/types.hpp"
#include "config/macros.hpp"
#include "type_traits/type_operations/forward.hpp"
#include "diagnostics/exceptions.hpp"
#include "type_traits/type_operations/move.hpp"
#include "utility/numeric_limits.hpp"

#include "type_traits/supported_operations/supported_operations.hpp"
#include "type_traits/type_properties/type_properties.hpp"

#include "memory/addressof.hpp"

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
			using self      = xns::allocator<T>;

			/* value type */
			using type      = T;

			/* size type */
			using size_type = xns::size_t;

			/* reference type */
			using mut_ref   = T&;

			/* const reference type */
			using const_ref = const T&;

			/* move reference type */
			using move_ref  = T&&;

			/* pointer type */
			using mut_ptr   = T*;

			/* const pointer type */
			using const_ptr = const T*;


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			non_instanciable(allocator);


			// -- public static methods ---------------------------------------

			/* allocate */
			static inline auto allocate(const size_type size = 1) noexcept(xns::no_exceptions) -> mut_ptr {

				// allocate memory
				mut_ptr ptr = static_cast<mut_ptr>(::malloc(size * sizeof(type)));

				if constexpr (xns::no_exceptions == false)
					// check failed allocation
					if (ptr == nullptr)
						throw xns::exception(-2, "allocator, failed to allocate memory");

				return ptr;
			}

			/* realloc */
			static inline auto realloc(mut_ptr addrs, const size_type size = 1) noexcept(xns::no_exceptions) -> mut_ptr {

				// check type is trivially copyable
				static_assert(xns::is_trivially_copyable<type>, "allocator, type is not trivially copyable");

				// reallocate memory
				mut_ptr ptr = static_cast<mut_ptr>(::realloc(addrs, size * sizeof(type)));

				if constexpr (xns::no_exceptions == false)
					// check failed reallocation
					if (ptr == nullptr)
						throw xns::exception(-2, "allocator, failed to reallocate memory");

				return ptr;
			}

			/* deallocate */
			static inline auto deallocate(mut_ptr pointer) noexcept -> void {
				::free(pointer);
			}


			// -- public accessors --------------------------------------------

			/* max size */
			static inline consteval auto max_size(void) noexcept -> size_type {
				return xns::limits<size_type>::max() / sizeof(type);
			}


			// -- public construct methods ------------------------------------

			/* default construct */
			static inline auto construct(mut_ptr addrs) noexcept(xns::is_nothrow_default_constructible<type>) -> void {
				// assert type is default constructible
				static_assert(xns::is_default_constructible<type>, "allocator, type is not default constructible");
				::new(self::voidify(*addrs)) type{};
			}

			/* copy construct */
			static inline auto construct(mut_ptr addrs, const_ref value) noexcept(xns::is_nothrow_copy_constructible<type>) -> void {
				// assert type is copy constructible
				static_assert(xns::is_copy_constructible<type>, "allocator, type is not copy constructible");
				::new(self::voidify(*addrs)) type{value};
			}

			/* move construct */
			static inline auto construct(mut_ptr addrs, move_ref value) noexcept(xns::is_nothrow_move_constructible<type>) -> void {
				// assert type is move constructible
				static_assert(xns::is_move_constructible<type>, "allocator, type is not move constructible");
				::new(self::voidify(*addrs)) type{xns::move(value)};
			}

			/* forward construct */
			template <typename... A> requires (sizeof...(A) > 1 || xns::is_not_same<type, xns::remove_cvr<A>...>)
			static inline auto construct(mut_ptr addrs, A&&... args) noexcept(xns::is_nothrow_constructible<type, A...>) -> void {
				// assert type is constructible
				static_assert(xns::is_constructible<type, A...>, "allocator, type is not constructible with given arguments");
				::new(self::voidify(*addrs)) type{xns::forward<A>(args)...};
			}


			// -- public destroy methods --------------------------------------

			/* destroy */
			static inline auto destroy(mut_ptr addrs) noexcept(xns::is_nothrow_destructible<type>) -> void {
				// check type is trivially destructible
				if constexpr (xns::is_trivially_destructible<type> == false) {
					// check type is destructible
					static_assert(xns::is_destructible<type>, "allocator, type is not destructible");
					// call object destructor
					addrs->~type();
				}
			}


			// -- public assign methods ---------------------------------------

			/* copy assign */
			static inline auto assign(mut_ref dst, const_ref src) noexcept(xns::is_nothrow_copy_assignable<type>) -> void {
				// assert type is copy assignable
				static_assert(xns::is_copy_assignable<type>, "allocator, type is not copy assignable");
				dst = src;
			}

			/* move assign */
			static inline auto assign(mut_ref dst, move_ref src) noexcept(xns::is_nothrow_move_assignable<type>) -> void {
				// assert type is move assignable
				static_assert(xns::is_move_assignable<type>, "allocator, type is not move assignable");
				dst = xns::move(src);
			}


		private:

			// -- private static methods --------------------------------------

			/* voidify */
			template <typename U>
			static inline constexpr auto voidify(U& value) noexcept -> void* {
				return const_cast<void*>(static_cast<const volatile void*>(xns::addressof(value)));
			}


	}; // class allocator

} // namespace xns

#endif // XNS_ALLOCATOR_HPP
