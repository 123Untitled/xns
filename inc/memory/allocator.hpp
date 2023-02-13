#ifndef ALLOCATOR_HEADER
#define ALLOCATOR_HEADER

#include <limits>
#include "types.hpp"
#include "macro.hpp"
#include "forward.hpp"
#include "move.hpp"
#include <cstdlib>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- A L L O C A T O R  C L A S S ----------------------------------------

	template <typename T>
	class Allocator final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* value type */
			using Value = T;

			/* size type */
			using Size = UInt64;

			/* reference type */
			using Reference = T&;

			/* const reference type */
			using ConstReference = const T&;

			/* move reference type */
			using MoveReference = T&&;

			/* pointer type */
			using Pointer = T*;

			/* const pointer type */
			using ConstPointer = const T*;


			// -- C O N S T R U C T O R S -------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(Allocator);


			// -- A L L O C A T I O N -----------------------------------------

			/* allocate */
			static Pointer allocate(const Size size = 1) {
				// allocate memory
				return static_cast<Pointer>(std::malloc(size * sizeof(Value)));
			}

			/* realloc */
			static Pointer realloc(Pointer addrs, const Size size = 1) {
				// reallocate memory
				return static_cast<Pointer>(std::realloc(addrs, size * sizeof(Value)));
			}

			/* deallocate */
			static void deallocate(Pointer pointer) {
				// deallocate memory
				std::free(pointer);
			}


			// -- A C C E S S O R S -------------------------------------------

			/* address */
			static Pointer address(Reference value) {
				// return address
				return &value;
			}

			/* const address */
			static ConstPointer address(ConstReference value) {
				// return address
				return &value;
			}

			/* max size */
			static Size max_size(void) {
				// return max size
				return std::numeric_limits<Size>::max() / sizeof(Value);
			}


			// -- C O N S T R U C T -------------------------------------------

			/* copy construct */
			static void construct(Pointer addrs, ConstReference value) {
				// construct object by copy
				new(addrs) Value{value};
			}

			/* move construct */
			static void construct(Pointer addrs, MoveReference value) {
				// construct object by move
				new(addrs) Value{Xf::move(value)};
			}

			/* forward construct */
			template <typename... Args>
			static void construct(Pointer addrs, Args&&... args) {
				// construct object by forwarding
				new(addrs) Value{Xf::forward<Args>(args)...};
			}


			// -- D E S T R U C T ---------------------------------------------

			/* destroy */
			static void destroy(Pointer addrs) {
				// destroy object
				addrs->~Value();
			}




	};

};

#endif
