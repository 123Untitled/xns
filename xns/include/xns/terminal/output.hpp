#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include "macro.hpp"
#include "types.hpp"
#include "string.hpp"
#include "string_literal.hpp"
#include "conversions.hpp"

#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


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

			/* new line */
			static void newline(void);

			/* write unknown bytes */
			static void write(const char* str);

			/* write bytes */
			static void write(const char* str, const xns::size_t size);

			/* write character */
			template <xns::is_char T>
			static void write(const T& ch) {
				// call buffer write
				write(&ch, sizeof(T));
			}

			/* write string */
			static void write(const xns::string& str);

			/* write string32 */
			static void write(const xns::string32& str);

			/* render */
			template <xns::string_literal L = "stdout">
			static void render(void) {

				static_assert(L == "stdout" || L == "stderr",
							  "): UNKNOWN FILE DESCRIPTOR :(");

				constexpr int fd = (L == "stdout") ? STDOUT_FILENO : STDERR_FILENO;

				// do nothing if buffer is empty
				if (_instance._buffer.empty()) { return; }

				// write buffer to file descriptor
				(void)::write(fd, _instance._buffer.pointer(),
								  _instance._buffer.size());

				// clear buffer
				_instance._buffer.clear();
			}

			/*
			template <class... A>
			static void print(const A&... args) {
				// write each argument
				(void)(write(args), ...);
			}*/

			template <xns::is_integral T>
			static void write(const T& number) {

				// convert number to string
				xns::string str = xns::conversion::integer_to_string(number);

				// write string
				write(str);
			}







		private:

			// -- P R I V A T E  E N U M S ------------------------------------

			/* buffer size */
			enum : xns::size_t { DEFAULT_BUFFER_SIZE = 1024 };


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* buffers */
			xns::string _buffer;


			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* instance */
			static output _instance;


	};




}




#endif