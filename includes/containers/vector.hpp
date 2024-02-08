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

#ifndef XNS_VECTOR_HPP
#define XNS_VECTOR_HPP

// local headers
#include "types.hpp"
#include "allocator.hpp"
#include "array.hpp"
#include "is_comparable.hpp"
#include "is_trivially_destructible.hpp"
#include "swap.hpp"

// c++ standard library headers
#include <iostream>



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- V E C T O R  C L A S S ----------------------------------------------

	template <typename T>
	class vector final {


		// -- assertions ------------------------------------------------------

		/* requires nothrow move operations */
		static_assert(xns::is_nothrow_move_constructible<T>
				   && xns::is_nothrow_move_assignable<T>,
					  "vector, requires nothrow move operations.");

		/* requires nothrow destructible */
		static_assert(xns::is_nothrow_destructible<T>,
					  "vector, requires nothrow destructible type.");


		// -- friends ---------------------------------------------------------

		/* make vector as friend */
		template <typename U, typename... A>
		friend auto make_vector(A&&...) -> xns::vector<U>;


		private:

			// -- forward declarations ----------------------------------------

			/* iterator */
			template <bool>
			class vector_iterator;


		public:


			// -- public types ------------------------------------------------

			/* self type */
			using self           = xns::vector<T>;

			/* value type */
			using value_type     = T;

			/* size type */
			using size_type      = xns::size_t;

			/* mutable reference type */
			using mut_ref        = T&;

			/* const reference type */
			using const_ref      = const T&;

			/* move reference type */
			using move_ref       = T&&;

			/* mutable pointer type */
			using mut_ptr        = T*;

			/* const pointer type */
			using const_ptr      = const T*;

			/* allocator type */
			using allocator      = xns::allocator<T>;

			/* iterator type */
			using iterator       = vector_iterator<false>;

			/* const iterator type */
			using const_iterator = vector_iterator<true>;


		private:

			// -- private members ---------------------------------------------

			/* data */
			mut_ptr _vector;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;


			// -- private lifecycle -------------------------------------------

			/* member constructor */
			inline vector(mut_ptr   ptr,
					const size_type capacity,
					const size_type size) noexcept
			: _vector{ptr}, _capacity{capacity}, _size{size} {}


		public:


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline vector(void) noexcept
			: _vector{nullptr}, _capacity{0}, _size{0} {}


			/* allocation constructor */
			explicit inline vector(mut_ptr ptr, const size_type size) noexcept
			: _vector{ptr}, _capacity{ptr ? size : 0}, _size{_capacity} {}
			// WARNING: this constructor is dangerous, use with caution
			// need to use same allocator as the one used to allocate ptr


			/* copy constructor */
			explicit vector(const self& other)
			: _vector{other._vector != nullptr ? allocator::allocate(other._size)
											   : nullptr},
			  _capacity{other._size}, _size{_capacity} {

				// loop through other vector
				for (size_type i = 0; i < _size; ++i)
					allocator::construct(_vector + i, other._vector[i]);
			}

			/* move constructor */
			inline vector(self&& other) noexcept
			: _vector{other._vector}, _capacity{other._capacity}, _size{other._size} {

				// invalidate other
				other._init();
			}

			/* destructor */
			inline ~vector(void) noexcept {

				if (_vector == nullptr)
					return;

				// destroy elements
				_clear();

				// deallocate memory
				allocator::deallocate(_vector);
			}


			// -- public iterators --------------------------------------------

			/* begin */
			inline auto begin(void) noexcept -> iterator {
				return self::iterator{_vector};
			}

			/* const begin */
			inline auto begin(void) const noexcept -> const_iterator {
				return self::const_iterator{_vector};
			}

			/* end */
			inline auto end(void) noexcept -> iterator {
				return self::iterator{_vector + _size};
			}

			/* const end */
			inline auto end(void) const noexcept -> const_iterator {
				return self::const_iterator{_vector + _size};
			}


			// -- D E B U G ---------------------------------------------------

			auto print(void) const -> void {
				std::cout << "\nsize: " << _size << std::endl;
				std::cout << "capacity: " << _capacity << std::endl;
				for (const auto& x : *this) {
					std::cout << x << " ";
				}
			}


			// important need to setup member like _capacity before operation may throw !


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) -> self& requires (not xns::is_trivially_copyable<T>) {

				// check for self-assignment
				if (this == &other)
					return *this;

				// destroy elements
				_clear();

				// allocate / reallocate memory
				if (_capacity < other._size)
					_vector = allocator::reallocate(_vector, other._size);

				// reset members
				_vector   = nullptr;
				_size     = 0;
				_capacity = 0;

				// reserve other size
				reserve(other._size);


				// copy construct elements
				for (size_type i = 0; i < other._size; ++i) {

					allocator::construct(_vector + i, other._vector[i]);

					if constexpr (not xns::is_nothrow_copy_constructible<T>)
						/* info: increment size after each construct
						   if throw, size reflects the number of valid elements */
						++_size;
				}

				if constexpr (xns::is_nothrow_copy_constructible<T>)
					// update size
					_size = other._size;

				// return self reference
				return *this;
			}

			/* copy assignment operator (trivially copyable) */
			auto operator=(const self& other) -> self& requires (xns::is_trivially_copyable<T>) {

				// check for self-assignment
				if (this == &other)
					return *this;

				// destroy elements
				_clear();

				// deallocate memory
				allocator::deallocate(_vector); /* info: no nullptr check */

				return *this;
			}

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {

				// check for self-assignment
				if (this == &other)
					return *this;

				// destroy elements
				_clear();

				// deallocate memory
				allocator::deallocate(_vector); /* info: no nullptr check */

				// move other members
				_vector   = other._vector;
				_capacity = other._capacity;
				_size     = other._size;

				// invalidate other
				other._init();

				return *this;
			}

			/* subscript operator */
			inline auto operator[](const size_type index) noexcept -> mut_ref {
				return _vector[index];
			}

			/* const subscript operator */
			inline auto operator[](const size_type index) const noexcept -> const_ref {
				return _vector[index];
			}

			/* at */
			auto at(const size_type index) noexcept -> mut_ref {
				return _vector[index];
			}

			/* const at */
			auto at(const size_type index) const noexcept -> const_ref {
				return _vector[index];
			}


			// -- public accessors --------------------------------------------

			/* empty */
			inline auto empty(void) const noexcept -> bool {
				return _size == 0;
			}

			/* size */
			inline auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			inline auto capacity(void) const noexcept -> size_type {
				return _capacity;
			}

			/* front */
			inline auto front(void) noexcept -> mut_ref {
				return *_vector;
			}

			/* const front */
			inline auto front(void) const noexcept -> const_ref {
				return *_vector;
			}

			/* back */
			inline auto back(void) noexcept -> mut_ref {
				return _vector[_size - 1];
			}

			/* const back */
			inline auto back(void) const noexcept -> const_ref {
				return _vector[_size - 1];
			}

			/* data */
			inline auto data(void) noexcept -> mut_ptr {
				return _vector;
			}

			/* const data */
			inline auto data(void) const noexcept -> const_ptr {
				return _vector;
			}




			// -- public memory management ------------------------------------

			/* reserve */
			inline auto reserve(const size_type capacity) -> void {

				// check capacity
				if (capacity <= _capacity) 
					return;

				// call reserve implementation
				_reserve(capacity);
			}


			/* resize */
			auto resize(const size_type size) -> void {

				// superior size
				if (size > _size) {

					// check capacity
					if (size > _capacity)
						reserve(size);

					// construct default elements
					for (size_type i = _size; i < size; ++i)
						allocator::construct(_vector + i);
				}

				// inferior size
				else
					// destroy only non-trivially destructible types
					if constexpr (not xns::is_trivially_destructible<T>)

						// destroy excess elements (if not equal size)
						for (size_type i = size; i < _size; ++i)
							allocator::destroy(_vector + i);

				// update size
				_size = size;
			}



			// -- public modifiers --------------------------------------------

			/* clear */
			auto clear(void) noexcept(xns::is_nothrow_destructible<T>) -> void {

				// destroy elements
				_clear();

				// update size
				_size = 0;
			}


			/* emplace */
			template <typename... A>
			auto emplace(const size_type pos, A&&... args) -> void {

				/* info: if construct throws, elements are not moved back.
						 so construct new element before and call insert */

				if constexpr (not xns::is_nothrow_constructible<T, A...>) {
					insert(pos, value_type{xns::forward<A>(args)...});
					return;
				}
				else {

					// call emplace if pos is equal to size
					if (pos == _size)
						return emplace_back(xns::forward<A>(args)...);

					// return if position is out of range
					if (pos > _size)
						return;

					// expand if no available space
					if (_available_capacity() == 0)
						_reserve(_expand());


					if constexpr (xns::is_trivially_copyable<T>)
						::memmove(_vector + pos + 1,           // destination
								  _vector + pos,               // source
								   (_size - pos) * sizeof(T)); // size

					else
						if constexpr (xns::is_nothrow_move_constructible<T>
								   && xns::is_nothrow_destructible<T>) {

							// move construct last element
							allocator::construct(_vector + _size, xns::move(_vector[_size - 1]));

							/* info: it is better for performance
									 to destroy and move construct than move assign */

							// move elements
							for (size_type i = _size - 1; i > pos; --i) {
								allocator::destroy(_vector + i);
								allocator::construct(_vector + i, xns::move(_vector[i - 1]));
							}
						}
						else
							static_assert(xns::always_false<T>, "vector, emplace not supports throw move operations");

					// construct new element in place
					allocator::construct(_vector + pos,
							xns::forward<A>(args)...);

					// update size
					++_size;
				}
			}

			/* emplace back */
			template <typename... A>
			auto emplace_back(A&&... args) -> void {

				// expand if no available space
				if (_available_capacity() == 0)
					_reserve(_expand());

				// construct new element
				allocator::construct(_vector + _size,
					  xns::forward<A>(args)...);

				// update size
				++_size;
			}

			/* push back */
			template <typename U>
			auto push_back(U&& value) -> void {

				// expand if no available space
				if (_available_capacity() == 0)
					_reserve(_expand());

				// construct new element
				allocator::construct(_vector + _size,
					  xns::forward<U>(value));

				// update size
				++_size;
			}

			/* pop back */
			inline auto pop_back(void) noexcept -> void {

				// return if size is zero
				if (_size == 0)
					return;

				// destroy only non-trivially destructible types
				if constexpr (not xns::is_trivially_destructible<T>)
					allocator::destroy(_vector + --_size);
				else
					--_size;
			}




			/* insert */
			template <typename U> requires (xns::is_same<value_type, xns::remove_cvr<U>>)
			auto insert(size_type pos, U&& value) -> void {

				// call emplace if pos is equal to size
				if (pos == _size)
					return push_back(xns::forward<U>(value));

				// return if position is out of range
				if (pos > _size)
					return;

				// check capacity
				if (_available_capacity() == 0)
					reserve(_expand());

				// move elements
				for (size_type x = _size; x > pos; --x) {
					// move element
					_vector[x] = xns::move(_vector[x - 1]);
				}

				// increment size
				++_size;

				allocator::destroy(_vector + pos);
				// copy or move value (need to check if U is nothrow copy constructible or nothrow move constructible) !!!
				allocator::construct(_vector + pos, xns::forward<U>(value));
				
				//_vector[pos] = xns::forward<U>(value);
			}


			/* erase */
			inline auto erase(const iterator& pos) noexcept -> void {
				// check position
				if (pos._ptr < _vector) { return; }
				// compute position (pointers subtraction gives a signed type (ptrdiff_t))
				erase(static_cast<size_type>(pos._ptr - _vector));
			}

			/* erase */
			auto erase(const size_type pos) noexcept -> void {
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






			/* swap */
			auto swap(self& other) noexcept -> void {
				// swap members
				xns::swap(_vector,   other._vector);
				xns::swap(_capacity, other._capacity);
				xns::swap(_size,     other._size);
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
						for (size_type z = x; z < (_size - 1); ++z)
							_vector[z] = xns::move(_vector[z + 1]);
						// move tmp
						_vector[_size - 1] = xns::move(tmp);
						// return
						return;
					}
				} // push back
				push_back(value);
			}

			/* dichotomic search */
			template <typename U>
			auto dichotomic_search(const U& value) noexcept -> iterator
				requires (xns::is_comparable<U, value_type>) {

				// check if U is comparable to value_type
				static_assert(is_comparable<U, value_type>,
					"): TYPE ARE NOT COMPARABLE IN DICHOTOMIC SEARCH :(");

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
					else    { return self::iterator(_vector + middle);            }
				} // not found
				return self::iterator(_vector + _size);

			}

			/* dichotomic insert */
			auto dichotomic_insert(const_ref value) -> void
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





		private:

			// -- private methods ---------------------------------------------

			/* init */
			inline auto _init(void) noexcept -> void {
				_vector   = nullptr;
				_capacity = 0;
				_size     = 0;
			}

			/* available capacity */
			inline auto _available_capacity(void) const noexcept -> size_type {
				// return available memory
				return _capacity - _size;
			}

			/* expand */
			inline auto _expand(void) const noexcept -> size_type {
				return _capacity ? _capacity << 1 : 1;
			}

			/* _reserve */
			auto _reserve(const size_type capacity) -> void requires (not xns::is_trivially_copyable<T>) {

				// allocate memory
				mut_ptr tmp = allocator::allocate(capacity);

				// reconstruct elements
				for (size_type i = 0; i < _size; ++i) {
					allocator::construct(tmp + i, xns::move(_vector[i]));
					allocator::destroy(_vector + i);
				}

				// deallocate memory
				allocator::deallocate(_vector); /* info: no nullptr check */

				// update members
				_capacity = capacity;
				  _vector = tmp;
			}

			/* _reserve (trivially copyable) */
			auto _reserve(const size_type capacity) -> void requires (xns::is_trivially_copyable<T> == true) {

				// reallocate memory
				  _vector = allocator::realloc(_vector, capacity);
				_capacity = capacity;
			}

			/* clear */
			auto _clear(void) noexcept -> void {

				// destroy only non-trivially destructible types
				if constexpr (not xns::is_trivially_destructible<T>)

					// destroy elements
					for (size_type i = 0; i < _size; ++i)
						allocator::destroy(_vector + i);
			}


	};



	// -- M A K E  V E C T O R ------------------------------------------------

	/* make vector */
	template <typename T, typename... A>
	inline auto make_vector(A&&... args) -> xns::vector<T> {

		// allocator type
		using allocator = typename xns::vector<T>::allocator;

		// create vector
		xns::vector<T> vec{
			allocator::allocate(sizeof...(A)),
			sizeof...(A),
			sizeof...(A)
		};

		typename xns::vector<T>::size_type x = 0;
		// fold expression to construct by forwarding
		(allocator::construct(&vec._vector[x], xns::forward<A>(args)), ..., ++x);

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
			using cond_ref = typename xns::conditional<C, vector_type::const_ref,
														  vector_type::mut_ref>;

			/* pointer type */
			using cond_ptr   = typename xns::conditional<C, vector_type::const_ptr,
															vector_type::mut_ptr>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline vector_iterator(void) noexcept
			: _ptr{nullptr} {}

			/* pointer constructor */
			inline vector_iterator(cond_ptr ptr) noexcept
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
			~vector_iterator(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator (non-const) */
			inline auto operator=(const vector_type::iterator& other) noexcept -> self& {
				// copy pointer
				_ptr = other._ptr;
				// return self reference
				return *this;
			}

			/* copy assignment operator (const) */
			inline auto operator=(const vector_type::const_iterator& other) noexcept -> self& {
				// assert invalid conversion
				static_assert(_const, "iterator, cannot convert const to non-const vector iterator.");
				// copy pointer
				_ptr = other._ptr;
				// return self reference
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(vector_type::iterator&& other) noexcept -> self& {
				return operator=(other);
			}

			/* move assignment operator (const) */
			inline auto operator=(vector_type::const_iterator&& other) noexcept -> self& {
				return operator=(other);
			}


			// -- public accessor operators -----------------------------------

			/* dereference operator */
			inline auto operator*(void) const noexcept -> cond_ref {
				return *_ptr;
			}

			/* arrow operator */
			inline auto operator->(void) const noexcept -> cond_ptr {
				return _ptr;
			}


			// -- public increment operators ----------------------------------

			/* pre-increment operator */
			inline auto operator++(void) noexcept -> self& {
				// increment pointer
				++_ptr;
				// return self reference
				return *this;
			}

			/* post-increment operator */
			inline auto operator++(int) noexcept -> self {
				// copy self
				self tmp{*this};
				// increment pointer
				++_ptr;
				// return copy
				return tmp;
			}


			// -- public decrement operators ----------------------------------

			/* pre-decrement operator */
			inline auto operator--(void) noexcept -> self& {
				// decrement pointer
				--_ptr;
				// return self reference
				return *this;
			}

			/* post-decrement operator */
			inline auto operator--(int) noexcept -> self {
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
			inline auto operator==(const vector_iterator<D>& other) const noexcept -> bool {
				// return pointer equality
				return _ptr == other._ptr;
			}

			/* inequality operator */
			template <bool D>
			inline auto operator!=(const vector_iterator<D>& other) const noexcept -> bool {
				return _ptr != other._ptr;
			}

			/* null equality operator */
			inline auto operator==(xns::null) const noexcept -> bool {
				return _ptr == nullptr;
			}

			/* null inequality operator */
			inline auto operator!=(xns::null) const noexcept -> bool {
				return _ptr != nullptr;
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
				return _ptr != nullptr;
			}

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
				return _ptr == nullptr;
			}


		private:

			// -- private members ---------------------------------------------

			/* pointer */
			cond_ptr _ptr;

	}; // vector_iterator

} // namespace xns

#endif // XNS_VECTOR_HPP
