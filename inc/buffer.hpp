#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include "macro.hpp"
#include "types.hpp"
#include "allocator.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "literal.hpp"

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I L E  D E S C R I P T O R  T Y P E S -----------------------------

	struct stdout {
		/* file descriptor */
		static constexpr int fd = STDOUT_FILENO;
	};

	struct stderr {
		/* file descriptor */
		static constexpr int fd = STDERR_FILENO;
	};

	/* is std file descriptor */
	template <class T>
	concept is_std_fd = Xf::is_same<T, stdout> || Xf::is_same<T, stderr>;



	// -- O U T P U T  C L A S S ----------------------------------------------

	class output final {

		private:

			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			output(void);

			/* non-assignable class */
			NON_ASSIGNABLE(output);


		public:

			// -- P U B L I C  D E S T R U C T O R S --------------------------

			/* destructor */
			~output(void);


			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------

			/* write unknown bytes */
			static void write(const char* str);

			/* write bytes */
			static void write(const char* str, const xns::cstring::size_type size);

			/* write string */
			static void write(const xns::cstring& str);

			/* write string */
			template <class T> requires (xns::is_literal<T>)
			static void write(void) {
				// call buffer write
				write(T::data(), T::size());
			}

			/* render */
			template <is_std_fd T = xns::stdout>
			static void render(void) {

				// do nothing if buffer is empty
				if (_instance._buffer.empty()) { return; }

				// write buffer to file descriptor
				(void)::write(T::fd, _instance._buffer.pointer(),
								  _instance._buffer.size());

				// clear buffer
				_instance._buffer.clear();
			}



		private:

			// -- P R I V A T E  E N U M S ------------------------------------

			/* buffer size */
			enum : xns::size_t { DEFAULT_BUFFER_SIZE = 1024 };


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* buffers */
			xns::cstring _buffer;


			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* instance */
			static output _instance;


	};




}




#endif
