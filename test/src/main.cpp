#include "unit_tests.hpp"


#include <array>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <stack>
#include <any>
#include <algorithm>
#include <numeric>

#include <cxxabi.h>
#include <dlfcn.h>
#include <execinfo.h>


#include "network.hpp"
#include "poller.hpp"
#include "socket.hpp"
#include "input.hpp"
#include "terminal.hpp"
#include "link.hpp"
#include "environment.hpp"

void start(void);


int main(const int ac, const char** av, const char** env) {


	// start main function
	try { UT::launcher(); }
	// catch memory errors
	catch (const xns::exception& except) {
		// write error message to stdout
		write(1, "\x1b[31mexcept has been thrown\x1b[0m\n", 34);
		// return failure
		return EXIT_FAILURE;
	} // else return success
	return EXIT_SUCCESS;

}



void start(void) {


	//xns::camera cam;
	//auto& specs = cam.get_specs();
	//specs.fov();
	//xns::projection proj;
	//proj.update(specs);



	//std::cout << "nano: " << xns::nano::numerator() << " / " << xns::nano::denominator() << std::endl;
	//std::cout << "micro: " << xns::micro::numerator() << " / " << xns::micro::denominator() << std::endl;


	//struct timespec tv;
	//clockid_t clk_id = CLOCK_REALTIME;

	//int res = clock_gettime(clk_id, &tv);

	//time_t t = tv.tv_sec;
	//struct tm* ptm = localtime(&t);

	//xns::out::write("clock_gettime: ");
	//xns::out::write(ptm->tm_hour);
	//xns::out::write(" ");
	//xns::out::write(ptm->tm_min);
	//xns::out::write(" ");
	//xns::out::write(ptm->tm_sec);
	//xns::out::write("\n");
	//xns::out::render();

}





