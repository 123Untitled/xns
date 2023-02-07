#include "Term.hpp"

Term::Termios		Term::_raw;
const Term::Termios Term::_origin	= Term::setupTerm();
constinit bool		Term::_israw	= false;
constinit bool		Term::_isready	= false;


void Term::staticDestructor(void) {
	if (_israw) {
		Term::setOrigin();
	}
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


TermSizeObserver::TermSizeObserver(void) {
	Term::subscript(this);
	std::cout << "call constructor TermSizeObserver" << std::endl;
}

TermSizeObserver::~TermSizeObserver(void) { }

std::list<TermSizeObserver*> Term::_observers;




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

void Term::get_process_info(void) {
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
// session ID
// group ID
// process ID
// thread ID


int Term::check_control_term(void) {

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





