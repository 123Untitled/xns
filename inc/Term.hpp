#ifndef _TERM_HPP_
#define _TERM_HPP_

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdlib>
#include <list>
#include <csignal>

#include "Types.hpp"
#include "Macro.hpp"



enum class VFlag : bool {
	NON_BLOCKING	= 0,
	BLOCKING		= 1
};

// TCSANOW
// The change occurs immediately.

// TCSADRAIN
// The change occurs after all output written to fildes has been transmitted to the terminal.
// This value of optional_actions should be used when changing parameters that affect output.

// TCSAFLUSH
// The change occurs after all output written to fildes has been transmitted to the terminal.
// Additionally, any input that has been received but not read is discarded.

// TCSASOFT
// If this value is or'ed into the optional_actions value,
// the values of the c_cflag, c_ispeed, and c_ospeed fields are ignored.

class TermSizeObserver;

class Term {

private:
	// alias type
	using Winsize = struct winsize;
	using Termios = struct termios;
	// original terminal settings
	static const Termios	_origin;
	// raw terminal settings
	static Termios			_raw;
	// raw flag
	static constinit bool	_israw;
	static constinit bool	_isready;


	static const Termios	setupTerm(void);
	static void				setupRaw(const Termios& origin);
	static void				staticDestructor(void);

	static void				signalHandlerTermSize(int signum);


public:
	NON_INSTANCIABLE(Term);

private:
	static std::list<TermSizeObserver*> _observers;
	// observers subscription
	static void callObservers(void);

	static int checkControlTerm(void);
	static void getProcessInfos(void);


public:
	static void subscript(TermSizeObserver* obs);

	static void				setRaw(const VFlag vmin);
	static void				setOrigin(void);
	static void				flush(void);
	static int				getTermSize(UInt32* w, UInt32* h);
};


////////////////
class TermSizeObserver {
private:
	// abstract member functions
	virtual void updateTermSize(UInt32 width, UInt32 height) = 0;
public:
	// default constructor
	TermSizeObserver(void);
	// destructor
	virtual ~TermSizeObserver(void);

	NON_COPYABLE(TermSizeObserver);

	friend class Term;
}; ////////////////////////

#endif

