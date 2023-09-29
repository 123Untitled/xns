#ifndef XNS_UNIQUE_PTR_HEADER
#define XNS_UNIQUE_PTR_HEADER

#include "types.hpp"
#include "allocator.hpp"
#include "inheritance.hpp"
#include "is_same.hpp"
#include "memory.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- U N I Q U E  P T R --------------------------------------------------

	template <typename T>
	class unique_ptr final {


		// -- friends ---------------------------------------------------------

		/* weak pointer as friend */
		template <typename>
		friend class weak_ptr;

		/* derived types as friend */
		template <typename>
		friend class unique_ptr;

		/* make unique as friend */
		template <typename U, typename... A>
		friend auto make_unique(A&&...) -> xns::unique_ptr<U>;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::unique_ptr<T>;

			/* value type */
			using type       = T;

			/* reference type */
			using mut_ref    = type&;

			/* move reference type */
			using move_ref   = type&&;

			/* const reference type */
			using const_ref  = const type&;

			/* pointer type */
			using mut_ptr    = type*;

			/* const pointer type */
			using const_ptr  = const type*;


		private:

			// -- private types -----------------------------------------------

			/* allocator type */
			using allocator  = xns::memory::pool<type>;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline unique_ptr(void) noexcept
			: _data{nullptr} {}

			/* nullptr constructor */
			inline unique_ptr(xns::null) noexcept
			: unique_ptr{} {}

			/* non-copyable class */
			NON_COPYABLE(unique_ptr);

			/* self move constructor */
			inline unique_ptr(self&& other) noexcept
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* derived move constructor */
			template <typename D> requires (xns::is_derived_from<D, type>)
			inline unique_ptr(xns::unique_ptr<D>&& other) noexcept
			: _data(other._data) {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			inline ~unique_ptr(void) noexcept {
				// deallocate memory
				free_ptr();
			}


			// -- public assignments ------------------------------------------

			/* nullptr assignment */
			inline auto assign(xns::null) noexcept -> void {
				// clean up
				reset();
			}

			/* self move assignment */
			auto assign(self&& other) noexcept -> void {
				// check for self assignment
				if (this != &other) {
					// deallocate memory
					free_ptr();
					// move other
					_data = other._data;
					// invalidate other
					other._data = nullptr; }
			}

			/* derived move assignment */
			template <class D> requires (xns::is_derived_from<D, type>)
			auto assign(unique_ptr<D>&& other) noexcept -> void {
				// check for self assignment
				if (this != reinterpret_cast<self*>(&other)) {
					// deallocate memory
					free_ptr();
					// move other
					_data = other._data;
					// invalidate other
					other._data = nullptr; }
			}


			// -- public assignment operators ---------------------------------

			/* nullptr assignment operator */
			inline auto operator=(xns::null) noexcept -> self& {
				// call nullptr assignment
				assign(nullptr);
				return *this;
			}

			/* self move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// call self move assignment
				assign(xns::move(other));
				return *this;
			}

			/* derived move assignment operator */
			template <typename D> requires (xns::is_derived_from<D, type>)
			inline auto operator=(xns::unique_ptr<D>&& other) noexcept -> self& {
				// call derived move assignment
				assign(xns::move(other));
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* dereference operator */
			inline auto operator*(void) noexcept -> mut_ref {
				return *_data;
			}

			/* const dereference operator */
			inline auto operator*(void) const noexcept -> const_ref {
				return *_data;
			}

			/* arrow operator */
			inline auto operator->(void) noexcept -> mut_ptr {
				return _data;
			}

			/* const arrow operator */
			inline auto operator->(void) const noexcept -> const_ptr {
				return _data;
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline operator bool(void) const noexcept {
				return _data != nullptr;
			}

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
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

			/* reset pointer */
			inline auto reset(void) noexcept -> void {
				free_ptr();
				init();
			}


			// -- public conversion -------------------------------------------

			/* base reference cast */
			template <typename B>
			inline auto as(void) noexcept -> xns::unique_ptr<B>& {
				static_assert(xns::is_base_of<B, type>, "WOOO, THIS CAST IS NOT ALLOWED");
				// return casted reference
				return reinterpret_cast<unique_ptr<B>&>(*this);
			}

			/* base const reference cast */
			template <typename B>
			inline auto as(void) const noexcept -> const unique_ptr<B>& {
				static_assert(xns::is_base_of<B, type>, "WOOO, THIS CAST IS NOT ALLOWED");
				// return casted const reference
				return reinterpret_cast<const unique_ptr<B>&>(*this);
			}


		private:


			// -- private methods ---------------------------------------------

			/* init */
			inline auto init(void) noexcept -> void {
				// initialize pointer
				_data = nullptr;
			}

			/* deallocate memory */
			inline auto free_ptr(void) noexcept -> void {
				// check pointer validity
				if (_data != nullptr) {
					// destroy object
					allocator::destroy(_data);
					// deallocate memory
					allocator::deallocate(_data);
				}
			}


			// -- private members ---------------------------------------------

			/* data */
			self::mut_ptr _data;


	};


	// -- non-member functions ------------------------------------------------

	/* make unique */
	template <typename T, typename... A>
	auto make_unique(A&&... args) -> xns::unique_ptr<T> {
		// instantiate unique pointer
		unique_ptr<T> ptr;
		// allocate memory
		ptr._data = unique_ptr<T>::allocator::allocate();
		// construct object by forwarding arguments
		unique_ptr<T>::allocator::construct(ptr._data, xns::forward<A>(args)...);
		// return unique pointer
		return ptr;
	}

}

#endif
