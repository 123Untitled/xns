#include "String.hpp"


#define nullchar '\0'


// -- C O N S T R U C T O R S -------------------------------------------------

/* default constructor */
String::String(void)
// initializations
: _str{nullptr}, _size{0}, _capacity{0} {
	// code here...
}

/* capacity constructor */
String::String(const Size capacity)
// initializations
: _str{allocation(capacity)}, _size{0}, _capacity{capacity} {
	// code here...
}

/* null-terminated string constructor */
String::String(const Char* str)
// initializations
: String{ } {
	// check if string is not empty
	if ((_size = get_len(str)) != 0) {
		// set capacity
		_capacity = _size + 1;
		// allocate memory
		_str = allocation(_capacity);
		// set nullchar
		_str[_size] = '\0';
		// copy string
		unsafe_copy(_str, str, _size);
	}
}


/* buffer constructor */
String::String(const char* str, const Size size)
: String{} {
	// initialize String with char * and len
	allocate(size);
	//copy((Char *)string);
}

/* fill constructor */
String::String(const char character, const Size size)
: String{} {
	// initialize String with char * and len
	allocate(size);
	fill(character);
}

/* copy constructor */
String::String(const String& copy)
// initializations
: String{copy._str, copy._size} {
	// nothing to do
}

/* move constructor */
String::String(String&& move) noexcept
// initializations
: _str{move._str}, _size{move._size}, _capacity{move._capacity} {
	// Copy the data pointer and its length from the
	move.initialize_members();
}

/* destructor */
String::~String(void) {
	// free memory
	deallocate();
}


// -- A S S I G N -------------------------------------------------------------

/* null-terminated string assignment */
String& String::assign(const char* str) {
	// assign string
	return assign(str, get_len(str));
}

/* buffer assignment */
String& String::assign(const char* str, const Size size) {
	// check if capacity is sufficient
	if (size > _capacity) {
		// reallocate memory
		reallocate(size);
	}
	// copy string
	copy(str);
	// return this
	return *this;
}

/* fill assignment */
String& String::assign(const char character, const Size size) {
	// check if capacity is sufficient
	if (size > _capacity) {
		// reallocate memory
		reallocate(size);
	}
	// fill string
	fill(character);
	// return this
	return *this;
}

/* copy assignment */
String& String::assign(const String& str) {
	// check if capacity is sufficient
	if (str._size > _capacity) {
		// reallocate memory
		reallocate(str._size);
	}
	// copy string
	copy(str._str);
	// return this
	return *this;
}

/* move assignment */
String& String::assign(String&& str) noexcept {
	// check if capacity is sufficient
	if (str._size > _capacity) {
		// reallocate memory
		reallocate(str._size);
	}
	// copy string
	copy(str._str);
	// return this
	return *this;
}



// -- O P E R A T O R S -------------------------------------------------------

/* assignment operator */
String& String::operator=(const String& copy) {
	// check for self-assignment
	if (this != &copy) {
		// delete self allocated memory
		if (_str != nullptr) { delete[] _str; }
		// check if copy is empty
		if (copy._str != nullptr) {
			// new memory allocation
			_str = new char[copy._capacity];
			// loop through copy string
			for (Size x = 0; x < copy._size; ++x) {
				// copy each character
				_str[x] = copy._str[x];
			} // set size
			_size = copy._size;
			// set capacity
			_capacity = copy._capacity;
		}
		else {
			// set to empty
			_str = nullptr; _size = 0; _capacity = 0;
		}
	} // return self reference
	return *this;
}


/* move assignment operator */
String& String::operator=(String&& move) noexcept {
	// check for self-assignment
	if (this != &move) {
		// delete self allocated memory
		if (_str != nullptr) { delete[] _str; }
		// copy the data pointer and its length from the
		_str = move._str; _size = move._size; _capacity = move._capacity;
		// release the data pointer from the source object so that
		// the destructor does not free the memory multiple times.
		move.initialize_members();
	} // return self reference
	return *this;
}


