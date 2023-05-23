#include "tuple.hpp"
#include "vector.hpp"
#include "xns.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <stack>
#include <any>

#include "random.hpp"
#include "trie.hpp"

#include "policy.hpp"

#include "safe_enum.hpp"
#include "literal.hpp"

#include "path.hpp"
// curiously recurring template pattern (CRTP) learn


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



#if !defined(XNS_UT)
int main(int ac, char** av) {


	//UT::meta_ut();
	//using unix_pp = xns::tuple<literal("/"), literal(".."), literal(".")>;

	//auto p0 = xns::make_path<unix_pp>("h/e/l/l/o");

	//auto p = xns::make_path<literal("/ "), literal(".."), literal(".")>("// well / hello / there /");


	return 0;


	//using t = path("/", "..", ".");

	/*
	using unix_path = xns::path<literal("/"), literal(".."), literal(".")>;

	unix_path p = xns::make_path<
		literal("/"),
		literal(".."),
		literal(".")>("h/e/l/l/o");

	unix_path p2 = xns::make_path("h/e/l/l/o");
	*/

	return 0;


	for (int i = 0 ; i < 20 ; ++i) {
		xns::output::write(xns::id::generate());
		xns::output::write("\n");
		//std::cout<< xns::id::generate().pointer() << std::endl;
	}
	//xns::output::write("hello", 5);
	xns::output::render<xns::stdout>();

	return 0;

	std::cout << (int)xns::max<char>() << std::endl;

	using toto_t = xns::literal<char, 'h', 'e', 'l', 'l', 'o'>;

	xns::output::write<toto_t>();

	xns::output::render<xns::stderr>();

	return 0;




	using policy = xns::moveable_t;

	//xns::vector<int, policy> v1{};

	//xns::vector<int, policy> v2{v1};

	auto v3 = xns::make_vector<int, policy>(1, 2, 3);

	for (xns::vector<int, policy>::size x = 0; x < v3.length(); ++x) {
		std::cout << v3[x] << std::endl;
	}

	/*

	Toto<policy> t;

	Toto<policy> t2{Xf::move(t)};
	//Toto<policy> t3{t};
	*/


	return 0;





	//using Proto = Xf::PolyMethod<Xf::UniquePointer<B>(void)>;
	//Xf::PolyMethod<Xf::UniquePointer<B>(void)> pm{f};
	//invoke<Proto>(pm);

	std::cout << sizeof(void*) << std::endl;

	xns::array a = xns::make_array(1, 2, 3);

	return EXIT_SUCCESS;


	Xf::Trie<xns::cstring> trie;

	xns::vector<xns::cstring> v;

	v.emplace_back("cd");
	v.emplace_back("go");
	v.emplace_back("move");

	trie.insert(v, "!!!");

	for (xns::vector<xns::cstring>::size x = 0; x < v.length(); ++x) {
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







	xns::unique_ptr<int> ap;
	xns::weak_ptr<int> wp{ap};
	return EXIT_SUCCESS;




	Xf::Trie<std::string> trie2;
	xns::cstring str = "hello";
	//trie2.insert(str, "world");
	//trie2.insert(str, "world2");

	//Xf::AutoPointer<std::string> p = trie.find(Xf::CString{"hello"});


	/*
	std::cout << "check" << std::endl;
	if (p != nullptr) {
		std::cout << "found: " << *p << std::endl;
	}
	else {
		std::cout << "not found" << std::endl;
	}*/

    //Xf::Vector<Xf::Tuple<int, float>> v;

    //v.emplace_back(2, 2.2f);

	//char c = 'a';
	//int n = 10;
	//Xf::Tuple<char, int> tuple{'a', n};

	//UT::array_ut();
	//UT::tuple_ut();



	return EXIT_SUCCESS;

	for (auto i = 0; i < 10; ++i) {
		std::cout << xns::random::random_gen(10) << std::endl;
	}

}
#endif





