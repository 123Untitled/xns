#include <Str.hpp>


void Str::debug(const char* message) const {

	if (_debug == true) {
		printf("%s::", typeid(*this).name());
		//puts(message);
		printf("%s -> ", message);
		fflush(stdout);
		if (_str)
			puts(_str);
		else
			printf("\n");
	}
}

void Str::debugOn(void) { _debug = true; }

void Str::debugOff(void) { _debug = false; }

bool Str::_debug = false;


/* --------------------------------------------------- */

/* CONSTRUCTORS & DESTRUCTOR */

/* default constructor */
Str::Str(void)
: _str{nullptr}, _len{0}, _capacity{0} {
	debug(DEFAULT_CONSTRUCTOR);
}

/* copy constructor */
Str::Str(const Str& copy)
: Str{copy._str, copy._len} {
	// copy constructor
	debug(COPY_CONSTRUCTOR);
}

/* Move constructor */
Str::Str(Str&& move) noexcept
: _str{move._str}, _len{move._len}, _capacity{move._capacity} {
	// Copy the data pointer and its length from the
	move.init();
	debug(MOVE_CONSTRUCTOR);
}

/* string constructor */
Str::Str(const char* string)
: Str{} {
	createStr(len(string));
	copy(string);
	debug(STRING_CONSTRUCTOR);
}

/* string size constructor */
Str::Str(const char* string, const UInt32 size)
: Str{} {
	// initialize Str with char * and len
	createStr(size);
	copy((Char *)string);
	debug(STRINGSIZE_CONSTRUCTOR);
}

/* capacity constructor */
Str::Str(const UInt32 size)
: Str{} {
	// initialize Str with char * and len
	createStr(size);
	debug(SIZE_CONSTRUCTOR);
}

/* fill constructor */
Str::Str(const char character, const UInt32 size)
: Str{} {
	// initialize Str with char * and len
	createStr(size);
	fill(character);
	debug(FILL_CONSTRUCTOR);
}

/* destructor */
Str::~Str(void) {
	debug(DESTRUCTOR);
	deleteStr();
}

/* --------------------------------------------------- */

/* createStr */
void Str::createStr(const UInt32 size) {
	if (size) {
		_str		= new Char[size + 1];
		_str[size]	= nullchar;
		_capacity	= size;
		reset();
	}
}

/* reset */
void Str::reset(void) {
	if (_str) {
		for (UInt32 x = 0; x < _capacity; x++) {
			_str[x] = 0;
		} _len = 0;
	}
}


/* deleteStr */
void Str::deleteStr(void) {
	if (_str)
		delete[] _str;
	init();
}

void Str::init(void) {
	_str = nullptr;
	_capacity = 0;
	_len = 0;
}



/* INIT METHODS */

void Str::copy(const Char* str) {

	if (_str && str) {
		UInt32	 x;
		for (x = 0; str[x] && x < _capacity; x++) {
			_str[x] = str[x];
		}
		_len = x;
	}
}

void Str::fill(const Char character) {

	if (_str) {
		for (UInt32 x = 0; x < _capacity; x++) {
			_str[x] = character;
		} _len = _capacity;
	}
}

UInt32 Str::len(const Char* str) {

	UInt32	 x = 0;
	if		(str) {
		while (str[x])
			x++;
	} return (x);
}


/* GETTERS & SETTERS */

UInt32 Str::getLen(void) const {
	return (_len);
}

char* Str::getPointer(void) const {
	return (_str);
}

UInt32 Str::getCapacity(void) const {
	return (_capacity);
}

StrErr Str::ownerSwap(Str& owner) {

	owner.deleteStr();
	owner._str = _str;
	owner._capacity = _capacity;
	owner._len = _len;
	init();
	//printf("Str ownerSwap %s\n", owner._str);
	return (STR_SUCCESS);
}


/* OPERATORS OVERLOAD */

Str& Str::operator=(const Str& other) {

	//printf("Str copy operator\n");
	//*this = Str{other};
	//printf("here\n");
	deleteStr();
	if (other._str) {
		createStr(other._capacity);
		_len = other._len;
		for (UInt32 x = 0; x < _len; x++) {
			_str[x] = other._str[x];
		}
	} return (*this);
}

Str& Str::operator=(Str&& other) {
	//printf("Str move operator\n");
	other.ownerSwap(*this);
	debug(MOVE_OPERATOR);
	return (*this);
}

Str& Str::operator=(const char* string) {
	deleteStr();
	*this = Str{string};
	return (*this);
}

Str Str::operator+(const Str& add) {

	Str string;

	if (_str || add._str) {
		string.createStr(_len + add._len);
		string.append(*this);
		string.append(add);
	}
	return (string);
}

/* index operator */
char& Str::operator[](const UInt32 index) const {
	return (_str[index]);
}

