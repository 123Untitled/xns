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

#ifndef XNS_SHARED_MEMORY_HEADER
#define XNS_SHARED_MEMORY_HEADER

#include "xns/system/unique_descriptor.hpp"
#include "xns/diagnostics/exceptions.hpp"

#include <sys/mman.h>
#include <sys/shm.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S H A R E D  M E M O R Y --------------------------------------------

	template <typename ___type>
	class shared_memory final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::shared_memory<___type>;

			/* value type */
			using value_type = ___type;

			/* size type */
			using size_type = xns::size_t;

			/* pointer type */
			using mut_ptr = value_type*;

			/* const pointer type */
			using const_ptr = const value_type*;

			/* reference type */
			using mut_ref = value_type&;

			/* const reference type */
			using const_ref = const value_type&;

			/* move reference type */
			using move_ref = value_type&&;



			// -- public lifecycle --------------------------------------------

			/* path constructor */
			template <typename... ___params>
			shared_memory(___params&&... args)
			: _shm_fd{::shm_open(xns::forward<___params>(args)...)},
			  _data{nullptr} {

				// check for error
				if (not _shm_fd)
					throw xns::exception{"shm_open failed", errno};

				// set size
				if (::ftruncate(_shm_fd, sizeof(value_type)) == -1)
					throw xns::exception{"ftruncate failed", errno};

				// map memory
				_data = static_cast<mut_ptr>(
					  ::mmap(nullptr, sizeof(value_type), PROT_READ | PROT_WRITE, MAP_SHARED,
							 _shm_fd, 0)
				);

				// check for error
				if (_data == MAP_FAILED)
					throw xns::exception{"mmap failed", errno};
			}

			/* deleted copy constructor */
			shared_memory(const self&) = delete;

			/* move constructor */
			shared_memory(self&& other) noexcept
			: _shm_fd{xns::move(other._shm_fd)},
			  _data{other._data} {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			~shared_memory(void) noexcept {
				if (_data == nullptr) return;
				// unmap memory
				::munmap(_data, sizeof(value_type));
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				// check for self assignment
				if (this == &other) { return *this; }

				// unmap memory
				if (_data != nullptr)
					::munmap(_data, sizeof(value_type));

				// set descriptor
				_shm_fd = xns::move(other._shm_fd);
				// set data
				_data = other._data;
				// invalidate other
				other._data = nullptr;
				// return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* data */
			inline auto data(void) noexcept -> mut_ptr {
				return _data;
			}

			/* data */
			inline auto data(void) const noexcept -> const_ptr {
				return _data;
			}

			/* operator -> */
			inline auto operator->(void) noexcept -> mut_ptr {
				return _data;
			}

			/* operator -> */
			inline auto operator->(void) const noexcept -> const_ptr {
				return _data;
			}

			/* operator * */
			inline auto operator*(void) noexcept -> mut_ref {
				return *_data;
			}

			/* operator * */
			inline auto operator*(void) const noexcept -> const_ref {
				return *_data;
			}


		private:

			// -- private members ---------------------------------------------

			/* shm descriptor */
			xns::unique_descriptor _shm_fd;

			/* data */
			mut_ptr _data;

	}; // class shared_memory

} // namespace xns

#endif // XNS_SHARED_MEMORY_HEADER
