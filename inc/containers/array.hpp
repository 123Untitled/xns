#ifndef ARRAY_HEADER
#define ARRAY_HEADER

#include "is_integral.hpp"
#include "types.hpp"
#include "move.hpp"
#include "type_traits.hpp"
#include "integer_sequence.hpp"
#include "pack_type.hpp"
#include "parameter_pack.hpp"
#include "common_type.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- A R R A Y  M E T A  U T I L I T I E S -------------------------------

	/* array forward declaration */
	template <class T, xns::size_t... N>
	class array;


	/* false type */
	template <class T>
	struct _is_xns_array                      : xns::no  { };

	/* true type */
	template <class T, xns::size_t... N>
	struct _is_xns_array<array<T, N...>>      : xns::yes { };

	/* is array for c style arrays */
	template <class T, xns::size_t N>
	struct _is_xns_array<T[N]>           : xns::yes  { };

	/* is array concept */
	template <class T>
	concept is_xns_array = _is_xns_array<T>::value;






	// -- A R R A Y  C L A S S ------------------------------------------------

	template <class T, xns::size_t... N>
	class array final {

		public:

			// -- T Y P E S ---------------------------------------------------

			/* value type */
			using value         = T;

			/* self type */
			using self          = array<value, N...>;

			/* reference type */
			using reference     = value&;

			/* move reference type */
			using MoveRef       = value&&;

			/* pointer type */
			using mut_pointer   = value*;

			/* const reference type */
			using const_ref     = const value&;

			/* const pointer type */
			using const_pointer = const value*;

			/* size type */
			using size_type     = decltype((N * ...));


		private:

			// -- P R I V A T E  C O N S T A N T S ----------------------------

			/* number of dimensions */
			static constexpr size_type _ndim = sizeof...(N);

			/* number of elements */
			static constexpr size_type _size = (N * ...);


			// -- A S S E R T I O N S -----------------------------------------

			/* check if T is not an array */
			//static_assert(!IsArray<T>,        "USE MULTIPLE DIMENSIONS INSTEAD -> Array<T, 3, 3, 3>");

			/* check if T is not void */
			static_assert(!xns::is_void<T>,       "VOID IS NOT ALLOWED");

			/* check if there is at least one dimension */
			static_assert(_ndim > 0,          "NEED AT LEAST ONE DIMENSION");

			/* check if all dimensions are equal to one */
			static_assert(!((N == 1) && ...), "SINGLE VALUE ? NO IT'S A JOKE!");

			/* check if one of the dimensions is one */
			static_assert(!((N == 1) || ...), "USELESS DIMENSION -> _*|*_");

			/* check if one of the dimensions is zero */
			static_assert((N * ...) > 0,      "SOMETHING TIMES ZERO IS ZERO!");


			// -- P R I V A T E  C O N S T A N T S ----------------------------

			/* dimension sizes */
			static constexpr size_type _dims[_ndim] = { N... };


		public:

			// -- P U B L I C  M E M B E R S ----------------------------------

			/* array data */
			value _data[_size];


			// -- P U B L I C  S U B S C R I P T  O P E R A T O R S -----------

			/* multidimensional subscript operator */
			template<class... I> // Size required all same
			constexpr value& operator()(I&&... indexs) requires (... && std::is_same_v<I, std::remove_reference_t<I>>) {
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "WRONG NUMBER OF INDICES");
				// return reference to element indexed by linearized indices
				return _data[_subscript(std::forward<I>(indexs)...)];
			}

			/* at */
			template <class... I>
			constexpr reference at(I&&... indexs) {
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "WRONG NUMBER OF INDICES");
				// return reference to element indexed by linearized indices
				return _data[_subscript(std::forward<I>(indexs)...)];
			}

			/* const at */
			template <class... I>
			constexpr const_ref at(I&&... indexs) const {
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "WRONG NUMBER OF INDICES");
				// return reference to element indexed by linearized indices
				return _data[_subscript(std::forward<I>(indexs)...)];
			}


			/* subscript operator */
			//template <Xf::integral_c Index>
			template <class Index>
			constexpr reference operator[](const Index index) {
				// check number of indices is valid
				static_assert(_ndim == 1, "FOR MULTIDIMENSIONAL SUBSCRIPT USE -> operator()");
				// return reference to element
				return _data[index];
			}

			/* const subscript operator */
			//template <Xf::integral_c Index>
			template <class Index>
			constexpr const_ref operator[](const Index index) const {
				// check number of indices is valid
				static_assert(_ndim == 1, "FOR MULTIDIMENSIONAL SUBSCRIPT USE -> operator()");
				// return reference to element
				return _data[index];
			}





			// -- P U B L I C  A C C E S S O R S ------------------------------

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
			constexpr const_ref front(void) const {
				// return constant reference to first element
				return _data[0];
			}

			/* back */
			constexpr reference back(void) {
				// return reference to last element
				return _data[_size - 1];
			}

			/* const back */
			constexpr const_ref back(void) const {
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



			// -- P U B L I C  M E T H O D S ----------------------------------

		private:

			/* print recursive */
			/*
			template <class U, SizeT... M>
			void _print(const Wrapper<U, M...>&) const {
				// code here...
			} */

		public:
			/* print array content */
			void print(void) const {

			}



			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------

			static void _debug(void) {
				std::cout << "A R R A Y - " << _ndim << "D" << std::endl;
				std::cout << "number of elements: " << _size << std::endl;
				for (unsigned int i = 0; i < _ndim; i++) {
					std::cout << "dimension[" << i << "] " << _dims[i] << "e" << std::endl;
				}
			}

			//template <class U, SizeT... M>
			//static void debug(const Wrapper<U, M...>&) { }




		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			// WARNING: this function has to be debugged
			// TODO: constexpr condition for single dimansionnal array

			/* helper function for subscript operator */
			template <class... I> requires (_ndim > 1)
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
			inline constexpr size_type _subscript(I&& index) const {
				// return linear index
				return index;
			}


	};

	template <class... A>
	array(A...) -> array<xns::common_type_t<A...>, sizeof...(A)>;


	// NEED TO DEDUCE TYPE OF ARRAY
	// no time to implement this now
	// TODO: implement this
	template <class... A>
	constexpr xns::array<std::common_type_t<A...>, sizeof...(A)> make_array(A&&... args) {
		using T = std::common_type_t<A...>;

		xns::array<T, sizeof...(A)> arr = {xns::forward<A>(args)...};

		// return array
		return arr;
	}


};

#endif

