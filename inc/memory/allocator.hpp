#ifndef ALLOCATOR_HEADER
#define ALLOCATOR_HEADER

// local headers
#include "types.hpp"
#include "macro.hpp"
#include "forward.hpp"
#include "exceptions.hpp"
#include "move.hpp"
#include "numeric_limits.hpp"
#include "policy.hpp"
#include "is_scalar.hpp"
#include "is_constructible.hpp"
#include "is_destructible.hpp"
#include "is_trivially_destructible.hpp"

// standard headers
#include <cstdlib>




// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L L O C A T O R ---------------------------------------------------

	template <typename T>
	class allocator final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self      = xns::allocator<T>;

			/* value type */
			using type      = T;

			/* size type */
			using size_type = xns::size_t;

			/* reference type */
			using mut_ref   = T&;

			/* const reference type */
			using const_ref = const T&;

			/* move reference type */
			using move_ref  = T&&;

			/* pointer type */
			using mut_ptr   = T*;

			/* const pointer type */
			using const_ptr = const T*;


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(allocator);


			// -- public static methods ---------------------------------------

			/* allocate */
			static inline auto allocate(const size_type size = 1) -> mut_ptr {
				// allocate memory
				mut_ptr ptr = static_cast<mut_ptr>(std::malloc(size * sizeof(type)));
				// check failed allocation
				if (!ptr) { throw xns::exception(-2, "FAILED TO ALLOCATE MEMORY"); }
				// return pointer
				return ptr;
			}

			/* realloc */
			static inline auto realloc(mut_ptr addrs, const size_type size = 1) -> mut_ptr {
				// check type is scalar (need to replace by is_trivially_copyable)
				static_assert(xns::is_scalar<type>, "TYPE IS NOT SCALAR");
				// reallocate memory
				mut_ptr ptr = static_cast<mut_ptr>(std::realloc(addrs, size * sizeof(type)));
				// check failed reallocation
				if (!ptr) { throw xns::exception(-2, "FAILED TO REALLOCATE MEMORY"); }
				// return pointer
				return ptr;
			}

			/* deallocate */
			static inline auto deallocate(mut_ptr pointer) noexcept -> void {
				// deallocate memory
				std::free(pointer);
			}


			// -- public accessors --------------------------------------------

			/* address */
			static inline auto address(mut_ref value) -> mut_ptr {
				// return address
				return &value;
			}

			/* const address */
			static inline auto address(const_ref value) -> const_ptr {
				// return constant address
				return &value;
			}

			/* max size */
			static inline consteval auto max_size(void) -> size_type {
				// return max size
				return xns::limits::max<size_type>() / sizeof(type);
			}


			// -- public construct methods ------------------------------------

			/* copy construct */
			static inline auto construct(mut_ptr addrs, const_ref value) -> void {
				// assert type is copy constructible
				static_assert(xns::is_copy_constructible<type>,
						"TYPE IS NOT COPY CONSTRUCTIBLE");
				// construct object by copy
				new(addrs) type{value};
			}

			/* move construct */
			static inline auto construct(mut_ptr addrs, move_ref value) -> void {
				// assert type is move constructible
				static_assert(xns::is_move_constructible<type>,
						"TYPE IS NOT MOVE CONSTRUCTIBLE");
				// construct object by move
				new(addrs) type{xns::move(value)};
			}

			/* forward construct */
			template <typename... A>
			static inline auto construct(mut_ptr addrs, A&&... args) -> void {
				// assert type is constructible
				static_assert(xns::is_constructible<type, A...>,
						"TYPE IS NOT CONSTRUCTIBLE");
				// construct object by forwarding arguments
				new(addrs) type{xns::forward<A>(args)...};
			}


			// -- public destroy methods --------------------------------------

			/* destroy */
			static inline auto destroy(mut_ptr addrs) -> void {
				// check type is trivially destructible
				if constexpr (xns::is_trivially_destructible<type> == false) {
					// check type is destructible
					static_assert(xns::is_destructible<type>,
							"TYPE IS NOT DESTRUCTIBLE");
					// call object destructor
					addrs->~type();
				}
			}


			// -- public assign methods ---------------------------------------

			/* copy assign */
			static inline auto assign(mut_ref dst, const_ref src) -> void {
				// assert type is copy assignable
				static_assert(xns::is_copy_assignable<type>,
						"TYPE IS NOT COPY ASSIGNABLE");
				// assign object by copy
				dst = src;
			}

			/* move assign */
			static inline auto assign(mut_ref dst, move_ref src) -> void {
				// assert type is move assignable
				static_assert(xns::is_move_assignable<type>,
						"TYPE IS NOT MOVE ASSIGNABLE");
				// assign object by move
				dst = xns::move(src);
			}


	};

}

#endif
