#include "unit_tests.hpp"
#include "is_constructible.hpp"

struct A {
	A(int) { std::cout << "A constructor" << std::endl; }
	~A() { std::cout << "A destructor" << std::endl; }
	auto operator=(const A&) -> A&
	//= delete;
	{ std::cout << "A copy assignment" << std::endl; return *this; }
};

struct B {
	B(float) { std::cout << "B constructor" << std::endl; }
	~B() { std::cout << "B destructor" << std::endl; }
};


/* unit test */
template <>
bool UT::unit_tests<"is_constructible">(void) {


	A a1{ 1 };
	A a2{ 2 };
	B b1{ 1.0f };
	B b2{ 2.0f };


	static_assert(
	xns::is_assignable<A, A>,
	"NOPE");

	//a1 = a2;



	bool c1 = xns::is_constructible  <A, int>; // true
	bool c2 = std::is_constructible_v<A, int>; // true
	bool c3 = xns::is_constructible  <B, int>; // false
	bool c4 = std::is_constructible_v<B, int>; // true
	bool c5 = xns::is_constructible  <A, float>; // false
	bool c6 = std::is_constructible_v<A, float>; // false
	bool c7 = xns::is_constructible  <B, float>; // true
	bool c8 = std::is_constructible_v<B, float>; // true


	std::cout << "xns is_constructible <A, int  > = " << c1 << "\n";
	std::cout << "std is_constructible <A, int  > = " << c2 << "\n\n";

	std::cout << "xns is_constructible <B, int  > = " << c3 << "\n";
	std::cout << "std is_constructible <B, int  > = " << c4 << "\n\n";

	std::cout << "xns is_constructible <A, float> = " << c5 << "\n";
	std::cout << "std is_constructible <A, float> = " << c6 << "\n\n";

	std::cout << "xns is_constructible <B, float> = " << c7 << "\n";
	std::cout << "std is_constructible <B, float> = " << c8 << "\n\n";
	return true;
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"is_constructible">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

