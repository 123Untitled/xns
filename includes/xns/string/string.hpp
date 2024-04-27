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

#ifndef XNS_STRING_HEADER
#define XNS_STRING_HEADER

// global includes
#include <iostream>
#include <iomanip>
#include <unistd.h>

// local includes
#include "xns/type_traits/types.hpp"
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_categories/is_char.hpp"
#include "xns/type_traits/type_properties/is_unsigned.hpp"
#include "xns/type_traits/type_properties/is_signed.hpp"

#include "xns/other/char_traits.hpp"

#include "xns/memory/memcpy.hpp"
#include "xns/memory/memset.hpp"
#include "xns/memory/memmove.hpp"

#include "xns/string/strcmp.hpp"
#include "xns/string/strncmp.hpp"
#include "xns/string/string_utils.hpp"
#include "xns/string/strlen.hpp"


#include "xns/utility/swap.hpp"

#include "xns/containers/list.hpp"
#include "xns/containers/tuple.hpp"
#include "xns/containers/vector.hpp"
#include "xns/containers/array.hpp"

#include "xns/memory/allocator.hpp"
#include "xns/utility/numeric_limits.hpp"



#include "xns/other/char_traits.hpp"


// strncmp
#include <cstring>


#include "xns/type_traits/other/string_literal.hpp"





// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- forward declarations ------------------------------------------------

	/* basic string */
	template <typename>
	class basic_string;

	/* basic string view */
	template <typename>
	class basic_string_view;


	/* c-string ascii type */
	using string         = xns::basic_string<char>;

	/* wide string type */
	using wstring        = xns::basic_string<wchar_t>;

	/* utf-8 string type */
	using u8string       = xns::basic_string<char8_t>;

	/* utf-16 string type */
	using u16string      = xns::basic_string<char16_t>;

	/* utf-32 string type */
	using u32string      = xns::basic_string<char32_t>;


	/* c-string ascii type */
	using string_view    = xns::basic_string_view<char>;

	/* wide string type */
	using wstring_view   = xns::basic_string_view<wchar_t>;

	/* utf-8 string type */
	using u8string_view  = xns::basic_string_view<char8_t>;

	/* utf-16 string type */
	using u16string_view = xns::basic_string_view<char16_t>;

	/* utf-32 string type */
	using u32string_view = xns::basic_string_view<char32_t>;




	// -- I S  S T R I N G  ---------------------------------------------------

	/* is string concept */
	template <typename ___type>
	concept is_string = xns::is_same<___type, xns::basic_string     <typename ___type::value_type>>
					 || xns::is_same<___type, xns::basic_string_view<typename ___type::value_type>>;


	/* basic string iterator */
	template <typename, bool>
	class basic_string_iterator;



	// -- B A S I C  S T R I N G ----------------------------------------------

	/* string class */
	template <typename ___char>
	class basic_string final {


		// -- friends -----------------------------------------------------

		/* output stream operator as friend */
		template <typename ___tp>
		friend std::ostream& operator<<(std::ostream&, const xns::basic_string<___tp>&);


		// -- assertions ------------------------------------------------------

		/* check if T is a character type */
		static_assert(xns::is_char<___char>,
				"basic_string: requires a character type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self            = xns::basic_string<___char>;

			/* traits type */
			using traits_type     = xns::char_traits<___char>;

			/* value type */
			using value_type      = traits_type::char_type;

			/* allocator type */
			using allocator_type  = xns::allocator<value_type>; // ___alloc

			/* size type */
			using size_type       = xns::allocator_traits<allocator_type>::size_type;

			/* difference type */
			using difference_type = xns::allocator_traits<allocator_type>::difference_type;

			/* reference type */
			using reference       = traits_type::reference;

			/* const reference type */
			using const_reference = traits_type::const_reference;

			/* pointer type */
			using pointer         = xns::allocator_traits<allocator_type>::pointer;

			/* const pointer type */
			using const_pointer   = xns::allocator_traits<allocator_type>::const_pointer;

			/* iterator type */
			using iterator        = xns::basic_string_iterator<value_type, false>;

			/* const iterator type */
 			using const_iterator  = xns::basic_string_iterator<value_type, true>;

			/* string view type */
			using view_type = xns::basic_string_view<value_type>;




			/* comparison type */
			using signed_type = xns::s64;
			/* allocator type */
			//using allocator = xns::allocator<value_type>;


		private:

			// -- private types -----------------------------------------------

			/* allocator traits type */
			using ___alloc_traits = xns::allocator_traits<allocator_type>;


			// -- private members ---------------------------------------------

			/* allocator */
			[[no_unique_address]] allocator_type _allocator;

			/* pointer */
			pointer _data;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			basic_string(void)
			: _allocator{}, _data{_allocate(0)}, _capacity{0U}, _size{0U} {
				_null_terminator();
			}

			/* allocator constructor */
			explicit basic_string(const allocator_type& ___at)
			: _allocator{___at}, _data{_allocate(0)}, _capacity{0U}, _size{0U} {
			}

			/* null-terminated string constructor */
			explicit basic_string(const_pointer ___st,
								  const allocator_type& ___at = allocator_type{})
			: _allocator{___at}, _data{nullptr}, _capacity{traits_type::length(___st)}, _size{_capacity} {
				// allocate memory
				_data = _allocate(_capacity);
				_null_terminator();
				traits_type::copy(_data, ___st, _size);
			}

			/* buffer constructor */
			constexpr basic_string(const_pointer ___st, const size_type ___sz,
								   const allocator_type& ___at = allocator_type{})
			: _allocator{___at}, _data{nullptr}, _capacity{___sz}, _size{___sz} {
				// allocate memory
				_data = _allocate(_size);
				_null_terminator();
				traits_type::copy(_data, ___st, _size);
			}

			/* fill constructor */
			constexpr basic_string(const size_type ___sz, const value_type ___ch,
								   const allocator_type& ___at = allocator_type{})
			: _allocator{___at}, _data{_allocate(___sz)}, _capacity{___sz}, _size{___sz}  {
				_null_terminator();
				traits_type::fill(_data, _size, ___ch);
			}

			/* string view constructor */
			constexpr explicit basic_string(const view_type& ___vw,
											const allocator_type& ___at = allocator_type{})
			: basic_string{___at, ___vw.data(), ___vw.size()} {
			}

			/* copy constructor */
			constexpr basic_string(const self& other)
			: basic_string{other._data, other._size} {
			}

			/* copy constructor */
			constexpr basic_string(const self& other, const allocator_type& ___at)
			: basic_string{___at, other._data, other._size} {
			}

			/* move constructor */
			constexpr basic_string(self&& other) noexcept
			: _allocator{xns::move(other._allocator)}, _data{other._data}, _capacity{other._capacity}, _size{other._size} {
				other._init();
			}

			/* move constructor */
			constexpr basic_string(self&& other, const allocator_type& ___at)
			: _allocator{___at}, _data{other._data}, _capacity{other._capacity}, _size{other._size} {
				other._init();
			}

			/* destructor */
			~basic_string(void) noexcept {
				_deallocate();
			}



			// -- public assignments ------------------------------------------

			/* string view assignment */
			auto assign(const view_type& view) -> void {
				assign(view.data(), view.size());
			}

			/* null-terminated string assignment */
			auto assign(const_pointer str) -> void {
				assign(str, xns::strlen(str));
			}

			/* buffer assignment */
			auto assign(const_pointer str, const size_type size) -> void {
				// check if size or pointer is null
				if (not size || not str) { clear(); return; }
				// check if capacity is sufficient
				if (_capacity < size) {
					// resize the string
					reallocate(size);
				} // copy string
				traits_type::copy(_data, str, size);
				// set nullchar
				_null_terminator(size);
			}

			/* fill assignment */
			auto assign(const value_type character, const size_type size) -> void {
				// check if size is zero
				if (not size) { clear(); return; }
				// check if capacity is sufficient
				if (_capacity < size) {
					// resize the string
					reallocate(size);
				} // fill string
				traits_type::fill(_data, size, character);
				// set nullchar
				_null_terminator(size);
			}


			/* copy assignment */
			auto assign(const self& other) -> void {
				// check for self-assignment
				if (this == &other) { return; }
				// check for other size
				if (other.empty()) { clear(); return; }
				// check if capacity is sufficient
				if (_capacity < other._size) {
					// reallocate memory
					reallocate(other._size);
				} // copy string
				traits_type::copy(_data, other._data, other._size);
				// set nullchar
				_null_terminator(other._size);
			}

			/* move assignment */
			auto assign(self&& other) noexcept -> void {
				// check for self-assignment
				if (this == &other)
					return;
				// deallocate memory
				if (_data)
					___alloc_traits::deallocate(_allocator, _data, _capacity);

				_copy_members(other);
				other._init();
			}




			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) -> self& {
				assign(other);
				return *this;
			}

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				assign(xns::move(other));
				return *this;
			}

			/* string view assignment operator */
			auto operator=(const view_type& view) -> self& {
				assign(view);
				return *this;
			}

			/* null-terminated string assignment operator */
			auto operator=(const_pointer str) -> self& {
				assign(str, traits_type::length(str));
				return *this;
			}

			/* character assignment operator */
			auto operator=(const value_type character) -> self& {
				assign(character, 1);
				return *this;
			}



			// -- public comparison operators ---------------------------------

			// -- C O M P A R I S O N -----------------------------------------

			// WARNING: constructor not allow empty string
			// so comparison with empty string is not equal...
			// need to fix this.

			/* string compare */
			auto compare(const self& ___ot) const noexcept -> signed_type {
				return traits_type::compare(_data, ___ot._data);
			}

			/* view compare */
			auto compare(const view_type& ___vw) const noexcept -> signed_type {
				return _size == ___vw.size()
				&& traits_type::compare(_data, ___vw.data(), _size) == 0;
			}

			/* null-terminated string compare */
			auto compare(const_pointer ___st) const noexcept -> signed_type {
				return traits_type::compare(_data, ___st);
			}

			/* string size compare */
			auto compare(const self& ___st, const size_type ___sz) const noexcept -> signed_type {
				return traits_type::compare(_data, ___st._data, ___sz);
			}

			/* null-terminated string size compare */
			auto compare(const_pointer str, size_type size) const noexcept -> signed_type {
				return _size == size && traits_type::compare(_data, str, size) == 0;
			}


			/* view equality operator */
			auto operator==(const view_type& ___vw) const noexcept -> bool {
				return _size == ___vw.size()
					&& traits_type::compare(_data, ___vw.data(), ___vw.size()) == 0;
			}

			/* null-terminated string equality operator */
			auto operator==(const_pointer ___st) const noexcept -> bool {
				return traits_type::compare(_data, ___st) == 0;
			}


			/* equality operator */
			auto operator==(const self& ___ot) const noexcept -> bool {
				return traits_type::compare(_data, ___ot._data) == 0;
			}

			/* less than */
			auto operator<(const self& ___st) const noexcept -> bool {
				return traits_type::compare(_data, ___st._data) < 0;
			}

			/* less than or equal */
			auto operator<=(const self& ___st) const noexcept -> bool {
				return traits_type::compare(_data, ___st._data) <= 0;
			}

			/* greater than */
			auto operator>(const self& ___st) const noexcept -> bool {
				return traits_type::compare(_data, ___st._data) > 0;
			}

			/* greater than or equal */
			auto operator>=(const self& ___st) const noexcept -> bool {
				return traits_type::compare(_data, ___st._data) >= 0;
			}



			// -- public iterators --------------------------------------------

			/* begin */
			auto begin(void) noexcept -> iterator {
				return iterator{_data};
			}

			/* end */
			auto end(void) noexcept -> iterator {
				return iterator{_data + _size};
			}

			/* const begin */
			auto begin(void) const noexcept -> const_iterator {
				return const_iterator{_data};
			}

			/* const end */
			auto end(void) const noexcept -> const_iterator {
				return const_iterator{_data + _size};
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			auto operator[](const size_type ___idx) noexcept -> reference {
				return _data[___idx];
			}

			/* const subscript operator */
			auto operator[](const size_type ___idx) const noexcept -> const_reference {
				return _data[___idx];
			}


			// -- public accessors --------------------------------------------

			/* empty */
			auto empty(void) const noexcept -> bool {
				return _size == 0;
			}

			/* length */
			auto length(void) const noexcept -> size_type {
				return _size;
			}

			/* size */
			auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			auto capacity(void) const noexcept -> size_type {
				return _capacity;
			}

			/* front */
			auto front(void) noexcept -> reference {
				return _data[0];
			}

			/* const front */
			auto front(void) const noexcept -> const_reference {
				return _data[0];
			}

			/* back */
			auto back(void) noexcept -> reference {
				return _data[_size - 1];
			}

			/* const back */
			auto back(void) const noexcept -> const_reference {
				return _data[_size - 1];
			}

			/* data */
			auto data(void) noexcept -> pointer {
				return _data;
			}

			/* const data */
			auto data(void) const noexcept -> const_pointer {
				return _data;
			}


			// INFO: in reserve(), does user need to know that nullchar is not included in available space?
			// answer: no, user should not know that nullchar is not included in available space


			/* get subview */
			auto subview(const size_type pos, const size_type size) const noexcept -> view_type {
				// check if index is out of bounds
				if (_data == nullptr || pos < _size)
					return view_type{};

				// return subview
				return (pos + size) < _size ? view_type{_data + pos, size}
											: view_type{_data + pos, _size - pos}; // return clamped subview
			}

			/* get substring */
			auto substr(const size_type pos, const size_type size) const -> self {
				// check if index is out of bounds
				if (_data != nullptr && pos < _size) {
					// return substring
					return pos + size < _size
							? self{_data + pos, size}
							// return clamped substring
							: self{_data + pos, _size - pos};
				} // return default substring
				return self{};
			}


			// -- public modifiers --------------------------------------------

			/* clear */
			auto clear(void) noexcept -> void {
				if (_data) { _null_terminator(0); }
			}

			/* swap */
			auto swap(self& other) noexcept -> void {
				// swap members
				xns::swap(_data,      other._data);
				xns::swap(_size,     other._size);
				xns::swap(_capacity, other._capacity);
			}

			/* reserve */
			auto reserve(const size_type request) -> void {
				// check if size is greater than capacity
				if (request > _capacity) {
					// reallocate memory
					reallocate(request);
				}
			}

			/* resize */
			void resize(const size_type request) {
				// check if size is greater than capacity
				if (request > _capacity) {
					reallocate(request);
				}
				if (_data) {
					// set nullchar
					_null_terminator(request);
				}
			}





			/* multiple string append */
			template <typename... ___params>
			auto append(___params&&... ___strs) -> self& {

				if constexpr (sizeof...(___strs) > 0) {

					// compute size
					const auto ___sz = (_compute_size(___strs) + ...);

					// check if there is enough space
					if (___sz > available())
						reallocate(try_expand(_size + ___sz));

					// offset
					size_type ___of = _size;

					// append strings
					(_append_multi(___of, ___strs), ...);

					// set nullchar
					_null_terminator(_size + ___sz);

				} return *this;
			}




			/* fill insert */
			auto insert(size_type index, const value_type character, const size_type count = 1) -> self& {
				// check count is not null
				if (!count) { return *this; }

				index = index > _size ? _size : index;

				size_type required = _size + count;

				// check if there is enough space
				if (count > available()) {
					// resize the string
					reallocate(try_expand(required));
				}

				size_type range = _size - index;

				// loop through new memory space and shift characters
				for (size_type x = 0, z = _size - 1; x < range; ++x, --z) {
					// set character
					_data[z + count] = _data[z];
				}

				size_type to = index + count;
				// loop through new memory space and set characters
				for (size_type x = index; x < to; ++x) {
					// set character
					_data[x] = character;
				}

				// set nullchar
				_null_terminator(required);

				// return self reference
				return *this;
			}


			/* buffer insert */
			auto insert(size_type index, const_pointer str, const size_type size) -> self& {
				// WARNING: not implemented

				// check if size or pointer is null
				if (!size || !str) { return *this; }

				// check if index is valid
				index = index > _size ? _size : index;

				const auto required = _size + size;

				// check if there is enough space
				if (size > available()) {
					// resize the string
					reallocate(try_expand(required));
				}
				// compute offset
				const auto offset = _data + index;
				// move characters
				xns::memmove(offset + size,
							 offset, _size - index);
				// copy string
				xns::memcpy(offset, str, size);
				// set nullchar
				_null_terminator(required);
				// return self reference
				return *this;
			}

			/* string insert */
			auto insert(const size_type index, const string& str) -> self& {
				// call buffer insert
				return insert(index, str._data, str._size);
			}

			/* null-terminated string insert */
			auto insert(const size_type index, const_pointer str) -> self& {
				// call buffer insert with size
				return insert(index, str, traits_type::length(str));
			}

			/* string view insert */
			auto insert(const size_type index, const view_type& view) -> self& {
				// call buffer insert with size
				return insert(index, view.data(), view.size());
			}




			/* erase */
			auto erase(const size_type ___idx) noexcept -> void {
				// check for valid index
				if (not (___idx < _size))
					return;
				// loop over string
				for (size_type i = ___idx; i < _size; ++i)
					_data[i] = _data[i + 1]; // nullchar will be shifted
				--_size;
			}

			/* erase range */
			auto erase(const size_type start, const size_type end) -> void {
				// check if index is valid and string is not null
				if (start <= end && end < _size && _data != nullptr) {

					const size_type shift = (end - start) + 1;
					// loop through string
					for (size_type x = start,
							  z = shift + x; z < _size; ++x, ++z) {
						// shift characters
						_data[x] = _data[z];
					}
					// decrement size
					_null_terminator(_size - shift);
				}
			}

			/* replace */
			auto replace(const size_type index, const size_type size, const_pointer str) -> void {
				// not implemented yet...
			}




			/* reverse */
			void reverse(void) {
				// check if string is not null
				if (not _size) { return; }
				// reverse string
				for (size_type x = 0, z = _size - 1; x < z; ++x, --z) {
					// swap characters
					xns::swap(_data[x], _data[z]);
				}
			}


		private:

			// -- private methods ---------------------------------------------

			/* available */
			auto available(void) const noexcept -> size_type {
				return _capacity - _size;
			}

			/* init */
			auto _init(void) noexcept -> void {
					_data = nullptr;
				_capacity = 0U;
					_size = 0U;
			}

			/* copy members */
			auto _copy_members(const self& ___ot) noexcept -> void {
				_data     = ___ot._data;
				_size     = ___ot._size;
				_capacity = ___ot._capacity;
			}

			/* set null terminator */
			auto _null_terminator(const size_type size) noexcept -> void {
				// update size
				_size = size;
				// set null character
				_data[size] = static_cast<value_type>(0);
			}

			/* set null terminator */
			auto _null_terminator(void) noexcept -> void {
				_data[_size] = static_cast<value_type>(0);
			}

			/* allocate */
			auto _allocate(const size_type ___req) -> pointer {
				// add one for null character
				return ___alloc_traits::allocate(_allocator, ___req + 1U);
			}

			/* deallocate */
			auto _deallocate(void) noexcept -> void {

				/* ptr always valid, except if fno-exceptions
				if (_data == nullptr)
					return;
				*/
				___alloc_traits::deallocate(_allocator, _data, _capacity + 1U);
			}

			/* realloc */
			auto reallocate(const size_type request) -> void {
				// reallocate memory
				//_data = xns::allocator<value_type>::realloc2(_data, request + 1U);
				// update capacity
				_capacity = request;
			}

			/* expand */
			auto expand(void) const noexcept -> size_type {
				return _capacity ? (_capacity << 2U) : 1U;
			}

			/* try expand */
			auto try_expand(const size_type request) const noexcept -> size_type {
				auto new_capacity = (_capacity << 1U);
				return request > new_capacity ? request : new_capacity;
			}

			/* self size */
			static constexpr auto _compute_size(const self& ___st) noexcept -> size_type {
				return ___st._size;
			}

			/* view size */
			static constexpr auto _compute_size(const view_type& ___vw) noexcept -> size_type {
				return ___vw.size();
			}

			/* char size */
			static constexpr auto _compute_size(const_reference ___ch) noexcept -> size_type {
				return 1U;
			}

			/* char array size */
			template <size_type ___sz>
			static constexpr auto _compute_size(const value_type (&)[___sz]) noexcept -> size_type {
				return ___sz - 1U; // assume null-terminated
			}

			/* self append */
			constexpr auto _append_multi(size_type& ___of, self& ___ot) noexcept -> void {
				traits_type::copy(_data + ___of, ___ot._data, ___ot._size);
				___of += ___ot._size;
			}

			/* view append */
			constexpr auto _append_multi(size_type& ___of, const view_type& ___vw) noexcept -> void {
				traits_type::copy(_data + ___of, ___vw.data(), ___vw.size());
				___of += ___vw.size();
			}

			/* char append */
			constexpr auto _append_multi(size_type& ___of, const_reference ___ch) noexcept -> void {
				traits_type::assign(_data[___of], ___ch);
				++___of;
			}

			/* char array append */
			template <size_type ___sz>
			constexpr auto _append_multi(size_type& ___of, const value_type (&___ar)[___sz]) noexcept -> void {
				traits_type::copy(_data + ___of, ___ar, ___sz - 1U);
				___of += ___sz - 1U;
			}

		public:

			// -- D E B U G ---------------------------------------------------

			/* debug string */
			void debug(void) const {
				if (_data) {
					if (_size) { std::cout << "string:   " << _data      << std::endl; }
					else { std::cout       << "string:   " << "empty"   << std::endl; }
				} else { std::cout         << "string:   " << "nullptr" << std::endl; }
				std::cout                  << "Size:     " << _size     << std::endl;
				std::cout                  << "Capacity: " << _capacity << std::endl;
			}


		public:

			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------




			/* to basic string (signed integer) */
			template <typename U>
			static auto to_basic_string(const U& vlue) -> xns::basic_string<value_type>
				// requirements
				requires(xns::is_signed<U> && xns::is_integral<U>) {

				U value = vlue;
				self str;

				str.reserve(xns::limits<U>::digits() + 1); // INFO: +1 for negative sign

				constexpr U type_min = xns::limits<U>::min();

				U base = 10;

				bool negative = false;

				size_type x = 0;

				// check negative
				if (value < 0) {
					// set negative flag
					negative = true;

					if (value == type_min) {
						// INFO: this is a special case
					}
					else {
						// inverse number
						value = -value;
					}
				}

				do {
					U rem = value % base;
					//_data[x] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
					str._data[x] = (value % 10) + '0';
					++x;
				} while ((value /= base));

				if (negative) { str._data[x++] = '-'; }

				str._null_terminator(x);
				// reverse all characters
				str.reverse();

				return str;
			}


		/* to basic string (unsigned integer) */
		template <typename U>
		static auto to_basic_string(const U& num) -> xns::basic_string<value_type>

			// requirements
			requires(xns::is_unsigned<U> && xns::is_integral<U>) {

			U number = num;

			self str;

			// debug !!!!
			//constexpr size_type size = 100;
			constexpr size_type size = xns::limits<U>::digits();
			//std::cout << "size: " << size << std::endl;
			//static_assert(size > 0, "size must be greater than zero");

			str._data = str._allocate(size);
			str._capacity = size;

			// declare iterator
			size_type x = 0;

			// loop through number
			do {
				str._data[x] = (number % 10) + '0';
				number /= 10;
				++x;
			} while (number);

			str._data[x] = static_cast<U>(0);
			str._size = x;

			// reverse all characters
			str.reverse();

			return str;
		}


		template <typename I>
		static bool to_integer(const self& str, I& value) requires(xns::is_integral<I>) {

			/* integer type */
			using integer       = xns::remove_cvref<I>;

			// index
			size_type x = 0;
			// negative flag
			int negative = 1;
			// reset value
			value = 0;

			// skip leading whitespace
			while (x < str.size() && xns::is_space(str[x])) {
				++x;
			}

			// check for sign
			if      (str[x] == '+') { ++x;                }
			else if (str[x] == '-') { ++x; negative = -1; }

			// check for required sign
			if constexpr (!xns::is_signed<I>) {
				if (negative < 0) { value = 0;
					return false;
				}
			}

			const constexpr integer max = xns::limits<integer>::max();

			// loop through digits
			while (x < str.size() && xns::is_digit(str[x])) {


				integer add = (str[x] - '0');

				// check for overflow
				integer test = (max - add) / 10;

				if (value > test) {
					value = negative > 0 ? max : xns::limits<integer>::min();
					return false;
				}

				// multiply by 10 and add digit
				value = (value * 10) + add;

				++x;
			}

			// skip trailing whitespace
			while (x < str.size() && xns::is_space(str[x])) { ++x; }

			if (x < str.size()) {
				value = 0;
				return false;
			}

			if constexpr (xns::is_signed<I>) {
				value *= negative;
			}

			return true;
		}



	}; // class basic_string



	/* deduction guide for null-terminated constructor */
	//template <typename T>
	//basic_string(const T*) -> basic_string<T>;



	/* to c-string ascii */
	template <typename T>
	auto to_string(const T& value) -> xns::string {
		return xns::string::to_basic_string<T>(value);
	}

	/* to wide string */
	template <typename T>
	auto to_wstring(const T& value) -> xns::wstring {
		return xns::wstring::to_basic_string<T>(value);
	}

	/* to utf-8 string */
	template <typename T>
	auto to_u8string(const T& value) -> xns::u8string {
		return xns::u8string::to_basic_string<T>(value);
	}

	/* to utf-16 string */
	template <typename T>
	auto to_u16string(const T& value) -> xns::u16string {
		return xns::u16string::to_basic_string<T>(value);
	}

	/* to utf-32 string */
	template <typename T>
	auto to_u32string(const T& value) -> xns::u32string {
		return xns::u32string::to_basic_string<T>(value);
	}






	// -- <<  O P E R A T O R  ------------------------------------------------

	/* output stream operator */
	template <typename ___type>
	inline std::ostream& operator<<(std::ostream& os, const xns::basic_string<___type>& str) {
			// check if string is null
			if (str._data) {
				// write string to os
				os.write(str._data, (long)str._size);
			}
			else { os.write("nullptr", 7); }
		return os;
	}


	// -- empty string --------------------------------------------------------

	/* empty string */
	template <typename ___char> requires(xns::is_same<___char, char>)
	consteval auto empty_string(void) noexcept -> const char* {
		return "";
	}

	/* empty string */
	template <typename ___char> requires(xns::is_same<___char, char8_t>)
	consteval auto empty_string(void) noexcept -> const char8_t* {
		return u8"";
	}

	/* empty string */
	template <typename ___char> requires(xns::is_same<___char, char16_t>)
	consteval auto empty_string(void) noexcept -> const char16_t* {
		return u"";
	}

	/* empty string */
	template <typename ___char> requires(xns::is_same<___char, char32_t>)
	consteval auto empty_string(void) noexcept -> const char32_t* {
		return U"";
	}

	/* empty string */
	template <typename ___char> requires(xns::is_same<___char, wchar_t>)
	consteval auto empty_string(void) noexcept -> const wchar_t* {
		return L"";
	}



	// -- B A S I C  S T R I N G  V I E W -------------------------------------

	template <typename ___type>
	class basic_string_view final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self            = xns::basic_string_view<___type>;

			/* character type */
			using value_type       = ___type;

			/* string type */
			using string_type     = xns::basic_string<value_type>;

			/* size type */
			using size_type       = string_type::size_type;

			/* comparison type */
			using signed_type     = xns::s64;

			/* const reference type */
			using const_reference       = const value_type&;

			/* const pointer type */
			using const_pointer       = const value_type*;


			// -- public constructors -----------------------------------------

			/* default constructor */
			constexpr basic_string_view(void) noexcept
			: _data{xns::empty_string<value_type>()}, _size{0U} {
			}

			/* pointer constructor */
			constexpr basic_string_view(const_pointer ___ptr) noexcept
			: _data{___ptr != nullptr ? ___ptr : xns::empty_string<value_type>()}, _size{xns::strlen(___ptr)} {
			}

			/* pointer and length constructor */
			constexpr basic_string_view(const_pointer ___ptr, const size_type ___sz) noexcept
			: _data{___ptr != nullptr ? ___ptr : xns::empty_string<value_type>()}, _size{_data ? ___sz : 0U} {
			}

			/* string constructor */
			constexpr basic_string_view(const string_type& str) noexcept
			: _data{str.data()}, _size{str.size()} {
			}

			/* copy constructor */
			constexpr basic_string_view(const self&) noexcept = default;

			/* move constructor */
			constexpr basic_string_view(self&&) noexcept = default;

			/* destructor */
			~basic_string_view(void) noexcept = default;


			// -- public modifiers --------------------------------------------

			/* pointer assignment */
			constexpr auto assign(const_pointer str) noexcept -> void {
				_data = str;
				_size = xns::strlen(str);
			}

			/* pointer and length assignment */
			constexpr auto assign(const_pointer str, const size_type size) noexcept -> void {
				_data = str;
				_size = size;
			}


			// -- public assignment operators ---------------------------------

			/* pointer assignment operator */
			constexpr auto operator=(const_pointer str) noexcept -> self& {
				assign(str);
				return *this;
			}

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			constexpr auto operator[](const size_type index) const noexcept -> const_reference {
				return _data[index];
			}


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* empty */
			constexpr auto empty(void) const noexcept -> bool {
				return _size == 0;
			}

			/* front */
			constexpr auto front(void) const noexcept -> const_reference {
				return *_data;
			}

			/* back */
			constexpr auto back(void) const noexcept -> const_reference {
				return _data[_size ? _size - 1 : 0];
			}

			/* data */
			constexpr auto data(void) const noexcept -> const_pointer {
				return _data;
			}


			// -- M O D I F I E R S -------------------------------------------

			/* remove prefix */
			constexpr void remove_prefix(const size_type size) noexcept {
				// check size
				if (size < _size) {
					// remove prefix
					_data  += size;
					_size -= size;
					return;
				} // else reset string
				_data = xns::empty_string<value_type>();
				_size = 0U;
			}

			/* remove suffix */
			constexpr void remove_suffix(const size_type size) noexcept {
				// check size
				if (size < _size) {
					// remove suffix
					_size -= size;
					return;
				} // else reset string
				_data = xns::empty_string<value_type>();
				_size = 0U;
			}


			/* null-terminated string compare */
			signed_type compare(const_pointer other) const {
				// compare nullptr-ness
				if (!_data)  { if (!other) { return 0; } return -1; }
				if (!other) { return 1; }

				size_type x = 0;

				// loop through strings
				while (x < _size) {
					// check for null terminator
					if (!other[x]) { return 1; }
					// compare characters
					if (_data[x] != other[x]) {
						// return difference
						return _data[x] < other[x] ? -1 : 1;
					} ++x;
				}
				// check for null terminator
				return other[x] ? -1 : 0;
			}

			/* string compare */
			template <xns::is_string ___string>
			signed_type compare(const ___string& other) const {

				// assert same character type
				static_assert(xns::is_same<value_type, typename ___string::value_type>,
					"): CAN'T COMPARE DIFFERENT STRING TYPES :(");

				// compare nullptr-ness
				// if (!_str)       { if (!other._str) { return 0; } return -1; }
				// if (!other._str) { return 1; }
				// this is not needed because the string or string view is never null

				// compare sizes
				/*if (_size != other._size) {
					// avoid overflow, can't just subtract
					return _size < other._size ? -1 : 1;
				}*/

				size_type x = 0;

				// loop through strings
				while (x < _size) {
					// compare characters
					if (_data[x] != other._data[x]) {
						// return difference
						return _data[x] < other._data[x] ? -1 : 1;
					} ++x;
				}

				// return equal
				return 0;
			}


			// -- comparison operators ----------------------------------------

			/* pointer comparison operator */
			constexpr auto operator==(const_pointer other) const noexcept -> bool {
				return compare(other) == 0;
			}

			/* equality operator */
			template <xns::is_string S>
			constexpr auto operator==(const S& other) const noexcept -> bool {
				return compare(other) == 0;
			}

			/* inequality operator */
			template <xns::is_string S>
			constexpr auto operator!=(const S& other) const noexcept -> bool {
				return compare(other) != 0;
			}

			/* less than operator */
			template <xns::is_string S>
			constexpr auto operator<(const S& other) const noexcept -> bool {
				return compare(other) < 0;
			}

			/* greater than operator */
			template <xns::is_string S>
			constexpr auto operator>(const S& other) const noexcept -> bool {
				return compare(other) > 0;
			}

			/* less than or equal to operator */
			template <xns::is_string S>
			constexpr auto operator<=(const S& other) const noexcept -> bool {
				return compare(other) <= 0;
			}

			/* greater than or equal to operator */
			template <xns::is_string S>
			constexpr auto operator>=(const S& other) const noexcept -> bool {
				return compare(other) >= 0;
			}



		private:

			// -- private members ---------------------------------------------

			/* data */
			const_pointer _data;

			/* size */
			size_type _size;

	}; // class basic_string_view



	/* deduction guide for null-terminated constructor */
	template <typename T>
	basic_string_view(const T*) -> basic_string_view<T>;


	inline std::ostream& operator<<(std::ostream& os, const xns::basic_string_view<char>& str) {
		// write string
		os.write(str.data(), (std::streamsize)str.size());
		// return stream
		return os;
	}



	// -- B A S I C  S T R I N G  I T E R A T O R -----------------------------

	/* basic string iterator */
	template <typename T, bool is_const>
	class basic_string_iterator {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::basic_string_iterator<T, is_const>;

			/* character type */
			using char_t = T;

			/* string type */
			using string_t = xns::basic_string<char_t>;

			/* reference type */
			using ref_t = typename xns::conditional<is_const, typename string_t::const_reference,
															  typename string_t::reference>;

			/* pointer type */
			using ptr_t = typename xns::conditional<is_const, typename string_t::const_pointer,
															  typename string_t::pointer>;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			basic_string_iterator(void) = delete;

			/* pointer constructor */
			constexpr basic_string_iterator(ptr_t ptr) noexcept
			: _ptr{ptr} {}

			/* copy constructor (non-const) */
			constexpr basic_string_iterator(const xns::basic_string_iterator<T, false>& other) noexcept
			: _ptr{other._ptr} {}

			/* copy constructor (const) */
			constexpr basic_string_iterator(const xns::basic_string_iterator<T, true>& other) noexcept
			: _ptr{other._ptr} {
				static_assert(is_const, "): CAN'T CONVERT NON-CONST TO CONST :(");
			}





			// -- public increment operators ----------------------------------

			/* prefix increment operator */
			constexpr self& operator++(void) noexcept {
				// increment pointer
				++_ptr;
				// return self reference
				return *this;
			}

			/* postfix increment operator */
			constexpr self operator++(int) noexcept {
				// copy self
				self copy{*this};
				// increment pointer
				++_ptr;
				// return copy
				return copy;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			constexpr bool operator==(const self& other) const noexcept {
				// return equality
				return _ptr == other._ptr;
			}

			/* inequality operator */
			constexpr bool operator!=(const self& other) const noexcept {
				// return inequality
				return _ptr != other._ptr;
			}


			// -- public accessors --------------------------------------------

			/* dereference operator */
			constexpr auto operator*(void) const noexcept -> ref_t {
				// return reference
				return *_ptr;
			}



		private:

			// -- private members ---------------------------------------------

			/* pointer */
			ptr_t _ptr;


	};







	template <xns::is_char T>
	auto char32_to(const xns::u32string& u32str) -> xns::basic_string<T> {

		// assertion
		static_assert(sizeof(T) == 1, "CHAR32_TO() ONLY SUPPORTS 8-BIT CHAR TYPES");

		// size alias
		using size_type = xns::u32string::size_type;

		// declare char string
		xns::string result;

		// reserve space
		result.reserve(u32str.size());

		//char* ptr = result.data();

		//xns::size_t i = 0;
		// loop over 32-bit chars
		for (xns::size_t _ = 0; _ < u32str.size(); ++_) {

			// get code point
			char32_t cp = u32str[_];

			// check for ascii
			if (cp < 0x80) {
				// append to result
				result.append(static_cast<char>(cp));
			}
			// check for 2-byte
			else if (cp < 0x800) {
				result.append(static_cast<char>(0xC0 | (cp >> 6)),
							  static_cast<char>(0x80 | (cp & 0x3F)));
			}
			// check for 3-byte
			else if (cp < 0x10000) {
				result.append(static_cast<char>(0xE0 |  (cp >> 12)),
							  static_cast<char>(0x80 | ((cp >> 6) & 0x3F)),
							  static_cast<char>(0x80 |  (cp & 0x3F)));
			}
			// check for 4-byte
			else {
				result.append(static_cast<char>(0xF0 |  (cp >> 18)),
							  static_cast<char>(0x80 | ((cp >> 12) & 0x3F)),
							  static_cast<char>(0x80 | ((cp >> 6)  & 0x3F)),
							  static_cast<char>(0x80 |  (cp & 0x3F)));
			}
		}
		return result;
	}


	inline auto stdchar32_to(const std::u32string& u32str) -> std::string {

		// assertion

		// size alias
		using size_type = std::u32string::size_type;

		// declare char string
		std::string result;

		// reserve space
		result.reserve(u32str.size());

		//char* ptr = result.data();

		//xns::size_t i = 0;
		// loop over 32-bit chars
		for (xns::size_t _ = 0; _ < u32str.size(); ++_) {

			// get code point
			char32_t cp = u32str[_];

			// check for ascii
			if (cp < 0x80) {
				// append to result
				result.push_back(static_cast<char>(cp));
			}
			// check for 2-byte
			else if (cp < 0x800) {
				result.push_back(static_cast<char>(0xC0 | (cp >> 6)));
				result.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
			}
			// check for 3-byte
			else if (cp < 0x10000) {
				result.push_back(static_cast<char>(0xE0 |  (cp >> 12)));
				result.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
				result.push_back(static_cast<char>(0x80 |  (cp & 0x3F)));
			}
			// check for 4-byte
			else {
				result.push_back(static_cast<char>(0xF0 |  (cp >> 18)));
				result.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
				result.push_back(static_cast<char>(0x80 | ((cp >> 6)  & 0x3F)));
				result.push_back(static_cast<char>(0x80 |  (cp & 0x3F)));
			}
		}
		return result;
	}





} // namespace xns

