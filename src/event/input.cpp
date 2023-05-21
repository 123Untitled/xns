#include "input.hpp"


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

Xf::Input::signed_type Xf::Input::_readed                = 0;
Xf::Input::CharT  Xf::Input::_buff[BUFFER_SIZE + 1] = { 0 };
xns::cstring       Xf::Input::_input                 = "";
bool              Xf::Input::_is_running            = false;

bool              Xf::Input::_windowed              = false;


// -- S T A T I C  P U B L I C  M E T H O D S ---------------------------------

/* parameters */
void Xf::Input::parameters(const bool windowed) {
	// set windowed mode
	_windowed = windowed;
}

/* input loop */
void Xf::Input::start_loop(void) {

	// get event instance
	Xf::Event& evnt = Xf::Event::instance();

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

		evnt.call_event(Xf::Evntype::LOOP);

		// read stdin
		read_input();
		// analyze readed bytes
		dispatch();
	}

}

/* stop input loop */
void Xf::Input::stop_loop(void) {
	// unset running flag
	_is_running = false;
}


// -- S T A T I C  P R I V A T E  M E T H O D S -------------------------------

/* read input while available */
void Xf::Input::read_input(void) {

	// reset previous readed bytes
	_input.clear();

	// read stdin
	if (read_stdin() > 0) {

		// append buffer to the string
		_input.append(_buff, _readed);

		// buffer is full, loop over reading
		if (_readed == BUFFER_SIZE) {
			// set to non-blocking read
			xns::terminal::raw_terminal(xns::VFlag::NON_BLOCKING);
			// read stdin again
			while (read_stdin() > 0) {
				// append buffer to the string
				_input.append(_buff, _readed);
			}

			// back to blocking read
			xns::terminal::raw_terminal(xns::VFlag::BLOCKING);
		}

	}
}

/* read stdin */
Xf::Input::signed_type Xf::Input::read_stdin(void) {
	// read bytes from stdin
	_readed = read(STDIN_FILENO, _buff, BUFFER_SIZE);
	// append null terminator
	_buff[_readed] = '\0';
	// return number of readed bytes
	return _readed;
}


void Xf::Input::dispatch(void) {

	if (_input.empty()) { return; }

	// get event instance
	Xf::Event& evnt = Xf::Event::instance();

	using Ev = Xf::Evntype;

	// filter extended ascii codes
	_input.filter(xns::cstring::is_multibyte, false);


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
		const xns::ubyte _char = _input[0];
		evnt.call_event(static_cast<Ev>(_char));
	}

	// filter control characters
	_input.filter(xns::cstring::is_control, false);

	evnt.call_input(_input);
}


