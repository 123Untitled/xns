#ifndef XNS_FRAGMENTATION_HPP
#define XNS_FRAGMENTATION_HPP

#include "xns/containers/vector.hpp"
#include "xns/terminal/terminal.hpp"
#include "xns/config/macros.hpp"
#include "xns/utility/numeric_limits.hpp"
#include "xns/terminal/escape.hpp"
#include "xns/color/color.hpp"
#include "xns/math/math.hpp"

#include <vector>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <typename T, typename... A>
	auto deviation(T&& value, A&&... values) -> T {

		constexpr auto n = sizeof...(A) + 1;
		// compute avg
		T avg = (value + ... + values) / n; 
		// variance computation
		T variance = ((xns::pow(value - avg, 2) + ... + xns::pow(values - avg, 2)) / (n - 1));
		// return standard deviation
		return xns::sqrt(variance);
	}

	// -- F R A G M E N T A T I O N -------------------------------------------

	class fragmentation final {

		public:

			/* print memory fragmentation */
			static auto display(const std::vector<void*>&) -> void;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = fragmentation;

			/* size_type */
			using size_type = xns::uintptr_t;




			// -- private lifecycle -------------------------------------------

			/* addrs constructor */
			fragmentation(const std::vector<void*>&);

			/* non-assignable class */
			unassignable(fragmentation);

			/* destructor */
			~fragmentation(void) = default;



			// -- private members ---------------------------------------------

			/* addrs */
			const std::vector<void*>& _addrs;

			/* terminal width */
			const size_type _width;

			/* min address */
			size_type _min_avg;

			/* max address */
			size_type _max_avg;


	};


	// bressenham's like algorithm
	// not for lines but for discrete points in 1D
	template <typename T>
	class divisor_iterator final {

		static_assert(xns::is_integral<T>, "): DIVISOR_ITERATOR: T must be integral :(");

		public:

			using self = xns::divisor_iterator<T>;

			using size_type = T;


			int euclid_stateless(void) const noexcept {
				//return _idx % _step < _pulse;
				return (_pulse * (_idx + _rotate)) % _step < _pulse;
			}



			inline constexpr divisor_iterator(const size_type step, const size_type pulse) noexcept
			: _step{step}, _pulse{pulse}, _rotate{0}, _idx{0}, _state{0} {
				do {
					++_state;
					++_idx;
				} while (!euclid_stateless());
			}

			constexpr auto operator++(void) noexcept -> self& {
				_state = 0;
				do {
					++_state;
					++_idx;
				} while (!euclid_stateless());
				return *this;
			}

			inline constexpr auto operator*(void) const noexcept -> size_type {
				return _state;
			}


			explicit inline constexpr operator bool(void) const noexcept {
				return _idx <= _step;
			}

			inline constexpr auto operator!(void) const noexcept -> bool {
				return _idx > _step;
			}

		private:

			size_type _step, _pulse, _rotate, _idx, _state;

	};


}

#endif
