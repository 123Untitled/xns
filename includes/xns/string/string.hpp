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

#include "xns/memory/memcpy.hpp"
#include "xns/memory/memset.hpp"
#include "xns/memory/memmove.hpp"

#include "xns/string/strcmp.hpp"
#include "xns/string/strncmp.hpp"
#include "xns/string/string_utils.hpp"


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

	template <typename>
	class basic_string_view;

	/* c-string ascii type */
	using string_view    = basic_string_view<char>;

	/* wide string type */
	using wstring_view   = basic_string_view<wchar_t>;

	/* utf-8 string type */
	using u8string_view  = basic_string_view<char8_t>;

	/* utf-16 string type */
	using u16string_view = basic_string_view<char16_t>;

	/* utf-32 string type */
	using u32string_view = basic_string_view<char32_t>;


	// -- forward declarations ------------------------------------------------

	template <typename>
	class basic_string;

	/* c-string ascii type */
	using string    = basic_string<char>;

	/* wide string type */
	using wstring   = basic_string<wchar_t>;

	/* utf-8 string type */
	using u8string  = basic_string<char8_t>;

	/* utf-16 string type */
	using u16string = basic_string<char16_t>;

	/* utf-32 string type */
	using u32string = basic_string<char32_t>;


	// -- I S  S T R I N G  ---------------------------------------------------

	/* is string concept */
	template <class T>
	concept is_string = xns::is_same<T, xns::basic_string<typename T::char_t>>
					 || xns::is_same<T, xns::basic_string_view<typename T::char_t>>;


	/* basic string iterator */
	template <typename, bool>
	class basic_string_iterator;


	// -- non-member functions ------------------------------------------------

	/* strlen (null-terminated string) */
	template <typename T>
	constexpr auto strlen(const T* str) noexcept -> typename basic_string<T>::size_type {
		//std::cout << "strlen (null-terminated string)" << std::endl;
		// check T is a character type
		static_assert(xns::is_char<T>,
				"): strlen requires a character type :(");
		// check if pointer is null
		if (str == nullptr) { return 0; }
		// compute length
		typename basic_string<T>::size_type x = 0;
		// loop until null terminator
		while (str[x] != static_cast<T>(0)) { ++x; }
		// return length
		return x;
	}

	/* strlen (basic string) */
	template <typename T>
	constexpr inline auto strlen(const xns::basic_string<T>& str) noexcept -> auto {
		return typename basic_string<T>::size_type{str.size()};
	}

	/* strlen (basic string view) */
	template <typename T>
	constexpr inline auto strlen(const basic_string_view<T>& view) noexcept -> auto {
		return typename basic_string_view<T>::size_type{view.size()};
	}

	/* strlen (character) */
	template <typename T> requires(xns::is_char<T>)
	constexpr inline auto strlen(const T& character) noexcept -> auto {
		//std::cout << "strlen (character)" << std::endl;
		return typename basic_string<T>::size_type{1};
	}




	// -- B A S I C  S T R I N G ----------------------------------------------

	/* string class */
	template <typename T>
	class basic_string final {


		// -- friends -----------------------------------------------------

		/* output stream operator as friend */
		friend std::ostream& operator<<(std::ostream& os, const xns::basic_string<char>& string);


		// -- assertions ------------------------------------------------------

		/* check if T is a character type */
		static_assert(xns::is_char<T>,
				"): basic string requires a character type :(");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using _self        = xns::basic_string<T>;

			/* traits type */
			using _traits      = xns::char_traits<T>;

			/* char type */
			using _char        = typename _traits::_char;

			/* size type */
			using _unsigned    = typename _traits::_size;

			/* mutable pointer type */
			using _mut_ptr     = typename _traits::_mut_ptr;

			/* const pointer type */
			using _const_ptr   = typename _traits::_const_ptr;

			/* mutable reference type */
			using _mut_ref     = typename _traits::_mut_ref;

			/* const reference type */
			using _const_ref   = typename _traits::_const_ref;

			/* signed int type */
			using _signed      = typename _traits::_signed;








			/* character type */
			using char_t      = xns::remove_cvr<T>;

			/* self type */
			using self        = basic_string<T>;

			/* size type */
			using size_type   = xns::size_t;

			/* comparison type */
			using signed_type = xns::s64;

			/* pointer type */
			using mut_ptr     = char_t*;

			/* reference type */
			using mut_ref     = char_t&;

			/* move reference type */
			using move_ref    = char_t&&;

			/* const reference type */
			using const_ref   = const char_t&;

			/* const pointer type */
			using const_ptr   = const char_t*;

			/* allocator type */
			using allocator   = xns::allocator<char_t>;

			/* string view type */
			using view_type        = xns::basic_string_view<char_t>;

			/* iterator type */
			using iterator    = xns::basic_string_iterator<char_t, false>;

			/* const iterator type */
			using const_iterator = xns::basic_string_iterator<char_t, true>;


		private:

			// -- private members ---------------------------------------------

			/* pointer */
			mut_ptr   _str;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline basic_string(void) noexcept
			: _str{nullptr}, _capacity{0}, _size{0} {}

			/* capacity constructor */
			explicit basic_string(const size_type capacity)
			: _str{nullptr}, _capacity{capacity}, _size{0} {
				// exit if capacity is zero
				if (not capacity) { return; }
				// allocate memory
				_str = allocate(capacity);
				// set nullchar
				null_terminator();
				//std::cout << "capacity constructor" << std::endl;
			}


			/* null-terminated string constructor */
			//explicit basic_string(const_ptr str)
			//: _str{nullptr}, _capacity{xns::strlen(str)}, _size{_capacity} {
			//	// exit if size is zero
			//	if (not _size) { return; }
			//	// allocate memory
			//	_str = allocate(_capacity);
			//	// set nullchar
			//	null_terminator();
			//	// copy string
			//	xns::memcpy(_str, str, _size);
			//}

			/* array constructor */
			template <size_type N>
			explicit basic_string(const char_t (&str)[N])
			: _str{nullptr}, _capacity{str[N - 1] == 0 ? N - 1 : N}, _size{_capacity} {
				// exit if size is zero
				if (not _size) { return; }
				// allocate memory
				_str = allocate(_capacity);
				// set nullchar
				null_terminator();
				// copy string
				xns::memcpy(_str, str, _size);

				//std::cout << "array constructor" << std::endl;
			}

			/* buffer constructor */
			basic_string(const_ptr str, const size_type size)
			: _str{nullptr}, _capacity{size}, _size{size} {
				// exit if buffer is null or empty
				if (not str || not size) { init(); return; }
				// allocate memory
				_str = allocate(size);
				// set nullchar
				null_terminator();
				// copy string
				xns::memcpy(_str, str, size);
				//std::cout << "buffer constructor" << std::endl;
			}

			/* fill constructor */
			basic_string(const char_t character, const size_type count)
			: _str{nullptr}, _capacity{count}, _size{count} {
				// exit if count is zero
				if (!count) { return; }
				// allocate memory
				_str = allocate(count);
				// set nullchar
				null_terminator();
				// fill string
				xns::memset(_str, character, count);
				//std::cout << "fill constructor" << std::endl;
			}

			/* string view constructor */
			explicit inline basic_string(const view_type& view)
			: basic_string{view.data(), view.size()} {
				//std::cout << "string view constructor" << std::endl;
			}

			/* copy constructor */
			inline basic_string(const self& other)
			: basic_string{other._str, other._size} {
				//std::cout << "copy constructor" << std::endl;
			}

			/* move constructor */
			inline basic_string(self&& other) noexcept
			: _str{other._str}, _capacity{other._capacity}, _size{other._size} {
				// invalidate other
				other.init();
			}

			/* destructor */
			inline ~basic_string(void) noexcept {
				// deallocate memory
				deallocate();
			}


			// -- public iterators --------------------------------------------

			/* begin */
			inline auto begin(void) noexcept -> iterator {
				return iterator{_str};
			}

			/* const begin */
			inline auto begin(void) const noexcept -> const_iterator {
				return const_iterator{_str};
			}

			/* end */
			inline auto end(void) noexcept -> iterator {
				return iterator{_str + _size};
			}

			/* const end */
			inline auto end(void) const noexcept -> const_iterator {
				return const_iterator{_str + _size};
			}



			// -- public assignments ------------------------------------------

			/* string view assignment */
			inline auto assign(const view_type& view) -> void {
				// return buffer assignment
				assign(view.data(), view.size());
			}

			/* null-terminated string assignment */
			inline auto assign(const_ptr str) -> void {
				// return buffer assignment
				assign(str, get_len(str));
			}

			/* buffer assignment */
			auto assign(const_ptr str, const size_type size) -> void {
				// check if size or pointer is null
				if (not size || not str) { clear(); return; }
				// check if capacity is sufficient
				if (_capacity < size) {
					// resize the string
					reallocate(size);
				} // copy string
				xns::memcpy(_str, str, size);
				// set nullchar
				null_terminator(size);
			}

			/* fill assignment */
			auto assign(const char_t character, const size_type size) -> void {
				// check if size is zero
				if (not size) { clear(); return; }
				// check if capacity is sufficient
				if (_capacity < size) {
					// resize the string
					reallocate(size);
				} // fill string
				xns::memset(_str, character, size);
				// set nullchar
				null_terminator(size);
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
				//_traits::copy(_str, other._str, other._size);
				xns::memcpy(_str, other._str, other._size);
				// set nullchar
				null_terminator(other._size);
			}

			/* move assignment */
			auto assign(self&& other) noexcept -> void {
				// check for self-assignment
				if (this != &other) {
					// deallocate memory
					if (_str) { allocator::deallocate(_str); }
					// move members
					_str      = other._str;
					_capacity = other._capacity;
					_size     = other._size;
					// invalidate other
					other.init(); }
			}




			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) -> self& {
				assign(other);
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				assign(xns::move(other));
				return *this;
			}

			/* string view assignment operator */
			inline auto operator=(const view_type& view) -> self& {
				assign(view);
				return *this;
			}

			/* null-terminated string assignment operator */
			inline auto operator=(const_ptr str) -> self& {
				assign(str, xns::strlen(str));
				return *this;
			}

			/* character assignment operator */
			inline auto operator=(const char_t character) -> self& {
				assign(character, 1);
				return *this;
			}


			// -- public append operators -------------------------------------

			/* string append operator */
			auto operator+=(const self& str) -> self& {
				// return string append
				return append(str);
			}

			/* null-terminated string append operator */
			auto operator+=(const_ptr str) -> self& {
				// return null-terminated string append
				return append(str, xns::strlen(str));
			}

			/* character append operator */
			auto operator+=(const char_t character) -> self& {
				// return character append
				return append(character);
			}

			/* string view append operator */
			auto operator+=(const view_type& view) -> self& {
				// return string view append
				return append(view);
			}



			// -- public subscript operators ----------------------------------

			/* subscript operator */
			inline auto operator[](const size_type index) noexcept -> mut_ref {
				return _str[index];
			}

			/* const subscript operator */
			inline auto operator[](const size_type index) const noexcept -> const_ref {
				return _str[index];
			}


			// -- public boolean operators ------------------------------------

			/* bool operator */
			explicit inline operator bool(void) const noexcept {
				return _size != 0;
			}

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
				return _size == 0;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline auto operator==(const self& str) const noexcept -> bool {
				// call compare method
				return compare(str._str) == 0;
			}

			/* string view equality operator */
			inline auto operator==(const view_type& view) const noexcept -> bool {
				// call compare method
				return compare(view) == 0;
			}

			/* null-terminated string equality operator */
			inline auto operator==(const_ptr str) const noexcept -> bool {
				// call compare method
				return compare(str) == 0;
			}

			/* less than */
			bool operator<(const self& str) const {
				return compare(str) < 0;
			}

			/* less than or equal */
			bool operator<=(const self& str) const {
				return compare(str) <= 0;
			}

			/* greater than */
			bool operator>(const self& str) const {
				return compare(str) > 0;
			}

			/* greater than or equal */
			bool operator>=(const self& str) const {
				return compare(str) >= 0;
			}





			// -- public accessors --------------------------------------------

			/* empty */
			inline auto empty(void) const noexcept -> bool {
				return _size == 0;
			}

			/* length */
			inline auto length(void) const noexcept -> size_type {
				return _size;
			}

			/* size */
			inline auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			inline auto capacity(void) const noexcept -> size_type {
				return _capacity;
			}

			/* available */
			inline auto available(void) const noexcept -> size_type {
				return _capacity - _size;
			}

			/* front */
			inline auto front(void) noexcept -> mut_ref {
				return _str[0];
			}

			/* const front */
			inline auto front(void) const noexcept -> const_ref {
				return _str[0];
			}

			/* back */
			inline auto back(void) noexcept -> mut_ref {
				return _str[_size - 1];
			}

			/* const back */
			inline auto back(void) const noexcept -> const_ref {
				return _str[_size - 1];
			}

			/* data */
			inline auto data(void) noexcept -> mut_ptr {
				return _str;
			}

			/* const data */
			inline auto data(void) const noexcept -> const_ptr {
				return _str;
			}


			// INFO: in reserve(), does user need to know that nullchar is not included in available space?
			// answer: no, user should not know that nullchar is not included in available space


			/* get subview */
			auto subview(const size_type pos, const size_type size) const noexcept -> view_type {
				// check if index is out of bounds
				if (_str == nullptr || pos < _size)
					return view_type{};

				// return subview
				return (pos + size) < _size ? view_type{_str + pos, size}
											: view_type{_str + pos, _size - pos}; // return clamped subview
			}

			/* get substring */
			auto substr(const size_type pos, const size_type size) const -> self {
				// check if index is out of bounds
				if (_str != nullptr && pos < _size) {
					// return substring
					return pos + size < _size
							? self{_str + pos, size}
							// return clamped substring
							: self{_str + pos, _size - pos};
				} // return default substring
				return self{};
			}


			// -- public modifiers --------------------------------------------

			/* clear */
			inline auto clear(void) noexcept -> void {
				if (_str) { null_terminator(0); }
			}

			/* swap */
			inline auto swap(self& other) noexcept -> void {
				// swap members
				xns::swap(_str,      other._str);
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
					// reallocate memory
					reallocate(request);
				}
				if (_str) {
					// set nullchar
					null_terminator(request);
				}
			}




			/* character append */
			auto append(const char_t character) -> self& {
				// check if there is enough space
				if (not available()) {
					// resize the string
					reallocate(expand());
				} // append character
				_str[_size] = character;
				// set nullchar
				null_terminator(_size + 1);
				// return self reference
				return *this;
			}


			/* fill append */
			auto append(const char_t character, const size_type count) -> self& {
				// check if there is enough space
				if (count > available()) {
					// resize the string
					reallocate(try_expand(_size + count));
				} // copy characters
				xns::memset(_str + _size, character, count);
				// set nullchar
				null_terminator(_size + count);
				// return self reference
				return *this;
			}

			/* string append */
			inline auto append(const self& str) -> self& {
				// call buffer append
				return append(str._str, str._size);
			}

			/* string view append */
			inline auto append(const view_type& view) -> self& {
				// call buffer append
				return append(view.data(), view.size());
			}


			/* null-terminated string append */
			inline auto append(const_ptr str) -> self& {
				// call buffer append
				return append(str, xns::strlen(str));
			}


			/* buffer append */ // WARNING: need to check nullptr
			auto append(const_ptr str, const size_type size) -> self& {
				// check if size or pointer is null
				if (not size || not str) { return *this; }
				// check if there is enough space
				if (size > available()) {
					// resize the string
					reallocate(try_expand(_size + size));
				} // copy string
				xns::memcpy(_str + _size, str, size);
				// set nullchar
				null_terminator(_size + size);
				// return self reference
				return *this;
			}





			template <typename... A>
			static consteval bool append_selector(void) {
				// minimum arguments needed
				constexpr size_type min = 2;
				// check if all arguments are of type string
				constexpr bool type = (xns::is_same<xns::remove_cvr<A>,
											self> && ...); // WARNING NEED TO RECHECK THIS AFTER RECENT CHANGES
				// check if there are at least two arguments
				constexpr bool required = sizeof...(A) >= min;
				// return boolean
				return type && required;
			}



			template <typename... A>
			auto multi_length(A&&... strings) const -> size_type {
				return (xns::strlen(xns::forward<A>(strings)) + ...);
			}

			/* multiple string append */
			template <typename... A> requires(append_selector<A...>())
			auto append_multi(A&&... strings) -> self& {

				// get the size of the strings
				size_type size = 0;
				((size += strings._size), ...);

				if (!size) { return *this; }

				// check if there is enough space
				if (size > available()) {
					// resize the string
					reallocate(try_expand(_size + size));
				}

				// loop through new memory space
				([&]{ for (size_type x = 0, z = _size; x < strings._size; ++x, ++z) {
						// set character
						_str[z] = strings._str[x];
					}
					_size += strings._size;
				}(), ...);

				_str[_size] = 0;

				return *this;
			}




			/* fill insert */
			auto insert(size_type index, const char_t character, const size_type count = 1) -> self& {
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
					_str[z + count] = _str[z];
				}

				size_type to = index + count;
				// loop through new memory space and set characters
				for (size_type x = index; x < to; ++x) {
					// set character
					_str[x] = character;
				}

				// set nullchar
				null_terminator(required);

				// return self reference
				return *this;
			}


			/* buffer insert */
			auto insert(size_type index, const_ptr str, const size_type size) -> self& {
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
				const auto offset = _str + index;
				// move characters
				xns::memmove(offset + size,
							 offset, _size - index);
				// copy string
				xns::memcpy(offset, str, size);
				// set nullchar
				null_terminator(required);
				// return self reference
				return *this;
			}

			/* string insert */
			auto insert(const size_type index, const string& str) -> self& {
				// call buffer insert
				return insert(index, str._str, str._size);
			}

			/* null-terminated string insert */
			auto insert(const size_type index, const_ptr str) -> self& {
				// call buffer insert with size
				return insert(index, str, xns::strlen(str));
			}

			/* string view insert */
			auto insert(const size_type index, const view_type& view) -> self& {
				// call buffer insert with size
				return insert(index, view.data(), view.size());
			}




			/* erase character */
			auto erase(const size_type index) -> void {
				// check if index is valid and string is not null
				if (index >= _size || _str != nullptr)
					return;
				// move characters

				// loop through string
				for (size_type x = index; x < _size; ++x) {
					// shift characters
					_str[x] = _str[x + 1]; // nullchar will be shifted
				} // decrement size
				--_size;
			}

			/* erase range */
			auto erase(const size_type start, const size_type end) -> void {
				// check if index is valid and string is not null
				if (start <= end && end < _size && _str != nullptr) {

					const size_type shift = (end - start) + 1;
					// loop through string
					for (size_type x = start,
							  z = shift + x; z < _size; ++x, ++z) {
						// shift characters
						_str[x] = _str[z];
					}
					// decrement size
					null_terminator(_size - shift);
				}
			}

			/* replace */
			auto replace(const size_type index, const size_type size, const_ptr str) -> void {
				// not implemented yet...
			}


			// -- S P E C I A L  M O D I F I E R S ----------------------------

			/* to uppercase */
			auto to_upper(void) -> void {
				// convert to uppercase
				for (size_type x = 0; x < _size; ++x)
					_str[x] = xns::to_upper(_str[x]);
			}

			/* to lowercase */
			void to_lower(void) {
				// convert to lowercase
				for (size_type x = 0; x < _size; ++x)
					_str[x] = xns::to_lower(_str[x]);
			}

			/* filter */ // INFO: ref functor
			template <bool inverse = true>
			auto filter(bool (&is_type)(const char_t)) -> void {
				// exit if string is null
				if (_str == nullptr) { return; }
				// offset
				size_type offset = 0;
				// loop through string
				for (size_type x = 0; x < _size; ++x) {
					// check if character is not of type
					if (is_type(_str[x]) != inverse) { ++offset; }
					// shift characters
					else { _str[x - offset] = _str[x]; }
				}
				_size -= offset;
				_str[_size] = 0;
			}

			/* reverse */
			void reverse(void) {
				// check if string is not null
				if (not _size) { return; }
				// reverse string
				for (size_type x = 0, z = _size - 1; x < z; ++x, --z) {
					// swap characters
					xns::swap(_str[x], _str[z]);
				}
			}

			void pull_repeat(void) {
				//size_type x = 0;
				//size_type z = 0;

				//if (_str) {
				//	while (z + x < _size) {
				//		while (_str[z + x] == _str[z + x + 1])
				//			x++;
				//		_str[z] = _str[z + x];
				//		z++;
				//	} _size = z;
				//	_str[_size] = nullchar;
				//}
			}

			/* forward remove duplicates */
			void forward_remove_duplicates(void) {
				static_assert(sizeof(char_t) == 1, "char_t must be 8-bit");

				bool seen[UINT8_MAX] = { false };

				if (!_str) { return; }

				xns::u8* ptr = reinterpret_cast<xns::u8*>(_str);
				// initialize new size
				size_type length = _size;

				_size = 0;
				// loop through string characters
				for (size_type z = 0, x = 0; x < length; ++x) {
					// check if character has been seen
					if (seen[ptr[x]]) { continue; }
					// set character as seen
					seen[ptr[x]] = true;
					// copy character to new position
					_str[_size++] = _str[x];
				} // set null character
				_str[_size] = 0;

			}

			/* backward remove duplicates */
			void backward_remove_duplicates(void) {

				//bool seen[UINT8_MAX] = { false };

				//if (!_str) { return; }

				//UInt8* ptr = reinterpret_cast<UInt8*>(_str);

				//size_type x = _size;
				//size_type z = x;

				//while (x--) {
				//	if (seen[ptr[x]]) { continue; }
				//	seen[ptr[x]] = true;
				//	_str[--z] = _str[x];
				//}
				//_size = _size - z;

				//for (x = 0; x < _size; ++x) {
				//	_str[x] = _str[x + z];
				//} _str[_size] = 0;

			}


			// -- S E A R C H I N G -------------------------------------------

			/* next word */
			size_type next_word(const size_type index) const {
				// idle if nullptr or index exceed length
				if (_str != nullptr && index < _size) {

					size_type x = index;
					// skip printable characters
					while (xns::is_print(_str[x])) { ++x; }
					// skip whitespace characters
					while (xns::is_space(_str[x])) { ++x; }

					// check null character
					if (_str[x]) { return x; }

				} // else return unchanged index
				return index;
			}

			/* previous word */ // INFO: not well implemented
			size_type previous_word(const size_type index) const {
				// idle if nullptr or index exceed length
				if (_str != nullptr && index < _size) {

					size_type x = index;
					// skip whitespace characters
					while (x != 0 && xns::is_space(_str[x])) { --x; }
					// skip printable characters
					while (x != 0 && xns::is_alpha(_str[x])) { --x; }

					return x;
				}
				return index;
			}

			/* next character */
			size_type next_character(const size_type index, const char_t character) const {
				// idle if nullptr or index exceed length
				if (_str != nullptr && index < _size) {
					// loop through string
					for (size_type x = index; x < _size; ++x) {
						// return index if character is found
						if (_str[x] == character) { return x; }
					}
				} // else return unchanged index
				return index;
			}

			/* previous character */
			size_type previous_character(const size_type index, const char_t character) const {
				// idle if nullptr or index exceed length
				if (_str != nullptr && index < _size) {
					// loop through string
					for (size_type x = index; x != 0; --x) {
						// return index if character is found
						if (_str[x] == character) return x;
					}
				} // else return unchanged index
				return index;
			}

			/* is only */
			bool is_only(bool (&is_type)(const char_t)) const {
				// return false if string is null or empty
				if (!_str || !_size) { return false; } // WARNING: functor is not checked
				// loop through string
				for (size_type x = 0; x < _size; ++x) {
					// return false if character is not of type
					if (!is_type(_str[x])) { return false; }
				} // return true if all characters are of type
				return true;
			}


			// -- E X T R A C T I O N -----------------------------------------

			/* split */
			template <bool keep = false> requires(keep == false)
			xns::vector<self> split(self&& sep) const {
				// vector of strings
				xns::vector<self> vec;
				// check if string is not null
				if (_str) {
					// loop through string characters
					for (size_type z = 0, x = 0; _str[x]; x += z, z = 0) {
						// skip separator characters
						while (is_charset(_str[x], sep._str)) { ++x; }
						// count non-separator characters
						while (_str[x + z]
								&& !is_charset(_str[x + z], sep._str)) { ++z; }
						// emplace string if z is not zero
						if (z) { vec.emplace_back(&(_str[x]), z); }
					} // return the vector
				} return vec;
			}


			/* divide */ // INFO: split but keep separators
			template <bool keep = false> requires(keep == true)
			xns::vector<self> split(self&& sep) const {
				// vector of strings
				xns::vector<self> vec;

				if (_str) {
					size_type z, x = 0;
					// loop through string characters
					while (_str[x]) {
						z = 0;
						// count separator characters
						while (is_charset(_str[x + z], sep._str)) { ++z; }
						// emplace string if z is not zero
						if (z) { vec.emplace_back(&(_str[x]), z);
							x += z;
						}
						z = 0;
						// count non-separator characters
						while (_str[x + z] && !is_charset(_str[x + z], sep._str)) { ++z; }
						// emplace string if z is not zero
						if (z) { vec.emplace_back(&(_str[x]), z);
							x += z;
						}
					} // return the vector
				} return vec;
			}


			// -- C O M P A R I S O N -----------------------------------------

			// WARNING: constructor not allow empty string
			// so comparison with empty string is not equal...
			// need to fix this.

			/* string compare */
			inline auto compare(const self& str) const noexcept -> signed_type {
				// call strcmp
				return xns::strcmp(_str, str._str);
			}

			/* string view compare */
			inline auto compare(const basic_string_view<char_t>& view) const noexcept -> signed_type {
				// call null-terminated string compare
				return compare(view.data());
			}

			/* null-terminated string compare */
			inline auto compare(const_ptr str) const noexcept -> signed_type {
				return str != nullptr ? xns::strcmp(_str, str) : 1;
			}

			/* string size compare */
			inline auto compare(const self& str, const size_type size) const noexcept -> signed_type {
				// call strncmp
				return xns::strncmp(_str, str._str, size);
			}

			/* null-terminated string size compare */
			inline auto compare(const_ptr str, size_type size) const noexcept -> signed_type {
				return str != nullptr ? xns::strncmp(_str, str, size) : 1;
			}


			// -- comparison operators ----------------------------------------




		private:

			// -- private methods ---------------------------------------------

			/* init */
			inline auto init(void) noexcept -> void {
				// initialize members
				_str  = nullptr;
				_size = _capacity = 0U;
			}

			/* set null terminator */
			inline auto null_terminator(const size_type size) noexcept -> void {
				// update size
				_size = size;
				// set null character
				_str[size] = static_cast<char_t>(0);
			}

			/* set null terminator */
			inline auto null_terminator(void) noexcept -> void {
				// set null character
				_str[_size] = static_cast<char_t>(0);
			}

			/* allocate */
			static inline auto allocate(const size_type request) -> mut_ptr {
				// add one for null character
				return allocator::allocate(request + 1U);
			}

			/* deallocate */
			inline auto deallocate(void) noexcept -> void {
				// check if memory is allocated
				if (_str) { allocator::deallocate(_str); }
			}

			/* realloc */
			inline auto reallocate(const size_type request) -> void {
				// reallocate memory
				_str = allocator::realloc(_str, request + 1U);
				// update capacity
				_capacity = request;
			}

			/* expand */
			inline auto expand(void) const noexcept -> size_type {
				return _capacity ? (_capacity << 2U) : 1U;
			}

			/* try expand */
			inline auto try_expand(const size_type request) const noexcept -> size_type {
				auto new_capacity = (_capacity << 1U);
				return request > new_capacity ? request : new_capacity;
			}







		public:

			// -- D E B U G ---------------------------------------------------

			/* print string */
			void _print_(void) const {
				if (_str && _size) {
					write(STDOUT_FILENO, _str, _size);
					write(STDOUT_FILENO, "\n", 1); }
			}

			/* debug string */
			void _debug_(void) const {
				if (_str) {
					if (_size) { std::cout << "string:   " << _str      << std::endl; }
					else { std::cout       << "string:   " << "empty"   << std::endl; }
				} else { std::cout         << "string:   " << "nullptr" << std::endl; }
				std::cout                  << "Size:     " << _size     << std::endl;
				std::cout                  << "Capacity: " << _capacity << std::endl;
			}


		public:

			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------


			/* is charset */
			static bool is_charset(const char_t character, const_ptr charset) {
				// check if charset is null
				if (!charset) { return false; }
				// loop through charset
				while (*charset) {
					// check if character is in charset
					if (character == *(charset)++) {
						return true; }
				} return false;
			}


			/* to basic string (signed integer) */
			template <typename U>
			static auto to_basic_string(const U& vlue) -> xns::basic_string<char_t>
				// requirements
				requires(xns::is_signed_integral<U>) {

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
					//_str[x] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
					str._str[x] = (value % 10) + '0';
					++x;
				} while ((value /= base));

				if (negative) { str._str[x++] = '-'; }

				str.null_terminator(x);
				// reverse all characters
				str.reverse();

				return str;
			}


		/* to basic string (unsigned integer) */
		template <typename U>
		static auto to_basic_string(const U& num) -> xns::basic_string<char_t>

			// requirements
			requires(xns::is_unsigned_integral<U>) {

			U number = num;

			self str;

			// debug !!!!
			//constexpr size_type size = 100;
			constexpr size_type size = xns::limits<U>::digits();
			//std::cout << "size: " << size << std::endl;
			//static_assert(size > 0, "size must be greater than zero");

			str._str = str.allocate(size);
			str._capacity = size;

			// declare iterator
			size_type x = 0;

			// loop through number
			do {
				str._str[x] = (number % 10) + '0';
				number /= 10;
				++x;
			} while (number);

			str._str[x] = static_cast<U>(0);
			str._size = x;

			// reverse all characters
			str.reverse();

			return str;
		}


		template <typename I>
		static bool to_integer(const self& str, I& value) requires(xns::is_integral<I>) {

			/* integer type */
			using integer       = xns::remove_cvr<I>;

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



	};



	/* deduction guide for null-terminated constructor */
	//template <typename T>
	//basic_string(const T*) -> basic_string<T>;


	/* to c-string ascii */
	template <typename T>
	inline auto to_string(const T& value) -> xns::string {
		return xns::string::to_basic_string<T>(value);
	}

	/* to wide string */
	template <typename T>
	inline auto to_wstring(const T& value) -> xns::wstring {
		return xns::wstring::to_basic_string<T>(value);
	}

	/* to utf-8 string */
	template <typename T>
	inline auto to_u8string(const T& value) -> xns::u8string {
		return xns::u8string::to_basic_string<T>(value);
	}

	/* to utf-16 string */
	template <typename T>
	inline auto to_u16string(const T& value) -> xns::u16string {
		return xns::u16string::to_basic_string<T>(value);
	}

	/* to utf-32 string */
	template <typename T>
	inline auto to_u32string(const T& value) -> xns::u32string {
		return xns::u32string::to_basic_string<T>(value);
	}






	// -- <<  O P E R A T O R  ------------------------------------------------

	/* output stream operator */
	inline std::ostream& operator<<(std::ostream& os, const xns::basic_string<char>& str) {
			// check if string is null
			if (str._str) {
				// write string to os
				os.write(str._str, (long)str._size);
			}
			else { os.write("nullptr", 7); }
		return os;
	}




	// -- B A S I C  S T R I N G  V I E W -------------------------------------

	template <typename T>
	class basic_string_view final {


		public:

			// -- public types ------------------------------------------------

			using _self           = xns::basic_string_view<T>;

			using _traits         = xns::char_traits<T>;

			using _char           = typename _traits::_char;

			using _unsigned       = typename _traits::_size;


			/* character type */
			using char_t          = xns::remove_cv<T>;

			/* self type */
			using self            = basic_string_view<char_t>;

			/* size type */
			using size_type       = typename xns::basic_string<char_t>::size_type;

			/* comparison type */
			using signed_type     = xns::s64;

			/* const reference type */
			using const_ref       = const char_t&;

			/* const pointer type */
			using const_ptr       = const char_t*;

			/* string type */
			using string_t        = xns::basic_string<char_t>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			inline constexpr basic_string_view(void) noexcept
			: _str{_empty}, _size{0} {}

			/* pointer constructor */
			inline constexpr basic_string_view(const_ptr str) noexcept
			: _str{str ? str : _empty}, /*_size{ xns::strlen(str)} temp for test */ _size{0} {

				if (str) {

					size_type x = 0;

					while (str[x]) {
						++x;
					}

					_size = x;

				} // this to be removed

			}

			/* pointer and length constructor */
			inline constexpr basic_string_view(const_ptr str, const size_type size) noexcept
			: _str{str ? str : _empty}, _size{str ? size : 0} {}

			/* string constructor */
			inline constexpr basic_string_view(const string_t& str) noexcept
			: _str{str.data()}, _size{str.size()} {}

			/* copy constructor */
			inline constexpr basic_string_view(const self& other) noexcept
			: _str{other._str}, _size{other._size} {}

			/* move constructor */
			inline constexpr basic_string_view(self&& other) noexcept
			: basic_string_view(other) {}

			/* destructor */
			inline ~basic_string_view(void) noexcept = default;


			// -- public modifiers --------------------------------------------

			/* pointer assignment */
			inline constexpr auto assign(const_ptr str) noexcept -> void {
				_str  = str ? str : _empty;
				_size = xns::strlen(str);
			}

			/* pointer and length assignment */
			inline constexpr auto assign(const_ptr str, const size_type size) noexcept -> void {
				_str  = str ? str : _empty;
				_size = str ? size : 0;
			}

			/* copy assignment */
			inline constexpr auto assign(const self& other) noexcept -> void {
				_str  = other._str;
				_size = other._size;
			}

			/* move assignment */
			inline constexpr auto assign(self&& other) noexcept -> void {
				assign(other);
			}


			// -- public assignment operators ---------------------------------

			/* pointer assignment operator */
			inline constexpr auto operator=(const_ptr str) noexcept -> self& {
				// call pointer assignment
				assign(str);
				// return self reference
				return *this;
			}

			/* copy assignment operator */
			inline constexpr auto operator=(const self& other) noexcept -> self& {
				// call copy assignment
				assign(other);
				// return self reference
				return *this;
			}

			/* move assignment operator */
			inline constexpr auto operator=(self&& other) noexcept -> self& {
				// call move assignment
				assign(other);
				// return self reference
				return *this;
			}


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			inline constexpr auto operator[](const size_type index) const noexcept -> const_ref {
				// return character
				return _str[_size ? index % _size : 0];
			}


			// -- public accessors --------------------------------------------

			/* at */
			inline constexpr auto at(const size_type index) const noexcept -> const_ref {
				// return character
				return _str[_size ? index % _size : 0];
			}

			/* size */
			inline constexpr auto size(void) const noexcept -> size_type {
				// return size
				return _size;
			}

			/* empty */
			inline constexpr auto empty(void) const noexcept -> bool {
				// return empty
				return _size == 0;
			}

			/* front */
			inline constexpr auto front(void) const noexcept -> const_ref {
				// return front
				return *_str;
			}

			/* back */
			inline constexpr auto back(void) const noexcept -> const_ref {
				// return back
				return _str[_size ? _size - 1 : 0];
			}

			/* data */
			inline constexpr auto data(void) const noexcept -> const_ptr {
				// return data
				return _str;
			}


			// -- M O D I F I E R S -------------------------------------------

			/* remove prefix */
			constexpr void remove_prefix(const size_type size) noexcept {
				// check size
				if (size < _size) {
					// remove prefix
					_str  += size;
					_size -= size;
					return;
				} // else reset string
				_str  = _empty;
				_size = 0;
			}

			/* remove suffix */
			constexpr void remove_suffix(const size_type size) noexcept {
				// check size
				if (size < _size) {
					// remove suffix
					_size -= size;
					return;
				} // else reset string
				_str  = _empty;
				_size = 0;
			}


			/* null-terminated string compare */
			signed_type compare(const_ptr other) const {
				// compare nullptr-ness
				if (!_str)  { if (!other) { return 0; } return -1; }
				if (!other) { return 1; }

				size_type x = 0;

				// loop through strings
				while (x < _size) {
					// check for null terminator
					if (!other[x]) { return 1; }
					// compare characters
					if (_str[x] != other[x]) {
						// return difference
						return _str[x] < other[x] ? -1 : 1;
					} ++x;
				}
				// check for null terminator
				return other[x] ? -1 : 0;
			}

			/* string compare */
			template <xns::is_string S>
			signed_type compare(const S& other) const {

				// assert same character type
				static_assert(xns::is_same<char_t, typename S::char_t>,
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
					if (_str[x] != other._str[x]) {
						// return difference
						return _str[x] < other._str[x] ? -1 : 1;
					} ++x;
				}

				// return equal
				return 0;
			}


			// -- comparison operators ----------------------------------------

			/* pointer comparison operator */
			inline constexpr auto operator==(const_ptr other) const noexcept -> bool {
				// return comparison
				return compare(other) == 0;
			}

			/* equality operator */
			template <xns::is_string S>
			inline constexpr auto operator==(const S& other) const noexcept -> bool {
				// return comparison
				return compare(other) == 0;
			}

			/* inequality operator */
			template <xns::is_string S>
			inline constexpr auto operator!=(const S& other) const noexcept -> bool {
				// return comparison
				return compare(other) != 0;
			}

			/* less than operator */
			template <xns::is_string S>
			inline constexpr auto operator<(const S& other) const noexcept -> bool {
				// return comparison
				return compare(other) < 0;
			}

			/* greater than operator */
			template <xns::is_string S>
			inline constexpr auto operator>(const S& other) const noexcept -> bool {
				// return comparison
				return compare(other) > 0;
			}

			/* less than or equal to operator */
			template <xns::is_string S>
			inline constexpr auto operator<=(const S& other) const noexcept -> bool {
				// return comparison
				return compare(other) <= 0;
			}

			/* greater than or equal to operator */
			template <xns::is_string S>
			inline constexpr auto operator>=(const S& other) const noexcept -> bool {
				// return comparison
				return compare(other) >= 0;
			}



		private:


			// -- private members ---------------------------------------------

			/* string */
			const_ptr _str;

			/* string length */
			size_type _size;


			// -- private static members --------------------------------------

			/* empty string */
			static constexpr const_ptr _empty = []() -> const_ptr {
					   if constexpr (xns::is_same<char_t, char>) {
					return   "";
				} else if constexpr (xns::is_same<char_t, char8_t>) {
					return u8"";
				} else if constexpr (xns::is_same<char_t, char16_t>) {
					return  u"";
				} else if constexpr (xns::is_same<char_t, char32_t>) {
					return  U"";
				} else if constexpr (xns::is_same<char_t, wchar_t>) {
					return  L"";
				} else {
					return nullptr;
				}

			}();

	};


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
			using ref_t = typename xns::conditional<is_const, typename string_t::const_ref,
															  typename string_t::mut_ref>;

			/* pointer type */
			using ptr_t = typename xns::conditional<is_const, typename string_t::const_ptr,
															  typename string_t::mut_ptr>;


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
			inline constexpr self& operator++(void) noexcept {
				// increment pointer
				++_ptr;
				// return self reference
				return *this;
			}

			/* postfix increment operator */
			inline constexpr self operator++(int) noexcept {
				// copy self
				self copy{*this};
				// increment pointer
				++_ptr;
				// return copy
				return copy;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline constexpr bool operator==(const self& other) const noexcept {
				// return equality
				return _ptr == other._ptr;
			}

			/* inequality operator */
			inline constexpr bool operator!=(const self& other) const noexcept {
				// return inequality
				return _ptr != other._ptr;
			}


			// -- public accessors --------------------------------------------

			/* dereference operator */
			inline constexpr auto operator*(void) const noexcept -> ref_t {
				// return reference
				return *_ptr;
			}



		private:

			// -- private members ---------------------------------------------

			/* pointer */
			ptr_t _ptr;


	};




	//template <typename T, typename U>
	//auto to_basic_string(const T& data) -> xns::basic_string<U> {
	//
	//
	//	return {};
	//}







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
				result.append(static_cast<char>(0xC0 | (cp >> 6)));
				result.append(static_cast<char>(0x80 | (cp & 0x3F)));
			}
			// check for 3-byte
			else if (cp < 0x10000) {
				result.append(static_cast<char>(0xE0 | (cp >> 12)));
				result.append(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
				result.append(static_cast<char>(0x80 | (cp & 0x3F)));
			}
			// check for 4-byte
			else {
				result.append(static_cast<char>(0xF0 | (cp >> 18)));
				result.append(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
				result.append(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
				result.append(static_cast<char>(0x80 | (cp & 0x3F)));
			}
		}
		return result;
	}





	// -- F O R M A T E D  S T R I N G  I T E R A T O R -----------------------

	/* formatted string iterator */
	template <xns::is_char T>
	class formated_string_iterator {

		public:


			// -- public types ------------------------------------------------

			/* self type */
			using self = formated_string_iterator<T>;

			/* const pointer type */
			using const_pointer = const T*;

			/* size type */
			using size_type = typename basic_string<T>::size_type;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			formated_string_iterator(void) = delete;

			/* constructor */
			template <xns::is_string S>
			constexpr formated_string_iterator(const S& str, const xns::size_t size) noexcept
			: _min{str.data()},
			  _max{str.data() + str.size()},
			  _size{size},
			  _view{} {
				*this += size;
			}

			/* destructor */
			~formated_string_iterator(void) noexcept = default;


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			constexpr operator bool(void) const noexcept {
				return _view.empty() == false;
				// return validity
				return _min < _max;
			}

			/* not operator */
			constexpr bool operator!(void) const noexcept {
				// return invalidity
				return _min >= _max;
			}


			// -- public accessors --------------------------------------------

			/* dereference operator */
			constexpr basic_string_view<T> operator*(void) const noexcept {
				return _view;
			}



			// -- public increment operators ----------------------------------

			/* prefix increment operator */
			constexpr self& operator++(void) noexcept {

				*this += 1;

				return *this;
			}


			constexpr self operator+=(const size_type size) noexcept {

				size_type x = 0;
				const_pointer pos = _min;

				// loop over string
				while ((pos < _max) && (x < size)) {

					// check for escape character
					if (*pos == 27) {
						// skip escape sequence
						while (pos < _max && *pos != 'm') {
							++pos;
						}
						(pos < _max) && ++pos;
						continue;
					}
					// count characters
					while (pos < _max && *pos != 27 && x < size) {
						++x; ++pos;
					}
				}

				// skip trailing escape sequence
				while (pos < _max && *pos == 27) {
					while (pos < _max && *pos != 'm') {
						++pos;
					}
					(pos < _max) && ++pos;
				}

				size_type len = static_cast<size_type>(pos - _min);

				_view = basic_string_view<T>{_min, len};

				_min = pos;


				return *this;
			}






		private:


			/* range min */
			const_pointer _min;

			/* range max */
			const_pointer _max;

			/* line size */
			xns::size_t _size;

			/* view */
			basic_string_view<T> _view;





	}; // formated_string_iterator

	// deduction guide
	template <xns::is_string S>
	formated_string_iterator(const S&, const xns::size_t) -> formated_string_iterator<typename S::char_t>;



	// -- F O R M A T E D  S T R I N G ----------------------------------------

	// -- forward declarations ------------------------------------------------

	template <xns::is_char T>
	class basic_fmt_string;

	/* c-string ascii type */
	using fmt_string = basic_fmt_string<char>;

	/* wide string type */
	using wfmt_string = basic_fmt_string<wchar_t>;

	/* utf-8 string type */
	using u8fmt_string = basic_fmt_string<char8_t>;

	/* utf-16 string type */
	using u16fmt_string = basic_fmt_string<char16_t>;

	/* utf-32 string type */
	using u32fmt_string = basic_fmt_string<char32_t>;


	// -- basic_fmt_string ----------------------------------------------------

	/* formatted string */
	template <xns::is_char T>
	class basic_fmt_string {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = basic_fmt_string<T>;



			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr basic_fmt_string(void) noexcept = default;

			/* string copy constructor */
			constexpr basic_fmt_string(const basic_string<T>& string) noexcept
			: _string{string},
			  _size{vlength(string)} {
			}

			/* string move constructor */
			constexpr basic_fmt_string(basic_string<T>&& string) noexcept
			: _string{xns::move(string)},
			  _size{vlength(_string)} {
			}

			template <class... A>
			constexpr basic_fmt_string(A&&... args) noexcept
			: _string{xns::forward<A>(args)...},
			  _size{vlength(_string)} {
			}

			/* destructor */
			~basic_fmt_string(void) noexcept = default;


			// -- public accessors --------------------------------------------

			/* string size */
			constexpr xns::size_t vsize(void) const noexcept {
				return _size;
			}

			/* string object */
			constexpr xns::basic_string<T>& string(void) noexcept {
				return _string;
			}

			/* const string object */
			constexpr const xns::basic_string<T>& string(void) const noexcept {
				return _string;
			}


			// -- public modifiers --------------------------------------------

			/* compute length */
			constexpr void compute_length(void) noexcept {
				_size = vlength(_string);
			}


		private:

			// -- private methods ---------------------------------------------

			/* compute length */
			static constexpr typename basic_string<T>::size_type vlength(const basic_string<T>& str) noexcept {

				typename basic_string<T>::size_type x = 0;

				bool escape = false;

				// loop over string
				for (typename basic_string<T>::size_type i = 0; i < str.size(); ++i) {

					escape == false
					? str[i] == 27   ? escape = true : ++x
					: str[i] == 'm' && (escape = false);
				}

				return x;
			}

			// -- private members ---------------------------------------------

			/* string */
			xns::basic_string<T> _string;

			/* visual length */
			xns::size_t _size;

	};


	// -- sub-formated string -------------------------------------------------

	/* sub-formated string */
	template <class T>
	auto sub_fmt_string(const T& str, const xns::size_t size) noexcept -> basic_string<typename T::char_t> {

		using const_pointer = typename T::const_ptr;
		using size_type = typename T::size_type;

		size_type x = 0;
		const_pointer ptr = str.data();
		const_pointer end = str.data() + str.size();
		const_pointer esc = nullptr;
		size_type m = 0;

		// loop over string
		while ((ptr < end) && (x < size)) {

			// check for escape character
			if (*ptr == 27) {
				m = 0;
				esc = ptr;
				// skip escape sequence
				while (ptr < end && *ptr != 'm') {
					++ptr; ++m;
				}
				++m;
				(ptr < end) && ++ptr;

				continue;
			}
			// count characters
			while (ptr < end && *ptr != 27 && x < size) {
				++x; ++ptr;
			}
		}

		basic_string<typename T::char_t> result;

		x = 0;
		if (esc) {
			result.append(basic_string_view<typename T::char_t>{esc, m});

			/*
			for (size_type i = 0; i < result.size(); ++i) {

				char c = result[i];

				if (c == 27) {
					std::cout << "e";
				}
				else {
					std::cout << c;
				}

			}
			std::cout << std::endl;
			*/
		}


		result.append(basic_string_view<typename T::char_t>{ptr,
				(size_type)(end - ptr)});

		return result;
	}














	// -- S C R O L L A B L E  S T R I N G ------------------------------------

	// class to encapsulate a string used for being displayed on a screen
	// in a scrollable view

	template <xns::is_char T>
	class scrollable {

		private:

			// -- T Y P E S ---------------------------------------------------

			/* size type */
			using size_type = typename xns::basic_string<T>::size_type;

			// -- M E M B E R S -----------------------------------------------

			/* string */
			xns::basic_string<T> _str;

			/* view size */
			size_type _view_size; // size of view

			/* start position */
			size_type _view_start; // offset from start of string

			/* view position */
			size_type _string_cursor; // position in string

			/* view position */
			size_type _screen_cursor; // position in view

			/* scroll offset */
			size_type _scrolloff; // vim-like scroll offset (half of view size)



		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			scrollable(void) noexcept
			: _str{}, _view_size{0}, _view_start{0}, _string_cursor{0}, _screen_cursor{0} {
			}

			/* destructor */
			~scrollable(void) noexcept = default;


			// -- P U B L I C  S E T T E R S ----------------------------------

			/* set view size */
			void set_view_width(const size_type width) noexcept {
				// set view size and scroll offset (half of view size)
				_scrolloff = (_view_size = width) / 2;
			}





			// -- P U B L I C  M O D I F I E R S ------------------------------

			/* insert */
			void insert(const xns::basic_string<T>& input) {
				_str.insert(_string_cursor, input);
				_string_cursor += input.length();
				_compute();
			}

			/* backspace */
			void backspace(void) {
				// check if cursor is not at start
				if (_string_cursor > 0) {
					// decrement cursor position
					//--_string_cursor;
					_str.erase(--_string_cursor);
					_compute();
				}
			}

			/* erase */
			void erase(void) {
				// check if cursor is not at end
				if (_str.not_empty()) {
					// erase character
					_str.erase(_string_cursor);
					_compute();
				}
			}


			/* move left */
			bool move_left(void) {
				// check if cursor is not at start
				if (_string_cursor > 0) {
					// decrement cursor position
					--_string_cursor;
					// compute view
					_compute();
					// return true
					return true;
				} // return false
				return false;
			}

			/* move right */
			bool move_right(void) {
				// check if cursor is not at end
				if (_string_cursor < _str.length()) {
					// increment cursor position
					++_string_cursor;
					// compute view
					_compute();
					// return true
					return true;
				} // return false
				return false;
			}

			/* reset */
			void reset(void) {
				// reset all members
				_str.clear();
				_view_start = 0;
				_string_cursor = 0;
				_screen_cursor = 0;
			}


			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* const pointer */
			typename xns::basic_string<T>::const_pointer view_pointer(void) const {
				// return constant pointer to first display element
				return _str.pointer() + _view_start;
			}

			/* view size */
			size_type view_size(void) const {
				// check if string is smaller than view size
				if (_str.length() < _view_size) {
					// return string length
					return _str.length();
				} // else return view size
				return _view_size;
			}

			/* get screen cursor position */
			size_type cursor_position(void) const {
				// return screen cursor position
				return _screen_cursor;
			}

			/* string */
			xns::basic_string<T>& string(void) {
				// return string
				return _str;
			}

			/* const string */
			const xns::basic_string<T>& string(void) const {
				// return string
				return _str;
			}




		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* ajust after move */
			// implement scrolloff like in vim
			// let cursor be at the middle of the view

			void _compute(void) {


				// VERSION: LOCKED ON RIGHT

				/*
				if (_str.length() < _view_size) {
					_view_start = 0;
					_screen_cursor = _string_cursor;
					return;
				}
				else {
					if (_string_cursor >= _view_size) {
						_view_start = _string_cursor - _view_size;
						_screen_cursor = _view_size;
					}
					else {
						_view_start = 0;
						_screen_cursor = _string_cursor;
					}
					return;

				}
				return;


				// VERSION: NO SCROLLOFF

				// check if cursor is before view
				if (_string_cursor < _view_start) {
					// move view start to cursor
					_view_start = _string_cursor;
				}

				else if (_string_cursor >= _view_start + _view_size) {
					// move view start to cursor
					_view_start = _string_cursor - _view_size;
				}

				// compute view position
				_screen_cursor = _string_cursor - _view_start;


				return;

				*/


				// VERSION: SCROLLOFF

				// If string_cursor is closer to the start of the string than the scrolloff
				if (_string_cursor < _scrolloff) {
					_view_start = 0;
				}

				// string_cursor is closer to the end than the scrolloff
				else if (_string_cursor > _str.length() - _scrolloff) {
					_view_start = _str.length() - _view_size;
					if (_view_start < 0) {
						_view_start = 0;
					}
				}

				// string_cursor is somewhere in the middle
				else {
					_view_start = _string_cursor - _scrolloff;
				}


				// If the string is shorter than the view
				if (_str.length() < _view_size) {
					// Start the view at the beginning
					_view_start = 0;
					// And position the cursor relative to the start of the string
					_screen_cursor = _string_cursor;
				}
				else {
					// Otherwise compute screen cursor position normally
					_screen_cursor = _string_cursor - _view_start;
				}

			}

	};





} // namespace xns



