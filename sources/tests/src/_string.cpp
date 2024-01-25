#include "unit_tests.hpp"

#include "string.hpp"
#include "string_literal.hpp"
#include "output.hpp"

#include "bit_view.hpp"
#include "terminal.hpp"

#include <string>


#define SUCCESS(msg) std::cout << "\x1b[32m" << "success" << "\x1b[0m" << ": " << msg << " > "
#define ERROR(msg)   std::cout << "\x1b[31m" << "error"   << "\x1b[0m" << ": " << msg << " > "
#define DIFF(a, b)   std::cout << "[ " << a << " ][ " << b << " ]" << std::endl

#define POINTER      "pointer   "
#define SIZE         "size      "
#define CAPACITY     "capacity  "
#define TERMINATOR   "terminator"

#define NULLPTR       false
#define ALLOCATED     true

template <typename T>
static void EXPECTED(	const xns::basic_string<T>& str,
						const bool ptr,
						const typename xns::basic_string<T>::size_type len,
						const typename xns::basic_string<T>::size_type cap) {
	using xns::string;

	// check pointer diff
	if ((!str.data()) != (!ptr)) ERROR(POINTER);
	else SUCCESS(POINTER);
	const char* null = ptr ? "address" : "null";
	// cast to pointer to print address
	if (str.data() != nullptr)
		DIFF((void*)str.data(), null);
	else DIFF("null", null);
	// check size
	if (str.size() != len) ERROR(SIZE);
	else SUCCESS(SIZE);
	DIFF(str.size(), len);
	// check capacity
	if (str.capacity() != cap) ERROR(CAPACITY);
	else SUCCESS(CAPACITY);
	DIFF(str.capacity(), cap);
	// check if str is null terminated
	if (str.data() != nullptr) {
		T terminator = str.data()[str.size()];
		if (terminator != 0) { ERROR(TERMINATOR); DIFF(terminator, "'\\0'"); }
		else { SUCCESS(TERMINATOR); DIFF("'\\0'", "'\\0'"); }
	}
	std::cout << std::endl;
}



// reserve test
template <typename T>
static void reserve_test(void) {

	using Str = xns::basic_string<T>;

	{
		Str s;

		s.reserve(42);
		EXPECTED(s, ALLOCATED, 0, 42);
	}
	{
		Str s;

		s.reserve(0);
		EXPECTED(s, NULLPTR, 0, 0);
	}
	{
		Str s;

		s.reserve(100);
		EXPECTED(s, ALLOCATED, 0, 100);

		s.reserve(50);
		EXPECTED(s, ALLOCATED, 0, 100);

		s.reserve(101);
		EXPECTED(s, ALLOCATED, 0, 101);

		s.reserve(100);
		EXPECTED(s, ALLOCATED, 0, 101);

	}
	{
		Str s;
		try {
			s.reserve(std::numeric_limits<typename Str::size_type>::max() - 1);
		}
		catch (const xns::exception& e) {
			write(1, "\x1b[31mexcept has been thrown\x1b[0m\n", 34);
		}
		EXPECTED(s, NULLPTR, 0, 0);
	}
}

// append string test
template <typename T>
static void append_string_test(void) {

	using Str = xns::basic_string<T>;

	{
		Str s1{"hello"};
		Str s2{" world!"};

		EXPECTED(s1, ALLOCATED, 5, 5);
		EXPECTED(s2, ALLOCATED, 7, 7);

		s1.append(s2);
		EXPECTED(s1, ALLOCATED, 12, 12);
		EXPECTED(s2, ALLOCATED, 7, 7);
	}

}

// append fill test
static void append_fill_test(void) {

	{
		xns::string s;
		EXPECTED(s, false, 0, 0);
		s.reserve(2);

		s.append('a', 3);
		EXPECTED(s, true, 3, 3);
		return;
	}

	{
		xns::string s{'x', 2};
		EXPECTED(s, true, 2, 3);

		s.append('a', 10);
		EXPECTED(s, true, 12, 13);
	}


}


static void subview(void) {
	xns::string s{"hello world!"};
	auto v = s.subview(6, 5);

	xns::print(v, " ", v.size(), '\n');
	xns::out::render();
}





