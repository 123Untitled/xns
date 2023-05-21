#include "event.hpp"


// -- P R I V A T E  C O N S T R U C T O R S ----------------------------------

/* default constructor */
Xf::Event::Event(void)
: _modes{ }, _current{ }, _next{ }, _stack{ } {
	// code here...
}

/* destructor */
Xf::Event::~Event(void) {
	// code here...
}


// -- S T A T I C  M E T H O D S ----------------------------------------------

/* get singleton instance */
Xf::Event& Xf::Event::instance(void) {
	// return instance
	return _instance;
}


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

/* singleton instance */
Xf::Event Xf::Event::_instance;


// -- P U B L I C  M E T H O D S ----------------------------------------------

/* add mode */
Xf::Evntmode Xf::Event::new_mode(void) {
	_modes.emplace_back(Mode{ });
	Xf::Debug::print("new mode: %d\n", _modes.length() - 1);
	if (_modes.empty()) {
		// error
		Evntmode mode{0};
		mode._state = false;
		return mode;
	}
	return Evntmode{_modes.length() - 1};
}

/* remove mode */
void Xf::Event::remove_mode(Evntmode& mode) {
	// check if index is valid
	if (!mode._state) { return; }
	// invalid index
	mode._state = false;
	//_modes.erase(mode._idx); WARNING: erase not implemented
}

/* set mode */
void Xf::Event::set_mode(const Evntmode& mode, const Evntopt opt) {
	// check if index is valid
	if (mode._state) {
		// check if mode is forced
		if (opt == Evntopt::FORCE) {
			// stack current mode
			_current = xns::make_unique_pointer<Size>(mode._idx);
			//_current.make(mode._idx);
			return;
		} // set next mode
		_next = xns::make_unique_pointer<Size>(mode._idx);
		//_next.make(mode._idx);
	}
}

/* apply mode */
void Xf::Event::next_mode(void) {
	//Xf::Debug::print("active mode: %d\n", *_current);
	// check if there is a mode query
	if (!_next) { return; }
	// mode to current mode
	_current = xns::move(_next);

	// get subscribers index by event type
	EventVector& subscribers = _modes[*_current]._second[IDX(Evntype::BEGIN)];
	// loop through all observers
	for (Size x = 0; x < subscribers.length(); ++x) {
		// call subscriber
		subscribers[x].call();
	}
}

/* is mode active */
bool Xf::Event::is_mode(void) const {
	// check if there is a current mode
	return _current ? true : false;
}

/* is mode active */
bool Xf::Event::is_mode(const Evntmode& mode) const {
	// check if there is a current mode and mode is valid
	if (!_current || !mode._state) { return false; }
	// check if mode is active
	return *_current == mode._idx ? true : false;
}

/* stack current mode */
void Xf::Event::stack_mode(void) {
	// check if there is a current mode
	if (!_current) { return; }
	// stack current mode
	_stack.emplace(*_current);
}

/* stack mode */
void Xf::Event::stack_mode(const Evntmode& mode, const Evntopt opt) {
	//std::cout << "   stack mode" << std::endl;
	// check if mode is valid
	if (!mode._state) { return; }
	// stack mode
	_stack.emplace(mode._idx);
	// check if mode is forced
	if (opt == Evntopt::FORCE) {
		// set next mode
		_current = xns::make_unique_pointer<Size>(mode._idx);
		//_current.make(mode._idx);
		return;
	} // set next mode
	_next = xns::make_unique_pointer<Size>(mode._idx);
	//_next.make(mode._idx);
}

/* unstack mode */
void Xf::Event::unstack_mode(void) {
	// check if there is a mode to unstack
	if (_stack.empty()) {
		Xf::Input::stop_loop();
		return; }
	// unstack mode
	//_next.make(*_stack.top());


	Xf::Debug::print("unstack mode: %d\n", _stack.top());
	/////////////
	_stack.pop();
	// maybe better to pop and set new top mode ???
	if (_stack.empty()) {
		Xf::Input::stop_loop();
		return;
	}
	//_next.make(*_stack.top());
	//_next.make(_stack.top());
	_next = xns::make_unique_pointer<Size>(_stack.top());
	_current = xns::move(_next);
	//////////////

	// remove mode from stack
	//_stack.pop();
}



