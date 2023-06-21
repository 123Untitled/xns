#include "unit_tests.hpp"
#include "make_signed.hpp"

#include <unistd.h>
#include <type_traits>


/* checker */
template <xns::string_literal msg, class T>
static bool checker(void) {

	// get signed type
	using type = xns::make_signed<T>;

	// evaluate constness
	constexpr bool const_test    = std::is_const<T>::value
							     ? std::is_const<type>::value
							     : !std::is_const<type>::value;

	// evaluate volatility
	constexpr bool volatile_test = std::is_volatile<T>::value
								 ? std::is_volatile<type>::value
								 : !std::is_volatile<type>::value;

	// evaluate size
	constexpr bool size_test     = sizeof(T) == sizeof(type);

	// evaluate sign
	constexpr bool sign_test     = std::is_signed<type>::value;

	// evalute integer
	constexpr bool integer_test  = std::is_integral<type>::value;


	// print test
	write(STDOUT_FILENO, msg.data(), msg.size());

	// all tests
	constexpr bool all_tests = const_test && volatile_test && size_test && sign_test && integer_test;

	// print result
	if constexpr (all_tests == true) {
		// print and return success
		write(STDOUT_FILENO, " \x1b[32msuccess\x1b[0m\n", 18);
		return true; }

	// print failed
	write(STDOUT_FILENO, " \x1b[31mfailed\x1b[0m [ ", 19);

	// print details
	if constexpr (const_test    == false) { write(STDOUT_FILENO, "const ", 6); }

	if constexpr (volatile_test == false) { write(STDOUT_FILENO, "volatile ", 9); }

	if constexpr (size_test     == false) { write(STDOUT_FILENO, "size ", 5); }

	if constexpr (sign_test     == false) { write(STDOUT_FILENO, "sign ", 5); }

	if constexpr (integer_test  == false) { write(STDOUT_FILENO, "integer ", 8); }

	write(STDOUT_FILENO, "]\n", 2);

	// return failure
	return false;
}


