#include "xns/memory/allocator.hpp"


class A {
	public:
		A(void) = default;
		A(int n): _n{n} {}
		A(const A&) = default;
		A(A&&) = default;
		~A(void) = default;
		A& operator=(const A&) = default;
		A& operator=(A&&) = default;
		void print(void) const {
			std::cout << "A" << std::endl;
		}
	private:

		int _n;
};

/* unit test */
auto unit_tests_allocator(void) -> int {

	using T = A;
	using alloc = xns::allocator<T>;
	//using alloc = allocator2<T>;

	T a{123};

	T* ptr = nullptr;

	ptr = alloc::allocate(1);

	alloc::construct(ptr);
	alloc::construct(ptr, a);
	alloc::construct(ptr, std::move(a));
	alloc::construct(ptr, 123);

	//alloc::deallocate(ptr);


	// code here...
	return 0;
}

#if defined(XNS_TEST_ALLOCATOR)
int main(void) {
	return unit_tests_allocator();
}
#endif

