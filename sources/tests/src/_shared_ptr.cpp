#include "unit_tests.hpp"
#include "shared_ptr.hpp"

#include <memory>
#include <iostream>

class _B; // Déclaration anticipée de la classe B

class _A {
public:
    std::shared_ptr<_B> b_ptr;
    ~_A() { std::cout << "A destructeur\n"; }
};

class _B {
public:
    std::shared_ptr<_A> a_ptr;
    ~_B() { std::cout << "B destructeur\n"; }
};



/* unit test */
template <>
int UT::unit_tests<"shared_ptr">(void) {

    auto a = std::make_shared<_A>();
    auto b = std::make_shared<_B>();

    a->b_ptr = b;
    b->a_ptr = a;


	//xns::shared_ptr<int> a;
	//xns::shared_ptr<int> b;
	//{
	//	xns::shared_ptr<int> c = xns::make_shared<int>(5);
	//	b = c;
	//	a = b;
	//}



	return 0;
}

#if defined(XNS_TEST_SHARED_PTR)
int main(void) {
	return UT::unit_tests<"shared_ptr">();
}
#endif


