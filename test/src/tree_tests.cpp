#include "unit_tests.hpp"
#include "tree.hpp"
#include "random.hpp"
#include "time.hpp"
#include "numeric_limits.hpp"
#include "input.hpp"
#include <set>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <map>
#include "escape.hpp"
#include "memcpy.hpp"
#include "benchmark.hpp"
#include "file.hpp"



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
		nodes.push_back(ast.new_node(nullptr, c));
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

	//ast.print();

	return ast;
}


static xns::size_t NSIZE = 0;




static void benchmark01(void) {

	int fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1) {
		std::cout << "error opening /dev/urandom" << std::endl;
		return ;
	}


	xns::benchmark<10> bench;

	using type = xns::size_t;

	// xns::memory::pool<xns::tree<xns::size_t>::node>::init();

	xns::vector<bool> res;
	xns::tree<type> tree;
	std::set<type> set;


	bench.run("xns::tree insert", [&tree, &fd]() -> void {

			for (xns::size_t i = 0; i < NSIZE; ++i) {
				type n = 0;
				::read(fd, &n, sizeof(type));

				tree.insert(n);
			}
	});

	bench.run("std::set insert", [&set, &fd]() -> void {

			for (xns::size_t i = 0; i < NSIZE; ++i) {
				type n = 0;
				::read(fd, &n, sizeof(type));

				set.insert(n);
			}
	});

	bench.result("insert");
	std::cout << "tree size: " << tree.size() << std::endl;
	std::cout << "set size: " << set.size() << std::endl;


	bench.run("xns::tree contains", [&tree, &fd, &res]() -> void {

			for (xns::size_t i = 0; i < NSIZE; ++i) {
				type n = 0;
				::read(fd, &n, sizeof(type));

				res.push_back(tree.contains(n));
			}
	});



	bench.run("std::set contains", [&set, &fd, &res]() -> void {

			for (xns::size_t i = 0; i < NSIZE; ++i) {
				type n = 0;
				::read(fd, &n, sizeof(type));

				res.push_back(set.contains(n));
			}
	});



	bench.result("contains");


	int fdr = open("results.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);


	if (fdr == -1) {
		std::cout << "error opening results.txt" << std::endl;
		return ;
	}

	for (xns::size_t i = 0; i < NSIZE; ++i) {
		if (res[i]) { ::write(fdr, "1", 1); }
		else { ::write(fdr, "0", 1); }
	}

	close(fd);
	close(fdr);




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
		vec.push_back(r);
	}



	for (auto& i : vec) {
		//std::cout << "\x1b[32m" << i << "\x1b[0m" << std::endl;
		//std::cout << std::endl;
		tree.insert(i);
		tree.print();
		usleep(10000);
		// std::cout << "tree depth: " << tree.depth() << std::endl;
		// std::cout << "tree size: " << tree.size() << std::endl << std::endl;
	}
		check_tree(tree);
	return ;

	for (auto& i : vec) {
		tree.print();
		std::cout << "erasing: \x1b[31m" << i << "\x1b[0m" << std::endl;
		tree.erase(i);
		check_tree(tree);
		usleep(10000);
	}
	tree.print();





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
				std::cout << "\x1b[32mINSERT\x1b[0m" << std::endl;
				int i = xns::random::integral<int>() % 100;
				vec.push_back(i);
				tree.insert(i);

			tree.print();
			balanced = false;
		}
		// check for up arrow
		else if (input == "\x1b[A") {
			xns::print(xns::escape::erase_screen(), xns::escape::move_home());
			xns::out::render();
			std::cout << "\x1b[31mBALANCE\x1b[0m" << std::endl;
			tree.print();
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
			}
			tree.insert(vec.back());
			balanced = false;
			tree.print();


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


template <>
bool UT::unit_tests<"tree">(void) {


	benchmark01();
	return true;
	insert();
	return true;
	interactive();
	return true;

}


int main(int ac, char** av) {




	if (ac == 2) {
		// atoi
		NSIZE = atoi(av[1]);
	}
	return UT::unit_tests<"tree">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}
