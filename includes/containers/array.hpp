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

#ifndef XNS_ARRAY_HEADER
#define XNS_ARRAY_HEADER

// local headers
#include "type_traits/types.hpp"
#include "type_traits/type_operations/move.hpp"
#include "type_traits/type_transformations/common_type.hpp"
#include "type_traits/type_categories/is_integral.hpp"
#include "type_traits/type_categories/is_enum.hpp"
#include "type_traits/type_categories/is_void.hpp"
#include "type_traits/type_operations/forward.hpp"
#include "type_traits/relationships_and_property_queries/is_convertible.hpp"
#include "other/swap.hpp"
#include "other/safe_enum.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <typename __type>
	concept is_index = xns::is_integral <xns::remove_cvr<__type>>
					|| xns::is_enum     <xns::remove_cvr<__type>>
					|| xns::is_safe_enum<xns::remove_cvr<__type>>
					|| xns::is_convertible<__type, unsigned char>
					|| xns::is_convertible<__type, unsigned short>
					|| xns::is_convertible<__type, unsigned int>
					|| xns::is_convertible<__type, unsigned long>
					|| xns::is_convertible<__type, unsigned long long>;


	// -- A R R A Y -----------------------------------------------------------

	template <typename T, xns::size_t... N>
	class array2 final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::array2<T, N...>;

			/* value type */
			using value_type = T;

			/* mutable reference type */
			using mut_ref    = value_type&;

			/* const reference type */
			using const_ref  = const value_type&;

			/* mutable pointer type */
			using mut_ptr    = value_type*;

			/* const pointer type */
			using const_ptr  = const value_type*;

			/* size type */
			using size_type  = xns::size_t;


		private:

			// -- private constants -------------------------------------------

			/* number of dimensions */
			static constexpr size_type _ndim = sizeof...(N);

			/* number of elements */
			static constexpr size_type _size = (N * ...);

			/* dimension sizes */
			static constexpr size_type _dims[_ndim] = { N... };


			// -- assertions --------------------------------------------------

			/* check if T is not void */
			static_assert(not xns::is_void<T>, "): VOID IS NOT ALLOWED :(");

			/* check if there is at least one dimension */
			static_assert(_ndim > 0,        "): NEED AT LEAST ONE DIMENSION :(");

			/* check if one of the dimensions is zero */
			static_assert(_size > 0,    "): SOMETHING TIMES ZERO IS ZERO! :(");


		public:

			// -- public members ----------------------------------------------

			/* array data */
			value_type _data[_size];


			// -- public assignments ------------------------------------------

			/* variadic assignment */
			template <typename... A>
			constexpr auto assign(A&&... args) -> void {
				// check number of arguments is valid
				static_assert(sizeof...(A) == _size, "): WRONG NUMBER OF ARGUMENTS :(");
				// declare index
				size_type i = 0;
				// assign arguments to array
				((_data[i] = xns::forward<A>(args), ++i), ...);
			}


			// -- public modifiers --------------------------------------------

			/* swap */
			constexpr auto swap(self& other) noexcept -> void {
				// loop over elements
				for (size_type i = 0; i < _size; ++i)
					xns::swap(_data[i], other._data[i]);
			}

			/* fill */
			constexpr auto fill(const value_type& value) -> void {
				// loop over elements
				for (size_type i = 0; i < _size; ++i)
					_data[i] = value;
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator (for 1D array) */
			template <typename I>
			constexpr auto operator[](const I& index) noexcept -> mut_ref {
				// check index is integral
				static_assert(xns::is_index<I>, "): I MUST BE INDEX TYPE :("); // TODO: fix this
				// return reference to indexed element
				return _data[static_cast<size_type>(index)];
			}

			/* const subscript operator */
			template <typename I>
			constexpr auto operator[](const I& index) const noexcept -> const_ref {
				// check index is integral
				static_assert(xns::is_index<I>, "): I MUST BE INDEX TYPE :("); // TODO: fix this
				// return constant reference to indexed element
				return _data[static_cast<size_type>(index)];
			}


			// -- public accessors --------------------------------------------

			/* at (compile time) */
			template <size_type... I>
			constexpr auto at(void) noexcept -> mut_ref {
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "): WRONG NUMBER OF INDICES :(");
				// return reference to element indexed by linearized indices
				return _data[sub<I...>()];
			}

			/* const at (compile time) */
			template <size_type... I>
			constexpr auto at(void) const noexcept -> const_ref {
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "): WRONG NUMBER OF INDICES :(");
				// return reference to element indexed by linearized indices
				return _data[sub<I...>()];
			}


			/* at */
			template <typename... I>
			constexpr auto at(I&&... indexs) noexcept -> mut_ref {
				// check all indices are integral
				static_assert((xns::is_index<I> && ...), "): I MUST BE INDEX TYPE :("); // TODO: fix this
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "): WRONG NUMBER OF INDICES :(");
				// return reference to element indexed by linearized indices
				return _data[sub(xns::forward<I>(indexs)...)];
			}

			/* const at */
			template <typename... I>
			constexpr auto at(I&&... indexs) const noexcept -> const_ref {
				// check all indices are integral
				static_assert((xns::is_index<I> && ...), "): I MUST BE INDEX TYPE :("); // TODO: fix this
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim,        "): WRONG NUMBER OF INDICES :(");
				// return reference to element indexed by linearized indices
				return _data[sub(xns::forward<I>(indexs)...)];
			}

			/* dimensions */
			constexpr auto dimensions(void) const noexcept -> size_type {
				// return number of dimensions
				return _ndim;
			}

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				// return number of elements
				return _size;
			}

			/* size of dimension */
			template <size_type IDX>
			constexpr auto size(void) const noexcept -> size_type {
				// return size of dimension indexed by IDX
				return _dims[IDX];
			}

			/* front */
			constexpr auto front(void) noexcept -> mut_ref {
				// return reference to first element
				return _data[0];
			}

			/* const front */
			constexpr auto front(void) const noexcept -> const_ref {
				// return constant reference to first element
				return _data[0];
			}

			/* back */
			constexpr auto back(void) noexcept -> mut_ref {
				// return reference to last element
				return _data[_size - 1];
			}

			/* const back */
			constexpr auto back(void) const noexcept -> const_ref {
				// return constant reference to last element
				return _data[_size - 1];
			}

			/* data */
			constexpr auto data(void) noexcept -> mut_ptr {
				// return pointer to data
				return _data;
			}

			/* const data */
			constexpr auto data(void) const noexcept -> const_ptr {
				// return constant pointer to data
				return _data;
			}


			// -- public print method -----------------------------------------

			/* print */
			void print(void) const {
				std::cout << "A R R A Y - " << _ndim << "D\n";
				std::cout << "number of elements: " << _size << "\n";
				for (size_type i = 0; i < _ndim; ++i) {
					std::cout << "dimension[" << i << "] " << _dims[i] << "e\n";
				} std::cout << "\n" << std::flush;
			}


			// -- loop methods ------------------------------------------------

			/* for each */
			template <typename F>
			constexpr void for_each(F&& func) {
				// loop over array
				for (size_type i = 0; i < _size; ++i)
					func(_data[i]);
			}

			/* const for each */
			template <typename F>
			constexpr void for_each(F&& func) const {
				// loop over array
				for (size_type i = 0; i < _size; ++i)
					func(_data[i]);
			}




		private:

			// -- private methods ---------------------------------------------

			// WARNING: this function has to be debugged

			template <size_type... I>
			static consteval auto sub(void) noexcept -> size_type {
				constexpr size_type index_arr[_ndim] = { I... };
				size_type linear = 0;
				size_type stride = 1;
				for (int i = _ndim - 1; i >= 0; --i) {
					linear += index_arr[i] * stride;
					stride *= _dims[i];
				} return linear;
			}



			/* helper function for subscript operator */
			template <class... I> requires (_ndim > 2)
			inline constexpr auto sub(I&&... indexs) const noexcept -> size_type {
				// initialize array with indexs casted to Size
				size_type index_arr[_ndim] = { static_cast<size_type>(indexs)... };
				// linear index declaration
				size_type linear = 0;
				// stride declaration
				size_type stride = 1;
				// loop over dimensions
				for (int i = _ndim - 1; i >= 0; --i) {
					// compute linear index
					linear += (index_arr[i] * stride);
					// update stride
					stride *= (_dims[i]);
				} // return linear index
				return linear;
			}

			/* subscript for 1D array */
			template <typename I> requires (_ndim == 1)
			inline constexpr auto sub(const I& index) const noexcept -> size_type {
				// return linear index
				return static_cast<size_type>(index);
			}

			/* subscript for 2D array */
			template <typename Y, typename X> requires (_ndim == 2)
			inline constexpr auto sub(const Y& y, const X& x) const noexcept -> size_type {
				// return linear index
				return (static_cast<size_type>(y) * _dims[1])
					  + static_cast<size_type>(x);
			}


	};


	/* deduction guide */
	template <typename... A>
	array2(A&&...) -> array2<xns::common_type<A...>, sizeof...(A)>;



	// -- A R R A Y -----------------------------------------------------------

	template <typename T, decltype(sizeof(0)) N>
	class array final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::array<T, N>;

			/* value type */
			using value_type = T;

			/* mutable reference type */
			using mut_ref    = value_type&;

			/* constant reference type */
			using const_ref  = const value_type&;

			/* mutable pointer type */
			using mut_ptr    = value_type*;

			/* constant pointer type */
			using const_ptr  = const value_type*;

			/* size type */
			using size_type  = decltype(sizeof(0));


			// -- public members ----------------------------------------------

			/* data */
			value_type _data[N];


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			constexpr auto operator[](const size_type index) noexcept -> mut_ref {
				return _data[index];
			}

			/* const subscript operator */
			constexpr auto operator[](const size_type index) const noexcept -> const_ref {
				return _data[index];
			}


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return N;
			}

			/* data */
			constexpr auto data(void) noexcept -> mut_ptr {
				return _data;
			}

			/* const data */
			constexpr auto data(void) const noexcept -> const_ptr {
				return _data;
			}


	}; // class array


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... A>
	array(A&&...) -> array<xns::common_type<A...>, sizeof...(A)>;

} // namespace xns

#endif // XNS_ARRAY_HEADER
