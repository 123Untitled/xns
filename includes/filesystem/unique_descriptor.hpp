#pragma once

#ifndef XNS_UNIQUE_DESCRIPTOR_HEADER
#define XNS_UNIQUE_DESCRIPTOR_HEADER

// local headers
#include "types.hpp"
#include "allocator.hpp"
#include "macros.hpp"
#include "string.hpp"

// operating system headers
#include <fcntl.h>
#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T R U S T  T A G  S T R U C T ---------------------------------------

	//struct trust {
	//
	//	/* trust constructor */
	//	explicit constexpr trust(void) noexcept = default;
	//
	//};


	// -- forward declarations ------------------------------------------------

	/* file class */
	template <decltype(sizeof(0))>
	class file;


	// -- U N I Q U E  D E S C R I P T O R  -----------------------------------

	/* unique descriptor */
	class unique_descriptor {


		// -- friends ---------------------------------------------------------

		/* file class as friend */
		//template <decltype(sizeof(0))>
		//friend class file;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::unique_descriptor;

			/* id type */
			using id_type = int;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline unique_descriptor(void) noexcept
			: _descriptor{NULL_DESCRIPTOR} {}

			/* descriptor constructor */
			inline unique_descriptor(const id_type& descriptor) noexcept
			: _descriptor{descriptor} {
			//: _descriptor{self::check_descriptor(descriptor)} {
			}

			/* non-copyable class */
			non_copyable(unique_descriptor);

			/* move constructor */
			inline unique_descriptor(self&& other) noexcept
			: _descriptor{other._descriptor} {
				// invalidate other
				other._descriptor = NULL_DESCRIPTOR;
			}

			/* destructor */
			inline ~unique_descriptor(void) noexcept {
				// close descriptor
				this->close_descriptor();
			}


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// check for self assignment
				if (this == &other) { return *this; }
				// close descriptor
				close_descriptor();
				// set descriptor
				_descriptor = other._descriptor;
				// invalidate other
				other._descriptor = NULL_DESCRIPTOR;
				// return self reference
				return *this;
			}

			/* descriptor assignment operator */
			inline auto operator=(const id_type& descriptor) noexcept -> self& {
				_descriptor = descriptor;
				// set descriptor
				//_descriptor = self::check_descriptor(descriptor);
				// return self reference
				return *this;
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
				// return descriptor validity
				return _descriptor != NULL_DESCRIPTOR;
			}

			/* not operator */
			inline bool operator!(void) const noexcept {
				// return descriptor invalidity
				return _descriptor == NULL_DESCRIPTOR;
			}


			// -- public conversion operators -----------------------------

			/* descriptor conversion operator */
			inline operator id_type(void) const noexcept {
				// return descriptor
				return _descriptor;
			}


			// -- public comparison operators -----------------------------

			/* equality operator */
			inline auto operator==(const self& other) const noexcept -> bool {
				// return descriptor equality
				return _descriptor == other._descriptor;
			}

			/* inequality operator */
			inline auto operator!=(const self& other) const noexcept -> bool {
				// return descriptor inequality
				return _descriptor != other._descriptor;
			}


			// -- public accessors ----------------------------------------

			/* is valid */
			inline auto valid(void) const noexcept -> bool {
				// return descriptor validity
				return _descriptor != NULL_DESCRIPTOR;
			}

			/* is invalid */
			inline auto invalid(void) const noexcept -> bool {
				// return descriptor invalidity
				return _descriptor == NULL_DESCRIPTOR;
			}

			/* get descriptor */
			inline auto get(void) const noexcept -> const id_type& {
				// return descriptor
				return _descriptor;
			}


			// -- public modifiers --------------------------------------------

			/* reset descriptor */
			inline auto reset(void) noexcept -> void {
				// close descriptor
				this->close_descriptor();
				// invalidate descriptor
				_descriptor = NULL_DESCRIPTOR;
			}

			/* set descriptor */
			inline auto set(const id_type& descriptor) noexcept -> void {
				// close descriptor
				this->close_descriptor();
				// set descriptor
				_descriptor = descriptor;
			}




		private:

			// -- private lifecycle -------------------------------------------

			///* private trusted constructor */
			//inline unique_descriptor(const trust, const id_type& descriptor) noexcept
			//: _descriptor{descriptor} {}


			// -- private methods ---------------------------------------------

			/* close descriptor */
			inline auto close_descriptor(void) noexcept -> void {
				// check for valid descriptor
				if (_descriptor != NULL_DESCRIPTOR) {
					// close descriptor
					if (::close(_descriptor) == -1) {
						// error
					}
				}
			}

			/* check descriptor */
			//static inline auto check_descriptor(const id_type& descriptor) noexcept -> unique_descriptor::id_type {
			//	// check if descriptor is valid
			//	return (::fcntl(descriptor, F_GETFD) != -1 || errno != EBADF)
			//		? descriptor : NULL_DESCRIPTOR;
			//}


			// -- private enums -----------------------------------------------

			/* descriptor type */
			enum : id_type { NULL_DESCRIPTOR = -1 };


			// -- private members ---------------------------------------------

			/* descriptor */
			id_type _descriptor;

	}; // class unique_descriptor

} // namespace xns

#endif // XNS_UNIQUE_DESCRIPTOR_HEADER
