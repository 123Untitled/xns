#ifndef XNS_GETLINE_HEADER
#define XNS_GETLINE_HEADER

#include "xns/system/unique_descriptor.hpp"
#include "xns/string/string.hpp"
#include "xns/type_traits/other/is_one_of.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <typename T>
	concept is_line = xns::is_one_of<T, xns::string, xns::string_view>;


	// -- G E T L I N E -------------------------------------------------------

	template <typename T>
	class getline final {

		// assert that T is a line type
		static_assert(xns::is_line<T>,
			"): GETLINE: T must be a line type [string or string_view] :(");

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::getline<T>;

			/* line type */
			using line_t = T;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			getline(void) = delete;

			/* unique descriptor constructor */
			inline getline(unique_descriptor&& fd) noexcept
			: _fd(xns::move(fd)) { }

			/* non-assignable */
			non_assignable(getline);

			/* destructor */
			inline ~getline(void) noexcept = default;



			// -- public methods ----------------------------------------------

			/* next line */
			/* use linked list to store read */
			inline auto next(line_t& line) noexcept -> bool {

				return true;
			}




		private:

			// -- private constants -------------------------------------------

			enum : decltype(sizeof(0)) { BUFFER_SIZE = 4096 };

			// -- forward declarations ----------------------------------------

			class node;


			// -- private types -----------------------------------------------

			/* node pointer */
			using node_ptr = node*;



			class node final {

				public:

					// -- public types ----------------------------------------

					/* self type */
					using self = node;



				private:

					// -- private members -------------------------------------

					/* buffer */
					char _buffer[BUFFER_SIZE + 1];

					/* current position */
					char* _position;

					/* next node */
					node_ptr _next;

			};



			// -- private members ---------------------------------------------

			/* file descriptor */
			xns::unique_descriptor _fd;

	};

}

#endif // XNS_GETLINE_HEADER
