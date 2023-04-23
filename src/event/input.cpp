#include "input.hpp"
// tmp includes
#include "window.hpp"


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

Xf::Input::Readed Xf::Input::_readed                = 0;
Xf::Input::Char   Xf::Input::_buff[BUFFER_SIZE + 1] = { 0 };
Xf::String<char> Xf::Input::_input                 = "";
bool              Xf::Input::_is_running            = false;


// -- S T A T I C  P U B L I C  M E T H O D S ---------------------------------

/* input loop */
void Xf::Input::start_loop(void) {

	// get event instance
	Xf::Event& evnt = Xf::Event::instance();

	// activate requested mode
	evnt.next_mode();

	// exit if there is no active mode
	if (!evnt.is_mode()) { return; std::cout << "no mode" << std::endl; }

	Xf::Term::instance().raw_terminal();
	//Xf::Escape::draw<Xf::enter_screen_t>();
	Xf::Escape::enter_screen();
	//Buffer::render();
	Xf::Output::render();




	// set running flag
	_is_running = true;
	// loop over reading
	while (_is_running) {
		//Xf::Debug::write("loop\n");
		// activate requested mode
		evnt.next_mode();
		std::cout << "PIPI" << std::endl;

		//Xf::Escape::draw<Xf::erase_screen_t>();
		Xf::Escape::erase_screen();
		//sleep(1);
		//Xf::WindowManager::draw_all();
		//Buffer::render();
		Xf::Output::render();
		//Xf::WindowManager::debug_window();


		evnt.call_event(Xf::Evntype::LOOP);


		//Buffer::render();
		Xf::Output::render();

		// read stdin
		read_input();
		// filter input
		filter_extended();
		// analyze readed bytes
		dispatch();
		Xf::Debug::write("--------------------\n");
	}

	//Xf::Escape::draw<Xf::erase_screen_t>();
	Xf::Escape::erase_screen();
	//Xf::Escape::draw<Xf::exit_screen_t>();
	Xf::Escape::exit_screen();
	//Buffer::render();
	Xf::Output::render();
	Xf::Term::instance().restore_terminal();
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
			Xf::Term::instance().raw_terminal(VFlag::NON_BLOCKING);
			// read stdin again
			while (read_stdin() > 0) {
				// append buffer to the string
				_input.append(_buff, _readed);
			}

			// back to blocking read
			Xf::Term::instance().raw_terminal(VFlag::BLOCKING);
		}

	}
}

/* read stdin */
SInt64 Xf::Input::read_stdin(void) {
	// read bytes from stdin
	_readed = read(STDIN_FILENO, _buff, BUFFER_SIZE);
	// append null terminator
	_buff[_readed] = '\0';
	// return number of readed bytes
	return _readed;
}

/* filter extended ascii codes */
void Xf::Input::filter_extended(void) {
	_input.filter(Xf::String<char>::is_multibyte, false);

	// loop over input
	//for (Size x = 0; x < _input.length(); ++x) {
	//	// check if input is superiour to 0x7f (127)
	//	//if (::String::is_multibyte(_input[x])) {
	//		// remove charater
	//	 //   _input.erase(x, 1); }
	//}
}

/* filter control characters */
void Xf::Input::filter_control(void) {
	_input.filter(Xf::String<char>::is_control, false);
	// loop over input
	//for (Size x = 0; x < _input.length(); ++x) {
	//	// check if input is in control range
	//	//if (::String::is_control(_input[x])) {
	//		// remove charater
	//	 //   _input.erase(x, 1); }
	//}
}

void Xf::Input::dispatch(void) {

	// get event instance
	Xf::Event& evnt = Xf::Event::instance();

	using Ev = Xf::Evntype;


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
		const UInt8 _char = _input[0];
		evnt.call_event(static_cast<Ev>(_char));
	}
	filter_control();
	if (_input.empty()) { return; }
	evnt.call_input(_input);
}


