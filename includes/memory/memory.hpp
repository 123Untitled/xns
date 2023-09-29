#ifndef XNS_MEMORY_HEADER
#define XNS_MEMORY_HEADER

// local headers
#include "os.hpp"
#include "types.hpp"
#include "exceptions.hpp"
#include "macros.hpp"
#include "is_constructible.hpp"
#include "is_destructible.hpp"
#include "is_trivially_destructible.hpp"

// operating system headers
#include <unistd.h>
#include <sys/mman.h>

//#include <sys/syscall.h>

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M O R Y  C L A S S ----------------------------------------------

	class memory final {


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = xns::size_t;


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(memory);


		private:

			// -- private enums -----------------------------------------------

			/* mmap flags */
			enum : int {
				M_PROTECTION =   PROT_READ | PROT_WRITE,
				M_FLAGS      = MAP_PRIVATE | MAP_ANONYMOUS
			};


			// -- private static methods --------------------------------------


			/* map */
			static inline auto map(const size_type size = page_size()) -> void* {
				//std::cout << "mmap allocate: " << size << std::endl;
				void* ptr = ::mmap(nullptr, size, M_PROTECTION, M_FLAGS, -1, 0);
				if (ptr == MAP_FAILED)
					throw xns::exception(-2, "mmap failed");
				return ptr;
			}

			/* unmap */
			static inline auto unmap(void* ptr, const size_type size) -> void {
				if (::munmap(ptr, size) == -1)
					throw xns::exception(-2, "munmap failed");
			}

			/* page size */
			static inline auto page_size(void) noexcept -> size_type {
				static const size_type page_size = init_page_size();
				return page_size;
			}

			/* system page size */
			static inline auto init_page_size(void) -> size_type {
				if (auto page_size = ::sysconf(_SC_PAGESIZE); page_size > 0) {
					return static_cast<size_type>(page_size);
				}
				throw xns::exception(-2, "sysconf failed");
			}

			/* padding */
			template <typename T>
			static consteval auto padding(void) noexcept -> decltype(sizeof(void*)) {
				// return padding
				return (-sizeof(T)) & (sizeof(void*) - 1);
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

			template <size_type N>
			class pool_impl final {


				public:

					// -- public types ----------------------------------------

					/* self type */
					using self = xns::memory::pool_impl<N>;


				private:

					// -- chunk -----------------------------------------------

					struct chunk final {


						// -- public types ------------------------------------

						/* pointer type */
						using pointer = chunk*;


						// -- public lifecycle --------------------------------

						/* non-instanciable class */
						NON_INSTANCIABLE(chunk);


						// -- public members ----------------------------------

						/* next chunk */
						pointer next;

					};


					// -- page ------------------------------------------------

					struct alignas(sizeof(xns::addr_t)) page final {

						// -- public types ------------------------------------

						/* self type */
						using self = pool_impl<N>::page;

						/* pointer type */
						using pointer = self*;



						// -- public lifecycle --------------------------------

						/* default constructor */
						inline page(const size_type capacity) noexcept
						: size{capacity}, next{nullptr} {

							auto nchunks = (size - sizeof(self)) / N;

							auto last = (reinterpret_cast<xns::ubyte*>(this) + (N * nchunks)) - N;
							auto data = reinterpret_cast<xns::ubyte*>(this + 1);

							while (data < last) {
								reinterpret_cast<struct chunk*>(data)->next
									= reinterpret_cast<struct chunk*>(data + N);
								data += N;
							}
							// set last chunk next pointer to nul
							reinterpret_cast<struct chunk*>(data)->next = nullptr;
						}

						/* destructor */
						inline ~page(void) noexcept = default;


						// -- public accessors --------------------------------

						/* first chunk */
						inline auto first_chunk(void) noexcept -> typename chunk::pointer {
							return reinterpret_cast<typename chunk::pointer>(this + 1);
						}


						// -- public modifiers --------------------------------

						/* extend */
						inline auto extend(void) noexcept -> void {
							auto nsize = size << 1;
							next = new (xns::memory::map(nsize)) page{nsize};
						}


						// -- public members ----------------------------------

						/* size */
						size_type size;

						/* next page */
						pointer next;

					};



					// -- private lifecycle -----------------------------------

					/* default constructor */
					inline pool_impl(void) noexcept
					: _head{new (xns::memory::map()) page{xns::memory::page_size()}},
					_tail{_head}, _chunk{_head->first_chunk()} {}

					/* non-assignable class */
					NON_ASSIGNABLE(pool_impl);

					/* destructor */
					inline ~pool_impl(void) noexcept(false) {
						// get head page
						typename page::pointer page = _head;
						// std::cout << "pool destructor [" << N << "]" << std::endl;
						// loop over pages
						while (page != nullptr) {
							// std::cout << "deallocate page: " << page->size << std::endl;
							typename page::pointer next = page->next;
							xns::memory::unmap(page, page->size);
							page = next; }
					}


					// -- private members -------------------------------------

					/* head page */
					typename page::pointer _head;

					/* tail page */
					typename page::pointer _tail;

					/* available chunk */
					typename chunk::pointer _chunk;


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
					static inline auto allocate(void) -> void* {
						// get instance
						self& instance = shared();

						typename chunk::pointer chunk = instance._chunk;

						if (chunk->next != nullptr) {
							instance._chunk = chunk->next;
						}
						else {
							instance._tail->extend();
							instance._tail = instance._tail->next;
							instance._chunk = instance._tail->first_chunk();
						}

						return static_cast<void*>(chunk);
					}


					/* deallocate */
					static inline auto deallocate(void* ptr) -> void {
						// get instance
						self& instance = shared();

						typename chunk::pointer chunk = reinterpret_cast<typename chunk::pointer>(ptr);

						chunk->next = instance._chunk;
						instance._chunk = chunk;
					}

			};


		public:


			template <typename T>
			class pool final {


				private:

					// -- private types -------------------------------------------

					/* allocator type */
					using allocator = xns::memory::pool_impl<
						sizeof(T) + xns::memory::padding<T>()>;


				public:

					// -- public types ----------------------------------------

					/* self type */
					using self      = xns::memory::pool<T>;

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
					NON_INSTANCIABLE(pool);


					// -- public static methods -------------------------------

					/* init memory (force lazy initialization) */
					inline static auto init(void) -> void {
						allocator::shared();
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


					/* make */
					template <typename... A>
					static inline auto make(A&&... args) -> mut_ptr {
						mut_ptr addr = allocate();
						construct(addr, xns::forward<A>(args)...);
						return addr;
					}

					/* store */
					static auto store(mut_ptr addrs) noexcept -> void {
						destroy(addrs);
						deallocate(addrs);
					}

			};

	};

}

#endif // MEMORY_HEADER
