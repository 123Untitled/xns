#include "Exec.hpp"

Exec::Exec(const char* exec)
: _execPath{nullptr} {
	// try different paths to get '_execPath'
	getExecPath(exec);
}

Exec::~Exec(void) {
	// Exec destructor
}

// initialize '_paths' static member variable at start
Exec::List<Exec::String> Exec::_paths = setupPaths();

Exec::List<Exec::String> Exec::setupPaths(void) {
	#define PATH_VARIABLE		"PATH"
	#define DELIMITER			':'
	List<String>				list;
	// get the 'PATH' environment variable content
	const char* paths = std::getenv(PATH_VARIABLE);
	// check paths ptr
	if (paths) {
		// iterate over characters
		for (UInt64 x = 0, len = 0; paths[x]; x += len) {
			// skip delimiter ':'
			while (paths[x] == DELIMITER) x++;
			// initialize path len
			len = 0;
			// count valid characters
			while (paths[x + len]
				&& paths[x + len] != DELIMITER)
				len++;
			// check path len
			if (len) {
				// add new path to the list
				list.push_back(String{&paths[x], len} + String{"/"});
			} } }
	// return path list with right value cast
	return (static_cast<List<String>&&>(list));
}

void Exec::getExecPath(const char* exec) {
	// local static string declaration
	static String	path;
	// be sure '_execPath' is null
	_execPath = nullptr;
	// check exec ptr
	if (exec) {
		// iterate over paths list
		for (auto ite = _paths.begin(); ite != _paths.end(); ite++) {
			// make copy of current path
			path = *ite;
			// append exec name to the path
			path.append(exec, strlen(exec));
			// check if executable exist
			if (!access(path.c_str(), X_OK)) {
				// assign exec path variable
				_execPath = path.c_str();
				std::cout << _execPath << std::endl;
				// exit loop
				return;
			}
		}
	}
}


void Exec::simpleExecution(const char** args, char** env) {

	SInt32 state = 0;
	SInt32 child = fork();

	if (!child) {
		execve(_execPath, const_cast<char*const*>(args), env);
		perror("execve");
		exit(1);
	}
	waitpid(child, &state, 0);
}



const char* Exec::execution(const char** args) {

	SInt32 stdinput = dup(STDIN_FILENO);
	SInt32 state = 0;
	SInt32 tube[2];
	pipe(tube);
	SInt32 child = fork();
	if (!child) {
		dup2(tube[1], STDOUT_FILENO);
		close(tube[0]);
		execve(_execPath, const_cast<char*const*>(args), nullptr);
		//perror("execve");
		exit(1);
	}
	dup2(tube[0], STDIN_FILENO);
	close(tube[1]);
	waitpid(child, &state, 0);


	const char* buff = readOutput();
	if (state) {
		write(STDOUT_FILENO, buff, strlen(buff));
		buff = nullptr;
	}
	dup2(stdinput, STDIN_FILENO);
	close(stdinput);
	return (buff);
}

const char* Exec::readOutput(void) {
	static char		buff[1024];
	static String	output;
	static SInt64	readed;

	output.clear();
	while ((readed = read(0, buff, 1024)) > 0)
		output.append(buff, readed);
	return (output.c_str());
}
