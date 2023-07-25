#include "unit_tests.hpp"
#include "string.hpp"




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
	if ((!str.pointer()) != (!ptr)) ERROR(POINTER);
	else SUCCESS(POINTER);
	const char* null = ptr ? "address" : "null";
	// cast to pointer to print address
	if (str.pointer() != nullptr)
		DIFF((void*)str.pointer(), null);
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
	if (str.pointer() != nullptr) {
		T terminator = str.pointer()[str.size()];
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

//// append string test
//template <typename T>
//static void append_string_test(void) {
//
//	using Str = Xf::String<T>;
//
//	{
//		Str s1{"hello"};
//		Str s2{" world!"};
//
//		EXPECTED(s1, ALLOCATED, 5, 5);
//		EXPECTED(s2, ALLOCATED, 7, 7);
//
//		s1.append(s2);
//		EXPECTED(s1, ALLOCATED, 12, 12);
//		EXPECTED(s2, ALLOCATED, 7, 7);
//	}
//
//}
//
//// append fill test
//static void append_fill_test(void) {
//
//	{
//		String s;
//		EXPECTED(s, false, 0, 0);
//		s.reserve(2);
//
//		s.append('a', 3);
//		EXPECTED(s, true, 3, 3);
//		return;
//	}
//
//	{
//		String s{'x', 2};
//		EXPECTED(s, true, 2, 3);
//
//		s.append('a', 10);
//		EXPECTED(s, true, 12, 13);
//	}
//
//
//}
//	//Xf::String str{"He3ll8o W2or1ld"};
//
//	//str._debug_();
//	//str.filter(Xf::String<>::is_digit);
//	//str._debug_();
//	//str.reserve(20);
//	//str._debug_();
//
//
//
//	////str.append(str2, str2, str2);
//

template <>
bool UT::unit_tests<"string">(void) {

	//append_string_test<char>();
	reserve_test<char>();
	//append_fill_test();
	return true;

	xns::basic_string<char16_t> sss;
   // sss.forward_remove_duplicates();
	xns::basic_string<char> s;
	const unsigned char c = 'a';

	s.to_string(c);
	for(char x = -11; x < +5'0; ++x) {
		s.to_string(x);
		//write(1, "final: ", 7);
		write(1, s.pointer(), s.size());
		write(1, "\n", 1);
	}

	return true;

}
