#include "terminal.hpp"

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


// -- S I N G L E T O N  I N S T A N C E --------------------------------------

/* singleton instance */
Xf::Term Xf::Term::_instance{};


// -- C O N S T R U C T O R S -------------------------------------------------

/* private default constructor */
Xf::Term::Term(void)
:	_is_raw{false}, _is_origin{false}, _is_setup{false},
	_origin{setup_terminal()}, _raw{},
 	_width{0}, _height{0} {

	// check if original terminal settings are available
	if (_is_origin) {
		// copy original terminal settings
		_raw = _origin;
		// setup raw terminal settings
		setup_raw();
		// set setup flag
		_is_setup = true;
	}

	// query terminal size
	query_terminal_size();

	// set resize signal handler
	std::signal(SIGWINCH, &Term::terminal_resize_handler);
}

/* destructor */
Xf::Term::~Term(void) {
	// restore terminal settings if raw
	if (_is_raw) { restore_terminal(); }
}


// -- M E T H O D S -----------------------------------------------------------

/* get singleton instance */
Xf::Term& Xf::Term::instance(void) {
	// return singleton instance
	return _instance;
}

/* get terminal settings */
const Xf::Term::Termios Xf::Term::setup_terminal(void) {

	// termios structure
	Termios origin;

	// get current terminal settings
	if (!tcgetattr(STDIN_FILENO, &origin)) {
		// if no error, set bool flag
		_is_origin = true;
	}

	// return by value original terminal setup
	return origin;
}

/* setup raw terminal */
void Xf::Term::setup_raw(void) {

	// setup new terminal structure
	_raw.c_iflag &= ~(	IXON		// disable Ctrl-S and Ctrl-Q
					|	ICRNL);		// disable Ctrl-M
	_raw.c_lflag &= ~(	ECHO		// disable echo
					|	ICANON		// non-canonical mode
					|	ISIG		// disable Ctrl-C and Ctrl-Z
					|	IEXTEN);	// disable Ctrl-V and Ctrl-O
	_raw.c_cc[VTIME] = 0;
}


/* flush stdin buffer */
void Xf::Term::flush(void) {
	// [TCIFLUSH] flushes data received but not read.
	tcflush(STDIN_FILENO, TCIFLUSH);
}

void Xf::Term::raw_terminal(const VFlag vmin) {

	// check if terminal is setup
	if (!_is_setup) { return; }

	// VMIN = Minimum number of characters to read
	_raw.c_cc[VMIN] = static_cast<UInt8>(vmin);

	// set non-canonical mode
	if (!tcsetattr(STDIN_FILENO, TCSANOW, &_raw)) {
		_is_raw = true;
	}
}

void Xf::Term::restore_terminal(void) {

	// check if terminal is setup
	if (!_is_setup) { return; }

	// reset orignal terminal settings
	if (!tcsetattr(STDIN_FILENO, TCSAFLUSH, &_origin)) {
		_is_raw = false;
	}
}


void Xf::Term::get_terminal_size(Wsize& width, Wsize& height) {
	// assign reference parameters
	width  = _instance._width;
	height = _instance._height;
}

/* query terminal size */
int Xf::Term::query_terminal_size(void) {

	// winsize structure
	Winsize win;

	// query terminal dimensions
	int err = ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

	// check error
	if (err != -1) {
		// assign result to reference parameters
		_instance._width = win.ws_col;
		_instance._height = win.ws_row;
	}
	// error return
	return err;

}

void Xf::Term::terminal_resize_handler(int signum) {
	static_cast<void>(signum);
	// query terminal size
	if (query_terminal_size() != -1) {
		// call resize event subscribers
		Xf::Event::instance().call_event(Xf::Evntype::TERMINAL_RESIZE);
	}
}




/* ------------------------------------------------------- */
	/*
	// returns the process group ID of the foreground process group on the terminal associated to fd,
	// which must be the controlling terminal of the calling process.
	{
		const pid_t tcgid = tcgetpgrp(STDOUT_FILENO);
		if (tcgid == -1) {
			perror("stdout not original tty !");
			return (EXIT_FAILURE);
		}
		std::cout << "stdout terminal control current process id: " << tcgid << std::endl;
	}
	{
		const pid_t tcgid = tcgetpgrp(STDIN_FILENO);
		if (tcgid == -1) {
			perror("stdin not original tty !");
			return (EXIT_FAILURE);
		}
		std::cout << "stdin terminal control current process id: " << tcgid << std::endl;
	}
	{
		const pid_t tcgid = tcgetpgrp(STDERR_FILENO);
		if (tcgid == -1) {
			perror("stderr is not original tty !");
			return (EXIT_FAILURE);
		}
		std::cout << "stderr terminal control current process id: " << tcgid << std::endl;
	}*/

