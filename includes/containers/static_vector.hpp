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

#ifndef XNS_STATIC_VECTOR_HEADER
#define XNS_STATIC_VECTOR_HEADER

#include "type_traits/type_operations/forward.hpp"
#include "type_traits/type_operations/move.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S T A T I C  V E C T O R --------------------------------------------

	template <typename T, decltype(sizeof(0)) N>
	class static_vector {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::static_vector<T, N>;

			/* value type */
			using value_type = T;

			/* size type */
			using size_type  = decltype(N);

			/* mutable reference type */
			using mut_ref    = T&;

			/* constant reference type */
			using const_ref  = const T&;

			/* mutable pointer type */
			using mut_ptr    = T*;

			/* constant pointer type */
			using const_ptr  = const T*;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr static_vector(void) noexcept
			: _data{}, _size{0} {
			}

			/* copy constructor */
			constexpr static_vector(const self& other) noexcept
			: _data{}, _size{other._size} {

				// cast data to pointer type
				mut_ptr sdata = reinterpret_cast<mut_ptr>(_data);
				mut_ptr odata = reinterpret_cast<mut_ptr>(other._data);

				// loop over objects
				for (size_type i = 0; i < _size; ++i)
					// call copy constructor
					new(sdata + i) T{odata[i]};
			}

			/* move constructor */
			constexpr static_vector(self&& other) noexcept
			: _data{}, _size{other._size} {

				// cast data to pointer type
				mut_ptr sdata = reinterpret_cast<mut_ptr>(_data);
				mut_ptr odata = reinterpret_cast<mut_ptr>(other._data);

				// loop over objects
				for (size_type i = 0; i < _size; ++i) {
					// call move constructor
					new(sdata + i) T{xns::move(odata[i])};
					// call destructor
					odata[i].~T();
				}

				// reset other size
				other._size = 0;
			}

			/* destructor */
			~static_vector(void) noexcept {

				// cast data to pointer type
				mut_ptr data = reinterpret_cast<mut_ptr>(_data);

				// loop over objects
				for (size_type i = 0; i < _size; ++i)
					// call destructor
					data[i].~T();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self& other) noexcept -> self& {
				// check for self-assignment
				if (this == &other)
					return *this;

				// cast data to pointer type
				mut_ptr sdata = reinterpret_cast<mut_ptr>(_data);
				mut_ptr odata = reinterpret_cast<mut_ptr>(other._data);


				// clear current data
				for (size_type i = 0; i < _size; ++i)
					// call destructor
					sdata[i].~T();

				// loop over objects
				for (size_type i = 0; i < other._size; ++i)
					// call copy constructor
					new(sdata + i) T{odata[i]};

				// set size
				_size = other._size;

				// return self reference
				return *this;
			}

			/* move assignment operator */
			constexpr auto operator=(self&& other) noexcept -> self& {

				// check for self-assignment
				if (this == &other)
					return *this;

				// cast data to pointer type
				mut_ptr sdata = reinterpret_cast<mut_ptr>(_data);
				mut_ptr odata = reinterpret_cast<mut_ptr>(other._data);

				// clear current data
				for (size_type i = 0; i < _size; ++i)
					// call destructor
					sdata[i].~T();

				// loop over objects
				for (size_type i = 0; i < other._size; ++i) {
					// call move constructor
					new(sdata + i) T{xns::move(odata[i])};
					// call destructor
					odata[i].~T();
				}

				// set size
				_size = other._size;

				// reset other size
				other._size = 0;

				// return self reference
				return *this;
			}


			// -- public subscript operators ----------------------------------

			/* mutable subscript operator */
			constexpr auto operator[](size_type index) noexcept -> mut_ref {
				return *(reinterpret_cast<mut_ptr>(_data) + index);
			}

			/* constant subscript operator */
			constexpr auto operator[](size_type index) const noexcept -> const_ref {
				return *(reinterpret_cast<const_ptr>(_data) + index);
			}


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			constexpr auto capacity(void) const noexcept -> size_type {
				return N;
			}

			/* data */
			constexpr auto data(void) noexcept -> mut_ptr {
				return reinterpret_cast<mut_ptr>(_data);
			}

			/* data */
			constexpr auto data(void) const noexcept -> const_ptr {
				return reinterpret_cast<const_ptr>(_data);
			}


			// -- public modifiers --------------------------------------------

			/* push back */
			constexpr auto push_back(const_ref value) noexcept(/* ... */true) -> void {

				// check if size is less than capacity
				if (_size == N)
					return;

				// cast data to pointer type
				mut_ptr data = reinterpret_cast<mut_ptr>(_data);

				// call copy constructor
				new(data + _size) T{value};

				// increment size
				++_size;
			}

			/* push back (move) */
			constexpr auto push_back(T&& value) noexcept(/* ... */true) -> void {

				// check if size is less than capacity
				if (_size == N)
					return;

				// cast data to pointer type
				mut_ptr data = reinterpret_cast<mut_ptr>(_data);

				// call move constructor
				new(data + _size) T{xns::move(value)};

				// increment size
				++_size;
			}

			/* emplace back */
			template <typename... A>
			constexpr auto emplace_back(A&&... args) noexcept(/* ... */true) -> void {

				// check if size is less than capacity
				if (_size == N)
					return;

				// cast data to pointer type
				mut_ptr data = reinterpret_cast<mut_ptr>(_data);

				// call constructor
				new(data + _size) T{xns::forward<A>(args)...};

				// increment size
				++_size;
			}

			/* pop back */
			constexpr auto pop_back(void) noexcept(/* ... */true) -> void {

				// check if size is zero
				if (_size == 0)
					return;

				// cast data to pointer type
				mut_ptr data = reinterpret_cast<mut_ptr>(_data);

				// call destructor
				data[_size - 1].~T();

				// decrement size
				--_size;
			}

			/* clear */
			constexpr auto clear(void) noexcept -> void {

				// cast data to pointer type
				mut_ptr data = reinterpret_cast<mut_ptr>(_data);

				// loop over objects
				for (size_type i = 0; i < _size; ++i)
					// call destructor
					data[i].~T();

				// reset size
				_size = 0;
			}


		private:

			// -- private members ---------------------------------------------

			/* data */
			unsigned char _data[sizeof(T) * N];

			/* size */
			size_type _size;

	}; // class static_vector

} // namespace xns

#endif // XNS_STATIC_VECTOR_HEADER
