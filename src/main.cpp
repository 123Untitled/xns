#include "unit_tests.hpp"
#include "xns.hpp"

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



#if !defined(XNS_UT)


void start(void);


int main(const int ac, const char** av, const char** env) {

	UT::dispatcher<"list">();
	//UT::dispatcher<"directory">();
	return 0;


	//UT::dispatcher<"make_signed">();
	UT::dispatcher<"is_signed", "make_unsigned">();
	//UT::dispatcher<"make_unsigned">();
	return 0;

	UT::dispatcher<"numeric_limits">();
	//UT::launcher();
	return 0;


	// setup environment
	xns::env::init(env);
	// start main function
	try { start(); }
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


	xns::camera cam;

	auto& specs = cam.get_specs();

	specs.fov();

	xns::projection proj;

	proj.update(specs);





	std::cout << "nano: " << xns::nano::numerator() << " / " << xns::nano::denominator() << std::endl;
	std::cout << "micro: " << xns::micro::numerator() << " / " << xns::micro::denominator() << std::endl;






	struct timespec tv;
	clockid_t clk_id = CLOCK_REALTIME;

	int res = clock_gettime(clk_id, &tv);

	time_t t = tv.tv_sec;
	struct tm* ptm = localtime(&t);

	xns::output::write("clock_gettime: ");
	xns::output::write(ptm->tm_hour);
	xns::output::write(" ");
	xns::output::write(ptm->tm_min);
	xns::output::write(" ");
	xns::output::write(ptm->tm_sec);
	xns::output::write("\n");
	xns::output::render();















	/*
	xns::terminal::raw_terminal();

	using node = xns::tree<char>::node;

	while (true) {
		generate_tree(xns::random::random_gen(30) + 3);
		char c; int r = read(0, &c, 1);
		if (r != 1 || c == 'q') { break; }
	}

	xns::terminal::restore_terminal();
	return EXIT_SUCCESS;
	*/



}
#endif