String& String::operator=(const char* str) {

	//*this = String{str};

	return *this;
}


/* subscript operator */
String::Reference String::operator[](const Size index) {
	return (_str[index]);
}

/* const subscript operator */
 String::ConstRef String::operator[](const Size index) const {
	return (_str[index]);
}

/* bool operator */
String::operator bool(void) const {
	return _str != nullptr;
}


/*
constexpr String String::operator+(const String& add) const {

	String string;

	if (_str || add._str) {
		string.allocate(_size + add._size);
		string.append(*this);
		string.append(add);
	}
	return (string);
} */
/*bool String::operator==(const String& compare) const {
	return (strcmp(compare._str, _str));
	//return (cmpr(equal));
}

bool String::operator==(const char* compare) const {
	return (strcmp(compare, _str));
	//return (strcmp(equal));
} */

// -- A C C E S S O R S -------------------------------------------------------

/* length */
String::Size String::length(void) const {
	// return the length of the string
	return _size;
}

/* capacity */
String::Size String::capacity(void) const {
	// return the allocated capacity of the string
	return _capacity;
}

/* getAvailable */
String::Size String::available(void) const {
	// return the available space in the string
	return _capacity - _size;
}

/* const pointer */
String::ConstPointer String::pointer(void) const {
	// return the pointer to the string
	return _str;
}


// -- P U B L I C   M E T H O D S ---------------------------------------------

/* move */
void String::move(String& owner) {
	// check for self-assignment
	if (this != &owner) {
		// delete owner allocated memory
		owner.deallocate();
		// set owner to self
		owner._str      = _str;
		owner._size     = _size;
		owner._capacity = _capacity;
		// set self to empty
		initialize_members();
	}
}




// -- P R I V A T E   M E T H O D S -------------------------------------------

/* initialize memory */
void String::initialize_memory(void) {
	// check if memory is allocated
	if (_str != nullptr) {
		// loop through memory
		for (Size x = 0; x < _capacity; ++x) {
			// set each character to null
			_str[x] = '\0';
		}
	}
}

/* initialize members */
void String::initialize_members(void) {
	// initialize members
	_str = nullptr; _size = 0; _capacity = 0;
}

/* allocate */
void String::allocate(const Size capacity) {
	// check new capacity is not zero
	if (capacity) {
		// deallocate previous allocated memory
		deallocate();
		// allocate new memory
		_str = new Char[capacity];
		// set capacity
		_capacity = capacity;
		// initialize memory
		initialize_memory();
	}
}

/* reallocate */
void String::reallocate(const Size capacity) {
	// check if capacity is greater than current capacity
	if (capacity > _capacity) {
		// allocate new memory
		char* str = new char[capacity];
		// loop through previous string
		for (Size x = 0; x < _size; ++x) {
			// copy each character
			str[x] = _str[x];
		}
		str[_size] = '\0';
		// deallocate previous memory
		delete[] _str;
		// set new memory
		_str = str;
		// set capacity
		_capacity = capacity;
	}
}


/* deallocate */
void String::deallocate(void) {
	// check if memory is allocated
	if (_str) {
		// delete memory
		delete[] _str;
	} // initialize members
	initialize_members();
}


/* allocation */
Char* String::allocation(const Size capacity) const {
	// check capacity is not zero
	if (capacity) {
		// allocate new memory space
		Char* str = new Char[capacity];
		// initialize memory
		unsafe_bzero(str, capacity);
		// return new memory space
		return str;
	} // else return null
	return nullptr;
}

void String::copy(Char *dest, const Char *src, UInt32 start) {

	UInt32 x = 0;

	if (dest && src) {
		while (src[x])
			dest[start++] = src[x++];
	}
}

