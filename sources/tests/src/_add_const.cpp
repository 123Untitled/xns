#include "xns/type_traits/type_modifications/add_const.hpp"
#include <concepts>
#include <iostream>


template <typename T, typename U>
concept local_is_same = std::same_as<T, U>;

template <typename T, typename U, typename V>
static auto check(void) -> int {
	if constexpr (local_is_same<T, U>){// && local_is_same<T, V>) {
		std::cout << "\x1b[32m" << "success" << "\x1b[0m" << std::endl;
		return 0;
	}
	else {
		std::cout << "\x1b[31m" << "failure" << "\x1b[0m" << std::endl;
		return 1;
	}
}


/* unit test */
auto unit_tests_add_const(void) -> int {

	using func = auto(*)(void) -> int;

	func f[] {

		&check<xns::add_const<int>, std::add_const_t<int>, const int>,
		&check<xns::add_const<int&>, std::add_const_t<int&>, int&>,
		&check<xns::add_const<int&&>, std::add_const_t<int&&>, const int&>,
		&check<xns::add_const<int*>, std::add_const_t<int*>, int* const>,
		&check<xns::add_const<int* const>, std::add_const_t<int* const>, int* const>,
		&check<xns::add_const<int* volatile>, std::add_const_t<int* volatile>, int* const volatile>,
		&check<xns::add_const<int* const volatile>, std::add_const_t<int* const volatile>, int* const volatile>,
		&check<xns::add_const<int[]>, std::add_const_t<int[]>, const int[]>,
		&check<xns::add_const<int[1]>, std::add_const_t<int[1]>, const int[1]>,
		&check<xns::add_const<int(*)[]>, std::add_const_t<int(*)[]>, int(*const)[]>,
		&check<xns::add_const<int(&)[]>, std::add_const_t<int(&)[]>, int(&)[]>,
		&check<xns::add_const<int(&&)[]>, std::add_const_t<int(&&)[]>, int(&&)[]>,

		&check<xns::add_const<const int>, std::add_const_t<const int>, const int>,
		&check<xns::add_const<const int&>, std::add_const_t<const int&>, const int&>,
		&check<xns::add_const<const int&&>, std::add_const_t<const int&&>, const int&&>,
		&check<xns::add_const<const int*>, std::add_const_t<const int*>, const int*>,
		&check<xns::add_const<const int* const>, std::add_const_t<const int* const>, const int* const>,
		&check<xns::add_const<const int* volatile>, std::add_const_t<const int* volatile>, const int* volatile>,
		&check<xns::add_const<const int* const volatile>, std::add_const_t<const int* const volatile>, const int* const volatile>,
		&check<xns::add_const<const int[]>, std::add_const_t<const int[]>, const int[]>,
		&check<xns::add_const<const int[1]>, std::add_const_t<const int[1]>, const int[1]>,
		&check<xns::add_const<const int(*)[]>, std::add_const_t<const int(*)[]>, const int(*const)[]>,
		&check<xns::add_const<const int(&)[]>, std::add_const_t<const int(&)[]>, const int(&)[]>,
		&check<xns::add_const<const int(&&)[]>, std::add_const_t<const int(&&)[]>, int(&)[]>,


		nullptr
	};
		//&check<xns::add_const<int[1]>, std::add_const_t<int[1]>>,
		//&check<xns::add_const<int(*)[]>, std::add_const_t<int(*)[]>>,
		//&check<xns::add_const<int(&)[]>, std::add_const_t<int(&)[]>>,
		//&check<xns::add_const<int(&&)[]>, std::add_const_t<int(&&)[]>>,
		//
		//&check<xns::add_const<const int>, std::add_const_t<const int>>,
		//&check<xns::add_const<const int&>, std::add_const_t<const int&>>,
		//&check<xns::add_const<const int&&>, std::add_const_t<const int&&>>,
		//&check<xns::add_const<const int*>, std::add_const_t<const int*>>,
		//&check<xns::add_const<const int* const>, std::add_const_t<const int* const>>,
		//&check<xns::add_const<const int* volatile>, std::add_const_t<const int* volatile>>,
		//&check<xns::add_const<const int* const volatile>, std::add_const_t<const int* const volatile>>,
		//&check<xns::add_const<const int[]>, std::add_const_t<const int[]>>,
		//&check<xns::add_const<const int[1]>, std::add_const_t<const int[1]>>,
		//&check<xns::add_const<const int(*)[]>, std::add_const_t<const int(*)[]>>,
		//&check<xns::add_const<const int(&)[]>, std::add_const_t<const int(&)[]>>,
		//&check<xns::add_const<const int(&&)[]>, std::add_const_t<const int(&&)[]>>,
		//nullptr
	//};

	for (func* i = f; *i; ++i) {
		auto r = (*i)();
		if (r)
			return r;
	}

	return 0;
}


#if defined(XNS_TEST_ADD_CONST)
int main(void) {
	return unit_tests_add_const();
}
#endif
