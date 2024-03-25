/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_PROBABILITY_HEADER
#define XNS_PROBABILITY_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/containers/vector.hpp"
#include "xns/containers/tuple.hpp"

#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- P R O B A B I L I T Y -----------------------------------------------

	template <typename T>
	class probability final {

		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* value type */
			using value_type = T;

			/* tuple type */
			using tuple = xns::tuple<value_type, float>;

			/* vector type */
			using vector = xns::vector<tuple>;

			/* size type */
			using size_type = typename vector::size;


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			vector _data;

			/* sum */
			float _sum;


		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			probability(void) {
			}

			/* capacity constructor */
			probability(const size_type size) {
				_data.reserve(size);
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* push value */
			void push(const value_type& value, const float prob) {
				// push value and probability
				_data.emplace_back(value, prob);
				// update sum
				_sum += prob;
			}

			/* move value */
			void push(value_type&& value, const float prob) {
				// move value and push probability
				_data.emplace_back(xns::move(value), prob);
				// update sum
				_sum += prob;
			}

			/* pop value */
			void pop(const size_type index) {
				// check index
				if (index >= _data.size()) { return; }
				// update sum
				_sum -= _data[index].template get<float>();
				// pop value
				// _data.erase(index);
			}



			/* launch */
			const value_type& launch(void) const {
				// set random seed
				std::srand(static_cast<unsigned int>(::getpid()));
				// get random number
				const float random = std::rand() % (size_type)_sum;
				// get probability
				float prob = 0.0;
				size_type x = 0;
				// loop through data
				for (size_type s = _data.size(); x < s; ++x) {
					// add probability
					prob += _data[x].template get<float>();
					// check probability
					if (prob >= random) { break; }
				}
				// return probability value
				return _data[x].template get<value_type>();
			}


		private:



	};


} // namespace xns

#endif // XNS_PROBABILITY_HEADER