#endif // XNS_STRING_HEADER





//
//
//
//namespace xns {
//
//
//	template <typename ___char,
//			  typename ___alloc = xns::allocator<___char>>
//	class sso_basic_string final {
//
//
//		// -- assertions ------------------------------------------------------
//
//		/* check if T is a character type */
//		static_assert(xns::is_char<___char>,
//				"basic_string: requires a character type");
//
//
//		public:
//
//			// -- public types ------------------------------------------------
//
//			/* self type */
//			using self            = xns::sso_basic_string<___char, ___alloc>;
//
//			/* value type */
//			using value_type      = ___char;
//
//			/* allocator type */
//			using allocator_type  = ___alloc;
//
//			/* size type */
//			using size_type       = xns::allocator_traits<allocator_type>::size_type;
//
//			/* difference type */
//			using difference_type = xns::allocator_traits<allocator_type>::difference_type;
//
//			/* reference type */
//			using reference       = value_type&;
//
//			/* const reference type */
//			using const_reference = const value_type&;
//
//			/* pointer type */
//			using pointer         = xns::allocator_traits<allocator_type>::pointer;
//
//			/* const pointer type */
//			using const_pointer   = xns::allocator_traits<allocator_type>::const_pointer;
//
//			/* iterator type */
//			using iterator        = xns::basic_string_iterator<value_type, false>;
//
//			/* const iterator type */
// 			using const_iterator  = xns::basic_string_iterator<value_type, true>;
//
//			/* string view type */
//			using view_type = xns::basic_string_view<value_type>;
//
//
//		private:
//
//			// -- private types -----------------------------------------------
//
//			/* allocator traits type */
//			using ___alloc_traits = xns::allocator_traits<allocator_type>;
//
//
//		private:
//
//
//			#ifdef _LIBCPP_BIG_ENDIAN
//    static const size_type __endian_factor = 1;
//#else
//    static const size_type __endian_factor = 2;
//#endif
//
//    // Attribute 'packed' is used to keep the layout compatible with the
//    // previous definition that did not use bit fields. This is because on
//    // some platforms bit fields have a default size rather than the actual
//    // size used, e.g., it is 4 bytes on AIX. See D128285 for details.
//    struct __long {
//        struct _LIBCPP_PACKED {
//            size_type __is_long_ : 1;
//            size_type __cap_ : sizeof(size_type) * CHAR_BIT - 1;
//        };
//        size_type __size_;
//        pointer   __data_;
//    };
//
//    enum {__min_cap = (sizeof(__long) - 1)/sizeof(value_type) > 2 ?
//                      (sizeof(__long) - 1)/sizeof(value_type) : 2};
//
//    struct __short {
//        struct _LIBCPP_PACKED {
//            unsigned char __is_long_ : 1;
//            unsigned char __size_ : 7;
//        };
//        char __padding_[sizeof(value_type) - 1];
//        value_type __data_[__min_cap];
//    };
    //static_assert(sizeof(__short) == (sizeof(value_type) * (__min_cap + 1)), "__short has an unexpected size.");
    //union __ulx{__long __lx; __short __lxx;};
    //enum {__n_words = sizeof(__ulx) / sizeof(size_type)};
    //struct __raw { size_type __words[__n_words]; };
    //struct __rep {
    //    union {
    //        __long  __l;
    //        __short __s;
    //        __raw   __r;
    //    }; };

	//		/* big string */
	//		struct big final {
	//			pointer   data;
	//			size_type size;
	//			size_type capacity : (sizeof(size_type) * xns::bits_per_byte) - 1;
	//			size_type is_small : 1;
	//		};
	//
	//		/* default capacity */
	//		enum : size_type {
	//			SSO_CAPACITY  = (sizeof(big) / sizeof(size_type)) - 1
	//		};
	//
	//		/* small string */
	//		struct small final {
	//			value_type data[SSO_CAPACITY];
	//			size_type available : (sizeof(value_type) * xns::bits_per_byte) - 1;
	//			size_type is_small : 1;
	//		};
	//
	//		/* sso union */
	//		union sso final {
	//			big   _big;
	//			small _small;
	//		};
	//
	//		/* sso string */
	//		self::sso _sso;
	//
	//		/* allocator */
	//		[[no_unique_address]] allocator_type _allocator;
	//
	//
	//	public:
	//
	//		// -- public lifecycle --------------------------------------------
	//
	//		/* default constructor */
	//		constexpr sso_basic_string(void) noexcept
	//		: _sso{._small{{0}, SSO_CAPACITY, 1}}, _allocator{} {
	//		}
	//
	//		~sso_basic_string(void) {
	//			if (not is_small()) {
	//				delete[] _sso._big.data;
	//			}
	//		}
	//
	//		auto is_small(void) const -> bool {
	//			// extract least significant byte
	//			return _sso._small.is_small;
	//		}
	//
	//		xns::size_t available(void) const {
	//			return is_small() ? _sso._small.available : _sso._big.capacity - _sso._big.size;
	//		}
	//
	//		xns::size_t capacity(void) const {
	//			return is_small() ? SSO_CAPACITY : _sso._big.capacity;
	//		}
	//
	//		xns::size_t size(void) const {
	//			return is_small() ? SSO_CAPACITY - _sso._small.available : _sso._big.size;
	//		}
	//
	//		void push_back(value_type c) {
	//
	//			if (is_small()) {
	//				// std::cout << "\x1b[32msmall pushing: " << (char)c << "\x1b[0m\n";
	//
	//					_sso._small.data[size()] = c;
	//					--_sso._small.available;
	//					_sso._small.data[size()] = 0;
	//
	//				if (_sso._small.available == 0) {
	//					// std::cout << "DYNAMIC ALLOCATION\n";
	//					pointer data = new value_type[SSO_CAPACITY * 2];
	//					xns::memcpy(data, _sso._small.data, SSO_CAPACITY);
	//					_sso._big.data = data;
	//					_sso._big.size = SSO_CAPACITY;
	//					_sso._big.capacity = SSO_CAPACITY * 2;
	//				}
	//			}
	//			else {
	//				// std::cout << "\x1b[31mbig pushing: " << (char)c << "\x1b[0m\n";
	//				if (_sso._big.size == _sso._big.capacity) {
	//					// std::cout << "REALLOCATION\n";
	//					pointer data = new value_type[_sso._big.capacity * 2];
	//					xns::memcpy(data, _sso._big.data, _sso._big.size);
	//					data[_sso._big.size] = c;
	//					delete[] _sso._big.data;
	//					_sso._big.data = data;
	//					++_sso._big.size;
	//					_sso._big.capacity *= 2;
	//				}
	//				else {
	//					_sso._big.data[_sso._big.size] = c;
	//					++_sso._big.size;
	//				}
	//			}
	//		}
	//
	//
	//
	//		void debug(void) {
	//			std::cout << "\n--------------------------------\n";
	//			std::cout << "     size: " << size() << std::endl;
	//			std::cout << " capacity: " << capacity() << std::endl;
	//			std::cout << "available: " << available() << std::endl;
	//			std::cout << " is_small: " << is_small() << std::endl;
	//			std::cout << "     data: ";
	//
	//			if (is_small()) {
	//				for (size_type x = 0; x < size(); ++x) {
	//					std::cout << _sso._small.data[x];
	//				}
	//			}
	//			else {
	//				for (size_type x = 0; x < size(); ++x) {
	//					std::cout << _sso._big.data[x];
	//				}
	//			}
	//
	//			std::cout << std::endl;
	//
	//		}
	//
	//
	//
	//};
	//




//} // namespace xns
//
//#endif // XNS_STRING_HEADER
