#ifndef XNS_FRAGMENTATION_HPP
#define XNS_FRAGMENTATION_HPP

#include "vector.hpp"
#include "terminal.hpp"
#include "macros.hpp"
#include "numeric_limits.hpp"
#include "escape.hpp"
#include "color.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F R A G M E N T A T I O N -------------------------------------------

	class fragmentation final {

		public:

			/* print memory fragmentation */
			static auto display(const xns::vector<void*>&) -> void;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = fragmentation;

			/* size_type */
			using size_type = xns::addr_t;




			// -- private lifecycle -------------------------------------------

			/* addrs constructor */
			inline fragmentation(const xns::vector<void*>&);

			/* non-assignable class */
			unassignable(fragmentation);

			/* destructor */
			inline ~fragmentation(void) = default;



			// -- private members ---------------------------------------------

			/* addrs */
			const xns::vector<void*>& _addrs;

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
