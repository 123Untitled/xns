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
#include <limits>
#include <cstdlib>




// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L L O C A T O R  C L A S S ----------------------------------------

	template <class T>
	class allocator final {

		public:

			// -- T Y P E S ---------------------------------------------------

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = allocator<value_type>;

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


			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(allocator);



			// -- A L L O C A T I O N -----------------------------------------

			/* allocate */
			static mutable_pointer allocate(const size_type size = 1) {
				// allocate memory
				mutable_pointer ptr = static_cast<mutable_pointer>(std::malloc(size * sizeof(value_type)));
				// check failed allocation
				if (!ptr) { throw xns::exception(-2, "FAILED TO ALLOCATE MEMORY"); }
				// return pointer
				return ptr;
			}

			/* realloc */
			static mutable_pointer realloc(mutable_pointer addrs, const size_type size = 1) {
				// check type is scalar (need to replace by is_trivially_copyable)
				static_assert(xns::is_scalar<value_type>, "TYPE IS NOT SCALAR");
				// reallocate memory
				mutable_pointer ptr = static_cast<mutable_pointer>(std::realloc(addrs, size * sizeof(value_type)));
				// check failed reallocation
				if (!ptr) { throw xns::exception(-2, "FAILED TO REALLOCATE MEMORY"); }
				// return pointer
				return ptr;
			}

			/* deallocate */
			static void deallocate(mutable_pointer pointer) {
				// deallocate memory
				std::free(pointer);
			}


			// -- public accessors --------------------------------------------

			/* address */
			static auto address(reference value) -> mutable_pointer {
				// return address
				return &value;
			}

			/* const address */
			static auto address(const_reference value) -> const_pointer {
				// return constant address
				return &value;
			}

			/* max size */
			static inline consteval auto max_size(void) -> size_type {
				// return max size
				return xns::limits::max<size_type>() / sizeof(value_type);
			}


			// -- public construct methods ------------------------------------

			/* copy construct */
			static inline auto construct(mutable_pointer addrs, const_reference value) -> void {

				static_assert(xns::is_copy_constructible<value_type>,
						"TYPE IS NOT COPY CONSTRUCTIBLE");

				// construct object by copy
				new(addrs) value_type{value};
			}

			/* move construct */
			static inline auto construct(mutable_pointer addrs, move_reference value) -> void {

				static_assert(xns::is_move_constructible<value_type>,
						"TYPE IS NOT MOVE CONSTRUCTIBLE");

				// construct object by move
				new(addrs) value_type{xns::move(value)};
			}

			/* forward construct */
			template <class... A>
			static inline auto construct(mutable_pointer addrs, A&&... args) -> void {

				static_assert(xns::is_constructible<value_type, A...>,
						"TYPE IS NOT CONSTRUCTIBLE");

				// construct object by forwarding arguments
				new(addrs) value_type{xns::forward<A>(args)...};
			}


			// -- public destroy methods --------------------------------------

			/* destroy */
			static inline auto destroy(mutable_pointer addrs) -> void {
				// check type is trivially destructible
				if constexpr (xns::is_trivially_destructible<value_type> == false) {
					// check type is destructible
					static_assert(xns::is_destructible<value_type>,
							"TYPE IS NOT DESTRUCTIBLE");
					// call object destructor
					addrs->~value_type();
				}
			}


			// -- public assign methods ---------------------------------------

			/* copy assign */
			static inline auto assign(reference dst, const_reference src) -> void {

				static_assert(xns::is_copy_assignable<value_type>,
						"TYPE IS NOT COPY ASSIGNABLE");

				// assign object by copy
				dst = src;
			}

			/* move assign */
			static inline auto assign(reference dst, move_reference src) -> void {

				static_assert(xns::is_move_assignable<value_type>,
						"TYPE IS NOT MOVE ASSIGNABLE");

				// assign object by move
				dst = xns::move(src);
			}

	};

}

#endif
