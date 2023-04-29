#include "auto_pointer.hpp"
#include "unit_tests.hpp"

template <class T>
using AutoP = Xf::AutoPointer<T>;

#define OWN Xf
#define own Xf


void f(...) {}

void UT::auto_pointer_ut(void) {

	using namespace Xf;
	/*
	bool d = Xf::is_derived_from_v<Class<int, float, char>, Base<int>>;
	bool b = Xf::is_base_of_v<Base<int>, Class<int, float, char>>;
	*/

	bool s1 = Xf::is_base_of_v<Base<int>, Base<int>>;
	bool s2 = Xf::is_derived_from_v<int, void>;

	std::cout << s2 << std::endl;

	using Base    = Base<int>;
	using Derived = Class<int, float, char>;


	//p1.assign(1, 2.0f, '3');

	//AutoP<A> p2 = AutoP<B>{1, 2.0f, '3'};

	//AutoP<B> p3{Xf::move(p1)};

	AutoP<Derived> p1 = make_auto_pointer<Derived>(123, 99.9f, 'X');
	if (!p1) {
		std::cout << "null" << std::endl;
	}

	AutoP<Base> p3;

	Xf::AutoPointer<Derived> p2;

	p2 << nullptr;

	p1 >> p2;

	Xf::move(p1) >> p2;

	own::AutoPointer<int> ptr_int = own::make_auto_pointer<int>(123);

	own::Vector<own::AutoPointer<int>> vec;

	vec.push_back(Xf::make_auto_pointer<int>(123));

	//Xf::AutoPointer<void> v{};


	std::cout << *p2 << std::endl;


	//AutoP<B> p4{p1};

	//p4.assign(p1);

	{
		//AutoP<A> base = Xf::make_auto_pointer<B>(1, 2.0f, '3');

	}


}

