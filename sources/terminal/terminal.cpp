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


static auto get_attr(void) -> xns::terminal::attribute {
	xns::terminal::attribute attr;
	attr.get();
	return attr;
}

// -- C O N S T R U C T O R S -------------------------------------------------

/* private default constructor */
xns::terminal::terminal(void)
: _origin{get_attr()}, _raw{_origin},
  _width{0u}, _height{0u} {

	// setup raw terminal settings
	_raw.raw();

	// query terminal size
	___self::_query_terminal_size();

	// set resize signal handler
	std::signal(SIGWINCH, &terminal::_resize_handler);
}

/* destructor */
xns::terminal::~terminal(void) noexcept {
	// restore terminal settings if raw
	_origin.set(TCSANOW); // here need to noexcept !
}



/* flush stdin buffer */
void xns::terminal::flush(void) {
	// [TCIFLUSH] flushes data received but not read.
	::tcflush(STDIN_FILENO, TCIFLUSH);
}

auto xns::terminal::raw(const VFlag vmin) -> void {

	// get instance
	auto& ___ins = self::shared();

	// VMIN = Minimum number of characters to read
	___ins._raw.min_read(static_cast<xns::ubyte>(vmin));

	// set raw terminal settings
	___ins._raw.set(TCSANOW);
}

/* restore */
auto xns::terminal::restore(void) -> void {
	// restore terminal settings
	___self::shared()._origin.set(TCSANOW);
}


/* query terminal size */
auto xns::terminal::_query_terminal_size(void) noexcept -> void {

	// winsize structure
	struct ::winsize win;

	// query terminal dimensions
	int err = ::ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

	// check error
	if (err == -1)
		return;

	// assign result
	_width = win.ws_col;
	_height = win.ws_row;
}

/* terminal resize handler */
auto xns::terminal::_resize_handler(const int) noexcept -> void {

	// query terminal size
	___self::shared()._query_terminal_size();
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





