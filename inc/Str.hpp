#ifndef STRING_HEADER
#define STRING_HEADER


#include "Types.hpp"

//#include <Enum.hpp>
#include <iostream>

#define DEFAULT_CONSTRUCTOR		"default-constructor"
#define COPY_CONSTRUCTOR		"copy-constructor"
#define MOVE_CONSTRUCTOR		"move-constructor"
#define STRING_CONSTRUCTOR		"string-constructor"
#define SIZE_CONSTRUCTOR		"size-constructor"
#define STRINGSIZE_CONSTRUCTOR	"string-size-constructor"
#define FILL_CONSTRUCTOR		"fill-constructor"
#define DESTRUCTOR				"destructor"
#define MOVE_OPERATOR			"move-operator"
#define COPY_OPERATOR			"copy-operator"

#define INDIRECTION_OPERATOR	"indirection-operator"

enum StrErr {
	STR_SUCCESS,
	STR_ERROR
};

class Strlst;

class Str {

friend class Strlst;

private:
	Char	*_str;
	UInt32	 _len;
	UInt32	 _capacity;
	#define nullchar '\0'
	static bool _debug;

public:
	// default constructor
	Str(void);
	// copy constructor
	Str(const Str& copy);
	// Move constructor.
	Str(Str&& move) noexcept;

	// capcity constructor
	Str(const UInt32 size);
	// buffer constructor
	Str(const Char* string);
	//explicit Str(const Char *string);
	// buffer constructor with capacity
	Str(const Char *string, const UInt32 size);
	// fill constructor
	Str(const Char character, const UInt32 size);
	// destructor
	~Str();

	void			print(void) const;
	void			print(const Char *var, const int flag) const;

	void			debug(const char *message) const;
	static void		debugOn(void);
	static void		debugOff(void);

	void			reset(void);
	void			deleteStr();

	bool			cmpr(const Str &compare) const;
	bool			ncmpr(const Str& compare) const;
	bool			cmpr(const char* compare) const;
	bool			ncmpr(const char* compare) const;

	StrErr			ownerSwap(Str &owner);
	void			extand();

	void			pullTwin(void);
	void			pullRepeat(void);
	//void			append(const Char string);
	void			append(const Str &string);
	void			addAt(const Char c, const UInt32 index);
	void			deleteAt(const UInt32 index);

	bool			setLen(const UInt32 len);
	UInt32			getLen()		const;
	UInt32			getCapacity()	const;

	// return available allocated bytes
	UInt getAvailable()	const;

	Char			*getPointer()	const;

	// Str assignment operator
	Str& operator=(const Str& other);
	// Str move operator
	Str& operator=(Str&& other);
	// litteral assignment operator
	Str& operator=(const Char* string);


	Str operator+(const Str &add);

	Char& operator[](const UInt32 index) const;
	//Char operator[](const UInt32 index) const;

	Char const* operator*(void) const;

	bool operator==(const Str& equal) const;

	bool operator==(const Char* equal) const;

	operator bool(void) const;

	Strlst split(Str&& sep) const;
	Strlst split2(Str&& sep) const;


	bool isOnlyPrint() const;

	UInt32 getNextWordIndex(const UInt index);
	UInt32 getPreviousWordIndex(UInt index);

	void copy(Char *dest, const Char *src, const UInt32 start);

	/* ------------------------------------------------ */

	// check character is uppercase
	static bool isUpper(const char character);
	// check character is lowercase
	static bool isLower(const char character);
	// check character is alphabetic
	static bool isAlpha(const char character);
	// check character is number
	static bool isNumber(const char character);
	// check character is printable
	static bool isPrint(const char character);
	// check character is whitespace
	static bool isSpace(const char character);
	// check character is symbol
	static bool isSymb(const char character);
	// check character is in character set
	static bool isSet(const char character, const char *sep);


private:

	bool strcmp(const Char *first, const Char* second) const;
	bool strncmp(const Char* first, const Char* second, UInt32 len) const;

	// new memory allocation
	char* allocation(const UInt size) const;

	void init();
	void copy(const Char *str);
	void fill(const Char c);

	UInt32 len(const Char *str);
	void createStr(const UInt32 size);


}; /////////////////////////////////////////////////



///////////////
class Strlst {

public:


private:


	class STRNode: public Str {


		//private: // public members
		public:
			STRNode*	_nxt;
			STRNode*	_prv;
			STRNode(void) = delete;
			STRNode(Str &&obj);
			STRNode(const Str &obj);
			~STRNode(void);
	};

	STRNode*	_head;
	STRNode*	_tail;
	UInt32		_size;
	UInt32		_node;

	static bool _debug;

	void deleteNode(STRNode *node);
	void init();
	void frontLink(STRNode *add);
	void backLink(STRNode *add);
	void freeLst();
	void debug(const char *message) const;

public:
	static void debugOn(void);
	static void debugOff(void);

	void deleteList();
	void deleteAt(const UInt32 index);

	Strlst(void);
	Strlst(const Strlst& copy);
	Strlst(Strlst&& move) noexcept;
	~Strlst(void);

	void operator=(Strlst&& move);
	void operator=(Strlst& copy);
	Str* operator[](const UInt32 index) const;

	//STRNode*	getHead(void);

	void print(void) const;

	void addFront(Str&& obj);
	void addFront(const Str& obj);
	void addBack(Str&& obj);
	void addBack(const Str& obj);

	void separator(Str&& sep);
	Str release(void);



	class Iterator {
	private:
		STRNode**	_ptr;

		Iterator(STRNode** node);
		//Iterator(STRNode* node);
	public:
		Iterator(Strlst& lst);

		void start(Strlst& lst);
		void end(Strlst& lst);


		operator bool();

		bool operator!(void);
		// Prefix increment operator.
		Iterator& operator++(void);
		// Postfix increment operator.
		Iterator operator++(int);
		// Postfix decrement operator.
		Iterator operator--(int);

		Str& operator*(void);

	};

};

#endif
