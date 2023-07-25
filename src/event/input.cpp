#include "input.hpp"


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

/* readed bytes */
//xns::input::signed_type xns::input::_readed{0};
//
///* buffer */
//xns::input::char_t xns::input::_buff[BUFFER_SIZE + 1]{'\0'};
//
///* input string */
//xns::input::string xns::input::_input{""};
//
///* running flag */
//bool xns::input::_is_running{false};
//
///* windowed mode */
//bool xns::input::_windowed{false};
//
//
//// -- S T A T I C  P U B L I C  M E T H O D S ---------------------------------
//
///* parameters */
//void xns::input::parameters(const bool windowed) {
//	// set windowed mode
//	_windowed = windowed;
//}
//
///* input loop */
//void xns::input::start_loop(void) {
//
//	// get event instance
//	xns::event& evnt = xns::event::instance();
//
//	// activate requested mode
//	//evnt.next_mode();
//
//	// exit if there is no active mode
//	//if (!evnt.is_mode()) { return; std::cout << "no mode" << std::endl; }
//
//	// set running flag
//	_is_running = true;
//	// loop over reading
//	while (_is_running) {
//		// activate requested mode
//		evnt.next_mode();
//
//		evnt.call_event(xns::evntype::LOOP);
//
//		// read stdin
//		read_input();
//		// analyze readed bytes
//		dispatch();
//	}
//
//}
//
///* stop input loop */
//void xns::input::stop_loop(void) {
//	// unset running flag
//	_is_running = false;
//}
//
//
//// -- S T A T I C  P R I V A T E  M E T H O D S -------------------------------
//
///* read input while available */
//void xns::input::read_input(void) {
//
//	// reset previous readed bytes
//	_input.clear();
//
//	// read stdin
//	if (read_stdin() > 0) {
//
//		// append buffer to the string
//		_input.append(_buff, static_cast<size_type>(_readed));
//
//		// buffer is full, loop over reading
//		if (_readed == BUFFER_SIZE) {
//			// set to non-blocking read
//			//xns::terminal::raw_terminal(xns::VFlag::NON_BLOCKING);
//			// read stdin again
//			while (read_stdin() > 0) {
//				// append buffer to the string
//				_input.append(_buff, static_cast<size_type>(_readed));
//			}
//			// WARNING: not tested with only blocking read
//			// back to blocking read
//			//xns::terminal::raw_terminal(xns::VFlag::BLOCKING);
//		}
//
//	}
//}
//
///* read stdin */
//xns::input::signed_type xns::input::read_stdin(void) {
//	// read bytes from stdin
//	_readed = read(STDIN_FILENO, _buff, BUFFER_SIZE);
//	// append null terminator
//	_buff[_readed] = '\0';
//	// return number of readed bytes
//	return _readed;
//}
//
//
//void xns::input::dispatch(void) {
//
//	if (_input.empty()) { return; }
//
//	// get event instance
//	xns::event& evnt = xns::event::instance();
//
//	using Ev = xns::evntype;
//
//	// filter extended ascii codes
//	_input.filter(xns::string::is_multibyte, false);
//
//
//	if (_input.length() == 3 && _input[0] == 0x1b) {
//
//		// check ctrl sequence
//		if (_input[1] == 0x5b) {
//			// check arrow sequence
//			switch (_input[2]) {
//				case 'A': // code for arrow up
//					evnt.call_event(Ev::UP);
//					return;
//				case 'B': // code for arrow down
//					evnt.call_event(Ev::DOWN);
//					return;
//				case 'C': // code for arrow right
//					evnt.call_event(Ev::RIGHT);
//					return;
//				case 'D': // code for arrow left
//					evnt.call_event(Ev::LEFT);
//					return;
//				default:
//					break;
//			}
//		}
//	}
//
//	if (_input.length() == 1) {
//		const xns::ubyte _char = (xns::ubyte)_input[0]; // NEED TO FIX CONVERSION
//		evnt.call_event(static_cast<Ev>(_char));
//	}
//
//	// filter control characters
//	_input.filter(xns::string::is_control, false);
//
//	evnt.call_input(_input);
//}
//
//
