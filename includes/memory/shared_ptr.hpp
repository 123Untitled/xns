#ifndef SHARED_PTR_HEADER
#define SHARED_PTR_HEADER

// local headers
#include "types.hpp"
#include "macros.hpp"
#include "allocator.hpp"
#include "inheritance.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S H A R E D  P O I N T E R  C L A S S -------------------------------

	template <typename T>
	class shared_ptr final {


		public:

			// -- public types ------------------------------------------------

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


			// -- friends -----------------------------------------------------

			/* weak pointer as friend */
			template <typename>
			friend class weak_ptr;

			/* derived types as friend */
			template <typename>
			friend class shared_ptr;

			/* make shared pointer as friend */
			template <typename U, typename... A>
			friend auto make_shared(A&&... args) -> xns::shared_ptr<U>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			shared_ptr(void) noexcept
			: _data{nullptr}, _count{nullptr} {}

			/* nullptr constructor */
			shared_ptr(xns::null) noexcept
			: shared_ptr{} {}

			/* self copy constructor */
			shared_ptr(const self& other) noexcept
			: _data{other._data}, _count{other._count} {
				// increment number of references
				if (_data) { ++(*_count); }
			}

			/* derived copy constructor */
			template <class D> requires xns::is_derived_from<D, value_type>
			shared_ptr(const shared_ptr<D>& other) noexcept
			: _data{other._data}, _count{other._count} {
				// increment number of references
				if (_data) { ++(*_count); }
			}

			/* self move constructor */
			shared_ptr(self&& other) noexcept
			: _data{other._data}, _count{other._count} {
				// invalidate other
				other._data  = nullptr;
				other._count = nullptr;
			}

			/* derived move constructor */
			template <class D> requires xns::is_derived_from<D, value_type>
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
			inline auto assign(xns::null) -> self& {
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
			template <class D> requires xns::is_derived_from<D, value_type>
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
			template <class D> requires xns::is_derived_from<D, value_type>
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
			self& operator=(xns::null) {
				// return nullptr assignment
				return assign(nullptr);
			}

			/* self copy assignment operator */
			shared_ptr& operator=(const self& other) {
				// return self copy assignment
				return assign(other);
			}

			/* derived copy assignment operator */
			template <class D> requires xns::is_derived_from<D, value_type>
			shared_ptr& operator=(const shared_ptr<D>& other) {
				// return derived copy assignment
				return assign(other);
			}

			/* self move assignment operator */
			shared_ptr& operator=(self&& other) {
				// return self move assignment
				return assign(xns::move(other));
			}

			/* derived move assignment operator */
			template <class D> requires xns::is_derived_from<D, value_type>
			shared_ptr& operator=(shared_ptr<D>&& other) {
				// return derived move assignment
				return assign(xns::move(other));
			}


			// -- public accessors --------------------------------------------

			/* count */
			inline auto count(void) const noexcept -> size_type {
				// return number of references
				return _data ? *_count : 0;
			}

			/* dereference operator */
			inline auto operator*(void) noexcept -> reference {
				// return reference
				return *_data;
			}

			/* const dereference operator */
			inline auto operator*(void) const noexcept -> const_reference {
				// return const reference
				return *_data;
			}

			/* arrow operator */
			inline auto operator->(void) noexcept -> mutable_pointer {
				// return pointer
				return _data;
			}

			/* const arrow operator */
			inline auto operator->(void) const noexcept -> const_pointer {
				// return const pointer
				return _data;
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline operator bool(void) const noexcept {
				// return pointer validity
				return _data != nullptr;
			}

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
				// return pointer invalidity
				return _data == nullptr;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline auto operator==(const self& other) const noexcept -> bool {
				// return pointer equality
				return _data == other._data;
			}

			/* inequality operator */
			inline auto operator!=(const self& other) const noexcept -> bool {
				// return pointer inequality
				return _data != other._data;
			}

			/* nullptr equality operator */
			inline auto operator==(xns::null) const noexcept -> bool {
				// return pointer invalidity
				return _data == nullptr;
			}

			/* nullptr inequality operator */
			inline auto operator!=(xns::null) const noexcept -> bool {
				// return pointer validity
				return _data != nullptr;
			}


			// -- public modifiers --------------------------------------------

			/* reset */
			auto reset(void) noexcept -> void {
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




		private:

			// -- private members ---------------------------------------------

			/* data */
			mutable_pointer _data;

			/* count */
			size_type* _count;

	};


	// -- F R I E N D  F U N C T I O N S --------------------------------------

	/* make shared pointer */
	template <typename T, typename... A>
	auto make_shared(A&&... args) -> xns::shared_ptr<T> {
		// instantiate shared pointer
		xns::shared_ptr<T> ptr;
		// allocate memory
		ptr._data = shared_ptr<T>::allocator::allocate();
		// allocate counter
		ptr._count = xns::allocator<typename shared_ptr<T>::size_type>::allocate();
		// construct object by forwarding arguments
		shared_ptr<T>::allocator::construct(ptr._data, xns::forward<A>(args)...);
		// initialize counter
		*ptr._count = 1;
		// return shared pointer
		return ptr;
	}




}

#endif
