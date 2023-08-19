#include "unit_tests.hpp"
#include "bit_view.hpp"
#include "string.hpp"
#include "terminal.hpp"

#include <string>
#include <sys/socket.h>

template <>
bool UT::unit_tests<"bit_view">(void) {

	xns::terminal::raw_terminal();

	/*
	char ll = 1;
	xns::bit_view bv0{ll};

	if (bv0.get<0>() != 1) {
		std::cout << "): bit_view: get<0> failed! :(\n";
		return false;
	}
	return true;
	*/



	unsigned short a = 0;
	xns::bit_view bv{a};

	char c = '\0';
	while (c != 'q') {

		read(0, &c, 1);

		if (c == 's') {
			read(0, &c, 1);
			if (c < '0' || c > '7') { continue; }

			switch (c) {
				case '0': bv.set<0>(); break;
				case '1': bv.set<1>(); break;
				case '2': bv.set<2>(); break;
				case '3': bv.set<3>(); break;
				case '4': bv.set<4>(); break;
				case '5': bv.set<5>(); break;
				case '6': bv.set<6>(); break;
				case '7': bv.set<7>(); break;
				default: continue;
			}

			std::cout << "\r\x1b[0K";
			bv.print();


		}
		else if (c == 't') {
			read(0, &c, 1);
			if (c < '0' || c > '7') { continue; }

			switch (c) {
				case '0': bv.toggle<0>(); break;
				case '1': bv.toggle<1>(); break;
				case '2': bv.toggle<2>(); break;
				case '3': bv.toggle<3>(); break;
				case '4': bv.toggle<4>(); break;
				case '5': bv.toggle<5>(); break;
				case '6': bv.toggle<6>(); break;
				case '7': bv.toggle<7>(); break;
				default: continue;
			}

			std::cout << "\r\x1b[0K";
			bv.print();
		}
		else if (c == 'g') {
			read(0, &c, 1);
			if (c < '0' || c > '7') { continue; }

			int bit = 0;

			switch (c) {
				case '0': bit = bv.get<0>(); break;
				case '1': bit = bv.get<1>(); break;
				case '2': bit = bv.get<2>(); break;
				case '3': bit = bv.get<3>(); break;
				case '4': bit = bv.get<4>(); break;
				case '5': bit = bv.get<5>(); break;
				case '6': bit = bv.get<6>(); break;
				case '7': bit = bv.get<7>(); break;
				default: continue;
			}

			std::cout << "\r\x1b[0K";
			std::cout << bit << std::endl;

		}
		else if (c == 'r') {

			read(0, &c, 1);
			if (c < '0' || c > '7') { continue; }

			switch (c) {
				case '0': bv.reset<0>(); break;
				case '1': bv.reset<1>(); break;
				case '2': bv.reset<2>(); break;
				case '3': bv.reset<3>(); break;
				case '4': bv.reset<4>(); break;
				case '5': bv.reset<5>(); break;
				case '6': bv.reset<6>(); break;
				case '7': bv.reset<7>(); break;
				default: continue;
			}

			std::cout << "\r\x1b[0K";
			bv.print();

		}


	}


	xns::terminal::restore_terminal();


	return true;
}

int main(void) {

	UT::unit_tests<"bit_view">();

	return 0;


}

