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

#include "xns/type_traits/type_operations/forward.hpp"
#include "xns/type_traits/type_operations/move.hpp"

#include "xns/type_traits/type_properties/is_trivially_copyable.hpp"
#include "xns/type_traits/supported_operations/is_trivially_destructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_destructible.hpp"

#include "xns/memory/memcpy.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S T A T I C  V E C T O R --------------------------------------------

	template <typename ___type, decltype(sizeof(0)) ___size>
	class static_vector {


		// -- assertions ------------------------------------------------------

		/* assert nothrow destructible */
		static_assert(xns::is_nothrow_destructible<___type>,
					"value type must be nothrow destructible");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::static_vector<___type, ___size>;

			/* value type */
			using value_type = ___type;

			/* size type */
			using size_type  = decltype(___size);

			/* mutable reference type */
			using mut_ref    = value_type&;

			/* constant reference type */
			using const_ref  = const value_type&;

			/* mutable pointer type */
			using mut_ptr    = value_type*;

			/* constant pointer type */
			using const_ptr  = const value_type*;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr static_vector(void) noexcept
			: _data{}, _size{0U} {
			}

			/* copy constructor */
			constexpr static_vector(const self& other)
				noexcept(xns::is_nothrow_copy_constructible<value_type>)
			: _data{}, _size{other._size} {

				// trivial copy
				if constexpr (xns::is_trivially_copyable<value_type>) {
					// call memcpy
					xns::memcpy(_data, other._data, sizeof(value_type) * _size);
				}

				// non-trivial copy
				else {

					// cast data to pointer type
					auto sdata = reinterpret_cast<mut_ptr>(_data);
					auto odata = reinterpret_cast<const_ptr>(other._data);

					// nothrow copy constructible
					if constexpr (xns::is_nothrow_copy_constructible<value_type>) {

						// loop over objects
						for (size_type i = 0U; i < _size; ++i)
							// call copy constructor
							::new((void*)(sdata + i)) value_type{odata[i]};

					}

					// throw copy constructible
					else {

						size_type i = 0U;

						try {
							// loop over objects
							for (; i < _size; ++i)
								// call copy constructor
								::new((void*)(sdata + i)) value_type{odata[i]};
						}
						catch (...) {
							// assign size
							_size = i;
							// re-throws
							throw;
						}

					}

				}
			}

			/* move constructor */
			// NOT FINISHED !!!
			constexpr static_vector(self&& other)
				noexcept(xns::is_nothrow_move_constructible<value_type>)
			: _data{}, _size{other._size} {

				// cast data to pointer type
				auto sdata = reinterpret_cast<mut_ptr>(_data);
				auto odata = reinterpret_cast<mut_ptr>(other._data);

				// loop over objects
				for (size_type i = 0; i < _size; ++i) {
					// call move constructor
					new(sdata + i) value_type{xns::move(odata[i])};
					// call destructor
					odata[i].~value_type();
				}

				// reset other size
				other._size = 0;
			}

			/* destructor */
			~static_vector(void) noexcept {

				// not trivially destructible
				if (not xns::is_trivially_destructible<value_type>) {

					// loop over objects
					for (size_type i = 0; i < _size; ++i)
						// call destructor
						reinterpret_cast<mut_ptr>(_data)[i].~value_type();
				}
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self& other) noexcept -> self&
				requires (xns::is_trivially_copyable<value_type>) {

				// no need to check for self-assignment since memcpy is safe

				// call memcpy
				xns::memcpy(_data, other._data, sizeof(value_type) * _size);

				// set size
				_size = other._size;

				return *this;
			}

			/* copy assignment operator */
			constexpr auto operator=(const self& other)
				noexcept(xns::is_nothrow_copy_constructible<value_type>) -> self&
				requires (not xns::is_trivially_copyable<value_type>) {

				// check for self-assignment
				if (this == &other)
					return *this;

				// non-trivially destructible
				if constexpr (not xns::is_trivially_destructible<value_type>) {
					// destruct objects
					_non_trivial_destroy();
				}

				// nothrow copy constructible
				if constexpr (xns::is_nothrow_copy_constructible<value_type>) {

					// loop over objects
					for (size_type i = 0; i < other._size; ++i)
						// call copy constructor
						::new((void*)(reinterpret_cast<mut_ptr>(_data) + i))
							value_type{reinterpret_cast<const_ptr>(other._data)[i]};

					// set size
					_size = other._size;
				}
				else {

					size_type i = 0U;

					try {
						// loop over objects
						for (; i < other._size; ++i)
							// call copy constructor
							::new((void*)(reinterpret_cast<mut_ptr>(_data) + i))
								value_type{reinterpret_cast<const_ptr>(other._data)[i]};
					}
					catch (...) {
						// assign size
						_size = i;
						// re-throws
						throw;
					}
				}

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
					sdata[i].~value_type();

				// loop over objects
				for (size_type i = 0; i < other._size; ++i) {
					// call move constructor
					new(sdata + i) value_type{xns::move(odata[i])};
					// call destructor
					odata[i].~value_type();
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
			constexpr auto operator[](const size_type index) noexcept -> mut_ref {
				return (reinterpret_cast<mut_ptr>(_data))[index];
			}

			/* constant subscript operator */
			constexpr auto operator[](const size_type index) const noexcept -> const_ref {
				return (reinterpret_cast<const_ptr>(_data))[index];
			}


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			constexpr auto capacity(void) const noexcept -> size_type {
				return ___size;
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
			constexpr auto push_back(const_ref value)
				noexcept(xns::is_nothrow_copy_constructible<value_type>) -> void {

				// check if size is less than capacity
				if (_size == ___size)
					return;

				// call copy constructor
				::new((void*)(reinterpret_cast<mut_ptr>(_data) + _size)) value_type{value};

				// increment size
				++_size;
			}

			/* push back (move) */
			constexpr auto push_back(value_type&& value)
				noexcept(xns::is_nothrow_move_constructible<value_type>) -> void {

				// check if size is less than capacity
				if (_size == ___size)
					return;

				// call move constructor
				::new((void*)(reinterpret_cast<mut_ptr>(_data) + _size)) value_type{xns::move(value)};

				// increment size
				++_size;
			}

			/* emplace back */
			template <typename... ___params>
			constexpr auto emplace_back(___params&&... args)
				noexcept(xns::is_nothrow_constructible<value_type, ___params...>) -> void {

				// check if size is less than capacity
				if (_size == ___size)
					return;

				// call constructor
				::new((void*)(reinterpret_cast<mut_ptr>(_data) + _size)) value_type{xns::forward<___params>(args)...};

				// increment size
				++_size;
			}

			/* pop back */
			constexpr auto pop_back(void) noexcept -> void {

				// trivially destructible
				if constexpr (xns::is_trivially_destructible<value_type>) {
					// decrement size
					_size -= (_size > 0U);
				}

				// non-trivially destructible
				else {
					// check if size is zero
					if (_size == 0U)
						return;
					// call destructor
					reinterpret_cast<mut_ptr>(_data)[--_size].~value_type();
				}
			}

			/* clear */
			constexpr auto clear(void) noexcept -> void {

				// non-trivially destructible
				if constexpr (not xns::is_trivially_destructible<value_type>) {
					// destruct objects
					_non_trivial_destroy();
				}
				// reset size
				_size = 0U;
			}


		private:

			// -- private methods ---------------------------------------------

			/* non trivial destroy */
			auto _non_trivial_destroy(void) noexcept -> void {

				// loop over objects
				for (size_type i = 0; i < _size; ++i)
					// call destructor
					reinterpret_cast<mut_ptr>(_data)[i].~value_type();
			}


			// -- private members ---------------------------------------------

			/* data */
			unsigned char _data[sizeof(value_type) * ___size];

			/* size */
			size_type _size;

	}; // class static_vector

} // namespace xns

#endif // XNS_STATIC_VECTOR_HEADER
