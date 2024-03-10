#include "fragmentation.hpp"


auto exponential_contrast(xns::f64 value, xns::f64 min, xns::f64 max) -> xns::f64 {
	auto center = (min + max) / 2.0;
	auto diff = max - min;
	auto x = value - center;
	auto y = x / diff;
	return y * y;
}


auto xns::fragmentation::display(const xns::vector<void*>& addrs) -> void {
	xns::fragmentation{addrs};
}


xns::fragmentation::fragmentation(const xns::vector<void*>& addrs)
:	_addrs{addrs},
	_width{xns::terminal::width()},
	_min_avg{xns::limits<size_type>::max()},
	_max_avg{0} {

	// avg vector
	xns::vector<size_type> avgs;
	avgs.reserve(_width);

	auto it = divisor_iterator<size_type>{addrs.size(), _width};
	xns::vector<void*>::size_type i = 0;

	// loop over divisors
	for (; it; ++it) {

		// get number of elements
		auto n = *it;

		size_type sum = 0;
		// sum addresses
		for (size_type j = 0; j < n; ++j) {
			auto addr = reinterpret_cast<size_type>(_addrs[i]);
			sum += addr;
			++i;
		}

		// compute average
		size_type avg = sum / n;

		// get min and max addresses
		_min_avg = xns::min(avg, _min_avg);
		_max_avg = xns::max(avg, _max_avg);
		avgs.push_back(avg);
	}

	// loop over averages
	for (auto& avg : avgs) {

		xns::f64 addr = static_cast<xns::f64>(     avg - _min_avg)
					  / static_cast<xns::f64>(_max_avg - _min_avg);

		// print color
		xns::print(xns::escape::rgb_color(xns::lch_to_rgb(
			xns::remap(addr, 0.0, 1.0, 20.0,   80.0), // luma
			xns::remap(addr, 0.0, 1.0, 20.0,   40.0), // chroma
			xns::remap(addr, 0.0, 1.0, 280.0, 340.0)  // hue
		), false), ' ');
	}
	xns::println(xns::escape::reset_style());
	xns::out::render();



	// -- compute differences ---------------------------------------------------

	xns::vector<size_type> diffs;

	size_type min_diff = xns::limits<size_type>::max();
	size_type max_diff = 0;


	for (i = 0; i < avgs.size(); ++i) {

		if (i == avgs.size() - 1) {
			auto diff = xns::diff(avgs[i], avgs[i - 1]);
			// get min and max differences
			min_diff = xns::min(diff, min_diff);
			max_diff = xns::max(diff, max_diff);
			diffs.push_back(diff);
		}
		else {
			auto diff = xns::diff(avgs[i], avgs[i + 1]);
			// get min and max differences
			min_diff = xns::min(diff, min_diff);
			max_diff = xns::max(diff, max_diff);
			diffs.push_back(diff);
		}
	}

	// loop over differences
	for (auto& d : diffs) {

		xns::f64 diff = static_cast<xns::f64>(d);

		// print color
		xns::print(xns::escape::rgb_color(xns::lch_to_rgb(
			xns::remap(diff, (xns::f64)min_diff, (xns::f64)max_diff, 25.0,   80.0), // luma
			xns::remap(diff, (xns::f64)min_diff, (xns::f64)max_diff, 10.0,   10.0), // chroma
			xns::remap(diff, (xns::f64)min_diff, (xns::f64)max_diff, 300.0, 300.0)  // hue
		), false), ' ');
	}

	xns::println(xns::escape::reset_style());
	xns::out::render();

}




	//xns::addr_t max_diff = 0;
	//size_type error = 0, nc = 0, sum_diff = 0;
	//size_type prev = 0;



		//
		//	// iterate over tree (in-order traversal)
		//	for (auto it = begin(); it; ++it) {
		//
		//		auto addr = it.address();
		//
		//		if (nc > 0) {
		//			const size_type diff = addr > prev ? addr - prev : prev - addr;
		//			sum_diff += (diff > sizeof(node_type)) ? diff : 0;
		//		}
		//
		//		prev = addr;
		//		// sum node addresses
		//		sum_rise += addr;
		//
		//		++nc;
		//		error += width;
		//
		//		if (error >= _size) {
		//			// compute average
		//			//std::cout << "nc: " << nc << std::endl;
		//			const size_type avg_diff = nc > 0 ? sum_diff / (nc - 1) : 0;
		//			const size_type avg_rise = sum_rise / nc;
		//			//std::cout << "diff: " << avg_diff << " rise: " << avg_rise << std::endl;
		//			// get min and max node addresses
		//			min = min == 0 || avg_rise < min ? avg_rise : min;
		//			max = max == 0 || avg_rise > max ? avg_rise : max;
		//			max_diff = max_diff == 0 || avg_diff > max_diff ? avg_diff : max_diff;
		//			// push average to vector
		//			vec.push_back(xns::array{avg_diff, avg_rise});
		//			// reset sum and counter
		//			sum_rise = 0;
		//			sum_diff = 0;
		//			nc = 0;
		//			error -= _size;
		//		}
		//	}
		//}
		//
		//for (auto& addr : vec) {
		//	xns::println("diff [", addr[0], "] addr[", addr[1] - min, ']');
		//}

		//const xns::f64 max_diff = static_cast<xns::f64>(max_diff);


		//xns::println(xns::escape::reset_style());

		//for (auto& addr : vec) {
		//
		//	xns::f64 diff = static_cast<xns::f64>(addr[0]);
		//
		//	const xns::f64 luma = xns::remap(diff, 0.0, (double)max_diff, 45.0, 80.0);
		//
		//	xns::print(xns::escape::rgb_color(xns::lch_to_rgb(luma, 0.0, 0.0), false), ' ');
		//}