/* unit test */
template <>
bool UT::unit_tests<"make_signed">(void) {

	// this test fails, because make_signed cannot detect underlying type of enum
	// normally, make_signed cannot compile if the underlying type is a bool
	enum ebool : bool { TRUE = true, FALSE = false };
	using type = xns::make_signed<ebool>;


	// enum types

	enum e00 : char               {};
	enum e01 : signed char        {};
	enum e02 : unsigned char      {};
	enum e03 : short              {};
	enum e04 : signed short       {};
	enum e05 : unsigned short     {};
	enum e06 : int                {};
	enum e07 : signed int         {};
	enum e08 : unsigned int       {};
	enum e09 : long               {};
	enum e10 : signed long        {};
	enum e11 : unsigned long      {};
	enum e12 : long long          {};
	enum e13 : signed long long   {};
	enum e14 : unsigned long long {};
	enum e15 : char8_t            {};
	enum e16 : char16_t           {};
	enum e17 : char32_t           {};
	enum e18 : wchar_t            {};


	// start tests

	return

	   checker<"char                                   ->", char>()
	&& checker<"signed char                            ->", signed char>()
	&& checker<"unsigned char                          ->", unsigned char>()

	&& checker<"short                                  ->", short>()
	&& checker<"signed short                           ->", signed short>()
	&& checker<"unsigned short                         ->", unsigned short>()

	&& checker<"int                                    ->", int>()
	&& checker<"signed int                             ->", signed int>()
	&& checker<"unsigned int                           ->", unsigned int>()

	&& checker<"long                                   ->", long>()
	&& checker<"signed long                            ->", signed long>()
	&& checker<"unsigned long                          ->", unsigned long>()

	&& checker<"long long                              ->", long long>()
	&& checker<"signed long long                       ->", signed long long>()
	&& checker<"unsigned long long                     ->", unsigned long long>()

	&& checker<"const char                             ->", const char>()
	&& checker<"volatile char                          ->", volatile char>()
	&& checker<"const volatile char                    ->", const volatile char>()

	&& checker<"const signed char                      ->", const signed char>()
	&& checker<"volatile signed char                   ->", volatile signed char>()
	&& checker<"const volatile signed char             ->", const volatile signed char>()

	&& checker<"const unsigned char                    ->", const unsigned char>()
	&& checker<"volatile unsigned char                 ->", volatile unsigned char>()
	&& checker<"const volatile unsigned char           ->", const volatile unsigned char>()

	&& checker<"const short                            ->", const short>()
	&& checker<"volatile short                         ->", volatile short>()
	&& checker<"const volatile short                   ->", const volatile short>()

	&& checker<"const signed short                     ->", const signed short>()
	&& checker<"volatile signed short                  ->", volatile signed short>()
	&& checker<"const volatile signed short            ->", const volatile signed short>()

	&& checker<"const unsigned short                   ->", const unsigned short>()
	&& checker<"volatile unsigned short                ->", volatile unsigned short>()
	&& checker<"const volatile unsigned short          ->", const volatile unsigned short>()

	&& checker<"const int                              ->", const int>()
	&& checker<"volatile int                           ->", volatile int>()
	&& checker<"const volatile int                     ->", const volatile int>()

	&& checker<"const signed int                       ->", const signed int>()
	&& checker<"volatile signed int                    ->", volatile signed int>()
	&& checker<"const volatile signed int              ->", const volatile signed int>()

	&& checker<"const unsigned int                     ->", const unsigned int>()
	&& checker<"volatile unsigned int                  ->", volatile unsigned int>()
	&& checker<"const volatile unsigned int            ->", const volatile unsigned int>()

	&& checker<"const long                             ->", const long>()
	&& checker<"volatile long                          ->", volatile long>()
	&& checker<"const volatile long                    ->", const volatile long>()

	&& checker<"const signed long                      ->", const signed long>()
	&& checker<"volatile signed long                   ->", volatile signed long>()
	&& checker<"const volatile signed long             ->", const volatile signed long>()

	&& checker<"const unsigned long                    ->", const unsigned long>()
	&& checker<"volatile unsigned long                 ->", volatile unsigned long>()
	&& checker<"const volatile unsigned long           ->", const volatile unsigned long>()

	&& checker<"const long long                        ->", const long long>()
	&& checker<"volatile long long                     ->", volatile long long>()
	&& checker<"const volatile long long               ->", const volatile long long>()

	&& checker<"const signed long long                 ->", const signed long long>()
	&& checker<"volatile signed long long              ->", volatile signed long long>()
	&& checker<"const volatile signed long long        ->", const volatile signed long long>()

	&& checker<"const unsigned long long               ->", const unsigned long long>()
	&& checker<"volatile unsigned long long            ->", volatile unsigned long long>()
	&& checker<"const volatile unsigned long long      ->", const volatile unsigned long long>()


	&& checker<"char8_t                                ->", char8_t>()
	&& checker<"const char8_t                          ->", const char8_t>()
	&& checker<"volatile char8_t                       ->", volatile char8_t>()
	&& checker<"const volatile char8_t                 ->", const volatile char8_t>()

	&& checker<"char16_t                               ->", char16_t>()
	&& checker<"const char16_t                         ->", const char16_t>()
	&& checker<"volatile char16_t                      ->", volatile char16_t>()
	&& checker<"const volatile char16_t                ->", const volatile char16_t>()

	&& checker<"char32_t                               ->", char32_t>()
	&& checker<"const char32_t                         ->", const char32_t>()
	&& checker<"volatile char32_t                      ->", volatile char32_t>()
	&& checker<"const volatile char32_t                ->", const volatile char32_t>()

	&& checker<"wchar_t                                ->", wchar_t>()
	&& checker<"const wchar_t                          ->", const wchar_t>()
	&& checker<"volatile wchar_t                       ->", volatile wchar_t>()
	&& checker<"const volatile wchar_t                 ->", const volatile wchar_t>()



	&& checker<"enum char                              ->", e00>()
	&& checker<"enum const char                        ->", const e00>()
	&& checker<"enum volatile char                     ->", volatile e00>()
	&& checker<"enum const volatile char               ->", const volatile e00>()

	&& checker<"enum signed char                       ->", e01>()
	&& checker<"enum const signed char                 ->", const e01>()
	&& checker<"enum volatile signed char              ->", volatile e01>()
	&& checker<"enum const volatile signed char        ->", const volatile e01>()

	&& checker<"enum unsigned char                     ->", e02>()
	&& checker<"enum const unsigned char               ->", const e02>()
	&& checker<"enum volatile unsigned char            ->", volatile e02>()
	&& checker<"enum const volatile unsigned char      ->", const volatile e02>()

	&& checker<"enum short                             ->", e03>()
	&& checker<"enum const short                       ->", const e03>()
	&& checker<"enum volatile short                    ->", volatile e03>()
	&& checker<"enum const volatile short              ->", const volatile e03>()

	&& checker<"enum signed short                      ->", e04>()
	&& checker<"enum const signed short                ->", const e04>()
	&& checker<"enum volatile signed short             ->", volatile e04>()
	&& checker<"enum const volatile signed short       ->", const volatile e04>()

	&& checker<"enum unsigned short                    ->", e05>()
	&& checker<"enum const unsigned short              ->", const e05>()
	&& checker<"enum volatile unsigned short           ->", volatile e05>()
	&& checker<"enum const volatile unsigned short     ->", const volatile e05>()

	&& checker<"enum int                               ->", e06>()
	&& checker<"enum const int                         ->", const e06>()
	&& checker<"enum volatile int                      ->", volatile e06>()
	&& checker<"enum const volatile int                ->", const volatile e06>()

	&& checker<"enum signed int                        ->", e07>()
	&& checker<"enum const signed int                  ->", const e07>()
	&& checker<"enum volatile signed int               ->", volatile e07>()
	&& checker<"enum const volatile signed int         ->", const volatile e07>()

	&& checker<"enum unsigned int                      ->", e08>()
	&& checker<"enum const unsigned int                ->", const e08>()
	&& checker<"enum volatile unsigned int             ->", volatile e08>()
	&& checker<"enum const volatile unsigned int       ->", const volatile e08>()

	&& checker<"enum long                              ->", e09>()
	&& checker<"enum const long                        ->", const e09>()
	&& checker<"enum volatile long                     ->", volatile e09>()
	&& checker<"enum const volatile long               ->", const volatile e09>()

	&& checker<"enum signed long                       ->", e10>()
	&& checker<"enum const signed long                 ->", const e10>()
	&& checker<"enum volatile signed long              ->", volatile e10>()
	&& checker<"enum const volatile signed long        ->", const volatile e10>()

	&& checker<"enum unsigned long                     ->", e11>()
	&& checker<"enum const unsigned long               ->", const e11>()
	&& checker<"enum volatile unsigned long            ->", volatile e11>()
	&& checker<"enum const volatile unsigned long      ->", const volatile e11>()

	&& checker<"enum long long                         ->", e12>()
	&& checker<"enum const long long                   ->", const e12>()
	&& checker<"enum volatile long long                ->", volatile e12>()
	&& checker<"enum const volatile long long          ->", const volatile e12>()

	&& checker<"enum signed long long                  ->", e13>()
	&& checker<"enum const signed long long            ->", const e13>()
	&& checker<"enum volatile signed long long         ->", volatile e13>()
	&& checker<"enum const volatile signed long long   ->", const volatile e13>()

	&& checker<"enum unsigned long long                ->", e14>()
	&& checker<"enum const unsigned long long          ->", const e14>()
	&& checker<"enum volatile unsigned long long       ->", volatile e14>()
	&& checker<"enum const volatile unsigned long long ->", const volatile e14>()

	&& checker<"enum char8_t                           ->", e15>()
	&& checker<"enum const char8_t                     ->", const e15>()
	&& checker<"enum volatile char8_t                  ->", volatile e15>()
	&& checker<"enum const volatile char8_t            ->", const volatile e15>()

	&& checker<"enum char16_t                          ->", e16>()
	&& checker<"enum const char16_t                    ->", const e16>()
	&& checker<"enum volatile char16_t                 ->", volatile e16>()
	&& checker<"enum const volatile char16_t           ->", const volatile e16>()

	&& checker<"enum char32_t                          ->", e17>()
	&& checker<"enum const char32_t                    ->", const e17>()
	&& checker<"enum volatile char32_t                 ->", volatile e17>()
	&& checker<"enum const volatile char32_t           ->", const volatile e17>()

	&& checker<"enum wchar_t                           ->", e18>()
	&& checker<"enum const wchar_t                     ->", const e18>()
	&& checker<"enum volatile wchar_t                  ->", volatile e18>()
	&& checker<"enum const volatile wchar_t            ->", const volatile e18>();

}

