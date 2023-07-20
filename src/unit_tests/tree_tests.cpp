#include "unit_tests.hpp"
#include "tree.hpp"
#include "random.hpp"


xns::size_t tpsc(const char& c) {
	return 1;
}

xns::string tpvc(const char& c) {
	xns::string s(&c, 1);
	return xns::string(&c, 1);
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
		//char c = xns::random::random_gen(94 - 33) + 33; // NEED TO IMPLEMENT RANDOM TEMPLATE, to fix implicite conversion
		char c = 'a';
		nodes.copy_back(ast.new_node(c));
	}
	auto p = ast.new_node('r');
	// set root node
	ast.root(p);
	p->set_right(nodes[0]);
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

	auto it = ast.in_order_begin();
	ast.print(tpsc, tpvc);

	while (it != ast.end()) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

}


template <>
bool UT::unit_tests<"tree">(void) {


	generate_tree(30);
	return true;

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


	return true;
}