auto unit_tests_string(void) -> int {


	{
		xns::string s{};
		xns::string a{"hello"};
		xns::string b{" world!"};
		xns::string c{"it's me"};
		xns::string_view d{"hello world!"};

		std::cout << "start test\n" << std::endl;
		s.multi_length(a, b, c, "fie", d, 'c');
	}


	return 0;

	xns::to_upper('a');
	//xns::to_basic_string<char>(42);

	/*{
		xns::fmt_string s{"hello!\x1b[3;31mworld!\x1b[0m."};

		std::cout << s.string() << std::endl;
		std::cout << s.vsize() << std::endl;
		std::cout << s.string().size() << std::endl;
	}*/
	{

		xns::string cs{"\x1b[32mhello!\x1b[3;31mworld!\x1b[0m."};
		std::cout << cs << std::endl;

		auto s3 = xns::sub_fmt_string(cs, 8);

		std::cout << s3 << std::endl;


	}

	{
		xns::string s{"\x1b[31mhello world!\x1b[32m I'm a string\x1b[34m with colors\x1b[0m"};
		xns::print(s, '\n');
		xns::out::render();

		xns::formated_string_iterator it{s, 3};

		xns::size_t i = 1;
		while (it) {

			auto view = *it;

			xns::print(view.size(), " `", view, "`\n");
			xns::out::render();

			it += 6;
		}

	}




	//append_string_test<char>();
	reserve_test<char>();
	//append_fill_test();
	return true;

	xns::basic_string<char16_t> sss;
   // sss.forward_remove_duplicates();
	xns::basic_string<char> s;
	const unsigned char c = 'a';
	//
	// s.to_string(c);
	// for(char x = -11; x < +5'0; ++x) {
	// 	s.to_string(x);
	// 	//write(1, "final: ", 7);
	// 	write(1, s.data(), s.size());
	// 	write(1, "\n", 1);
	// }

	return 0;

}


#include <cstring>

void compare(void) {

	xns::array arr = {
		xns::string_view{"arthur"},
		xns::string_view{"loas"},
		xns::string_view{"robert"},
		xns::string_view{"noemie"}
	};

	long c1 = 0;
	long c2 = 0;

	for (xns::size_t i = 0; i < arr.size()-1; ++i) {

		c1 = std::strcmp(arr[i].data(), arr[i+1].data());
		c2 = arr[i].compare(arr[i+1]);

		if ((c1 < 0 && c2 < 0) || c1 == c2 || (c1 > 0 && c2 > 0)) {
			std::cout << "\x1b[32m";
		}
		else {
			std::cout << "\x1b[31m";
		}
		std::cout << arr[i] << " " << arr[i+1] << std::endl;
		std::cout << "strcmp: " << c1 << " compare: " << c2 << std::endl;
		std::cout << "\x1b[0m";


	}






}



/*
void test(const char* ptr) {
	std::cout << "from const char*\n";
}

template <xns::size_t N>
void test(const char(&ptr)[N]) {
	std::cout << "from const char(&)[N]\n";
}*/



struct from_pointer {};
struct from_array {};

//template <std::size_t N>
//void test(from_array, const char(&ptr)[N]) {
//    std::cout << "from const char(&)[" << N << "]\n";
//}
//
//void test(from_pointer, const char* ptr) {
//    std::cout << "from const char*\n";
//}
//
//template <std::size_t N>
//void test2(const xns::basic_string_literal<N>& str) {
//	std::cout << "from string_literal\n";
//}

/*void test2(const char* ptr) {
	std::cout << "from const char*\n";
}*/

/*
template <std::size_t N>
void test2(const char(&ptr)[N]) {
	std::cout << "from const char(&)[" << N << "]\n";
}*/


static auto insert_test(void) -> void {

	xns::string s{"hello world!"};
	std::cout << s << std::endl;
	std::cout << "size: " << s.size() << " | capacity: " << s.capacity() << std::endl;
	std::cout << "inserting 'my ' at index 6" << std::endl;
	s.insert(6, "my ");
	std::cout << s << std::endl;
	std::cout << "size: " << s.size() << " | capacity: " << s.capacity() << std::endl;



}

namespace xns {
template <typename T>
consteval auto bits(void) noexcept -> xns::size_t {
	return sizeof(T) * xns::bits_per_byte;
}
}


