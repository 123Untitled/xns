#ifndef UNIQUE_SOCKET_HEADER
#define UNIQUE_SOCKET_HEADER

// local headers
#include "macro.hpp"
#include "vector.hpp"
#include "unique_descriptor.hpp"
#include "reference.hpp"
#include "move.hpp"
#include "link.hpp"

#include "is_comparable.hpp"

// operating system headers
#include <unistd.h>
#include <poll.h>





// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- N E T W O R K  N A M E S P A C E ------------------------------------

	namespace network {


		// -- forward declarations --------------------------------------------

		class poller;
		class socket;


		// -- U N I Q U E  S O C K E T  C L A S S -----------------------------

		/* unique socket */
		class socket final : public xns::unique_descriptor,
							 public xns::link<xns::network::socket,
											  xns::network::poller> {


			public:

				// -- public types --------------------------------------------

				/* self type */
				using self = xns::network::socket;

				/* descriptor type */
				using descriptor = xns::unique_descriptor::descriptor;

				/* link type */
				using link = xns::link<self, xns::network::poller>;


				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline socket(void) noexcept
				: unique_descriptor{}, link{} {}

				/* descriptor constructor */
				inline socket(const descriptor& socket) noexcept
				: unique_descriptor{socket}, link{} {}

				/* unique descriptor constructor */
				inline socket(unique_descriptor&& socket) noexcept
				: unique_descriptor{xns::move(socket)}, link{} {}

				/* non-copyable class */
				NON_COPYABLE(socket);

				/* move constructor */
				inline socket(self&& other) noexcept
				: unique_descriptor{xns::move(other)}, link{xns::move(other)} {}

				/* destructor */
				inline ~socket(void) noexcept = default;


				// -- public assignment operators -----------------------------

				/* move assignment operator */
				inline auto operator=(self&& other) noexcept -> self& {
					unique_descriptor::operator=(xns::move(other));
					link::operator=(xns::move(other));
					return *this;
				}

				/* descriptor assignment operator */
				inline auto operator=(const descriptor& socket) noexcept -> void {
					unique_descriptor::operator=(socket);
				}


			private:

		};


	}

}




#endif // UNIQUE_SOCKET_HEADER
