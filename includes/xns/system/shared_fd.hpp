#ifndef XNS_SHARED_DESCRIPTOR_HEADER
#define XNS_SHARED_DESCRIPTOR_HEADER

// local headers
#include "xns/type_traits/types.hpp"
#include "xns/memory/allocator.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S H A R E D  D E S C R I P T O R ------------------------------------

	class shared_descriptor {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = shared_descriptor;

			/* descriptor type */
			using descriptor = int;

			/* size type */
			using size_type = xns::size_t;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline shared_descriptor(void) noexcept
			: _descriptor{NULL_DESCRIPTOR}, _count{nullptr} {}

			/* descriptor constructor */
			inline shared_descriptor(const descriptor& descriptor)
			: _descriptor{check_descriptor(descriptor)}, _count{nullptr} {

				if (_descriptor != NULL_DESCRIPTOR) {
					_count = xns::allocator<size_type>::allocate();
					*_count = 1;
				}
			}

			/* copy constructor */
			inline shared_descriptor(const self& other) noexcept
			: _descriptor{other._descriptor}, _count{other._count} {
				if (_descriptor != NULL_DESCRIPTOR) {
					++(*_count);
				}
			}

			/* move constructor */
			shared_descriptor(self&& other) noexcept
			: _descriptor{other._descriptor}, _count{other._count} {
				other._descriptor = NULL_DESCRIPTOR;
				other._count = nullptr;
			}

			/* destructor */
			~shared_descriptor(void) noexcept {
				close_descriptor();
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) noexcept -> self& {
				if (this != &other) {
					close_descriptor();
					_descriptor = other._descriptor;
					_count = other._count;
					if (_descriptor != NULL_DESCRIPTOR) {
						++(*_count);
					}
				}
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				if (this != &other) {
					close_descriptor();
					_descriptor = other._descriptor;
					_count = other._count;
					other._descriptor = NULL_DESCRIPTOR;
					other._count = nullptr;
				}
				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* descriptor conversion operator */
			inline operator int(void) const noexcept {
				return _descriptor;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline auto operator==(const self& other) const noexcept -> bool {
				return _descriptor == other._descriptor;
			}

			/* inequality operator */
			inline auto operator!=(const self& other) const noexcept -> bool {
				return _descriptor != other._descriptor;
			}


			// -- public accessor ---------------------------------------------

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
			inline auto get(void) const noexcept -> const descriptor& {
				// return descriptor
				return _descriptor;
			}


			// -- public modifiers ----------------------------------------

			/* reset descriptor */
			inline auto reset(void) noexcept -> void {
				// close descriptor
				close_descriptor();
				// invalidate descriptor
				_descriptor = NULL_DESCRIPTOR;
				// invalidate count
				_count = nullptr;
			}


		private:

			// -- private methods ---------------------------------------------

			/* check descriptor */
			inline auto check_descriptor(const descriptor& descriptor)
				noexcept -> shared_descriptor::descriptor {
				// check if descriptor is valid
				return (::fcntl(descriptor, F_GETFD) != -1 || errno != EBADF)
					? descriptor : NULL_DESCRIPTOR;
			}

			/* close descriptor */
			inline auto close_descriptor(void) noexcept -> void {
				// check for valid descriptor
				if (_descriptor != NULL_DESCRIPTOR) {
					if (--(*_count) == 0) {
						::close(_descriptor);
						xns::allocator<size_type>::deallocate(_count);
					}
				}
			}


			// -- private enums -----------------------------------------------

			/* descriptor type */
			enum { NULL_DESCRIPTOR = -1 };


			// -- private members ---------------------------------------------

			/* descriptor */
			descriptor _descriptor;

			/* count */
			size_type* _count;

	};


}


#endif






