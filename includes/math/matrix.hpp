#ifndef XNS_MATRIX_HEADER
#define XNS_MATRIX_HEADER

#include "types.hpp"
#include "array.hpp"
#include "is_same.hpp"
#include "is_scalar.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* forward declaration */
	template <class, xns::ubyte, xns::ubyte>
	class matrix;


	// -- I S  M A T R I X ----------------------------------------------------

	/* is matrix concept */
	template <class T>
	concept is_matrix = xns::is_same<T, xns::matrix<typename T::value_type,
															 T::rows,
															 T::cols>>;


	//matrix<float, 3, 3> mat;

	// -- M A T R I X ---------------------------------------------------------

	template <class T, xns::ubyte R, xns::ubyte C>
	class matrix {


		// -- friends ---------------------------------------------------------

		/* other matrix as friend */
		template <class, xns::ubyte, xns::ubyte>
		friend class xns::matrix;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::matrix<T, R, C>;

			/* array type */
			using array_type = xns::array<T, R, C>;

			/* value type */
			using value_type = T;

			/* reference type */
			using reference = T&;

			/* const reference type */
			using const_reference = const T&;

			/* size type */
			using size_type = typename array_type::size_type;


			// -- public constants --------------------------------------------

			/* number of rows */
			static constexpr xns::ubyte rows = R;

			/* number of columns */
			static constexpr xns::ubyte cols = C;


			// -- constructors ------------------------------------------------

			/* default constructor */
			constexpr matrix(void)
			: _data{ } {}

			/* copy constructor */
			constexpr matrix(const self& other)
			: _data{other._data} {}

			/* move constructor */
			constexpr matrix(self&& other)
			: _data{xns::move(other._data)} {}

			/* variadic constructor */
			template <class... A>
			constexpr matrix(A&&... args) requires (xns::is_same_cvr<T, A...>)
			: _data{xns::forward<A>(args)...} {
				// check if number of arguments is correct
				static_assert(sizeof...(args) == R * C,
					"): NUMBER OF ARGUMENTS MUST BE EQUAL TO MATRIX SIZE :(");
			}

			/* destructor */
			constexpr ~matrix(void) {}


			// -- public assignment methods -----------------------------------

			/* copy assignment */
			void assign(const self& other) {
				// check for self assignment
				if (this != &other) {
					// copy data
					_data = other._data; }
			}

			/* move assignment */
			void assign(self&& other) {
				// check for self assignment
				if (this != &other) {
					// move data
					_data = xns::move(other._data); }
			}

			/* variadic assignment */
			template <class... A>
			void assign(A&&... args) requires (xns::is_same<T, A...>) {
				// check if number of arguments is correct
				static_assert(sizeof...(args) == R * C,
					"): NUMBER OF ARGUMENTS MUST BE EQUAL TO MATRIX SIZE :(");
				// assign data
				_data.assign(xns::forward<A>(args)...);
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self& other) -> self& {
				// call copy assignment and return self reference
				assign(other);
				return *this;
			}

			/* move assignment operator */
			constexpr auto operator=(self&& other) -> self& {
				// call move assignment and return self reference
				assign(xns::move(other));
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* at */
			constexpr reference at(const xns::ubyte& row, const xns::ubyte& col) {
				// return value indexed by row and col
				return _data.at(row, col);
			}

			/* const at */
			constexpr const_reference at(const xns::ubyte& row, const xns::ubyte& col) const {
				// return constant value indexed by row and col
				return _data.at(row, col);
			}


			// -- public arithmetic methods -----------------------------------

			/* addition */
			template <class M1, class M2>
			friend constexpr auto add_matrix(const M1&, const M2&);

			/* subtraction */
			template <class M1, class M2>
			friend constexpr auto subtract_matrix(const M1&, const M2&);

			/* multiplication */
			template <class M1, class M2>
			friend constexpr auto multiply_matrix(const M1&, const M2&);




			/* new matrix resulting from multiplication with other matrix */
			template <xns::is_matrix M>
			constexpr auto multiply(const M& other) const -> xns::matrix<T, rows, M::cols> {

				// check dimensions
				static_assert(cols == M::rows, "): DIMENSIONS MUST MATCH :(");

				// result matrix
				xns::matrix<T, rows, M::cols> result;

				// iterate over rows
				for (size_type i = 0; i < rows; ++i) {
					// iterate over columns
					for (size_type j = 0; j < M::cols; ++j) {
						// iterate over columns
						for (size_type k = 0; k < cols; ++k) {
							// add product of elements
							result._data.at(i, j) += _data.at(i, k) * other._data.at(k, j);
						}
					}
				}

				// return result
				return result;
			}



			/* scale matrix */
			template <xns::is_scalar S>
			constexpr void scale(const S& scalar) {
				// iterate over elements
				/*
				for (size_type i = 0; i < _data.size(); ++i) {
					// multiply element by scalar
					_data[i] *= scalar; }
					*/
			}



			// -- public arithmetic operators ---------------------------------


			/* multiply by scalar */
			template <xns::is_scalar S>
			void operator*=(const S& scalar) {
				// multiply by scalar
				scale(scalar);
			}


			// -- public print methods ----------------------------------------

			/* print */
			constexpr void print(void) const {
				// iterate over rows
				for (size_type i = 0; i < rows; ++i) {
					// iterate over columns
					for (size_type j = 0; j < cols; ++j) {
						// print element
						std::cout << _data.at(i, j) << " ";
					} // new line
					std::cout << "\n";
				} // flush
				std::cout << "\n" << std::flush;

				_data.print();
			}





		private:

			// -- private members ---------------------------------------------

			/* matrix data */
			array_type _data;


	};


	// -- M A T R I X  A R I T H M E T I C ------------------------------------

	/* addition */
	template <class M1, class M2>
	constexpr auto add_matrix(const M1& lhs, const M2& rhs) {

		// check types are matrices
		static_assert(xns::is_matrix<M1> && xns::is_matrix<M2>,
							"): TYPES MUST BE MATRICES :(");

		// check matrices are same
		static_assert(xns::is_same<M1, M2>, "): MATRICES MUST BE SAME TYPE :(");

		// result matrix
		M1 result;

		// size type
		using size_type = typename M1::size_type;

		// get array si
		constexpr size_type size = result._data.size();

		// iterate over rows
		for (size_type i = 0; i < size; ++i) {
			// add elements
			result._data[i] = lhs._data[i] + rhs._data[i];
		}

		// return result
		return result;

	}

	/* subtraction */
	template <class M1, class M2>
	constexpr auto subtract_matrix(const M1& lhs, const M2& rhs) {

		// check types are matrices
		static_assert(xns::is_matrix<M1> && xns::is_matrix<M2>,
							"): TYPES MUST BE MATRICES :(");

		// check matrices are same
		static_assert(xns::is_same<M1, M2>, "): MATRICES MUST BE SAME TYPE :(");

		// result matrix
		M1 result;

		// size type
		using size_type = typename M1::size_type;

		// iterate over rows
		for (size_type i = 0; i < result._data.size(); ++i) {
			// add elements
			result._data[i] = lhs._data[i] - rhs._data[i];
		}

		// return result
		return result;
	}

	/* addition */
	template <xns::is_matrix M1, xns::is_matrix M2>
	constexpr auto operator+(const M1& lhs, const M2& rhs) {
		return add_matrix(lhs, rhs);
	}

	/* subtraction */
	template <xns::is_matrix M1, xns::is_matrix M2>
	constexpr auto operator-(const M1& lhs, const M2& rhs) {
		return subtract_matrix(lhs, rhs);
	}

	/* multiplication */
	template <xns::is_matrix M1, xns::is_matrix M2>
	constexpr auto operator*(const M1& lhs, const M2& rhs) {
		return multiply_matrix(lhs, rhs);
	}

	// max matrix
	template <xns::is_matrix M1, xns::is_matrix M2>
	consteval auto& max_matrix(const M1& lhs, const M2& rhs) {
		return lhs;
		//return lhs._data.size() > rhs._data.size() ? lhs : rhs;
	}

	// min matrix
	template <xns::is_matrix M1, xns::is_matrix M2>
	consteval auto& min_matrix(const M1& lhs, const M2& rhs) {
		return lhs;
		//return lhs._data.size() < rhs._data.size() ? lhs : rhs;
	}


	/* multiplication */
	template <class M1, class M2>
	constexpr auto multiply_matrix(const M1& lhs, const M2& rhs) {

		// check types are matrices
		static_assert(xns::is_matrix<M1> && xns::is_matrix<M2>,
						"): TYPES MUST BE MATRICES :(");

		// check dimensions // WARNING -----| not good ! (or)
		//static_assert(M1::cols == M2::rows || M2::cols == M1::rows,
						//"): DIMENSIONS MUST MATCH :(");
		static_assert(M1::cols == M2::rows,
						"): DIMENSIONS MUST MATCH :(");

		// result col m1 x row m2

		// get greatest rows and columns
		constexpr auto rows = M1::rows > M2::rows ? M1::rows : M2::rows;
		constexpr auto cols = M1::cols > M2::cols ? M1::cols : M2::cols;

		/*
		// get greatest matrix
		constexpr auto& greatest = max_matrix(lhs, rhs);

		// get smallest matrix
		constexpr auto& smallest = min_matrix(lhs, rhs);
		*/



		// result matrix
		xns::remove_reference<decltype(lhs)> result;

		// size type
		using size_type = typename M1::size_type;

		/*
		// iterate over rows
		for (size_type i = 0; i < result.rows; ++i) {
			// iterate over columns
			for (size_type j = 0; j < result.cols; ++j) {
				// iterate over elements
				for (size_type k = 0; k < smallest.cols; ++k) {
					// add elements
					result.at(i, j) += lhs.at(i, k) * rhs.at(k, j);
				}
			}
		}*/

		// return result
		return result;
	}


	// -- M A T R I X  T Y P E S ----------------------------------------------

	/* 1x1 matrix */
	template <class T>
	using matrix_1x1 = xns::matrix<T, 1, 1>;

	/* 2x1 matrix */
	template <class T>
	using matrix_2x1 = xns::matrix<T, 2, 1>;

	/* 2x2 matrix */
	template <class T>
	using matrix_2x2 = xns::matrix<T, 2, 2>;

	/* 3x2 matrix */
	template <class T>
	using matrix_3x2 = xns::matrix<T, 3, 2>;

	/* 3x3 matrix */
	template <class T>
	using matrix_3x3 = xns::matrix<T, 3, 3>;

	/* 4x4 matrix */
	template <class T>
	using matrix_4x4 = xns::matrix<T, 4, 4>;




}

#endif