const char* Str::operator*(void) const {
	debug(INDIRECTION_OPERATOR);
	return(_str);
}

bool Str::operator==(const Str& compare) const {
	return (strcmp(compare._str, _str));
	//return (cmpr(equal));
}

bool Str::operator==(const char* compare) const {
	return (strcmp(compare, _str));
	//return (strcmp(equal));
}

Str::operator bool(void) const {
	return (_str);
}


void Str::print(void) const {
	printf(	"%9s :: %s\n"\
			"%9s :: %u\n"\
			"%9s :: %u\n\n",
			"_str",			_str,
			"_capacity",	_capacity,
			"_len",			_len
	);
}


bool Str::setLen(const UInt32 len) {
	if (_str && len < _len) {
		_str[len] = nullchar;
		_len = len;
		return (true);
	}
	return (false);
}

void Str::pullRepeat(void) {

	UInt32 x = 0;
	UInt32 z = 0;

	if (_str) {
		while (z + x < _len) {
			while (_str[z + x] == _str[z + x + 1])
				x++;
			_str[z] = _str[z + x];
			z++;
		} _len = z;
		_str[_len] = nullchar;
	}
}

void Str::pullTwin(void) {

	if (!_str)
		return;
	for (UInt32 x = 0; _str[x + 1]; x++) {
		for (UInt32 z = x + 1; _str[z]; z++) {
			if (_str[x] != _str[z])
				continue;
			for (z = x; _str[z]; z++) {
				_str[z] = _str[z + 1];
			} _len--; x--;
			break;
		}
	}
}

// split string
Strlst Str::split(Str&& sep) const {
	Strlst	lst{};
	UInt32	z = 0;
	// check string is not null
	if (!_str)
		return (lst);
	// iterate over string
	for (UInt32 x = 0; _str[x]; x += z) {
		z = 0;
		// skip separators
		while (isSet(_str[x], sep._str))
			x++;
		// count non-separators chars
		while (_str[x + z] && !isSet(_str[x + z], sep._str))
			z++;
		// if word, add to string list
		if (z)
			lst.addBack(Str{&(_str[x]), z});
	} // return list
	return (lst);
}


Strlst Str::split2(Str&& sep) const {

	UInt32 z = 0;
	Strlst lst;

	if (!_str)
		return (lst);
	UInt32 x = 0;
	while (_str[x]) {
		z = 0;
		if (isSet(_str[x + z], sep._str)) {
			while (isSet(_str[x + z], sep._str))
				z++;
			lst.addBack(Str{&(_str[x]), z});
		}
		x += z;
		z = 0;
		if (_str[x + z] && !isSet(_str[x + z], sep._str)) {
			while (_str[x + z] && !isSet(_str[x + z], sep._str))
				z++;
			lst.addBack(Str{&(_str[x]), z});
		}
		x += z;
	}
	return (lst);
}




void Str::print(const Char *var, const int flag) const {
	/*
	if (_str) {
		int i = 0;
		while (_str[i])
			printf("%d\n", _str[i++]);
	}*/
	if (var)
		printf("%9s :: %s\n", "variable",		var);
	if (flag)
	{
		UInt32 x = 0;
		while (_str[x]) {
			printf("%d ", (unsigned char)_str[x]);
			fflush(stdout);
			x++;
		}
		printf("\n");
	}
	else {
		printf(	"%9s :: %s\n"\
				"%9s :: %u\n"\
				"%9s :: %u\n\n",
				"_str",			_str,
				"_capacity",	_capacity,
				"_len",			_len
		);
	}
}


/* getAvailable */
UInt Str::getAvailable(void) const {
	return (_capacity - _len);
}

/* allocation */
char* Str::allocation(const UInt size) const {
	char *tmp = new char[size + 1]();
	tmp[size] = nullchar;
	return (tmp);
}

void Str::copy(Char *dest, const Char *src, UInt32 start) {

	UInt32 x = 0;

	if (dest && src) {
		while (src[x])
			dest[start++] = src[x++];
	}
}


void Str::append(const Str &append) {

	if (!append._str)
		return;
	if (!_str) {
		createStr(append._len);
		copy(append._str);
	}
	else if (append._len > getAvailable()) {

		Char *tmp = allocation(_len + append._len);
		copy(tmp, _str, 0);
		copy(tmp, append._str, _len);
		delete [] _str;
		_str = tmp;
		_len += append._len;
		_capacity = _len;
	}
	else {
		copy(_str, append._str, _len);
		_len += append._len;
	}
}

