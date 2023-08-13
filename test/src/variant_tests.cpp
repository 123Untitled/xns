#include "unit_tests.hpp"
#include "variant.hpp"
#include "string.hpp"



struct A {
	A(int) { std::cout << "A int constructor" << std::endl; }
	A(A&&) { std::cout << "A move constructor" << std::endl; }
	A(const A&) { std::cout << "A copy constructor" << std::endl; }
	A& operator=(A&&) { std::cout << "A move assignment" << std::endl; return *this; }
	A& operator=(const A&) { std::cout << "A copy assignment" << std::endl; return *this; }
	~A() { std::cout << "A destructor" << std::endl; }
};

// operator<<
std::ostream& operator<<(std::ostream& os, const A& a) {
	return os << "A";
}

struct B {
	B(float) { std::cout << "B float constructor" << std::endl; }
	B(B&&) { std::cout << "B move constructor" << std::endl; }
	B(const B&) { std::cout << "B copy constructor" << std::endl; }
	B& operator=(B&&) { std::cout << "B move assignment" << std::endl; return *this; }
	B& operator=(const B&) { std::cout << "B copy assignment" << std::endl; return *this; }
	~B() { std::cout << "B destructor" << std::endl; }
};

// operator<<
std::ostream& operator<<(std::ostream& os, const B& b) {
	return os << "B";
}

struct C {
	C(char) { std::cout << "C char constructor" << std::endl; }
	C(C&&) { std::cout << "C move constructor" << std::endl; }
	C(const C&) { std::cout << "C copy constructor" << std::endl; }
	C& operator=(C&&) { std::cout << "C move assignment" << std::endl; return *this; }
	C& operator=(const C&) { std::cout << "C copy assignment" << std::endl; return *this; }
	~C() { std::cout << "C destructor" << std::endl; }
};

// operator<<
std::ostream& operator<<(std::ostream& os, const C& c) {
	return os << "C";
}




#include <string>
#include <vector>
#include <chrono>


template <typename T>
void benchmark(void) {

	using variant = T;

	// get time in nanoseconds
	auto get_time = []() -> auto {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	};

	// get time in nanoseconds
	auto start = get_time();

	std::vector<variant> vec;

	for (std::size_t i = 0; i < 10000000; ++i) {
		vec.push_back(variant{});
	}

	for (std::size_t i = 0; i < 10000000; ++i) {
		variant& var = vec[i];
		var.template emplace<std::size_t>(i);
	}

	for (std::size_t i = 0; i < 10000000; ++i) {
		variant& var = vec[i];
		var.template emplace<float>(123.456f);
	}

	for (std::size_t i = 0; i < 10000000; ++i) {
		variant& var = vec[i];
		var.template emplace<std::string>("hello world");
	}


	std::vector<variant> vec2;

	for (std::size_t i = 0; i < 10000000; ++i) {
		vec2.push_back(vec[i]);
	}

	std::vector<variant> vec3;

	for (std::size_t i = 0; i < 10000000; ++i) {
		vec3.push_back(std::move(vec[i]));
	}

	// get time in nanoseconds
	auto end = get_time();

	long long ms = (end - start);
	// / 1000000.0);

	// print time in milliseconds
	std::cout << "time: " << ms << " ns" << std::endl;

}


/* unit test */
template <>
bool UT::unit_tests<"variant">(void) {




	xns::variant<A, B, C> v00{};


	v00.emplace<A>(0);

	if (v00.has<A>())
		std::cout << "v00 has A" << std::endl;
	else
		std::cout << "v00 does not have A" << std::endl;

	v00.emplace<B>(0.0f);

	if (v00.has<B>())
		std::cout << "v00 has B" << std::endl;
	else
		std::cout << "v00 does not have B" << std::endl;

	xns::variant<A, B, C> v01{xns::in_place_index<1>(), 0.0f};

	std::cout << "-----" << std::endl;

	v01 = xns::move(v00);

	//xns::variant<A, B, C> v02{v00};


	return true;


	/*
	xns::variant<A, B, C> v0{
		xns::in_place_index<1>(),
		0.0f }; // does not compile
	*/
	xns::variant<A, B, C> v0{};

	xns::variant<A, B, C> v1{};


	xns::variant<A, B, C> v2{xns::move(v1)};

	return true;



	if (v0) {
	}



	std::cout << "has B: " << v0.has<A>() << std::endl;

	auto& val = v0.get<B>();

	std::cout << "val: " << val << std::endl;

	v0.reset();

	std::cout << "has B: " << v0.has<B>() << std::endl;

	//start<double>();

	return true;





	// code here...
	return false;
}





int main(void) {


	benchmark<xns::variant<std::string, std::size_t, float>>();
	benchmark<std::variant<std::string, std::size_t, float>>();


	return EXIT_SUCCESS;

	return UT::unit_tests<"variant">()
		? EXIT_SUCCESS : EXIT_FAILURE;
};
