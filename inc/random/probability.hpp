#ifndef PROBABILITY_HEADER
#define PROBABILITY_HEADER

#include "types.hpp"
#include "vector.hpp"
#include "tuple.hpp"

#include <unistd.h>


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- P R O B A B I L I T Y  C L A S S ------------------------------------

	template <class T>
	class Probability final {

		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* value type */
			using Value = T;

			/* tuple type */
			using Tuple = Xf::Tuple<Value, Float>;

			/* vector type */
			using vector = xns::vector<Tuple>;

			/* size type */
			using size = typename vector::size;


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			vector _data;

			/* sum */
			Float _sum;


		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			Probability(void) {
				// code here...
			}

			/* capacity constructor */
			Probability(const Size size) {
				_data.reserve(size);
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* push value */
			void push(const Value& value, const Float prob) {
				// push value and probability
				_data.emplace_back(value, prob);
				// update sum
				_sum += prob;
			}

			/* move value */
			void push(Value&& value, const Float prob) {
				// move value and push probability
				_data.emplace_back(xns::move(value), prob);
				// update sum
				_sum += prob;
			}

			/* pop value */
			void pop(const Size index) {
				// check index
				if (index >= _data.size()) { return; }
				// update sum
				_sum -= _data[index].template get<Float>();
				// pop value
				// _data.erase(index);
			}



			/* launch */
			const Value& launch(void) const {
				// set random seed
				std::srand(std::time(NULL) / getpid());
				// get random number
				const Float random = std::rand() % (UInt32)_sum;
				// get probability
				Float prob = 0.0;
				Size x = 0;
				// loop through data
				for (Size s = _data.size(); x < s; ++x) {
					// add probability
					prob += _data[x].template get<Float>();
					// check probability
					if (prob >= random) { break; }
				}
				// return probability value
				return _data[x].template get<Value>();
			}


		private:



	};







}

#endif
