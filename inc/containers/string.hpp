#ifndef STRING_HEADER
#define STRING_HEADER

// global includes
#include <iostream>
#include <iomanip>
#include <unistd.h>

// local includes
#include "policy.hpp"
#include "types.hpp"
#include "move.hpp"
#include "is_char.hpp"

#include "allocator.hpp"
#include "vector.hpp"
#include "array.hpp"
#include "numeric_limits.hpp"

#include "is_unsigned.hpp"
#include "is_signed.hpp"




// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// forward declarations
	template <xns::is_char T>
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


	// forward declarations
	template <xns::is_char T>
	class basic_string;

	/* c-string ascii type */
	using string    = basic_string<char>;

	/* wide string type */
	using wstring   = basic_string<wchar_t>;

	/* utf-8 string type */
	using string8   = basic_string<char8_t>;

	/* utf-16 string type */
	using string16  = basic_string<char16_t>;

	/* utf-32 string type */
	using string32  = basic_string<char32_t>;


	// -- I S  S T R I N G  ---------------------------------------------------

	/* is string concept */
	template <class T>
	concept is_string = xns::is_same<T, xns::basic_string<typename T::char_t>>
			|| xns::is_same<T, xns::basic_string_view<typename T::char_t>>;


	// -- S T R I N G  C L A S S ----------------------------------------------

	/* string class */
	template <xns::is_char T>
	class basic_string {

		public:

			// -- friends -----------------------------------------------------

			/* conversion class is friend */
			friend class conversion;


			// -- public types ------------------------------------------------

			/* character type */
			using char_t          = xns::remove_cvr<T>;

			/* self type */
			using self            = basic_string<T>;

			/* size type */
			using size_type       = xns::size_t;

			/* comparison type */
			using signed_type     = xns::s64;

			/* pointer type */
			using mutable_pointer = char_t*;

			/* reference type */
			using reference       = char_t&;

			/* move reference type */
			using move_reference  = char_t&&;

			/* const reference type */
			using const_reference = const char_t&;

			/* const pointer type */
			using const_pointer   = const char_t*;

			/* allocator type */
			using allocator       = xns::allocator<char_t>;


		private:

			// -- M E M B E R S -----------------------------------------------

			/* pointer */
			mutable_pointer _str;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;


		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			basic_string(void)
			: _str{nullptr}, _capacity{0}, _size{0} {
				// code here...
			}

			/* capacity constructor */
			explicit basic_string(const size_type capacity)
			: basic_string{} {
				std::cout << "capacity constructor" << std::endl;
				// exit if capacity is zero
				if (!capacity) { return; }
				// allocate memory
				_str = allocator::allocate(capacity + 1);
				// set capacity if allocation was successful
				if (_str == nullptr) { return; }
				// set capacity
				_capacity = capacity;
				// set nullchar
				*_str = 0;
			}

			/* string view constructor */
			explicit basic_string(const basic_string_view<char_t>& view)
			: basic_string{view.data(), view.size()} {
				// code here...
			}


			/* null-terminated string constructor */
			basic_string(const_pointer str)
			: basic_string{} {
				// exit if string is null or empty
				if ((_size = get_len(str)) == 0) { return; }
				// set capacity
				_capacity = _size;
				// allocate memory
				_str = allocator::allocate(_capacity + 1);
				// exit if allocation failed
				if (_str == nullptr) { _initialize_members(); return; }
				// set nullchar
				_str[_size] = 0;
				// copy string
				_unsafe_copy(_str, str, _size);
			}

			/* buffer constructor */
			explicit basic_string(const_pointer str, const size_t size)
			: basic_string{} {
				// exit if string is null or empty
				if (!str || !size) { return; }
				// allocate memory
				_str = allocator::allocate(size + 1);
				// exit if allocation failed
				if (_str == nullptr) { return; }
				// set capacity
				_capacity = size;
				// set nullchar
				_str[size] = 0;
				// copy string
				_unsafe_copy(_str, str, size);
				// set size
				_size = size;
			}

			/* fill constructor */
			explicit basic_string(const char_t character, const size_type count)
			: basic_string{} {
				// exit if count is zero
				if (!count) { return; }
				// allocate memory
				_str = allocator::allocate(count + 1);
				// exit if allocation failed
				if (_str == nullptr) { return; }
				// set capacity
				_capacity = count;
				// set nullchar
				_str[count] = 0;
				// fill string
				_unsafe_fill(_str, character, count);
				// set size
				_size = count;
			}

			/* copy constructor */
			basic_string(const self& other)
			: basic_string{other._str, other._size} {
				//std::cout << "copy constructor" << std::endl;
				// code here...
			}


			/* move constructor */
			basic_string(self&& other) noexcept
			: _str{other._str}, _capacity{other._capacity}, _size{other._size} {
				//std::cout << "move constructor" << std::endl;
				// invalidate other
				other._initialize_members();
			}

			/* destructor */
			~basic_string(void) {
				// check if pointer is valid
				if (_str) {
					// deallocate memory
					allocator::deallocate(_str);
				}
			}




			// -- A S S I G N -------------------------------------------------


			/* string view assignment */
			void assign(const basic_string_view<char_t>& view) {
				// return buffer assignment
				assign(view.data(), view.size());
			}


			/* null-terminated string assignment */
			void assign(const_pointer str) {
				assign(str, get_len(str));
			}

			/* buffer assignment */
			void assign(const_pointer str, const size_type size) {

				// WARNING: need to handle this case !
				// check if size or pointer is null
				if (!size || !str) { clear(); return; }

				// check if capacity is sufficient
				if (_capacity < size) {
					// resize the string
					mutable_pointer tmp = _realloc(size);
					// check if reallocation failed
					if (tmp == nullptr) { return; }
					// update members
					_str_and_capacity(tmp, size);
				}

				// loop through string
				for (size_type x = 0; x < size; ++x) {
					// copy character
					_str[x] = str[x];
				}

				_size_and_terminator(size);

			}

			/* fill assignment */
			void assign(const char_t character, const size_type size = 1) {
				// unimplemented
			}


			// WARNING: need to rework this with realloc
			/* copy assignment */
			void assign(const self& other) {
				// check for self-assignment
				if (this != &other) {
					// check if capacity is sufficient
					if (_capacity < other._size) {
						// deallocate memory
						if (_str) { allocator::deallocate(_str); }
						// allocate memory
						_str = allocator::allocate(other._size + 1);
						// check if allocation was successful
						if (_str == nullptr) { return; }
						// set capacity
						_capacity = other._size;
					}
					// loop through other string
					for (size_type i = 0; i < other._size; ++i) {
						// copy character
						_str[i] = other._str[i];
					}
					_size_and_terminator(other._size);
				}
			}

			/* move assignment */
			void assign(self&& other) noexcept {
				// check for self-assignment
				if (this != &other) {
					// deallocate memory
					if (_str) { allocator::deallocate(_str); }
					// move members
					_str      = other._str;
					_capacity = other._capacity;
					_size     = other._size;
					// invalidate other
					other._initialize_members();
				}
			}




			// -- A S S I G N M E N T  O P E R A T O R S ----------------------

			/* copy assignment operator */
			self& operator=(const self& other) {
				return assign(other), *this;
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				return assign(xns::move(other)), *this;
			}

			/* string view assignment operator */
			self& operator=(const basic_string_view<char_t>& view) {
				return assign(view), *this;
			}

			/* null-terminated string assignment operator */
			self& operator=(const_pointer str) {
				return assign(str, get_len(str)), *this;
			}

			/* character assignment operator */
			self& operator=(const char_t character) {
				return assign(character, 1), *this;
			}


			// -- C O N C A T E N A T I O N  O P E R A T O R S ----------------

			/* string append operator */
			self& operator+=(const self& str) {
				// return string append
				return append(str);
			}

			/* null-terminated string append operator */
			self& operator+=(const_pointer str) {
				// return null-terminated string append
				return append(str, get_len(str));
			}

			/* character append operator */
			self& operator+=(const char_t character) {
				// return character append
				return append(character);
			}

			/* string view append operator */
			self& operator+=(const basic_string_view<char_t>& view) {
				// return string view append
				return append(view);
			}



			// -- S U B S C R I P T  O P E R A T O R S ------------------------

			/* subscript operator */
			reference operator[](const size_type index) {
				return _str[index];
			}

			/* const subscript operator */
			const_reference operator[](const size_type index) const {
				return _str[index];
			}


			// -- B O O L E A N  O P E R A T O R S ----------------------------

			/* bool operator */
			operator bool(void) const {
				return _size != 0;
			}

			/* bool not operator */
			bool operator!(void) const {
				return _size == 0;
			}


			// -- C O M P A R I S O N  O P E R A T O R S ----------------------

			/* equality operator */
			bool operator==(const self& str) const {
				// call compare method
				return compare(str._str) == 0;
			}

			/* string view equality operator */
			bool operator==(const basic_string_view<char_t>& view) const {
				// call compare method
				return compare(view) == 0;
			}

			/* null-terminated string equality operator */
			bool operator==(const_pointer str) const {
				// call compare method
				return compare(str) == 0;
			}


			// -- A C C E S S O R S -------------------------------------------

			/* empty */
			auto empty(void) const noexcept -> bool {
				return _size == 0;
			}

			/* not empty */
			bool not_empty(void) const noexcept {
				return _size != 0;
			}

			/* length */
			size_type length(void) const noexcept {
				return _size;
			}

			/* size */
			size_type size(void) const noexcept {
				return _size;
			}

			/* capacity */
			size_type capacity(void) const noexcept {
				return _capacity;
			}

			/* available */
			size_type available(void) const noexcept {
				// INFO: nullchar is not included in available space
				return _capacity - _size;
			}

			/* pointer */
			mutable_pointer pointer(void) noexcept {
				return _str;
			}

			/* const pointer */
			const_pointer pointer(void) const noexcept {
				return _str;
			}

			/* data */
			mutable_pointer data(void) noexcept {
				return _str;
			}

			/* const data */
			const_pointer data(void) const noexcept {
				return _str;
			}

			// INFO: in reserve(), does user need to know that nullchar is not included in available space?
			// answer: no, user should not know that nullchar is not included in available space



			// -- M O D I F I E R S -------------------------------------------

			/* clear */
			void clear(void) noexcept {
				// reset size
				_size = 0;
				// WARNING: nullchar not set
				if (_str) { _str[0] = 0; }
			}

			/* reserve */
			void reserve(const size_type requested) {
				// check if size is greater than capacity
				if (requested > _capacity) {
					// reallocate memory
					mutable_pointer new_str = allocator::realloc(_str, requested + 1);
					// check if reallocation failed
					if (new_str == nullptr) { return; }
					// set new pointer
					_str = new_str;
					// set new capacity
					_capacity = requested;
				}
			}

			/* resize */
			void resize(const size_type requested) {
				// check if size is greater than capacity
				if (requested > _capacity) {
					// reallocate memory
					mutable_pointer new_str = allocator::realloc(_str, requested + 1);
					// set new pointer
					_str = new_str;
					// set new capacity
					_capacity = requested;
				}
				// set new size
				_size = requested;

				if (_str) {
					// set nullchar
					_str[_size] = 0;
				}
			}



			// -- A P P E N D -------------------------------------------------

			/* character append */
			self& append(const char_t character) {

				if (!available()) {
					// resize the string
					mutable_pointer new_str = _realloc(_size + 1);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, _size + 1);
				}
				// append character
				_str[_size] = character;
				// update size and nullchar
				_size_and_terminator(_size + 1);
				// return self reference
				return *this;
			}


			/* fill append */
			self& append(const char_t character, const size_type count) {
				// check if there is enough space
				if (count > available()) {
					// resize the string
					mutable_pointer new_str = _realloc(_size + count);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, _size + count);
				}
				// loop through new memory space
				for (size_type x = 0, z = _size; x < count; ++x, ++z) {
					// set character
					_str[z] = character;
				}
				_size_and_terminator(_size + count);
				// return self reference
				return *this;
			}




			/* string append */
			self& append(const self& str) {
				// call buffer append
				return append(str._str, str._size);
			}


			/* string view append */
			self& append(const basic_string_view<char_t>& view) {
				// call buffer append
				return append(view.data(), view.size());
			}


			/* null-terminated string append */
			self& append(const_pointer str) {
				// call buffer append
				return append(str, string::get_len(str));
			}


			/* buffer append */ // WARNING: need to check nullptr
			self& append(const_pointer str, size_type size) {

				// check if size or pointer is null
				if (!size || !str) { return *this; }

				// check if there is enough space
				if (size > available()) {
					// resize the string
					mutable_pointer new_str = _realloc(_size + size);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, _size + size);
				}

				// loop through new memory space
				for (size_type x = 0, z = _size; x < size; ++x, ++z) {
					// set character
					_str[z] = str[x];
				}

				_size_and_terminator(_size + size);

				// return self reference
				return *this;
			}





			template <typename... A>
			static constexpr bool append_selector(void) {
				// minimum arguments needed
				constexpr size_type min = 2;
				// check if all arguments are of type string
				constexpr bool type = (xns::is_same<
											xns::remove_reference<A>,
											self> && ...); // WARNING NEED TO RECHECK THIS AFTER RECENT CHANGES
				// check if there are at least two arguments
				constexpr bool required = sizeof...(A) >= min;
				// return boolean
				return type && required;
			}

			/* multiple string append */
			template <typename... A>
			self& append(A&&... strings) requires(append_selector<A...>()) {

				// get the size of the strings
				size_type size = 0;
				((size += strings._size), ...);

				if (!size) { return *this; }

				// check if there is enough space
				if (size > available()) {
					// resize the string
					mutable_pointer new_str = _realloc(_size + size);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, _size + size);
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



			// -- I N S E R T -------------------------------------------------

			/* fill insert */
			self& insert(size_type index, const char_t character, const size_type count = 1) {
				// check count is not null
				if (!count) { return *this; }

				index = index > _size ? _size : index;

				size_type required = _size + count;

				// check if there is enough space
				if (count > available()) {
					// resize the string
					mutable_pointer new_str = _realloc(required);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, required);
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

				_size_and_terminator(required);

				// return self reference
				return *this;
			}


			/* buffer insert */
			self& insert(size_type index, const_pointer str, const size_type size) {
				// WARNING: not implemented

				// check if size or pointer is null
				if (!size || !str) { return *this; }

				// check if index is valid
				index = index > _size ? _size : index;

				size_type required = _size + size;

				// check if there is enough space
				if (size > available()) {
					// resize the string
					mutable_pointer new_str = _realloc(required);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, required);
				}

				size_type range = _size - index;

				// loop through new memory space and shift characters
				for (size_type x = 0, z = _size - 1; x < range; ++x, --z) {
					// set character
					_str[z + size] = _str[z];
				}

				size_type to = index + size;
				// loop through new memory space and set characters
				for (size_type x = index, z = 0; x < to; ++x, ++z) {
					// set character
					_str[x] = str[z];
				}

				_size_and_terminator(required);

				// return self reference
				return *this;
			}

			/* string insert */
			self& insert(const size_type index, const string& str) {
				// call buffer insert
				return insert(index, str._str, str._size);
			}

			/* null-terminated string insert */
			self& insert(const size_type index, const_pointer str) {
				// call buffer insert with size
				return insert(index, str, string::get_len(str));
			}



			// -- E R A S E ---------------------------------------------------

			/* erase character */
			self& erase(const size_type index) {
				// check if index is valid and string is not null
				if (index < _size && _str != nullptr) {
					// loop through string
					for (size_type x = index; x < _size; ++x) {
						// shift characters
						_str[x] = _str[x + 1];
					} // decrement size
					--_size;
				} // return self reference
				return *this;
			}

			/* erase range */
			self& erase(const size_type start, const size_type end) {
				// check if index is valid and string is not null
				if (start <= end && end < _size && _str != nullptr) {

					const size_type shift = (end - start) + 1;
					// loop through string
					for (size_type x = start,
							  z = shift + x; z < _size; ++x, ++z) {
						// shift characters
						_str[x] = _str[z];
					} // decrement size
					_size_and_terminator(_size - shift);
				} // return self reference
				return *this;
			}


			// -- S P E C I A L  M O D I F I E R S ----------------------------

			/* to uppercase */
			void to_uppercase(void) {
				// check if string is not null
				if (_str != nullptr) {
					// convert to uppercase
					for (size_type x = 0; x < _size; ++x) {
						_str[x] = string::to_uppercase(_str[x]);
					}
				}
			}

			/* to lowercase */
			void to_lowercase(void) {
				// check if string is not null
				if (_str != nullptr) {
					// convert to lowercase
					for (size_type x = 0; x < _size; ++x) {
						_str[x] = string::to_lowercase(_str[x]);
					}
				}
			}

			/* filter */ // INFO: ref functor
			void filter(bool (&is_type)(const char_t), bool keep = true) {
				// exit if string is null
				if (_str == nullptr) { return; }
				// offset
				size_type offset = 0;
				// loop through string
				for (size_type x = 0; x < _size; ++x) {
					// check if character is not of type
					if (is_type(_str[x]) != keep) { ++offset; }
					// shift characters
					else { _str[x - offset] = _str[x]; }
				}
				_size -= offset;
				_str[_size] = 0;
			}

			/* reverse */
			void reverse(void) {
				// check if string is not null
				if (_str != nullptr && _size) {
					// reverse string
					for (size_type x = 0, z = _size - 1; x < z; ++x, --z) {
						// swap characters
						char_t tmp = _str[x];
						_str[x] = _str[z];
						_str[z] = tmp;
					}
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
					while (is_printable(_str[x])) { ++x; }
					// skip whitespace characters
					while (is_whitespace(_str[x])) { ++x; }

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
					while (x != 0 && string::is_whitespace(_str[x])) { --x; }
					// skip printable characters
					while (x != 0 && string::is_alpha(_str[x])) { --x; }

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
			template <xns::restrict R = xns::assignable_t>
			xns::vector<self, R> split(self&& sep) const {
				// vector of strings
				xns::vector<self, R> vec;
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
			xns::vector<self> divide(self&& sep) const {
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
			signed_type compare(const self& str) const {
				// call null-terminated string compare
				return compare(str._str);
			}

			/* string view compare */
			signed_type compare(const basic_string_view<char_t>& view) const {
				// call null-terminated string compare
				return compare(view.data());
			}

			/* null-terminated string compare */
			signed_type compare(const_pointer str2) const {
				// temporary pointers
				const_pointer str1 = _str;
				// compare nullptr-ness
				if (!str1) { if (!str2) { return 0; } return -1; }
				if (!str2) { return 1; }
				// loop through strings
				while (*str1 && *str2 && *str1 == *str2) {
					++str1; ++str2;
				} // return difference
				return *str1 - *str2;
			}

			/* string size compare */
			signed compare(const self& str, const size_type size) const {
				// call null-terminated string size compare
				return compare(str._str, size);
			}

			/* null-terminated string size compare */
			signed compare(const_pointer str2, size_type size) const {
				// temporary pointers
				const_pointer str1 = _str;
				// compare nullptr-ness
				if (!str1) { if (!str2) { return 0; } return -1; }
				if (!str2) { return 1; }
				// loop through strings
				while (*str1 && *str2 && --size && *str1 == *str2) {
					++str1; ++str2;
				} // return difference
				return *str1 - *str2;
			}


			// -- comparison operators ----------------------------------------

			///* less than */
			//bool operator<(const self& str) const {
			//	return compare(str) < 0;
			//}

			///* less than or equal */
			//bool operator<=(const self& str) const {
			//	return compare(str) <= 0;
			//}

			///* greater than */
			//bool operator>(const self& str) const {
			//	return compare(str) > 0;
			//}

			///* greater than or equal */
			//bool operator>=(const self& str) const {
			//	return compare(str) >= 0;
			//}



			// -- C O N V E R S I O N -----------------------------------------

			/* unsigned integer to string */
			template <xns::is_unsigned N>
			void to_string(N number) {
				// temporary string
				clear();

				constexpr N size = xns::limits::digits<N>();

				// WARNING: need to verify class
				// error doesn't checked with this method
				reserve(size);

				// convert number to string
				size_type x = 0;
				// loop through number
				do {
					_str[x] = (number % 10) + '0';
					number /= 10;
					++x;
				} while (number);

				_size_and_terminator(x);
				// reverse all characters
				reverse();
			}


			/* signed integer to string */
			//template <typename N, typename = Xf::enable_if_signed<N>>
			template <xns::is_signed N>
			void to_string(N number) {
				// temporary string
				clear();

				constexpr size_type size = xns::limits::digits<N>() + 1; // INFO: +1 for negative sign
				constexpr N type_min = xns::limits::min<N>();
				N base = 10;

				// WARNING: need to verify class
				// error doesn't checked with this method
				reserve(size);
				bool negative = false;

				size_type x = 0;
				// check negative
				if (number < 0) {
					// set negative flag
					negative = true;

					if (number == type_min) {
						// INFO: this is a special case
					}
					else {
						// inverse number
						number = -number;
					}
				}
				do {
					N rem = number % base;
					//_str[x] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
					_str[x] = (number % 10) + '0';
					++x;
				} while ((number /= base));

				if (negative) { _str[x++] = '-'; }

				_size_and_terminator(x);
				// reverse all characters
				reverse();
			}



		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* initialize members */
			void _initialize_members(void) {
				_str = nullptr; _size = 0; _capacity = 0;
			}

			void _size_and_terminator(const size_type size) {
				// set terminator
				_str[_size = size] = 0;
			}

			void _str_and_capacity(mutable_pointer str, const size_type capacity) {
				// set capacity
				_capacity = capacity;
				// set pointer
				_str = str;
			}

			/* set members */
			void _set_members(char_t* str, const size_type size, const size_type capacity) {
				// set members
				_str = str; _size = size; _capacity = capacity;
			}


			/* allocate members */
			void _unsafe_allocate(const size_type capacity) {
				// check requested capacity
				if (!capacity) { return; }
				// allocate memory
				_str = allocator::allocate(capacity);
				// set capacity on success
				if (_str) { _capacity = capacity; }
			}

			/* realloc */
			mutable_pointer _realloc(const size_type requested) {
				// reallocate memory
				return allocator::realloc(_str, requested + 1);
			}

			/* allocate other */
			mutable_pointer _allocate(const size_type capacity) const {
				// check requested capacity
				if (!capacity) { return nullptr; }
				// allocate memory
				return allocator::allocate(capacity);
			}


			/* deallocate members */
			void _deallocate(void) {
				// check if memory is allocated
				if (_str) { allocator::deallocate(_str); }
				// reset members
				_initialize_members();
			}


			/* reallocate */
			void reallocate(const size_type capacity);



			/* unsafe copy */
			void _unsafe_copy(mutable_pointer dst, const_pointer src, const size_type size) {
				// loop through source
				for (size_type x = 0; x < size; ++x) {
					// copy character to dst
					dst[x] = src[x];
				}
			}

			/* unsafe fill */
			void _unsafe_fill(mutable_pointer dst, const char_t character, const size_type size) {
				// loop through dst
				for (size_type x = 0; x < size; ++x) {
					// set each character to character
					dst[x] = character;
				}
			}

			/* unsafe bzero */
			void _unsafe_bzero(mutable_pointer dst, const size_type size) {
				// loop through dst
				for (size_type x = 0; x < size; ++x) {
					// set each character to null
					dst[x] = 0;
				}
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

			/* get len */
			static constexpr size_type get_len(const_pointer str) {
				// check if str is null
				if (!str) { return 0; }
				// loop through str
				for (size_type x = 0; ; ++x) {
					// check if null
					if (!str[x]) { return x; }
				}
			}

			/* is upper */
			static bool is_uppercase(const char_t character) {
				// return true if character is upper
				return (character > 0x40 && character < 0x5b);
			}

			/* is lower */
			static bool is_lowercase(const char_t character) {
				// return true if character is lower
				return (character > 0x60 && character < 0x7b);
			}

			/* is alpha */
			static bool is_alpha(const char_t character) {
				// return true if character is alpha
				return (is_uppercase(character) || is_lowercase(character));
			}

			/* is digit */
			static bool is_digit(const char_t character) {
				// return true if character is digit
				return (character > 0x2f && character < 0x3a);
			}

			/* is hexadecimal */
			static bool is_hexadecimal(const char_t character) {
				// return true if character is hexadecimal
				return (is_digit(character)
						|| (character > 0x40 && character < 0x47)
						|| (character > 0x60 && character < 0x67));
			}

			/* is print */
			static bool is_printable(const char_t character) {
				// return true if character is printable
				return (character > 0x1f && character < 0x7f);
			}

			/* is whitespace */
			static bool is_whitespace(const char_t character) {
				// return true if character is white-space
				return ((character > 0x08 && character < 0x0e) || character == 0x20);
			}

			/* is control */
			static bool is_control(const char_t character) {
				// return true if character is control
				return character < 0x20 || character == 0x7f;
			}

			/* is graphical */
			static bool is_graphical(const char_t character) {
				// return true if character is graphical
				return (character > 0x20 && character < 0x7f);
			}

			/* is multi-byte */
			static bool is_multibyte(const char_t character) {
				// return true if character is multi-byte
				return character & 0x80;
			}

			/* is charset */
			static bool is_charset(const char_t character, const_pointer charset) {
				// check if charset is null
				if (!charset) { return false; }
				// loop through charset
				while (*charset) {
					// check if character is in charset
					if (character == *(charset)++) {
						return true; }
				} return false;
			}

			/* to uppercase */
			static char_t to_uppercase(const char_t character) {
				// return uppercase character
				return is_lowercase(character) ? character - 0x20 : character;
			}

			/* to lowercase */
			static char_t to_lowercase(const char_t character) {
				// return lowercase character
				return is_uppercase(character) ? character + 0x20 : character;
			}

			friend std::ostream& operator<<(std::ostream& os, const xns::basic_string<char>& string);

	};



	/* deduction guide for string{const char_t*} */

	template <xns::is_char T>
	basic_string(const T*) -> basic_string<T>;




	template <xns::is_char T>
	auto char32_to(const xns::string32& u32str) -> xns::basic_string<T> {

		// assertion
		static_assert(sizeof(T) == 1, "CHAR32_TO() ONLY SUPPORTS 8-BIT CHAR TYPES");

		// size alias
		using size_type = xns::string32::size_type;
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



	// -- <<  O P E R A T O R  ------------------------------------------------

	/* output stream operator */
	inline std::ostream& operator<<(std::ostream& os, const xns::basic_string<char>& string) {

			// check if string is null
			if (string._str) {
				// write string to os
				os.write(string._str, (long)string._size);
			}
			else { os.write("nullptr", 7); }
		return os;
	}








	// -- S C R O L L A B L E  S T R I N G ------------------------------------

	// class to encapsulate a string used for being displayed on a screen
	// in a scrollable view

	template <xns::is_char T>
	class scroll_string {

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
			scroll_string(void) noexcept
			: _str{ }, _view_size{0}, _view_start{0}, _string_cursor{0}, _screen_cursor{0} {
				// code here...
			}

			/* destructor */
			~scroll_string(void) noexcept = default;


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



	// -- S T R I N G  V I E W ------------------------------------------------

	template <xns::is_char T>
	class basic_string_view final {


		public:

			// -- public types ------------------------------------------------

			/* character type */
			using char_t          = xns::remove_cv<T>;

			/* self type */
			using self            = basic_string_view<char_t>;

			/* size type */
			using size_type       = typename xns::basic_string<char_t>::size_type;

			/* comparison type */
			using signed_type     = xns::s64;

			/* reference type */
			using reference       = char_t&;

			/* move reference type */
			using move_reference  = char_t&&;

			/* const reference type */
			using const_reference = const char_t&;

			/* const pointer type */
			using const_pointer   = const char_t*;


			// -- public constructors -----------------------------------------

			/* default constructor */
			constexpr basic_string_view(void) noexcept
			: _str{nullptr}, _size{0} {}

			/* nullptr constructor */
			constexpr basic_string_view(xns::null) noexcept
			: basic_string_view() {}

			/* pointer constructor */
			constexpr basic_string_view(const_pointer str) noexcept
			: _str{str}, _size{_strlen(str)} {}

			/* pointer and length constructor */
			constexpr basic_string_view(const_pointer str, const size_type size) noexcept
			: _str{str}, _size{str ? size : 0} {}

			/* string constructor */
			constexpr basic_string_view(const xns::basic_string<char_t>& str) noexcept
			: _str{str.data()}, _size{str.length()} {}

			/* copy constructor */
			constexpr basic_string_view(const self& other) noexcept
			: _str{other._str}, _size{other._size} {}

			/* move constructor */
			constexpr basic_string_view(self&& other) noexcept
			: _str{other._str}, _size{other._size} {
				// invalidate other
				other._str  = nullptr;
				other._size = 0;
			}

			/* destructor */
			~basic_string_view(void) noexcept = default;


			// -- assignments -------------------------------------------------

			/* pointer assignment */
			constexpr void assign(const_pointer str) noexcept {
				// assign string
				_str = str;
				// assign size
				_size = _strlen(str);
			}

			/* pointer and length assignment */
			constexpr void assign(const_pointer str, const size_type size) noexcept {
				// assign string
				_str = str;
				// assign size
				_size = str ? size : 0;
			}

			/* copy assignment */
			constexpr void assign(const self& other) noexcept {
				// copy string
				_str = other._str;
				// copy size
				_size = other._size;
			}

			/* move assignment */
			constexpr void assign(self&& other) noexcept {
				// move string
				_str = other._str;
				// move size
				_size = other._size;
				// invalidate other
				other._str  = nullptr;
				other._size = 0;
			}


			// -- A S S I G N M E N T  O P E R A T O R S ----------------------

			/* pointer assignment operator */
			constexpr self& operator=(const_pointer str) noexcept {
				// return pointer assignment
				return assign(str), *this;
			}

			/* copy assignment operator */
			constexpr self& operator=(const self& other) noexcept {
				// return copy assignment
				return assign(other), *this;
			}

			/* move assignment operator */
			constexpr self& operator=(self&& other) noexcept {
				// return move assignment
				return assign(xns::move(other)), *this;
			}


			// -- S U B S C R I P T I O N  O P E R A T O R S ------------------

			/* subscript operator */
			constexpr const_reference operator[](const size_type index) const noexcept {
				// return character
				return _str[index];
			}


			// -- A C C E S S O R S -------------------------------------------

			/* at */
			constexpr const_reference at(const size_type index) const noexcept {
				// return character
				return _str[index];
			}

			/* size */
			constexpr size_type size(void) const noexcept {
				// return size
				return _size;
			}

			/* length */
			constexpr size_type length(void) const noexcept {
				// return size
				return _size;
			}

			/* empty */
			constexpr bool empty(void) const noexcept {
				// return empty
				return _size == 0;
			}

			/* front */
			constexpr const_reference front(void) const noexcept {
				// return front
				return *_str;
			}

			/* back */
			constexpr const_reference back(void) const noexcept {
				// return back
				return _str[_size - 1];
			}

			/* const pointer */
			constexpr const_pointer pointer(void) const noexcept {
				// return pointer
				return _str;
			}

			/* data */
			constexpr const_pointer data(void) const noexcept {
				// return data
				return _str;
			}


			// -- M O D I F I E R S -------------------------------------------

			/* remove prefix */
			constexpr void remove_prefix(const size_type size) noexcept {
				// check size
				if (size < _size) { // remove prefix
					_str    += size;
					_size -= size;
					return; }
				// else reset string
				_str    = nullptr;
				_size = 0;
			}

			/* remove suffix */
			constexpr void remove_suffix(const size_type size) noexcept {
				// check size
				if (size < _size) { // remove suffix
					_size -= size;
					return; }
				// else reset string
				_str    = nullptr;
				_size = 0;
			}


			/* null-terminated string compare */
			signed_type compare(const_pointer other) const {
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
				if (!_str)       { if (!other._str) { return 0; } return -1; }
				if (!other._str) { return 1; }

				// compare sizes
				if (_size != other._size) {
					// avoid overflow, can't just subtract
					return _size < other._size ? -1 : 1;
				}

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
			constexpr bool operator==(const_pointer other) const noexcept {
				// return comparison
				return compare(other) == 0;
			}

			/* string comparison operator */
			template <xns::is_string S>
			constexpr bool operator==(const S& other) const noexcept {
				// return comparison
				return compare(other) == 0;
			}

		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* compute length */
			constexpr size_type _strlen(const_pointer str) const noexcept {
				// check pointer validity
				if (!str) { return 0; }
				// compute length
				size_type x = 0;
				// loop until null terminator
				while (str[x] != '\0') { ++x; }
				// return length
				return x;
			}


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* string */
			const_pointer _str;

			/* string length */
			size_type _size;


	};


	/* deduction guide */
	template <xns::is_char T>
	basic_string_view(const T*) -> basic_string_view<T>;


};











#endif