template <typename T>
class sso {

	public:

	using char_t = T;
	using mut_ptr = char_t*;
	using size_type = xns::size_t;

	private:

	enum : size_type {
		CAPACITY_BITS = xns::bits<size_type>() - 1
	};

	struct big {
		mut_ptr   data;
		size_type size;
		size_type capacity : CAPACITY_BITS;
		size_type is_small : 1;
	};

	enum : size_type {
		SSO_CAPACITY  = (sizeof(big) / sizeof(char_t)) - 1
	};


	struct small {
		char_t data[SSO_CAPACITY];
		size_type available : xns::bits<char_t>() - 1;
		size_type is_small : 1;
	};

	union sso_u {
		big   _big;
		small _small;
	};

	sso_u impl;

	public:

	void debug(void) const {

		std::cout << "SSO_CAPACITY: " << SSO_CAPACITY << std::endl;
		std::cout << "sizeof(small::data): " << sizeof(small::data) << std::endl;
	}

	static_assert(sizeof(big) == sizeof(small));

	using bview = xns::bit_view<typename sso<T>::sso_u>;


	sso(void)
	: impl{._small{{0}, SSO_CAPACITY, 1}} {
	}

	~sso(void) {

		if (is_small()) {
		}
		else {
			delete[] impl._big.data;
		}
	}





	auto is_small(void) const -> bool {
		// extract least significant byte
		return impl._small.is_small;
	}

	xns::size_t available(void) const {
		return is_small() ? impl._small.available : impl._big.capacity - impl._big.size;
	}

	xns::size_t capacity(void) const {
		return is_small() ? SSO_CAPACITY : impl._big.capacity;
	}

	xns::size_t size(void) const {
		return is_small() ? SSO_CAPACITY - impl._small.available : impl._big.size;
	}

	void push_back(T c) {
		if (is_small()) {
			std::cout << "\x1b[32msmall pushing: " << (char)c << "\x1b[0m\n";

				impl._small.data[size()] = c;
				--impl._small.available;
				impl._small.data[size()] = 0;

			if (impl._small.available == 0) {
				std::cout << "DYNAMIC ALLOCATION\n";
				char_t* data = new char_t[SSO_CAPACITY * 2];
				xns::memcpy(data, impl._small.data, SSO_CAPACITY);
				impl._big.data = data;
				impl._big.size = SSO_CAPACITY;
				impl._big.capacity = SSO_CAPACITY * 2;
			}
		}
		else {
			std::cout << "\x1b[31mbig pushing: " << (char)c << "\x1b[0m\n";
			if (impl._big.size == impl._big.capacity) {
				std::cout << "REALLOCATION\n";
				char_t* data = new char_t[impl._big.capacity * 2];
				xns::memcpy(data, impl._big.data, impl._big.size);
				data[impl._big.size] = c;
				delete[] impl._big.data;
				impl._big.data = data;
				++impl._big.size;
				impl._big.capacity *= 2;
			}
			else {
				impl._big.data[impl._big.size] = c;
				++impl._big.size;
			}
		}
	}

	void print(void) {
		std::cout << "\nsize: "      << size()
				  << "\ncapacity: "  << capacity()
				  << "\navailable: " << available()
				  << "\nin small: "  << is_small() << std::endl;

		bview view{impl};
		view.print();
		::write(1, "string: ", 8);

		char_t* data = impl._small.data;

		if (is_small())
		  	::write(1, impl._small.data, size());
		else
		 	::write(1, impl._big.data, size());
		::write(1, "\n\n\n", 3);

		// for (xns::size_t i = 0; i < size(); ++i) {
		// 	std::cout << "c: " << impl.big.data[i];
		// }
		// std::cout << std::endl;
	}


};

#include "input.hpp"

template <typename T>
void sso_test(const T* msg) {

	if (msg == nullptr) { return; }

	sso<T> s;

	xns::terminal::raw();

	xns::string input;

	s.print();
	//while (input != "q") {
	//
	//	input = xns::in::read();
	//	s.push_back(input.front());
	//	s.print();
	//}





	xns::terminal::restore();

	return;


	while (*msg) {
		s.print();
		s.push_back(*msg);
		++msg;
	}
	s.print();



}



