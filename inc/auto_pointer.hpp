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

	// -- P O I N T E R  C L A S S --------------------------------------------

	template <class T>
	class AutoPointer final {

		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using Value     = T;

			/* self type */
			using Self      = AutoPointer<Value>;

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
			friend class AutoPointer;

			/* make auto pointer function as friend */
			template <class U, class... A>
			friend AutoPointer<U> make_auto_pointer(A&&... args);


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			AutoPointer(void)
			// initialize pointer
			: _data(nullptr) {
				// code here...
			}

			/* copy constructor */
			AutoPointer(const Self& other)
			// allocate memory
			: _data(Allocator::allocate()) {
				// check allocation success
				if (_data != nullptr) {
					// construct object copy
					Allocator::construct(_data, *other._data);
				}
			}

			/* move constructor for derived types */
			template <class D>
			AutoPointer(AutoPointer<D>&& other) requires (Xf::is_base_of_c<T, D>)
			// initialize pointer
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			~AutoPointer(void) {
				// check pointer validity
				if (_data != nullptr) {
					// destroy object
					Allocator::destroy(_data);
					// deallocate memory
					Allocator::deallocate(_data);
				}
			}


			// -- A S S I G N -------------------------------------------------

			/* copy assignment */
			Self& assign(const Self& other) {
				// check for self assignment
				if (this != &other) {
					// clean up
					_clean();
					// check other pointer validity
					if (other._data != nullptr) {
						// allocate memory
						_data = Allocator::allocate();
						// construct object by copy
						Allocator::construct(_data, *other._data); }
				} // return self reference
				return *this;
			}

			/* move assignment for derived types */
			template <class D>
			Self& assign(AutoPointer<D>&& other) requires (Xf::is_base_of_c<T, D>) {
				// check for self assignment
				if (this != &other) {
					// clean up
					_clean();
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
				_clean();
				// return self reference
				return *this;
			}


			// -- A S S I G N M E N T  O P E R A T O R S ----------------------

			/* copy assignment operator */
			Self& operator=(const Self& other) {
				// return copy assignment
				return assign(other);
			}

			/* move assignment operator */
			template <class D>
			Self& operator=(AutoPointer<D>&& other)
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


			/* copy assignment operator */
			Self& operator<<(const Self& other) {
				// return copy assignment
				return assign(other);
			}

			/* move assignment operator */
			template <class D>
			Self& operator<<(AutoPointer<D>&& other)
			// requires derived or self type
			requires (Xf::is_base_of_c<T, D>) {
				// return move assignment
				return assign(Xf::move(other));
			}

			/* nullptr assignment operator */
			Self& operator<<(Xf::Nullptr) {
				// return nullptr assignment
				return assign(nullptr);
			}


			/* copy assignment operator */
			Self& operator>>(Self& other) {
				// return copy assignment
				return other.assign(*this);
			}

			/* move assignment operator */
			template <class D>
			Self& operator>>(AutoPointer<D>& other)
			// requires derived or self type
			requires (Xf::is_base_of_c<T, D>) {
				// return move assignment
				return other.assign(Xf::move(*this));
			}

			/* nullptr assignment operator */
			Self& operator>>(Xf::Nullptr) {
				// clean up
				_clean();
				// return self reference
				return *this;
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





		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			void _clean(void) {
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

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			Pointer _data;


	};


	// -- F R I E N D  F U N C T I O N S --------------------------------------

	template <class U, class... A>
	AutoPointer<U> make_auto_pointer(A&&... args) {
		// instantiate auto pointer
		AutoPointer<U> ptr;
		// memory allocation
		ptr._data = AutoPointer<U>::Allocator::allocate();
		// check allocation success
		if (ptr._data) {
			// construct object by forwarding arguments
			AutoPointer<U>::Allocator::construct(ptr._data, Xf::forward<A>(args)...);
		} // return instance
		return ptr;
	}

}

#endif
