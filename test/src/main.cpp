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

void start(void);

/*void* operator new(std::size_t size) {
	auto ptr = malloc(size);
	if (!ptr)
		throw std::bad_alloc{};
	std::cout << "new: " << size << ", ptr: " << ptr << '\n';

	return ptr;
}*/

#include "observer.hpp"
#include "link.hpp"



class A;
class B;
class C;

class C {
	public:
};


//////////////////////
class A : public xns::link<A, B> {
public:

    ~A(void) {
		std::cout << "A: " << this << " destructor:\n";
		// notify all observers of this class to detach
    }

	/*void update(xns::link<B, A>& p) noexcept override {
		std::cout << "A update:\n";
		xns::link<A, B>::detach(p);
	}*/
};


/////////////////////
class B : public xns::link<B, A> {
public:
    ~B(void) {
		std::cout << "B: " << this << " destructor:\n";
		// notify all observers of this class to detach
		//xns::link<B, A>::notify();
    }
private:
	/*
	void update(xns::link<A, B>& s) noexcept override {
		std::cout << "B update:\n";
		xns::link<B, A>::detach(s);
	}*/
};



void test(void) {

	static_assert(std::derived_from<B, xns::link<B, A>>, "B must be derived from link<B, A>");

}


#include "utilities.hpp"



int main(const int ac, const char** av, const char** env) {

	xns::vector<int> v = xns::make_vector<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	xns::vector<int> v2 = xns::make_copy(v);




	// initialize seed
	std::srand((unsigned)std::time(nullptr));

	xns::vector<int> vvv{};
	for (int i = 0; i < 100; ++i) {
		//vvv.copy_back(std::rand() % 1000);
		vvv.dichotomic_insert(std::rand() % 100000);
	}

	for (auto& i : vvv) {
		std::cout << i << ", ";
	}
	std::cout << std::endl;


	auto it = vvv.dichotomic_search(1000);
	return 0;
	if (it != vvv.end()) {
		std::cout << "found: " << *it << std::endl;
	} else {
		std::cout << "not found" << std::endl;
	}

	return 0;


	xns::network::poller poller;

	xns::network::socket sss[10] {
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
		::socket(AF_INET, SOCK_STREAM, 0),
	};



	for (auto& s : sss) {
		poller.add_socket(s);
	}

	for (auto& s : sss) {
		poller.remove_socket(s);
	}

	return 0;





	return 0;
	xns::network::port port{8080};

	auto sock = xns::network::make_socket<xns::network::ipv4, xns::stream>();

	xns::network::ipv4_address addr{xns::string_view{"127.0.0.1"}, port};

	xns::network::bind(sock, addr);

	xns::network::listen(sock, 1);

	xns::network::session session = xns::network::accept(sock);

	return 0;


	/*
	xns::socket<xns::local, xns::stream> sock{};

	sock.create();
	sock.bind(xns::string_view{"./debug.sock"});
	sock.listen(1);
	sock.accept();
	*/

	xns::socket<xns::ipv4, xns::stream> sock2{};

	sock2.create();
	sock2.bind("127.0.0.1", (unsigned short)8080);
	sock2.listen(1);
	sock2.accept();


	return 0;

	UT::dispatcher<"debug">();
	UT::dispatcher<"tree">();
	UT::dispatcher<"array">();
	UT::dispatcher<"list">();
	UT::dispatcher<"directory">();
	return 0;


	//UT::dispatcher<"make_signed">();
	UT::dispatcher<"is_signed", "make_unsigned">();
	//UT::dispatcher<"make_unsigned">();
	return 0;

	UT::dispatcher<"numeric_limits">();
	//UT::launcher();
	return 0;


	// setup environment
	//xns::env::init(env);
	//// start main function
	//try { start(); }
	//// catch memory errors
	//catch (const xns::exception& except) {
	//	// write error message to stdout
	//	write(1, "\x1b[31mexcept has been thrown\x1b[0m\n", 34);
	//	// return failure
	//	return EXIT_FAILURE;
	//} // else return success
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
	//xns::out::flush();















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





