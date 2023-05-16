#ifndef UNIQUE_POINTER_HEADER
#define UNIQUE_POINTER_HEADER

#include "types.hpp"
#include "allocator.hpp"
#include "inheritance.hpp"
#include "is_same.hpp"



// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	/* WeakPointer forward declaration */
	//template <class T>
	//class WeakPointer;


	// -- U N I Q U E  P O I N T E R  C L A S S -------------------------------

	template <class T>
	class UniquePointer final {

		public:

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


			// -- F R I E N D S -----------------------------------------------

			/* weak pointer as friend */
			template <class>
			friend class WeakPointer;

			/* derived types as friend */
			template <class>
			friend class UniquePointer;

			/* make unique pointer as friend */
			template <class U, class... A>
			friend UniquePointer<U> make_unique_pointer(A&&... args);


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			UniquePointer(void) noexcept
			: _data{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			UniquePointer(Xf::Nullptr) noexcept
			: UniquePointer{ } {
				// code here...
			}

			/* non-copyable class */
			NON_COPYABLE(UniquePointer);

			/* self move constructor */
			UniquePointer(Self&& other) noexcept
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* derived move constructor */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			UniquePointer(UniquePointer<D>&& other) noexcept
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			~UniquePointer(void) {
				// check pointer validity
				if (_data != nullptr) {
					// destroy object
					Allocator::destroy(_data);
					// deallocate memory
					Allocator::deallocate(_data);
				}
			}


			// -- P U B L I C  A S S I G N M E N T ----------------------------

			/* nullptr assignment */
			Self& assign(Xf::Nullptr) {
				// clean up
				reset();
				// return self reference
				return *this;
			}

			/* self move assignment */
			Self& assign(Self&& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					this->~UniquePointer();
					// initialize pointer
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}

			/* derived move assignment */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			Self& assign(UniquePointer<D>&& other) {
				// check for self assignment
				if (this != reinterpret_cast<Self*>(&other)) {
					// deallocate memory
					this->~UniquePointer();
					// initialize pointer
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* nullptr assignment operator */
			Self& operator=(Xf::Nullptr) {
				// return nullptr assignment
				return assign(nullptr);
			}

			/* self move assignment operator */
			Self& operator=(Self&& other) {
				// return self move assignment
				return assign(Xf::move(other));
			}

			/* derived move assignment operator */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			Self& operator=(UniquePointer<D>&& other) {
				// return derived move assignment
				return assign(Xf::move(other));
			}


			// -- P U B L I C  A C C E S S O R S  O P E R A T O R S -----------

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

			/* boolean operator */
			operator bool(void) const {
				// return pointer validity
				return _data != nullptr;
			}

			/* not operator */
			bool operator!(void) const {
				// return pointer invalidity
				return _data == nullptr;
			}


			// -- P U B L I C  C O M P A R I S O N  O P E R A T O R S ---------

			/* equality operator */
			bool operator==(const Self& other) const noexcept {
				// return pointer equality
				return _data == other._data;
			}

			/* inequality operator */
			bool operator!=(const Self& other) const noexcept {
				// return pointer inequality
				return _data != other._data;
			}

			/* nullptr equality operator */
			bool operator==(Xf::Nullptr) const noexcept {
				// return pointer invalidity
				return _data == nullptr;
			}

			/* nullptr inequality operator */
			bool operator!=(Xf::Nullptr) const noexcept {
				// return pointer validity
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
					// invalidate pointer
					_data = nullptr;
				}
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			Pointer _data;


	};


	// -- F R I E N D  F U N C T I O N S --------------------------------------

	/* make unique pointer */
	template <class T, class... A>
	UniquePointer<T> make_unique_pointer(A&&... args) {
		// instantiate unique pointer
		UniquePointer<T> ptr;
		// allocate memory
		ptr._data = UniquePointer<T>::Allocator::allocate();
		// check allocation success
		if (ptr._data) {
			// construct object by forwarding arguments
			UniquePointer<T>::Allocator::construct(ptr._data, Xf::forward<A>(args)...);
		} // return instance
		return ptr;
	}

}

#endif
