#ifndef POLLER_HEADER
#define POLLER_HEADER

// local headers
#include "socket.hpp"




// -- S T R U C T  P O L L F D  O P E R A T O R S ---------------------


// -- comparison operators --------------------------------------------

/* equality operator */
inline auto operator==(const struct pollfd& lhs,
						const struct pollfd& rhs) noexcept -> bool {
	return lhs.fd == rhs.fd;
}

/* inequality operator */
inline auto operator!=(const struct pollfd& lhs,
						const struct pollfd& rhs) noexcept -> bool {
	return lhs.fd != rhs.fd;
}

/* less than operator */
inline auto operator<(const struct pollfd& lhs,
						const struct pollfd& rhs) noexcept -> bool {
	return lhs.fd < rhs.fd;
}

/* greater than operator */
inline auto operator>(const struct pollfd& lhs,
						const struct pollfd& rhs) noexcept -> bool {
	return lhs.fd > rhs.fd;
}

/* less than or equal to operator */
inline auto operator<=(const struct pollfd& lhs,
						const struct pollfd& rhs) noexcept -> bool {
	return !(lhs > rhs);
}

/* greater than or equal to operator */
inline auto operator>=(const struct pollfd& lhs,
						const struct pollfd& rhs) noexcept -> bool {
	return !(lhs < rhs);
}


// -- X N S  N A M E S P A C E ------------------------------------------------


namespace xns {


	// -- N E T W O R K  N A M E S P A C E ------------------------------------

	namespace network {


		// -- S T R U C T  P O L L F D  O P E R A T O R S ---------------------

		// -- comparison operators (with socket) ------------------------------

		/* equality operator */
		inline auto operator==(const struct pollfd& lhs,
							   const xns::network::socket& rhs) noexcept -> bool {
			return lhs.fd == rhs.get();
		}

		/* equality operator (inverted) */
		inline auto operator==(const xns::network::socket& lhs,
							   const struct pollfd& rhs) noexcept -> bool {
			return rhs.fd == lhs.get();
		}

		/* inequality operator */
		inline auto operator!=(const struct pollfd& lhs,
							   const xns::network::socket& rhs) noexcept -> bool {
			return lhs.fd != rhs.get();
		}

		/* inequality operator (inverted) */
		inline auto operator!=(const xns::network::socket& lhs,
							   const struct pollfd& rhs) noexcept -> bool {
			return rhs.fd != lhs.get();
		}

		/* less than operator */
		inline auto operator<(const struct pollfd& lhs,
							  const xns::network::socket& rhs) noexcept -> bool {
			return lhs.fd < rhs.get();
		}

		/* less than operator (inverted) */
		inline auto operator<(const xns::network::socket& lhs,
							  const struct pollfd& rhs) noexcept -> bool {
			return rhs.fd > lhs.get();
		}

		/* greater than operator */
		inline auto operator>(const struct pollfd& lhs,
							  const xns::network::socket& rhs) noexcept -> bool {
			return lhs.fd > rhs.get();
		}

		/* greater than operator (inverted) */
		inline auto operator>(const xns::network::socket& lhs,
							  const struct pollfd& rhs) noexcept -> bool {
			return rhs.fd < lhs.get();
		}

		/* less than or equal to operator */
		inline auto operator<=(const struct pollfd& lhs,
							   const xns::network::socket& rhs) noexcept -> bool {
			return !(lhs > rhs);
		}

		/* less than or equal to operator (inverted) */
		inline auto operator<=(const xns::network::socket& lhs,
							   const struct pollfd& rhs) noexcept -> bool {
			return !(lhs > rhs);
		}

		/* greater than or equal to operator */
		inline auto operator>=(const struct pollfd& lhs,
							   const xns::network::socket& rhs) noexcept -> bool {
			return !(lhs < rhs);
		}

		/* greater than or equal to operator (inverted) */
		inline auto operator>=(const xns::network::socket& lhs,
							   const struct pollfd& rhs) noexcept -> bool {
			return !(lhs < rhs);
		}



		// -- P O L L E R  C L A S S ------------------------------------------

		/* poller */
		class poller final : public xns::link<xns::network::poller,
											  xns::network::socket> {


			public:

				// -- public types --------------------------------------------

				/* self type */
				using self = xns::network::poller;

				/* link type */
				using link = xns::link<self, xns::network::socket>;


				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline poller(void) noexcept = default;

				/* destructor */
				~poller(void) noexcept = default;



				// -- public modifiers ----------------------------------------

				/* add socket */
				auto add_socket(network::socket& socket) noexcept -> void {
					// link
					link::attach(socket);
					// dichotomic insert
					_poll.dichotomic_insert({socket.get(),
											 static_cast<short>(POLLIN),
											 static_cast<short>(0)});
					print();

				}

				/* remove socket */
				auto remove_socket(network::socket& sock) noexcept -> void {
					// unlink
					link::detach(sock);
					// assume pollfd is sorted
					_poll.erase(_poll.dichotomic_search(sock));
					print();
				}

				auto print(void) -> void {

					std::cout << "\x1b[1;34m" << "poller" << "\x1b[0m" << std::endl;
					for (const auto& fd : _poll) {
						std::cout << fd.fd << std::endl;
					}
					std::cout << std::endl;
				}


				/* poll */
				inline auto poll(void) noexcept -> void {
					nfds_t size = static_cast<nfds_t>(_poll.size());
					int nd = ::poll(_poll.data(), size, -1);


					// check error
					if (nd == -1) { return; }

					if (nd == 0) { return; }

					// check for events
					for (size_type i = 0; i < size; ++i) {

						struct pollfd& poll = _poll[i];

						if (poll.revents & POLLIN || poll.revents & POLLPRI) {
							// POLLIN: Data other than high priority data may be read without blocking.
							// This is equivalent to ( POLLRDNORM | POLLRDBAND ).
						}
						else if (poll.revents & POLLHUP) {
							// POLLHUP: The device or socket has been disconnected.
							// This flag is output only, and ignored if present in the input events bitmask.
							// Note that POLLHUP and POLLOUT are mutually exclusive and should never be present in the revents bitmask at the same time.
							_poll.erase(i); // need to remove link
						}
						else if (poll.revents & POLLERR) {
							// POLLERR: An exceptional condition has occurred on the device or socket.
							// This flag is output only, and ignored if present in the input events bitmask.
							_poll.erase(i); // need to remove link
						}
						else if (poll.revents & POLLNVAL) {
							// POLLNVAL: The file descriptor is not open.
							// This flag is output only, and ignored if present in the input events bitmask.
							_poll.erase(i); // need to remove link
						}
						else if (poll.revents & POLLOUT || poll.revents & POLLWRBAND) {
							// POLLOUT: Normal data may be written without blocking.
							// This is equivalent to POLLWRNORM.
						}
					}

				}

				void run(void) noexcept {
					while (_poll.size() > 0 && _running) {
						poll();
					}
				}


			private:




				// -- private types -------------------------------------------

				/* pollfd type */
				using pollfd_t = struct pollfd;

				/* pollfd vector type */
				using poll_vector = xns::vector<pollfd_t>;

				/* size type */
				using size_type = typename poll_vector::size_type;


				// -- private members -----------------------------------------

				/* is running */
				bool _running;

				/* pollfd vector */
				poll_vector _poll;


		};



		class bsd_poller final {

			public:



		};


	}



}



#endif // POLLER_HEADER
