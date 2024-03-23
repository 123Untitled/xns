#include "unit_tests.hpp"
#include "xns/network/poller.hpp"
#include "xns/network/socket.hpp"
#include "xns/network/network.hpp"


/* unit test */

auto unit_tests_poller(void) -> int {

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

	poller.stop();





	return 0;
	xns::network::port port{8080};

	auto sock = xns::network::make_socket<xns::network::ipv4, xns::stream>();

	xns::network::ipv4_address addr{xns::string_view{"127.0.0.1"}, port};

	xns::network::bind(sock, addr);

	xns::network::listen(sock, 1);


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
	//sock2.accept();
	// code here...
	return 0;
}

#if defined(XNS_TEST_POLLER)
int main(void) {
	return unit_tests_poller();
}
#endif


