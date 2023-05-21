#ifndef SHARED_PTR_HEADER
#define SHARED_PTR_HEADER

#include "types.hpp"
#include "macro.hpp"
#include "type_traits.hpp"
#include "allocator.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- S H A R E D  P O I N T E R  C L A S S -------------------------------

	template <class T>
	class shared_ptr final {

		public:

			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = shared_ptr<value_type>;

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

			/* size type */
			using size_type       = typename allocator::size_type;


			// -- F R I E N D S -----------------------------------------------

			/* weak pointer as friend */
			template <class U>
			friend class weak_ptr;

			/* derived types as friend */
			template <class>
			friend class shared_ptr;

			/* make shared pointer as friend */
			template <class U, class... A>
			friend shared_ptr<U> make_shared_pointer(A&&... args);


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			shared_ptr(void) noexcept
			: _data{nullptr}, _count{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			shared_ptr(Xf::Nullptr) noexcept
			: shared_ptr{ } {
				// code here...
			}

			/* self copy constructor */
			shared_ptr(const self& other) noexcept
			: _data{other._data}, _count{other._count} {
				// check pointer validity
				if (_data) {
					// increment number of references
					++(*_count);
				}
			}

			/* derived copy constructor */
			template <class D> requires Xf::is_base_of_c<T, D>
			shared_ptr(const shared_ptr<D>& other) noexcept
			: _data{other._data}, _count{other._count} {
				// check pointer validity
				if (_data) {
					// increment number of references
					++(*_count);
				}
			}

			/* self move constructor */
			shared_ptr(self&& other) noexcept
			: _data{other._data}, _count{other._count} {
				// invalidate other
				other._data  = nullptr;
				other._count = nullptr;
			}

			/* derived move constructor */
			template <class D> requires Xf::is_base_of_c<T, D>
			shared_ptr(shared_ptr<D>&& other) noexcept
			: _data{other._data}, _count{other._count} {
				// invalidate other
				other._data  = nullptr;
				other._count = nullptr;
			}

			/* destructor */
			~shared_ptr(void) {
				// check pointer validity
				if ((_data != nullptr) && (--(*_count) == 0)) {
					// destroy object
					allocator::destroy(_data);
					// deallocate memory
					allocator::deallocate(_data);
					// deallocate counter
					xns::allocator<size_type>::deallocate(_count);
				}
			}


			// -- P U B L I C  A S S I G N M E N T ----------------------------

			/* nullptr assignment */
			self& assign(Xf::Nullptr) {
				// clean up
				reset();
				// return self reference
				return *this;
			}

			/* self copy assignment */
			self& assign(const self& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					this->~shared_ptr();
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
			self& assign(const shared_ptr<D>& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					this->~shared_ptr();
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
			self& assign(self&& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					this->~shared_ptr();
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
			self& assign(shared_ptr<D>&& other) {
				// check for self assignment
				if (this != reinterpret_cast<self*>(&other)) {
					// deallocate memory
					this->~shared_ptr();
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
			self& operator=(Xf::Nullptr) {
				// return nullptr assignment
				return assign(nullptr);
			}

			/* self copy assignment operator */
			shared_ptr& operator=(const self& other) {
				// return self copy assignment
				return assign(other);
			}

			/* derived copy assignment operator */
			template <class D> requires Xf::is_base_of_c<T, D>
			shared_ptr& operator=(const shared_ptr<D>& other) {
				// return derived copy assignment
				return assign(other);
			}

			/* self move assignment operator */
			shared_ptr& operator=(self&& other) {
				// return self move assignment
				return assign(Xf::move(other));
			}

			/* derived move assignment operator */
			template <class D> requires Xf::is_base_of_c<T, D>
			shared_ptr& operator=(shared_ptr<D>&& other) {
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
					allocator::destroy(_data);
					// deallocate memory
					allocator::deallocate(_data);
					// deallocate counter
					xns::allocator<size_type>::deallocate(_count);
					// initialize pointer
					_data = nullptr;
					// initialize counter
					_count = nullptr;
				}
			}

			/* count */
			size_type count(void) const {
				// return number of references
				return _data ? *_count : 0;
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* data */
			mutable_pointer _data;

			/* count */
			size_type* _count;

	};


	// -- F R I E N D  F U N C T I O N S --------------------------------------

	/* make shared pointer */
	template <class T, class... A>
	shared_ptr<T> make_shared_pointer(A&&... args) {
		// instantiate shared pointer
		shared_ptr<T> ptr;
		// allocate memory
		ptr._data = shared_ptr<T>::allocator::allocate();
		// check allocation failure
		if (ptr._data == nullptr) { return ptr; }
		// allocate counter
		ptr._count = xns::allocator<typename shared_ptr<T>::size_type>::allocate();
		// check allocation failure
		if (ptr._count == nullptr) {
			// deallocate memory
			shared_ptr<T>::allocator::deallocate(ptr._data);
			// set pointer to nullptr
			ptr._data = nullptr;
			// return shared pointer
			return ptr;
		} // else construct object by forwarding arguments
		shared_ptr<T>::allocator::construct(ptr._data, Xf::forward<A>(args)...);
		// initialize counter
		*ptr._count = 1;
		// return shared pointer
		return ptr;
	}




}

#endif