void String::copy(const Char* str) {

	if (_str && str) {
		UInt32	 x;
		for (x = 0; str[x] && x < _capacity; x++) {
			_str[x] = str[x];
		}
		_size = x;
	}
}

void String::fill(const Char character) {

	if (_str) {
		for (UInt32 x = 0; x < _capacity; x++) {
			_str[x] = character;
		} _size = _capacity;
	}
}

/* unsafe copy */
void String::unsafe_copy(Char* dst, const Char* src, const Size size) {
	// loop through src
	for (Size x = 0; x < size; ++x) {
		// copy character to dst
		dst[x] = src[x];
	}
}

/* unsafe bzero */
void String::unsafe_bzero(Char* dst, const Size size) {
	// loop through dst
	for (Size x = 0; x < size; ++x) {
		// set each character to null
		dst[x] = '\0';
	}
}









bool String::resize(const UInt32 len) {
	if (_str && len < _size) {
		_str[len] = nullchar;
		_size = len;
		return (true);
	}
	return (false);
}

void String::pull_repeat(void) {

	Size x = 0;
	Size z = 0;

	if (_str) {
		while (z + x < _size) {
			while (_str[z + x] == _str[z + x + 1])
				x++;
			_str[z] = _str[z + x];
			z++;
		} _size = z;
		_str[_size] = nullchar;
	}
}


