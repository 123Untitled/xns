#ifndef AST_HEADER
#define AST_HEADER

// local headers
#include "vector.hpp"
#include "string.hpp"
#include "memory.hpp"
#include "unique_ptr.hpp"




#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// node types:
	// binary operators (add, sub, mul, div, mod, pow, eq, ne, lt, gt, le, ge, and, or, xor, shl, shr)
	// unary operators (neg, not, inc, dec)
	// literals (int, float, string, bool)
	// identifiers (var, func, class, enum, struct, union, namespace)
	// statements (block, if, while, for, foreach, switch, case, default, break, continue, return, throw, try, catch)
	// declarations (var, func, class, enum, struct, union, namespace)
	// definitions (var, func, class, enum, struct, union, namespace)
	// expressions (call, index, member, cast, sizeof, alignof, typeid, new, delete)
	// other (empty, error)

	// these are the node types that are used in the AST
	// but i want to implement a more generic system
	// node types:
	// leaf
	// branch (binary, unary, ternary, n-ary)

	template <typename T>
	class ast final {

		private:

			// -- private forward declarations --------------------------------

			/* node */
			class node;


		public:

			// -- public types ------------------------------------------------

			/* node pointer type */
			using node_ptr = node*;


			template <typename U>
			node_ptr new_node(void) {

				return new node();
			}


		private:

			class node {

				private:

					// -- private members -----------------------------------------

					/* parent */
					node_ptr _parent;

			};


			class unary final : public node {

				private:

					// -- private members -----------------------------------------

			};

			class binary final : public node {


				private:

					// -- private members -----------------------------------------

					/* left */
					xns::unique_ptr<node> _left;

					/* right */
					xns::unique_ptr<node> _right;

			};

			class ternary final : public node {


				private:

					// -- private members -----------------------------------------

					/* left */
					xns::unique_ptr<node> _left;

					/* middle */
					xns::unique_ptr<node> _middle;

					/* right */
					xns::unique_ptr<node> _right;

			};


			class n_ary final : public node {


				private:

					// -- private members -----------------------------------------

					/* children */
					xns::vector<xns::unique_ptr<node>> _childs;

			};



			class leaf final : public node {

			};


	};



}

#endif // AST_HEADER
