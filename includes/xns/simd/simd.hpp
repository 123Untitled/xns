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

#ifndef XNS_SIMD_HEADER
#define XNS_SIMD_HEADER

#include "xns/type_traits/type_operations/forward.hpp"
#include "xns/type_traits/type_transformations/common_type.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S I M D -------------------------------------------------------------

	template <typename __type, decltype(sizeof(0)) __size>
	class simd final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::simd<__type, __size>;

			/* size type */
			using size_type  = decltype(__size);

			/* value type */
			using value_type = __type;

			/* mutable reference type */
			using mut_ref    = value_type&;

			/* constant reference type */
			using const_ref  = const value_type&;

			/* mutable pointer type */
			using mut_ptr    = value_type*;

			/* constant pointer type */
			using const_ptr  = const value_type*;


		private:

			/* underlying type */
			using __underlying = __attribute__((__ext_vector_type__(__size))) __type;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr simd(void) noexcept = default;

			/* variadic constructor */
			template <typename... __params>
			inline constexpr simd(__params&&... __args) noexcept
			: __data{xns::forward<__params>(__args)...} {
			}

			/* copy constructor */
			constexpr simd(const self&) noexcept = default;

			/* move constructor */
			constexpr simd(self&&) noexcept = default;

			/* destructor */
			~simd(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return __size;
			}

			/* data */
			constexpr auto data(void) noexcept -> mut_ptr {
				return reinterpret_cast<mut_ptr>(&__data);
			}

			/* data */
			constexpr auto data(void) const noexcept -> const_ptr {
				return reinterpret_cast<const_ptr>(&__data);
			}

			/* underlying */
			constexpr auto underlying(void) noexcept -> __underlying& {
				return __data;
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			constexpr auto operator[](const size_type __idx) noexcept -> mut_ref {
				return reinterpret_cast<mut_ptr>(&__data)[__idx];
			}

			/* subscript operator */
			constexpr auto operator[](const size_type __idx) const noexcept -> const_ref {
				return reinterpret_cast<const_ptr>(&__data)[__idx];
			}


		private:

			// -- private members ---------------------------------------------

			/* data */
			__underlying __data;

	}; // class simd


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... __params>
	simd(__params...) -> simd<xns::common_type<__params...>, sizeof...(__params)>;


} // namespace xns


inline auto test(void) -> void {

	xns::simd simd{1.0f, 2.0f, 3.0f, 4.0f};

	simd[0] += 1.0f;
	++simd[1];

	auto* data = simd.data();

	auto& underlying = simd.underlying();

}

#endif // XNS_SIMD_HEADER
