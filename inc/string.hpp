#ifndef STRING_HEADER
#define STRING_HEADER

// global includes
#include <iostream>
#include <iomanip>
#include <unistd.h>

// local includes
#include "Types.hpp"
#include "move.hpp"
#include "type_traits.hpp"
#include "allocator.hpp"


// forward declarations
class LString;


// -- S T R I N G  C L A S S --------------------------------------------------

class String {

	public:

		// -- A L I A S E S ---------------------------------------------------

		/* character type */
		using Char = char;

		/* size type */
		using Size = UInt64;

		/* pointer type */
		using Pointer = Char*;

		/* const pointer type */
		using ConstPointer = const Char*;

		/* reference type */
		using Reference = Char&;

		/* const reference type */
		using ConstRef = const Char&;

		/* allocator type */
		using Allocator = Xf::Allocator<Char>;


		// -- C O N S T R U C T O R S -----------------------------------------

		/* default constructor */
		String(void);

		/* capacity constructor */
		String(const Size capacity);

		/* null-terminated string constructor */
		String(const Char* str);

		/* buffer constructor */
		String(const Char *string, const Size size);

		/* fill constructor */
		String(const Char character, const Size size);

		/* copy constructor */
		String(const String& copy);

		/* move constructor */
		String(String&& move) noexcept;

		/* destructor */
		~String(void);


		// -- F R I E N D S ---------------------------------------------------

		/* LString class */
		friend class LString;



		// -- A S S I G N -----------------------------------------------------

		/* null-terminated string assignment */
		String& assign(const Char* str);

		/* buffer assignment */
		String& assign(const Char* str, const Size size);

		/* fill assignment */
		String& assign(const Char character, const Size size);

		/* copy assignment */
		String& assign(const String& str);

		/* move assignment */
		String& assign(String&& str) noexcept;




		// -- O P E R A T O R S -----------------------------------------------


		/* assignment operator */
		String& operator=(const String& copy);

		/* move assignment operator */
		String& operator=(String&& str) noexcept;

		/* null-terminated string assignment operator */
		String& operator=(const Char* str);

		/* character assignment operator */
		String& operator=(const Char character);

		/* concatenation assignment operator */
		String& operator+=(const String& str);

		/* null-terminated string concatenation assignment operator */
		String& operator+=(const Char* str);

		/* character concatenation assignment operator */
		String& operator+=(const Char character);

		/* subscript operator */
		Reference operator[](const Size index);

		/* const subscript operator */
		ConstRef operator[](const Size index) const;

		/* bool operator */
		operator bool(void) const;




		/* concatenation operator */
		//String operator+(const String& str) const;
		//String operator+(const String &add);

		/* equality operator */
		//bool operator==(const String& str) const;

		/* null-terminated string equality operator */
		//bool operator==(const Char* str) const;




		// -- A C C E S S O R S -----------------------------------------------

		/* length */
		Size length(void) const;

		/* capacity */
		Size capacity(void) const;

		/* available */
		Size available(void) const;

		/* const pointer */
		ConstPointer pointer(void) const;


		// -- P U B L I C  M E T H O D S --------------------------------------

		/* move */
		void move(String& owner);



		// -- S E A R C H I N G -----------------------------------------------

		/* next word */
		Size next_word(const Size index) const;

		/* previous word */
		Size previous_word(const Size index) const;

		/* next character */
		Size next_character(const Size index, const Char character) const;

		/* previous character */
		Size previous_character(const Size index, const Char character) const;

		/* is only */
		bool is_only(bool (*is_type)(const Char)) const;

		// -- M O D I F I E R S -----------------------------------------------

		/* clear */
		void clear(void);

		String& append(const Char character, Size size);

		String& append(const String& str);

		String& append(const Char* str, Size size);

		String& append(const Char* str);




		String& insert(const Char character, const Size count, const Size index);

		String& insert(const Char* str, const Size index);

		String& insert(const Char* str, const Size size, const Size index);

		String& insert(const String& str, const Size index);






		void addAt(const Char c, const UInt32 index);
		void deleteAt(const UInt32 index);
		bool resize(const Size size);


		/* to uppercase */
		void to_uppercase(void);

		/* to lowercase */
		void to_lowercase(void);


		// -- E X T R A C T I O N ---------------------------------------------

		LString split(String&& sep) const;

		LString split2(String&& sep) const;


		// -- A L G O R I T H M S ---------------------------------------------


		void pull_repeat(void);

		/* forward remove duplicates */
		void forward_remove_duplicates(void);

		/* backward remove duplicates */
		void backward_remove_duplicates(void);


	private:

		// -- P R I V A T E  M E M B E R S ------------------------------------

		//mutable Size _cache;

		Char*  _str;
		Size   _size;
		Size   _capacity;


		// -- P R I V A T E  M E T H O D S ------------------------------------

		/* initialize memory */
		void initialize_memory(void);

		/* initialize members */
		void initialize_members(void);

