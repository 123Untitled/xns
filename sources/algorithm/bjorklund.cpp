#include "xns/algorithm/bjorklund.hpp"

/* member constructor */
xns::bjorklund::bjorklund(const size_type step,
						  const size_type pulse,
						  const size_type burst) noexcept
:	_step{step},
	_pulse{pulse > step ? step : pulse},
	_burst{burst ? burst : 1},
	_front{nullptr}, _back{nullptr} {}

/* node default constructor */
inline xns::bjorklund::node::node(void) noexcept
: _data{0}, _up{nullptr}, _last{this} {}

/* node data constructor */
inline xns::bjorklund::node::node(const size_type data) noexcept
: _data{data}, _up{nullptr}, _last{this} {}

/* push */
auto xns::bjorklund::node::push(node_ptr ptr) noexcept -> void {
	_last->_up = ptr;
	_last = ptr->_last;
}

/* compute */
auto xns::bjorklund::compute(size_type& f, size_type& b) noexcept -> void {
	//(f > b) ? f -= (b = f - b) : b -= (f != 0 ? f : b);
	for (size_type i = 0; i < f; ++i) {
		_front[i].push(_back + i);
	}
}

/* generate */
auto xns::bjorklund::generate(const size_type step,
							  const size_type pulse,
							  const size_type burst) -> xns::vector<size_type> {
	return xns::bjorklund{step, pulse, burst}.generate_impl();
}

/* generate bursts */
auto xns::bjorklund::gen_bursts(void) const -> xns::vector<size_type> {
	auto pulse = _pulse;

	xns::vector<size_type> bursts;

	while (pulse > 0) {
		if (_burst > pulse) {
			bursts.push_back(pulse);
			break; }
		bursts.push_back(_burst);
		pulse -= _burst;
	}
	return bursts;
}

auto xns::bjorklund::print(const size_type size) const noexcept -> void {

	for (size_type i = 0; i < size; ++i) {
		std::cout << "[";
		bool state = false;
		for (auto sub = _front + i; sub; sub = sub->_up) {
			if (not state) {
				std::cout << _front[i]._data;
			}
			else {
				std::cout << ", " << _front[i]._data;
			}
		}
		std::cout << "] ";
	}
	std::cout << std::endl;
}


auto xns::bjorklund::generate_impl(void) -> xns::vector<size_type> {

	if (_step == 0) { return {}; }

	// -- allocation ----------------------------------------------------------

	auto bursts = gen_bursts();

	auto sub_step  = (_step - _pulse) + bursts.size();
	auto sub_pulse = bursts.size();

	// node allocation
	allocator a{};
	_front = xns::allocator_traits<allocator>::allocate(a, _step);

	for (size_type i = 0; i < sub_pulse; ++i)
		___lifecycle::construct(_front + i, 1U);
	for (size_type i = sub_pulse; i < sub_step; ++i)
		___lifecycle::construct(_front + i);
	for (size_type i = sub_step; i < _step; ++i)
		___lifecycle::construct(_front + i, 1U);

	size_type i = 0;
	size_type j = sub_step;
	size_type y = 0;

	// loop over bursts
	while (y < bursts.size()) {
		// get burst count
		auto n = bursts[y] - 1;
		// loop over burst count
		for (size_type z = 0; z < n; ++z) {
			_front[i].push(_front + j);
			++j;
		}
		++i;
		++y;
	}


	// -- algorithm -----------------------------------------------------------

	size_type f = sub_pulse;
	size_type b = sub_step - bursts.size();

	// loop until back sequence is 1
	while (b > 1) {
		_back = _front + f;
		while (b > f) {
			b -= f;
			compute(f, b);
			_back += f;
		}
		f -= (b = f - b);
		compute(f, b);
	} f += b;


	xns::vector<size_type> seq;
	seq.reserve(_step);

	// retrieve sequence to fill vector
	for (i = 0U; i < f; ++i) {
		// loop over subsequence
		for (auto sub = _front + i; sub; sub = sub->_up)
			seq.push_back(sub->_data);
	}

	// deallocate nodes
	xns::allocator_traits<allocator>::deallocate(a, _front, _step);

	return seq;
}
