#include "xns.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <stack>
#include <any>

#include "unit_tests.hpp"


#if !defined(XNS_UT)


xns::size_t tpsc(const char& c) {
	return 1;
}

xns::cstring tpvc(const char& c) {
	std::cout << "value: " << c << std::endl;
	xns::cstring s(&c, 1);
	std::cout << "cstring: " << s.pointer() << std::endl;
	return xns::cstring(&c, 1);
}


void generate_tree(const xns::size_t size) {
	// check size
	if (!size) { return; }
	// create tree
	xns::tree<char> ast;
	// vector of node pointers
	xns::vector<xns::tree<char>::node*> nodes;
	// reserve space for nodes
	nodes.reserve(size);
	// loop to allocate nodes
	for (auto i = nodes.start(); i < size; ++i) {
		char c = xns::random::random_gen(94 - 33) + 33;
		nodes.copy_back(ast.new_node(c));
	}
	// set root node
	ast.root(nodes[0]);
	// alias to node
	using node = xns::tree<char>::node;

	node* current = nodes[0];

	for (auto i = nodes.start() + 1; i < size; ++i) {
		do {
			if (xns::random::random_bool()) {

				if (current->left())  { current = current->left();  }

				else { current->set_left(nodes[i]); break; }
			}
			else {
				if (current->right()) { current = current->right(); }

				else { current->set_right(nodes[i]); break; }
			}
		} while (true);

		// reset current to root
		current = nodes[0];
	}


	ast.print(tpsc, tpvc);

}




int main(int ac, char** av) {

	xns::terminal::raw_terminal();

	using node = xns::tree<char>::node;

	while (true) {
		generate_tree(xns::random::random_gen(30) + 3);
		char c; int r = read(0, &c, 1);
		if (r != 1 || c == 'q') { break; }
	}

	xns::terminal::restore_terminal();
	return EXIT_SUCCESS;

//	const char* tree = R"(
//            a
//         /     \
//        b       c
//      /   \   /   \
//     d     e f     g
//    / \   /
//   h   i j
//	)";
	//std::cout << tree << std::endl;



	//auto it = ast.pre_order_begin();


	////xns::cstring newick = ast.newick(node0);
	////xns::cstring dot = ast.dot(node0);

	////std::cout << newick.pointer() << std::endl;
	////std::cout << dot.pointer() << std::endl;


	//xns::tree<int>::size_type depth = 0;
	//xns::tree<int>::size_type level = 0;

	//const xns::tree<int>::size_type max_depth = ast.depth();

	//xns::tree<int>::size_type max = 0;

	//while (it != ast.end()) {

	//	// get max number of children in a branch
	//	depth = ast.depth(it);
	//	max = ast.max_width(it);
	//	level = ast.level(it);

	//	// check if we are on a new level
	//	//if (level != ast.level(it)) {
	//	//	level = ast.level(it);
	//		std::cout << std::endl << std::endl;
	//	//}
	//	//std::cout << std::endl << std::endl;


	//	// compute number of spaces to print
	//	const xns::tree<int>::size_type spaces = level * 10;

	//	// print spaces
	//	for (xns::tree<int>::size_type i = 0; i < spaces; ++i) { std::cout << " "; }

	//	std::cout << *it;
	//	std::cout << "[\x1b[32m" << ast.max_width(it) << "\x1b[0m]";
	//	std::cout << "[\x1b[34m" << ast.level(it) << "\x1b[0m]";
	//	std::cout << "[\x1b[33m" << ast.depth(it) << "\x1b[0m]";

	//	++it;

	//}

	//std::cout << std::endl << std::endl;





	return EXIT_SUCCESS;




}
#endif





