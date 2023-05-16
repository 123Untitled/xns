#ifndef POINTER_HEADER
#define POINTER_HEADER

#include "types.hpp"
#include "allocator.hpp"
#include "inheritance.hpp"
#include "is_same.hpp"

#include <iostream>



/* namespace name idea */
namespace OWN { }


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	/* WeakPointer forward declaration */
	template <class T>
	class WeakPointer;

	// -- P O I N T E R  C L A S S --------------------------------------------

	template <class T>
	class UniquePointer final {

		public:

			template <class U>
			friend class WeakPointer;

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using Value     = T;

			/* self type */
			using Self      = UniquePointer<Value>;

			/* reference type */
			using Reference = Value&;

			/* move reference type */
			using MoveRef   = Value&&;

			/* pointer type */
			using Pointer   = Value*;

			/* const reference type */
			using ConstRef  = const Value&;

			/* const pointer type */
			using ConstPtr  = const Value*;

			/* allocator type */
			using Allocator = Xf::Allocator<Value>;

			/* size type */
			using Size      = SizeT;



			// -- F R I E N D S -----------------------------------------------

			/* inherited types as friends */
			template <class>
			friend class UniquePointer;

			/* make auto pointer function as friend */
			template <class U, class... A>
			friend UniquePointer<U> make_unique_pointer(A&&... args);


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			UniquePointer(void) noexcept
			// initialize pointer
			: _data{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			UniquePointer(Xf::Nullptr) noexcept
			// initialize pointer
			: _data{nullptr} {
				// code here...
			}

			/* non-copyable class */
			NON_COPYABLE(UniquePointer);

			/* move constructor for self type */
			UniquePointer(Self&& other) noexcept
			// initialize pointer
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* move constructor for derived types */
			template <class D>
			UniquePointer(UniquePointer<D>&& other) noexcept
			requires (Xf::is_base_of_c<T, D>)
			// initialize pointer
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			~UniquePointer(void) {
				// clean up
				reset();
			}


			// -- A S S I G N -------------------------------------------------

			/* move assignment for self type */
			Self& assign(Self&& other) {
				// check for self assignment
				if (this != &other) {
					// clean up
					reset();
					// initialize pointer
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}

			/* move assignment for derived types */
			template <class D>
			Self& assign(UniquePointer<D>&& other) requires (Xf::is_base_of_c<T, D>) {
				// check for self assignment
				if (this != reinterpret_cast<Self*>(&other)) {
					// clean up
					reset();
					// initialize pointer
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}

			/* nullptr assignment */
			Self& assign(Xf::Nullptr) {
				// clean up
				reset();
				// invalidate pointer
				_data = nullptr;
				// return self reference
				return *this;
			}


			// -- A S S I G N M E N T  O P E R A T O R S ----------------------

			/* move assignment operator for self type */
			Self& operator=(Self&& other) {
				// return copy assignment
				return assign(Xf::move(other));
			}

			/* move assignment operator for derived types */
			template <class D>
			Self& operator=(UniquePointer<D>&& other)
			// requires derived or self type
			requires (Xf::is_base_of_c<T, D>) {
				// return move assignment
				return assign(Xf::move(other));
			}

			/* nullptr assignment operator */
			Self& operator=(Xf::Nullptr) {
				// return nullptr assignment
				return assign(nullptr);
			}


			// -- A C C E S S O R S  O P E R A T O R S ------------------------

			/* dereference operator */
			Reference operator*(void) {
				// return reference
				return *_data;
			}

			/* const dereference operator */
			ConstRef operator*(void) const {
				// return const reference
				return *_data;
			}

			/* arrow operator */
			Pointer operator->(void) {
				// return pointer
				return _data;
			}

			/* const arrow operator */
			ConstPtr operator->(void) const {
				// return const pointer
				return _data;
			}


			// -- B O O L E A N  O P E R A T O R S ----------------------------

			/* bool operator */
			operator bool(void) const {
				// return pointer validity
				return _data != nullptr;
			}

			/* not operator */
			bool operator!(void) const {
				// return pointer validity
				return _data == nullptr;
			}


			// -- E Q U A L I T Y  O P E R A T O R S --------------------------

			/* equality operator */
			bool operator==(const Self& other) const {
				// return pointer equality
				return _data == other._data;
			}

			/* inequality operator */
			bool operator!=(const Self& other) const {
				// return pointer inequality
				return _data != other._data;
			}

			/* nullptr equality operator */
			bool operator==(Xf::Nullptr) const {
				// return pointer validity
				return _data == nullptr;
			}

			/* nullptr inequality operator */
			bool operator!=(Xf::Nullptr) const {
				// return pointer invalidity
				return _data != nullptr;
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* reset pointer */
			void reset(void) {
				// check pointer validity
				if (_data != nullptr) {
					// destroy object
					Allocator::destroy(_data);
					// deallocate memory
					Allocator::deallocate(_data);
				}
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			Pointer _data;


	};


	// -- F R I E N D  F U N C T I O N S --------------------------------------

	/* make unique pointer */
	template <class U, class... A>
	UniquePointer<U> make_unique_pointer(A&&... args) {
		// instantiate auto pointer
		UniquePointer<U> ptr;
		// memory allocation
		ptr._data = UniquePointer<U>::Allocator::allocate();
		// check allocation success
		if (ptr._data) {
			// construct object by forwarding arguments
			UniquePointer<U>::Allocator::construct(ptr._data, Xf::forward<A>(args)...);
		} // return instance
		return ptr;
	}

}

#endif
