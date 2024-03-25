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

#ifndef XNS_VECTOR_HEADER
#define XNS_VECTOR_HEADER

// local headers

#include "xns/memory/allocator.hpp"
#include "xns/memory/memcpy.hpp"

#include "xns/containers/array.hpp"

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_comparable.hpp"
#include "xns/type_traits/relationships_and_property_queries/extent.hpp"
#include "xns/type_traits/supported_operations/is_trivially_destructible.hpp"

#include "xns/utility/swap.hpp"


// c++ standard library headers
#include <iostream>
#include <cstring>



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- V E C T O R  C L A S S ----------------------------------------------

	template <typename __type,
			  typename __alloc = xns::allocator<__type>>
	class vector final {


		// -- assertions ------------------------------------------------------

		/* requires nothrow move operations */
		//static_assert(xns::is_nothrow_move_constructible<T>
		//		   && xns::is_nothrow_move_assignable<T>,
		//			  "vector, requires nothrow move operations.");

		/* requires nothrow destructible */
		static_assert(xns::is_nothrow_destructible<__type>,
					  "vector, requires nothrow destructible type.");


		private:

			// -- forward declarations ----------------------------------------

			/* iterator */
			template <bool>
			class vector_iterator;


		public:


			// -- public types ------------------------------------------------

			/* self type */
			using self           = xns::vector<__type, __alloc>;

			/* value type */
			using value_type     = __type;

			/* allocator type */
			using allocator      = __alloc;

			/* size type */
			using size_type      = xns::size_t;

			/* mutable reference type */
			using mut_ref        = value_type&;

			/* const reference type */
			using const_ref      = const value_type&;

			/* move reference type */
			using move_ref       = value_type&&;

			/* mutable pointer type */
			using mut_ptr        = allocator::mut_ptr;

			/* const pointer type */
			using const_ptr      = allocator::const_ptr;

			/* iterator type */
			using iterator       = vector_iterator<false>;

			/* const iterator type */
			using const_iterator = vector_iterator<true>;


		private:

			// -- private members ---------------------------------------------

			/* data */
			mut_ptr _data;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;


		public:




			/*
			template <class InputIt>
			constexpr vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());

			constexpr vector(const vector& other);
			constexpr vector(const vector& other, const Allocator& alloc);

			constexpr vector(vector&& other) noexcept;
			constexpr vector(vector&& other, const Allocator& alloc);

			*/


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr vector(void) noexcept(true /* allocator default construct */)
			: _data{nullptr}, _capacity{0}, _size{0} {
			}

			/* array constructor */
			template <typename T> requires (xns::extent<xns::remove_cvr<T>> != 0)
			explicit constexpr vector(T&& __arr) noexcept(true /* check for noexcept copy/move construct */)
			: _data{nullptr}, _capacity{xns::extent<xns::remove_cvr<T>>}, _size{_capacity} {

				// allocate memory
				_data = allocator::allocate(_capacity);

				// copy elements
				for (size_type i = 0; i < _size; ++i)
					allocator::construct(_data + i, xns::forward<T>(__arr)[i]);
			}

			/*
			constexpr vector( size_type count, const T& value, const Allocator& alloc = Allocator());
			constexpr explicit vector( size_type count, const Allocator& alloc = Allocator());
			*/

			/* allocation constructor */
			explicit inline vector(mut_ptr ptr, const size_type size) noexcept
			: _data{ptr}, _capacity{ptr ? size : 0}, _size{_capacity} {}
			// WARNING: this constructor is dangerous, use with caution
			// need to use same allocator as the one used to allocate ptr


			/* copy constructor */
			explicit vector(const self& other) noexcept(xns::is_nothrow_copy_constructible<value_type>)
			:   _data{other._size > 0 ? allocator::allocate(other._size) : nullptr},
			  _capacity{other._size},
			      _size{_capacity} {

				// trival copy
				if constexpr (xns::is_trivially_copyable<value_type>) {

					std::cout << "trivial vector copy" << std::endl;

					// copy elements
					xns::memcpy(_data, other._data, _size * sizeof(value_type));
				}

				// non-trivial copy
				else {

					// construct for nothrow copy constructible types
					if constexpr (xns::is_nothrow_copy_constructible<value_type>) {

						std::cout << "nothrow vector copy" << std::endl;

						// copy construct elements
						for (size_type i = 0; i < _size; ++i)
							allocator::construct(_data + i, other._data[i]);
					}

					else {

						std::cout << "throw vector copy" << std::endl;

						size_type i = 0;

						// try construct
						try {
							// copy construct elements
							while (i < _size) {
								allocator::construct(_data + i, other._data[i]);
								++i; }
						}
						// clean up on exception
						catch (...) {

							// destroy only non-trivially destructible types
							if constexpr (not xns::is_trivially_destructible<value_type>) {
								// destroy elements
								for (size_type j = 0; j < i; ++j)
									allocator::destroy(_data + j);
							}

							// deallocate memory
							allocator::deallocate(_data);

							// forward exception
							throw;
						}

					} // throw copy

				} // non-trivial copy

			} // copy constructor


			/* move constructor */
			inline vector(self&& other) noexcept
			: _data{other._data}, _capacity{other._capacity}, _size{other._size} {

				// invalidate other
				other._init();
			}

			/* destructor */
			~vector(void) noexcept {

				if (_data == nullptr)
					return;

				// destroy elements
				_clear();

				// deallocate memory
				allocator::deallocate(_data);
			}


			// -- public iterators --------------------------------------------

			/* begin */
			inline auto begin(void) noexcept -> iterator {
				return self::iterator{_data};
			}

			/* const begin */
			inline auto begin(void) const noexcept -> const_iterator {
				return self::const_iterator{_data};
			}

			/* end */
			inline auto end(void) noexcept -> iterator {
				return self::iterator{_data + _size};
			}

			/* const end */
			inline auto end(void) const noexcept -> const_iterator {
				return self::const_iterator{_data + _size};
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
			auto operator=(const self& other) -> self& requires (not xns::is_trivially_copyable<value_type>) {

				// check for self-assignment
				if (this == &other)
					return *this;

				// destroy elements
				_clear();

				// allocate / reallocate memory
				if (_capacity < other._size)
					_data = allocator::reallocate(_data, other._size);

				// reset members
				_data   = nullptr;
				_size     = 0;
				_capacity = 0;

				// reserve other size
				reserve(other._size);


				// copy construct elements
				for (size_type i = 0; i < other._size; ++i) {

					allocator::construct(_data + i, other._data[i]);

					if constexpr (not xns::is_nothrow_copy_constructible<value_type>)
						/* info: increment size after each construct
						   if throw, size reflects the number of valid elements */
						++_size;
				}

				if constexpr (xns::is_nothrow_copy_constructible<value_type>)
					// update size
					_size = other._size;

				// return self reference
				return *this;
			}

			/* copy assignment operator (trivially copyable) */
			auto operator=(const self& other) -> self& requires (xns::is_trivially_copyable<value_type>) {

				// check for self-assignment
				if (this == &other)
					return *this;

				// destroy elements
				_clear();

				// deallocate memory
				allocator::deallocate(_data); /* info: no nullptr check */

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
				allocator::deallocate(_data); /* info: no nullptr check */

				// move other members
				_data   = other._data;
				_capacity = other._capacity;
				_size     = other._size;

				// invalidate other
				other._init();

				return *this;
			}

			/* subscript operator */
			inline auto operator[](const size_type index) noexcept -> mut_ref {
				return _data[index];
			}

			/* const subscript operator */
			inline auto operator[](const size_type index) const noexcept -> const_ref {
				return _data[index];
			}

			/* at */
			auto at(const size_type index) noexcept -> mut_ref {
				return _data[index];
			}

			/* const at */
			auto at(const size_type index) const noexcept -> const_ref {
				return _data[index];
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
				return *_data;
			}

			/* const front */
			inline auto front(void) const noexcept -> const_ref {
				return *_data;
			}

			/* back */
			inline auto back(void) noexcept -> mut_ref {
				return _data[_size - 1];
			}

			/* const back */
			inline auto back(void) const noexcept -> const_ref {
				return _data[_size - 1];
			}

			/* data */
			inline auto data(void) noexcept -> mut_ptr {
				return _data;
			}

			/* const data */
			inline auto data(void) const noexcept -> const_ptr {
				return _data;
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
						allocator::construct(_data + i);
				}

				// inferior size
				else
					// destroy only non-trivially destructible types
					if constexpr (not xns::is_trivially_destructible<value_type>)

						// destroy excess elements (if not equal size)
						for (size_type i = size; i < _size; ++i)
							allocator::destroy(_data + i);

				// update size
				_size = size;
			}



			// -- public modifiers --------------------------------------------

			/* clear */
			auto clear(void) noexcept(xns::is_nothrow_destructible<value_type>) -> void {

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

				if constexpr (not xns::is_nothrow_constructible<value_type, A...>) {
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


					if constexpr (xns::is_trivially_copyable<value_type>)
						::memmove(_data + pos + 1,           // destination
								  _data + pos,               // source
								   (_size - pos) * sizeof(value_type)); // size

					else
						if constexpr (xns::is_nothrow_move_constructible<value_type>
								   && xns::is_nothrow_destructible<value_type>) {

							// move construct last element
							allocator::construct(_data + _size, xns::move(_data[_size - 1]));

							/* info: it is better for performance
									 to destroy and move construct than move assign */

							// move elements
							for (size_type i = _size - 1; i > pos; --i) {
								allocator::destroy(_data + i);
								allocator::construct(_data + i, xns::move(_data[i - 1]));
							}
						}
						else
							static_assert(xns::always_false<value_type>, "vector, emplace not supports throw move operations");

					// construct new element in place
					allocator::construct(_data + pos,
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
				allocator::construct(_data + _size,
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
				allocator::construct(_data + _size,
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
				if constexpr (not xns::is_trivially_destructible<value_type>)
					allocator::destroy(_data + --_size);
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
					_data[x] = xns::move(_data[x - 1]);
				}

				// increment size
				++_size;

				allocator::destroy(_data + pos);
				// copy or move value (need to check if U is nothrow copy constructible or nothrow move constructible) !!!
				allocator::construct(_data + pos, xns::forward<U>(value));
				
				//_data[pos] = xns::forward<U>(value);
			}


			/* erase */
			inline auto erase(const iterator& pos) noexcept -> void {
				// check position
				if (pos._ptr < _data) { return; }
				// compute position (pointers subtraction gives a signed type (ptrdiff_t))
				erase(static_cast<size_type>(pos._ptr - _data));
			}

			/* erase */
			auto erase(const size_type pos) noexcept -> void {
				// check position
				if (pos >= _size) { return; }
				// move elements
				for (size_type x = pos; x < (_size - 1); ++x) {
					// move element
					_data[x] = xns::move(_data[x + 1]);
				} // decrement size
				--_size;
				// destroy last element
				allocator::destroy(_data + _size);
			}






			/* swap */
			auto swap(self& other) noexcept -> void {
				// swap members
				xns::swap(_data,   other._data);
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
					if (((_data[x] != compare) && ...)) {
						// if no match, maybe move, check shift
						if (z != x) {
							// move element
							_data[z] = xns::move(_data[x]);
						} // increment z
						++z;
					}
				} // finaly, destroy elements and decrement size
				while (z < _size) { allocator::destroy(_data + --_size); }
			}

			/* move elements to the back of the vector if exists, else push back */
			auto to_back(const value_type& value) -> void {
				// loop over vector
				for (size_type x = 0; x < _size; ++x) {
					// check for match
					if (_data[x] == value) {
						// declare tmp
						value_type tmp = xns::move(_data[x]);
						// move elements
						for (size_type z = x; z < (_size - 1); ++z)
							_data[z] = xns::move(_data[z + 1]);
						// move tmp
						_data[_size - 1] = xns::move(tmp);
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
				static_assert(xns::is_comparable<U, value_type>,
					"type are not comparable in dichotomic search");

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
					if      (value > _data[middle]) { lower = middle + 1; }
					// check value is lower
					else if (value < _data[middle]) { upper = middle - 1; }
					// else value is equal
					else    { return self::iterator(_data + middle);            }
				} // not found
				return self::iterator(_data + _size);

			}

			/* dichotomic insert */
			auto dichotomic_insert(const_ref value) -> void
				requires (xns::is_comparable<value_type>) {

				// check if U is comparable to value_type
				static_assert(is_comparable<value_type>,
					"type are not comparable in dichotomic insert");


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
					if (value > _data[middle]) { lower = middle + 1; }
					// check value is lower
					else if (value < _data[middle]) {

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
				_data   = nullptr;
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
			auto _reserve(const size_type capacity) -> void requires (not xns::is_trivially_copyable<value_type>) {

				// allocate memory
				mut_ptr tmp = allocator::allocate(capacity);

				// reconstruct elements
				for (size_type i = 0; i < _size; ++i) {
					allocator::construct(tmp + i, xns::move(_data[i]));
					allocator::destroy(_data + i);
				}

				// deallocate memory
				allocator::deallocate(_data); /* info: no nullptr check */

				// update members
				_capacity = capacity;
				  _data = tmp;
			}

			/* _reserve (trivially copyable) */
			auto _reserve(const size_type capacity) -> void requires (xns::is_trivially_copyable<value_type> == true) {

				// reallocate memory
				  _data = allocator::realloc(_data, capacity);
				_capacity = capacity;
			}

			/* clear */
			auto _clear(void) noexcept -> void {

				// destroy only non-trivially destructible types
				if constexpr (not xns::is_trivially_destructible<value_type>)

					// destroy elements
					for (size_type i = 0; i < _size; ++i)
						allocator::destroy(_data + i);
			}


	}; // class vector


	// -- V E C T O R  I T E R A T O R ----------------------------------------

	template <typename T, typename __alloc> template <bool C>
	class vector<T, __alloc>::vector_iterator final {


		// -- friends ---------------------------------------------------------

		/* other iterator as friend */
		template <bool D>
		friend class vector_iterator;

		/* vector as friend */
		friend class vector<T, __alloc>;


		private:

			// -- private constants -------------------------------------------

			/* iterator is const */
			static constexpr bool _const = C;


		public:

			// -- public types ------------------------------------------------

			/* list type */
			using vector_type = xns::vector<T, __alloc>;

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

#endif // XNS_VECTOR_HEADER
