#include "unit_tests.hpp"

#include "xns/memory/unique_ptr.hpp"
#include "xns/containers/vector.hpp"

template <class T>
using AutoP = xns::unique_ptr<T>;

#define OWN Xf
#define own Xf


void f(...) {}


auto unit_tests_unique_ptr(void) -> int {



	using namespace xns;
	/*
	bool d = Xf::is_derived_from_v<Class<int, float, char>, Base<int>>;
	bool b = Xf::is_base_of_v<Base<int>, Class<int, float, char>>;
	*/

	//bool s1 = xns::is_base_of<Base<int>, Base<int>>;
	//bool s2 = xns::is_derived_from<int, void>;



	//using Base    = Base<int>;
	//using Derived = Class<int, float, char>;


	//p1.assign(1, 2.0f, '3');

	//AutoP<A> p2 = AutoP<B>{1, 2.0f, '3'};

	//AutoP<B> p3{Xf::move(p1)};

	//AutoP<Derived> p1 = xns::make_unique<Derived>(123, 99.9f, 'X');
	//if (!p1) {
	//	std::cout << "null" << std::endl;
	//}
	//
	//AutoP<Base> p3;
	//
	//xns::unique_ptr<Derived> p2;




	//xns::unique_ptr<int> ptr_int = xns::make_unique<int>(123);
	//
	//xns::vector<xns::unique_ptr<int>> vec;
	//
	//vec.push_back(xns::make_unique<int>(123));
	//
	////Xf::AutoPointer<void> v{};
	//
	//
	//std::cout << *p2 << std::endl;


	//AutoP<B> p4{p1};

	//p4.assign(p1);

	{
		//AutoP<A> base = Xf::make_auto_pointer<B>(1, 2.0f, '3');

	}

	return 0;

}

#if defined(XNS_TEST_UNIQUE_PTR)
int main(void) {
	return unit_tests_unique_ptr();
}
#endif


