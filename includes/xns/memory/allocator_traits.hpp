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

#ifndef XNS_ALLOCATOR_TRAITS_HEADER
#define XNS_ALLOCATOR_TRAITS_HEADER

#include "xns/memory/pointer_traits.hpp"

#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/type_modifications/make_unsigned.hpp"
#include "xns/type_traits/type_properties/is_empty.hpp"

#include "xns/type_traits/type_properties/have_member_types.hpp"

#include "xns/type_traits/type_transformations/lazy_conditional.hpp"
#include "xns/type_traits/type_transformations/remove_cvref.hpp"

#include "xns/utility/numeric_limits.hpp"

#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

#include "xns/type_traits/supported_operations/is_constructible.hpp"
#include "xns/type_traits/supported_operations/is_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_move_constructible.hpp"

#include "xns/type_traits/supported_operations/is_destructible.hpp"
#include "xns/type_traits/supported_operations/is_trivially_destructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_destructible.hpp"

#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L L O C A T O R  T R A I T S --------------------------------------

	/* allocator traits */
	template <typename ___alloc>
	class allocator_traits final {


		// -- assertions ------------------------------------------------------

		/* requires value type */
		static_assert(requires { typename ___alloc::value_type; },
				"allocator_traits, allocator must have a value_type member type");

		/* requires allocate and deallocate */
		static_assert(requires {
			___alloc{}.allocate(0);
			___alloc{}.deallocate(nullptr);
			}, "allocator_traits, type does not meet allocator requirements");

		/* requires nothrow deallocate */
		static_assert(noexcept(___alloc{}.deallocate(nullptr)),
					  "list: allocator must be nothrow deallocate");


		private:

			// -- private types -----------------------------------------------

			/* ___pointer */
			template <typename ___a>
			using ___pointer
			= typename ___a::pointer;

			/* ___const_pointer */
			template <typename ___a>
			using ___const_pointer
			= typename ___a::const_pointer;

			/* ___void_pointer */
			template <typename ___a>
			using ___void_pointer
			= typename ___a::void_pointer;

			/* ___const_void_pointer */
			template <typename ___a>
			using ___const_void_pointer 
			= typename ___a::const_void_pointer;

			/* ___difference_type */
			template <typename ___a>
			using ___difference_type 
			= typename ___a::difference_type;

			/* ___size_type */
			template <typename ___a>
			using ___size_type 
			= typename ___a::size_type;

			/* ___propagate_on_container_copy_assignment */
			template <typename ___a>
			using ___propagate_on_container_copy_assignment 
			= typename ___a::propagate_on_container_copy_assignment;

			/* ___propagate_on_container_move_assignment */
			template <typename ___a>
			using ___propagate_on_container_move_assignment 
			= typename ___a::propagate_on_container_move_assignment;

			/* ___propagate_on_container_swap */
			template <typename ___a>
			using ___propagate_on_container_swap 
			= typename ___a::propagate_on_container_swap;

			/* ___is_always_equal */
			template <typename ___a>
			using ___is_always_equal
			= typename ___a::is_always_equal;

			/* ___rebind */
			template <typename ___a, typename ___new>
			using ___rebind = typename ___a::template rebind<___new>;

			/* ___rebind_alloc */
			template <typename, typename>
			struct ___rebind_alloc;

			/* ___rebind_alloc specialisation */
			template <template <typename, typename...>
					  typename ___wrapper, typename ___type, typename ...___params, typename ___new>
			struct ___rebind_alloc<___wrapper<___type, ___params...>, ___new> {
				static_assert(xns::is_same<___new, typename ___wrapper<___new, ___params...>::value_type>,
						"allocator_traits, cannot deduce rebind type, allocator must implement rebind");
				using other = ___wrapper<___new, ___params...>;
			};


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self
				= xns::allocator_traits<___alloc>;

			/* allocator type */
			using allocator_type
				= ___alloc;

			/* value type */
			using value_type
				= typename ___alloc::value_type;

			/* pointer type */
			using pointer
				= xns::lazy_conditional<xns::have_pointer<___alloc>,
										value_type*,
										___pointer, ___alloc>;

			/* const pointer type */
			using const_pointer
				= xns::lazy_conditional<xns::have_const_pointer<___alloc>,
										typename xns::pointer_traits<pointer>::template rebind<const value_type>,
										___const_pointer, ___alloc>;

			/* void pointer type */
			using void_pointer
				= xns::lazy_conditional<xns::have_void_pointer<___alloc>,
										typename xns::pointer_traits<pointer>::template rebind<void>,
										___void_pointer, ___alloc>;

			/* const void pointer type */
			using const_void_pointer
				= xns::lazy_conditional<xns::have_const_void_pointer<___alloc>,
										const void*,
										//typename xns::pointer_traits<pointer>::template rebind<const void>,
										___const_void_pointer, ___alloc>;

			/* difference type */
			using difference_type
				= xns::lazy_conditional<xns::have_difference_type<___alloc>,
										typename xns::pointer_traits<pointer>::difference_type,
										___difference_type, ___alloc>;

			/* size type */
			using size_type
				= xns::lazy_conditional<xns::have_size_type<___alloc>,
										xns::make_unsigned<difference_type>,
										___size_type, ___alloc>;

			/* propagate on container copy assignment */
			using propagate_on_container_copy_assignment
				= xns::lazy_conditional<xns::have_propagate_on_container_copy_assignment<___alloc>,
										xns::false_type,
										___propagate_on_container_copy_assignment, ___alloc>;

			/* propagate on container move assignment */
			using propagate_on_container_move_assignment
				= xns::lazy_conditional<xns::have_propagate_on_container_move_assignment<___alloc>,
										xns::false_type,
										___propagate_on_container_move_assignment, ___alloc>;

			/* propagate on container swap */
			using propagate_on_container_swap
				= xns::lazy_conditional<xns::have_propagate_on_container_swap<___alloc>,
										xns::false_type,
										___propagate_on_container_swap, ___alloc>;

			/* is always equal */
			using is_always_equal
				= xns::lazy_conditional<xns::have_is_always_equal<___alloc>,
										xns::conditional<xns::is_empty<___alloc>, xns::true_type, xns::false_type>,
										___is_always_equal, ___alloc>;

			/* rebind alloc */
			template <typename ___type>
			using rebind_alloc
				= xns::lazy_conditional<xns::have_rebind<___alloc>,
										typename ___rebind_alloc<___alloc, ___type>::other,
										___rebind, ___alloc, ___type>;

			/* rebind traits */
			template <typename __type>
			using rebind_traits = xns::allocator_traits<rebind_alloc<__type>>;


		private:

			// -- private constants -------------------------------------------

			/* max size */
			enum : size_type {
				___max_size = xns::limits<size_type>::max() / sizeof(value_type)
			};


		public:

			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			___xns_not_instantiable(allocator_traits);



			// -- public static methods ---------------------------------------

			// max size
			/**
			 * @fn max_size
			 * @brief returns the maximum object size supported by the allocator
			 * @param a allocator
			 * @return size
			*/
			static constexpr auto max_size(const allocator_type& ___a)
				noexcept(noexcept(___a.max_size())) -> size_type
				requires (requires { ___a.max_size(); }) {
					return ___a.max_size();
			}

			static constexpr auto max_size(const allocator_type& ___a)
				noexcept -> size_type requires (!requires { ___a.max_size(); }) {
					return ___max_size;
			}




			// allocate
			/**
			 * @fn allocate
			 * @brief allocates uninitialized storage using the allocator
			 * @param a allocator
			 * @param n size
			 * @return pointer
			 */
			[[nodiscard]] static constexpr auto allocate(allocator_type& ___a, const size_type ___n = 1)
				noexcept(noexcept(___a.allocate(___n))) -> pointer {
				return ___a.allocate(___n);
			}


			// allocate hint
			/**
			* @fn allocate
			* @brief allocates uninitialized storage using the allocator with a hint
			* @param a allocator
			* @param n size
			* @param h hint
			* @return pointer
			*/
			[[nodiscard]] static constexpr auto allocate(allocator_type&    ___a,
														 const size_type    ___n,
														 const_void_pointer ___h)
				noexcept(noexcept(___a.allocate(___n, ___h)))
				-> pointer requires (requires { ___a.allocate(___n, ___h); }) {
				return ___a.allocate(___n, ___h);
			}

			// deallocate
			/**
			 * @fn deallocate
			 * @brief deallocates storage using the allocator
			 * @param a allocator
			 * @param p pointer
			 */
			static constexpr auto deallocate(allocator_type& ___a, pointer ___p)
				noexcept(noexcept(___a.deallocate(___p)))
				-> void requires (requires { ___a.deallocate(___p); }) {
				___a.deallocate(___p);
			}

			// deallocate with size
			/**
			 * @fn deallocate
			 * @brief deallocates storage using the allocator
			 * @param a allocator
			 * @param p pointer
			 * @param n size
			 */
			static constexpr auto deallocate(allocator_type& ___a, pointer ___p, const size_type ___n)
				noexcept(noexcept(___a.deallocate(___p, ___n)))
				-> void requires (requires { ___a.deallocate(___p, ___n); }) {
				___a.deallocate(___p, ___n);
			}

			// select on container copy construction
			/**
			 * @fn select_on_container_copy_construction
			 * @brief obtains the allocator to use after copying a standard container
			 * @param a allocator
			 * @return allocator
			 */
			//[[nodiscard]] static constexpr auto select_on_container_copy_construction(const allocator_type& ___a)
			//	noexcept(noexcept(___a.select_on_container_copy_construction()))
			//	-> allocator_type requires (requires { ___a.select_on_container_copy_construction(); }) {
			//	return ___a.select_on_container_copy_construction();
			//}

			// select on container copy construction
			/**
			 * @fn select_on_container_copy_construction
			 * @brief obtains the allocator to use after copying a standard container
			 * @param a allocator
			 * @return allocator
			 */
			//static constexpr auto select_on_container_copy_construction(const allocator_type& ___a)
			//	noexcept(xns::is_nothrow_copy_constructible<allocator_type>) // does exception may throw here or in parent function?
			//	-> const allocator_type& requires (!requires { ___a.select_on_container_copy_construction(); }) {
			//		return ___a;
			//}

			// allocate_at_least (public static member function)
			// allocates storage at least as large as the requested size via an allocator

			// select_on_container_copy_construction [static] (public static member function)
			// obtains the allocator to use after copying a standard container


	}; // class allocator_traits

} // namespace xns

#endif // XNS_ALLOCATOR_TRAITS_HEADER
