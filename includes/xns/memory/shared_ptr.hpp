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
#include "xns/memory/allocator_traits.hpp"
#include "xns/memory/lifecycle.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_derived_from.hpp"
#include "xns/utility/swap.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S H A R E D  P O I N T E R ------------------------------------------

	template <typename ___type>
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
			using self        = xns::shared_ptr<___type>;

			/* value type */
			using value_type  = ___type;

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


		private:

			// -- private types -----------------------------------------------

			/* allocator traits type */
			using ___alloc_traits = xns::allocator_traits<allocator>;

			/* count allocator type */
			using ___count_alloc = typename ___alloc_traits::template rebind_alloc<size_type>;

			/* count allocator traits type */
			using ___count_alloc_traits = xns::allocator_traits<___count_alloc>;

			/* lifecycle type */
			using ___lifecycle = xns::lifecycle<value_type>;



		public:

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
				___lifecycle::destroy(_data);

				allocator alloc{};

				// deallocate object
				___alloc_traits::deallocate(alloc, _data);

				___count_alloc count_alloc{};

				// deallocate counter
				___count_alloc_traits::deallocate(count_alloc, _count);
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
	template <typename ___type, typename... ___params>
	auto make_shared(___params&&... ___args) -> xns::shared_ptr<___type> {

		using ___shared = xns::shared_ptr<___type>;
		using ___alloc  = typename ___shared::allocator;

		// instantiate shared pointer
		___shared ptr;

		___alloc alloc{};

		// allocate memory
		ptr._data = ___shared::___alloc_traits::allocate(alloc);

		// here need to try catch

		using ___calloc = typename ___shared::___count_alloc;
		using ___calloc_traits = xns::allocator_traits<___calloc>;

		___calloc count_alloc{};

		// allocate counter
		ptr._count = ___calloc_traits::allocate(count_alloc);

		// construct object by forwarding arguments
		___shared::___lifecycle::construct(ptr._data, xns::forward<___params>(___args)...);

		// initialize counter
		*ptr._count = 1;

		// return shared pointer
		return ptr;
	}




}

#endif