		/* allocate */
		void allocate(const Size capacity);

		/* deallocate */
		void deallocate(void);

		/* reallocate */
		void reallocate(const Size capacity);

		// new memory allocation
		Char* allocation(const Size size) const;


		/* unsafe copy */
		static void unsafe_copy(Char* dst, const Char* src, const Size size);

		/* unsafe bzero */
		static void unsafe_bzero(Char* dst, const Size size);



	public:


		/*
		template <typename... Strings>
		void append(Strings... strings) {
			static_assert((Xf::is_same<String, Strings>::value && ...), "append() requires all arguments to be Strings");
			// get the size of the strings
			Size size = 0;
			((size += strings.length()), ...);
			// resize the string
			reallocate(_size + size);
			// append the strings
			((append(strings), ...));
		}
          */



		bool			cmpr(const String &compare) const;
		bool			ncmpr(const String& compare) const;
		bool			cmpr(const Char* compare) const;
		bool			ncmpr(const Char* compare) const;




		// -- D E B U G -------------------------------------------------------

		/* print string */
		void print_string(void) const;

		/* debug string */
		void debug_string(void) const;


	private:

		bool strcmp(const Char *first, const Char* second) const;
		bool strncmp(const Char* first, const Char* second, UInt32 len) const;


		void copy(Char *dest, const Char *src, const UInt32 start);
		void copy(const Char *str);
		void fill(const Char c);

	public:

		// -- P U B L I C  S T A T I C  M E T H O D S -------------------------

		/* get len */
		static Size get_len(const Char *str);

		/* is upper */
		static bool is_uppercase(const Char character);

		/* is lower */
		static bool is_lowercase(const Char character);

		/* is alpha */
		static bool is_alpha(const Char character);

		/* is digit */
		static bool is_digit(const Char character);

		/* is hexadecimal */
		static bool is_hexadecimal(const Char character);

		/* is print */
		static bool is_printable(const Char character);

		/* is whitespace */
		static bool is_whitespace(const Char character);

		/* is control */
		static bool is_control(const Char character);

		/* is graphical */
		static bool is_graphical(const Char character);

		/* is charset */
		static bool is_charset(const Char character, const Char* charset);

		/* is multi-byte */
		static bool is_multibyte(const Char character);

		/* to uppercase */
		static Char to_uppercase(const Char character);

		/* to lowercase */
		static Char to_lowercase(const Char character);



}; // end of class String






// -- L S T R I N G  C L A S S ------------------------------------------------

class LString final {

	public:

		// -- A L I A S E S ---------------------------------------------------

		using Size = String::Size;

		// -- C O N S T R U C T O R S -----------------------------------------

		/* default constructor */
		LString(void);

		/* copy constructor */
		LString(const LString& copy);

		/* move constructor */
		LString(LString&& move) noexcept;

		/* destructor */
		~LString(void);


		// -- O P E R A T O R S -----------------------------------------------

		/* assignment operator */
		LString& operator=(const LString& other);

		/* move operator */
		LString& operator=(LString&& other) noexcept;

		/* index operator */
		String* operator[](const UInt32 index) const;


	private:

		// -- N O D E  C L A S S ----------------------------------------------

		class Node final : public String {

			public:
				Node*	_nxt;
				Node*	_prv;

				// -- C O N S T R U C T O R S ---------------------------------

				/* deleted default constructor */
				Node(void) = delete;

				/* string copy constructor */
				Node(const String &obj);

				/* string move constructor */
				Node(String &&obj);

				/* copy constructor */
				Node(const Node& copy);

				/* move constructor */
				Node(Node&& move) noexcept;

				/* destructor */
				~Node(void);
		};


		// -- P R I V A T E  M E M B E R S ------------------------------------

		Node* _head;
		Node* _tail;

		Size _size;
		Size _node;

		static bool _debug;



		void deleteNode(Node *node);

		/* initialize members */
		void initialize_members(void);

		void front_link(Node *add);

		void back_link(Node *add);

		void freeLst();

		void debug(const char *message) const;

	public:

		static void debugOn(void);
		static void debugOff(void);

		void deleteList();
		void deleteAt(const UInt32 index);



		void print(void) const;


		/* add front move */
		void add_front(String&& str);

		/* add front copy */
		void add_front(const String& str);

		/* add back move */
		void add_back(String&& str);

		/* add back copy */
		void add_back(const String& str);



		void separator(String&& sep);

		/* merge */
		String merge(void);




		class Iterator {
			private:
				Node**	_ptr;

				Iterator(Node** node);
				//Iterator(STRNode* node);

			public:
				Iterator(LString& lst);

				void start(LString& lst);

				void end(LString& lst);


				operator bool();

				bool operator!(void);
				// Prefix increment operator.
				Iterator& operator++(void);
				// Postfix increment operator.
				Iterator operator++(int);
				// Postfix decrement operator.
				Iterator operator--(int);

				String& operator*(void);

		};

};


#endif
