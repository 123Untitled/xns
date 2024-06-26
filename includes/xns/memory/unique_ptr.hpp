/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_UNIQUE_PTR_HEADER
#define XNS_UNIQUE_PTR_HEADER

#include "xns/type_traits/relationships_and_property_queries/is_base_of.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_derived_from.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"

#include "xns/type_traits/types.hpp"

#include "xns/memory/allocator.hpp"
#include "xns/memory/lifecycle.hpp"
#include "xns/memory/allocator_traits.hpp"
#include "xns/memory/memory.hpp"


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

			/* allocator type */
			using allocator  = xns::allocator<type>;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline unique_ptr(void) noexcept
			: _data{nullptr} {
			}

			/* nullptr constructor */
			inline unique_ptr(xns::null) noexcept
			: _data{nullptr} {
			}

			/* pointer constructor */
			inline unique_ptr(mut_ptr ptr) noexcept
			: _data{ptr} {
			}

			/* non-copyable class */
			non_copyable(unique_ptr);

			/* self move constructor */
			inline unique_ptr(self&& other) noexcept
			: _data(other._data) {
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
				free();
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
					free();
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
					free();
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

			/* get */
			inline auto get(void) noexcept -> mut_ptr {
				return _data;
			}

			/* const get */
			inline auto get(void) const noexcept -> const_ptr {
				return _data;
			}



			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
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

			/* reset */
			inline auto reset(void) noexcept -> void {
				free(); init();
			}

			/* release */
			inline auto release(void) noexcept -> mut_ptr {
				// get pointer
				mut_ptr ptr = _data;
				// invalidate pointer
				_data = nullptr;
				// return pointer
				return ptr;
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
				_data = nullptr;
			}

			/* deallocate memory */
			inline auto free(void) noexcept -> void {
				// check pointer validity
				if (_data == nullptr)
					return;

				allocator a;

				xns::lifecycle<type>::destroy(_data);
				xns::allocator_traits<allocator>::deallocate(a, _data);

				// destroy object
				//allocator::destroy(_data);
				//// deallocate memory
				//allocator::deallocate(_data);
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

		xns::allocator<T> a;

		// allocate memory
		ptr._data = xns::allocator_traits<xns::allocator<T>>::allocate(a, 1);

		xns::lifecycle<T>::construct(ptr._data, xns::forward<A>(args)...);

		// construct object by forwarding arguments
		// return unique pointer
		return ptr;
	}

} // namespace xns

#endif // XNS_UNIQUE_PTR_HEADER
