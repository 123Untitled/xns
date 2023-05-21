#ifndef UNIQUE_POINTER_HEADER
#define UNIQUE_POINTER_HEADER

#include "types.hpp"
#include "allocator.hpp"
#include "inheritance.hpp"
#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- U N I Q U E  P O I N T E R  C L A S S -------------------------------

	template <class T>
	class unique_ptr final {

		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = unique_ptr<value_type>;

			/* reference type */
			using reference       = value_type&;

			/* move reference type */
			using move_reference  = value_type&&;

			/* pointer type */
			using mutable_pointer = value_type*;

			/* const reference type */
			using const_reference = const value_type&;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* allocator type */
			using allocator       = xns::allocator<value_type>;


			// -- F R I E N D S -----------------------------------------------

			/* weak pointer as friend */
			template <class>
			friend class weak_ptr;

			/* derived types as friend */
			template <class>
			friend class unique_ptr;

			/* make unique pointer as friend */
			template <class U, class... A>
			friend unique_ptr<U> make_unique_pointer(A&&... args);


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			unique_ptr(void) noexcept
			: _data{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			unique_ptr(xns::null) noexcept
			: unique_ptr{ } {
				// code here...
			}

			/* non-copyable class */
			NON_COPYABLE(unique_ptr);

			/* self move constructor */
			unique_ptr(self&& other) noexcept
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* derived move constructor */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			unique_ptr(unique_ptr<D>&& other) noexcept
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			~unique_ptr(void) {
				// check pointer validity
				if (_data != nullptr) {
					// destroy object
					allocator::destroy(_data);
					// deallocate memory
					allocator::deallocate(_data);
				}
			}


			// -- P U B L I C  A S S I G N M E N T ----------------------------

			/* nullptr assignment */
			self& assign(xns::null) {
				// clean up
				reset();
				// return self reference
				return *this;
			}

			/* self move assignment */
			self& assign(self&& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					this->~unique_ptr();
					// initialize pointer
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}

			/* derived move assignment */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			self& assign(unique_ptr<D>&& other) {
				// check for self assignment
				if (this != reinterpret_cast<self*>(&other)) {
					// deallocate memory
					this->~unique_ptr();
					// initialize pointer
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* nullptr assignment operator */
			self& operator=(xns::null) {
				// return nullptr assignment
				return assign(nullptr);
			}

			/* self move assignment operator */
			self& operator=(self&& other) {
				// return self move assignment
				return assign(Xf::move(other));
			}

			/* derived move assignment operator */
			template <class D> requires (Xf::is_base_of_c<T, D>)
			self& operator=(unique_ptr<D>&& other) {
				// return derived move assignment
				return assign(Xf::move(other));
			}


			// -- P U B L I C  A C C E S S O R S  O P E R A T O R S -----------

			/* dereference operator */
			reference operator*(void) {
				// return reference
				return *_data;
			}

			/* const dereference operator */
			const_reference operator*(void) const {
				// return const reference
				return *_data;
			}

			/* arrow operator */
			mutable_pointer operator->(void) {
				// return pointer
				return _data;
			}

			/* const arrow operator */
			const_pointer operator->(void) const {
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
			bool operator==(const self& other) const noexcept {
				// return pointer equality
				return _data == other._data;
			}

			/* inequality operator */
			bool operator!=(const self& other) const noexcept {
				// return pointer inequality
				return _data != other._data;
			}

			/* nullptr equality operator */
			bool operator==(xns::null) const noexcept {
				// return pointer invalidity
				return _data == nullptr;
			}

			/* nullptr inequality operator */
			bool operator!=(xns::null) const noexcept {
				// return pointer validity
				return _data != nullptr;
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* reset pointer */
			void reset(void) {
				// check pointer validity
				if (_data != nullptr) {
					// destroy object
					allocator::destroy(_data);
					// deallocate memory
					allocator::deallocate(_data);
					// invalidate pointer
					_data = nullptr;
				}
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			mutable_pointer _data;


	};


	// -- F R I E N D  F U N C T I O N S --------------------------------------

	/* make unique pointer */
	template <class T, class... A>
	unique_ptr<T> make_unique_pointer(A&&... args) {
		// instantiate unique pointer
		unique_ptr<T> ptr;
		// allocate memory
		ptr._data = unique_ptr<T>::allocator::allocate();
		// check allocation success
		if (ptr._data) {
			// construct object by forwarding arguments
			unique_ptr<T>::allocator::construct(ptr._data, Xf::forward<A>(args)...);
		} // return instance
		return ptr;
	}

}

#endif
