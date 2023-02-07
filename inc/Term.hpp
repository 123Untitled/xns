#ifndef TERM_HEADER
#define TERM_HEADER

#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdlib>
#include <list>
#include <csignal>
#include <fcntl.h>

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


/* forwared declaration */
class TermSizeObserver;


// -- T E R M  C L A S S ------------------------------------------------------

class Term {


	public:

		// -- C O N S T R U C T O R S -----------------------------------------

		/* non-instanceable class */
		NON_INSTANCIABLE(Term);


		// -- P U B L I C  M E T H O D S --------------------------------------

		/* check_control_term */
		static int check_control_term(void);

		/* get_process_info */
		static void get_process_info(void);

		static void subscript(TermSizeObserver* obs);

		static void setRaw(const VFlag vmin = VFlag::BLOCKING);
		static void setOrigin(void);
		static void flush(void);
		static int getTermSize(UInt32* w, UInt32* h);


	private:

		// -- P R I V A T E  A L I A S E S ------------------------------------

		/* Winsize */
		using Winsize = struct winsize;

		/* Termios */
		using Termios = struct termios;


		// -- P R I V A T E  M E M B E R S ------------------------------------

		// original terminal settings
		static const Termios	_origin;

		// raw terminal settings
		static Termios			_raw;

		// raw flag
		static constinit bool	_israw;

		static constinit bool	_isready;


		// -- P R I V A T E  M E T H O D S ------------------------------------

		static const Termios setupTerm(void);
		static void setupRaw(const Termios& origin);
		static void staticDestructor(void);

		static void signalHandlerTermSize(int signum);



		static std::list<TermSizeObserver*> _observers;

		// observers subscription
		static void callObservers(void);


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

