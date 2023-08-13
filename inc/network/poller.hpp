#ifndef POLLER_HEADER
#define POLLER_HEADER

// local headers
#include "socket.hpp"
#include "numeric_limits.hpp"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>



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



		template <typename T>
		class kvnt final {

			public:

				// -- public types --------------------------------------------

				/* identifier type */
				using identifier = decltype(xns::declval<struct kevent>().ident);

				/* filter type */
				using filter = decltype(xns::declval<struct kevent>().filter);

				/* flags type */
				using flags = decltype(xns::declval<struct kevent>().flags);

				/* filter flags type */
				using filter_flags = decltype(xns::declval<struct kevent>().fflags);

				/* data type */
				using data = decltype(xns::declval<struct kevent>().data);

				/* user data type */
				using user_data = T;




				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline constexpr kvnt(void) noexcept
				: _kevent{} {}

				/* struct kevent constructor */
				inline constexpr kvnt(struct kevent& kevent) noexcept
				: _kevent{kevent} {}

				/* copy constructor */
				inline constexpr kvnt(const kvnt& other) noexcept
				: _kevent{other._kevent} {}

				/* move constructor */
				inline constexpr kvnt(kvnt&& other) noexcept
				: kvnt{other} {}

				/* destructor */
				inline ~kvnt(void) noexcept = default;


				// -- public assignment operators -----------------------------

				/* copy assignment operator */
				inline constexpr kvnt& operator=(const kvnt& other) noexcept {
					_kevent = other._kevent;
					return *this;
				}

				/* move assignment operator */
				inline constexpr kvnt& operator=(kvnt&& other) noexcept {
					return operator=(other);
				}

				// -- public conversion operators -----------------------------

				/* kevent conversion operator */
				inline constexpr operator struct kevent&(void) noexcept {
					return _kevent;
				}

				/* kevent pointer conversion operator */
				inline constexpr operator struct kevent*(void) noexcept {
					return &_kevent;
				}

				/* to kvnt conversion operator */
				static inline constexpr auto to_kvnt(struct kevent& kevent) noexcept -> kvnt& {
					return *static_cast<kvnt*>(static_cast<void*>(&kevent));
				}


				// -- public modifiers ----------------------------------------

				/* setup */
				inline constexpr auto setup(const xns::network::socket& socket,
											const filter& filter,
											const flags& flags,
											const filter_flags& filter_flags,
											const data& data,
											user_data& user_data) noexcept -> void {

					if (socket.valid()) {
						_kevent.ident = static_cast<identifier>(socket.get());
					}
					_kevent.filter = filter;
					_kevent.flags = flags;
					_kevent.fflags = filter_flags;
					_kevent.data = data;
					_kevent.udata = static_cast<void*>(&user_data);
				}


				// -- public accessors ----------------------------------------

				/* get ident */
				inline constexpr auto get_ident(void) const noexcept -> const identifier& {
					return _kevent.ident;
				}

				/* get filter */
				inline constexpr auto get_filter(void) const noexcept -> const filter& {
					return _kevent.filter;
				}

				/* get flags */
				inline constexpr auto get_flags(void) const noexcept -> const flags& {
					return _kevent.flags;
				}

				/* get filter flags */
				inline constexpr auto get_filter_flags(void) const noexcept -> const filter_flags& {
					return _kevent.fflags;
				}

				/* get data */
				inline constexpr auto get_data(void) const noexcept -> const data& {
					return _kevent.data;
				}

				/* get user data */
				inline constexpr auto get_user_data(void) const noexcept -> const user_data& {
					return *static_cast<user_data*>(_kevent.udata);
				}


			private:

				// -- private members -----------------------------------------

				/* kevent */
				struct kevent _kevent;

		};



		class bsd_poller final {

			public:

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline bsd_poller(void) noexcept
				: _kqueue{::kqueue()},
				  _kevents{} {
					_kevents.reserve(128);
				}

				auto add_socket(network::socket& socket) noexcept -> void {

					xns::network::kvnt<network::socket> event{};
					// setup event
					event.setup(socket, EVFILT_READ, EV_ADD, 0, 0, socket);
					// add event
					if (::kevent(_kqueue.get(), event, 1, nullptr, 0, nullptr) == -1) {
						std::cout << "error: " << std::strerror(errno) << std::endl;
					} // increase buffer size
					_kevents.push_back();
				}

				auto remove_socket(network::socket& socket) noexcept -> void {

					xns::network::kvnt<network::socket> event{};
					// setup event
					event.setup(socket, EVFILT_READ, EV_DELETE, 0, 0, socket);
					// add event
					if (kevent(_kqueue.get(), event, 1, nullptr, 0, nullptr) == -1) {
						std::cout << "error: " << std::strerror(errno) << std::endl;
					} // decrease buffer size
					_kevents.pop_back();
				}

				auto poll(void) noexcept -> void {

					bool range = xns::limits::in_range<int>(_kevents.size());

					if (range == false) { return; }

					int nev = kevent(_kqueue.get(), nullptr, 0, _kevents.data(),
									 static_cast<int>(_kevents.size()), nullptr);

					if (nev < 0) {
						std::cout << "error: " << std::strerror(errno) << std::endl;
						return;
					}

					for (size_type i = 0; i < static_cast<size_type>(nev); ++i) {

						auto& event = kvnt<network::socket>::to_kvnt(_kevents[i]);


						if (event.get_filter() == EVFILT_READ) {

							auto& socket = event.get_user_data();

						}




						std::cout << "event: " << _kevents[i].ident << std::endl;
					}
				}

				// return the number of events placed in the eventlist, up to the value given by nevents.
				// If an error occurs while processing an element of the changelist and there is enough room in the eventlist,
				// then the event will be placed in the eventlist with EV_ERROR set in flags and the system error in data.
				// Otherwise, -1 will be returned, and errno will be set to indicate the error condition.
				// If the time limit expires, then kevent(), kevent64() and kevent_qos() return 0.

				//struct kevent {
				//	uintptr_t ident;        /* identifier for this event */
				//	uint32_t  filter;       /* filter for event */
				//	uint32_t  flags;        /* action flags for kqueue */
				//	uint32_t  fflags;       /* filter flag value */
				//	int64_t   data;         /* filter data value */
				//	void     *udata;        /* opaque user data identifier */
				//};


			private:

				// -- private types -------------------------------------------

				/* kevent type */
				using kevent_t = struct kevent;

				/* kevent vector type */
				using kevent_vector = xns::vector<kevent_t>;

				/* size type */
				using size_type = typename kevent_vector::size_type;


				// -- private members -----------------------------------------

				/* kqueue */
				xns::unique_descriptor _kqueue;

				/* kevent vector */
				kevent_vector _kevents;


		};





	}



}



#endif // POLLER_HEADER
