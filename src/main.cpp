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






int main(int ac, char** av) {

	xns::tree<const int> __tree;
	//auto ii = __tree.pre_order_begin();
	xns::tree<const int>::pre_order_iterator _iii = __tree.pre_order_begin();
	//xns::tree<const int>::const_pre_order_iterator _iii{iiii};




	while (_iii != __tree.end()) {
		std::cout << "here" << std::endl;
		const int& ptr = *_iii;

		std::cout << *_iii << std::endl;
		++_iii;
	}

		//const int ptr = *_iii;



	using node = xns::tree<char>::node;

	xns::tree<char> ast;




	node* node0 = ast.new_node('a');
	node* node1 = ast.new_node('b');
	node* node2 = ast.new_node('c');
	node* node3 = ast.new_node('d');
	node* node4 = ast.new_node('e');
	node* node5 = ast.new_node('f');
	node* node6 = ast.new_node('g');
	node* node7 = ast.new_node('h');
	node* node8 = ast.new_node('i');
	node* node9 = ast.new_node('j');


	node0->left(node1);
	node0->right(node2);

	node1->left(node3);
	node1->right(node4);

	node2->left(node5);
	node2->right(node6);

	node3->left(node7);
	node3->right(node8);

	node4->left(node9);


const char* tree = R"(
            a
         /     \
        b       c
      /   \   /   \
     d     e f     g
    / \   /
   h   i j
)";



	ast.root(node0);

	auto it = ast.pre_order_begin();

	std::cout << tree << std::endl;

	//xns::cstring newick = ast.newick(node0);
	//xns::cstring dot = ast.dot(node0);

	//std::cout << newick.pointer() << std::endl;
	//std::cout << dot.pointer() << std::endl;


	xns::tree<int>::size_type depth = 0;
	xns::tree<int>::size_type level = 0;

	const xns::tree<int>::size_type max_depth = ast.depth();

	xns::tree<int>::size_type max = 0;

	while (it != ast.end()) {

		// get max number of children in a branch
		depth = ast.depth(it);
		max = ast.max_line(it);
		level = ast.level(it);

		// check if we are on a new level
		//if (level != ast.level(it)) {
		//	level = ast.level(it);
			std::cout << std::endl << std::endl;
		//}
		//std::cout << std::endl << std::endl;


		// compute number of spaces to print
		const xns::tree<int>::size_type spaces = level * 10;

		// print spaces
		for (xns::tree<int>::size_type i = 0; i < spaces; ++i) { std::cout << " "; }

		std::cout << *it;
		std::cout << "[\x1b[32m" << ast.max_line(it) << "\x1b[0m]";
		std::cout << "[\x1b[34m" << ast.level(it) << "\x1b[0m]";
		std::cout << "[\x1b[33m" << ast.depth(it) << "\x1b[0m]";

		++it;

	}

	std::cout << std::endl << std::endl;





	return EXIT_SUCCESS;




}
#endif