/* forward remove duplicates */
void String::forward_remove_duplicates(void) {

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
void String::backward_remove_duplicates(void) {

	bool seen[UINT8_MAX] = { false };

	if (!_str) { return; }

	UInt8* ptr = reinterpret_cast<UInt8*>(_str);

	Size x = _size;
	Size z = x;

	while (x--) {
		if (seen[ptr[x]]) { continue; }
		seen[ptr[x]] = true;
		_str[--z] = _str[x];
	}
	_size = _size - z;

	for (x = 0; x < _size; ++x) {
		_str[x] = _str[x + z];
	} _str[_size] = 0;

}

/* split */
LString String::split(String&& sep) const {
	// create a empty list
	LString lst{ };
	// check if string is empty
	if (!_str) { return lst; }
	// loop through string characters
	for (Size z, x = 0; _str[x]; x += z) {
		// initialize z
		z = 0;
		// skip separator characters
		while (is_charset(_str[x], sep._str)) { ++x; }
		// count non-separator characters
		while (_str[x + z] && !is_charset(_str[x + z], sep._str))
		{	++z; }
		// check if z is not zero
		if (z) {
			// append a new string to the list
			lst.add_back(String{&(_str[x]), z});
		}
	} // return the list
	return lst;
}


LString String::split2(String&& sep) const {

	UInt32 z = 0;
	LString lst;

	if (!_str)
		return (lst);
	UInt32 x = 0;
	while (_str[x]) {
		z = 0;
		if (is_charset(_str[x + z], sep._str)) {
			while (is_charset(_str[x + z], sep._str))
				z++;
			lst.add_back(String{&(_str[x]), z});
		}
		x += z;
		z = 0;
		if (_str[x + z] && !is_charset(_str[x + z], sep._str)) {
			while (_str[x + z] && !is_charset(_str[x + z], sep._str))
				z++;
			lst.add_back(String{&(_str[x]), z});
		}
		x += z;
	}
	return (lst);
	// what is the difference between split and split2?
	// split2 keeps the separators in the list
}



/* print string */
void String::print_string(void) const {
	if (_str && _size) {
		write(STDOUT_FILENO, _str, _size);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/* debug string */
void String::debug_string(void) const {
	if (_str) {
		if (_size) {
			std::cout << "String: "   << std::setw(10) << _str      << std::endl;
			std::cout << "Size: "     << std::setw(10) << _size     << std::endl;
			std::cout << "Capacity: " << std::setw(10) << _capacity << std::endl;
			return;
		}
		write(STDOUT_FILENO, "(empty)", 7);
		return;
	}
	write(STDOUT_FILENO, "(null)", 6);
}







String& String::append(const String& append) {

	if (!append._str)
		return *this;
	if (!_str) {
		allocate(append._size);
		copy(append._str);
	}
	else if (append._size > available()) {

		Char *tmp = allocation(_size + append._size);
		copy(tmp, _str, 0);
		copy(tmp, append._str, _size);
		delete [] _str;
		_str = tmp;
		_size += append._size;
		_capacity = _size;
	}
	else {
		copy(_str, append._str, _size);
		_size += append._size;
	}
	return *this;
}

/*
void String::appendAt(const String &append, const UInt32 index) {

	if (append._str) {
		if (!_str) {
			createString(append._size);
			copy(append._str);
		}
		else if (append._size > getAvailable()) {

			Char *tmp = allocation(_size + append._size);
			copy(tmp, _str, 0);
			copy(tmp, append._str, _size);
			delete [] _str;
			_str = tmp;
			_size += append._size;
			_capacity = _size;
		}
		else {
			copy(_str, append._str, _size);
			_size += append._size;
		}
	}
}*/




void String::addAt(const Char c, UInt32 index)
{
	if (!_str) {
		allocate(1);
		*_str = c;
		_size = 1;
		return;
	}

	if (index > _size)
		index = _size;

	if (!available()) {

		Char	*tmp;
		UInt32	size;

		if (_capacity)
			size = _capacity * 2;
		else size = 1;
		tmp = allocation(size);
		++_size;
		tmp[index] = c;
		for (UInt32 x = 0; x < index; x++) {
			tmp[x] = _str[x];
		}
		for (UInt32 x = index; x < _size; x++) {
			tmp[x + 1] = _str[x];
		}
		delete[] _str;
		_str = tmp;
		_capacity = size;
	}
	else {

		for (UInt32 x = _size; x > index; x--) {
			_str[x] = _str[x - 1];
		}
		++_size;
		_str[index] = c;
	}
	_str[_size] = '\0';
}

void String::deleteAt(const UInt32 index) {
	// idle if nullptr or index exceed len
	if (_str != nullptr && index < _size) {
		// decrease current len
		--_size;
		//
		for (UInt32 x = index; x < _size; x++) {
			_str[x] = _str[x + 1];
		} // assign new null character
		_str[_size] = nullchar;
	}
}

/*
UInt32 String::getLastWordIndex(const UInt32 index) {

	return (index);
}*/


bool String::cmpr(const String &compare) const {
	return (strcmp(_str, compare._str));
}

bool String::cmpr(const char* compare) const {
	return (strcmp(_str, compare));
}

bool String::ncmpr(const String& compare) const {
	return (strncmp(_str, compare._str, _size));
}

bool String::ncmpr(const char* compare) const {
	return (strncmp(_str, compare, _size));
}

bool String::strcmp(const Char *first, const Char* second) const {

	if (!first || !second)
		return (first == second);
	while (*first && *second
			&& *first == *second) {
		first++;
		second++;
	} return (*first == *second);
}

bool String::strncmp(const Char* first, const Char* second, UInt32 len) const {

	if (!first || !second)
		return (first == second);
	while (*first && *second && --len
			&& *first == *second) {
		first++;
		second++;
	} return (*first == *second);
}


// -- S E A R C H I N G -------------------------------------------------------

/* next word */
String::Size String::next_word(const Size index) const {
	// idle if nullptr or index exceed length
	if (_str != nullptr && index < _size) {

		Size x = index;

		// skip printable characters
		while (is_printable(_str[x])) { ++x; }

		// skip whitespace characters
		while (is_whitespace(_str[x])) { ++x; }

		// check null character
		if (_str[x]) return x;

	} // else return unchanged index
	return index;
}

/* previous word */
String::Size String::previous_word(const Size index) const {
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
String::Size String::next_character(const Size index, const char character) const {
	// idle if nullptr or index exceed length
	if (_str != nullptr && index < _size) {
		// search for character
		for (Size x = index; x < _size; ++x) {
			if (_str[x] == character) return x;
		}
	} // else return unchanged index
	return index;
}

/* previous character */
String::Size String::previous_character(const Size index, const char character) const {
	// idle if nullptr or index exceed length
	if (_str != nullptr && index < _size) {
		// search for character
		for (Size x = index; x != 0; --x) {
			if (_str[x] == character) return x;
		}
	} // else return unchanged index
	return index;
}

// -- M O D I F I E R S -------------------------------------------------------

/* clear */
void String::clear() {
	_size = 0;
}

/* to uppercase */
void String::to_uppercase(void) {
	// check if string is not empty
	if (_str != nullptr) {
		// convert to uppercase
		for (Size x = 0; x < _size; ++x) {
			_str[x] = String::to_uppercase(_str[x]);
		}
	}
}

/* to lowercase */
void String::to_lowercase(void) {
	// check if string is not empty
	if (_str != nullptr) {
		// convert to lowercase
		for (Size x = 0; x < _size; ++x) {
			_str[x] = String::to_lowercase(_str[x]);
		}
	}
}



// -- P U B L I C  S T A T I C  M E T H O D S ---------------------------------

/* get len */
String::Size String::get_len(const char* str) {
	// initialize length
	Size x = 0;
	// check string allocation
	if (str) {
		// count string length
		while (str[x]) { ++x; }
	} // return length
	return x;
}

/* is uppercase */
bool String::is_uppercase(const char character) {
	// return true if character is upper
	return (character > 0x40 && character < 0x5b);
}

/* is lowercase */
bool String::is_lowercase(const char character) {
	// return true if character is lower
	return (character > 0x60 && character < 0x7b);
}

/* is alpha */
bool String::is_alpha(const char character) {
	// return true if character is alpha
	return (is_uppercase(character) || is_lowercase(character));
}

/* is digit */
bool String::is_digit(const char character) {
	// return true if character is digit
	return (character > 0x2f && character < 0x3a);
}

/* is hexadecimal */
bool String::is_hexadecimal(const char character) {
	// return true if character is hexadecimal
	return (is_digit(character)
			|| (character > 0x40 && character < 0x47)
			|| (character > 0x60 && character < 0x67));
}

/* is printable */
bool String::is_printable(const char character) {
	// return true if character is printable
	return (character > 0x1f && character < 0x7f);
}

/* is whitespace */
bool String::is_whitespace(const char character) {
	// return true if character is white-space
	return ((character > 0x08 && character < 0x0e) || character == 0x20);
}

/* is graphical */
bool String::is_graphical(const char character) {
	// return true if character is graphical
	return (character > 0x20 && character < 0x7f);
}

/* is control */
bool String::is_control(const char character) {
	// return true if character is control
	return (character < 0x20 || character == 0x7f);
}

/* is multi-byte */
bool String::is_multibyte(const char character) {
	// return true if character is multi-byte
	return (character > 0x7f);
}



/* is only */
bool String::is_only(bool (*is_type)(const char)) const {
	// check string allocation
	if (_str) {
		// loop through string
		for (Size x = 0; x < _size; ++x) {
			// return false if character is not of type
			if (!is_type(_str[x])) { return false; }
		} // return true if all characters are of type
		return true;
	} // return false if string is nullptr
	return false;
}



bool String::is_charset(const Char character, const char* charset) {
	if (charset) {
		while (*charset) {
			if (character == *(charset)++)
				return (true);
		} } return (false);
}

/* to uppercase */
char String::to_uppercase(const char character) {
	// return uppercase character
	return (is_lowercase(character) ? character - 0x20 : character);
}

/* to lowercase */
char String::to_lowercase(const char character) {
	// return lowercase character
	return (is_uppercase(character) ? character + 0x20 : character);
}








