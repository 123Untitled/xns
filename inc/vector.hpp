#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <iostream>
#include "Types.hpp"
#include "allocator.hpp"
#include "array.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- V E C T O R  C L A S S ----------------------------------------------

	template <typename T>
	class Vector final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using Value = T;

			/* size type */
			using Size = UInt64;

			/* reference type */
			using Reference = Value&;

			/* const reference type */
			using ConstReference = const Value&;

			/* move reference type */
			using MoveReference = Value&&;

			/* pointer type */
			using Pointer = Value*;

			/* const pointer type */
			using ConstPointer = const Value*;

			/* allocator type */
			using Allocator = Xf::Allocator<Value>;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Vector(void)
			// initializations
			: _vector{nullptr}, _capacity{0}, _size{0} { }



			/* copy constructor */
			Vector(const Vector& other)
			// initializations
			: Vector{} {
				// reserve other size
				reserve(other._size);
				// loop through other vector
				for (Size x = 0; x < other._size; ++x) {
					// construct value by copy
					Allocator::construct(_vector + x, other._vector[x]);
				} // set size
				_size = other._size;
			}

			/* move constructor */
			Vector(Vector&& other) noexcept
			// initializations
			: _vector{other._vector}, _capacity{other._capacity}, _size{other._size} {
				// invalidate other vector
				other.initialize_members();
			}

			/* destructor */
			~Vector(void) {
				// check pointer
				if (_vector) {
					// clear vector
					clear();
					// deallocate memory
					Allocator::deallocate(_vector, _capacity);
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
			Vector& operator=(const Vector& other) {
				// check for self-assignment
				if (this != &other) {
					// clear vector
					clear();
					// !!!!!!! NOTE : optimize this one
					// reserve other size
					reserve(other._size);
					// loop through other vector
					for (Size x = 0; x < other._size; ++x) {
						// construct value by copy
						Allocator::construct(_vector + x, other._vector[x]);
					} // set size
					_size = other._size;
				} // return self reference
				return *this;
			}

			/* move operator */
			Vector& operator=(Vector&& other) noexcept {
				// check for self-assignment
				if (this != &other) {
					// clear vector
					clear();
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
			Reference operator[](const Size index) {
				// return reference
				return _vector[index];
			}

			/* const subscript operator */
			ConstReference operator[](const Size index) const {
				// return reference
				return _vector[index];
			}


			// -- E L E M E N T  A C C E S S ----------------------------------

			/* front */
			Reference front(void) {
				// return reference
				return *_vector;
			}

			/* const front */
			ConstReference front(void) const {
				// return reference
				return *_vector;
			}

			/* back */
			Reference back(void) {
				print();
				// return reference
				return *(_vector + (_size - 1));
			}

			/* const back */
			ConstReference back(void) const {
				// return reference
				return *(_vector + (_size - 1));
			}

			/* data */
			Pointer data(void) {
				// return pointer
				return _vector;
			}

			/* const data */
			ConstPointer data(void) const {
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
			Size size(void) const {
				// return size
				return _size;
			}

			/* capacity */
			Size capacity(void) const {
				// return capacity
				return _capacity;
			}

			/* max size */
			Size max_size(void) const {
				// return max size
				return Allocator::max_size();
			}

			/* reserve */
			void reserve(const Size capacity) {
				// check capacity
				if (capacity > _capacity) {
					// allocate memory
					Pointer tmp = Allocator::allocate(capacity);
					// check pointer
					if (_vector != nullptr) {
						// loop through vector
						for (Size x = 0; x < _size; ++x) {
							// move elements
							tmp[x] = Xf::move(_vector[x]);
						} // deallocate memory
						Allocator::deallocate(_vector, _capacity);
					} // assign capacity
					_capacity = capacity;
					// assign pointer
					_vector = tmp;
				}
			}


			// -- M O D I F I E R S -------------------------------------------

			/* clear */
			void clear(void) {
				// loop through vector
				for (Size x = 0; x < _size; ++x) {
					// destroy object
					Allocator::destroy(_vector + x);
				} // reset size
				_size = 0;
			}

			/* emplace */
			template <typename... Args>
			void emplace(Size pos, Args&&... args) {
				// check position
				if (pos > _size) { return; }
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // move elements
				for (Size x = _size; x > pos; --x) {
					// move element
					_vector[x] = Xf::move(_vector[x - 1]);
				} // construct element
				Allocator::construct(_vector + pos, Xf::forward<Args>(args)...);
				// increment size
				++_size;
			}

			/* emplace back */
			template <typename... Args>
			void emplace_back(Args&&... args) {
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // construct element
				Allocator::construct(_vector + _size, Xf::forward<Args>(args)...);
				// increment size
				++_size;
			}

			/* copy push back */
			void push_back(const Value& value) {
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // construct element
				Allocator::construct(_vector + _size, value);
				// increment size
				++_size;
			}

			/* move push back */
			void push_back(Value&& value) {
				// check capacity
				if (!available()) {
					// double capacity
					reserve(grow());
				} // construct element
				Allocator::construct(_vector + _size, Xf::move(value));
				// increment size
				++_size;
			}

			/* pop back */
			void pop_back(void) {
				// check size
				if (!_size) { return; }
				// destroy object
				Allocator::destroy(_vector + (_size - 1));
				// decrement size
				--_size;
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
			Size available(void) const {
				// return available memory
				return _capacity - _size;
			}

			/* check capacity */
			inline Size grow(void) {
				return (_capacity << 1) + (_capacity == 0);
			}

			/* destroy */
			//void destroy(


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			Pointer _vector;

			/* capacity */
			Size _capacity;

			/* size */
			Size _size;



	};

};

#endif
