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

#ifndef XNS_WEAK_PTR_HEADER
#define XNS_WEAK_PTR_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_derived_from.hpp"
#include "xns/type_traits/type_operations/move.hpp"

#include "xns/memory/allocator.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	/* unique pointer forward declaration */
	template <class>
	class unique_ptr;

	/* shared pointer forward declaration */
	template <class>
	class shared_ptr;


	// -- W E A K  P O I N T E R  C L A S S -----------------------------------

	template <class T>
	class weak_ptr final {

		public:

			// -- F R I E N D S -----------------------------------------------

			/* derived types as friend */
			template <class>
			friend class weak_ptr;


			// -- P U B L I C  A L I A S E S ----------------------------------

			/* value type */
			using value_type      = T;

			/* self type */
			using self            = weak_ptr<value_type>;

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

			/* size type */
			using size_type       = xns::size_t;


			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			weak_ptr(void) noexcept
			: _data{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			weak_ptr(xns::null) noexcept
			: weak_ptr{ } {
				// code here...
			}

			/* pointer constructor */
			weak_ptr(mutable_pointer ptr) noexcept
			: _data{ptr} {
				// code here...
			}

			/* unique pointer constructor */
			template <class D>
			weak_ptr(const xns::unique_ptr<D>& unique) noexcept
			requires (xns::is_derived_from<D, value_type>)
			: _data{unique._data} {
				// code here...
			}

			/* shared pointer constructor */
			template <class D>
			weak_ptr(const xns::shared_ptr<D>& shared) noexcept
			requires (xns::is_derived_from<D, value_type>)
			: _data{shared._data} {
				// code here...
			}

			/* copy constructor */
			weak_ptr(const self& other) noexcept
			: _data{other._data} {
				// code here...
			}

			/* derived copy constructor */
			template <class D>
			weak_ptr(const weak_ptr<D>& other) noexcept
			requires (xns::is_derived_from<D, value_type>)
			: _data{other._data} {
				// code here...
			}

			/* move constructor */
			weak_ptr(self&& other) noexcept
			: _data{other._data} {
				// invalidate other
				other._data = nullptr;
			}

			/* derived move constructor */
			template <class D>
			weak_ptr(weak_ptr<D>&& other) noexcept
			requires (xns::is_derived_from<D, value_type>)
			: _data{other._data} {
				// invalidate other
				other._data = nullptr;
			}

			/* destructor */
			~weak_ptr(void) noexcept = default;


			// -- P U B L I C  A S S I G N M E N T ----------------------------

			/* nullptr assignment */
			self& assign(xns::null) noexcept {
				// assign null pointer
				_data = nullptr;
				// return self reference
				return *this;
			}

			/* pointer assignment */
			self& assign(mutable_pointer ptr) noexcept {
				// assign pointer
				_data = ptr;
				// return self reference
				return *this;
			}

			/* copy assignment */
			self& assign(const self& other) noexcept {
				// assign other data
				_data = other._data;
				// return self reference
				return *this;
			}

			/* derived copy assignment */
			template <class D>
			self& assign(const weak_ptr<D>& other) noexcept
			requires (xns::is_derived_from<D, value_type>) {
				// assign other data
				_data = other._data;
				// return self reference
				return *this;
			}

			/* move assignment */
			self& assign(self&& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// assign other data
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}

			/* derived move assignment */
			template <class D>
			self& assign(weak_ptr<D>&& other) noexcept
			requires (xns::is_derived_from<D, value_type>) {
				// check for self assignment
				if (this != &other) {
					// assign other data
					_data = other._data;
					// invalidate other
					other._data = nullptr;
				} // return self reference
				return *this;
			}

			/* unique pointer assignment */
			template <class D>
			self& assign(const xns::unique_ptr<D>& ptr) noexcept
			requires (xns::is_derived_from<D, value_type>) {
				// assign pointer
				_data = ptr._data;
				// return self reference
				return *this;
			}

			/* shared pointer assignment */
			template <class D>
			self& assign(const xns::shared_ptr<D>& ptr) noexcept
			requires (xns::is_derived_from<D, value_type>) {
				// assign pointer
				_data = ptr._data;
				// return self reference
				return *this;
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* nullptr assignment operator */
			self& operator=(xns::null) noexcept {
				// return nullptr assignment
				return assign(nullptr);
			}

			/* pointer assignment operator */
			self& operator=(mutable_pointer ptr) noexcept {
				// return pointer assignment
				return assign(ptr);
			}

			/* copy assignment operator */
			self& operator=(const self& other) noexcept {
				// return copy assignment
				return assign(other);
			}

			/* derived copy assignment operator */
			template <class D>
			self& operator=(const weak_ptr<D>& other) noexcept
			requires (xns::is_derived_from<D, value_type>) {
				// return derived copy assignment
				return assign(other);
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// return move assignment
				return assign(xns::move(other));
			}

			/* derived move assignment operator */
			template <class D>
			self& operator=(weak_ptr<D>&& other) noexcept
			requires (xns::is_derived_from<D, value_type>) {
				// return derived move assignment
				return assign(xns::move(other));
			}

			/* unique pointer assignment operator */
			template <class D>
			self& operator=(const xns::unique_ptr<D>& ptr) noexcept
			requires (xns::is_derived_from<D, value_type>) {
				// return unique pointer assignment
				return assign(ptr);
			}

			/* shared pointer assignment operator */
			template <class D>
			self& operator=(const xns::shared_ptr<D>& ptr) noexcept
			requires (xns::is_derived_from<D, value_type>) {
				// return shared pointer assignment
				return assign(ptr);
			}


			// -- P U B L I C  A C C E S S O R S  O P E R A T O R S -----------

			/* dereference operator */
			reference operator*(void) noexcept {
				// return reference
				return *_data;
			}

			/* const dereference operator */
			const_reference operator*(void) const noexcept {
				// return const reference
				return *_data;
			}

			/* arrow operator */
			mutable_pointer operator->(void) noexcept {
				// return pointer
				return _data;
			}

			/* const arrow operator */
			const_pointer operator->(void) const noexcept {
				// return const pointer
				return _data;
			}


			// -- P U B L I C  B O O L E A N S  O P E R A T O R S -------------

			/* boolean operator */
			operator bool(void) const noexcept {
				// return pointer validity
				return _data != nullptr;
			}

			/* not operator */
			bool operator!(void) const noexcept {
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

			/* null equality operator */
			bool operator==(xns::null) const noexcept {
				// return pointer invalidity
				return _data == nullptr;
			}

			/* null inequality operator */
			bool operator!=(xns::null) const noexcept {
				// return pointer validity
				return _data != nullptr;
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* pointer */
			mutable_pointer _data;



	};


}

#endif
