#include "event.hpp"


// -- P R I V A T E  C O N S T R U C T O R S ----------------------------------

/* default constructor */
xns::event::event(void)
: _modes{ }, _current{ }, _next{ }, _stack{ } {
	// code here...
}

/* destructor */
xns::event::~event(void) {
	// code here...
}


// -- S T A T I C  M E T H O D S ----------------------------------------------

/* get singleton instance */
xns::event& xns::event::instance(void) {
	// return instance
	return _instance;
}


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

/* singleton instance */
xns::event xns::event::_instance;


// -- P U B L I C  M E T H O D S ----------------------------------------------

/* add mode */
xns::evntmode xns::event::new_mode(void) {
	_modes.emplace_back(mode{ });
	if (_modes.empty()) {
		// error
		evntmode mode{0};
		mode._state = false;
		return mode;
	}
	return evntmode{_modes.size() - 1};
}

/* remove mode */
void xns::event::remove_mode(evntmode& mode) {
	// check if index is valid
	if (!mode._state) { return; }
	// invalid index
	mode._state = false;
	//_modes.erase(mode._idx); WARNING: erase not implemented
}

/* set mode */
void xns::event::set_mode(const evntmode& mode, const evntopt opt) {
	// check if index is valid
	if (mode._state) {
		// check if mode is forced
		if (opt == evntopt::FORCE) {
			// stack current mode
			_current = xns::make_unique<xns::size_t>(mode._idx);
			//_current.make(mode._idx);
			return;
		} // set next mode
		_next = xns::make_unique<xns::size_t>(mode._idx);
		//_next.make(mode._idx);
	}
}

/* apply mode */
void xns::event::next_mode(void) {
	//Xf::Debug::print("active mode: %d\n", *_current);
	// check if there is a mode query
	if (!_next) { return; }
	// mode to current mode
	_current = xns::move(_next);

	// get subscribers index by event type
	event_vector& subscribers = xns::get<1>(_modes[*_current])[IDX(evntype::BEGIN)];//._second[IDX(evntype::BEGIN)];
	// loop through all observers
	for (xns::size_t x = 0; x < subscribers.size(); ++x) {
		// call subscriber
		subscribers[x].call();
	}
}

/* is mode active */
bool xns::event::is_mode(void) const {
	// check if there is a current mode
	return _current ? true : false;
}

/* is mode active */
bool xns::event::is_mode(const evntmode& mode) const {
	// check if there is a current mode and mode is valid
	if (!_current || !mode._state) { return false; }
	// check if mode is active
	return *_current == mode._idx ? true : false;
}

/* stack current mode */
void xns::event::stack_mode(void) {
	// check if there is a current mode
	if (!_current) { return; }
	// stack current mode
	_stack.emplace(*_current);
}

/* stack mode */
void xns::event::stack_mode(const evntmode& mode, const evntopt opt) {
	//std::cout << "   stack mode" << std::endl;
	// check if mode is valid
	if (!mode._state) { return; }
	// stack mode
	_stack.emplace(mode._idx);
	// check if mode is forced
	if (opt == evntopt::FORCE) {
		// set next mode
		_current = xns::make_unique<xns::size_t>(mode._idx);
		//_current.make(mode._idx);
		return;
	} // set next mode
	_next = xns::make_unique<xns::size_t>(mode._idx);
	//_next.make(mode._idx);
}

/* unstack mode */
void xns::event::unstack_mode(void) {
	// check if there is a mode to unstack
	if (_stack.empty()) {
		//xns::input::stop_loop();
		xns::event::stop_loop();
		return; }
	// unstack mode
	//_next.make(*_stack.top());


	/////////////
	_stack.pop();
	// maybe better to pop and set new top mode ???
	if (_stack.empty()) {
		xns::event::stop_loop();
		//xns::input::stop_loop();
		return;
	}
	//_next.make(*_stack.top());
	//_next.make(_stack.top());
	_next = xns::make_unique<xns::size_t>(_stack.top());
	_current = xns::move(_next);
	//////////////

	// remove mode from stack
	//_stack.pop();
}



/* call all event subscribers */
void xns::event::call_event(const evntype type) {
	// exit if no current mode or invalid event type
	if (!_current || type >= evntype::EVNT_MAX) { return; }
	// get subscribers index by event type
	event_vector& subscribers = xns::get<1>(_modes[*_current])[IDX(type)];//._second[IDX(type)];
	// loop through all observers
	for (xns::size_t x = 0; x < subscribers.size(); ++x) {
		// call subscriber
		subscribers[x].call();
	}
}

/* call all input subscribers */
void xns::event::call_input(const xns::string& input) {
	// exit if no current mode
	if (!_current) { return; }
	// get subscribers
	input_vector& subscribers = xns::get<0>(_modes[*_current]);//._first;
	// loop through all observers
	for (xns::size_t x = 0; x < subscribers.size(); ++x) {
		// call subscriber
		subscribers[x].call(input);
	}
}


// -- P R I V A T E  M E T H O D S --------------------------------------------

/* subscribe function to event */
void xns::event::_subscribe(const evntmode& mode, const evntype type, event_function function) {
	// check invalid pointers and event type
	if (!function || type >= evntype::EVNT_MAX) { return; }
	// get event subscriber vector
	event_vector& subscribers = xns::get<1>(_modes[mode._idx])[IDX(type)];//._second[IDX(type)];
	// add new subscriber
	subscribers.emplace_back(function);
}

