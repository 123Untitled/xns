#include "Input.hpp"

SInt64							Input::_readed;
char							Input::_buff[BUFFER_SIZE + 1];
Input::String					Input::_input;
Input::List<Input::Observer*>	Input::_observers[static_cast<UInt64>
												(KeyEvent::EVNT_NBR)];

SInt64 Input::readInput(void) {
	// read bytes from stdin
	_readed = read(STDIN_FILENO, _buff, BUFFER_SIZE);
	// append null terminator
	_buff[_readed] = '\0';
	// return number of readed bytes
	return (_readed);
}

void Input::getEvent(void) {
	// reset string
	_input.clear();
	// read stdin
	if (readInput() > 0) {
		// append buffer to the string
		_input.append(_buff, _readed);
		// buffer is full, loop over reading
		if (_readed == BUFFER_SIZE) {
			// set to non-blocking read
			Term::setRaw(VFlag::NON_BLOCKING);
			// read stdin again
			while (readInput() > 0) {
				// append buffer to the string
				_input.append(_buff, _readed);
			} // back to blocking read
			Term::setRaw(VFlag::BLOCKING);
		} // analyze readed bytes
		processInput();
	}
}

void Input::processArrow(void) {

	switch (_input[2]) {
		case 'A': // code for arrow up
			callObservers(KeyEvent::KEY_UP);
			break;
		case 'B': // code for arrow down
			callObservers(KeyEvent::KEY_DOWN);
			break;
		case 'C': // code for arrow right
			callObservers(KeyEvent::KEY_RIGHT);
			break;
		case 'D': // code for arrow left
			callObservers(KeyEvent::KEY_LEFT);
			break;
		default:
			break;
	}
}

void Input::processEscape(void) {
	if (_input[1] == 0x5b)
		processArrow();
}

void Input::processInput(void) {
	if (_input.length() == 3) {
		if (_input[0] == 0x1b)
			processEscape();
	}
	else if (_input.length() == 1) {
		if (_input[0] == 0x1b)
			callObservers(KeyEvent::KEY_ESCAPE);
	}
}


void Input::subscript(Observer* obs, const KeyEvent key) {
	// add new observer to indexed list by 'key'
	_observers[static_cast<UInt64>(key)].push_back(obs);
}

void Input::callObservers(const KeyEvent key) {
	// indexed list by 'key' iterator declaration
	auto ite = _observers[static_cast<UInt64>(key)].begin();
	// iterate over observer list
	while (ite != _observers[static_cast<UInt64>(key)].end()) {
		// call indexed inherited function by 'key'
		((*ite)->*Observer::_keyfn[static_cast<UInt64>(key)])();
		// move to next observer
		ite++;
	}
}

/////////////////////////////////////////////////// OBSERVER

Input::Observer::Observer(void) {
	// Observer constructor
}

Input::Observer::~Observer(void) {
	// Observer destructor
}

const Input::Observer::Keyfn \
Input::Observer::_keyfn[static_cast<UInt64>(KeyEvent::EVNT_NBR)] = {
	// member functions static array initialization
	&Input::Observer::onKeyUp,
	&Input::Observer::onKeyDown,
	&Input::Observer::onKeyLeft,
	&Input::Observer::onKeyRight,
	&Input::Observer::onKeyEscape,
	&Input::Observer::onKeyEnter,
};




