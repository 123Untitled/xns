#include "Term.hpp"

Term::Termios		Term::_raw;
const Term::Termios Term::_origin	= Term::setupTerm();
constinit bool		Term::_israw	= false;
constinit bool		Term::_isready	= false;


void Term::staticDestructor(void) {
	if (_israw)
		Term::setOrigin();
}

const Term::Termios Term::setupTerm(void) {
	// termios struct declaration
	Termios origin;
	// get current terminal setup
	if (!tcgetattr(STDIN_FILENO, &origin)) {
		// if no error, set bool flag
		_isready = true;
		// setup raw terminal settings
		setupRaw(origin);
	} // assign function to execute when program exit
	std::atexit(&staticDestructor);
	std::signal(SIGWINCH, &Term::signalHandlerTermSize);
	// return by value original terminal setup
	return (origin);
}

void Term::setupRaw(const Termios& origin) {
	_raw = origin;
	// setup new terminal structure
	_raw.c_iflag &= ~(	IXON		// disable Ctrl-S and Ctrl-Q
					|	ICRNL);		// disable Ctrl-M
	_raw.c_lflag &= ~(	ECHO		// disable echo
					|	ICANON		// non-canonical mode
					|	ISIG		// disable Ctrl-C and Ctrl-Z
					|	IEXTEN);	// disable Ctrl-V and Ctrl-O
	_raw.c_cc[VTIME] = 0;

}


void Term::flush(void) {
	//	TCIFLUSH flushes data received but not read.
	tcflush(STDIN_FILENO, TCIFLUSH);
}

void Term::setRaw(const VFlag vmin) {
	// VMIN -> Minimum number of characters to read
	_raw.c_cc[VMIN] = static_cast<UInt8>(vmin);
	// set non-canonical mode
	if (!tcsetattr(STDIN_FILENO, TCSANOW, &_raw))
		_israw = true;
}

void Term::setOrigin(void) {
	// reset orignal terminal settings
	if (!tcsetattr(STDIN_FILENO, TCSAFLUSH, &_origin))
		_israw = false;
}


int Term::getTermSize(UInt32* w, UInt32* h) {
	// declare Winsize structure
	Winsize win;
	// query terminal dimensions
	int err = ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	// assign result to size pointers
	if (w) *w = win.ws_col;
	if (h) *h = win.ws_row;
	// error return
	return (err);
}

void Term::signalHandlerTermSize(int signum) {
	callObservers();
}


void Term::subscript(TermSizeObserver* obs) {
	// add new observer to the list
	_observers.push_back(obs);
}

void Term::callObservers(void) {
	UInt32 width = 0, height = 0;

	getTermSize(&width, &height);
	// indexed list by 'key' iterator declaration
	auto ite = _observers.begin();
	// iterate over observer list
	while (ite != _observers.end()) {
		// call indexed inherited function by 'key'
		(*ite)->updateTermSize(width, height);
		// move to next observer
		ite++;
	}
}

#include <iostream>

TermSizeObserver::TermSizeObserver(void) {
	Term::subscript(this);
	std::cout << "call constructor TermSizeObserver" << std::endl;
}

TermSizeObserver::~TermSizeObserver(void) { }

std::list<TermSizeObserver*> Term::_observers;





