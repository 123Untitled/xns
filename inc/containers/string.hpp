#ifndef STRING_HEADER
#define STRING_HEADER

// global includes
#include <iostream>
#include <iomanip>
#include <unistd.h>

// local includes
#include "types.hpp"
#include "move.hpp"
#include "string_traits.hpp"

#include "allocator.hpp"
#include "vector.hpp"
#include "array.hpp"
#include "numeric_limits.hpp"


// forward declarations
class LString;

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- S T R I N G  C L A S S ----------------------------------------------

	// forward declarations
	template <Xf::is_char_c T>
	class String;

	/* c-string ascii type */
	using CString   = String<char>;

	/* wide string type */
	using WString   = String<wchar_t>;

	/* utf-8 string type */
	using String8  = String<char8_t>;

	/* utf-16 string type */
	using String16 = String<char16_t>;

	/* utf-32 string type */
	using String32 = String<char32_t>;


	/* string class */
	template <Xf::is_char_c T>
	class String {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* character type */
			using CharT = remove_cv_t<T>;

			/* size type */
			using Size = UInt64;

			/* comparison type */
			using Signed = SInt32;

			/* pointer type */
			using Pointer = CharT*;

			/* reference type */
			using Reference = CharT&;

			/* move reference type */
			using MoveReference = CharT&&;

			/* const reference type */
			using ConstRef = const CharT&;

			/* const pointer type */
			using ConstPointer = const CharT*;

			/* allocator type */
			using Allocator = Xf::Allocator<CharT>;


		private:

			// -- M E M B E R S -----------------------------------------------

			/* pointer */
			Pointer _str;

			/* capacity */
			Size _capacity;

			/* size */
			Size _size;


		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			String(void)
			: _str{nullptr}, _capacity{0}, _size{0} {
				// code here...
			}

			/* capacity constructor */
			explicit String(const Size capacity)
			: String{} {
				std::cout << "capacity constructor" << std::endl;
				// exit if capacity is zero
				if (!capacity) { return; }
				// allocate memory
				_str = Allocator::allocate(capacity + 1);
				// set capacity if allocation was successful
				if (_str == nullptr) { return; }
				// set capacity
				_capacity = capacity;
				// set nullchar
				*_str = 0;
			}

			/* null-terminated string constructor */
			String(ConstPointer str)
			: String{} {
				// exit if string is null or empty
				if ((_size = get_len(str)) == 0) { return; }
				// set capacity
				_capacity = _size;
				// allocate memory
				_str = Allocator::allocate(_capacity + 1);
				// exit if allocation failed
				if (_str == nullptr) { _initialize_members(); return; }
				// set nullchar
				_str[_size] = 0;
				// copy string
				_unsafe_copy(_str, str, _size);
			}

			/* buffer constructor */
			explicit String(ConstPointer str, const Size size)
			: String{} {
				// exit if string is null or empty
				if (!str || !size) { return; }
				// allocate memory
				_str = Allocator::allocate(size + 1);
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
			explicit String(const CharT character, const Size count)
			: String{} {
				// exit if count is zero
				if (!count) { return; }
				// allocate memory
				_str = Allocator::allocate(count + 1);
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
			String(const String& other)
			: String{other._str, other._size} {
				// code here...
			}


			/* move constructor */
			String(String&& other) noexcept
			: _str{other._str}, _capacity{other._capacity}, _size{other._size} {
				// invalidate other
				other._initialize_members();
			}

			/* destructor */
			~String(void) {
				// check if pointer is valid
				if (_str) {
					// deallocate memory
					Allocator::deallocate(_str);
				}
			}




			// -- A S S I G N -----------------------------------------------------

			/* null-terminated string assignment */
			String& assign(ConstPointer str) {
				return assign(str, get_len(str));
			}

			/* buffer assignment */
			String& assign(ConstPointer str, const Size size) {

				// WARNING: need to handle this case !
				// check if size or pointer is null
				if (!size || !str) { clear(); return *this; }

				// check if capacity is sufficient
				if (_capacity < size) {
					// resize the string
					Pointer tmp = _realloc(size);
					// check if reallocation failed
					if (tmp == nullptr) { return *this; }
					// update members
					_str_and_capacity(tmp, size);
				}

				// loop through string
				for (Size x = 0; x < size; ++x) {
					// copy character
					_str[x] = str[x];
				}

				_size_and_terminator(size);

				return *this;
			}

			/* fill assignment */
			String& assign(const CharT character, const Size size = 1) {

			}

			// WARNING: need to rework this with realloc
			/* copy assignment */
			String& assign(const String& other) {
				// check for self-assignment
				if (this != &other) {
					// check if capacity is sufficient
					if (_capacity < other._size) {
						// deallocate memory
						if (_str) { Allocator::deallocate(_str); }
						// allocate memory
						_str = Allocator::allocate(other._size + 1);
						// check if allocation was successful
						if (_str == nullptr) { return *this; }
						// set capacity
						_capacity = other._size;
					}
					// loop through other string
					for (Size i = 0; i < other._size; ++i) {
						// copy character
						_str[i] = other._str[i];
					}
					_size_and_terminator(other._size);
				}
				// return self reference
				return *this;
			}

			/* move assignment */
			String& assign(String&& other) noexcept {
				// check for self-assignment
				if (this != &other) {
					// deallocate memory
					if (_str) { Allocator::deallocate(_str); }
					// move members
					_str = other._str;
					_capacity = other._capacity;
					_size = other._size;
					// invalidate other
					other._initialize_members();
				}
				// return self reference
				return *this;
			}




			// -- A S S I G N M E N T  O P E R A T O R S ----------------------

			/* copy assignment operator */
			String& operator=(const String& other) {
				return assign(other);
			}

			/* move assignment operator */
			String& operator=(String&& other) noexcept {
				return assign(Xf::move(other));
			}

			/* null-terminated string assignment operator */
			String& operator=(ConstPointer str) {
				return assign(str, get_len(str));
			}

			/* character assignment operator */
			String& operator=(const CharT character) {
				return assign(character, 1);
			}


			// -- C O N C A T E N A T I O N  O P E R A T O R S ----------------

			/* concatenation assignment operator */
			String& operator+=(const String& str) {
				return append(str);
			}

			/* null-terminated string concatenation assignment operator */
			String& operator+=(ConstPointer str) {
				return append(str, get_len(str));
			}

			/* character concatenation assignment operator */
			String& operator+=(const CharT character) {
				return append(character);
			}


			// -- S U B S C R I P T  O P E R A T O R S ------------------------

			/* subscript operator */
			Reference operator[](const Size index) {
				return _str[index];
			}

			/* const subscript operator */
			ConstRef operator[](const Size index) const {
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
			bool operator==(const String& str) const {
				// call compare method
				return compare(str._str) == 0;
			}

			/* null-terminated string equality operator */
			bool operator==(ConstPointer str) const {
				// call compare method
				return compare(str) == 0;
			}


			// -- A C C E S S O R S -------------------------------------------

			/* empty */
			bool empty(void) const {
				return _size == 0;
			}

			/* not empty */
			bool not_empty(void) const {
				return _size != 0;
			}

			/* length */
			Size length(void) const {
				return _size;
			}

			/* size */
			Size size(void) const {
				return _size;
			}

			/* capacity */
			Size capacity(void) const {
				return _capacity;
			}

			/* available */
			Size available(void) const {
				// INFO: nullchar is not included in available space
				return _capacity - _size;
			}

			/* pointer */
			Pointer pointer(void) {
				return _str;
			}

			/* const pointer */
			ConstPointer pointer(void) const {
				return _str;
			}

			// INFO: in reserve(), does user need to know that nullchar is not included in available space?
			// answer: no, user should not know that nullchar is not included in available space



			// -- M O D I F I E R S -------------------------------------------

			/* clear */
			void clear(void) {
				// reset size
				_size = 0;
				// WARNING: nullchar not set
				if (_str) { _str[0] = 0; }
			}

			/* reserve */
			void reserve(const Size requested) {
				// check if size is greater than capacity
				if (requested > _capacity) {
					// reallocate memory
					Pointer new_str = Allocator::realloc(_str, requested + 1);
					// check if reallocation failed
					if (new_str == nullptr) { return; }
					// set new pointer
					_str = new_str;
					// set new capacity
					_capacity = requested;
				}
			}



			// -- A P P E N D -------------------------------------------------

			/* fill append */
			String& append(const CharT character, const Size count = 1) {
				// check if there is enough space
				if (count > available()) {
					// resize the string
					Pointer new_str = _realloc(_size + count);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, _size + count);
				}
				// loop through new memory space
				for (Size x = 0, z = _size; x < count; ++x, ++z) {
					// set character
					_str[z] = character;
				}
				_size_and_terminator(_size + count);
				// return self reference
				return *this;
			}


			/* string append */
			String& append(const String& str) {
				// call buffer append
				return append(str._str, str._size);
			}

			/* null-terminated string append */
			String& append(ConstPointer str) {
				// call buffer append
				return append(str, String::get_len(str));
			}


			/* buffer append */ // WARNING: need to check nullptr
			String& append(ConstPointer str, Size size) {

				// check if size or pointer is null
				if (!size || !str) { return *this; }

				// check if there is enough space
				if (size > available()) {
					// resize the string
					Pointer new_str = _realloc(_size + size);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, _size + size);
				}

				// loop through new memory space
				for (Size x = 0, z = _size; x < size; ++x, ++z) {
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
				constexpr Size min = 2;
				// check if all arguments are of type String
				constexpr bool type = (Xf::IsSame_s<Xf::remove_reference_t<A>, String<CharT>>::value&& ...);
				// check if there are at least two arguments
				constexpr bool required = sizeof...(A) >= min;
				// return boolean
				return type && required;
			}

			/* multiple string append */
			template <typename... A>
			String& append(A&&... strings) requires(append_selector<A...>()) {

				// get the size of the strings
				Size size = 0;
				((size += strings._size), ...);

				if (!size) { return *this; }

				// check if there is enough space
				if (size > available()) {
					// resize the string
					Pointer new_str = _realloc(_size + size);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, _size + size);
				}

				// loop through new memory space
				([&]{ for (Size x = 0, z = _size; x < strings._size; ++x, ++z) {
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
			String& insert(Size index, const CharT character, const Size count = 1) {
				// check count is not null
				if (!count) { return *this; }

				index = index > _size ? _size : index;

				Size required = _size + count;

				// check if there is enough space
				if (count > available()) {
					// resize the string
					Pointer new_str = _realloc(required);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, required);
				}

				Size range = _size - index;

				// loop through new memory space and shift characters
				for (Size x = 0, z = _size - 1; x < range; ++x, --z) {
					// set character
					_str[z + count] = _str[z];
				}

				Size to = index + count;
				// loop through new memory space and set characters
				for (Size x = index; x < to; ++x) {
					// set character
					_str[x] = character;
				}

				_size_and_terminator(required);

				// return self reference
				return *this;
			}


			/* buffer insert */
			String& insert(Size index, ConstPointer str, const Size size) {
				// WARNING: not implemented

				// check if size or pointer is null
				if (!size || !str) { return *this; }

				// check if index is valid
				index = index > _size ? _size : index;

				Size required = _size + size;

				// check if there is enough space
				if (size > available()) {
					// resize the string
					Pointer new_str = _realloc(required);
					// check if reallocation failed
					if (new_str == nullptr) { return *this; }
					// update data
					_str_and_capacity(new_str, required);
				}

				Size range = _size - index;

				// loop through new memory space and shift characters
				for (Size x = 0, z = _size - 1; x < range; ++x, --z) {
					// set character
					_str[z + size] = _str[z];
				}

				Size to = index + size;
				// loop through new memory space and set characters
				for (Size x = index, z = 0; x < to; ++x, ++z) {
					// set character
					_str[x] = str[z];
				}

				_size_and_terminator(required);

				// return self reference
				return *this;
			}

			/* string insert */
			String& insert(const Size index, const String& str) {
				// call buffer insert
				return insert(index, str._str, str._size);
			}

			/* null-terminated string insert */
			String& insert(const Size index, ConstPointer str) {
				// call buffer insert with size
				return insert(index, str, String::get_len(str));
			}



			// -- E R A S E ---------------------------------------------------

			/* erase character */
			String& erase(const Size index) {
				// check if index is valid and string is not null
				if (index < _size && _str != nullptr) {
					// loop through string
					for (Size x = index; x < _size; ++x) {
						// shift characters
						_str[x] = _str[x + 1];
					} // decrement size
					--_size;
				} // return self reference
				return *this;
			}

			/* erase range */
			String& erase(const Size start, const Size end) {
				// check if index is valid and string is not null
				if (start <= end && end < _size && _str != nullptr) {

					const Size shift = (end - start) + 1;
					// loop through string
					for (Size x = start,
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
					for (Size x = 0; x < _size; ++x) {
						_str[x] = String::to_uppercase(_str[x]);
					}
				}
			}

			/* to lowercase */
			void to_lowercase(void) {
				// check if string is not null
				if (_str != nullptr) {
					// convert to lowercase
					for (Size x = 0; x < _size; ++x) {
						_str[x] = String::to_lowercase(_str[x]);
					}
				}
			}

			/* filter */ // INFO: ref functor
			void filter(bool (&is_type)(const CharT), bool keep = true) {
				// exit if string is null
				if (_str == nullptr) { return; }
				// offset
				Size offset = 0;
				// loop through string
				for (Size x = 0; x < _size; ++x) {
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
					for (Size x = 0, z = _size - 1; x < z; ++x, --z) {
						// swap characters
						CharT tmp = _str[x];
						_str[x] = _str[z];
						_str[z] = tmp;
					}
				}
			}

			void pull_repeat(void) {
				//Size x = 0;
				//Size z = 0;

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
				static_assert(Xf::is_8bit_v<CharT>, "CharT must be 8-bit");

				bool seen[UINT8_MAX] = { false };

				if (!_str) { return; }

				UInt8* ptr = reinterpret_cast<UInt8*>(_str);
				// initialize new size
				Size length = _size;

				_size = 0;
				// loop through string characters
				for (Size z = 0, x = 0; x < length; ++x) {
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

				//Size x = _size;
				//Size z = x;

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
			Size next_word(const Size index) const {
				// idle if nullptr or index exceed length
				if (_str != nullptr && index < _size) {

					Size x = index;
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
			Size previous_word(const Size index) const {
				// idle if nullptr or index exceed length
				if (_str != nullptr && index < _size) {

					Size x = index;
					// skip whitespace characters
					while (x != 0 && String::is_whitespace(_str[x])) { --x; }
					// skip printable characters
					while (x != 0 && String::is_alpha(_str[x])) { --x; }

					return x;
				}
				return index;
			}

			/* next character */
			Size next_character(const Size index, const CharT character) const {
				// idle if nullptr or index exceed length
				if (_str != nullptr && index < _size) {
					// loop through string
					for (Size x = index; x < _size; ++x) {
						// return index if character is found
						if (_str[x] == character) { return x; }
					}
				} // else return unchanged index
				return index;
			}

			/* previous character */
			Size previous_character(const Size index, const CharT character) const {
				// idle if nullptr or index exceed length
				if (_str != nullptr && index < _size) {
					// loop through string
					for (Size x = index; x != 0; --x) {
						// return index if character is found
						if (_str[x] == character) return x;
					}
				} // else return unchanged index
				return index;
			}

			/* is only */
			bool is_only(bool (&is_type)(const CharT)) const {
				// return false if string is null or empty
				if (!_str || !_size) { return false; } // WARNING: functor is not checked
				// loop through string
				for (Size x = 0; x < _size; ++x) {
					// return false if character is not of type
					if (!is_type(_str[x])) { return false; }
				} // return true if all characters are of type
				return true;
			}

			// -- E X T R A C T I O N -----------------------------------------

			/* split */
			Xf::Vector<String<CharT>> split(String&& sep) const {
				// vector of strings
				Xf::Vector<String<CharT>> vec;
				// check if string is not null
				if (_str) {
					// loop through string characters
					for (Size z = 0, x = 0; _str[x]; x += z, z = 0) {
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
			Xf::Vector<String<CharT>> divide(String&& sep) const {
				// vector of strings
				Xf::Vector<String<CharT>> vec;

				if (_str) {
					UInt32 z, x = 0;
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
			Signed compare(const String& str) const {
				// call null-terminated string compare
				return compare(str._str);
			}

			/* null-terminated string compare */
			Signed compare(ConstPointer str2) const {
				// temporary pointers
				ConstPointer str1 = _str;
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
			Signed compare(const String& str, const Size size) const {
				// call null-terminated string size compare
				return compare(str._str, size);
			}

			/* null-terminated string size compare */
			Signed compare(ConstPointer str2, Size size) const {
				// temporary pointers
				ConstPointer str1 = _str;
				// compare nullptr-ness
				if (!str1) { if (!str2) { return 0; } return -1; }
				if (!str2) { return 1; }
				// loop through strings
				while (*str1 && *str2 && --size && *str1 == *str2) {
					++str1; ++str2;
				} // return difference
				return *str1 - *str2;
			}


			// -- C O N V E R S I O N -----------------------------------------

			/* unsigned integer to string */
			template <Xf::is_unsigned_integral_c N>
			void to_string(N number) {
				// temporary string
				clear();

				constexpr N size = Xf::max_digits<N>();

				// WARNING: need to verify class
				// error doesn't checked with this method
				reserve(size);

				// convert number to string
				Size x = 0;
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
			template <Xf::is_signed_integral_c N>
			void to_string(N number) {
				// temporary string
				clear();

				constexpr Size size = Xf::max_digits<N>() + 1; // INFO: +1 for negative sign
				constexpr N type_min = Xf::min<N>();
				N base = 10;

				// WARNING: need to verify class
				// error doesn't checked with this method
				reserve(size);
				bool negative = false;

				Size x = 0;
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

			void _size_and_terminator(const Size size) {
				// set terminator
				_str[_size = size] = 0;
			}

			void _str_and_capacity(Pointer str, const Size capacity) {
				// set capacity
				_capacity = capacity;
				// set pointer
				_str = str;
			}

			/* set members */
			void _set_members(CharT* str, const Size size, const Size capacity) {
				// set members
				_str = str; _size = size; _capacity = capacity;
			}


			/* allocate members */
			void _unsafe_allocate(const Size capacity) {
				// check requested capacity
				if (!capacity) { return; }
				// allocate memory
				_str = Allocator::allocate(capacity);
				// set capacity on success
				if (_str) { _capacity = capacity; }
			}

			/* realloc */
			Pointer _realloc(const Size requested) {
				// reallocate memory
				return Allocator::realloc(_str, requested + 1);
			}

			/* allocate other */
			Pointer _allocate(const Size capacity) const {
				// check requested capacity
				if (!capacity) { return nullptr; }
				// allocate memory
				return Allocator::allocate(capacity);
			}


			/* deallocate members */
			void _deallocate(void) {
				// check if memory is allocated
				if (_str) { Allocator::deallocate(_str); }
				// reset members
				_initialize_members();
			}


			/* reallocate */
			void reallocate(const Size capacity);



			/* unsafe copy */
			void _unsafe_copy(Pointer dst, ConstPointer src, const Size size) {
				// loop through source
				for (Size x = 0; x < size; ++x) {
					// copy character to dst
					dst[x] = src[x];
				}
			}

			/* unsafe fill */
			void _unsafe_fill(Pointer dst, const CharT character, const Size size) {
				// loop through dst
				for (Size x = 0; x < size; ++x) {
					// set each character to character
					dst[x] = character;
				}
			}

			/* unsafe bzero */
			void _unsafe_bzero(Pointer dst, const Size size) {
				// loop through dst
				for (Size x = 0; x < size; ++x) {
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
					if (_size) { std::cout << "String:   " << _str      << std::endl; }
					else { std::cout       << "String:   " << "empty"   << std::endl; }
				} else { std::cout         << "String:   " << "nullptr" << std::endl; }
				std::cout                  << "Size:     " << _size     << std::endl;
				std::cout                  << "Capacity: " << _capacity << std::endl;
			}


		public:

			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------

			/* get len */
			static constexpr Size get_len(ConstPointer str) {
				// check if str is null
				if (!str) { return 0; }
				// loop through str
				for (Size x = 0; ; ++x) {
					// check if null
					if (!str[x]) { return x; }
				}
			}

			/* is upper */
			static bool is_uppercase(const CharT character) {
				// return true if character is upper
				return (character > 0x40 && character < 0x5b);
			}

			/* is lower */
			static bool is_lowercase(const CharT character) {
				// return true if character is lower
				return (character > 0x60 && character < 0x7b);
			}

			/* is alpha */
			static bool is_alpha(const CharT character) {
				// return true if character is alpha
				return (is_uppercase(character) || is_lowercase(character));
			}

			/* is digit */
			static bool is_digit(const CharT character) {
				// return true if character is digit
				return (character > 0x2f && character < 0x3a);
			}

			/* is hexadecimal */
			static bool is_hexadecimal(const CharT character) {
				// return true if character is hexadecimal
				return (is_digit(character)
						|| (character > 0x40 && character < 0x47)
						|| (character > 0x60 && character < 0x67));
			}

			/* is print */
			static bool is_printable(const CharT character) {
				// return true if character is printable
				return (character > 0x1f && character < 0x7f);
			}

			/* is whitespace */
			static bool is_whitespace(const CharT character) {
				// return true if character is white-space
				return ((character > 0x08 && character < 0x0e) || character == 0x20);
			}

			/* is control */
			static bool is_control(const CharT character) {
				// return true if character is control
				return character < 0x20 || character == 0x7f;
			}

			/* is graphical */
			static bool is_graphical(const CharT character) {
				// return true if character is graphical
				return (character > 0x20 && character < 0x7f);
			}

			/* is multi-byte */
			static bool is_multibyte(const CharT character) {
				// return true if character is multi-byte
				return character & 0x80;
			}

			/* is charset */
			static bool is_charset(const CharT character, ConstPointer charset) {
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
			static CharT to_uppercase(const CharT character) {
				// return uppercase character
				return is_lowercase(character) ? character - 0x20 : character;
			}

			/* to lowercase */
			static CharT to_lowercase(const CharT character) {
				// return lowercase character
				return is_uppercase(character) ? character + 0x20 : character;
			}


	};




	// -- S T A T I C  T E X T  C L A S S -------------------------------------

	/* forward declaration */
	template <Xf::is_char_c T, typename Xf::String<T>::Size N>
	class StaticText;

	/* c-string ascii type */
	template <typename Xf::String<char>::Size N>
	using CText = StaticText<char, N>;

	/* wide string type */
	template <typename Xf::String<wchar_t>::Size N>
	using WText = StaticText<wchar_t, N>;

	/* utf-8 string type */
	template <typename Xf::String<char8_t>::Size N>
	using Text8 = StaticText<char8_t, N>;

	/* utf-16 string type */
	template <typename Xf::String<char8_t>::Size N>
	using Text16 = StaticText<char16_t, N>;

	/* utf-32 string type */
	template <typename Xf::String<char8_t>::Size N>
	using Text32 = StaticText<char32_t, N>;


	// -- D E D U C T I O N  G U I D E S --------------------------------------

	/* null terminated string deduction guide */
	template <typename T>
	StaticText(const T* s)
		-> StaticText<T, sizeof(s) - 1>;

	/* null terminated string deduction guide */
	/*template <typename T, typename Xf::String<T>::Size N>
	StaticText(const T (&)[N])
		-> StaticText<T, N>;*/

	/* buffer string deduction guide */
	template <typename T, typename Xf::String<T>::Size N>
	StaticText(const T (&)[N], typename Xf::String<T>::Size)
		-> StaticText<T, N - 1>;



	/* copy constructor deduction guide */
	//template <typename T, typename Xf::String<T>::Size N>
	//StaticText(const StaticText<T, N>&)
		//-> StaticText<T, N>;

	/* default constructor deduction guide */
	//StaticText(void) -> StaticText<char, 3>;



	/* static text class */
	template <Xf::is_char_c T, typename Xf::String<T>::Size N>
	class StaticText {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* character type */
			using CharT         = remove_cv_t<T>;

			/* size type */
			using Size          = typename Xf::String<CharT>::Size;

			/* comparison type */
			using Signed        = typename Xf::String<CharT>::Signed;

			/* pointer type */
			using Pointer       = typename Xf::String<CharT>::Pointer;

			/* reference type */
			using Reference     = typename Xf::String<CharT>::Reference;

			/* move reference type */
			using MoveReference = typename Xf::String<CharT>::MoveReference;

			/* const reference type */
			using ConstRef      = typename Xf::String<CharT>::ConstRef;

			/* const pointer type */
			using ConstPointer  = typename Xf::String<CharT>::ConstPointer;


		private:

			// -- M E M B E R S -----------------------------------------------

			/* pointer */
			CharT _str[N + 1];


		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			consteval StaticText(void) noexcept {
				// code here...
				for (Size x = 0; x <= N; ++x) {
					_str[x] = '\0';
				}
			}

			/* null-terminated string constructor */ // INFO: this handle array
			consteval StaticText(ConstPointer str) noexcept {

				for (Size x = 0; x < N; ++x) {
					_str[x] = str[x];
				}
				_str[N] = '\0';
			}


			/*
			constexpr StaticText(const CharT str[N]) noexcept {

				for (Size x = 0; x < N; ++x) {
					_str[x] = str[x];
				}
				_str[N] = '\0';
			}*/

			/* buffer string constructor */
			consteval StaticText(ConstPointer str, Size size) noexcept {

				Size x = 0;
				for (;x < size && x < N; ++x) {
					_str[x] = str[x];
				}
				_str[x] = '\0';
			}

			/* fill constructor */
			consteval StaticText(const CharT character, Size size) noexcept {

				Size x = 0;
				for (;x < size && x < N; ++x) {
					_str[x] = character;
				}
				_str[x] = '\0';
			}

			/* copy constructor */
			consteval StaticText(const StaticText& other) noexcept {

				/*
				for (Size x = 0; x < N; ++x) {
					_str[x] = other._str[x];
				}
				_str[N] = '\0';
				*/
			}

			/* move constructor */
			consteval StaticText(StaticText&& other) noexcept {

				/*
				for (Size x = 0; x < N; ++x) {
					_str[x] = other._str[x];
				}
				_str[N] = '\0';
				*/
			}


			// -- S U B S C R I P T  O P E R A T O R S ------------------------

			/* subscript operator */
			consteval Reference operator[](const Size index) noexcept {
				return _str[index];
			}

			/* const subscript operator */
			consteval ConstRef operator[](const Size index) const noexcept {
				return _str[index];
			}


			// -- A C C E S S O R S -------------------------------------------

			/* empty */
			consteval bool empty(void) const noexcept {
				// return true if empty
				return *_str == 0;
			}

			/* not empty */
			consteval bool not_empty(void) const noexcept {
				// return true if not empty
				return *_str != 0;
			}

			/* length */
			consteval Size length(void) const noexcept {
				for (Size x = 0; x < N; ++x) {
					if (_str[x] == '\0') {
						return x;
					}
				} return N;
			}

			/* size */
			consteval Size size(void) const noexcept {
				// return size
				return length();
			}

			/* capacity */
			consteval Size capacity(void) const noexcept {
				// return capacity
				return N;
			}

			/* available */
			consteval Size available(void) const noexcept {
				// return available space
				return N - length();
			}

			/* pointer */
			consteval Pointer pointer(void) {
				// return pointer to first element
				return _str;
			}

			/* const pointer */
			consteval ConstPointer pointer(void) const {
				// return constant pointer to first element
				return _str;
			}


			consteval void set_size(const Size size) noexcept {
				if (size <= N) {
					_str[size] = '\0';
				}
			}

			consteval void reverse(void) noexcept {

				Size x = 0;
				Size y = length() - 1;

				while (x < y) {
					CharT temp = _str[x];
					_str[x] = _str[y];
					_str[y] = temp;
					++x;
					--y;
				}
			}

			// -- S T A T I C  F U N C T I O N S ------------------------------




	};

	/* number to static text */
	template <Xf::is_char_c C = char, Xf::integral_c T>
	consteval auto to_text(const T number) {

		// remove const and volatile
		using Type = Xf::remove_cv_t<T>;

		SizeT digits = Xf::static_digits<Xf::Dec, Type>(number);

		Xf::StaticText<C, digits> text;

		Type num = number;

		SizeT x = 0;

		do {
			text[x] = number % 10 + '0';
			number /= 10;
			++x;
		} while (number);

		text.set_size(x);
		text.reverse();

		return text;
	}

	/* deduction guide */
	//template <Xf::is_char_c C, Xf::integral_c T, T N>
	//to_text(void) -> to_text<C, T, N>(void);


	// -- S C R O L L A B L E  S T R I N G ------------------------------------

	// class to encapsulate a string used for being displayed on a screen
	// in a scrollable view

	template <Xf::is_char_c T>
	class ScrollString {

		private:

			// -- M E M B E R S -----------------------------------------------

			/* string */
			Xf::String<T> _str;

			/* view size */
			Size _view_size; // size of view

			/* start position */
			Size _view_start; // offset from start of string

			/* view position */
			Size _string_cursor; // position in string

			/* view position */
			Size _screen_cursor; // position in view

			/* scroll offset */
			Size _scrolloff; // vim-like scroll offset (half of view size)



		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			ScrollString(void) noexcept
			: _str{ }, _view_size{0}, _view_start{0}, _string_cursor{0}, _screen_cursor{0} {
				// code here...
			}

			/* destructor */
			~ScrollString(void) noexcept = default;


			// -- P U B L I C  S E T T E R S ----------------------------------

			/* set view size */
			void set_view_width(const Size width) noexcept {
				// set view size and scroll offset (half of view size)
				_scrolloff = (_view_size = width) / 2;
			}





			// -- P U B L I C  M O D I F I E R S ------------------------------

			/* insert */
			void insert(const Xf::String<T> input) {
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



			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* const pointer */
			typename Xf::String<T>::ConstPointer view_pointer(void) const {
				// return constant pointer to first display element
				return _str.pointer() + _view_start;
			}

			/* view size */
			Size view_size(void) const {
				// check if string is smaller than view size
				if (_str.length() < _view_size) {
					// return string length
					return _str.length();
				} // else return view size
				return _view_size;
			}

			/* get screen cursor position */
			Size cursor_position(void) const {
				// return screen cursor position
				return _screen_cursor;
			}

			/* get string */
			const Xf::String<T>& string(void) const {
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



};









#endif
