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

#ifndef XNS_MEMORY_HEADER
#define XNS_MEMORY_HEADER

// local headers
#include "xns/config/os.hpp"
#include "xns/type_traits/types.hpp"
#include "xns/diagnostics/exceptions.hpp"
#include "xns/config/macros.hpp"
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

#include "xns/type_traits/type_properties/is_trivially_copyable.hpp"

#include "xns/type_traits/supported_operations/is_constructible.hpp"
#include "xns/type_traits/supported_operations/is_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_destructible.hpp"
#include "xns/type_traits/supported_operations/is_trivially_destructible.hpp"
#include "xns/type_traits/supported_operations/is_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_move_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_destructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_assignable.hpp"

// operating system headers
#include <unistd.h>
#include <sys/mman.h>

//#include <sys/syscall.h>

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	// -- M E M O R Y ---------------------------------------------------------

	class memory final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = xns::size_t;


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			non_instantiable(memory);


		private:

			// -- private enums -----------------------------------------------

			/* mmap flags */
			enum : int {
				M_PROTECTION =   PROT_READ | PROT_WRITE,
				M_FLAGS      = MAP_PRIVATE | MAP_ANONYMOUS
			};

			/* memory constants */
			enum : size_type {
				ALIGNMENT = sizeof(void*),
				DEFAULT_PAGE_SIZE = 4096
			};


		public:

			// -- private static methods --------------------------------------

			/* map */
			static inline auto map(const size_type size = page_size(), void* addr = nullptr) noexcept(xns::no_exceptions) -> void* {
				// map memory
				void* ptr = ::mmap(addr, size, M_PROTECTION, M_FLAGS, -1, 0);

				if constexpr (xns::no_exceptions == false)
					if (ptr == MAP_FAILED)
						throw xns::exception(-2, "mmap failed");

				return ptr;
			}

			/* unmap */
			static inline auto unmap(void* ptr, const size_type size) noexcept -> void {
				// not good idea to throw exception in destructor
				::munmap(ptr, size);
			}

			/* page size */
			static inline auto page_size(void) -> size_type {
				static const size_type page_size = [](void) noexcept -> size_type {
					const auto size = ::sysconf(_SC_PAGESIZE);
					return size > 0 ? static_cast<size_type>(size) : DEFAULT_PAGE_SIZE;
				}();
				return page_size;
			}

			/* padding */
			template <typename T>
			static consteval auto padding(void) noexcept -> decltype(sizeof(void*)) {
				// padding
				return (ALIGNMENT - (sizeof(T) & (ALIGNMENT - 1))) & (ALIGNMENT - 1);
				// alternative: (-sizeof(T)) & (sizeof(void*) - 1);
			}

			/* align */
			static inline auto align(const size_type size) noexcept -> size_type {
				return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
			}

			/* power of two padding */
			template <typename T>
			static consteval auto padding_power(void) noexcept -> decltype(sizeof(void*)) {
				xns::size_t align = 1;
				while (align < sizeof(T))
					align <<= 1;
				return align - sizeof(T);
			}

	}; // class memory

} // namespace xns





namespace xns {


	// -- M E M O R Y  C L A S S ----------------------------------------------

	class memory2 final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = xns::size_t;


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			uninstantiable(memory2);


		public:

			// -- private enums -----------------------------------------------

			/* mmap flags */
			enum : int {
				M_PROTECTION =   PROT_READ | PROT_WRITE,
				M_FLAGS      = MAP_PRIVATE | MAP_ANONYMOUS
			};

			/* default page size */
			enum : size_type {
				DEFAULT_PAGE_SIZE = 4096
			};


			// -- private static methods --------------------------------------

			/* map */
			static inline auto map(const size_type size = page_size(), void* addr = nullptr) noexcept(xns::no_exceptions) -> void* {
				// map memory
				void* ptr = ::mmap(addr, size, M_PROTECTION, M_FLAGS, -1, 0);

				if constexpr (xns::no_exceptions == false)
					if (ptr == MAP_FAILED)
						throw xns::exception(-2, "mmap failed");

				return ptr;
			}

			/* unmap */
			static inline auto unmap(void* ptr, const size_type size) noexcept -> void {
				::munmap(ptr, size);
				// not good idea to throw exception in destructor
			}

			/* page size */
			static inline auto page_size(void) -> size_type {
				static const size_type page_size = init_page_size();
				//std::cout << "page size: " << (page_size << 4) << std::endl;
				return page_size;
				//return page_size << 4;
			}

			/* system page size */
			static inline auto init_page_size(void) noexcept -> size_type {
				if (const auto page_size = ::sysconf(_SC_PAGESIZE); page_size > 0)
					return static_cast<size_type>(page_size);
				return DEFAULT_PAGE_SIZE;
			}