/*
void Str::appendAt(const Str &append, const UInt32 index) {

	if (append._str) {
		if (!_str) {
			createStr(append._len);
			copy(append._str);
		}
		else if (append._len > getAvailable()) {

			Char *tmp = allocation(_len + append._len);
			copy(tmp, _str, 0);
			copy(tmp, append._str, _len);
			delete [] _str;
			_str = tmp;
			_len += append._len;
			_capacity = _len;
		}
		else {
			copy(_str, append._str, _len);
			_len += append._len;
		}
	}
}*/




void Str::addAt(const Char c, UInt32 index)
{
	if (!_str) {
		createStr(1);
		*_str = c;
		_len = 1;
		return;
	}

	if (index > _len)
		index = _len;

	if (!getAvailable()) {

		Char	*tmp;
		UInt32	size;

		if (_capacity)
			size = _capacity * 2;
		else size = 1;
		tmp = allocation(size);
		++_len;
		tmp[index] = c;
		for (UInt32 x = 0; x < index; x++) {
			tmp[x] = _str[x];
		}
		for (UInt32 x = index; x < _len; x++) {
			tmp[x + 1] = _str[x];
		}
		delete[] _str;
		_str = tmp;
		_capacity = size;
	}
	else {

		for (UInt32 x = _len; x > index; x--) {
			_str[x] = _str[x - 1];
		}
		++_len;
		_str[index] = c;
	}
	_str[_len] = '\0';
}

void Str::deleteAt(const UInt32 index) {
	// idle if nullptr or index exceed len
	if (_str != nullptr && index < _len) {
		// decrease current len
		--_len;
		//
		for (UInt32 x = index; x < _len; x++) {
			_str[x] = _str[x + 1];
		} // assign new null character
		_str[_len] = nullchar;
	}
}

/*
UInt32 Str::getLastWordIndex(const UInt32 index) {

	return (index);
}*/


bool Str::cmpr(const Str &compare) const {
	return (strcmp(_str, compare._str));
}

bool Str::cmpr(const char* compare) const {
	return (strcmp(_str, compare));
}

bool Str::ncmpr(const Str& compare) const {
	return (strncmp(_str, compare._str, _len));
}

bool Str::ncmpr(const char* compare) const {
	return (strncmp(_str, compare, _len));
}

bool Str::strcmp(const Char *first, const Char* second) const {

	if (!first || !second)
		return (first == second);
	while (*first && *second
			&& *first == *second) {
		first++;
		second++;
	} return (*first == *second);
}

bool Str::strncmp(const Char* first, const Char* second, UInt32 len) const {

	if (!first || !second)
		return (first == second);
	while (*first && *second && --len
			&& *first == *second) {
		first++;
		second++;
	} return (*first == *second);
}



UInt32 Str::getPreviousWordIndex(UInt index) {

	UInt x = index;

	if (_str != nullptr) {

		if (index >= _len)
			x = _len - 1;

		while (x != 0 && Str::isSpace(_str[x])) {
			x--;
		}
		while (x != 0 && Str::isAlpha(_str[x])) {
			x--;
		}
		return (x + 1);
	}

	return (index);

	/*
	if (ptr[pos] != 32 && pos && ptr[pos - 1] == 32)
		x++;
	while (pos - x && ptr[pos - x] == 32)
		x++;
	while (pos - x) {

		if (ptr[pos - x] == 32) {
			x--;
			break;
		}
		x++;
	}
	pos -= x;
	*/
}



UInt32 Str::getNextWordIndex(const UInt32 index) {
	/////////////////
	UInt32 x = index;
	// check nullptr and index bound
	if (_str && index < _len) {
		// skip symbol
		while (Str::isSymb(_str[x]))
			x++;
		// skip white-space
		while (Str::isSpace(_str[x]))
			x++;
		// check null character
		if (_str[x]) return (x);
	} // else return start index
	return (index);
}

bool Str::isSpace(const char character) {
	return ((character > 0x08
			&& character < 0x0e)
			|| character == 0x20);
}

bool Str::isUpper(const Char character) {
	return (character > 0x40
		&& character < 0x5b);
}

bool Str::isLower(const Char character) {
	return (character > 0x60
		&& character < 0x7b);
}

bool Str::isNumber(const Char character) {
	return (character > 0x2f
		&& character < 0x3a);
}

bool Str::isAlpha(const Char character) {
	return (isUpper(character)
		|| isLower(character));
}

bool Str::isSymb(const Char character) {
	return (character > 0x20
		&& character < 0x7f);
}

bool Str::isPrint(const Char character) {
	return (character > 0x1f
		&& character < 0x7f);
}

bool Str::isOnlyPrint(void) const {
	if (_str) {
		for (UInt32 x = 0; x < _len; x++) {
			if (!Str::isPrint(_str[x]))
				return (false);
		} return (true);
	} return (false);
}

bool Str::isSet(const Char character, const char* sep) {
	if (sep) {
		while (*sep) {
			if (character == *(sep)++)
				return (true);
		} } return (false);
}
