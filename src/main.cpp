#include "atoi.hpp"
#include "unique_pointer.hpp"
#include "xns.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <stack>
#include <any>

#include "variant.hpp"


#include "map.hpp"
#include "print.hpp"


template <class T>
struct type_name {

		static constexpr const char* name(void) {

			if constexpr (xns::is_same<T, int>) {
				return "int";
			}
			if constexpr (xns::is_same<T, float>) {
				return "float";
			}

				return "unknown";
		}
};

void funcc(void);

class TT {

	public:

		TT(void) {
			std::cout << "TT::TT()" << std::endl;
		}

		~TT(void) {
			std::cout << "TT::~TT()" << std::endl;
		}

		NON_ASSIGNABLE(TT);
};

#include "unit_tests.hpp"


template <xns::is_safe_enum E>
void funccc(void) {

}

struct def {
	using type = xns::s64;
	enum enum_type : type {
		MAX = 100
	};
};

using safe = xns::safe_enum<def>;


struct hire {

};


#include "any.hpp"
#include "index_of.hpp"

struct c1 {
	c1(void) {
		std::cout << "c1 constructor" << std::endl;
	}
	~c1(void) {
		std::cout << "c1 destructor" << std::endl;
	}
	c1& operator=(int) {
		std::cout << "c1 operator=" << std::endl;
		return *this;
	}
};

struct c2 {
	c2(void) {
		std::cout << "c2 constructor" << std::endl;
	}
	~c2(void) {
		std::cout << "c2 destructor" << std::endl;
	}
	c2& operator=(int) {
		std::cout << "c2 operator=" << std::endl;
		return *this;
	}
};

struct c3 {
	c3(void) {
		std::cout << "c3 constructor" << std::endl;
	}

	~c3(void) {
		std::cout << "c3 destructor" << std::endl;
	}

	c3& operator=(int) {
		std::cout << "c3 operator=" << std::endl;
		return *this;
	}
};

#include "is_all_unique.hpp"

#if !defined(XNS_UT)

int main(int ac, char** av) {

	xns::safe_union<int*, xns::u32*> u0;

	std::cout << "sizeof(u0) = " << sizeof(u0) << std::endl;



	xns::safe_union<int, void*, float> u;


	std::cout << u.get<int>() << std::endl;
	u.set<float>(123);
	const int i = u.get<int>();
	std::cout << u.get<int>() << std::endl;
	xns::safe_union<int, void*, float> u2 = u;
	std::cout << u2.get<int>() << std::endl;

	xns::safe_union<int, char> iii;
	//if (u == 2) {
	//	std::cout << "equal" << std::endl;
	//}

	if (u) {
		std::cout << "true" << std::endl;
	}

	if (u == 1230.0f) {
		std::cout << "equal" << std::endl;
	}
	else {
		std::cout << "not equal" << std::endl;
	}

	u.reset();

	if (!u) {
		std::cout << "false" << std::endl;
	}

	std::cout << u.get<int>() << std::endl;



	/*
	u.set<int>(10);
	u.destroy<int>();
	u.set<char>('a');

	std::cout << "int: " << u.get<int>() << std::endl;
	std::cout << "float: " << u.get<char>() << std::endl;
	*/

	//xns::size_t sizee = xns::size_of_max<bbase>();
	//xns::size_t align = xns::align_of_max<bbase>();
	//std::cout << sizee << std::endl;
	//std::cout << align << std::endl;
	return EXIT_SUCCESS;



	// test with xns::unique_ptr
	xns::unique_ptr<tests::derived> derived = xns::make_unique_pointer<tests::derived>();

	auto& ref = derived.as<tests::base>();

	xns::unique_ptr<tests::base> base = xns::make_unique_pointer<tests::base>();

	//tests::derived& ref2 = base.as<tests::derived>();


	ref->echo();

	//ref->echo();

	/*
	xns::unique_ptr<tests::base> ptr = xns::move(derived);
	xns::unique_ptr<tests::base> ptr2;
	ptr2 = xns::move(derived);
	*/


	// test with std::unique_ptr
	/*
	std::unique_ptr<tests::derived> derived2 = std::make_unique<tests::derived>();
	std::unique_ptr<tests::base>& ref2 = derived2;
	std::unique_ptr<tests::base> ptr3 = std::move(derived2);
	std::unique_ptr<tests::base> ptr4;
	ptr4 = std::move(derived2);
	*/








	/*
	xns::any a = 1;

	xns::any b = 2.0f;

	xns::any c = xns::cstring{"hello"};
	*/

	//a = c;

	//std::cout << a.s_cast<xns::cstring>() << std::endl;


	return EXIT_SUCCESS;


	//std::cout << xns::max<xns::s64>() << std::endl;

	xns::string_view sv = "  -1234 ";
	//xns::cstring sv = "1234";
	xns::s64 num;
	xns::string_to_integer(sv, num);

	std::cout << num << std::endl;

	return EXIT_SUCCESS;



	xns::cstring str11 = "hello";
	xns::cstring str22 = "world";
	xns::string_view str33 = "hello";

	if (str33 != str11) {
		std::cout << "equal" << std::endl;
	}
	else {
		std::cout << "not equal" << std::endl;
	}




	if (str11 != str22) {
		std::cout << "equal" << std::endl;
	}
	else {
		std::cout << "not equal" << std::endl;
	}


	UT::path_ut();
	return EXIT_SUCCESS;
	funccc<xns::safe_enum<int>>();


	constexpr xns::string_view s = "hello";

	constexpr xns::size_t size = s.length();

	std::cout << "string: " << s.pointer() << "\nsize: " << size << std::endl;


	xns::string_view s2{s};

	s2 = s;

	//std::cout << "string: " << s2.pointer() << "\nsize: " << s2.length() << std::endl;


	return EXIT_SUCCESS;



	//xns::path p {"/home/alexander/Downloads/1.txt"};



	xns::print("");



	//xns::map<xns::cstring, xns::cstring> map;

	//map.copy_insert("cd", "cd");


	return EXIT_SUCCESS;






	xns::trie<xns::cstring> trie;

	xns::vector<xns::cstring> v;

	v.emplace_back("cd");
	v.emplace_back("go");
	v.emplace_back("move");

	trie.insert("cd", "cd");
	//trie.insert(v, "!!!");

	for (xns::vector<xns::cstring>::size_type x = 0; x < v.size(); ++x) {
		auto weak = trie.find(v[x]);
		if (weak != nullptr) {
			std::cout.write(weak->pointer(), weak->size()) << std::endl;
			std::cout << (xns::size_t)weak->pointer() << std::endl;
		}
		else {
			std::cout << "not found" << std::endl;
		}
	}

	return EXIT_SUCCESS;




}
#endif