			/* padding */
			template <typename T>
			static consteval auto padding(void) noexcept -> decltype(sizeof(void*)) {
				// size of type
				constexpr size_type size = sizeof(T);
				// memory block alignment
				constexpr size_type align = sizeof(void*);
				// padding
				return (align - (size & (align - 1))) & (align - 1);
				// alternative: (-sizeof(T)) & (sizeof(void*) - 1);
			}

			/* power of two padding */
			template <typename T>
			static consteval auto padding_power(void) noexcept -> decltype(sizeof(void*)) {
				xns::size_t align = 1;
				while (align < sizeof(T))
					align <<= 1;
				return align - sizeof(T);
			}


			// -- pool implementation -----------------------------------------
			// dumb fast fixed size pool allocator
			// advantage: speed allocation and deallocation
			// cons: cannot give back memory to system

			template <size_type N>
			class pool_impl final {


				public:

					// -- public types ----------------------------------------

					/* self type */
					using self = xns::memory2::pool_impl<N>;


				private:

					// -- forward declarations --------------------------------

					struct page;
					struct chunk;


					// -- private types ---------------------------------------

					/* page pointer type */
					using page_ptr = page*;

					/* chunk pointer type */
					using chunk_ptr = chunk*;

					/* void pointer type */
					using void_ptr = void*;


					// -- chunk -----------------------------------------------

					struct chunk final {

						// -- public lifecycle --------------------------------

						/* non-instantiable class */
						uninstantiable(chunk);

						// -- public members ----------------------------------

						/* next chunk */
						chunk_ptr _next;
					};


					// -- page ------------------------------------------------

					struct alignas(sizeof(void*)) page final {

						// -- public types ------------------------------------

						/* self type */
						using self = pool_impl<N>::page;


						// -- public lifecycle --------------------------------

						/* default constructor */
						inline page(const size_type capacity) noexcept
						: _capacity{capacity}, _next{nullptr} {

							auto nchunks = (_capacity - sizeof(self)) / N;

							auto ptr  = data();
							auto last = (ptr + (N * (nchunks - 1)));


							while (ptr < last) {
								reinterpret_cast<chunk_ptr>(ptr)->_next = reinterpret_cast<chunk_ptr>(ptr + N);
								ptr += N;
							}
							// set last chunk next pointer to nul
							reinterpret_cast<chunk_ptr>(ptr)->_next = nullptr;

						}

						/* destructor */
						inline ~page(void) noexcept = default;


						// -- public accessors --------------------------------

						/* chunks */
						inline auto chunks(void) noexcept -> chunk_ptr {
							return reinterpret_cast<chunk_ptr>(this + 1);
						}

						/* data */
						inline auto data(void) noexcept -> xns::ubyte* {
							return reinterpret_cast<xns::ubyte*>(this + 1);
						}

						/* capacity */
						inline auto capacity(void) const noexcept -> size_type {
							return _capacity;
						}


						// -- public modifiers --------------------------------

						/* extend */
						inline auto extend(void) noexcept -> void {
							auto ncap = _capacity;// << 1;
							_next = new (xns::memory2::map(ncap)) page{ncap};
						}


						// -- public members ----------------------------------

						/* capacity */
						size_type _capacity;

						/* next page */
						page_ptr _next;

						/* first chunk */
						chunk_ptr _chunks;

					};



					// -- private lifecycle -----------------------------------

					/* default constructor */
					inline pool_impl(void) noexcept
					:	_head{new (xns::memory2::map()) page{xns::memory2::page_size()}},
						_tail{_head},
						_current{_head->chunks()} {}

					/* non-assignable class */
					unassignable(pool_impl);

					/* destructor */
					inline ~pool_impl(void) noexcept {
						// get head page
						auto ptr = _head;
						// loop over pages
						while (ptr != nullptr) {
							auto next = ptr->_next;
							xns::memory2::unmap(ptr, ptr->capacity());
							ptr = next;
						}
					}


					// -- private members -------------------------------------

					/* head page */
					page_ptr _head;

					/* tail page */
					page_ptr _tail;

					/* available chunk */
					chunk_ptr _current;


				public:

					// -- public accessors ------------------------------------

					/* instance */
					static inline auto shared(void) -> self& {
						// static instance
						static self instance;
						return instance;
					}


					// -- public static methods -------------------------------



					/* allocate */
					static inline auto allocate(void) -> void_ptr {
						// get instance
						self& pool = shared();

						chunk_ptr ch = pool._current;

						if (ch->_next == nullptr) {
							pool._tail->extend();
							pool._tail = pool._tail->_next;
							pool._current = pool._tail->chunks();
						}
						else {
							pool._current = ch->_next;
						}

						return static_cast<void_ptr>(ch);
					}


