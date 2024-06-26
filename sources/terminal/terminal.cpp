/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#include "xns/terminal/terminal.hpp"

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



// -- C O N S T R U C T O R S -------------------------------------------------

/* private default constructor */
xns::terminal::terminal(void)
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
	std::signal(SIGWINCH, &terminal::terminal_resize_handler);
}

/* destructor */
xns::terminal::~terminal(void) noexcept {
	// restore terminal settings if raw
	if (_is_raw == false)
		return;
	restore();
}


// -- M E T H O D S -----------------------------------------------------------


/* get terminal settings */
auto xns::terminal::setup_terminal(void) -> const struct termios {

	// termios structure
	struct termios origin;

	// get current terminal settings
	if (::tcgetattr(STDIN_FILENO, &origin) != 0)
		return origin;

	// if no error, set bool flag
	_is_origin = true;
	// return by value original terminal setup
	return origin;
}

/* setup raw terminal */
auto xns::terminal::setup_raw(void) -> void {

	// get flag type
	using iflag = decltype(_raw.c_iflag);
	using lflag = decltype(_raw.c_lflag);


	// setup new terminal structure
	_raw.c_iflag &= ~static_cast<iflag>(  IXON   // disable Ctrl-S and Ctrl-Q
										| ICRNL  // disable Ctrl-M
	);

	_raw.c_lflag &= ~static_cast<lflag>(  ECHO   // disable echo
										| ICANON // non-canonical mode
										| ISIG   // disable Ctrl-C and Ctrl-Z
										| IEXTEN // disable Ctrl-V and Ctrl-O
	);

	_raw.c_cc[VTIME] = 0;
}


/* flush stdin buffer */
void xns::terminal::flush(void) {
	// [TCIFLUSH] flushes data received but not read.
	::tcflush(STDIN_FILENO, TCIFLUSH);
}

auto xns::terminal::raw(const VFlag vmin) -> void {

	// get instance
	auto& instance = self::shared();

	// check if terminal is setup
	if (instance._is_setup == false) { return; }

	// VMIN = Minimum number of characters to read
	instance._raw.c_cc[VMIN] = static_cast<xns::ubyte>(vmin);

	// set non-canonical mode
	if (::tcsetattr(STDIN_FILENO, TCSANOW, &instance._raw) != 0)
		return;

	instance._is_raw = true;
}

auto xns::terminal::restore(void) -> void {
	// get instance
	auto& instance = self::shared();
	// check if terminal is setup
	if (instance._is_setup == false) { return; }
	// reset orignal terminal settings
	if (::tcsetattr(STDIN_FILENO, TCSAFLUSH, &instance._origin) != 0)
		return;
	instance._is_raw = false;
}



/* query terminal size */
int xns::terminal::query_terminal_size(void) {

	// winsize structure
	struct winsize win;

	// query terminal dimensions
	int err = ::ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

	// check error
	if (err != -1) {
		// assign result to reference parameters
		_width = win.ws_col;
		_height = win.ws_row;
	}
	// error return
	return err;

}

void xns::terminal::terminal_resize_handler(int signum) {
	// get instance
	auto& instance = self::shared();
	static_cast<void>(signum);
	// query terminal size
	if (instance.query_terminal_size() != 0)
		return;
	// call resize event subscribers
	//xns::event::shared().call_event(xns::evntype::TERMINAL_RESIZE);
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

void xns::terminal::get_process_info(void) {
	// get the current process ID
	const pid_t pid = ::getpid();
	xns::println("current process id: ", pid);
	// get the parent process ID
	const pid_t ppid = ::getppid();
	xns::println("parent process id: ", ppid);


	// get the current process real group ID
	const gid_t gid = ::getgid();
	xns::println("current process real group id: ", gid);
	// get the current process effective group ID
	const gid_t egid = ::getegid();
	xns::println("current process effective group id: ", egid);


	// get the current process real user ID
	const uid_t uid = ::getuid();
	xns::println("current process real user id: ", uid);
	// returns the current process effective user ID
	const uid_t euid = ::geteuid();
	xns::println("current process effective user id: ", euid);


	// returns the PGID of the process specified by pid.
	const pid_t pgid = ::getpgid(ppid);
	xns::println("parent process group id: ", pgid);

	// returns the PGID of the current process
	const pid_t cgid = ::getpgrp();
	xns::println("current process group id: ", cgid);
}


int xns::terminal::check_control_term(void) {

	//char term[L_ctermid];
	//char *ptr;

	const char* tty = ::ctermid(nullptr);

	const int fd = ::open(tty, O_RDWR);

	constexpr int fds[3] { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO };

	constexpr const char* descriptor[3] = {
		"stdin", "stdout", "stderr" };

	// get the calling process ID
	const pid_t pid = ::getpid();
	// get the current process session ID
	const pid_t sid = ::getsid(pid);
	// get the process group ID of the session
	// for which the terminal specified by fildes is the controlling terminal.
	//const pid_t cid = tcgetsid(STDOUT_FILENO);

	int status = 0;

	for (xns::size_t x : { 0U, 1U, 2U }) {
		if (not ::isatty(fds[x])) {
			status = -1;
			dprintf(fd, "[%s] is not a tty.\n", descriptor[x]);
			continue;
		}
		if (sid != ::tcgetsid(fds[x])) {
			status = -1;
			dprintf(fd, "[%s] is not the controlling terminal.\n", descriptor[x]);
		}
		//dprintf(fd, "sid: %d, tcsid: %d\n", sid, tcgetsid(fds[x]));
	}

	::close(fd);
	return status;

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





