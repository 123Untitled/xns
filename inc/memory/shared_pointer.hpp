#ifndef SHARED_PTR_HEADER
#define SHARED_PTR_HEADER

#include "types.hpp"
#include "macro.hpp"
#include "type_traits.hpp"
#include "allocator.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- S H A R E D  P O I N T E R  C L A S S -------------------------------

	template <class T>
	class SharedPointer final {

		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using Value     = T;

			/* self type */
			using Self      = SharedPointer<Value>;

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
			using Allocator = Allocator<Value>;

			/* size type */
			using Size      = typename Allocator::Size;


			// -- F R I E N D S -----------------------------------------------

			/* weak pointer as friend */
			template <class U>
			friend class WeakPointer;

			/* derived types as friend */
			template <class>
			friend class SharedPointer;

			/* make shared pointer as friend */
			template <class U, class... A>
			friend SharedPointer<U> make_shared_pointer(A&&... args);


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			SharedPointer(void) noexcept
			: _data{nullptr}, _count{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			SharedPointer(Xf::Nullptr) noexcept
			: SharedPointer{ } {
				// code here...
			}

			/* self copy constructor */
			SharedPointer(const Self& other) noexcept
			: _data{other._data}, _count{other._count} {
				// check pointer validity
				if (_data) {
					// increment number of references
					++(*_count);
				}
			}

			/* derived copy constructor */
			template <class D> requires Xf::is_base_of_c<T, D>
			SharedPointer(const SharedPointer<D>& other) noexcept
			: _data{other._data}, _count{other._count} {
				// check pointer validity
				if (_data) {
					// increment number of references
					++(*_count);
				}
			}

			/* self move constructor */
			SharedPointer(Self&& other) noexcept
			: _data{other._data}, _count{other._count} {
				// invalidate other
				other._data  = nullptr;
				other._count = nullptr;
			}

			/* derived move constructor */
			template <class D> requires Xf::is_base_of_c<T, D>
			SharedPointer(SharedPointer<D>&& other) noexcept
			: _data{other._data}, _count{other._count} {
				// invalidate other
				other._data  = nullptr;
				other._count = nullptr;
			}

			/* destructor */
			~SharedPointer(void) {
				// check pointer validity
				if ((_data != nullptr) && (--(*_count) == 0)) {
					// destroy object
					Allocator::destroy(_data);
					// deallocate memory
					Allocator::deallocate(_data);
					// deallocate counter
					Xf::Allocator<Size>::deallocate(_count);
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

			/* self copy assignment */
			Self& assign(const Self& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					this->~SharedPointer();
					// assign pointer and counter
					_data  = other._data;
					_count = other._count;
					// check pointer validity
					if (_data) {
						// increment number of references
						++(*_count); }
				} // return self reference
				return *this;
			}

			/* derived copy assignment */
			template <class D> requires Xf::is_base_of_c<T, D>
			Self& assign(const SharedPointer<D>& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					this->~SharedPointer();
					// assign pointer and counter
					_data  = other._data;
					_count = other._count;
					// check pointer validity
					if (_data) {
						// increment number of references
						++(*_count); }
				} // return self reference
				return *this;
			}


			/* self move assignment */
			Self& assign(Self&& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					this->~SharedPointer();
					// assign pointer and counter
					_data  = other._data;
					_count = other._count;
					// invalidate other
					other._data  = nullptr;
					other._count = nullptr;
				} // return self reference
				return *this;
			}

			/* derived move assignment */
			template <class D> requires Xf::is_base_of_c<T, D>
			Self& assign(SharedPointer<D>&& other) {
				// check for self assignment
				if (this != reinterpret_cast<Self*>(&other)) {
					// deallocate memory
					this->~SharedPointer();
					// assign pointer and counter
					_data  = other._data;
					_count = other._count;
					// invalidate other
					other._data  = nullptr;
					other._count = nullptr;
				} // return self reference
				return *this;
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* nullptr assignment operator */
			Self& operator=(Xf::Nullptr) {
				// return nullptr assignment
				return assign(nullptr);
			}

			/* self copy assignment operator */
			SharedPointer& operator=(const Self& other) {
				// return self copy assignment
				return assign(other);
			}

			/* derived copy assignment operator */
			template <class D> requires Xf::is_base_of_c<T, D>
			SharedPointer& operator=(const SharedPointer<D>& other) {
				// return derived copy assignment
				return assign(other);
			}

			/* self move assignment operator */
			SharedPointer& operator=(Self&& other) {
				// return self move assignment
				return assign(Xf::move(other));
			}

			/* derived move assignment operator */
			template <class D> requires Xf::is_base_of_c<T, D>
			SharedPointer& operator=(SharedPointer<D>&& other) {
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


			// -- P U B L I C  B O O L E A N  O P E R A T O R S ---------------

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

			/* reset */
			void reset(void) {
				// check pointer validity
				if ((_data != nullptr) && (--(*_count) == 0)) {
					// destroy object
					Allocator::destroy(_data);
					// deallocate memory
					Allocator::deallocate(_data);
					// deallocate counter
					Xf::Allocator<Size>::deallocate(_count);
					// initialize pointer
					_data = nullptr;
					// initialize counter
					_count = nullptr;
				}
			}

			/* count */
			Size count(void) const {
				// return number of references
				return _data ? *_count : 0;
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			Pointer _data;

			/* count */
			Size* _count;

	};


	// -- F R I E N D  F U N C T I O N S --------------------------------------

	/* make shared pointer */
	template <class T, class... A>
	SharedPointer<T> make_shared_pointer(A&&... args) {
		// instantiate shared pointer
		SharedPointer<T> ptr;
		// allocate memory
		ptr._data = SharedPointer<T>::Allocator::allocate();
		// check allocation failure
		if (ptr._data == nullptr) { return ptr; }
		// allocate counter
		ptr._count = Xf::Allocator<typename SharedPointer<T>::Size>::allocate();
		// check allocation failure
		if (ptr._count == nullptr) {
			// deallocate memory
			SharedPointer<T>::Allocator::deallocate(ptr._data);
			// set pointer to nullptr
			ptr._data = nullptr;
			// return shared pointer
			return ptr;
		} // else construct object by forwarding arguments
		SharedPointer<T>::Allocator::construct(ptr._data, Xf::forward<A>(args)...);
		// initialize counter
		*ptr._count = 1;
		// return shared pointer
		return ptr;
	}




}

#endif