					/* deallocate */
					static inline auto deallocate(void* ptr) -> void {
						// cast pointer to chunk
						chunk_ptr ch = static_cast<chunk_ptr>(ptr);
						// set next pointer to current chunk
						ch->_next = shared()._current;
						// set current chunk to deallocated chunk
						shared()._current = ch;
					}

			};



		public:


			template <typename T>
			class pool final {


				private:

					// -- private types ---------------------------------------

					/* allocator type */
					using allocator = xns::memory2::pool_impl<
						  sizeof(T) + xns::memory2::padding<T>()>;


				public:

					// -- public types ----------------------------------------

					/* self type */
					using self      = xns::memory2::pool<T>;

					/* value type */
					using type      = T;

					/* reference type */
					using mut_ref   = type&;

					/* move reference type */
					using move_ref  = type&&;

					/* const reference type */
					using const_ref = const type&;

					/* pointer type */
					using mut_ptr   = type*;

					/* const pointer type */
					using const_ptr = const type*;


					// -- public lifecycle ------------------------------------

					/* non-instantiable class */
					uninstantiable(pool);


					// -- public static methods -------------------------------

					/* init memory (force lazy initialization) */
					static inline auto init(void) -> void {
						self::allocator::shared();
					}


					// -- public allocation methods ---------------------------

					/* allocate */
					static inline auto allocate(void) -> mut_ptr {
						return static_cast<mut_ptr>(allocator::allocate());
					}

					/* deallocate */
					static inline auto deallocate(mut_ptr addr) noexcept -> void {
						allocator::deallocate(addr);
					}


					// -- public construction methods -------------------------

					/* copy construct */
					static inline auto construct(mut_ptr addr, const_ref value) -> void {
						// check type is copy constructible
						static_assert(xns::is_copy_constructible<type>,
							"TYPE IS NOT CONSTRUCTIBLE");
						// construct object by copy
						new (addr) type{value};
					}

					/* move construct */
					static inline auto construct(mut_ptr addr, move_ref value) -> void {
						// check type is move constructible
						static_assert(xns::is_move_constructible<type>,
							"TYPE IS NOT CONSTRUCTIBLE");
						// construct object by move
						new (addr) type{xns::move(value)};
					}

					/* forward construct */
					template <typename... A>
					static inline auto construct(mut_ptr addr, A&&... args) -> void {
						// check type is constructible
						static_assert(xns::is_constructible<type, A...>,
							"TYPE IS NOT CONSTRUCTIBLE");
						// construct object by forwarding arguments
						new (addr) type{xns::forward<A>(args)...};
					}

