#include "unit_tests.hpp"
#include "tree.hpp"
#include "random.hpp"
#include "time.hpp"
#include "numeric_limits.hpp"
#include "input.hpp"

xns::size_t tpsc(const char& c) {
	return 1;
}

xns::string tpvc(const char& c) {
	return xns::string(&c, 1);
}

xns::size_t intsize(const int& i) {
	xns::string str;
	str.to_string(i);
	return str.size();
}

xns::string intstr(const int& i) {
	xns::string str;
	str.to_string(i);
	return str;
}

xns::size_t strsize(const xns::string& str) {
	return str.size();
}

xns::string strstr(const xns::string& str) {
	return str;
}



xns::tree<char> generate_tree(const xns::size_t size) {
	// check size
	if (!size) { return {}; }
	// create tree
	xns::tree<char> ast;
	// vector of node pointers
	xns::vector<xns::tree<char>::node*> nodes;
	// reserve space for nodes
	nodes.reserve(size);
	// loop to allocate nodes
	for (xns::size_t i = 0; i < size; ++i) {
		char c = (xns::random::integral<unsigned char>() % 94) + 33;
		nodes.copy_back(ast.new_node(nullptr, c));
	}
	// set root node
	ast.root(ast.new_node(nullptr, 'r'));
	// alias to node
	using node_ptr = xns::tree<char>::node_pointer;


	for (xns::size_t i = 0 + 1; i < size; ++i) {
		// start at root
		node_ptr current = ast.root();
		do {
			if (xns::random::integral<bool>()) {

				if (current->left())  { current = current->left();  }

				else { current->set_left(nodes[i]); break; }
			}
			else {
				if (current->right()) { current = current->right(); }

				else { current->set_right(nodes[i]); break; }
			}
		} while (true);
	}

	ast.print(tpsc, tpvc);

	return ast;
}



#include <set>
#include <chrono>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <map>

auto now(void) -> long long {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}


class benchmark final {

	public:
		benchmark(void) = default;
		~benchmark(void) = default;


		template <typename F, typename... A>
		static auto run(const char* msg, F&& func, A&&... args) -> void {
			// time of benchmark (5s in nanoseconds)
			xns::size_t alpha = 5'000'000'000;


			xns::size_t count = 0;

			constexpr xns::size_t max = xns::limits::max<xns::size_t>();

			auto start = xns::time::now();

			// no cursor
			::write(1, "\x1b[?25l", 6);

			while (((xns::time::now() - start) < alpha) && (count < max)) {
				std::cout << count << " operations\r";
				func(xns::forward<A>(args)...);
				++count;
			}

			// cursor on
			::write(1, "\x1b[?25h", 6);

			auto end = xns::time::now();

			std::cout << "\n" << msg << " : "
					  << count << " function calls in " << (end - start) / 1'000'000 << " ms"
					  << " (avg " << ((end - start) / count) << " ns)\n";
		}

	private:


};


static void benchmark2(void) {

	xns::size_t size{100'000'000U};
	//xns::size_t size{1000U};
	std::vector<xns::size_t> nvec;
	std::cout << "filling vector with [" << size << "] random numbers..." << std::endl;
	for (xns::size_t i = 0; i < size; ++i) {
		nvec.push_back(xns::random::integral<xns::size_t>());
	}
	std::cout << "done." << std::endl;

	{

		xns::size_t index = 0;


		benchmark::run("xns::tree insert", [&nvec]() -> void {
			xns::size_t N = 1000;
			xns::tree<xns::size_t> tree;
			for (std::size_t i = 0; i < N; ++i) {
				tree.insert(nvec[i]);
			}
		});

		benchmark::run("std::set insert", [&nvec]() -> void {
			xns::size_t N = 1000;
			std::set<xns::size_t> set;
			for (std::size_t i = 0; i < N; ++i) {
				set.insert(nvec[i]);
			}
		});




	}
	return;



	return;




	//std::vector<int> vec;

	//for (int i = 0; i < 1000000; ++i) {
	//	vec.push_back(xns::random::integral<int>());
	//}



	//benchmark::run("std::set insert", []() -> void {
	//	std::set<int> tree;
	//	for (int i = 0; i < 1000000; ++i) {
	//		tree.insert(i);
	//	}
	//});

	//benchmark::run("xns::tree insert", []() -> void {
	//	xns::tree<int> tree;
	//	for (int i = 0; i < 1000000; ++i) {
	//		tree.insert(i);
	//	}
	//});

	////xns::tree<int> tree;
	////std::set<int> set;
	//for (auto& i : vec) {
	//	tree.insert(i);
	//	set.insert(i);
	//}

	//benchmark::run("std::set contains", [](std::set<int>& set, std::vector<int>& vec) -> void {
	//	for (auto& i : vec) {
	//		set.contains(i);
	//	}
	//}, set, vec);

	//benchmark::run("xns::tree contains", [](xns::tree<int>& tree, std::vector<int>& vec) -> void {
	//	for (auto& i : vec) {
	//		tree.contains(i);
	//	}
	//}, tree, vec);





}




