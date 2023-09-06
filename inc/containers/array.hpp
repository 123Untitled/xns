#ifndef ARRAY_HEADER
#define ARRAY_HEADER

// local headers
#include "types.hpp"
#include "move.hpp"
#include "common_type.hpp"
#include "is_integral.hpp"
#include "is_enum.hpp"
#include "is_void.hpp"
#include "forward.hpp"
#include "is_convertible.hpp"

#include "safe_enum.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <class T>
	concept is_index = is_integral <xns::remove_cvr<T>>
					|| is_enum     <xns::remove_cvr<T>>
					|| is_safe_enum<xns::remove_cvr<T>>
					|| is_convertible<T, unsigned char,
										 unsigned short,
										 unsigned int,
										 unsigned long,
										 unsigned long long>;


	// -- A R R A Y -----------------------------------------------------------

	template <class T, xns::size_t... N>
	class array final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self            = array<T, N...>;

			/* value type */
			using value_type      = T;

			/* reference type */
			using reference       = value_type&;

			/* pointer type */
			using mut_pointer     = value_type*;

			/* const reference type */
			using const_reference = const value_type&;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* size type */
			using size_type       = xns::size_t;


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
			static_assert(!xns::is_void<T>, "): VOID IS NOT ALLOWED :(");

			/* check if there is at least one dimension */
			static_assert(_ndim > 0,        "): NEED AT LEAST ONE DIMENSION :(");

			/* check if one of the dimensions is zero */
			static_assert((N * ...) > 0,    "): SOMETHING TIMES ZERO IS ZERO! :(");


		public:

			// -- public members ----------------------------------------------

			/* array data */
			value_type _data[_size];


			// -- public assignments ------------------------------------------

			/* variadic assignment */
			template <class... A>
			constexpr void assign(A&&... args) {
				// check number of arguments is valid
				static_assert(sizeof...(A) == _size, "): WRONG NUMBER OF ARGUMENTS :(");
				// declare index
				size_type i = 0;
				// assign arguments to array
				((_data[i] = xns::forward<A>(args), ++i), ...);
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator (for 1D array) */
			template <class I>
			constexpr reference operator[](const I& index) {
				// check index is integral
				static_assert(xns::is_index<I>, "): I MUST BE INDEX TYPE :("); // TODO: fix this
				// return reference to indexed element
				return _data[static_cast<size_type>(index)];
			}

			/* const subscript operator */
			template <class I>
			constexpr const_reference operator[](const I& index) const {
				// check index is integral
				static_assert(xns::is_index<I>, "): I MUST BE INDEX TYPE :("); // TODO: fix this
				// return constant reference to indexed element
				return _data[static_cast<size_type>(index)];
			}


			// -- public accessors --------------------------------------------

			/* at */
			template <class... I>
			constexpr reference at(I&&... indexs) {
				// check all indices are integral
				static_assert((xns::is_index<I> && ...), "): I MUST BE INDEX TYPE :("); // TODO: fix this
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim,        "): WRONG NUMBER OF INDICES :(");
				// return reference to element indexed by linearized indices
				return _data[_subscript(xns::forward<I>(indexs)...)];
			}

			/* const at */
			template <class... I>
			constexpr const_reference at(I&&... indexs) const {
				// check all indices are integral
				static_assert((xns::is_index<I> && ...), "): I MUST BE INDEX TYPE :("); // TODO: fix this
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim,        "): WRONG NUMBER OF INDICES :(");
				// return reference to element indexed by linearized indices
				return _data[_subscript(xns::forward<I>(indexs)...)];
			}

			/* dimensions */
			constexpr size_type dimensions(void) const {
				// return number of dimensions
				return _ndim;
			}

			/* capacity */
			constexpr size_type capacity(void) const {
				// return number of elements
				return _size;
			}

			/* size */
			constexpr size_type size(void) const {
				// return number of elements
				return _size;
			}

			/* size of dimension */
			template <size_type IDX>
			constexpr size_type size(void) const {
				// return size of dimension indexed by IDX
				return _dims[IDX];
			}

			/* front */
			constexpr reference front(void) {
				// return reference to first element
				return _data[0];
			}

			/* const front */
			constexpr const_reference front(void) const {
				// return constant reference to first element
				return _data[0];
			}

			/* back */
			constexpr reference back(void) {
				// return reference to last element
				return _data[_size - 1];
			}

			/* const back */
			constexpr const_reference back(void) const {
				// return constant reference to last element
				return _data[_size - 1];
			}

			/* pointer */
			constexpr mut_pointer pointer(void) {
				// return pointer to data
				return _data;
			}

			/* const pointer */
			constexpr const_pointer pointer(void) const {
				// return constant pointer to data
				return _data;
			}

			/* data */
			constexpr mut_pointer data(void) {
				// return pointer to data
				return _data;
			}

			/* const data */
			constexpr const_pointer data(void) const {
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
			template <class F>
			constexpr void for_each(F&& func) {
				// loop over elements
				for (size_type i = 0; i < _size; ++i) {
					// apply function to element
					func(_data[i]);
				}
			}


		private:

			// -- private methods ---------------------------------------------

			// WARNING: this function has to be debugged

			/* helper function for subscript operator */
			template <class... I> requires (_ndim > 2)
			inline constexpr size_type _subscript(I&&... indexs) const {
				// initialize array with indexs casted to Size
				size_type index_arr[_ndim] = { static_cast<size_type>(indexs)... };
				// linear index declaration
				size_type linear = 0;
				// stride declaration
				size_type stride = 1;
				// loop over dimensions
				for (int i = _ndim - 1; i >= 0; --i) {
					// compute linear index
					linear += index_arr[i] * stride;
					// update stride
					stride *= _dims[i];
				} // return linear index
				return linear;
			}

			/* subscript for 1D array */
			template <class I> requires (_ndim == 1)
			inline constexpr size_type _subscript(const I& index) const {
				// return linear index
				return static_cast<size_type>(index);
			}

			/* subscript for 2D array */
			template <class Y, class X> requires (_ndim == 2)
			inline constexpr size_type _subscript(const Y& y, const X& x) const {
				// return linear index
				return (static_cast<size_type>(y) * _dims[1])
					  + static_cast<size_type>(x);
			}


	};


	/* deduction guide */
	template <class... A>
	array(A...) -> array<xns::common_type<A...>, sizeof...(A)>;


}

#endif

