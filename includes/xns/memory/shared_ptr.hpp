/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_SHARED_PTR_HEADER
#define XNS_SHARED_PTR_HEADER

// local headers
#include "xns/memory/allocator.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_derived_from.hpp"
#include "xns/utility/swap.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S H A R E D  P O I N T E R ------------------------------------------

	template <typename T>
	class shared_ptr final {


		// -- friends ---------------------------------------------------------

		/* weak pointer as friend */
		template <typename>
		friend class weak_ptr;

		/* derived types as friend */
		template <typename>
		friend class shared_ptr;

		/* make shared pointer as friend */
		template <typename U, typename... A>
		friend auto make_shared(A&&... args) -> xns::shared_ptr<U>;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self        = xns::shared_ptr<T>;

			/* value type */
			using value_type  = T;

			/* mutable reference type */
			using mut_ref     = value_type&;

			/* move reference type */
			using move_ref    = value_type&&;

			/* const reference type */
			using const_ref   = const value_type&;

			/* mutable pointer type */
			using mut_ptr     = value_type*;

			/* const pointer type */
			using const_ptr   = const value_type*;

			/* allocator type */
			using allocator   = xns::allocator<value_type>;

			/* size type */
			using size_type   = typename allocator::size_type;



			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline shared_ptr(void) noexcept
			: _data{nullptr}, _count{nullptr} {
			}

			/* nullptr constructor */
			inline shared_ptr(xns::null) noexcept
			: shared_ptr{} {
			}

			/* self copy constructor */
			inline shared_ptr(const self& other) noexcept
			: _data{other._data}, _count{other._count} {
				// increment number of references
				this->increment();
			}

			/* derived copy constructor */
			template <typename D> requires xns::is_derived_from<D, value_type>
			inline shared_ptr(const xns::shared_ptr<D>& other) noexcept
			: _data{other._data}, _count{other._count} {
				// increment number of references
				this->increment();
			}

			/* self move constructor */
			inline shared_ptr(self&& other) noexcept
			: _data{other._data}, _count{other._count} {
				// invalidate other
				other.init();
			}

			/* derived move constructor */
			template <typename D> requires xns::is_derived_from<D, value_type>
			inline shared_ptr(xns::shared_ptr<D>&& other) noexcept
			: _data{other._data}, _count{other._count} {
				// invalidate other
				other.init();
			}

			/* destructor */
			inline ~shared_ptr(void) noexcept {
				this->free();
			}


			// -- public assignment -------------------------------------------

			/* nullptr assignment */
			inline auto assign(xns::null) noexcept -> void {
				reset();
			}

			/* self copy assignment */
			auto assign(const self& other) noexcept -> void {
				// check for self assignment
				if (this == &other)
					return;
				// deallocate memory
				this->free();
				// assign pointer and counter
				_data  = other._data;
				_count = other._count;
				// increment number of references
				this->increment();
			}

			/* derived copy assignment */
			template <typename D> requires xns::is_derived_from<D, value_type>
			auto assign(const xns::shared_ptr<D>& other) noexcept -> void {
				// check for self assignment
				if (this == reinterpret_cast<self*>(&other))
					return;
				// deallocate memory
				this->free();
				// assign pointer and counter
				_data  = other._data;
				_count = other._count;
				// increment number of references
				this->increment();
			}


			/* self move assignment */
			auto assign(self&& other) noexcept -> void {
				// check for self assignment
				if (this == &other)
					return;
				// deallocate memory
				this->free();
				// assign pointer and counter
				_data  = other._data;
				_count = other._count;
				// invalidate other
				other.init();
			}

			/* derived move assignment */
			template <class D> requires xns::is_derived_from<D, value_type>
			auto assign(xns::shared_ptr<D>&& other) noexcept -> void {
				// check for self assignment
				if (this == reinterpret_cast<self*>(&other))
					return;
				// deallocate memory
				this->free();
				// assign pointer and counter
				_data  = other._data;
				_count = other._count;
				// invalidate other
				other.init();
			}


			// -- public assignment operators ---------------------------------

			/* nullptr assignment operator */
			inline auto operator=(xns::null) noexcept -> self& {
				this->assign(nullptr);
				return *this;
			}

			/* self copy assignment operator */
			inline auto operator=(const self& other) noexcept -> self& {
				this->assign(other);
				return *this;
			}

			/* derived copy assignment operator */
			template <class D> requires xns::is_derived_from<D, value_type>
			inline auto operator=(const xns::shared_ptr<D>& other) noexcept -> self& {
				this->assign(other);
				return *this;
			}

			/* self move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				this->assign(xns::move(other));
				return *this;
			}

			/* derived move assignment operator */
			template <class D> requires xns::is_derived_from<D, value_type>
			inline auto operator=(xns::shared_ptr<D>&& other) noexcept -> self& {
				this->assign(xns::move(other));
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* count */
			inline auto count(void) const noexcept -> size_type {
				return _data != nullptr ? *_count : 0;
			}

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
			explicit inline operator bool(void) const noexcept {
				return _data != nullptr;
			}

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
				return _data == nullptr;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline auto operator==(const self& other) const noexcept -> bool {
				return _data == other._data;
			}

			/* inequality operator */
			inline auto operator!=(const self& other) const noexcept -> bool {
				return _data != other._data;
			}

			/* nullptr equality operator */
			inline auto operator==(xns::null) const noexcept -> bool {
				return _data == nullptr;
			}

			/* nullptr inequality operator */
			inline auto operator!=(xns::null) const noexcept -> bool {
				return _data != nullptr;
			}


			// -- public modifiers --------------------------------------------

			/* swap */
			inline auto swap(self& other) noexcept -> void {
				// swap pointers
				xns::swap(_data, other._data);
				// swap counters
				xns::swap(_count, other._count);
			}

			/* reset */
			auto reset(void) noexcept -> void {
				this->free();
				this->init();
			}


		private:

			// -- private methods ---------------------------------------------

			/* free */
			auto free(void) noexcept -> void {
				// check pointer validity
				if (_data == nullptr)
					return;
				// check there are still references
				if (--(*_count) > 0)
					return;
				// destroy object
				allocator::destroy(_data);
				// deallocate object
				allocator::deallocate(_data);
				// deallocate counter
				xns::allocator<size_type>::deallocate(_count);
				std::cout << "deallocated" << std::endl;
			}

			/* init */
			inline auto init(void) noexcept -> void {
				_data  = nullptr;
				_count = nullptr;
			}

			/* increment */
			inline auto increment(void) noexcept -> void {
				// check pointer validity
				if (_data == nullptr)
					return;
				// increment number of references
				++(*_count);
			}


			// -- private members ---------------------------------------------

			/* data */
			mut_ptr _data;

			/* count */
			size_type* _count;

	};


	// -- friend functions ----------------------------------------------------

	/* make shared pointer */
	template <typename T, typename... A>
	auto make_shared(A&&... args) -> xns::shared_ptr<T> {
		// instantiate shared pointer
		xns::shared_ptr<T> ptr;
		// allocate memory
		ptr._data = shared_ptr<T>::allocator::allocate();

		// here need to try catch

			// allocate counter
			ptr._count = xns::allocator<typename shared_ptr<T>::size_type>::allocate();

			// construct object by forwarding arguments
			xns::shared_ptr<T>::allocator::construct(ptr._data, xns::forward<A>(args)...);

		// initialize counter
		*ptr._count = 1;
		// return shared pointer
		return ptr;
	}




}

#endif
