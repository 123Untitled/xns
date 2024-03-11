#include "unit_tests.hpp"
#include "tuple.hpp"
#include <tuple>

const int&& foo(void) {

	static int i = 0;

	return xns::move(i);
}

class a {
	public:
		a(void) {
			std::cout << "a ctor" << std::endl;
		}
		a(const a&) {
			std::cout << "a copy ctor" << std::endl;
		}
		a(a&&) {
			std::cout << "a move ctor" << std::endl;
		}
		~a(void) {
			std::cout << "a dtor" << std::endl;
		}

		a& operator=(const a&) {
			std::cout << "a copy assign" << std::endl;
			return *this;
		}
		a& operator=(a&&) {
			std::cout << "a move assign" << std::endl;
			return *this;
		}

		bool operator==(const a&) {
			return true;
		}

};

class b {
	public:
		b(void) {
			std::cout << "b ctor" << std::endl;
		}
		b(const b&) {
			std::cout << "b copy ctor" << std::endl;
		}
		b(b&&) {
			std::cout << "b move ctor" << std::endl;
		}
		~b(void) {
			std::cout << "b dtor" << std::endl;
		}

		b& operator=(const b&) {
			std::cout << "b copy assign" << std::endl;
			return *this;
		}
		b& operator=(b&&) {
			std::cout << "b move assign" << std::endl;
			return *this;
		}

		bool operator==(const b&) const noexcept {
			return true;
		}
};


auto unit_tests_tuple(void) -> int {

	xns::tuple<int, a> tt1{};
	std::tuple<int, a> tt2{};

	std::cout << "sizeof: " << sizeof(tt1) << std::endl;
	std::cout << "sizeof: " << sizeof(tt2) << std::endl;

	return 0;


	//xns::tuple<int, b, b> tt2{1, b{}, b{}};
	//
	//if (tt1 == tt2)
	//	std::cout << "equal" << std::endl;
	//else
	//	std::cout << "not equal" << std::endl;

	return 0;
		

	//a a0;

	//xns::tuple<a, float, b> td{};
	xns::tuple<float, int> td{};
	//std::tuple<a, float, b> t0{};
	std::tuple<float, int> t0{};
	//std::get<float>(t0);

	xns::get<1>(td);
	auto aa0 = xns::get<0>(xns::move(td));

	std::cout << "sizeof xns: " << sizeof(td) << std::endl;
	std::cout << "sizeof std: " << sizeof(t0) << std::endl;

	std::cout << "xns is_trivially default constructible: " << std::is_trivially_default_constructible<decltype(td)>::value << std::endl;
	std::cout << "xns is_trivially copy constructible: " << std::is_trivially_copy_constructible<decltype(td)>::value << std::endl;
	std::cout << "xns is_trivially move constructible: " << std::is_trivially_move_constructible<decltype(td)>::value << std::endl;
	std::cout << "xns is_trivially copy assignable: " << std::is_trivially_copy_assignable<decltype(td)>::value << std::endl;
	std::cout << "xns is_trivially move assignable: " << std::is_trivially_move_assignable<decltype(td)>::value << std::endl;
	std::cout << "xns is_trivially destructible: " << std::is_trivially_destructible<decltype(td)>::value << std::endl;
	std::cout << "std is_trivially default constructible: " << std::is_trivially_default_constructible<decltype(t0)>::value << std::endl;
	std::cout << "std is_trivially copy constructible: " << std::is_trivially_copy_constructible<decltype(t0)>::value << std::endl;
	std::cout << "std is_trivially move constructible: " << std::is_trivially_move_constructible<decltype(t0)>::value << std::endl;
	std::cout << "std is_trivially copy assignable: " << std::is_trivially_copy_assignable<decltype(t0)>::value << std::endl;
	std::cout << "std is_trivially move assignable: " << std::is_trivially_move_assignable<decltype(t0)>::value << std::endl;
	std::cout << "std is_trivially destructible: " << std::is_trivially_destructible<decltype(t0)>::value << std::endl;

	return 0;

	//xns::tuple<a, b> tt{};
	//
	//td = tt;

	return 0;
	//
	//int i = 0;
	//float f = 0.0f;
	//
	//xns::tuple t0{i, f};
	//xns::tuple t1{0, 0.0f};
	//
	//t0 = t1; // here error
	//
	//std::tuple t3{i, f};
	//std::tuple t2{0, 0.0f};
	//
	//t3 = t2; // here error
	//


	//
	//xns::get<0>(t0) = 1;
	//std::get<0>(t1) = 1;
	//
	//std::cout << "sizeof: " << sizeof(t0) << std::endl;
	//std::cout << "sizeof: " << sizeof(t1) << std::endl;
	return 0;



	//xns::tuple<int> t4{1};
	//
	//const auto& v = xns::get<int>(xns::move(t4));
	//
	//
	//xns::tuple<int, float, const char(&)[6]> _tuple = xns::make_tuple(1, 2.0f, "hello");
	//
	//int refff = xns::get<int>(xns::move(_tuple));
	//
	//static_assert(xns::is_unique<char, int, float, const char*>);
	//
	//
	//int& reff = xns::get<0>(_tuple);


	//_tuple.set<0>(2);


	//auto ret = xns::get<float>(_tuple);

	//std::cout << ret << std::endl;

	return 0;




	//std::cout << refff << std::endl;



	//Type type{1, 2.0, 'c'};

	//xns::tuple<Type, int, float> t3{xns::move(type), 2, 3.0f};

	//Tuple<float, char> t02 = t3;

	//t3.iterate();

	//Tuple<Type, int, float> t4 = {2, 3.0f, 'c'};

	//Tuple<Type, int> t3{};


	//Tuple<Type, int> t4 = t3;

	//auto t4 = t3;

   // Tuple<Type> t4 = t3;

	//Tuple t5{123, 99.9, 'c'};

	//t3 = t4;

	//t3.iterate();
	//t4.iterate();
	//t5.iterate();

	return 0;

}


#if defined(XNS_TEST_TUPLE)
int main(void) {
	return unit_tests_tuple();
}
#endif

