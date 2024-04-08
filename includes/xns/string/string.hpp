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
	template <typename ___type>
	concept is_string = xns::is_same<___type, xns::basic_string     <typename ___type::char_type>>
					 || xns::is_same<___type, xns::basic_string_view<typename ___type::char_type>>;


	/* basic string iterator */
	template <typename, bool>
	class basic_string_iterator;


	// -- non-member functions ------------------------------------------------


	/* strlen (basic string) */
	//template <typename T>
	//constexpr auto strlen(const xns::basic_string<T>& str) noexcept -> auto {
	//	return typename basic_string<T>::size_type{str.size()};
	//}
	//
	///* strlen (basic string view) */
	//template <typename T>
	//constexpr auto strlen(const basic_string_view<T>& view) noexcept -> auto {
	//	return typename basic_string_view<T>::size_type{view.size()};
	//}
	//
	///* strlen (character) */
	//template <typename T> requires(xns::is_char<T>)
	//constexpr auto strlen(const T& character) noexcept -> auto {
	//	//std::cout << "strlen (character)" << std::endl;
	//	return typename basic_string<T>::size_type{1};
	//}




	// -- B A S I C  S T R I N G ----------------------------------------------

	/* string class */
	template <typename ___char>
	class basic_string final {


		// -- friends -----------------------------------------------------

		/* output stream operator as friend */
		friend std::ostream& operator<<(std::ostream& os, const xns::basic_string<char>& string);


		// -- assertions ------------------------------------------------------

		/* check if T is a character type */
		static_assert(xns::is_char<___char>,
				"basic_string: requires a character type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using _self        = xns::basic_string<___char>;

			/* traits type */
			using _traits      = xns::char_traits<___char>;

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
			using char_type   = xns::remove_cvref<___char>;

			/* self type */
			using self        = xns::basic_string<___char>;

			/* size type */
			using size_type   = xns::size_t;

			/* comparison type */
			using signed_type = xns::s64;

			/* pointer type */
			using mut_ptr     = char_type*;

			/* reference type */
			using mut_ref     = char_type&;

			/* move reference type */
			using move_ref    = char_type&&;

			/* const reference type */
			using const_ref   = const char_type&;

			/* const pointer type */
			using const_ptr   = const char_type*;

			/* allocator type */
			using allocator   = xns::allocator<char_type>;

			/* string view type */
			using view_type        = xns::basic_string_view<char_type>;

			/* iterator type */
			using iterator    = xns::basic_string_iterator<char_type, false>;

			/* const iterator type */
			using const_iterator = xns::basic_string_iterator<char_type, true>;


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
			basic_string(void) noexcept
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
			explicit basic_string(const char_type (&str)[N])
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
			basic_string(const char_type character, const size_type count)
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
			explicit basic_string(const view_type& view)
			: basic_string{view.data(), view.size()} {
				//std::cout << "string view constructor" << std::endl;
			}

			/* copy constructor */
			basic_string(const self& other)
			: basic_string{other._str, other._size} {
				//std::cout << "copy constructor" << std::endl;
			}

			/* move constructor */
			basic_string(self&& other) noexcept
			: _str{other._str}, _capacity{other._capacity}, _size{other._size} {
				// invalidate other
				other.init();
			}

			/* destructor */
			~basic_string(void) noexcept {
				// deallocate memory
				deallocate();
			}


			// -- public iterators --------------------------------------------

			/* begin */
			auto begin(void) noexcept -> iterator {
				return iterator{_str};
			}

			/* const begin */
			auto begin(void) const noexcept -> const_iterator {
				return const_iterator{_str};
			}

			/* end */
			auto end(void) noexcept -> iterator {
				return iterator{_str + _size};
			}

			/* const end */
			auto end(void) const noexcept -> const_iterator {
				return const_iterator{_str + _size};
			}



			// -- public assignments ------------------------------------------

			/* string view assignment */
			auto assign(const view_type& view) -> void {
				// return buffer assignment
				assign(view.data(), view.size());
			}

			/* null-terminated string assignment */
			auto assign(const_ptr str) -> void {
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
			auto assign(const char_type character, const size_type size) -> void {
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
			auto operator=(const_ptr str) -> self& {
				assign(str, xns::strlen(str));
				return *this;
			}

			/* character assignment operator */
			auto operator=(const char_type character) -> self& {
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
			auto operator+=(const char_type character) -> self& {
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
			auto operator[](const size_type index) noexcept -> mut_ref {
				return _str[index];
			}

			/* const subscript operator */
			auto operator[](const size_type index) const noexcept -> const_ref {
				return _str[index];
			}


			// -- public boolean operators ------------------------------------

			/* bool operator */
			explicit operator bool(void) const noexcept {
				return _size != 0;
			}

			/* not operator */
			auto operator!(void) const noexcept -> bool {
				return _size == 0;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			auto operator==(const self& str) const noexcept -> bool {
				// call compare method
				return compare(str._str) == 0;
			}

			/* string view equality operator */
			auto operator==(const view_type& view) const noexcept -> bool {
				// call compare method
				return compare(view) == 0;
			}

			/* null-terminated string equality operator */
			auto operator==(const_ptr str) const noexcept -> bool {
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

			/* available */
			auto available(void) const noexcept -> size_type {
				return _capacity - _size;
			}

			/* front */
			auto front(void) noexcept -> mut_ref {
				return _str[0];
			}

			/* const front */
			auto front(void) const noexcept -> const_ref {
				return _str[0];
			}

			/* back */
			auto back(void) noexcept -> mut_ref {
				return _str[_size - 1];
			}

			/* const back */
			auto back(void) const noexcept -> const_ref {
				return _str[_size - 1];
			}

			/* data */
			auto data(void) noexcept -> mut_ptr {
				return _str;
			}

			/* const data */
			auto data(void) const noexcept -> const_ptr {
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
			auto clear(void) noexcept -> void {
				if (_str) { null_terminator(0); }
			}

			/* swap */
			auto swap(self& other) noexcept -> void {
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
			auto append(const char_type character) -> self& {
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
			auto append(const char_type character, const size_type count) -> self& {
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
			auto append(const self& str) -> self& {
				// call buffer append
				return append(str._str, str._size);
			}

			/* string view append */
			auto append(const view_type& view) -> self& {
				// call buffer append
				return append(view.data(), view.size());
			}


			/* null-terminated string append */
			auto append(const_ptr str) -> self& {
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
				constexpr bool type = (xns::is_same<xns::remove_cvref<A>,
											self> && ...); // WARNING NEED TO RECHECK THIS AFTER RECENT CHANGES
				// check if there are at least two arguments
				constexpr bool required = sizeof...(A) >= min;
				// return boolean
				return type && required;
			}



			// NOT FINISHED
			template <typename... A>
			auto multi_length(A&&... strings) const -> size_type {
				return 0;
				//return (xns::strlen(xns::forward<A>(strings)) + ...);
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
			auto insert(size_type index, const char_type character, const size_type count = 1) -> self& {
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
			auto filter(bool (&is_type)(const char_type)) -> void {
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
				static_assert(sizeof(char_type) == 1, "char_type must be 8-bit");

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
			size_type next_character(const size_type index, const char_type character) const {
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
			size_type previous_character(const size_type index, const char_type character) const {
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
			bool is_only(bool (&is_type)(const char_type)) const {
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
			auto compare(const self& str) const noexcept -> signed_type {
				// call strcmp
				return xns::strcmp(_str, str._str);
			}

			/* string view compare */
			auto compare(const basic_string_view<char_type>& view) const noexcept -> signed_type {
				// call null-terminated string compare
				return compare(view.data());
			}

			/* null-terminated string compare */
			auto compare(const_ptr str) const noexcept -> signed_type {
				return str != nullptr ? xns::strcmp(_str, str) : 1;
			}

			/* string size compare */
			auto compare(const self& str, const size_type size) const noexcept -> signed_type {
				// call strncmp
				return xns::strncmp(_str, str._str, size);
			}

			/* null-terminated string size compare */
			auto compare(const_ptr str, size_type size) const noexcept -> signed_type {
				return str != nullptr ? xns::strncmp(_str, str, size) : 1;
			}


			// -- comparison operators ----------------------------------------




		private:

			// -- private methods ---------------------------------------------

			/* init */
			auto init(void) noexcept -> void {
				// initialize members
				_str  = nullptr;
				_size = _capacity = 0U;
			}

			/* set null terminator */
			auto null_terminator(const size_type size) noexcept -> void {
				// update size
				_size = size;
				// set null character
				_str[size] = static_cast<char_type>(0);
			}

			/* set null terminator */
			auto null_terminator(void) noexcept -> void {
				// set null character
				_str[_size] = static_cast<char_type>(0);
			}

			/* allocate */
			static auto allocate(const size_type request) -> mut_ptr {
				// add one for null character
				return allocator::allocate(request + 1U);
			}

			/* deallocate */
			auto deallocate(void) noexcept -> void {
				// check if memory is allocated
				if (_str) { allocator::deallocate(_str); }
			}

			/* realloc */
			auto reallocate(const size_type request) -> void {
				// reallocate memory
				_str = allocator::realloc(_str, request + 1U);
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
			static bool is_charset(const char_type character, const_ptr charset) {
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
			static auto to_basic_string(const U& vlue) -> xns::basic_string<char_type>
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
		static auto to_basic_string(const U& num) -> xns::basic_string<char_type>

			// requirements
			requires(xns::is_unsigned<U> && xns::is_integral<U>) {

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
	inline std::ostream& operator<<(std::ostream& os, const xns::basic_string<char>& str) {
			// check if string is null
			if (str._str) {
				// write string to os
				os.write(str._str, (long)str._size);
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
			using char_type       = ___type;

			/* string type */
			using string_type     = xns::basic_string<char_type>;

			/* size type */
			using size_type       = string_type::size_type;

			/* comparison type */
			using signed_type     = xns::s64;

			/* const reference type */
			using const_ref       = const char_type&;

			/* const pointer type */
			using const_ptr       = const char_type*;


			// -- public constructors -----------------------------------------

			/* default constructor */
			constexpr basic_string_view(void) noexcept
			: _data{xns::empty_string<char_type>()}, _size{0U} {
			}

			/* pointer constructor */
			constexpr basic_string_view(const_ptr ___ptr) noexcept
			: _data{___ptr != nullptr ? ___ptr : xns::empty_string<char_type>()}, _size{xns::strlen(___ptr)} {
			}

			/* pointer and length constructor */
			constexpr basic_string_view(const_ptr ___ptr, const size_type ___sz) noexcept
			: _data{___ptr != nullptr ? ___ptr : xns::empty_string<char_type>()}, _size{_data ? ___sz : 0U} {
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
			constexpr auto assign(const_ptr str) noexcept -> void {
				_data = str;
				_size = xns::strlen(str);
			}

			/* pointer and length assignment */
			constexpr auto assign(const_ptr str, const size_type size) noexcept -> void {
				_data = str;
				_size = size;
			}


			// -- public assignment operators ---------------------------------

			/* pointer assignment operator */
			constexpr auto operator=(const_ptr str) noexcept -> self& {
				assign(str);
				return *this;
			}

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			constexpr auto operator[](const size_type index) const noexcept -> const_ref {
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
			constexpr auto front(void) const noexcept -> const_ref {
				return *_data;
			}

			/* back */
			constexpr auto back(void) const noexcept -> const_ref {
				return _data[_size ? _size - 1 : 0];
			}

			/* data */
			constexpr auto data(void) const noexcept -> const_ptr {
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
				_data = xns::empty_string<char_type>();
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
				_data = xns::empty_string<char_type>();
				_size = 0U;
			}


			/* null-terminated string compare */
			signed_type compare(const_ptr other) const {
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
				static_assert(xns::is_same<char_type, typename ___string::char_type>,
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
			constexpr auto operator==(const_ptr other) const noexcept -> bool {
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
			const_ptr _data;

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