					/* destroy */
					static inline auto destroy(mut_ptr addr) noexcept -> void {
						// check type is trivially destructible
						if constexpr (xns::is_trivially_destructible<type> == false) {
							// check type is destructible
							static_assert(xns::is_destructible<type>,
									"TYPE IS NOT DESTRUCTIBLE");
							// call object destructor
							addr->~type();
						}
					}

			};

	};



	// locality implementation
	// fixed size pool allocator with locality
	// advantage: good memory locality
	// cons: slow allocation and deallocation



	template <typename T>
	class locality final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::locality<T>;

			/* size type */
			using size_type = decltype(sizeof(void*));

			/* mutable pointer type */
			using mut_ptr = T*;

			/* const pointer type */
			using const_ptr = const T*;


		private:


			class chunk final {

				public:

					// metadata only contains pointers to next and previous chunks
					struct alignas(sizeof(void*)) meta final {

						meta(void) = delete;

						inline meta(chunk* nc, chunk* pc, chunk* na, chunk* pa) noexcept
							: _nc{nc}, _pc{pc}, _na{na}, _pa{pa} {}

						unassignable(meta);

						/* data */
						chunk *_nc, *_pc, *_na, *_pa;
					};

					struct first final {};
					struct last  final {};

					chunk(void) noexcept
					: _meta{this + 1, this - 1, this + 1, this - 1} {}

					chunk(chunk::first) noexcept
					: _meta{this + 1, nullptr, this + 1, nullptr} {}

					chunk(chunk::last) noexcept
					: _meta{nullptr, this - 1, nullptr, this - 1} {}



					inline auto next_available(void) noexcept -> chunk* {
						return _meta._na;
					}

					inline auto next_available(chunk* na) noexcept -> void {
						_meta._na = na;
					}

					inline auto prev_available(void) noexcept -> chunk* {
						return _meta._pa;
					}

					inline auto prev_available(chunk* pa) noexcept -> void {
						_meta._pa = pa;
					}

					inline auto data(void) noexcept -> mut_ptr {
						return reinterpret_cast<mut_ptr>(_data);
					}


					// -- members ---------------------------------------------

					/* metadata */
					meta _meta;

					/* data */
					alignas(alignof(T)) xns::ubyte _data[sizeof(T)];

			};


			class alignas(sizeof(void*)) block final {

				private:

					// -- private types ---------------------------------------

					/* self type */
					using self = xns::locality<T>::block;


				public:


					inline block(const size_type capacity) noexcept
						:	_capacity{capacity},
						_next{nullptr}, _prev{nullptr},
						_chunks{reinterpret_cast<chunk*>(this + 1)} {

							typename chunk::first first{};

							// construct first chunk
							new (_chunks) chunk{first};

							// compute number of chunks
							const size_type nchunks = (capacity - sizeof(self)) / sizeof(chunk);

							typename chunk::last last{};

							// construct last chunk
							new (_chunks + (nchunks - 1)) chunk{last};

							// construct chunks
							for (size_type i = 1; i < nchunks - 1; ++i) {
								new (_chunks + i) chunk{};
							}

						}

					/* capacity */
					inline auto capacity(void) const noexcept -> size_type {
						return _capacity;
					}

					/* next block */
					inline auto next(void) const noexcept -> self* {
						return _next;
					}

					/* prev block */
					inline auto prev(void) const noexcept -> self* {
						return _prev;
					}

					/* extend */
					inline auto extend(void) noexcept -> void {
						auto ncap = _capacity << 1;
						_next = new (xns::memory2::map(ncap)) self{ncap};
					}

					/* chunks */
					inline auto chunks(void) noexcept -> chunk* {
						return _chunks;
					}


				private:

					// -- members ---------------------------------------------

					/* capacity */
					size_type _capacity;

					/* next block */
					block* _next;

					/* prev block */
					block* _prev;

					/* chunks */
					chunk* _chunks;

			};


			// -- private methods ---------------------------------------------

			/* metadata accessors */
			inline auto metadata(mut_ptr addr) -> chunk* {
				chunk* ch = reinterpret_cast<chunk*>(
						reinterpret_cast<xns::ubyte*>(addr) - sizeof(typename self::chunk::meta));

				#if XNS_EXCEPTIONS
				if (ch->data() != addr)
					throw xns::exception(-2, "invalid address");
				#endif

				return ch;
			}

			/* extend */
			inline auto extend(void) noexcept -> void {
				_tail->extend();
				_tail = _tail->next();
			}


		public:



			// -- public lifecycle --------------------------------------------

			/* non-assignable class */
			unassignable(locality);

			static inline auto shared(void) -> self& {
				static self instance;
				return instance;
			}


			// -- public static methods ---------------------------------------

			/* allocate */
			static auto allocate(mut_ptr hint = nullptr) -> mut_ptr {

				// get instance
				self& sshared = shared();

				if (hint == nullptr) {
					// to be implemented...
				}

				chunk* ch = sshared.metadata(hint);

				if (ch->next_available()) {
					chunk* next = ch->next_available();
					ch->next_available(next->next_available());
					return next->data();
				}
				else if (ch->prev_available()) {
					chunk* prev = ch->prev_available();
					ch->prev_available(prev->prev_available());
					return prev->data();
				}

				// extend
				sshared.extend();
				ch = sshared._tail->chunks();


				return nullptr;
			}




		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			inline locality(void)
				: _head{new (xns::memory2::map()) self::block{xns::memory2::page_size()}}, _tail{_head} {
				}

			/* destructor */
			inline ~locality(void) noexcept(false) {
				// get head page
				auto ptr = _head;
				// loop over pages
				while (ptr != nullptr) {
					auto next = ptr->next();
					xns::memory2::unmap(ptr, ptr->capacity());
					ptr = next;
				}
			}


			// -- private members ---------------------------------------------

			/* head block */
			block* _head;

			/* tail block */
			block* _tail;

	};






	///////////////////////////////////////////////////////////////////////////

	// test:
	// reinterpret block as balanced binary tree
	template <typename T>
	inline auto reinterpret_block(void) -> void {

		const xns::size_t size = xns::memory2::page_size();

		void* ptr = xns::memory2::map(size);

		struct node final {
			xns::ubyte data[sizeof(T)];
			node* left;
			node* right;
		};

		struct page final {
			xns::size_t size;
			node* root;
		};

		const xns::size_t avail = size - sizeof(page);
		const xns::size_t nnode = avail / sizeof(node);









	}


}

#endif // MEMORY_HEADER
