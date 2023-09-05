#ifndef VECTOR_HEADER
#define VECTOR_HEADER

// local headers
#include "types.hpp"
#include "allocator.hpp"
#include "array.hpp"
#include "is_comparable.hpp"

// c++ standard library headers
#include <iostream>

// simd headers
#include <arm_neon.h>



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- V E C T O R  C L A S S ----------------------------------------------

	template <class T>
	class vector final {


		private:

			// -- forward declarations ----------------------------------------

			/* iterator */
			template <bool>
			class vector_iterator;


		public:



			// -- public types ------------------------------------------------

			/* self type */
			using self = vector<T>;

			/* value type */
			using value_type = T;

			/* size type */
			using size_type = xns::size_t;

			/* reference type */
			using reference = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* move reference type */
			using move_reference = value_type&&;

			/* pointer type */
			using pointer = value_type*;

			/* const pointer type */
			using const_pointer = const value_type*;

			/* allocator type */
			using allocator = xns::allocator<value_type>;

			/* iterator type */
			using iterator = vector_iterator<false>;

			/* const iterator type */
			using const_iterator = vector_iterator<true>;


			// -- friends -----------------------------------------------------

			/* make vector as friend */
			template <class U, class... A>
			friend auto make_vector(A&&...) -> vector<U>;

			/* make copy as friend */
			template <class U>
			friend auto make_copy(const U&) -> U;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline vector(void) noexcept
			: _vector{nullptr}, _capacity{0}, _size{0} {}



			/* copy constructor */
			explicit vector(const self& other)
			: _vector{nullptr}, _capacity{other._capacity}, _size{other._size} {

				if (other._vector == nullptr) { return; }

				// allocate memory
				_vector = allocator::allocate(_capacity);

				// loop through other vector
				for (size_type x = 0; x < _size; ++x) {
					// construct value by copy
					allocator::construct(_vector + x, other._vector[x]);
				}
			}


		public:

			/* move constructor */
			vector(self&& other) noexcept
			// initializations
			: _vector{other._vector}, _capacity{other._capacity}, _size{other._size} {

				// invalidate other vector
				other.initialize_members();
			}

			/* destructor */
			inline ~vector(void) {
				// clear vector
				clear();
				// deallocate memory
				if (_vector)
					allocator::deallocate(_vector);
			}


			// -- public iterators --------------------------------------------

			/* begin */
			auto begin(void) noexcept -> iterator {
				return iterator{_vector};
			}

			/* const begin */
			auto begin(void) const noexcept -> const_iterator {
				return const_iterator{_vector};
			}

			/* end */
			auto end(void) noexcept -> iterator {
				return iterator{_vector + _size};
			}

			/* const end */
			auto end(void) const noexcept -> const_iterator {
				return const_iterator{_vector + _size};
			}


			// -- D E B U G ---------------------------------------------------

			auto print(void) const -> void {
				std::cout << "\nsize: " << _size << std::endl;
				std::cout << "capacity: " << _capacity << std::endl;
				for (const auto& x : *this) {
					std::cout << x << " ";
				}
			}


			// -- public assignment operators ---------------------------------

			/* copy operator */
			auto operator=(const self& other) -> self& {
				// check for self-assignment
				if (this != &other) {
					// clear vector
					clear();
					allocator::deallocate(_vector);
					// !!!!!!! NOTE : optimize this one
					// reserve other size
					reserve(other._size);
					// loop through other vector
					for (size_type x = 0; x < other._size; ++x) {
						// construct value by copy
						allocator::construct(_vector + x, other._vector[x]);
					} // set size
					_size = other._size;
				} // return self reference
				return *this;
			}

			/* move operator */
			auto operator=(self&& other) noexcept -> self& {
				// check for self-assignment
				if (this != &other) {
					// clear vector
					clear();
					allocator::deallocate(_vector);
					// move other vector
					_vector = other._vector;
					// move other capacity
					_capacity = other._capacity;
					// move other size
					_size = other._size;
					// invalidate other vector
					other.initialize_members();
				} // return self reference
				return *this;
			}

			/* subscript operator */
			auto operator[](const size_type index) -> reference {
				// return reference
				return _vector[index];
			}

			/* const subscript operator */
			auto operator[](const size_type index) const -> const_reference {
				// return reference
				return _vector[index];
			}

			/* at */
			auto at(const size_type index) -> reference {
				// return reference
				return _vector[index];
			}

			/* const at */
			auto at(const size_type index) const -> const_reference {
				// return reference
				return _vector[index];
			}


			// -- public accessors --------------------------------------------

			/* empty */
			auto empty(void) const noexcept -> bool {
				// return result
				return _size == 0;
			}

			/* size */
			auto size(void) const noexcept -> size_type {
				// return size
				return _size;
			}

			/* capacity */
			auto capacity(void) const noexcept -> size_type {
				// return capacity
				return _capacity;
			}

			/* front */
			auto front(void) noexcept -> reference {
				// return reference
				return *_vector;
			}

			/* const front */
			auto front(void) const noexcept -> const_reference {
				// return reference
				return *_vector;
			}

			/* back */
			auto back(void) noexcept -> reference {
				// return reference
				return *(_vector + (_size - 1));
			}

			/* const back */
			auto back(void) const noexcept -> const_reference {
				// return reference
				return *(_vector + (_size - 1));
			}

			/* data */
			auto data(void) noexcept -> pointer {
				// return pointer
				return _vector;
			}

			/* const data */
			auto data(void) const noexcept -> const_pointer {
				// return pointer
				return _vector;
			}




			// -- public memory management ------------------------------------

			/* reserve */
			auto reserve(const size_type capacity) -> void {
				// check capacity
				if (capacity <= _capacity) { return; }
				// allocate memory
				pointer tmp = allocator::allocate(capacity);
				// loop through vector
				for (size_type x = 0; x < _size; ++x) {
					// move element
					allocator::construct(tmp + x, xns::move(_vector[x]));
					// destroy element
					allocator::destroy(_vector + x);
				} // deallocate old memory
				allocator::deallocate(_vector); // INFO: do not check for nullptr
				// assign capacity
				_capacity = capacity;
				// assign pointer
				_vector = tmp;
			}

			/* resize */
			auto resize(const size_type size) -> void {

				// check size
				if (size < _size) {
					// loop through vector
					for (size_type x = size; x < _size; ++x) {
						// destroy elements
						allocator::destroy(_vector + x);
					}
				}
				else if (size > _size) {
					// check capacity
					if (size > _capacity) {
						// reserve size
						reserve(size);
					} // loop through vector
					for (size_type x = _size; x < size; ++x) {
						// construct elements
						allocator::construct(_vector + x);
					}
				}
				// assign size
				_size = size;


			}



			// -- public modifiers --------------------------------------------

			/* clear */
			auto clear(void) noexcept -> void {
				// loop over vector
				for (size_type x = 0; x < _size; ++x) {
					// destroy object
					allocator::destroy(_vector + x);
				} // reset size
				_size = 0;
			}

			/* emplace */
			template <typename... A>
			auto emplace(size_type pos, A&&... args) -> void {
				// check position
				if (pos > _size) { return; }
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // move elements
				for (size_type x = _size; x > pos; --x) {
					// move element
					_vector[x] = xns::move(_vector[x - 1]);
				} // construct element
				allocator::construct(_vector + pos, xns::forward<A>(args)...);
				// increment size
				++_size;
			}

			/* emplace back */
			template <class... A>
			auto emplace_back(A&&... args) -> void {
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // construct element
				allocator::construct(_vector + _size, xns::forward<A>(args)...);
				// increment size
				++_size;
			}

			/* push back */
			template <typename U>
			auto push_back(U&& value) -> void {
				// assert U is same as value_type
				static_assert(xns::is_same<xns::remove_cvr<U>, value_type>,
						"): VECTOR: PUSH BACK TYPE MISMATCH :(");
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // construct element
				allocator::construct(_vector + _size, xns::forward<U>(value));
				// increment size
				++_size;
			}

			/* pop back */
			inline auto pop_back(void) noexcept -> void {
				// check size
				if (not _size) { return; }
				// destroy object
				allocator::destroy(_vector + (--_size));
			}


			// -- E R A S E ---------------------------------------------------

			/* erase */
			auto erase(const size_type pos) -> void {
				// check position
				if (pos >= _size) { return; }
				// move elements
				for (size_type x = pos; x < (_size - 1); ++x) {
					// move element
					_vector[x] = xns::move(_vector[x + 1]);
				} // decrement size
				--_size;
				// destroy last element
				allocator::destroy(_vector + _size);
			}

			/* erase */
			inline auto erase(const iterator& pos) -> void {
				// check position
				if (pos._ptr < _vector) { return; }
				// compute position (pointers subtraction gives a signed type (ptrdiff_t))
				erase(static_cast<size_type>(pos._ptr - _vector));
			}



			/* filter */ //requires is_comparable<U, value>
			/* remove all elements that match the given value */
			template <class... A>
			auto filter(const A&... compare) -> void {
				// z is the index of the next element to move
				size_type z = 0;
				// loop over vector
				for (size_type x = 0; x < _size; ++x) {
					// loop over arguments to compare
					if (((_vector[x] != compare) && ...)) {
						// if no match, maybe move, check shift
						if (z != x) {
							// move element
							_vector[z] = xns::move(_vector[x]);
						} // increment z
						++z;
					}
				} // finaly, destroy elements and decrement size
				while (z < _size) { allocator::destroy(_vector + --_size); }
			}

			/* move elements to the back of the vector if exists, else push back */
			auto to_back(const value_type& value) -> void {
				// loop over vector
				for (size_type x = 0; x < _size; ++x) {
					// check for match
					if (_vector[x] == value) {
						// declare tmp
						value_type tmp = xns::move(_vector[x]);
						// move elements
						for (size_type z = x; z < (_size - 1); ++z) {
							// move element
							_vector[z] = xns::move(_vector[z + 1]);
						}
						// move tmp
						_vector[_size - 1] = xns::move(tmp);
						// return
						return;
					}
				} // push back
				copy_back(value);
			}

			/* dichotomic search */
			template <class U>
			auto dichotomic_search(const U& value) -> iterator
				requires (xns::is_comparable<U, value_type>) {

				// check if U is comparable to value_type
				//static_assert(is_comparable<U, value_type>,
				//	"): TYPE ARE NOT COMPARABLE IN DICHOTOMIC SEARCH :(");

				// check size
				if (!_size) { return end(); }

				// initialize bounds
				size_type lower = 0;
				size_type upper = _size - 1;

				// loop
				while (lower <= upper) {
					std::cout << "loop" << std::endl;
					// compute middle
					size_type middle = (lower + upper) / 2;

					// check value is greater
					if      (value > _vector[middle]) { lower = middle + 1; }
					// check value is lower
					else if (value < _vector[middle]) { upper = middle - 1; }
					// else value is equal
					else    { return iterator(_vector + middle);            }
				} // not found
				return end();

			}

			/* dichotomic insert */
			auto dichotomic_insert(const_reference value) -> void
				requires (xns::is_comparable<value_type>) {

				// check if U is comparable to value_type
				static_assert(is_comparable<value_type>,
					"): TYPE ARE NOT COMPARABLE IN DICHOTOMIC INSERT :(");


				// initialize bounds
				size_type lower = 0;
				size_type upper = _size - 1;


				// check size
				if (!_size) { return push_back(value); }

				// loop
				while (lower <= upper) {
					// compute middle
					size_type middle = (lower + upper) / 2;
					// check value is greater
					if (value > _vector[middle]) { lower = middle + 1; }
					// check value is lower
					else if (value < _vector[middle]) {

						if (middle == 0) { lower = 0; break; }
						// update upper
						upper = middle - 1;
					}
					// else value is already in the vector
					else { return; }

				} // insert

				insert(lower, value);
			}


			/* insert */
			auto insert(size_type pos, const_reference value) -> void {
				// check position
				if (pos > _size) { return; }
				// check capacity
				if (available() == 0) { reserve(grow()); }
				// move elements
				for (size_type x = _size; x > pos; --x) {
					// move element
					_vector[x] = xns::move(_vector[x - 1]);
				} // increment size
				++_size;
				// copy value
				_vector[pos] = value;
			}



		private:

			// -- private methods ---------------------------------------------

			/* initialize members */
			auto initialize_members(void) -> void {
				// initialize pointer
				_vector = nullptr;
				// initialize capacity
				_capacity = 0;
				// initialize size
				_size = 0;
			}

			/* available */
			auto available(void) const -> size_type {
				// return available memory
				return _capacity - _size;
			}

			/* check capacity */
			inline auto grow(void) const -> size_type {
				return (_capacity * 2) + (_capacity == 0);
			}



			// -- private members ---------------------------------------------

			/* data */
			pointer _vector;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;



	};



	// -- M A K E  V E C T O R ------------------------------------------------

	/* make vector */
	template <class T, class... A>
	xns::vector<T> make_vector(A&&... args) {

		using allocator = typename xns::vector<T>::allocator;

		// create vector
		xns::vector<T> vec;

		// allocate memory
		vec._vector = allocator::allocate(sizeof...(A));

		typename vector<T>::size_type x = 0;
		// fold expression to construct by forwarding
		(allocator::construct(&vec._vector[x++], xns::forward<A>(args)), ...);

		// assign sizes
		vec._size = vec._capacity = sizeof...(A);

		return vec;
	}


	// -- V E C T O R  I T E R A T O R ----------------------------------------

	template <class T> template <bool C>
	class vector<T>::vector_iterator final {


		// -- friends ---------------------------------------------------------

		/* other iterator as friend */
		template <bool D>
		friend class vector_iterator;

		/* vector as friend */
		friend class vector<T>;


		private:

			// -- private constants -------------------------------------------

			/* iterator is const */
			static constexpr bool _const = C;


		public:

			// -- public types ------------------------------------------------

			/* list type */
			using vector_type = xns::vector<T>;

			/* value type */
			using value_type = typename vector_type::value_type;

			/* self type */
			using self = vector_type::vector_iterator<C>;



			/* reference type */
			using reference = typename xns::conditional<C, vector_type::const_reference,
														   vector_type::reference>;

			/* pointer type */
			using pointer   = typename xns::conditional<C, vector_type::const_pointer,
														   vector_type::pointer>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline vector_iterator(void) noexcept
			: _ptr{nullptr} {}

			/* pointer constructor */
			inline vector_iterator(pointer ptr) noexcept
			: _ptr{ptr} {}

			/* copy constructor (non-const) */
			inline vector_iterator(const vector_type::iterator& other) noexcept
			: _ptr{other._ptr} {}

			/* copy constructor (const) */
			inline vector_iterator(const vector_type::const_iterator& other) noexcept
			: _ptr{other._ptr} {
				// assert invalid conversion
				static_assert(_const,
						"): CANNOT CONVERT CONST TO NON-CONST VECTOR ITERATOR :(");
			}

			/* move constructor (non-const) */
			inline vector_iterator(vector_type::iterator&& other) noexcept
			: vector_iterator{other._ptr} {}

			/* move constructor (const) */
			inline vector_iterator(vector_type::const_iterator&& other) noexcept
			: vector_iterator{other._ptr} {}

			/* destructor */
			inline ~vector_iterator(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator (non-const) */
			inline self& operator=(const vector_type::iterator& other) noexcept {
				// copy pointer
				_ptr = other._ptr;
				// return self reference
				return *this;
			}

			/* copy assignment operator (const) */
			inline self& operator=(const vector_type::const_iterator& other) noexcept {
				// assert invalid conversion
				static_assert(_const,
						"): CANNOT CONVERT CONST TO NON-CONST VECTOR ITERATOR :(");
				// copy pointer
				_ptr = other._ptr;
				// return self reference
				return *this;
			}

			/* move assignment operator */
			inline self& operator=(vector_type::iterator&& other) noexcept {
				// call copy assignment operator
				return operator=(other);
			}

			/* move assignment operator (const) */
			inline self& operator=(vector_type::const_iterator&& other) noexcept {
				// call copy assignment operator
				return operator=(other);
			}


			// -- public accessor operators -----------------------------------

			/* dereference operator */
			inline reference operator*(void) const noexcept {
				// return value
				return *_ptr;
			}

			/* arrow operator */
			inline pointer operator->(void) const noexcept {
				// return address
				return _ptr;
			}


			// -- public increment operators ----------------------------------

			/* pre-increment operator */
			inline self& operator++(void) noexcept {
				// increment pointer
				++_ptr;
				// return self reference
				return *this;
			}

			/* post-increment operator */
			inline self operator++(int) noexcept {
				// copy self
				self tmp{*this};
				// increment pointer
				++_ptr;
				// return copy
				return tmp;
			}


			// -- public decrement operators ----------------------------------

			/* pre-decrement operator */
			inline self& operator--(void) noexcept {
				// decrement pointer
				--_ptr;
				// return self reference
				return *this;
			}

			/* post-decrement operator */
			inline self operator--(int) noexcept {
				// copy self
				self tmp{*this};
				// decrement pointer
				--_ptr;
				// return copy
				return tmp;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			template <bool D>
			inline bool operator==(const vector_iterator<D>& other) const noexcept {
				// return pointer equality
				return _ptr == other._ptr;
			}

			/* inequality operator */
			template <bool D>
			inline bool operator!=(const vector_iterator<D>& other) const noexcept {
				// return pointer inequality
				return _ptr != other._ptr;
			}

			/* null equality operator */
			inline bool operator==(xns::null) const noexcept {
				// return pointer invalidity
				return _ptr == nullptr;
			}

			/* null inequality operator */
			inline bool operator!=(xns::null) const noexcept {
				// return pointer validity
				return _ptr != nullptr;
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
				// return pointer validity
				return _ptr != nullptr;
			}

			/* not operator */
			inline bool operator!(void) const noexcept {
				// return pointer invalidity
				return _ptr == nullptr;
			}


		private:

			// -- private members ---------------------------------------------

			/* pointer */
			pointer _ptr;

	};



};

#endif
