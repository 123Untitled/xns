#ifndef XNS_POLLER_HEADER
#define XNS_POLLER_HEADER

// local headers
#include "xns/network/socket.hpp"
#include "xns/utility/numeric_limits.hpp"
#include "xns/config/os.hpp"

// operating system headers
#if defined(XNS_LINUX)
	#include <sys/epoll.h>
#elif defined(XNS_BSD) || defined(XNS_APPLE)
	#include <sys/types.h>
	#include <sys/event.h>
	#include <sys/time.h>
#endif



// -- X N S  N A M E S P A C E ------------------------------------------------


namespace xns {


	// -- N E T W O R K  N A M E S P A C E ------------------------------------

	namespace network {



		// -- P O L L E R  C L A S S ------------------------------------------

		/* poller */
		class test final : public xns::link<xns::network::test,
											xns::network::socket> {

			public:

				/* self type */
				using self = xns::network::test;

				/* link type */
				using link = xns::link<self, xns::network::socket>;

				/* add socket */
				auto add_socket(network::socket& socket) noexcept -> void {
					//link::attach(socket);
				}
				/* remove socket */
				auto remove_socket(network::socket& sock) noexcept -> void {
					//link::detach(sock);
				}
		};




		// -- P O L L E R  B A S E  C L A S S ---------------------------------

		template <typename T>
		class poller_interface {


			public:

				// -- public types --------------------------------------------

				/* self type */
				using self = poller_interface<T>;


				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline poller_interface(void) noexcept = default;

				/* copy constructor */
				inline poller_interface(const self& base) noexcept = default;

				/* move constructor */
				inline poller_interface(self&& base) noexcept = default;

				/* destructor */
				inline ~poller_interface(void) noexcept = default;


				// -- public assignment operators -----------------------------

				/* copy assignment operator */
				inline auto operator=(const self& base) noexcept -> self& = default;

				/* move assignment operator */
				inline auto operator=(self&& base) noexcept -> self& = default;


				// -- public interface ----------------------------------------

				/* add socket */
				inline auto add_socket(network::socket& socket) noexcept -> void {
					static_cast<T*>(this)->add_socket(socket);
				}

				/* remove socket */
				inline auto remove_socket(network::socket& socket) noexcept -> void {
					static_cast<T*>(this)->remove_socket(socket);
				}

				/* run */
				inline auto run(void) noexcept -> void {
					static_cast<T*>(this)->run();
				}

				/* stop */
				inline auto stop(void) noexcept -> void {
					static_cast<T*>(this)->stop();
				}

		};







#if defined(XNS_APPLE) || defined(XNS_BSD)


		class poller final : public poller_interface<poller> {


			public:

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline poller(void) noexcept
				: _kqueue{::kqueue()},
				  _kevents{},
				  _is_running{true} {
					_kevents.reserve(DEFAULT_BUFF_SIZE);
				}

				/* add socket */
				auto add_socket(network::socket& socket) noexcept -> void {

					// make kevent struct
					const struct kevent event{
						/* identifier for this event */
						.ident  = static_cast<uintptr_t>(socket.get()),
						/* filter for event */
						.filter = EVFILT_READ,
						/* general flags */
						.flags  = EV_ADD,
						/* filter-specific flags */
						.fflags = 0,
						/* filter-specific data */
						.data   = 0,
						/* opaque user data identifier */
						.udata  = &socket
					};

					// add event
					if (::kevent(_kqueue.get(), &event, 1, nullptr, 0, nullptr) == -1) {
						std::cout << "error: " << std::strerror(errno) << std::endl;
					} // increase buffer size
					_kevents.emplace_back(); // INFO need to call resize
				}

				auto remove_socket(network::socket& socket) noexcept -> void {

					// make kevent struct
					struct kevent event{
						/* identifier for this event */
						.ident  = static_cast<uintptr_t>(socket.get()),
						/* filter for event */
						.filter = EVFILT_READ,
						/* general flags */
						.flags  = EV_DELETE,
						/* filter-specific flags */
						.fflags = 0,
						/* filter-specific data */
						.data   = 0,
						/* opaque user data identifier */
						.udata  = nullptr
					};

					// add event
					if (kevent(_kqueue.get(), &event, 1, nullptr, 0, nullptr) == -1) {
						std::cout << "error: " << std::strerror(errno) << std::endl;
					} // decrease buffer size
					_kevents.pop_back();
				}

