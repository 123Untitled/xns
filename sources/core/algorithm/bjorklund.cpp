#include "bjorklund.hpp"

/* argument constructor */
xns::bjorklund::bjorklund(const size_type step, const size_type pulse) noexcept
: _step{step}, _pulse{pulse}, _front{nullptr}, _back{nullptr} {}

inline xns::bjorklund::node::node(const size_type data) noexcept
: _data{data}, _up{nullptr}, _last{this} {}


auto xns::bjorklund::node::push(node_ptr node) noexcept -> void {
	_last->_up = node;
	_last = node->_last;
}

auto xns::bjorklund::compute(size_type& f, size_type& b) noexcept -> void {
	(f > b) ? f -= (b = f - b) : b -= (f != 0 ? f : b);
	for (size_type i = 0; i < f; ++i)
		_front[i].push(_back + i);
}

auto xns::bjorklund::generate(const size_type step, const size_type pulse) -> xns::vector<size_type> {
	return xns::bjorklund{step, pulse}.generate_impl();
}

auto xns::bjorklund::generate_impl(void) -> xns::vector<size_type> {

	if (_step == 0 || _pulse > _step) { return {}; }

	// -- allocation ----------------------------------------------------------

	// vector to store sequence
	xns::vector<size_type> seq;
	seq.reserve(_step);

	// node allocation
	_front = allocator::allocate(_step);

	for (size_type i = 0; i < _pulse; ++i)
		allocator::construct(_front + i, 1U);
	for (size_type i = _pulse; i < _step; ++i)
		allocator::construct(_front + i, 0U);

	// -- algorithm -----------------------------------------------------------

	size_type f = _pulse;
	size_type b = _step - _pulse;

	// loop until back sequence is 1
	while (b > 1) {
		_back = _front + f;
		while (b > f) {
			compute(f, b);
			_back += f;
		} compute(f, b);
	}

	f += b;

	// retrieve sequence to fill vector
	for (size_type i = 0; i < f; ++i) {
		// loop over subsequence
		for (auto sub = _front + i; sub; sub = sub->_up)
			seq.push_back(sub->_data);
	}

	// deallocate nodes
	allocator::deallocate(_front);

	return seq;






	//xns::vector<void*> addrs[2];
	//addrs[0].reserve(_step);
	//for (size_type i = 0; i < _step; ++i)
	//	addrs[0].push_back(_front + i);

			//addrs[1].push_back(sub);
	for (auto n : seq)
		std::cout << (n ? "x" : "-");
	std::cout << std::endl;
	//xns::fragmentation::display(addrs[0]);
	//xns::fragmentation::display(addrs[1]);

}




//void xns::bjorklund::generate(void) {
//
//	if (_step == 0) { return; }
//
//	// -- allocation ----------------------------------------------------------
//
//	// node allocation
//	node_ptr head = allocator::allocate(_step);
//	// assign first back node
//	node_ptr tail = &(head[_pulse]);
//	//node_ptr tail = &(head[_step - 1]);
//
//	xns::vector<void*> addrs0;
//	for (size_type i = 0; i < _step; ++i)
//		addrs0.push_back((void*)&(head[i]));
//
//	xns::fragmentation::display(addrs0);
//
//	// initialize first node
//	allocator::construct(head, 1U);
//	// initialize front sequence
//	for (size_type i = 1; i < _pulse; ++i)
//		allocator::construct(head + i, 1U, &(head[i - 1]));
//	// initialize back sequence
//	for (size_type i = _pulse; i < _step; ++i)
//		allocator::construct(head + i, 0U, &(head[i - 1]));
//
//
//
//	// -- algorithm -----------------------------------------------------------
//
//	size_type f = _pulse;
//	size_type b = _step - _pulse;
//		// node iterator
//		node_ptr elm = head;
//
//	// loop until back sequence is 1
//	while (b > 1) {
//		std::cout << "\x1b[32mloop\x1b[0m" << std::endl;
//
//		std::cout << "f: " << f << " b: " << b << std::endl;
//		// check if front is greater than back or back is greater than front
//		(f > b) ? f -= (b = f - b) : b -= (f != 0 ? f : b);
//
//		elm = head;
//		//tail->_prev->_next = nullptr;
//		// loop until front is reached
//		for (size_type i = 0; i < f; ++i) {
//			std::cout << "\x1b[31mloop\x1b[0m" << std::endl;
//			// move tail to end of subsequence
//			elm->_last->_up = tail;
//			// set new end of subsequence
//			elm->_last = tail->_last;
//			if (tail->_last->_up) {
//				std::cout << "UP NOT NULL" << std::endl;
//				throw std::runtime_error("UP NOT NULL");
//			}
//			//elm->_last->_up = nullptr;
//			// retrieve new tail
//		tail = tail->_next;
//
//				//tail = tail->_prev;
//			// initialize new tail
//			//tail->_next = nullptr;
//			//tail->_prev = nullptr;
//			// move to next node
//			elm = elm->_next;
//		}
//		
//		tail = elm;
//	}
//
//	elm->_next = nullptr;
//
//	std::cout << "\x1b[32mend\x1b[0m" << std::endl;
//	std::cout << "f: " << f << " b: " << b << std::endl;
//
//	//return;
//
//	xns::vector<size_type> seq;
//	seq.reserve(_step);
//
//	xns::vector<void*> addrs;
//	seq.reserve(_step);
//
//	int y = 0;
//	// retrieve sequence to fill vector
//	for (node_ptr node = head; node; node = node->_next) {
//		//std::cout << "[" << y << "], " << std::flush;
//		int x = 0;
//		// loop over subsequence
//		for (auto sub = node; sub; sub = sub->_up) {
//			std::cout << "(" << sub->_data << "), " << std::flush;
//			seq.push_back(sub->_data);
//			addrs.push_back((void*)sub);
//			++x;
//		}
//		std::cout << std::endl;
//		++y;
//	}
//	std::cout << std::endl;
//
//	// deallocate nodes
//	allocator::deallocate(head);
//
//	std::cout << "step: " << _step << std::endl;
//	std::cout << "pulse: " << _pulse << std::endl;
//
//	for (auto n : seq)
//		std::cout << n;
//	std::cout << std::endl;
//
//	//xns::fragmentation::display(addrs);
//}



	//while (b > 1) {
	//
	//	// check if front is greater than back or back is greater than front
	//	(f > b) ? f -= (b = f - b) : b -= (f != 0 ? f : b);
	//
	//	// node iterator
	//	node_ptr elm = head;
	//	// loop until front is reached
	//	for (size_type i = 0; i < f; ++i) {
	//		// move tail to end of subsequence
	//		elm->_last->_up = tail;
	//		// set new end of subsequence
	//		elm->_last = tail->_last;
	//		// retrieve new tail
	//		tail = tail->_prev;
	//		// initialize new tail
	//		tail->_next = nullptr;
	//		// move to next node
	//		elm = elm->_next;
	//	}
	//}
