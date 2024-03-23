#include "unit_tests.hpp"
#include "xns/type_traits/supported_operations/is_constructible.hpp"
#include "xns/type_traits/supported_operations/is_assignable.hpp"

struct AA {
	AA(int) { std::cout << "A constructor" << std::endl; }
	~AA() { std::cout << "A destructor" << std::endl; }
	auto operator=(const AA&) -> AA&
	//= delete;
	{ std::cout << "A copy assignment" << std::endl; return *this; }
};

struct BB {
	BB(float) { std::cout << "B constructor" << std::endl; }
	~BB() { std::cout << "B destructor" << std::endl; }
};


/* unit test */

auto unit_tests_is_constructible(void) -> int {


	AA a1{ 1 };
	AA a2{ 2 };
	BB b1{ 1.0f };
	BB b2{ 2.0f };


	static_assert(
	xns::is_assignable<AA, AA>,
	"NOPE");

	//a1 = a2;



	bool c1 = xns::is_constructible  <AA, int>; // true
	bool c2 = std::is_constructible_v<AA, int>; // true
	bool c3 = xns::is_constructible  <BB, int>; // false
	bool c4 = std::is_constructible_v<BB, int>; // true
	bool c5 = xns::is_constructible  <AA, float>; // false
	bool c6 = std::is_constructible_v<AA, float>; // false
	bool c7 = xns::is_constructible  <BB, float>; // true
	bool c8 = std::is_constructible_v<BB, float>; // true


	std::cout << "xns is_constructible <A, int  > = " << c1 << "\n";
	std::cout << "std is_constructible <A, int  > = " << c2 << "\n\n";

	std::cout << "xns is_constructible <B, int  > = " << c3 << "\n";
	std::cout << "std is_constructible <B, int  > = " << c4 << "\n\n";

	std::cout << "xns is_constructible <A, float> = " << c5 << "\n";
	std::cout << "std is_constructible <A, float> = " << c6 << "\n\n";

	std::cout << "xns is_constructible <B, float> = " << c7 << "\n";
	std::cout << "std is_constructible <B, float> = " << c8 << "\n\n";

	return 0;
}

#if defined(XNS_TEST_IS_CONSTRUCTIBLE)
int main(void) {
	return unit_tests_is_constructible();
}
#endif