				auto run(void) noexcept -> void {

					bool range = xns::limits<int>::in_range(_kevents.size());

					if (range == false) { return; }


					while (_is_running == true) {

						int nev = ::kevent(_kqueue.get(), nullptr, 0, _kevents.data(),
										static_cast<int>(_kevents.size()), nullptr);

						if (nev < 0) {
							std::cout << "error: " << std::strerror(errno) << std::endl;
							return;
						}

						for (size_type i = 0; i < static_cast<size_type>(nev); ++i) {

							if (_kevents[i].filter == EVFILT_READ) {
								void* data = _kevents[i].udata;
							}

							std::cout << "event: " << _kevents[i].ident << std::endl;
						}
					}
				}

				auto stop(void) noexcept -> void {
					_is_running = false;
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

				// -- private constants ---------------------------------------

				enum : xns::ubyte { DEFAULT_BUFF_SIZE = 128 };


				// -- private types -------------------------------------------

				/* kevent vector type */
				using event_vector = xns::vector<struct kevent>;

				/* size type */
				using size_type = typename event_vector::size_type;


				// -- private members -----------------------------------------

				/* kqueue */
				xns::unique_descriptor _kqueue;

				/* kevent vector */
				event_vector _kevents;

				/* is running */
				bool _is_running;


		};


#elif defined(XNS_LINUX)


		class poller final : public poller_interface<poller> {

			public:

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline poller(void) noexcept
				: _epoll{::epoll_create1(0)},
				  _events{},
				  _is_running{true} {
					_events.reserve(DEFAULT_BUFF_SIZE);
				}

				auto add_socket(network::socket& socket) noexcept -> void {

					struct epoll_event event{};

					// setup event
					event.events = EPOLLIN;
					event.data.fd = socket.get();
					event.data.ptr = &socket;

					// add event
					if (::epoll_ctl(_epoll.get(), EPOLL_CTL_ADD, socket.get(), &event) == -1) {
						std::cout << "error: " << std::strerror(errno) << std::endl;
					} // increase buffer size
					_events.emplace_back(); // INFO need to call resize
				}

				auto remove_socket(network::socket& socket) noexcept -> void {

					struct epoll_event event{};

					// setup event
					event.events = EPOLLIN;
					event.data.fd = socket.get();
					event.data.ptr = &socket;

					// add event
					if (::epoll_ctl(_epoll.get(), EPOLL_CTL_DEL, socket.get(), &event) == -1) {
						std::cout << "error: " << std::strerror(errno) << std::endl;
					} // decrease buffer size
					_events.pop_back();
				}

				auto run(void) noexcept -> void {

					while (_is_running == true) {

						int nev = ::epoll_wait(_epoll.get(), _events.data(),
											static_cast<int>(_events.size()), -1);
						// CHECK NEV IS GREATER THAN VECTOR SIZE

						if (nev < 0) {
							std::cout << "error: " << std::strerror(errno) << std::endl;
							return;
						}

						for (size_type i = 0; i < static_cast<size_type>(nev); ++i) {

							if (_events[i].events & EPOLLIN) {

								void* data = _events[i].data.ptr;
							}

							std::cout << "event: " << _events[i].data.fd << std::endl;
						}
					}
				}

				auto stop(void) noexcept -> void {
					_is_running = false;
				}

			private:

				// -- private constants ---------------------------------------

				enum : xns::ubyte { DEFAULT_BUFF_SIZE = 128 };


				// -- private types -------------------------------------------

				/* epoll event vector type */
				using event_vector = xns::vector<struct epoll_event>;

				/* size type */
				using size_type = typename event_vector::size_type;


				// -- private members -----------------------------------------

				/* epoll */
				xns::unique_descriptor _epoll;

				/* epoll event vector */
				event_vector _events;

				/* is running */
				bool _is_running;

		};


#endif // XNS_OS



	} // namespace network



} //



#endif // POLLER_HEADER
