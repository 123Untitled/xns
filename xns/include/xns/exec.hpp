#ifndef EXEC_HEADER
#define EXEC_HEADER

#include <unistd.h>
#include <iostream>
#include <string>
#include <list>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>

#include "types.hpp"

class Exec {
	private:
	// typedef and alias
	template<class T>
	using List = std::list<T>;
	typedef std::string String;

	// static
	static List<String>	_paths;
	static List<String> setupPaths(void);

	// private attributs
	const char*			_execPath;
	void getExecPath(const char* exec);
	const char* readOutput(void);


	public:
	Exec(const char* exec);
	Exec(void)						= delete;
	Exec(const Exec&)				= delete;
	Exec& operator=(const Exec&)	= delete;

	const char* execution(const char** args);
	void simpleExecution(const char** args, char** env);
	~Exec(void);
};



#endif
