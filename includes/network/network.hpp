#ifndef XNS_NETWORK_HEADER
#define XNS_NETWORK_HEADER

// local headers
#include "socket.hpp"
#include "work_in_progress.hpp"
#include "address.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- N E T W O R K  N A M E S P A C E ------------------------------------

	namespace network {


		// -- types -----------------------------------------------------------

		/* port type */
		using port = xns::u16;


		/* assigns a name to an unnamed socket */
		template <class address_t>
		inline int bind(const xns::network::socket& socket, const address_t& address) noexcept {
			// check address type
			static_assert(xns::network::is_address<address_t>, "): INVALID ADDRESS TYPE :(");
			// bind socket
			return ::bind(socket.get(),
						reinterpret_cast<const struct sockaddr*>(&address._addr),
							 address.size());
		}

		/* connect */
		template <class address_t>
		inline int connect(const xns::network::socket& socket, const address_t& address) noexcept {

			// check address type
			static_assert(xns::network::is_address<address_t>, "): INVALID ADDRESS TYPE :(");

			// connect socket
			return ::connect(socket.get(),
						reinterpret_cast<const struct sockaddr*>(&address._addr),
							 address.size());
		}

		/* listen */
		inline int listen(const xns::network::socket& socket, const int& backlog) noexcept {
			return ::listen(socket.get(), backlog);
		}

		/* accept */
		inline void accept(const xns::network::socket& socket) noexcept {

			/*
			xns::network::address address;

			xns::network::socket client{
				::accept(socket.get(),
						reinterpret_cast<struct sockaddr*>(&address._addr),
						&address._size)
			};
			*/


		}

		/* make socket */
		template <class domain_t, class type_t>
		inline auto make_socket(void) noexcept -> xns::network::socket {
			// create socket with domain, type, and protocol
			return xns::network::socket{
				::socket(domain_t::value, type_t::value, 0)
			};
		}


	}


}


#endif // NETWORK_HEADER