#include "benchmark.hpp"
#include "random.hpp"


static auto benchmark(void) {

	xns::size_t check_sum = 0;
	xns::size_t N = 2000;;
	xns::benchmark<5> bench;


	//bench.run("sso::string", [&] {
	//	xns::sso_string<char> s;
	//	for (xns::size_t i = 0; i < N; ++i) {
	//		s.push_back(xns::random::integral<char>());
	//	}
	//	check_sum += s.size();
	//});

	bench.run("xns::string", [&] {
		xns::string s;
		for (xns::size_t i = 0; i < N; ++i) {
			s.append(xns::random::integral<char>());
		}
		check_sum += s.size();
	});


	bench.result("push_back");
	std::cout << "check_sum: " << check_sum << std::endl;
}

#include <string.h>
#include "strcmp.hpp"
#include "strncmp.hpp"





static int func(void) {


	xns::u8string_view sv{u8"hello world!"};
	xns::string_view sv2{"hello world!"};

	std::cout << xns::strcmp(sv.data(), sv2.data()) << std::endl;

	//std::cout << sv.data() << std::endl;
	return 0;




	xns::string s0{"My|name|is|tutur|to"};
	auto v = s0.split<true>(xns::string{"|"});
	for (auto& s : v) {
		std::cout << s << std::endl;
	}


	return 0;


	std::cout << xns::strncmp("hello", "world", 0) << std::endl;
	std::cout << xns::strncmp("hello", "hellz", 4) << std::endl;
	std::cout << xns::strcmp("hello", "aorld") << std::endl;
	std::cout << xns::strcmp("hello", "hello") << std::endl;
	return 0;




	return 0;

	benchmark();
	return 0;

	sso_test<char8_t>(u8"");
	return 0;

	unsigned char arr[4] {0,0,0,0xff};
	int i = 1;

	xns::bit_view<unsigned char[4]> v1{arr};
	xns::bit_view<int> v2{i};

	v1.print();
	v2.print();

	return 0;


	std::string s;

	for (char c = 'a'; c < 'z'; ++c) {
		std::cout << "size: " << s.size() << " | capacity: " << s.capacity() << std::endl;
		s.push_back(c);
	}







	auto str = xns::to_string(-42);

	for (auto& c : str) {
		std::cout << '>' << c << std::endl;
	}


	// for (auto& c : str) {
		// std::cout << c << std::endl;
	// }

	std::cout << "size: " << str.size() << std::endl;
	std::cout << "capacity: " << str.capacity() << std::endl;
	write(1, str.data(), str.size());


	//insert_test();
	return 0;

	reserve_test<char>();
	append_string_test<char>();
	append_fill_test();

}


#if defined(XNS_TEST_STRING)
int main(int ac, char** av) {

	const char* str = av[1];


	xns::string s0{str};

	//xns::string s{"hello world!"};

	//std::cout << s << std::endl;
	return 0;


	return unit_tests_string();
}
#endif






//    struct __long
//    {
//        pointer   __data_;
//        size_type __size_;
//        size_type __cap_ : sizeof(size_type) * CHAR_BIT - 1;
//        size_type __is_long_ : 1;
//    };
//
//    enum {__min_cap = (sizeof(__long) - 1)/sizeof(value_type) > 2 ?
//                      (sizeof(__long) - 1)/sizeof(value_type) : 2};
//
//    struct __short
//    {
//        value_type __data_[__min_cap];
//        unsigned char __padding_[sizeof(value_type) - 1];
//        unsigned char __size_ : 7;
//        unsigned char __is_long_ : 1;
//    };

// The __endian_factor is required because the field we use to store the size
// has one fewer bit than it would if it were not a bitfield.
//
// If the LSB is used to store the short-flag in the short string representation,
// we have to multiply the size by two when it is stored and divide it by two when
// it is loaded to make sure that we always store an even number. In the long string
// representation, we can ignore this because we can assume that we always allocate
// an even amount of value_types.
//
// If the MSB is used for the short-flag, the max_size() is numeric_limits<size_type>::max() / 2.
// This does not impact the short string representation, since we never need the MSB
// for representing the size of a short string anyway.