/* call all event subscribers */
void Xf::Event::call_event(const Evntype type) {
	// exit if no current mode or invalid event type
	if (!_current || type >= Evntype::EVNT_MAX) { return; }
	// get subscribers index by event type
	EventVector& subscribers = _modes[*_current]._second[IDX(type)];
	// loop through all observers
	for (Size x = 0; x < subscribers.length(); ++x) {
		// call subscriber
		subscribers[x].call();
	}
}

/* call all input subscribers */
void Xf::Event::call_input(const xns::cstring& input) {
	// exit if no current mode
	if (!_current) { return; }
	// get subscribers
	InputVector& subscribers = _modes[*_current]._first;
	// loop through all observers
	for (Size x = 0; x < subscribers.length(); ++x) {
		// call subscriber
		subscribers[x].call(input);
	}
}


// -- P R I V A T E  M E T H O D S --------------------------------------------

/* subscribe function to event */
void Xf::Event::_subscribe(const Evntmode& mode, const Evntype type, EventFunction function) {
	// check invalid pointers and event type
	if (!function || type >= Evntype::EVNT_MAX) { return; }
	// get event subscriber vector
	EventVector& subscribers = _modes[mode._idx]._second[IDX(type)];
	// add new subscriber
	subscribers.emplace_back(function);
}

/* subscribe function to input */
void Xf::Event::_subscribe(const Evntmode& mode, InputFunction function) {
	// check invalid pointers
	if (!function) { return; }
	// get input subscriber vector
	InputVector& subscribers = _modes[mode._idx]._first;
	// add new subscriber
	subscribers.emplace_back(function);
}






//     _______  ________  ________  ________  ________  ________   _______  ________
//   ╱╱       ╲╱    ╱   ╲╱    ╱   ╲╱        ╲╱        ╲╱        ╲_╱       ╲╱        ╲
//  ╱╱        ╱         ╱         ╱        _╱         ╱         ╱         ╱         ╱
// ╱        _╱╲        ╱         ╱╱       ╱╱         ╱         ╱         ╱        _╱
// ╲________╱  ╲______╱╲__╱_____╱ ╲______╱ ╲__╱__╱__╱╲________╱╲________╱╲________╱


/* index private constructor */
Xf::Evntmode::Evntmode(const Size idx)
: _idx{idx}, _state{true} {
	// code here...
}

/* destructor */
Xf::Evntmode::~Evntmode(void) {
	// check if mode is active
	if (_state) {
		Xf::Debug::write("EVNTMODE: destructor called\n");
		// remove mode from event manager
		Xf::Event::instance().remove_mode(*this);
	}
}

/* move constructor */
Xf::Evntmode::Evntmode(Evntmode&& other) noexcept
: _idx{other._idx}, _state{other._state} {
	// invalidate other
	other._state = false;
}

/* move assignment operator */
Xf::Evntmode& Xf::Evntmode::operator=(Evntmode&& other) noexcept {
	// check for self-assignment
	if (this != &other) {
		// move other
		_idx   = other._idx;
		_state = other._state;
		// invalidate other
		other._state = false;
	} // return self reference
	return *this;
}


// -- P U B L I C  M E T H O D S ----------------------------------------------

/* subscribe function to event */
void Xf::Evntmode::subscribe(const Evntype type, Event::EventFunction function) {
	// check if mode is active
	if (_state) {
		// subscribe to event
		Xf::Event::instance()._subscribe(*this, type, function);
	}
}

/* subscribe function to input */
void Xf::Evntmode::subscribe(Event::InputFunction function) {
	// check if mode is active
	if (_state) {
		// subscribe to input
		Xf::Event::instance()._subscribe(*this, function);
	}
}




