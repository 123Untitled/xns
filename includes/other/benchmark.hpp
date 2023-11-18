#ifndef XNS_BENCHMARK_HEADER
#define XNS_BENCHMARK_HEADER

// local headers
#include "types.hpp"
#include "time.hpp"
#include "output.hpp"
#include "escape.hpp"
#include "string.hpp"
#include "tree.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <xns::size_t TIME_SEC>
	class benchmark final {


		public:

			// -- public lifecycle ------------------------------------------------

			/* default constructor */
			inline benchmark(void) noexcept
			: _benchs{} {}

			/* destructor */
			inline ~benchmark(void) noexcept = default;



			// -- public methods --------------------------------------------------

			template <typename F, typename... A>
			auto run(const xns::string_view& msg, F&& func, A&&... args) -> void {


				cycle_type count = 0;

				constexpr xns::size_t max = xns::limits::max<xns::size_t>();

				time_type start = xns::time::now();

				// hide cursor
				xns::print(xns::escape::hide_cursor());

				while (((xns::time::now() - start) < TIME_NANO) && (count < max)) {
					func(xns::forward<A>(args)...);
					xns::print(++count, " operations\r");
					xns::out::render();
					++count;
				}
				// show cursor
				xns::println(xns::escape::show_cursor());
				xns::out::render();


				time_type end = xns::time::now();

				data_t data{};
				data._msg = msg;
				data._time = (end - start) / 1'000'000;
				data._cycle = count;
				data._average = (end - start) / count;

				_benchs.insert(data);

			}


			auto result(const xns::string_view& msg) -> void {

				xns::println("\n\x1b[34m", msg, "\x1b[0m");

				auto it = _benchs.in_order_begin();

				xns::size_t i = 0;

				average_type prev = 0;


				if (it) {
					const auto& data = *it;
					xns::println(data._msg, " -> ", data._cycle, " cycles in ",
							data._time, " ms", " [AVG ", data._average, " ns]");
					prev = data._average;
					++it; ++i;
				}

				while (it) {
					const auto& data = *it;
						if (i == _benchs.size() - 1)
							xns::print("\x1b[32m");

						double faster = prev / static_cast<double>(data._average);

						xns::println(data._msg, " -> ", data._cycle, " cycles in ",
								data._time, " ms", " [AVG ", data._average, " ns] ", "(", faster, "x) FASTER");

					prev = data._average;
					++it;
					++i;
				}

				xns::println("\x1b[0m");
				xns::out::render();
				_benchs.clear();
			}


		private:



			// -- private types -----------------------------------------------

			/* time */
			using time_type = typename xns::time::size_type;

			/* cycle type */
			using cycle_type = xns::size_t;

			/* average type */
			using average_type = xns::size_t;

			/* msg type */
			using msg_type = xns::string_view;


			// -- private constants -------------------------------------------

			/* time in nanoseconds */
			inline static constexpr time_type TIME_NANO = TIME_SEC * 1'000'000'000;


			// -- private structs ---------------------------------------------

			struct data_t final {

				using self = data_t;

				msg_type _msg;
				time_type _time;
				cycle_type _cycle;
				average_type _average;

				// INFO:
				// operator are inverted because reverse iterator is not implemented

				inline auto operator==(const self& other) const noexcept -> bool {
					return _average == other._average;
				}

				inline auto operator!=(const self& other) const noexcept -> bool {
					return _average != other._average;
				}

				inline auto operator<(const self& other) const noexcept -> bool {
					return _average > other._average;
				}

				inline auto operator>(const self& other) const noexcept -> bool {
					return _average < other._average;
				}

				inline auto operator<=(const self& other) const noexcept -> bool {
					return _average >= other._average;
				}

				inline auto operator>=(const self& other) const noexcept -> bool {
					return _average <= other._average;
				}

			};


			// -- private members -------------------------------------------------

			/* benchmarks infos */
			xns::tree<data_t> _benchs;

	};

}

#endif // BENCHMARK_HEADER
