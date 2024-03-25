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

#ifndef XNS_FILE_HEADER
#define XNS_FILE_HEADER

// local headers
#include "xns/string/string.hpp"
#include "xns/system/unique_descriptor.hpp"

// operating system headers
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I L E -------------------------------------------------------------

	template <decltype(sizeof(0)) S = 1024>
	class file final : public xns::unique_descriptor {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::file<S>;

			/* size type */
			using size_type = decltype(S);

			/* signed type */
			using signed_type = decltype(::read(0, nullptr, 0));


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline file(void) noexcept
			: xns::unique_descriptor{}, _buffer{}, _readed{0} {
			}

			/* variadic constructor */
			template <typename... __params>
			inline file(const xns::string& __path, __params&&... __args) noexcept
			: xns::unique_descriptor{::open(__path.data(), xns::forward<__params>(__args)...)},
			  _buffer{}, _readed{0} {
			}

			/* not copyable class */
			XNS_NOT_COPYABLE(file);

			/* move constructor */
			inline file(self&& other) noexcept = default;

			/* destructor */
			~file(void) noexcept = default;


			// -- public methods ----------------------------------------------
			
			/* read */
			inline auto read(void) noexcept -> size_type {
				// read descriptor
				const signed_type readed = static_cast<signed_type>(::read(*this, _buffer, S));
				// assign readed bytes
				_readed = static_cast<size_type>(readed > 0 ? readed : 0);
				// return readed bytes
				return _readed;
			}

			/* readed */
			inline auto readed(void) const noexcept -> size_type {
				return _readed;
			}



			// -- public subscript operators ----------------------------------

			/* subscript operator */
			inline auto operator[](const size_type index) const noexcept -> char {
				return _buffer[index];
			}


		private:

			// -- private members ---------------------------------------------

			/* buffer */
			char _buffer[S];

			/* readed bytes */
			size_type _readed;

	}; // class file

} // namespace xns

#endif // XNS_FILE_HEADER