/* subscribe function to input */
void xns::event::_subscribe(const evntmode& mode, input_function function) {
	// check invalid pointers
	if (!function) { return; }
	// get input subscriber vector
	input_vector& subscribers = xns::get<0>(_modes[mode._idx]);//._first;
	// add new subscriber
	subscribers.emplace_back(function);
}






//     _______  ________  ________  ________  ________  ________   _______  ________
//   ╱╱       ╲╱    ╱   ╲╱    ╱   ╲╱        ╲╱        ╲╱        ╲_╱       ╲╱        ╲
//  ╱╱        ╱         ╱         ╱        _╱         ╱         ╱         ╱         ╱
// ╱        _╱╲        ╱         ╱╱       ╱╱         ╱         ╱         ╱        _╱
// ╲________╱  ╲______╱╲__╱_____╱ ╲______╱ ╲__╱__╱__╱╲________╱╲________╱╲________╱


/* index private constructor */
xns::evntmode::evntmode(const xns::size_t idx)
: _idx{idx}, _state{true} {
	// code here...
}

/* destructor */
xns::evntmode::~evntmode(void) {
	// check if mode is active
	if (_state) {
		// remove mode from event manager
		xns::event::instance().remove_mode(*this);
	}
}

/* move constructor */
xns::evntmode::evntmode(evntmode&& other) noexcept
: _idx{other._idx}, _state{other._state} {
	// invalidate other
	other._state = false;
}

/* move assignment operator */
xns::evntmode& xns::evntmode::operator=(evntmode&& other) noexcept {
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
void xns::evntmode::subscribe(const evntype type, event::event_function function) {
	// check if mode is active
	if (_state) {
		// subscribe to event
		xns::event::instance()._subscribe(*this, type, function);
	}
}

/* subscribe function to input */
void xns::evntmode::subscribe(event::input_function function) {
	// check if mode is active
	if (_state) {
		// subscribe to input
		xns::event::instance()._subscribe(*this, function);
	}
}







// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

/* readed bytes */
xns::event::signed_type xns::event::_readed{0};

/* buffer */
xns::event::char_t xns::event::_buff[BUFFER_SIZE + 1]{'\0'};

/* input string */
xns::event::string xns::event::_input{""};

/* running flag */
bool xns::event::_is_running{false};

/* windowed mode */
bool xns::event::_windowed{false};


// -- S T A T I C  P U B L I C  M E T H O D S ---------------------------------

/* parameters */
void xns::event::parameters(const bool windowed) {
	// set windowed mode
	_windowed = windowed;
}

/* input loop */
void xns::event::start_loop(void) {

	// get event instance
	xns::event& evnt = xns::event::instance();

	// activate requested mode
	//evnt.next_mode();

	// exit if there is no active mode
	//if (!evnt.is_mode()) { return; std::cout << "no mode" << std::endl; }

	// set running flag
	_is_running = true;
	// loop over reading
	while (_is_running) {
		// activate requested mode
		evnt.next_mode();

		evnt.call_event(xns::evntype::LOOP);

		// read stdin
		read_input();
		// analyze readed bytes
		dispatch();
	}

}

/* stop input loop */
void xns::event::stop_loop(void) {
	// unset running flag
	_is_running = false;
}


// -- S T A T I C  P R I V A T E  M E T H O D S -------------------------------

/* read input while available */
void xns::event::read_input(void) {

	// reset previous readed bytes
	_input.clear();

	// read stdin
	if (read_stdin() > 0) {

		// append buffer to the string
		_input.append(_buff, static_cast<size_type>(_readed));

		// buffer is full, loop over reading
		if (_readed == BUFFER_SIZE) {
			// set to non-blocking read
			//xns::terminal::raw_terminal(xns::VFlag::NON_BLOCKING);
			// read stdin again
			while (read_stdin() > 0) {
				// append buffer to the string
				_input.append(_buff, static_cast<size_type>(_readed));
			}
			// WARNING: not tested with only blocking read
			// back to blocking read
			//xns::terminal::raw_terminal(xns::VFlag::BLOCKING);
		}

	}
}

/* read stdin */
xns::event::signed_type xns::event::read_stdin(void) {
	// read bytes from stdin
	_readed = read(STDIN_FILENO, _buff, BUFFER_SIZE);
	// append null terminator
	_buff[_readed] = '\0';
	// return number of readed bytes
	return _readed;
}


void xns::event::dispatch(void) {

	if (_input.empty()) { return; }

	// get event instance
	xns::event& evnt = xns::event::instance();

	using Ev = xns::evntype;

	// filter extended ascii codes
	_input.filter(xns::string::is_multibyte, false);


	if (_input.length() == 3 && _input[0] == 0x1b) {

		// check ctrl sequence
		if (_input[1] == 0x5b) {
			// check arrow sequence
			switch (_input[2]) {
				case 'A': // code for arrow up
					evnt.call_event(Ev::UP);
					return;
				case 'B': // code for arrow down
					evnt.call_event(Ev::DOWN);
					return;
				case 'C': // code for arrow right
					evnt.call_event(Ev::RIGHT);
					return;
				case 'D': // code for arrow left
					evnt.call_event(Ev::LEFT);
					return;
				default:
					break;
			}
		}
	}

	if (_input.length() == 1) {
		const xns::ubyte _char = (xns::ubyte)_input[0]; // NEED TO FIX CONVERSION
		evnt.call_event(static_cast<Ev>(_char));
	}

	// filter control characters
	_input.filter(xns::string::is_control, false);

	evnt.call_input(_input);
}


