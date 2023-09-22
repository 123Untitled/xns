#ifndef SOCKET_HEADER
#define SOCKET_HEADER

// local headers
#include "types.hpp"
#include "macros.hpp"
#include "forward.hpp"
#include "is_one_of.hpp"
#include "conditional.hpp"
#include "string.hpp"
#include "safe_enum.hpp"
#include "vector.hpp"

#include "socket.hpp"
#include "address.hpp"


// operating system headers
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// c++ standard headers
#include <cstring>
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- public domain types -------------------------------------------------

	/* address family definition */
	struct family_def {
		// integral type
		using type = xns::u8;
		// enum type
		enum enum_type : type {
			LOCAL = 0,
			IPV4  = 1,
			IPV6  = 2,
			UNDEF = 3,
			MAX
		};
	};

	/* address family type */
	using family_type = xns::safe_enum<family_def>;


	// -- forward declarations ------------------------------------------------

	/* address class */
	class address;

	/* local domain (unix domain) */
	struct local {
		#ifdef __linux__
		static constexpr int value = AF_LOCAL;
		#elif __APPLE__ || __FreeBSD__
		static constexpr int value = PF_LOCAL;
		#endif

		/* family lookup table index */
		static constexpr family_type family = family_type::LOCAL;

		/* make address */
		static address make_address(const xns::string_view&) noexcept;

	};

	/* inet domain (ipv4 domain) */
	struct ipv4 {
		#ifdef __linux__
			static const int value = AF_INET;
		#elif __APPLE__ || __MACH__ || __FreeBSD__
			static const int value = PF_INET;
		#endif
		static constexpr family_type family = family_type::IPV4;

		/* make address */
		static address make_address(const xns::string_view&, const xns::u16) noexcept;
	};

	/* inet6 domain */
	struct ipv6 {
		#ifdef __linux__
			static const int value = AF_INET6;
		#elif __APPLE__ || __MACH__ || __FreeBSD__
			static const int value = PF_INET6;
		#endif
		static constexpr family_type family = family_type::IPV6;

		/* make address */
		static address make_address(const xns::string_view&, const xns::u16) noexcept;
	};


	/* stream type */
	struct stream   { static const int value = SOCK_STREAM; };

	/* datagram type */
	struct datagram { static const int value = SOCK_DGRAM;  };

	/* raw type */
	struct raw      { static const int value = SOCK_RAW;    };



	// -- A D D R E S S  C L A S S --------------------------------------------

	class address {

		// -- friends ---------------------------------------------------------

		/* local as friend */
		friend struct local;

		/* ipv4 as friend */
		friend struct ipv4;

		/* ipv6 as friend */
		friend struct ipv6;



		private:

			// -- private enums -----------------------------------------------



			// -- private types -----------------------------------------------

			/* lookup table type */
			template <class T>
			using lookup = xns::array<T, family_type::size()>;


			// -- private static members --------------------------------------

			/* method table */
			// to be implemented...

			/* family name table */
			static constexpr lookup<xns::string_view> _family_name = {
				"local",
				"ipv4",
				"ipv6",
				"undef"
			};


			// -- private members ---------------------------------------------

			/* address */
			::sockaddr_storage _addr;

			/* address size */
			::socklen_t _size;

			/* address family */
			family_type _family;



		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = address;




			// -- public lifecycle --------------------------------------------

			/* default constructor */
			address(void) noexcept
			: _addr{}, _size{0}, _family{family_type::UNDEF} {}

			/* family constructor */
			explicit address(const family_type family) noexcept
			: _addr{}, _size{0}, _family{family} {

				// set family
				_addr.ss_family = family;

			}

			explicit address(struct ::sockaddr* addr, ::socklen_t size) noexcept
			: _addr{}, _size{size}, _family{family_type::UNDEF} {

			}


			/* copy constructor */
			address(const self& other) noexcept
			: _addr{other._addr}, _size{other._size}, _family{other._family} {}

			/* move constructor */
			address(self&& other) noexcept
			: _addr{xns::move(other._addr)}, _size{other._size}, _family{other._family} {}








			template <class I>
			static family_type domain_to_family(const I& domain) noexcept {
				// require integral type
				static_assert(xns::is_integral<I>, "): INVALID DOMAIN TYPE :(");
				// find family
				switch (domain) {
					case local::value: return family_type::LOCAL;
					case  ipv4::value: return family_type::IPV4;
					case  ipv6::value: return family_type::IPV6;
					default:           return family_type::UNDEF;
				}
			}

			template <class D, class... A>
			static address make_address(A&&... args) noexcept {
				// require domain type
				static_assert(xns::is_one_of<D,
							  local, ipv4, ipv6>, "): INVALID DOMAIN TYPE :(");

				// create address
				return D::make_address(xns::forward<A>(args)...);
			}


			// -- public conversions ------------------------------------------

			/* conversion */
			template <class T>
			auto as(void) noexcept {

				using address_type = xns::remove_cvrp<T>;

				// require sockaddr type
				static_assert(xns::is_one_of<address_type,
						sockaddr, sockaddr_in, sockaddr_in6, sockaddr_un>,
						"): INVALID SOCKADDR TYPE :(");

				return reinterpret_cast<address_type*>(&_addr);

			}

			sockaddr* as_sockaddr(void) noexcept {
				return reinterpret_cast<sockaddr*>(&_addr);
			}

			socklen_t size(void) const noexcept {
				return _size;
			}


			constexpr const xns::string_view& family_name(void) const noexcept {
				return _family_name[_family];
			}



			///* non-assignable class */
			//NON_ASSIGNABLE(address);

			///* destructor */
			//~address(void) noexcept = default;


			//// -- public accessors ------------------------------------

			///* get address */
			//struct sockaddr* get(void) noexcept {
			//	return reinterpret_cast<struct sockaddr*>(&_addr);
			//}

			///* get size */
			//::socklen_t size(void) const noexcept {
			//	return _size;
			//}



	};



	// -- S O C K E T  C L A S S ----------------------------------------------

	template <class D, class T>
	class socket final {

		public:

			// -- assertions --------------------------------------------------

			/* domain assertion */
			static_assert(xns::is_one_of<D, xns::local,
											xns::ipv4,
											xns::ipv6>,
				"): INVALID SOCKET DOMAIN :(");

			/* type assertion */
			static_assert(xns::is_one_of<T, xns::stream,
											xns::datagram,
											xns::raw>,
				"): INVALID SOCKET TYPE :(");


		public:

			// -- public type types -------------------------------------------




		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = socket<D, T>;

			/* protocol type */
			using protocol = int;

			/* size type */
			using size_type = xns::size_t;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			socket(void) noexcept
			: _socket{} {}

			/* non-copyable class */
			NON_COPYABLE(socket);

			/* move constructor */
			socket(self&& other) noexcept
			: _socket(xns::move(other._socket)) {
			}

			/* destructor */
			~socket(void) noexcept {
			}


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// check for self assignment
				if (this != &other) {
				} // return self reference
				return *this;
			}



			// -- public modifiers --------------------------------------------

			/* create an endpoint for communication and returns a descriptor */
			void create(const int protocol = 0) noexcept {
				// create socket
				_socket = ::socket(D::value, T::value, protocol);
			}

			/* bind a name to a socket */
			template <class... A>
			void bind(A&&... args) noexcept {

				// check descriptor validity
				if (_socket.invalid()) { return; }


				// create address
				address addr = D::make_address(xns::forward<A>(args)...);

				// bind socket
				if (::bind(_socket.get(), addr.as_sockaddr(), addr.size()) == -1) {
					std::cout << "bind error: " << std::strerror(errno) << std::endl;
				}
				//::unlink("./debug.sock");

			}

			/* listen for connections on a socket */
			void listen(const int backlog = 0) const noexcept {
				// check descriptor validity
				if (_socket.invalid()) { return; }
				// listen on socket
				if (::listen(_socket.get(), backlog) == -1) {
					// error
				}
			}

			/* accept a connection on a socket */
			void accept(void) const noexcept {
				// check descriptor validity
				if (_socket.invalid()) { return; }


				std::cout << "accepting..." << std::endl;


				sockaddr_storage addr;
				socklen_t size = sizeof(sockaddr_storage);

				std::cout << "address size: " << size << std::endl;

				// accept connection
				network::socket sock = ::accept(_socket.get(), reinterpret_cast<sockaddr*>(&addr), &size);

				std::cout << "address size: " << size << std::endl;

				//self::address address{addr, size};

				if (sock.invalid()) {
					std::cout << "accept error: " << std::strerror(errno) << std::endl;
					return;
				}

				std::cout << "accept success: " << std::endl;


				switch (addr.ss_family) {
					case AF_INET: {
										std::cout << "AF_INET" << std::endl;
										break;
									}
					case AF_INET6: {
										std::cout << "AF_INET6" << std::endl;
										break;
									}
					case AF_LOCAL: {
										std::cout << "AF_LOCAL" << std::endl;
										break;
									}
					default: {
									std::cout << "UNKNOWN: " << (int)addr.ss_family << std::endl;
									break;
								}
				}

				char ipstr[INET_ADDRSTRLEN];
				struct sockaddr_in *s = (struct sockaddr_in *)&addr;
				inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(ipstr));

				std::cout << "ip: " << ipstr << std::endl;

				char buffer[1024];
				long readed = ::recv(sock.get(), buffer, 1024, 0);
				if (readed == -1) {
					std::cout << "error: " << std::strerror(errno) << std::endl;
				}
				else {
					buffer[readed] = '\0';
					std::cout << "readed: " << buffer << std::endl;
				}
			}


			void connect(const std::string& path) noexcept {

				// check descriptor validity
				if (_socket.invalid()) { return; }

				// create address
				//address addr = D::make_address(path);

				// connect socket
				//if (::connect(_socket, addr.as_sockaddr(), addr.size()) == -1) {
					// error
				//}
			}


		private:


			// -- private members ---------------------------------------------

			/* descriptor */
			xns::network::socket _socket;

	};



	// -- N E T W O R K  N A M E S P A C E ------------------------------------

	/* network namespace */
	namespace network {


		class server final {


			public:



			private:

				// -- private types -------------------------------------------



				// -- private members -----------------------------------------


		};





	} // namespace network

} // namespace xns

	// command for local socket: echo $(tty) | nc -U ./xns_debug.sock
	// command for tcp socket: echo "hello" | nc localhost 1234
	// command for udp socket: echo "hello" | nc -u localhost 1234


#endif
