#ifndef ADDRESS_HEADER
#define ADDRESS_HEADER

// local headers
#include "macros.hpp"
#include "types.hpp"
#include "is_integral.hpp"
#include "string.hpp"
#include "is_one_of.hpp"

// operating system headers
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- N E T W O R K  N A M E S P A C E ------------------------------------

	namespace network {


		/* local domain (unix domain) */
		struct local {
			#ifdef __linux__
			static constexpr int value = AF_LOCAL;
			#elif __APPLE__ || __FreeBSD__
			static constexpr int value = PF_LOCAL;
			#endif
		};

		/* inet domain (ipv4 domain) */
		struct ipv4 {
			#ifdef __linux__
				static constexpr int value = AF_INET;
			#elif __APPLE__ || __MACH__ || __FreeBSD__
				static constexpr int value = PF_INET;
			#endif
		};

		/* inet6 domain */
		struct ipv6 {
			#ifdef __linux__
				static constexpr int value = AF_INET6;
			#elif __APPLE__ || __MACH__ || __FreeBSD__
				static constexpr int value = PF_INET6;
			#endif
		};


		class socket;
		class session;


		// -- I P V 4  A D D R E S S  C L A S S -------------------------------

		/* ipv4 address */
		class ipv4_address final {

			// -- friends -----------------------------------------------------

			template <class A>
			friend int bind(const xns::network::socket&, const A&) noexcept;


			public:

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				ipv4_address(void) noexcept;

				/* ip and port constructor */
				template <class S, class P>
				ipv4_address(const S& ip, const P& port) noexcept
				: _addr{} {

					// check ip is string
					static_assert(xns::is_string<S>, "): IP MUST BE STRING :(");

					// check port is 16-bit unsigned integer
					static_assert(xns::is_unsigned_integral<P> && sizeof(P) == 2,
						"): PORT MUST BE 16-BIT UNSIGNED INTEGER :(");

					_addr.sin_family = ipv4::value;
					_addr.sin_port = htons(port);

					int ret = ::inet_pton(ipv4::value, ip.data(), &_addr.sin_addr);

					(void)ret;

				}

				/* destructor */
				~ipv4_address(void) noexcept = default;


				// -- public accessors ----------------------------------------

				/* size */
				constexpr auto size(void) const noexcept -> ::socklen_t {
					return sizeof(_addr);
				}


			private:

				// -- private members -----------------------------------------

				/* address */
				::sockaddr_in _addr;

		};


		// -- I P V 6  A D D R E S S  C L A S S -------------------------------

		/* ipv6 address */
		class ipv6_address final {


			public:

			private:

				// -- private members -----------------------------------------

				/* address */
				::sockaddr_in6 _addr;

				/* size */
				::socklen_t _size;

		};


		// -- L O C A L  A D D R E S S  C L A S S -----------------------------

		/* local address */
		class local_address final {

			public:

			private:

				// -- private members -----------------------------------------

				/* address */
				::sockaddr_un _addr;

				/* size */
				::socklen_t _size;

		};


		// -- A D D R E S S  C L A S S ----------------------------------------

		/* address */
		class address final {

			// -- friends -----------------------------------------------------

			template <class A>
			friend int bind(const xns::network::socket&, const A&) noexcept;
			//friend session accept(const socket&) noexcept;

			public:

				// -- public types --------------------------------------------

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				address(void) noexcept
				: _addr{}, _size{sizeof(::sockaddr_storage)} {}


				// -- public accessors ----------------------------------------

				/* size */
				constexpr auto size(void) const noexcept -> ::socklen_t {
					return _size;
				}

			private:

				// -- private members -----------------------------------------

				/* address */
				::sockaddr_storage _addr;

				/* size */
				::socklen_t _size;

		};


		// -- I S  A D D R E S S ----------------------------------------------

		/* is address */
		template <class T>
		concept is_address = xns::is_one_of<T, ipv4_address, ipv6_address, local_address>;



	}





}

#endif // ADDRESS_HEADER
