#ifndef MEMORY_HEADER
#define MEMORY_HEADER

// local headers
#include "os.hpp"
#include "types.hpp"
#include "exceptions.hpp"
#include "macro.hpp"
#include "is_constructible.hpp"
#include "is_destructible.hpp"
#include "is_trivially_destructible.hpp"

// operating system headers
#include <unistd.h>
#include <sys/mman.h>

//#include <emmintrin.h>
//#include <arm_neon.h>
//#include <sys/syscall.h>

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M O R Y  N A M E S P A C E --------------------------------------

	namespace memory {


		class mmap final {

			public:

				// -- public types ------------------------------------------------

				/* size type */
				using size_type = xns::size_t;


				// -- public lifecycle --------------------------------------------

				/* non-instantiable class */
				NON_INSTANCIABLE(mmap);


				// -- public static methods ---------------------------------------

				/* page size */
				static inline auto page_size(void) noexcept -> size_type {
					static const size_type page_size = _page_size();
					return page_size;
				}

				/* allocate */
				static inline auto allocate(const size_type size = page_size()) -> void* {
					//std::cout << "mmap allocate: " << size << std::endl;
					void* ptr = ::mmap(nullptr, size, M_PROTECTION, M_FLAGS, -1, 0);
					if (ptr == MAP_FAILED)
						throw xns::exception(-2, "mmap failed");
					return ptr;
				}

				/* deallocate */
				static inline auto deallocate(void* ptr, const size_type size) -> void {
					if (::munmap(ptr, size) == -1)
						throw xns::exception(-2, "munmap failed");
				}

			private:

				// -- private methods ---------------------------------------------

				/* system page size */
				static inline auto _page_size(void) -> size_type {
					if (auto page_size = ::sysconf(_SC_PAGESIZE); page_size > 0) {
						return static_cast<size_type>(page_size);
					}
					throw xns::exception(-2, "sysconf failed");
				}


				// -- private enums -----------------------------------------------

				/* mmap flags */
				enum : int {
					M_PROTECTION =   PROT_READ | PROT_WRITE,
					M_FLAGS      = MAP_PRIVATE | MAP_ANONYMOUS
				};


		};


		/* padding */
		template <typename T>
		consteval auto padding(void) noexcept -> decltype(sizeof(void*)) {
			// return padding
			return (-sizeof(T)) & (sizeof(void*) - 1);
		}

		/* power of two padding */
		template <typename T>
		consteval auto padding_power(void) noexcept -> decltype(sizeof(void*)) {
			xns::size_t align = 1;
			while (align < sizeof(T))
				align <<= 1;
			return align - sizeof(T);
		}





		template <typename T>
		class pool final {


			public:

				// -- public types --------------------------------------------

				/* self type */
				using self            = xns::memory::pool<T>;

				/* value type */
				using value_type      = T;

				/* size type */
				using size_type       = xns::size_t;

				/* reference type */
				using reference       = T&;

				/* const reference type */
				using const_reference = const T&;

				/* move reference type */
				using move_reference  = T&&;

				/* pointer type */
				using mutable_pointer = T*;

				/* const pointer type */
				using const_pointer   = const T*;


			private:

				// -- implementation ------------------------------------------

				template <size_type N>
				class impl {


					public:

						// -- public types ------------------------------------

						/* self type */
						using self = self::impl<N>;


					private:

						// -- chunk -------------------------------------------

						struct chunk final {


							// -- public types --------------------------------

							/* pointer type */
							using pointer = chunk*;


							// -- public lifecycle ----------------------------

							/* non-instanciable class */
							NON_INSTANCIABLE(chunk);


							// -- public members ------------------------------

							/* next chunk */
							pointer next;

						};


						// -- page --------------------------------------------

						struct alignas(sizeof(xns::addr_t)) page final {

							// -- public types --------------------------------

							/* self type */
							using self = impl<N>::page;

							/* pointer type */
							using pointer = self*;



							// -- public lifecycle ----------------------------

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


							// -- public accessors ----------------------------

							/* first chunk */
							inline auto first_chunk(void) noexcept -> typename chunk::pointer {
								return reinterpret_cast<typename chunk::pointer>(this + 1);
							}


							// -- public modifiers ----------------------------

							/* extend */
							inline auto extend(void) noexcept -> void {
								auto nsize = size << 1;
								next = new (xns::memory::mmap::allocate(nsize)) page{nsize};
							}


							// -- public members ------------------------------

							/* size */
							size_type size;

							/* next page */
							pointer next;

						};



						// -- private lifecycle -------------------------------

						/* default constructor */
						inline impl(void) noexcept
						: _head{new (mmap::allocate()) page{mmap::page_size()}},
						_tail{_head}, _chunk{_head->first_chunk()} {}

						/* non-assignable class */
						NON_ASSIGNABLE(impl);

						/* destructor */
						inline ~impl(void) noexcept(false) {
							// get head page
							typename page::pointer page = _head;
							std::cout << "pool destructor [" << N << "]" << std::endl;
							// loop over pages
							while (page != nullptr) {
								std::cout << "deallocate page: " << page->size << std::endl;
								typename page::pointer next = page->next;
								mmap::deallocate(page, page->size);
								page = next; }
						}


						// -- private members ---------------------------------

						/* head page */
						typename page::pointer _head;

						/* tail page */
						typename page::pointer _tail;

						/* available chunk */
						typename chunk::pointer _chunk;


					public:

						// -- public accessors --------------------------------

						/* instance */
						static inline auto shared(void) -> self& {
							// static instance
							static self instance;
							return instance;
						}


						// -- public static methods ---------------------------


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

				// -- public lifecycle ----------------------------------------

				/* non-instantiable class */
				NON_INSTANCIABLE(pool);


				// -- public static methods -----------------------------------

				/* init memory (force lazy initialization) */
				inline static auto init(void) -> void {
					allocator::shared();
				}

				/* make */
				template <typename... A>
				static inline auto make(A&&... args) -> mutable_pointer {

					static_assert(xns::is_constructible<value_type, A...>,
						"TYPE IS NOT CONSTRUCTIBLE");

					return static_cast<mutable_pointer>(new (allocator::allocate()) value_type{args...});
				}

				/* delete */
				static auto store(mutable_pointer addrs) noexcept -> void {
					// check type is trivially destructible
					if constexpr (xns::is_trivially_destructible<value_type> == false) {
						// check type is destructible
						static_assert(xns::is_destructible<value_type>,
								"TYPE IS NOT DESTRUCTIBLE");
						// call object destructor
						addrs->~value_type();
					}
					allocator::deallocate(addrs);
				}


			private:

				// -- private types -------------------------------------------

				/* allocator type */
				using allocator = self::impl<sizeof(T) + padding<T>()>;


		};


	}





// -O3
// deallocate page: 16384
// deallocate page: 32768
// deallocate page: 65536
// deallocate page: 131072
// deallocate page: 262144
// deallocate page: 524288
// deallocate page: 1048576
// deallocate page: 2097152
// deallocate page: 4194304
// deallocate page: 8388608
// deallocate page: 16777216
// deallocate page: 33554432
// deallocate page: 67108864
// deallocate page: 134217728
// deallocate page: 268435456
// deallocate page: 536870912
// deallocate page: 1073741824
// deallocate page: 2147483648
// deallocate page: 4294967296

// -O0
// deallocate page: 16384
// deallocate page: 32768
// deallocate page: 65536
// deallocate page: 131072
// deallocate page: 262144
// deallocate page: 524288
// deallocate page: 1048576
// deallocate page: 2097152
// deallocate page: 4194304
// deallocate page: 8388608
// deallocate page: 16777216
// deallocate page: 33554432
// deallocate page: 67108864
// deallocate page: 134217728
// deallocate page: 268435456
// deallocate page: 536870912
// deallocate page: 1073741824










}

#endif // MEMORY_HEADER
