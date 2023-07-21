#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <iostream>
#include "types.hpp"
#include "allocator.hpp"
#include "array.hpp"
#include "policy.hpp"



// -- I S  C O M P A R A B L E ------------------------------------------------

template <class T, class U>
concept is_comparable = requires(T t, U u) {
	{ t == u }; { t != u };
	{ t <= u }; { t >= u };
	{ t < u };  { t > u };
};




// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- V E C T O R  C L A S S ----------------------------------------------

	template <class T, xns::restrict R = xns::assignable_t>
	class vector final {

		ASSERT_RESTRICT(R);

		public:

			// -- F R I E N D S -----------------------------------------------

			/* make vector as friend */
			template <class U, class S, class... A>
			friend vector<U, S> make_vector(A&&... args);


			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using value_type = T;

			/* restrict type */
			using restrict = R;

			/* self type */
			using self = vector<value_type, restrict>;

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


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			vector(void)
			// initializations
			: _vector{nullptr}, _capacity{0}, _size{0} { }



			/* copy constructor */
			vector(const self& other)
			// initializations
			: vector{} {
				ASSERT_COPYABLE(R);
				// reserve other size
				reserve(other._size);
				// loop through other vector
				for (size_type x = 0; x < other._size; ++x) {
					// construct value by copy
					allocator::construct(_vector + x, other._vector[x]);
				} // set size
				_size = other._size;
			}

			/* move constructor */
			vector(self&& other) noexcept
			// initializations
			: _vector{other._vector}, _capacity{other._capacity}, _size{other._size} {
				ASSERT_MOVEABLE(R);

				// invalidate other vector
				other.initialize_members();
			}

			/* destructor */
			~vector(void) {
				// check pointer
				if (_vector) {
					// clear vector
					clear();
					// deallocate memory
					allocator::deallocate(_vector);
				}
			}


			// -- D E B U G ---------------------------------------------------

			void print(void) const {
				std::cout << "\nsize: " << _size << std::endl;
				std::cout << "capacity: " << _capacity << std::endl;
				/*for (Size x = 0; x < _size; ++x) {
					std::cout << _vector[x] << std::endl;
				}*/
			}

			// -- O P E R A T O R S -------------------------------------------

			/* copy operator */
			vector& operator=(const self& other) {
				ASSERT_COPYABLE(R);
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
			vector& operator=(self&& other) noexcept {
				ASSERT_MOVEABLE(R);
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
			reference operator[](const size_type index) {
				// return reference
				return _vector[index];
			}

			/* const subscript operator */
			const_reference operator[](const size_type index) const {
				// return reference
				return _vector[index];
			}

			/* at */
			reference at(const size_type index) {
				// return reference
				return _vector[index];
			}

			/* const at */
			const_reference at(const size_type index) const {
				// return reference
				return _vector[index];
			}


			// -- E L E M E N T  A C C E S S ----------------------------------

			/* front */
			reference front(void) {
				// return reference
				return *_vector;
			}

			/* const front */
			const_reference front(void) const {
				// return reference
				return *_vector;
			}

			/* back */
			reference back(void) {
				// return reference
				return *(_vector + (_size - 1));
			}

			/* const back */
			const_reference back(void) const {
				// return reference
				return *(_vector + (_size - 1));
			}

			/* data */
			pointer data(void) {
				// return pointer
				return _vector;
			}

			/* const data */
			const_pointer data(void) const {
				// return pointer
				return _vector;
			}


			// -- C A P A C I T Y ---------------------------------------------

			/* empty */
			bool empty(void) const {
				// return result
				return _size == 0;
			}

			/* size */
			size_type size(void) const {
				// return size
				return _size;
			}

			/* capacity */
			size_type capacity(void) const {
				// return capacity
				return _capacity;
			}

			/* max size */
			size_type max_size(void) const {
				// return max size
				return allocator::max_size();
			}

			/* reserve */
			void reserve(const size_type capacity) {
				// check capacity
				if (capacity > _capacity) {
					// allocate memory
					pointer tmp = allocator::allocate(capacity);
					// check pointer
					if (_vector != nullptr) {
						// loop through vector
						for (size_type x = 0; x < _size; ++x) {
							// move elements
							allocator::construct(tmp + x, xns::move(_vector[x]));
							allocator::destroy(_vector + x);
						} // deallocate memory
						allocator::deallocate(_vector);
					} // assign capacity
					_capacity = capacity;
					// assign pointer
					_vector = tmp;
				}
			}

			// -- iteration ---------------------------------------------------

			/* start */
			size_type start(void) const {
				// return start
				return 0;
			}


			// -- M O D I F I E R S -------------------------------------------

			/* clear */
			void clear(void) {
				// loop through vector
				for (size_type x = 0; x < _size; ++x) {
					// destroy object
					allocator::destroy(_vector + x);
				} // reset size
				_size = 0;
			}

			/* emplace */
			template <typename... Args>
			void emplace(size_type pos, Args&&... args) {
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
				allocator::construct(_vector + pos, xns::forward<Args>(args)...);
				// increment size
				++_size;
			}

			/* emplace back */
			template <class... A>
			void emplace_back(A&&... args) {
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
			void push_back(void) {
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // construct element
				allocator::construct(_vector + _size);
				// increment size
				++_size;
			}

			/* copy push back */
			void copy_back(const value_type& value) {
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // construct element
				allocator::construct(_vector + _size, value);
				// increment size
				++_size;
			}

			/* move back */ // INFO: this is preferred over move push back
			void move_back(value_type&& value) {
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // construct element
				allocator::construct(_vector + _size, xns::move(value));
				// increment size
				++_size;
			}

			/* pop back */
			void pop_back(void) {
				// check size
				if (!_size) { return; }
				// destroy object
				allocator::destroy(_vector + (_size - 1));
				// decrement size
				--_size;
			}


			// -- E R A S E ---------------------------------------------------

			/* erase */
			void erase(const size_type pos) {
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



			/* filter */ //requires is_comparable<U, value>
			/* remove all elements that match the given value */
			template <class... A>
			void filter(const A&... compare) {
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
			void to_back(const value_type& value) {
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





		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* initialize members */
			void initialize_members(void) {
				// initialize pointer
				_vector = nullptr;
				// initialize capacity
				_capacity = 0;
				// initialize size
				_size = 0;
			}

			/* available */
			size_type available(void) const {
				// return available memory
				return _capacity - _size;
			}

			/* check capacity */
			inline size_type grow(void) {
				return (_capacity * 2) + (_capacity == 0);
			}

			/* destroy */
			//void destroy(


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			pointer _vector;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;



	};


	// -- F R I E N D  F U N C T I O N S --------------------------------------

	/* make vector */
	template <class T, class R = xns::assignable_t, class... A>
	xns::vector<T, R> make_vector(A&&... args) {

		using allocator = typename xns::vector<T, R>::allocator;

		// create vector
		xns::vector<T, R> vec;

		// allocate memory
		vec._vector = allocator::allocate(sizeof...(A));

		// check allocation success
		if (vec._vector != nullptr) {

			typename vector<T, R>::size_type x = 0;

			// fold expression to construct by forwarding
			(allocator::construct(&vec._vector[x++], xns::forward<A>(args)), ...);

			// assign sizes
			vec._size = vec._capacity = sizeof...(args);

		}
		return vec;
	}

};

#endif
