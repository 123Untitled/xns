#include "work_in_progress.hpp"



// -- L O C A L  S T R U C T --------------------------------------------------

xns::address xns::local::make_address(const xns::string_view& path) noexcept {

	address addr{};

	::sockaddr_un* sun = addr.as<sockaddr_un>();

	sun->sun_family = local::value;


	// WARNING: unicode, utf8, etc... string not handled yet.

	::socklen_t x = 0;
	// manually copy path to address
	while (x < path.size()
		&& x < sizeof(sun->sun_path) - 1U) {
		sun->sun_path[x] = path[x];
		++x;
	}
	// null terminate path
	sun->sun_path[x] = '\0';
	// set address size
	addr._size = sizeof(sun->sun_family) + x + 1U;

	return addr;

}

xns::address xns::ipv4::make_address(const xns::string_view& host, const xns::u16 port) noexcept {

	address addr{};


	std::cout << "host: " << host.data() << std::endl;
	::sockaddr_in* sin = addr.as<sockaddr_in>();

	sin->sin_family = ipv4::value;

	sin->sin_port = htons(port);

	int ret = ::inet_pton(ipv4::value, host.data(), &sin->sin_addr);

	if (ret == -1)
		std::cout << "inet_pton: " << ::strerror(errno) << std::endl;
	else if (ret == 0)
		std::cout << "inet_pton: invalid address" << std::endl;


	addr._size = sizeof(sockaddr_in);


	return addr;

}


xns::address xns::ipv6::make_address(const xns::string_view& host, const xns::u16 port) noexcept {

	address addr{};

	::sockaddr_in6* sin6 = addr.as<sockaddr_in6>();

	sin6->sin6_family = ipv6::value;

	sin6->sin6_port = htons(port);

	if (::inet_pton(ipv6::value, host.data(), &sin6->sin6_addr) <= 0) {
		// error
	}

	addr._size = sizeof(sockaddr_in6);

	return addr;

}