#endif
	//
	///* string class */
	//template <typename T>
	//class sso_string {
	//
	//
	//	// -- assertions ------------------------------------------------------
	//
	//	/* check if T is a character type */
	//	static_assert(xns::is_char<T>,
	//			"): BASIC STRING REQUIRES A CHARACTER TYPE :(");
	//
	//
	//	public:
	//
	//
	//
	//		// -- public types ------------------------------------------------
	//
	//		/* character type */
	//		using char_t      = xns::remove_cvr<T>;
	//
	//		/* self type */
	//		using self        = sso_string<T>;
	//
	//		/* size type */
	//		using size_type   = xns::size_t;
	//
	//		/* comparison type */
	//		using signed_type = xns::s64;
	//
	//		/* pointer type */
	//		using mut_ptr     = char_t*;
	//
	//		/* reference type */
	//		using mut_ref     = char_t&;
	//
	//		/* move reference type */
	//		using move_ref    = char_t&&;
	//
	//		/* const reference type */
	//		using const_ref   = const char_t&;
	//
	//		/* const pointer type */
	//		using const_ptr   = const char_t*;
	//
	//		/* allocator type */
	//		using allocator   = xns::allocator<char_t>;
	//
	//		/* string view type */
	//		using view        = xns::basic_string_view<char_t>;
	//
	//		/* iterator type */
	//		using iterator    = xns::basic_string_iterator<char_t, false>;
	//
	//		/* const iterator type */
	//		using const_iterator = xns::basic_string_iterator<char_t, true>;
	//
	//
	//	private:
	//
	//		// -- private members ---------------------------------------------
	//
	//
	//		/* big string */
	//		struct big final {
	//			mut_ptr   data;
	//			size_type size;
	//			size_type capacity : (sizeof(size_type) * XNS_CHAR_BIT) - 1;
	//			size_type is_small : 1;
	//		};
	//
	//		/* default capacity */
	//		enum : size_type {
	//			SSO_CAPACITY  = (sizeof(big) / sizeof(char_t)) - 1
	//		};
	//
	//		/* small string */
	//		struct small final {
	//			char_t data[SSO_CAPACITY];
	//			size_type available : (sizeof(char_t) * XNS_CHAR_BIT) - 1;
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
	//
	//	public:
	//
	//		sso_string(void)
	//		: _sso{._small{{0}, SSO_CAPACITY, 1}} {}
	//
	//		~sso_string(void) {
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
	//		void push_back(T c) {
	//			if (is_small()) {
	//				// std::cout << "\x1b[32msmall pushing: " << (char)c << "\x1b[0m\n";
	//
	//					_sso._small.data[size()] = c;
	//					--_sso._small.available;
	//					_sso._small.data[size()] = 0;
	//
	//				if (_sso._small.available == 0) {
	//					// std::cout << "DYNAMIC ALLOCATION\n";
	//					char_t* data = new char_t[SSO_CAPACITY * 2];
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
	//					char_t* data = new char_t[_sso._big.capacity * 2];
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
	//};
