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

#ifndef XNS_VECTOR_HEADER
#define XNS_VECTOR_HEADER

#include "xns/config/config.hpp"

#include "xns/memory/allocator.hpp"
#include "xns/memory/allocator_traits.hpp"
#include "xns/memory/lifecycle.hpp"

#include "xns/memory/memcpy.hpp"
#include "xns/memory/memset.hpp"
#include "xns/memory/memmove.hpp"

#include "xns/iterator/distance.hpp"

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_comparable.hpp"

#include "xns/type_traits/supported_operations/is_trivially_destructible.hpp"
#include "xns/type_traits/supported_operations/is_trivially_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_trivially_move_constructible.hpp"

#include "xns/type_traits/supported_operations/is_nothrow_copy_assignable.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_moveable.hpp"

#include "xns/type_traits/other/type_at.hpp"

#include "xns/utility/swap.hpp"


#include <iostream>
#include <unistd.h>


#include "xns/containers/container_traits.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	// -- V E C T O R ---------------------------------------------------------

	/* vector */
	template <typename ___type,
			  typename ___alloc = xns::allocator<___type>>
	class vector final {


		// -- assertions ------------------------------------------------------

		/* requires nothrow move semantic */
		static_assert(xns::is_nothrow_moveable<___type>,
					  "vector requires nothrow move semantic.");

		/* requires nothrow move semantic allocator */
		static_assert(xns::is_nothrow_moveable<___alloc>,
					  "vector requires nothrow move semantic allocator.");

		/* requires nothrow destructible type */
		static_assert(xns::is_nothrow_destructible<___type>,
					  "vector requires nothrow destructible type.");


		private:

			// -- forward declarations ----------------------------------------

			/* iterator */
			template <bool, bool>
			class ___iterator;


			// -- private types -----------------------------------------------

			/* self type */
			using ___self                = xns::vector<___type, ___alloc>;

			/* allocator traits type */
			using ___alloc_traits        = xns::allocator_traits<___alloc>;

			/* lifecycle type */
			using ___lifecycle           = xns::lifecycle<___type>;


			// -- debug -------------------------------------------------------

#ifdef XNS_TEST_VECTOR

			/* debug */
			template <unsigned ___sz>
			static constexpr auto _(const char (&___msg)[___sz]) -> void {
				::write(STDOUT_FILENO, "\x1b[31mvector: \x1b[0m", 17);
				::write(STDOUT_FILENO, ___msg, ___sz);
				::write(STDOUT_FILENO, "\n", 1);
			}
#else
#	define _(msg)
#endif


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type             = ___type;

			/* allocator type */
			using allocator_type         = ___alloc;

			/* size type */
			using size_type              = unsigned long long;

			/* difference type */
			using difference_type        = long long;

			/* reference type */
			using reference              = value_type&;

			/* const reference type */
			using const_reference        = const value_type&;

			/* pointer type */
			using pointer                = ___alloc_traits::pointer;

			/* const pointer type */
			using const_pointer          = ___alloc_traits::const_pointer;

			/* iterator type */
			using iterator               = ___iterator<false, false>;

			/* const iterator type */
			using const_iterator         = ___iterator<true, false>;

			/* reverse iterator */
			using reverse_iterator       = ___iterator<false, true>;

			/* const reverse iterator */
			using const_reverse_iterator = ___iterator<true, true>;


		private:

			// -- private enums -----------------------------------------------

			/* noexcept */
			enum : bool {
				___noexcept_allocate = noexcept(___alloc_traits::allocate(xns::declval<___alloc&>(), 0U)),
				___throw_copy        = !xns::is_nothrow_copy_constructible<value_type>,
				___trivial_destruct  = xns::is_trivially_destructible<value_type>,
				___trivial_copy      = xns::is_trivially_copyable<value_type>,
				___requires_destruct = !xns::is_trivially_destructible<value_type>
			};

			/* is allocator */
			template <typename ___tp>
			using ___is_allocator = xns::bool_constant<xns::same_as<xns::remove_cvref<___tp>, allocator_type>>;

			/* is value type */
			template <typename ___tp>
			using ___is_value_type = xns::bool_constant<xns::same_as<xns::remove_cvref<___tp>, value_type>>;


			// -- private members ---------------------------------------------

			/* allocator */
			[[no_unique_address]]
			allocator_type _allocator;

			/* data */
			pointer _data;

			/* end */
			pointer _end;

			/* end capacity */
			pointer _cap;


			// -- private classes ---------------------------------------------

			class ___destroy final {

				public:

					// -- public lifecycle ------------------------------------

					/* vector constructor */
					constexpr ___destroy(___self& ___v) noexcept
					: _vector{___v}, _complete{false} {
					}

					/* non-assignable class */
					___xns_not_assignable(___destroy);

					/* destructor */
					~___destroy(void) noexcept {
						if (not _complete) {
							_vector._clear();
							_vector._unsafe_deallocate();
						}
					}


					// -- public modifiers ------------------------------------

					/* complete */
					constexpr auto complete(void) noexcept -> void {
						_complete = true;
					}


				private:

					// -- private members -------------------------------------

					/* vector */
					___self& _vector;

					/* complete */
					bool _complete;

			}; // class ___destroy


		public:


			// -- debug -------------------------------------------------------

			auto print(void) const -> void {
				std::cout << "    size: " << size()     << "\r\n";
				std::cout << "capacity: " << capacity() << "\r\n";
				for (const auto& x : *this) {
					std::cout << x << " "; }
				std::cout << "\r\n";
			}


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr vector(void)
				// noexcept specification
				noexcept(xns::is_nothrow_default_constructible<allocator_type>)
			// initializer
			: _allocator{}, _data{nullptr}, _end{nullptr}, _cap{nullptr} {
				_("default constructor");
			}

			/* allocator constructor */
			template <typename ___tp> requires ___is_allocator<___tp>::value
			constexpr explicit vector(___tp&& ___a)
				// noexcept specification
				noexcept(xns::is_nothrow_constructible<allocator_type, ___tp&&>)
			// initializer
			: _allocator{xns::forward<___tp>(___a)}, _data{nullptr}, _end{nullptr}, _cap{nullptr} {
				_("allocator constructor");
			}

			/* fill emplace constructor */
			template <typename... ___params>
			constexpr vector(const size_type ___sz, const ___params&... ___args)
				// noexcept specification
				noexcept(false)
			// initializer
			: _allocator{}, _data{_allocate(___sz)}, _end{_data}, _cap{_data + ___sz} {

				_("emplace constructor");
				// fill construct elements
				_fill_construct(___args...);
			}

			/* fill emplace constructor with allocator */
			template <typename ___tp, typename... ___params> requires ___is_allocator<___tp>::value
			constexpr vector(___tp&& ___a, const size_type ___sz, const ___params&... ___args)
				// noexcept specification
				noexcept(false)
			// initializer
			: _allocator{xns::forward<___tp>(___a)}, _data{_allocate(___sz)}, _end{_data}, _cap{_data + ___sz} {

				_("emplace constructor with allocator");
				// fill construct elements
				_fill_construct(___args...);
			}

			/* copy constructor */
			constexpr vector(const ___self& ___ot) noexcept (false)
			// initializer
			: _allocator{___ot._allocator}, _data{nullptr}, _end{nullptr}, _cap{nullptr} {

				_("copy constructor");

				const auto ___sz = ___ot.size();

				_data = _end  = _allocate(___sz);
				_cap  = _data + ___sz;

				if constexpr (___trivial_copy) {
					xns::memcpy(_data, ___ot._data, ___sz);
				}

				else if constexpr (not ___throw_copy) {
					for (auto ___it = ___ot._data; ___it < ___ot._end; ++___it) {
						___lifecycle::construct(_end, *___it);
						++_end; }
				}

				else {
					// create destroy guard
					___destroy ___d{*this};
					for (auto ___it = ___ot._data; ___it < ___ot._end; ++___it) {
						___lifecycle::construct(_end, *___it);
						++_end; }
					// complete
					___d.complete();
				}

			}

			/* move constructor */
			constexpr vector(___self&& ___ot) noexcept
			// initializer
			: _allocator{xns::move(___ot._allocator)}, _data{___ot._data}, _end{___ot._end}, _cap{___ot._cap} {
				_("move constructor");
				// invalidate other
				___ot._init();
			}

			/* container constructor */
			template <xns::is_container ___container>
			constexpr vector(const ___container& ___c) noexcept(false)
			// initializer
			: _allocator{}, _data{nullptr}, _end{nullptr}, _cap{nullptr} {

				_("container constructor");

				const auto ___sz = xns::size(___c);

				_data = _end  = _allocate(___sz);
				_cap  = _data + ___sz;

				//if constexpr (___trivial_copy) {
				// here check if container is contiguous
				//
				//	xns::memcpy(_data, ___container_traits::data(___c), ___sz);
				//}

				if constexpr (not ___throw_copy) {
					const auto end = xns::end(___c);
					for (auto ___it = xns::begin(___c); ___it != end; ++___it) {
						___lifecycle::construct(_end, *___it);
						++_end; }
				}

				else {
					// create destroy guard
					___destroy ___d{*this};
					const auto end = xns::end(___c);
					for (auto ___it = xns::begin(___c); ___it != end; ++___it) {
						___lifecycle::construct(_end, *___it);
						++_end; }
					// complete
					___d.complete();
				}
			}


			/* iterator constructor */
			//template <typename ___it> requires (not xns::is_integral<___it>)
			//constexpr vector(___it first, ___it last) noexcept(false)
			//// initializer
			//: _allocator{}, _data{nullptr}, _end{nullptr}, _cap{nullptr} {
			//	
			//	_("iterator constructor");

				//// get distance
				//const auto ___dist = xns::distance(first, last);
				//
				//// check distance
				//if (___dist <= 0) {
				//	_("iterator constructor, distance <= 0");
				//	return;
				//}
				//
				//// allocate memory
				//_data = _allocate(___dist);
				//_end  = _data;
				//_cap  = _data + ___dist;
				//
				//// check for contiguous iterator
				//if constexpr (xns::random_access_iterator<typename xns::iterator_traits<___it>::iterator_category>
				//		   && xns::is_trivially_copyable<value_type>) {
				//	// copy elements
				//	xns::memcpy(_data, first, ___dist);
				//	_("iterator constructor, contiguous iterator, trivially copyable");
				//}
				//else if constexpr (xns::is_nothrow_copy_constructible<value_type>) {
				//
				//	// copy elements
				//	for (; first != last; ++first, ++_end)
				//		___lifecycle::construct(_end, *first);
				//}
				//else {
				//
				//	// create destroy guard
				//	___destroy ___d{*this};
				//
				//	// copy elements
				//	for (; first != last; ++first, ++_end)
				//		___lifecycle::construct(_end, *first);
				//
				//	// complete
				//	___d.complete();
				//}
			//}

			/* iterator constructor */
			//template <typename ___it>
			//constexpr vector(___it first, ___it last, const allocator_type& ___a = allocator_type{}) {
			//}


			///* allocation constructor WILL BE REMOVED ! */
			//explicit vector(pointer ptr, const size_type size) noexcept
			//: _allocator{}, _data{ptr}, _capacity{ptr ? size : 0}, _size{_capacity} {
			//}
			//// WARNING: this constructor is dangerous, use with caution
			//// need to use same allocator as the one used to allocate ptr


			/* destructor */
			constexpr ~vector(void) noexcept {
				// destroy elements
				_clear();
				// deallocate memory
				_deallocate();
			}


		private:

			/* fill construct */
			constexpr auto _fill_construct(const_reference ___vl) noexcept(xns::is_nothrow_copy_constructible<value_type>) -> void {

				// trivially copyable
				if constexpr (xns::is_trivially_copyable<value_type>) {
					xns::memset(_data, ___vl, _cap - _data);
				}
				else if constexpr (xns::is_nothrow_copy_constructible<value_type>) {
					// construct elements
					for (; _end < _cap; ++_end)
						___lifecycle::construct(_end, ___vl);
				}
				else {
					// create destroy guard
					___destroy ___d{*this};
					// construct elements
					for (; _end < _cap; ++_end)
						___lifecycle::construct(_end, ___vl);
					// complete
					___d.complete();
				}
			}


			/* fill construct */
			template <typename... ___params>
			constexpr auto _fill_construct(const ___params&... ___args)
				// noexcept specification
				noexcept(xns::is_nothrow_constructible<value_type, const ___params&...>) -> void {

				if constexpr (xns::is_nothrow_constructible<value_type, const ___params&...>) {
					// construct elements
					for (; _end < _cap; ++_end)
						___lifecycle::construct(_end, ___args...);
				}
				else {
					// create destroy guard
					___destroy ___d{*this};
					// construct elements
					for (; _end < _cap; ++_end)
						___lifecycle::construct(_end, ___args...);
					// complete
					___d.complete();
				}
			}


		public:


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const ___self& ___ot) -> ___self&
				// requirements
				requires (xns::is_nothrow_copy_constructible<value_type>) {

				// check self assignment
				if (this == &___ot)
					return *this;

				{
					const auto ___sz = ___ot.size();

					// check sufficient capacity
					if (___sz > capacity()) {
						pointer ___tmp = _allocate(___sz);
						_clear();
						_update_members(___tmp, ___tmp, ___tmp + ___sz);
					}
					else {
						_clear();
						_end = _data;
					}

				}

				for (pointer ___ptr = ___ot._data; ___ptr < ___ot._end; ++___ptr, ++_end)
					___lifecycle::construct(_end, *___ptr);

				return *this;
			}

			/* move assignment operator */
			constexpr auto operator=(___self&& ___ot) noexcept -> ___self& {

				// check self assignment
				if (this == &___ot)
					return *this;

				// destroy elements
				_clear();
				
				// deallocate memory
				_deallocate();

				// copy members
				_copy_members(___ot);

				// invalidate other
				___ot._init();

				return *this;
			}



			// -- public iterators --------------------------------------------

			/* begin */
			constexpr auto begin(void) noexcept -> iterator {
				return iterator{_data};
			}

			/* const begin */
			constexpr auto begin(void) const noexcept -> const_iterator {
				return const_iterator{_data};
			}

			/* cbegin */
			constexpr auto cbegin(void) const noexcept -> const_iterator {
				return const_iterator{_data};
			}

			/* end */
			constexpr auto end(void) noexcept -> iterator {
				return iterator{_end};
			}

			/* const end */
			constexpr auto end(void) const noexcept -> const_iterator {
				return const_iterator{_end};
			}

			/* cend */
			constexpr auto cend(void) const noexcept -> const_iterator {
				return const_iterator{_end};
			}

			/* rbegin */
			constexpr auto rbegin(void) noexcept -> reverse_iterator {
				return reverse_iterator{_end - 1};
			}

			/* const rbegin */
			constexpr auto rbegin(void) const noexcept -> const_reverse_iterator {
				return const_reverse_iterator{_end - 1};
			}

			/* crbegin */
			constexpr auto crbegin(void) const noexcept -> const_reverse_iterator {
				return const_reverse_iterator{_end - 1};
			}

			/* rend */
			constexpr auto rend(void) noexcept -> reverse_iterator {
				return reverse_iterator{_data - 1};
			}

			/* const rend */
			constexpr auto rend(void) const noexcept -> const_reverse_iterator {
				return const_reverse_iterator{_data - 1};
			}

			/* crend */
			constexpr auto crend(void) const noexcept -> const_reverse_iterator {
				return const_reverse_iterator{_data - 1};
			}


			// -- public accessors --------------------------------------------

			/* empty */
			inline constexpr auto empty(void) const noexcept -> bool {
				return _data == _end;
			}

			/* size */
			inline constexpr auto size(void) const noexcept -> size_type {
				return static_cast<size_type>(_end - _data);
			}

			/* max size */
			constexpr auto max_size(void) const noexcept -> size_type {

				const auto ___max  = ___alloc_traits::max_size(_allocator);
				const auto ___diff = static_cast<size_type>(xns::limits<difference_type>::max());

				return (___max < ___diff) ? ___max : ___diff;
			}

			/* capacity */
			inline constexpr auto capacity(void) const noexcept -> size_type {
				return static_cast<size_type>(_cap - _data);
			}

			/* front */
			inline constexpr auto front(void) noexcept -> reference {
				return *_data;
			}

			/* const front */
			inline constexpr auto front(void) const noexcept -> const_reference {
				return *_data;
			}

			/* back */
			inline constexpr auto back(void) noexcept -> reference {
				return *(_end - 1);
			}

			/* const back */
			inline constexpr auto back(void) const noexcept -> const_reference {
				return *(_end - 1);
			}

			/* data */
			inline constexpr auto data(void) noexcept -> pointer {
				return _data;
			}

			/* const data */
			inline constexpr auto data(void) const noexcept -> const_pointer {
				return _data;
			}

			/* subscript operator */
			inline constexpr auto operator[](const size_type ___idx) noexcept -> reference {
				return _data[___idx];
			}

			/* const subscript operator */
			inline constexpr auto operator[](const size_type ___idx) const noexcept -> const_reference {
				return _data[___idx];
			}

			/* get allocator */
			inline constexpr auto get_allocator(void) const noexcept -> allocator_type {
				return _allocator;
			}


			// -- public memory management ------------------------------------


			/* shrink to fit */
			constexpr auto shrink_to_fit(void)
				// noexcept specification
				noexcept(false) -> void {

				// check if capacity is equal to size
				if (_end == _cap)
					return;

				// call shrink implementation
				_shrink();
			}

			/* reserve */
			constexpr auto reserve(const size_type ___cap)
				noexcept(___noexcept_allocate) -> void {

				// check capacity
				if (___cap <= capacity())
					return;

				// call reserve implementation
				_reserve(___cap);
			}


			/* resize */
			auto resize(const size_type ___sz) -> void {
				//static_assert(xns::always_false<value_type>, "resize not implemented");

				// superior size
				if (___sz > size()) {

					// check capacity
					if (___sz > capacity()) {

						if constexpr (___noexcept_allocate) {
							if (!_reserve(_try_expand(___sz)))
								return; }
						else _reserve(_try_expand(___sz));
					}

				}

				// inferior size
				else {

					// destroy only non-trivially destructible types
					if constexpr (___requires_destruct) {
						;
					}

						// destroy excess elements (if not equal size)
						//for (size_type i = ___sz; i < _size; ++i)
						//	___lifecycle::destroy(_data + i);
				}

				// update size
				//_size = ___sz;
			}



			// -- public modifiers --------------------------------------------

			/* clear */
			constexpr auto clear(void) noexcept -> void {

				// destroy elements
				_clear();

				// reset end
				_end = _data;
			}



			/* push back */
			constexpr auto push_back(const_reference ___vl)
				// noexcept specification
				noexcept(false) -> void {

				// expand if no available space
				if (!(_end < _cap))
					_reserve(_expand());

				// construct new element by copy
				___lifecycle::construct(_end, ___vl);

				// increment end
				++_end;
			}

			/* push back */
			constexpr auto push_back(value_type&& ___vl)
				// noexcept specification
				noexcept(false) -> void {

				// expand if no available space
				if (!(_end < _cap))
					_reserve(_expand());

				// construct new element by move
				___lifecycle::construct(_end, xns::move(___vl));

				// increment end
				++_end;
			}


			/* emplace back */
			template <typename... ___params>
			constexpr auto emplace_back(___params&&... ___args)
				// noexcept specification
				noexcept(false) -> void {

				// expand if no available space
				if (!(_end < _cap))
					_reserve(_expand());

				// construct new element in place
				___lifecycle::construct(_end, xns::forward<___params>(___args)...);

				// increment end
				++_end;
			}

			/* pop back */
			constexpr auto pop_back(void) noexcept -> void {

				// non-trivially destructible
				if constexpr (___requires_destruct)
					___lifecycle::destroy(--_end);
				else
					--_end;
			}

			/* swap */
			constexpr auto swap(___self& ___ot) noexcept {
				// swap allocators
				xns::swap(_allocator, ___ot._allocator);
				// swap members
				xns::swap(_data, ___ot._data);
				xns::swap(_cap,  ___ot._cap);
				xns::swap(_end,  ___ot._end);
			}


		private:

			// -- private methods ---------------------------------------------

			/* init */
			constexpr auto _init(void) noexcept -> void {
				_data = _end  = _cap = nullptr;
			}

			/* copy members */
			constexpr auto _copy_members(const ___self& ___ot) noexcept -> void {
				_data = ___ot._data;
				_end  = ___ot._end;
				_cap  = ___ot._cap;
			}

			/* allocate */
			constexpr auto _allocate(const size_type ___sz) noexcept(false) -> pointer
				// requirements
				requires (___noexcept_allocate == false) {
				return ___alloc_traits::allocate(_allocator, ___sz);
			}

			/* allocate (noexcept) */
			constexpr auto _allocate(const size_type ___sz) noexcept(false) -> pointer
				// requirements
				requires (___noexcept_allocate == true) {

				pointer ___ptr = ___alloc_traits::allocate(_allocator, ___sz);

				if (___ptr == nullptr)
					throw xns::exception("vector, allocation failed", -2);
				return ___ptr;
			}

			/* deallocate */
			constexpr auto _deallocate(void) noexcept -> void {
				// deallocate memory
				if (_data == nullptr)
					return;
				___alloc_traits::deallocate(_allocator, _data, static_cast<size_type>(_cap - _data));
			}

			/* unsafe deallocate */
			constexpr auto _unsafe_deallocate(void) noexcept -> void {
				// deallocate memory
				___alloc_traits::deallocate(_allocator, _data, static_cast<size_type>(_cap - _data));
			}

			/* available capacity */
			constexpr auto _available_capacity(void) const noexcept -> size_type {
				return _cap - _end;
			}

			/* expand */
			constexpr auto _expand(void) const noexcept -> size_type {

				const auto ___max = max_size();
				const auto ___cap = capacity();

				if (___cap >= ___max)
					return ___max;
				else
					return ___cap ? ___cap << 1U : 1U;
			}

			/* try expand */
			constexpr auto _try_expand(const size_type ___sz) const noexcept -> size_type {
				const auto ___exp = _expand();
				return ___exp < ___sz ? ___sz : ___exp;
			}


			/* destroy */
			static constexpr auto _destroy(pointer ___ptr, const size_type ___sz) noexcept -> void {

				// destroy only non-trivially destructible types
				if constexpr (not ___trivial_destruct)
					// destroy elements
					for (size_type i = 0; i < ___sz; ++i)
						___lifecycle::destroy(___ptr + i);
			}


			/* clear */
			constexpr auto _clear(void) noexcept -> void {

				// destroy only non-trivially destructible types
				if constexpr (___requires_destruct)
					// destroy elements
					for (pointer ___ptr = _data; ___ptr < _end; ++___ptr)
						___lifecycle::destroy(___ptr);
			}

			/* update members */
			constexpr auto _update_members(pointer ___ptr,
										   pointer ___end,
										   pointer ___cap) noexcept -> void {
				_data = ___ptr;
				_end  = ___end;
				_cap  = ___cap;
			}

			/* shrink */
			constexpr auto _shrink(void) noexcept(false) -> void
				// requirements
				requires (xns::is_trivially_copyable<value_type>) {

				// get size
				const auto ___sz = size();

				// reallocate memory
				const pointer ___tmp = _allocate(___sz);

				// trivially copyable
				xns::memcpy(___tmp, _data, ___sz);

				// clean up
				this->~vector();

				// compute end
				const pointer ___end = ___tmp + ___sz;

				// update data
				_update_members(___tmp, ___end, ___end);
			}

			/* shrink */
			constexpr auto _shrink(void) noexcept(false) -> void
				// requirements
				requires (not xns::is_trivially_copyable<value_type>) {

				// reallocate memory
				const pointer ___tmp = _allocate(size());

				pointer ___ptr = _data;
				pointer ___end = ___tmp;

				// move construct elements
				for (; ___ptr < _end; ++___ptr, ++___end)
					___lifecycle::construct(___end, xns::move(*___ptr));

				// clean up
				this->~vector();

				// update data
				_update_members(___tmp, ___end, ___end);

			}

			/* reserve */
			constexpr auto _reserve(const size_type ___cap) noexcept(false) -> void
				// requirements
				requires (xns::is_trivially_copyable<value_type>) {

				// reallocate memory
				const pointer ___tmp = _allocate(___cap);

				// get size
				const auto ___sz = size();

				// trivially copyable
				xns::memcpy(___tmp, _data, ___sz);

				// clean up
				this->~vector();

				// update data
				_update_members(___tmp, ___tmp + ___sz, ___tmp + ___cap);
			}

			/* reserve */
			constexpr auto _reserve(const size_type ___cap) noexcept(false) -> void
				// requirements
				requires (not xns::is_trivially_copyable<value_type>) {

				// reallocate memory
				const pointer ___tmp = _allocate(___cap);

				pointer ___ptr = _data;
				pointer ___end = ___tmp;

				// move construct elements
				for (; ___ptr < _end; ++___ptr, ++___end)
					___lifecycle::construct(___end, xns::move(*___ptr));

				// clean up
				this->~vector();

				// update data
				_update_members(___tmp, ___end, ___tmp + ___cap);

			}


		// -- friends ---------------------------------------------------------

		/* filter as friend */
		template <typename ___tp, typename ___al, typename... ___pa>
		friend auto filter(xns::vector<___tp, ___al>&, const ___pa&...) noexcept -> void;

	}; // class vector


	// -- I T E R A T O R -----------------------------------------------------

	template <typename ___type, typename ___alloc>
	template <bool ___const, bool ___reverse>
	class vector<___type, ___alloc>::___iterator {


		// -- friends ---------------------------------------------------------

		/* other iterator as friend */
		template <bool, bool>
		friend class ___iterator;

		/* vector as friend */
		template <typename, typename>
		friend class xns::vector;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ___iterator<___const, ___reverse>;

			/* vector type */
			using ___vector = xns::vector<___type, ___alloc>;


		public:

			// -- public types ------------------------------------------------

			/* pointer type */
			using pointer           = xns::conditional<___const, ___vector::const_pointer,
																 ___vector::pointer>;
			/* iterator type */
			using iterator_type     = pointer;

			/* value type */
			using value_type        = ___vector::value_type;

			/* difference type */
			using difference_type   = ___vector::difference_type;

			/* reference type */
			using reference         = xns::conditional<___const, ___vector::const_reference,
																 ___vector::reference>;
			/* iterator category */
			using iterator_category = xns::random_access_iterator_tag;


		private:

			// -- private members ---------------------------------------------

			/* pointer */
			pointer _iter;


		private:

			// -- private lifecycle -------------------------------------------

			/* pointer constructor */
			constexpr explicit ___iterator(const pointer ___it) noexcept
			: _iter{___it} {
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr ___iterator(void) noexcept
			: _iter{nullptr} {
			}

			/* copy constructor */
			constexpr ___iterator(const ___self&) noexcept = default;

			/* copy constructor */
			constexpr ___iterator(const ___iterator<!___const, ___reverse>& other) noexcept
			: _iter{other._iter} {
				static_assert(___const,
						"non-const iterator cannot be constructed from const iterator"); 
			}

			/* move constructor */
			constexpr ___iterator(___self&&) noexcept = default;

			/* destructor */
			~___iterator(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const ___self&) noexcept -> ___self& = default;

			/* copy assignment operator */
			constexpr auto operator=(const ___iterator<!___const, ___reverse>& other) noexcept -> ___self& {
				static_assert(___const,
						"non-const iterator cannot be assigned from const iterator");
				_iter = other._iter;
				return *this;
			}

			/* move assignment operator */
			constexpr auto operator=(___self&&) noexcept -> ___self& = default;

			/* move assignment operator */
			template <bool ___rev>
			constexpr auto operator=(___iterator<!___const, ___rev>&& other) noexcept -> ___self& {
				static_assert(___const,
						"non-const iterator cannot be assigned from const iterator");
				_iter = other._iter;
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* operator* */
			constexpr auto operator*(void) const noexcept -> reference {
				return *_iter;
			}

			/* operator-> */
			constexpr auto operator->(void) const noexcept -> pointer {
				return _iter;
			}

			/* operator[] */
			constexpr auto operator[](const difference_type __n) const noexcept -> reference
				requires (not ___reverse) {
				return _iter[__n];
			}

			/* operator[] (reverse) */
			constexpr auto operator[](const difference_type __n) const noexcept -> reference
				requires ___reverse {
				return _iter[-__n];
			}

			/* base */
			constexpr auto base(void) const noexcept -> iterator_type {
				return _iter;
			}


			// -- public arithmetic operators ---------------------------------

			/* operator++ */
			constexpr auto operator++(void) noexcept -> ___self&
				requires (not ___reverse) {
				++_iter;
				return *this;
			}

			/* operator++ (reverse) */
			constexpr auto operator++(void) noexcept -> ___self&
				requires ___reverse {
				--_iter;
				return *this;
			}

			/* operator++ */
			constexpr auto operator++(int) noexcept -> ___self
				requires (not ___reverse) {
				___self tmp{*this};
				++_iter;
				return tmp;
			}

			/* operator++ (reverse) */
			constexpr auto operator++(int) noexcept -> ___self
				requires ___reverse {
				___self tmp{*this};
				--_iter;
				return tmp;
			}

			/* operator-- */
			constexpr auto operator--(void) noexcept -> ___self&
				requires (not ___reverse) {
				--_iter;
				return *this;
			}

			/* operator-- (reverse) */
			constexpr auto operator--(void) noexcept -> ___self&
				requires ___reverse {
				++_iter;
				return *this;
			}

			/* operator-- */
			constexpr auto operator--(int) noexcept -> ___self
				requires (not ___reverse) {
				___self tmp{*this};
				--_iter;
				return tmp;
			}

			/* operator-- (reverse) */
			constexpr auto operator--(int) noexcept -> ___self
				requires ___reverse {
				___self tmp{*this};
				++_iter;
				return tmp;
			}

			/* operator+ */
			constexpr auto operator+(const difference_type __n) const noexcept -> ___self
				requires (not ___reverse) {
				___self tmp{_iter + __n};
				return tmp;
			}

			/* operator+ (reverse) */
			constexpr auto operator+(const difference_type __n) const noexcept -> ___self
				requires ___reverse {
				___self tmp{_iter - __n};
				return tmp;
			}

			/* operator+= */
			constexpr auto operator+=(const difference_type __n) noexcept -> ___self&
				requires (not ___reverse) {
				_iter += __n;
				return *this;
			}

			/* operator+= (reverse) */
			constexpr auto operator+=(const difference_type __n) noexcept -> ___self&
				requires ___reverse {
				_iter -= __n;
				return *this;
			}

			/* operator- */
			constexpr auto operator-(const difference_type __n) const noexcept -> ___self
				requires (not ___reverse) {
				___self tmp{_iter - __n};
				return tmp;
			}

			/* operator- (reverse) */
			constexpr auto operator-(const difference_type __n) const noexcept -> ___self
				requires ___reverse {
				___self tmp{_iter + __n};
				return tmp;
			}

			/* operator-= */
			constexpr auto operator-=(const difference_type __n) noexcept -> ___self&
				requires (not ___reverse) {
				_iter -= __n;
				return *this;
			}

			/* operator-= (reverse) */
			constexpr auto operator-=(const difference_type __n) noexcept -> ___self&
				requires ___reverse {
				_iter += __n;
				return *this;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			template <bool ___c, bool ___r>
			constexpr auto operator==(const ___iterator<___c, ___r>& __rhs) const noexcept -> bool {
				return _iter == __rhs._iter;
			}

			/* inequality operator */
			template <bool ___c, bool ___r>
			constexpr auto operator!=(const ___iterator<___c, ___r>& __rhs) const noexcept -> bool {
				return _iter != __rhs._iter;
			}

			/* less than operator */
			template <bool ___c, bool ___r>
			constexpr auto operator<(const ___iterator<___c, ___r>& __rhs) const noexcept -> bool {
				return _iter < __rhs._iter;
			}

			/* greater than operator */
			template <bool ___c, bool ___r>
			constexpr auto operator>(const ___iterator<___c, ___r>& __rhs) const noexcept -> bool {
				return _iter > __rhs._iter;
			}

			/* less than or equal operator */
			template <bool ___c, bool ___r>
			constexpr auto operator<=(const ___iterator<___c, ___r>& __rhs) const noexcept -> bool {
				return _iter <= __rhs._iter;
			}

			/* greater than or equal operator */
			template <bool ___c, bool ___r>
			constexpr auto operator>=(const ___iterator<___c, ___r>& __rhs) const noexcept -> bool {
				return _iter >= __rhs._iter;
			}




	}; // class ___iterator







			/* remove all elements that match the given value */
			template <typename ___type, typename ___alloc, typename... ___params>
			auto filter(xns::vector<___type, ___alloc>& ___v, const ___params&... ___vls) noexcept -> void {

				if constexpr (sizeof...(___params) == 0) {
					return;
				}
				else {

					using ___vector = xns::vector<___type, ___alloc>;
					using ___lifecycle = typename ___vector::___lifecycle;

					static_assert(xns::are_comparable<___type, ___params...>,
						"types are not comparable in filter");

					typename ___vector::pointer ___z = ___v._data;
					typename ___vector::pointer ___x = ___v._data;

					// loop over vector
					for (; ___x < ___v._end; ++___x) {

						if (((*___x != ___vls) && ...)) {
							// if no match, maybe move, check shift
							if (___z != ___x) {
								// move element
								*___z = xns::move(*___x);
							} // increment z
							++___z;
						}
					}
					___v._end = ___z;
					// destroy elements
					for (; ___x < ___v._end; ++___x) {
						___lifecycle::destroy(___x);
					}
				}
			}

} // namespace xns

#endif // XNS_VECTOR_HEADER

/*
			*/

			/* move elements to the back of the vector if exists, else push back */
/*
			auto to_back(const value_type& value) -> void {
				// loop over vector
				for (size_type x = 0; x < _size; ++x) {
					// check for match
					if (_data[x] == value) {
						// declare tmp
						value_type tmp = xns::move(_data[x]);
						// move elements
						for (size_type z = x; z < (_size - 1); ++z)
							_data[z] = xns::move(_data[z + 1]);
						// move tmp
						_data[_size - 1] = xns::move(tmp);
						// return
						return;
					}
				} // push back
				push_back(value);
			}
			*/

			/* dichotomic search */
/*
			template <typename U>
			auto dichotomic_search(const U& value) noexcept -> iterator
				requires (xns::is_comparable<U, value_type>) {

				// check if U is comparable to value_type
				static_assert(xns::is_comparable<U, value_type>,
					"type are not comparable in dichotomic search");

				// check size
				if (!_size) { return end(); }

				// initialize bounds
				size_type lower = 0;
				size_type upper = _size - 1;

				// loop
				while (lower <= upper) {
					std::cout << "loop" << std::endl;
					// compute middle
					size_type middle = (lower + upper) / 2;

					// check value is greater
					if      (value > _data[middle]) { lower = middle + 1; }
					// check value is lower
					else if (value < _data[middle]) { upper = middle - 1; }
					// else value is equal
					else    { return ___self::iterator(_data + middle);            }
				} // not found
				return ___self::iterator(_data + _size);

			}
			*/

			/* dichotomic insert */
/*
			auto dichotomic_insert(const_reference value) -> void
				requires (xns::is_comparable<value_type>) {

				// check if U is comparable to value_type
				static_assert(is_comparable<value_type>,
					"type are not comparable in dichotomic insert");


				// initialize bounds
				size_type lower = 0;
				size_type upper = _size - 1;


				// check size
				if (!_size) { return push_back(value); }

				// loop
				while (lower <= upper) {
					// compute middle
					size_type middle = (lower + upper) / 2;
					// check value is greater
					if (value > _data[middle]) { lower = middle + 1; }
					// check value is lower
					else if (value < _data[middle]) {

						if (middle == 0) { lower = 0; break; }
						// update upper
						upper = middle - 1;
					}
					// else value is already in the vector
					else { return; }

				} // insert

				insert(lower, value);
			}
			*/
