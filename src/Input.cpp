#include "Input.hpp"


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

SInt64      Xf::Input::_readed                = 0;
char        Xf::Input::_buff[BUFFER_SIZE + 1] = { 0 };
std::string Xf::Input::_input                 = "";
bool        Xf::Input::_is_running            = false;


// -- S T A T I C  P U B L I C  M E T H O D S ---------------------------------

void Xf::Input::get_event(void) {
	// reset string
	_input.clear();
	// read stdin
	if (read_stdin() > 0) {
		// append buffer to the string
		_input.append(_buff, _readed);
		// buffer is full, loop over reading
		if (_readed == BUFFER_SIZE) {
			// set to non-blocking read
			Term::setRaw(VFlag::NON_BLOCKING);
			// read stdin again
			while (read_stdin() > 0) {
				// append buffer to the string
				_input.append(_buff, _readed);
			} // back to blocking read
			Term::setRaw(VFlag::BLOCKING);
		} // analyze readed bytes
		//processInput();
	}
}

/* input loop */
void Xf::Input::start_loop(void) {
	// set running flag
	_is_running = true;
	// loop over reading
	while (_is_running) {
		// read stdin
		get_event();
		// analyze readed bytes
		process_input();
	}
}

/* stop input loop */
void Xf::Input::stop_loop(void) {
	// unset running flag
	_is_running = false;
}


// -- S T A T I C  P R I V A T E  M E T H O D S -------------------------------

/* read stdin */
SInt64 Xf::Input::read_stdin(void) {
	// read bytes from stdin
	_readed = read(STDIN_FILENO, _buff, BUFFER_SIZE);
	// append null terminator
	_buff[_readed] = '\0';
	// return number of readed bytes
	return _readed;
}





void Xf::Input::process_input(void) {

	// get event instance
	Xf::Event& evnt = Xf::Event::instance();

	using Ev = Xf::Evntype;

	if (_input.length() == 3) {

		// check escape sequence
		if (_input[0] == 0x1b) {
			// check ctrl sequence
			if (_input[1] == 0x5b) {
				// check arrow sequence
				switch (_input[2]) {
					case 'A': // code for arrow up
						evnt.call_event(Ev::UP);
						break;
					case 'B': // code for arrow down
						evnt.call_event(Ev::DOWN);
						break;
					case 'C': // code for arrow right
						evnt.call_event(Ev::RIGHT);
						break;
					case 'D': // code for arrow left
						evnt.call_event(Ev::LEFT);
						break;
					default:
						break;
				}
			}
		}

	}
	else if (_input.length() == 1) {

		switch (_input[0]) {
			case 0x1b:
				evnt.call_event(Ev::ESCAPE);
				break;
			case 0x0a:
				evnt.call_event(Ev::ENTER);
				break;
			case 0x7f:
				evnt.call_event(Ev::BACKSPACE);
				break;
			case 0x09:
				evnt.call_event(Ev::TAB);
				break;
			case 0x0d:
				evnt.call_event(Ev::RETURN);
				break;
			default:
				evnt.call_input(_input);
				break;
		}
	}
}

