
#include "string.hpp"

// this program generates a single header file from the source files
// steps:
// get all header files
// get all include directories
// execute clang++ -MM on each header file with include directories
// parse output and format to tsort input
// execute tsort on formatted input
// invert output
// now we have a list of header files in order of inclusion
// parse all header files to get all system header names
// remove duplicates
// write system header names to output file
// parse all header files to get all code inside namespace block
// write code to output file
// done







#include "directory.hpp"
#include "output.hpp"




void headers(const xns::string& path) {


	for (xns::filesystem::recursive_iterator it{path}; it; ++it) {

		xns::output::write(it.path());
		xns::output::newline();

	}
	xns::output::render();


}




#include <fcntl.h>

int main(int ac, char** av, char** env) {

	headers("inc");

	int fd = ::open("xns.hpp", O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if (fd == -1) {
		perror("open");
		return 1;
	}

	::write(fd, "#pragma once\n", 13);

	::close(fd);

	return 0;


	/*
	sh::envp envp{env};


	envp.print();

	sh::str compiler = envp.search("clang++");
	sh::str tsort    = envp.search("tsort");

	compiler.print();
	tsort.print();
	*/

	return 0;
}


