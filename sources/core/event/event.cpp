#include "event.hpp"


// -- P R I V A T E  C O N S T R U C T O R S ----------------------------------

/* default constructor */
xns::event::event(void)
: _modes{}, _current{}, _next{} {}



// -- S T A T I C  M E T H O D S ----------------------------------------------

/* get singleton instance */
xns::event& xns::event::shared(void) {
	static self instance;
	return instance;
}


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

///* singleton instance */
//xns::event xns::event::_instance;


// -- P U B L I C  M E T H O D S ----------------------------------------------

/* add mode */
auto xns::event::new_mode(void) -> evntmode {
	_modes.emplace_back(mode{});
	return evntmode{_modes.size() - 1};
}

/* remove mode */
auto xns::event::remove_mode(evntmode& md) -> void {
	// check if index is valid
	if (not md._state) { return; }
	// invalid index
	md._state = false;
	// remove mode
	_modes.erase(md._idx);
}

/* set mode */
auto xns::event::set_mode(const evntmode& md, const evntopt opt) -> void {
	// check if index is valid
	if (not md._state) { return; }
	// check if mode is forced
	if (opt == evntopt::FORCE) {
		// stack current mode
		_current = &md._idx;
		return;
	} // set next mode
	_next = &md._idx;
}

/* apply mode */
auto xns::event::next_mode(void) -> void {
	// check if there is a mode query
	if (!_next) { return; }
	// mode to current mode
	_current = xns::move(_next);

	// get subscribers index by event type
	event_vector& subscribers = xns::get<1>(_modes[*_current])[
		xns::evntype::BEGIN
	];
	// loop through all observers
	for (xns::size_t x = 0; x < subscribers.size(); ++x) {
		// call subscriber
		subscribers[x].call();
	}
}

/* has mode active */
auto xns::event::has_mode(void) const -> bool {
	// check if there is a current mode
	return _current ? true : false;
}

/* is mode active */
auto xns::event::is_mode(const evntmode& md) const -> bool {
	// check if there is a current mode and mode is valid
	if (!_current || !md._state) { return false; }
	// check if mode is active
	return *_current == md._idx ? true : false;
}



/* call all event subscribers */
void xns::event::call_event(const xns::evntype type) {
	// exit if no current mode or invalid event type
	if (!_current || type >= xns::evntype::EVNT_MAX) { return; }
	// get subscribers index by event type
	event_vector& subscribers = xns::get<1>(_modes[*_current])[type];
	// loop through all observers
	for (auto& subscriber : subscribers) {
		// call subscriber
		subscriber.call();
	}
}

/* call all input subscribers */
void xns::event::call_input(const xns::string& input) {
	// exit if no current mode
	if (!_current) { return; }
	// get subscribers
	input_vector& subscribers = xns::get<0>(_modes[*_current]);
	// loop through all observers
	for (auto& subscriber : subscribers) {
		// call subscriber
		subscriber.call(input);
	}
}


// -- P R I V A T E  M E T H O D S --------------------------------------------

/* subscribe function to event */
void xns::event::_subscribe(const evntmode& md, const xns::evntype type, event_function function) {
	// check invalid pointers and event type
	if (not function || type >= xns::evntype::EVNT_MAX)
		return;
	// get event subscriber vector
	event_vector& subscribers = xns::get<1>(_modes[md._idx])[type];
	// add new subscriber
	subscribers.emplace_back(function);
}

/* subscribe function to input */
void xns::event::_subscribe(const evntmode& md, input_function function) {
	// check invalid pointers
	if (not function) 
		return;
	// get input subscriber vector
	input_vector& subscribers = xns::get<0>(_modes[md._idx]);//._first;
	// add new subscriber
	subscribers.emplace_back(function);
}







/* index private constructor */
xns::evntmode::evntmode(const xns::size_t idx)
: _idx{idx}, _state{true} {}

/* destructor */
xns::evntmode::~evntmode(void) {
	// check if mode is active
	if (_state) {
		// remove mode from event manager
		xns::event::shared().remove_mode(*this);
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
		xns::event::shared()._subscribe(*this, type, function);
	}
}

/* subscribe function to input */
void xns::evntmode::subscribe(event::input_function function) {
	// check if mode is active
	if (_state) {
		// subscribe to input
		xns::event::shared()._subscribe(*this, function);
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
	xns::event& evnt = xns::event::shared();

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
			// read stdin again
			while (read_stdin() > 0) {
				// append buffer to the string
				_input.append(_buff, static_cast<size_type>(_readed));
			}
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
	xns::event& evnt = xns::event::shared();

	using ev = xns::evntype;


	// filter extended ascii codes
	_input.filter<false>(xns::is_multi);


	if (_input.length() == 3 && _input[0] == 0x1b) {

		// check ctrl sequence
		if (_input[1] == 0x5b) {
			// check arrow sequence
			switch (_input[2]) {
				case 'A': // code for arrow up
					evnt.call_event(ev::UP);
					return;
				case 'B': // code for arrow down
					evnt.call_event(ev::DOWN);
					return;
				case 'C': // code for arrow right
					evnt.call_event(ev::RIGHT);
					return;
				case 'D': // code for arrow left
					evnt.call_event(ev::LEFT);
					return;
				default:
					break;
			}
		}
	}

	if (_input.length() == 1) {
		const xns::ubyte _char = (xns::ubyte)_input[0]; // NEED TO FIX CONVERSION
		evnt.call_event(static_cast<ev>(_char));
	}

	// filter control characters
	_input.filter<false>(xns::is_cntrl);

	evnt.call_input(_input);
}