static auto benchmark(void) -> void {

	using type = std::size_t;


	// print lambda
	auto print = [](const char* msg, long long time) -> void {
		std::cout << msg << (double)time / (double)1000000 << " ms" << std::endl;
	};


	type ns[] = {100,
				1000,
				10000,
				100000,
				1000000};
				//10000000};


	// setup vector of random numbers
	std::vector<type> _vec;
	for (type i = 0; i < ns[sizeof(ns) / sizeof(type) - 1]; ++i) {
		_vec.push_back(xns::random::integral<type>());
	}


	// loop over N values
	for (type& N : ns) {

		std::cout << "\nBenchmarking with N = \x1b[32m" << N << "\x1b[0m" << std::endl;

		std::set<type> stree;
		xns::tree<type> xtree;


		xns::size_t std_time = 0;
		xns::size_t xns_time = 0;
			// insert
			{
				//auto start = now();
				auto start = xns::time::now();
				for (type i = 0; i < N; ++i) {
					stree.insert(_vec[i]);
				}
				//auto end = now();
				auto end = xns::time::now();
				print("  insert std::set  -> ", end - start);
				std_time = end - start;
			}
			{
				//auto start = now();
				auto start = xns::time::now();
				for (type i = 0; i < N; ++i) {
					xtree.insert(_vec[i]);
				}
				//auto end = now();
				auto end = xns::time::now();
				print("  insert xns::tree -> ", end - start);
				xns_time = end - start;
			}

			// calculate ratio
			if (std_time > xns_time) {
				std::cout << "  ------------------- \x1b[32m" << (double)std_time / (double)xns_time << "\x1b[0m times faster" << std::endl;
			}
			else if (std_time < xns_time) {
				std::cout << "  ------------------- \x1b[31m" << (double)xns_time / (double)std_time << "\x1b[0m times faster" << std::endl;
			}

			// contains
			{
				//auto start = now();
				auto start = xns::time::now();
				for (type i = 0; i < N; ++i) {
					stree.contains(_vec[i]);
				}
				//auto end = now();
				auto end = xns::time::now();
				print("  search std::set  -> ", end - start);
				std_time = end - start;
			}
			{
				//auto start = now();
				auto start = xns::time::now();
				for (type i = 0; i < N; ++i) {
					xtree.contains(_vec[i]);
				}
				//auto end = now();
				auto end = xns::time::now();
				print("  search xns::tree -> ", end - start);
				xns_time = end - start;
			}

			// calculate ratio
			if (std_time > xns_time) {
				std::cout << "  ------------------- \x1b[32m" << (double)std_time / (double)xns_time << "\x1b[0m times faster" << std::endl;
			}
			else if (std_time < xns_time) {
				std::cout << "  ------------------- \x1b[31m" << (double)xns_time / (double)std_time << "\x1b[0m times faster" << std::endl;
			}

	}

}


/* insert */
static auto insert(void) -> void {



	xns::tree<int> tree;
	xns::vector<int> vec;

	unsigned int n = (xns::random::integral<unsigned int>() % 20) + 30;
	//unsigned int n = 3;
	//unsigned int n = 100000;

	for (unsigned int i = 0; i < n; ++i) {
		int r = xns::random::integral<int>() % 100;
		//int r = xns::random::integral<int>();
		vec.copy_back(r);
	}



	for (auto& i : vec) {
		//std::cout << "\x1b[32m" << i << "\x1b[0m" << std::endl;
		//std::cout << std::endl;
		//usleep(10000);
		tree.insert(i);
		//tree.is_balanced();
		//tree.is_sorted();
		// std::cout << "tree depth: " << tree.depth() << std::endl;
		// std::cout << "tree size: " << tree.size() << std::endl << std::endl;
	}
	tree.print(intsize, intstr);


	//std::cout << "END OF TEST" << std::endl;

}


static auto interactive(void) -> void {

	xns::terminal::raw_terminal();
	xns::print(xns::escape::enter_screen(),
			xns::escape::move_home());
	xns::out::render();


	xns::tree<int> tree;
	std::vector<int> vec;
	bool balanced = false;

	xns::string input;

	while (true) {

		input = xns::in::read();

		// check for right arrow
		if (input == "\x1b[C") {
			xns::print(xns::escape::erase_screen(), xns::escape::move_home());
			xns::out::render();
			if (tree.is_balanced() == false) {
				std::cout << "\x1b[35mNOT BALANCED!\x1b[0m" << std::endl;
			}
			else {
				std::cout << "\x1b[32mINSERT\x1b[0m" << std::endl;
				int i = xns::random::integral<int>() % 100;
				vec.push_back(i);
				tree.insert(i);
			}

			tree.print(intsize, intstr);
			balanced = false;
		}
		// check for up arrow
		else if (input == "\x1b[A") {
			xns::print(xns::escape::erase_screen(), xns::escape::move_home());
			xns::out::render();
			std::cout << "\x1b[31mBALANCE\x1b[0m" << std::endl;
			tree.full_balance();
			tree.print(intsize, intstr);
			balanced = true;
		}
		// check for down arrow
		else if (input == "\x1b[B") {
			xns::print(xns::escape::erase_screen(), xns::escape::move_home());
			xns::out::render();
			std::cout << "\x1b[33mBACK\x1b[0m" << std::endl;
			tree.clear();

			for (std::vector<int>::size_type i = 0; i < vec.size() - 1; ++i) {
				tree.insert(vec[i]);
				tree.full_balance();
			}
			tree.insert(vec.back());
			balanced = false;
			tree.print(intsize, intstr);


		}
		else if (input == "q") {
			break;
		}
		else {
			std::cout << "unknown command" << std::endl;
		}
	}

	xns::print(xns::escape::exit_screen());
	xns::out::render();
	xns::terminal::restore_terminal();

}

#include "memory.hpp"

template <>
bool UT::unit_tests<"tree">(void) {

	xns::memory::pool<xns::tree<xns::size_t>::node>::init();

	insert();
	return true;
	benchmark2();
	return true;
	interactive();
	return true;


	xns::tree<char> tr = generate_tree(20);

	auto it = tr.in_order_begin();
	tr.print(tpsc, tpvc);

	while (it != tr.end()) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;


	return true;
}


int main(void) {
	UT::unit_tests<"tree">();
	return 0;
}
