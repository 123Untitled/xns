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


			// -- A C C E S S O R S -------------------------------------------

			/* address */
			static mutable_pointer address(reference value) {
				// return address
				return &value;
			}

			/* const address */
			static const_pointer address(const_reference value) {
				// return constant address
				return &value;
			}

			/* max size */
			inline static consteval size_type max_size(void) {
				// return max size
				return xns::limits::max<size_type>() / sizeof(value_type);
			}


			// -- C O N S T R U C T -------------------------------------------

			/* copy construct */
			static void construct(mutable_pointer addrs, const_reference value) {

				static_assert(xns::is_copy_constructible<value_type>,
						"TYPE IS NOT COPY CONSTRUCTIBLE");

				// construct object by copy
				new(addrs) value_type{value};
			}

			/* move construct */
			static void construct(mutable_pointer addrs, move_reference value) {

				static_assert(xns::is_move_constructible<value_type>,
						"TYPE IS NOT MOVE CONSTRUCTIBLE");

				// construct object by move
				new(addrs) value_type{xns::move(value)};
			}

			/* forward construct */
			template <class... A>
			static void construct(mutable_pointer addrs, A&&... args) {

				static_assert(xns::is_constructible<value_type, A...>,
						"TYPE IS NOT CONSTRUCTIBLE");

				// construct object by forwarding arguments
				new(addrs) value_type{xns::forward<A>(args)...};
			}


			// -- D E S T R U C T ---------------------------------------------

			/* destroy */
			static void destroy(mutable_pointer addrs) {

				if constexpr (xns::is_trivially_destructible<value_type> == false) {
					static_assert(xns::is_destructible<value_type>,
							"TYPE IS NOT DESTRUCTIBLE");
					// call object destructor
					addrs->~value_type();
				}
			}

	};

}

#endif
