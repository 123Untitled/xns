#ifndef ARRAY_HEADER
#define ARRAY_HEADER

#include "is_integral.hpp"
#include "types.hpp"
#include "move.hpp"
#include "type_traits.hpp"
#include "integer_sequence.hpp"
#include "pack_type.hpp"
#include "parameter_pack.hpp"

#include <iostream>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- A R R A Y  M E T A  U T I L I T I E S -------------------------------

	/* array forward declaration */
	template <class T, SizeT... N>
	class Array;


	/* is array false type */
	template <class T>
	struct IsArray_s                 : Xf::false_t { };

	/* is array true type */
	template <class T, SizeT... N>
	struct IsArray_s<Array<T, N...>> : Xf::true_t  { };

	/* is array for c style arrays */
	template <class T, SizeT N>
	struct IsArray_s<T[N]>           : Xf::true_t  { };

	/* is array value */
	template <class T>
	constexpr bool IsArray_v = IsArray_s<T>::value;

	/* is array concept */
	template <class T>
	concept IsArray = IsArray_v<T>;





	// -- A R R A Y  C L A S S ------------------------------------------------

	template <class T, SizeT... N>
	class Array final {

		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using Value     = T;

			/* self type */
			using Self      = Array<Value, N...>;

			/* reference type */
			using Reference = Value&;

			/* move reference type */
			using MoveRef   = Value&&;

			/* pointer type */
			using Pointer   = Value*;

			/* const reference type */
			using ConstRef  = const Value&;

			/* const pointer type */
			using ConstPtr  = const Value*;

			/* size type */
			using Size      = decltype((N * ...));


		private:

			// -- P R I V A T E  C O N S T A N T S ----------------------------

			/* number of dimensions */
			static constexpr Size _ndim = sizeof...(N);

			/* number of elements */
			static constexpr Size _size = (N * ...);


			// -- A S S E R T I O N S -----------------------------------------

			/* check if T is not an array */
			//static_assert(!IsArray<T>,        "USE MULTIPLE DIMENSIONS INSTEAD -> Array<T, 3, 3, 3>");

			/* check if T is not void */
			static_assert(IsNotVoid<T>,       "VOID IS NOT ALLOWED");

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
			static constexpr SizeT _dims[_ndim] = { N... };


		public:

			// -- P U B L I C  M E M B E R S ----------------------------------

			/* array data */
			Value _data[_size];


			// -- P U B L I C  S U B S C R I P T  O P E R A T O R S -----------

			/* multidimensional subscript operator */
			template<class... I> // Size required all same
			Value& operator()(I&&... indexs) requires (... && std::is_same_v<I, std::remove_reference_t<I>>) {
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "WRONG NUMBER OF INDICES");
				// return reference to element indexed by linearized indices
				return _data[_subscript(std::forward<I>(indexs)...)];
			}

			/* at */
			template <class... I>
			Reference at(I&&... indexs) {
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "WRONG NUMBER OF INDICES");
				// return reference to element indexed by linearized indices
				return _data[_subscript(std::forward<I>(indexs)...)];
			}

			/* const at */
			template <class... I>
			ConstRef at(I&&... indexs) const {
				// check number of indices is valid
				static_assert(sizeof...(I) == _ndim, "WRONG NUMBER OF INDICES");
				// return reference to element indexed by linearized indices
				return _data[_subscript(std::forward<I>(indexs)...)];
			}


			/* subscript operator */
			//template <Xf::integral_c Index>
			template <class Index>
			Reference operator[](const Index index) {
				// check number of indices is valid
				static_assert(_ndim == 1, "FOR MULTIDIMENSIONAL SUBSCRIPT USE -> operator()");
				// return reference to element
				return _data[index];
			}

			/* const subscript operator */
			//template <Xf::integral_c Index>
			template <class Index>
			ConstRef operator[](const Index index) const {
				// check number of indices is valid
				static_assert(_ndim == 1, "FOR MULTIDIMENSIONAL SUBSCRIPT USE -> operator()");
				// return reference to element
				return _data[index];
			}





			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* dimensions */
			constexpr Size dimensions(void) const {
				// return number of dimensions
				return _ndim;
			}

			/* capacity */
			constexpr Size capacity(void) const {
				// return number of elements
				return _size;
			}

			/* size */
			constexpr Size size(void) const {
				// return number of elements
				return _size;
			}

			/* size of dimension */
			template <Size IDX>
			constexpr Size size(void) const {
				// return size of dimension indexed by IDX
				return _dims[IDX];
			}

			/* front */
			constexpr Reference front(void) {
				// return reference to first element
				return _data[0];
			}

			/* const front */
			constexpr ConstRef front(void) const {
				// return constant reference to first element
				return _data[0];
			}

			/* back */
			constexpr Reference back(void) {
				// return reference to last element
				return _data[_size - 1];
			}

			/* const back */
			constexpr ConstRef back(void) const {
				// return constant reference to last element
				return _data[_size - 1];
			}

			/* pointer */
			constexpr Pointer pointer(void) {
				// return pointer to data
				return _data;
			}

			/* const pointer */
			constexpr ConstPtr pointer(void) const {
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
			template<class... I>
			constexpr Size _subscript(I&&... indexs) const {
				// initialize array with indexs casted to Size
				Size index_arr[_ndim] = { static_cast<Size>(indexs)... };
				// linear index declaration
				Size linear = 0;
				// stride declaration
				Size stride = 1;
				// loop over dimensions
				for (int i = _ndim - 1; i >= 0; --i) {
					// compute linear index
					linear += index_arr[i] * stride;
					// update stride
					stride *= _dims[i];
				} // return linear index
				return linear;
			}


	};

};

#endif

