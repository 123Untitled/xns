#ifndef PAIR_HEADER
#define PAIR_HEADER

#include "move.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- P A I R  C L A S S ----------------------------------------------------

	template <typename T1, typename T2>
	struct Pair final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* first type */
			using First = T1;

			/* first reference type */
			using FirstRef = First&;

			/* first const reference type */
			using FirstConstRef = const First&;

			/* first move reference type */
			using FirstMoveRef = First&&;

			/* first pointer type */
			using FirstPtr = First*;

			/* first const pointer type */
			using FirstConstPtr = const First*;

			/* second type */
			using Second = T2;

			/* second reference type */
			using SecondRef = Second&;

			/* second const reference type */
			using SecondConstRef = const Second&;

			/* second move reference type */
			using SecondMoveRef = Second&&;

			/* second pointer type */
			using SecondPtr = Second*;

			/* second const pointer type */
			using SecondConstPtr = const Second*;


			// -- P U B L I C  M E M B E R S ----------------------------------

			/* first object */
			First _first;

			/* second object */
			Second _second;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Pair(void)
			// initializations
			: _first{}, _second{} { }

			/* copy pair constructor */
			Pair(FirstConstRef first, SecondConstRef second)
			// initializations
			: _first{first}, _second{second} { }

			/* move pair constructor */
			Pair(FirstMoveRef first, SecondMoveRef second)
			// initializations
			: _first{Xf::move(first)}, _second{Xf::move(second)} { }

			/* copy constructor */
			Pair(const Pair& other)
			// initializations
			: _first{other._first}, _second{other._second} { }

			/* move constructor */
			Pair(Pair&& other)
			// initializations
			: _first{Xf::move(other._first)}, _second{Xf::move(other._second)} { }

			/* destructor */
			~Pair(void) { }


			// -- O P E R A T O R S -------------------------------------------

			/* copy operator */
			Pair& operator=(const Pair& other) {
				// check for self assignment
				if (this != &other) {
					// copy first object
					_first = other._first;
					// copy second object
					_second = other._second;
				} // return self reference
				return *this;
			}

			/* move operator */
			Pair& operator=(Pair&& other) {
				// check for self assignment
				if (this != &other) {
					// move first object
					_first = Xf::move(other._first);
					// move second object
					_second = Xf::move(other._second);
				} // return self reference
				return *this;
			}

	};

};

#endif