void Xf::Term::get_process_info(void) {
	// get the current process ID
	const pid_t pid = getpid();
	std::cout << "current process id: " << pid << std::endl;
	// get the parent process ID
	const pid_t ppid = getppid();
	std::cout << "parent process id: " << ppid << std::endl;


	// get the current process real group ID
	const gid_t gid = getgid();
	std::cout << "current process real group id: " << gid << std::endl;
	// get the current process effective group ID
	const gid_t egid = getegid();
	std::cout << "current process effective group id: " << egid << std::endl;


	// get the current process real user ID
	const uid_t uid = getuid();
	std::cout << "current process real user id: " << uid << std::endl;
	// returns the current process effective user ID
	const uid_t euid = geteuid();
	std::cout << "current process effective user id: " << euid << std::endl;


	// returns the PGID of the process specified by pid.
	const pid_t pgid = getpgid(ppid);
	std::cout << "parent PGID: " << pgid << std::endl;

	// returns the PGID of the current process
	const pid_t cgid = getpgrp();
	std::cout << "current PGID: " << cgid << std::endl;
}


int Xf::Term::check_control_term(void) {

	//char term[L_ctermid];
	//char *ptr;

	const char* tty = ctermid(nullptr);

	const int fd = open(tty, O_RDWR);

	constexpr int fds[3] { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO };

	constexpr const char* descriptor[3] = {
		"stdin", "stdout", "stderr" };

	// get the calling process ID
	const pid_t pid = getpid();
	// get the current process session ID
	const pid_t sid = getsid(pid);
	// get the process group ID of the session
	// for which the terminal specified by fildes is the controlling terminal.
	//const pid_t cid = tcgetsid(STDOUT_FILENO);

	int status = 0;

	for (UInt x : { 0, 1, 2 }) {
		if (!isatty(fds[x])) {
			status = -1;
			dprintf(fd, "[%s] is not a tty.\n", descriptor[x]);
			continue;
		}
		if (sid != tcgetsid(fds[x])) {
			status = -1;
			dprintf(fd, "[%s] is not the controlling terminal.\n", descriptor[x]);
		}
		//dprintf(fd, "sid: %d, tcsid: %d\n", sid, tcgetsid(fds[x]));
	}

	close(fd);
	return (status);

	//std::cout << "terminal control session id: " << npid << std::endl;
	//std::cout << "current pid: " << pid << std::endl;
	//std::cout << "current process session id: " << sid << std::endl;

}




/*
int ttyConfig(void) {

	if (!isatty(STDIN_FILENO)) {
		write(STDERR_FILENO, "stdin is not a tty.", 19);
		return (-1);
	}
	if (!isatty(STDOUT_FILENO)) {
		write(STDERR_FILENO, "stdout is not a tty.", 19);
		return (-1);
	}

	char ttyIn[PATH_MAX + 1];
	char ttyOut[PATH_MAX + 1];

	ttyname_r(STDIN_FILENO, ttyIn, PATH_MAX);

	ttyname_r(STDOUT_FILENO, ttyOut, PATH_MAX);

	int ttyInFd = open(ttyIn, O_RDWR);

	int ttyOutFd = open(ttyOut, O_RDWR);

	write(ttyOutFd, ttyOut, strlen(ttyOut));
	write(ttyOutFd, "\n", 1);
	write(ttyOutFd, ttyIn, strlen(ttyIn));
	write(ttyOutFd, "\n", 1);

	std::cout << "fdin: " << ttyInFd << std::endl;
	std::cout << "fdout: " << ttyOutFd << std::endl;
	char c = 0;
	//read(ttyInFd, &c, 1);

	tcflush(ttyInFd, TCIFLUSH);

	close(ttyInFd);
	close(ttyOutFd);

	return 0;


}*/





