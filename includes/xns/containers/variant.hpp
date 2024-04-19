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

#ifndef XNS_VARIANT_HEADER
#define XNS_VARIANT_HEADER

// local headers
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

#include "xns/type_traits/other/in_place.hpp"
#include "xns/type_traits/other/index_of.hpp"
#include "xns/type_traits/other/type_at.hpp"
#include "xns/type_traits/other/is_all_unique.hpp"
#include "xns/type_traits/type_properties/is_const.hpp"

#include "xns/memory/lifecycle.hpp"
#include "xns/containers/aligned_storage.hpp"

#include "xns/other/indexed_element.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	template <typename... A>
	concept is_all_trivially_destructible = (xns::is_trivially_destructible<A> && ...);


	// -- V A R I A N T -------------------------------------------------------

	template <typename... A>
	class variant final {


		private:

			// -- private types -----------------------------------------------

			/* storage type */
			using storage = xns::aligned_storage<xns::sizeof_max<A...>(),
												 xns::alignof_max<A...>()>;


			// -- private enums -----------------------------------------------

			/* null index */
			enum : xns::size_t { NULL_INDEX = sizeof...(A) };


		public:

			// -- public types ------------------------------------------------

			/* self */
			using self = xns::variant<A...>;


		private:



			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr variant(void) noexcept
			: _storage{}, _index{NULL_INDEX} {}

			/* type constructor */
			template <typename T>
			explicit constexpr variant(const T& value) requires xns::is_one_of<T, A...>
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// call allocator constructor
				xns::lifecycle<T>::construct(
					xns::ptr<T>(_storage), value
				);
			}

			/* type move constructor */
			template <typename T>
			explicit constexpr variant(T&& value) requires xns::is_one_of<T, A...>
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// call allocator constructor
				xns::lifecycle<T>::construct(
					xns::ptr<T>(_storage), xns::move(value)
				);
			}

			/* in place type constructor */
			template <typename T, typename... U>
			constexpr variant(xns::in_place_type<T>, U&&... args)
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// call allocator constructor
				xns::lifecycle<T>::construct(
					xns::ptr<T>(_storage), xns::forward<U>(args)...
				);
			}

			/* in place index constructor */
			template <xns::size_t I, typename... U>
			constexpr variant(xns::in_place_index<I>, U&&... args)
			: _storage{}, _index{I} {
				// get type at index
				using T = xns::type_at<I, A...>;
				// call allocator constructor
				xns::lifecycle<T>::construct(
					xns::ptr<T>(_storage), xns::forward<U>(args)...
				);
			}

			/* copy constructor */
			constexpr variant(const self& other)
			: _storage{}, _index{other._index} {
				// call indexed copy constructor
				_copies[CONSTRUCT][_index](_storage, other._storage);
			}

			/* move constructor */
			inline constexpr variant(self&& other) noexcept
			: _storage{}, _index{other._index} {
				// call indexed move constructor
				_moves[CONSTRUCT][_index](_storage, other._storage);
			}

			/* destructor */
			inline constexpr ~variant(void) noexcept {
				// call indexed destructor
				_destructors[_index](_storage);
			}


			// -- default assignment operators --------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self& other) -> self& {
				// check if type is same as current type
				if (_index == other._index) {
					// call indexed copy assignment
					_copies[ASSIGN][_index](_storage, other._storage);
					return *this; }
				// call indexed destructor
				_destructors[_index](_storage);
				// set index
				_index = other._index;
				// call indexed copy constructor
				_copies[CONSTRUCT][_index](_storage, other._storage);

				return *this;
			}

			/* move assignment operator */
			constexpr auto operator=(self&& other) noexcept -> self& {
				// check if type is same as current type
				if (_index == other._index) {
					// call indexed move assignment
					_moves[ASSIGN][_index](_storage, other._storage);
					return *this; }
				// call indexed destructor
				_destructors[_index](_storage);
				// set index
				_index = other._index;
				// call indexed move constructor
				_moves[CONSTRUCT][_index](_storage, other._storage);

				return *this;
			}


			// -- public modifiers --------------------------------------------

			/* emplace value */
			template <typename T, typename... U>
			constexpr auto emplace(U&&... args) -> void {
				// check if type is in variant
				static_assert(xns::is_one_of<T, A...>,
						"): VARIANT: TYPE NOT IN CONTAINER :(");
				// call indexed destructor
				_destructors[_index](_storage);
				// set index
				_index = xns::index_of<T, A...>();

				// call allocator emplace constructor
				xns::lifecycle<T>::construct(
					xns::ptr<T>(_storage), xns::forward<U>(args)...
				);
			}

			/* reset value */
			inline constexpr auto reset(void) noexcept -> void {
				// call indexed destructor
				_destructors[_index](_storage);
				// set null index
				_index = NULL_INDEX;
			}




			// -- public accessors --------------------------------------------


			/* is containing type */
			inline constexpr auto contains(void) const noexcept -> bool {
				// return index validity
				return _index != NULL_INDEX;
			}

			/* is empty */
			inline constexpr auto empty(void) const noexcept -> bool {
				// return index invalidity
				return _index == NULL_INDEX;
			}

			/* has type */
			template <typename T>
			inline constexpr auto has(void) const noexcept -> bool {
				// check if type is in variant
				static_assert(xns::is_one_of<T, A...>,
						"): VARIANT: TYPE NOT IN CONTAINER :(");
				// return index validity
				return _index == xns::index_of<T, A...>();
			}


			// -- boolean operators -------------------------------------------

			/* boolean operator */
			explicit inline constexpr operator bool(void) const noexcept {
				// return index validity
				return _index != NULL_INDEX;
			}

			/* not operator */
			inline constexpr auto operator!(void) const noexcept -> bool {
				// return index invalidity
				return _index == NULL_INDEX;
			}


		private:

			// -- private methods ---------------------------------------------

			/* custom copy constructor */
			template <typename T>
			static inline constexpr auto copy_construct(storage& dst, const storage& src) -> void {
				// call allocator copy constructor
				xns::lifecycle<T>::construct(
					xns::ptr<T>(dst), xns::ref<T>(src)
				);
			}

			/* custom move constructor */
			template <typename T>
			static inline constexpr auto move_construct(storage& dst, storage& src) noexcept -> void {
				// call allocator move constructor
				xns::lifecycle<T>::construct(
					xns::ptr<T>(dst), xns::move(xns::ref<T>(src))
				);
			}

			/* custom copy assignment */
			template <typename T>
			static inline constexpr auto copy_assign(storage& dst, const storage& src) -> void {
				// call allocator copy assignment
				xns::lifecycle<T>::assign(
					xns::ref<T>(dst), xns::ref<T>(src)
				);
			}

			/* custom move assignment */
			template <typename T>
			static inline constexpr auto move_assign(storage& dst, storage& src) noexcept -> void {
				// call allocator move assignment
				xns::lifecycle<T>::assign(
					xns::ref<T>(dst), xns::move(xns::ref<T>(src))
				);
			}

			/* custom destructor */
			template <typename T>
			static inline constexpr auto destructor(storage& obj) noexcept -> void {
				// call allocator destructor
				xns::lifecycle<T>::destroy(
					xns::ptr<T>(obj)
				);
			}


			/* empty kill */
			static inline constexpr auto nope(storage&) noexcept -> void {}

			/* empty move */
			static inline constexpr auto nope(storage&, storage&) noexcept -> void {}

			/* empty copy */
			static inline constexpr auto nope(storage&, const storage&) noexcept -> void {}


			// -- private members ---------------------------------------------

			/* storage */
			self::storage _storage;

			/* type index */
			xns::size_t _index;


			// -- private types -----------------------------------------------

			/* copy prototype */
			using copy_proto = auto(*)(self::storage&, const self::storage&) -> void;

			/* move prototype */
			using move_proto = auto(*)(self::storage&, self::storage&) noexcept -> void;

			/* destructor prototype */
			using kill_proto = auto(*)(self::storage&) noexcept -> void;


			// -- private constants -------------------------------------------

			/* method type index */
			enum : xns::u8 { CONSTRUCT, ASSIGN };


			// -- private static members --------------------------------------

			/* move lookup array */
			static constexpr move_proto _moves[2][sizeof...(A) + 1] {
				{ &move_construct<A>..., &nope },
				{ &move_assign<A>...,    &nope }
			};

			/* copy lookup array */
			static constexpr copy_proto _copies[2][sizeof...(A) + 1] {
				{ &copy_construct<A>..., &nope },
				{ &copy_assign<A>...,    &nope }
			};

			/* destructors lookup array */
			static constexpr kill_proto _destructors[sizeof...(A) + 1] {
				&destructor<A>..., &nope
			};


			// -- friends -----------------------------------------------------

			/* get mutable reference as friend */
			template <typename T, typename... U>
			friend inline constexpr auto get(xns::variant<U...>&) -> T&;

			/* get mutable rvalue reference as friend */
			template <typename T, typename... U>
			friend inline constexpr auto get(xns::variant<U...>&&) -> T&&;

			/* get const reference as friend */
			template <typename T, typename... U>
			friend inline constexpr auto get(const xns::variant<U...>&) -> const T&;

			/* get const rvalue reference as friend */
			template <typename T, typename... U>
			friend inline constexpr auto get(const xns::variant<U...>&&) -> const T&&;


			/* get indexed mutable reference as friend */
			template <xns::size_t I, typename... T>
			friend inline constexpr auto get(xns::variant<T...>&) -> xns::indexed_element<I, xns::variant<T...>>&;

			/* get indexed mutable rvalue reference as friend */
			template <xns::size_t I, typename... T>
			friend inline constexpr auto get(xns::variant<T...>&&) -> xns::indexed_element<I, xns::variant<T...>>&&;

			/* get indexed const reference as friend */
			template <xns::size_t I, typename... T>
			friend inline constexpr auto get(const xns::variant<T...>&) -> const xns::indexed_element<I, xns::variant<T...>>&;

			/* get indexed const rvalue reference as friend */
			template <xns::size_t I, typename... T>
			friend inline constexpr auto get(const xns::variant<T...>&&) -> const xns::indexed_element<I, xns::variant<T...>>&&;

	};



	/* get mutable reference */
	template <typename T, typename... A>
	inline constexpr auto get(xns::variant<A...>& variant) -> T& {
		// check if type is in variant
		static_assert(xns::is_one_of<T, A...>,
				"): VARIANT: TYPE NOT IN CONTAINER :(");
		// return mutable reference
		return xns::ref<T>(variant._storage);
	}

	/* get mutable rvalue reference */
	template <typename T, typename... A>
	inline constexpr auto get(xns::variant<A...>&& variant) -> T&& {
		// check if type is in variant
		static_assert(xns::is_one_of<T, A...>,
				"): VARIANT: TYPE NOT IN CONTAINER :(");
		// return mutable rvalue reference
		return xns::move(xns::ref<T>(variant._storage));
	}

	/* get const reference */
	template <typename T, typename... A>
	inline constexpr auto get(const xns::variant<A...>& variant) -> const T& {
		// check if type is in variant
		static_assert(xns::is_one_of<T, A...>,
				"): VARIANT: TYPE NOT IN CONTAINER :(");
		// return const reference
		return xns::ref<T>(variant._storage);
	}

	/* get const rvalue reference */
	template <typename T, typename... A>
	inline constexpr auto get(const xns::variant<A...>&& variant) -> const T&& {
		// check if type is in variant
		static_assert(xns::is_one_of<T, A...>,
				"): VARIANT: TYPE NOT IN CONTAINER :(");
		// return const rvalue reference
		return xns::move(xns::ref<T>(variant._storage));
	}


	/* get indexed mutable reference */
	template <xns::size_t I, typename... T>
	inline constexpr auto get(xns::variant<T...>& variant) -> xns::indexed_element<I, xns::variant<T...>>& {
		// check if index out of bounds
		static_assert(I < sizeof...(T),
				"): VARIANT: INDEX OUT OF BOUNDS :(");
		// return mutable reference
		return xns::ref<xns::type_at<I, T...>>(variant._storage);
	}

	/* get indexed mutable rvalue reference */
	template <xns::size_t I, typename... T>
	inline constexpr auto get(xns::variant<T...>&& variant) -> xns::indexed_element<I, xns::variant<T...>>&& {
		// check if index out of bounds
		static_assert(I < sizeof...(T),
				"): VARIANT: INDEX OUT OF BOUNDS :(");
		// return mutable rvalue reference
		return xns::move(xns::ref<xns::type_at<I, T...>>(variant._storage));
	}

	/* get indexed const reference */
	template <xns::size_t I, typename... T>
	inline constexpr auto get(const xns::variant<T...>& variant) -> const xns::indexed_element<I, xns::variant<T...>>& {
		// check if index out of bounds
		static_assert(I < sizeof...(T),
				"): VARIANT: INDEX OUT OF BOUNDS :(");
		// return const reference
		return xns::ref<xns::type_at<I, T...>>(variant._storage);
	}

	/* get indexed const rvalue reference */
	template <xns::size_t I, typename... T>
	inline constexpr auto get(const xns::variant<T...>&& variant) -> const xns::indexed_element<I, xns::variant<T...>>&& {
		// check if index out of bounds
		static_assert(I < sizeof...(T),
				"): VARIANT: INDEX OUT OF BOUNDS :(");
		// return const rvalue reference
		return xns::move(xns::ref<xns::type_at<I, T...>>(variant._storage));
	}

} // namespace xns

#endif // XNS_VARIANT_HEADER
