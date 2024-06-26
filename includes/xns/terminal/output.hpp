/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_OUTPUT_HEADER
#define XNS_OUTPUT_HEADER

// xns headers
#include "xns/config/macros.hpp"
#include "xns/type_traits/types.hpp"
#include "xns/string/string.hpp"
#include "xns/type_traits/other/string_literal.hpp"
#include "xns/type_traits/type_categories/is_floating_point.hpp"

// operating system headers
#include <unistd.h>

// c++ standard library headers
#include <sstream>




// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	struct flush final {
		non_instanciable(flush);
	};

	struct buffered final {
		non_instanciable(buffered);
	};


	// -- O U T  C L A S S ----------------------------------------------------

	class out final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::out;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			out(void);

			/* non-assignable class */
			___xns_not_assignable(out);

			/* destructor */
			~out(void) noexcept = default;


			// -- private static methods --------------------------------------

			/* shared */
			static auto shared(void) -> ___self&;


		public:



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
				// append character to buffer
				___self::shared()._buffer.append(ch);
			}

			/* write float / double */
			template <xns::is_floating_point T>
			static void write(const T& number) {
				std::stringstream ss;

				ss << number;
				___self::shared()._buffer.append(ss.str().c_str(), ss.str().size());

			}

			/* write string */
			static void write(const xns::string& str);

			/* write string view */
			static void write(const xns::string_view& str);

			/* write string32 */
			static void write(const xns::u32string& str);

			/* render */
			template <xns::basic_string_literal L = "stdout">
			static void render(void) {

				static_assert(L == "stdout" || L == "stderr",
							  "): UNKNOWN FILE DESCRIPTOR :(");

				constexpr int fd = (L == "stdout") ? STDOUT_FILENO : STDERR_FILENO;

				auto& ___out = ___self::shared();

				// do nothing if buffer is empty
				if (___out._buffer.empty()) { return; }

				// write buffer to file descriptor
				static_cast<void>(::write(fd, ___out._buffer.data(),
								  ___out._buffer.size()));

				// clear buffer
				___out._buffer.clear();
			}

			/*
			template <class... A>
			static void print(const A&... args) {
				// write each argument
				(void)(write(args), ...);
			}*/

			template <xns::is_integral T> requires (xns::is_char<T> == false)
			static void write(const T& number) {

				// convert number to string
				xns::string str = xns::to_string(number);

				// write string
				xns::out::write(str);
			}







		private:

			// -- friends -----------------------------------------------------

			/* print as friend */
			template <typename... A>
			friend auto print(const A&... args) -> void;

			/* println as friend */
			template <typename... A>
			friend auto println(const A&... args) -> void;

			template <typename T, typename... A> requires (xns::is_same<T, flush> || xns::is_same<T, buffered>)
			friend auto println(const A&... args) -> void;


			// -- P R I V A T E  E N U M S ------------------------------------

			/* buffer size */
			enum : xns::size_t { DEFAULT_BUFFER_SIZE = 1024 };


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* buffers */
			xns::string _buffer;

	};



	template <typename... A>
	auto print(const A&... args) -> void {
		// write each argument
		(out::write(args), ...);
	}

	template <typename... A>
	auto println(const A&... args) -> void {
		// write each argument
		(out::write(args), ...);
		// get out instance
		auto& out = out::shared();
		// append new line
		out._buffer.append('\n');
	}

	template <typename T, typename... A> requires (xns::is_same<T, flush> || xns::is_same<T, buffered>)
	auto println(const A&... args) -> void {
		// write each argument
		(out::write(args), ...);
		// get out instance
		auto& out = out::shared();
		// append new line
		out._buffer.append('\n');

		if constexpr (xns::is_same<T, flush>) {
			// render buffer
			out::render();
		}
	}


}




#endif
