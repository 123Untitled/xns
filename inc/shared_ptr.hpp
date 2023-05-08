#ifndef SHARED_PTR_HEADER
#define SHARED_PTR_HEADER
#include <iostream>

#include "macro.hpp"
#include "types.hpp"
#include "type_traits.hpp"
#include "allocator.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- S H A R E D  P T R  C L A S S ---------------------------------------

	template <class S, class... A>
	concept not_self = (!Xf::IsSame_s<Xf::remove_reference_t<A>, S>::value&& ...) || (sizeof...(A) > 1);

	template <typename T>
	class SharedPointer final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* size type */
			using Size = UInt64;

			/* value type */
			using Value = T;

			/* reference type */
			using Reference = Value&;

			/* pointer type */
			using Pointer = Value*;

			/* const reference type */
			using ConstReference = const Value&;

			/* const pointer type */
			using ConstPointer = const Value*;

			/* move reference type */
			using MoveReference = Value&&;

			/* self type */
			using Self = SharedPointer<Value>;

			/* allocator type */
			using Alloc = Allocator<Value>;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			SharedPointer(void)
			: _pointer{nullptr}, _count{nullptr} {
				// code here...
			}


			/* forward constructor */
			template <class... A> // requires argument is not Self
			SharedPointer(A&&... arguments) requires (not_self<Self, A...>)
			: SharedPointer{} {
				make(Xf::forward<A>(arguments)...);
			}


			/* move constructor */
			SharedPointer(const Self& other)
			: _pointer{other._pointer}, _count{other._count} {
				// check if pointer is not null
				if (_pointer) {
					// increment number of references
					++(*_count);
				}
			}

			/* move constructor */
			SharedPointer(Self&& other)
			: _pointer{other._pointer}, _count{other._count} {
				// invalidate other
				other._pointer = nullptr;
				other._count = nullptr;
			}

			/* destructor */
			~SharedPointer(void) {
				if ((_pointer != nullptr) && (--(*_count) == 0)) {
					Alloc::destroy(_pointer);
					Alloc::deallocate(_pointer);
					Allocator<Size>::deallocate(_count);
				}
			}


			// -- O P E R A T O R S -------------------------------------------

			/* copy assignment operator */
			SharedPointer& operator=(const Self& other) {

				if (this != &other) {
					this->~SharedPointer();
					_pointer = other._pointer;
					_count   = other._count;
					if (_pointer) {
						++(*_count);
					} // return self reference
				} return *this;
			}

			/* move assignment operator */
			SharedPointer& operator=(SharedPointer&& move) {

				if (this != &move) {
					this->~SharedPointer();
					_pointer = move._pointer;
					_count   = move._count;
					move._pointer = nullptr;
					move._count   = nullptr;
				} return *this;
			}

			/* dereference operator */
			Reference operator*(void) {
				// return dereferenced pointer
				return *_pointer;
			}

			/* const dereference operator */
			ConstReference operator*(void) const {
				// return dereferenced const pointer
				return *_pointer;
			}

			/* arrow operator */
			Pointer operator->(void) {
				// return pointer
				return _pointer;
			}

			/* const arrow operator */
			ConstPointer operator->(void) const {
				// return const pointer
				return _pointer;
			}


			// -- M E T H O D S -----------------------------------------------

			/* make shared */
			template <class... A>
			void make(A&&... arguments) {
				this->~SharedPointer();
				// WARNING: need to deallocate existing pointer
				if ((_pointer = Alloc::allocate())) {

					if ((_count = Allocator<Size>::allocate())) {
						Alloc::construct(_pointer, Xf::forward<A>(arguments)...);
						*_count = 1;
						return;
					}
					Alloc::deallocate(_pointer);
					_pointer = nullptr;
				}
				_count = nullptr;
			}

			/* release */
			void release(void) {
				this->~SharedPointer();
				_pointer = nullptr;
				_count   = nullptr;
			}

			UInt use_count(void) const {
				return _pointer ? *_count : 0;
			}





		private:

			/* pointer */
			Pointer _pointer;

			/* count */
			Size* _count;


	};

}

#endif
