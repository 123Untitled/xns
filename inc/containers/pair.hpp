#ifndef PAIR_HEADER
#define PAIR_HEADER

#include "move.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- P A I R -------------------------------------------------------------

	template <class T, class U>
	struct pair final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = pair<T, U>;

			/* first type */
			using first = T;

			/* second type */
			using second = U;


			// -- public members ----------------------------------------------

			/* first object */
			first _first;

			/* second object */
			second _second;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			pair(void)
			: _first{}, _second{} { }

			/* copy pair constructor */
			pair(const first& first, const second& second)
			: _first{first}, _second{second} { }

			/* move pair constructor */
			pair(first&& first, second&& second)
			: _first{xns::move(first)}, _second{xns::move(second)} { }

			/* copy constructor */
			pair(const self& other)
			: _first{other._first}, _second{other._second} { }

			/* move constructor */
			pair(self&& other)
			: _first{xns::move(other._first)}, _second{xns::move(other._second)} { }

			/* destructor */
			~pair(void) { }


			// -- O P E R A T O R S -------------------------------------------

			/* copy operator */
			self& operator=(const self& other) {
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
			self& operator=(self&& other) {
				// check for self assignment
				if (this != &other) {
					// move first object
					_first = xns::move(other._first);
					// move second object
					_second = xns::move(other._second);
				} // return self reference
				return *this;
			}

	};

};

#endif
