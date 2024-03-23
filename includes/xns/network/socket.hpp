#ifndef XNS_UNIQUE_SOCKET_HEADER
#define XNS_UNIQUE_SOCKET_HEADER

// local headers
#include "xns/config/macros.hpp"

#include "xns/containers/vector.hpp"
#include "xns/containers/reference_wrapper.hpp"

#include "xns/system/unique_descriptor.hpp"
#include "xns/other/link.hpp"

#include "xns/type_traits/relationships_and_property_queries/is_comparable.hpp"
#include "xns/type_traits/type_operations/move.hpp"

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

				/* id type */
				using id_type = xns::unique_descriptor::id_type;

				/* link type */
				using link = xns::link<self, xns::network::poller>;


				// -- public lifecycle ----------------------------------------

				/* default constructor */
				inline socket(void) noexcept
				: unique_descriptor{}, link{} {}

				/* descriptor constructor */
				inline socket(const id_type sock) noexcept
				: unique_descriptor{sock}, link{} {}

				/* unique descriptor constructor */
				inline socket(unique_descriptor&& sock) noexcept
				: unique_descriptor{xns::move(sock)}, link{} {}

				/* non-copyable class */
				NON_COPYABLE(socket);

				/* move constructor */
				inline socket(self&& other) noexcept
				: unique_descriptor{xns::move(other)}, link{xns::move(other)} {}

				/* destructor */
				~socket(void) noexcept { /* error when set = default; */ }


				// -- public assignment operators -----------------------------

				/* move assignment operator */
				inline auto operator=(self&& other) noexcept -> self& {
					unique_descriptor::operator=(xns::move(other));
					link::operator=(xns::move(other));
					return *this;
				}

				/* descriptor assignment operator */
				inline auto operator=(const id_type& sock) noexcept -> self& {
					unique_descriptor::operator=(sock);
					return *this;
				}


			private:

		};


	}

}




#endif // UNIQUE_SOCKET_HEADER
