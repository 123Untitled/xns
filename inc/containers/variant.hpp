#ifndef VARIANT_HEADER
#define VARIANT_HEADER

// local headers
#include "is_constructible.hpp"
#include "array.hpp"
#include "in_place.hpp"
#include "index_of.hpp"
#include "type_at.hpp"
#include "is_all_unique.hpp"

// std headers
#include <type_traits>
#include <iostream>
#include <typeinfo>

// -- X N S  N A M E S P A C E ------------------------------------------------


template <class T>
void print_type(void) {

	std::cout << typeid(T).name() << std::endl;

}

namespace xns {


	template <class... A>
	struct constructible_type {


		private:

			// -- private structs ---------------------------------------------

			template <class...>
			struct impl;

			template <class T, class... Tp>
			requires (xns::is_constructible_strict<T, A...> == false)
			struct impl<T, Tp...> final {
				using type = typename impl<Tp...>::type;
			};

			template <class T, class... Tp>
			requires (xns::is_constructible_strict<T, A...> == true)
			struct impl<T, Tp...> final {
				using type = T;
			};

			template <class T> requires (!xns::is_constructible_strict<T, A...>)
			struct impl<T> final {
				static_assert(xns::is_constructible_strict<T, A...>,
							  "): NO CONSTRUCTIBLE TYPE IN VARIADIC :(");
			};



		public:

			template <class... T>
			static consteval auto counter(void) -> xns::size_t {
				xns::size_t count = 0;
				((count += xns::is_constructible_strict<T, A...>), ...);
				return count;
			}


			template <class... T>
			using type = typename impl<T...>::type;
	};



	/* get max size of parameter pack */
	template <class... A>
	consteval auto size_of_max(void) -> xns::size_t {
		xns::size_t size = 0;
		((size = (sizeof(A) > size ? sizeof(A) : size)), ...);
		return size;
	}

	/* get max alignment of parameter pack */
	template <class... A>
	consteval auto align_of_max(void) -> xns::size_t {
		xns::size_t align = 0;
		((align = (alignof(A) > align ? alignof(A) : align)), ...);
		return align;
	}



	// -- A L I G N E D  S T O R A G E  S T R U C T ---------------------------

	template <xns::size_t L, decltype(L) A>
	struct aligned_storage final {


		// -- public members --------------------------------------------------

		alignas(A) xns::ubyte _data[L];


		// -- public accessors ------------------------------------------------

		/* data */
		inline constexpr auto data(void) noexcept -> xns::ubyte* {
			return _data;
		}

		/* size */
		inline consteval auto size(void) const noexcept -> decltype(L) {
			return L;
		}


		// -- public conversion -----------------------------------------------

		/* cast to type reference */
		template <class T>
		inline constexpr auto to_reference(void) noexcept -> T& {
			return *static_cast<T*>(static_cast<void*>(_data));
		}

		/* cast to const type reference */
		template <class T>
		inline constexpr auto to_reference(void) const noexcept -> const T& {
			return *static_cast<const T*>(static_cast<const void*>(_data));
		}

		/* cast to type pointer */
		template <class T>
		inline constexpr auto to_pointer(void) noexcept -> T* {
			return static_cast<T*>(static_cast<void*>(_data));
		}

		/* cast to const type pointer */
		template <class T>
		inline constexpr auto to_pointer(void) const noexcept -> const T* {
			return static_cast<const T*>(static_cast<const void*>(_data));
		}



	};





	// -- V A R I A N T  C L A S S --------------------------------------------

	template <class... A>
	class variant final {


		// -- assertions ------------------------------------------------------

		static_assert(xns::is_all_unique<A...>,
				"): TYPES MUST BE UNIQUE IN VARIANT :(");


		private:

			// -- private enums -----------------------------------------------

			/* null index */
			enum : xns::size_t { NULL_INDEX = sizeof...(A) };


		public:

			// -- public types ------------------------------------------------

			/* self */
			using self = variant<A...>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr variant(void) noexcept
			: _storage{}, _index{NULL_INDEX} {
			}

			/* type constructor */
			template <typename T>
			explicit constexpr variant(const T& value) requires xns::is_one_of<T, A...>
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// construct value by copy
				new(_storage.template to_pointer<T>()) T{value};
			}

			/* type move constructor */
			template <typename T>
			explicit constexpr variant(T&& value) requires xns::is_one_of<T, A...>
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// construct value by move
				new(_storage.template to_pointer<T>()) T{xns::move(value)};
			}

			/* in place type constructor */
			template <typename T, typename... U>
			constexpr variant(xns::in_place_type<T>, U&&... args)
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// construct value by emplace
				new(_storage.template to_pointer<T>()) T{xns::forward<U>(args)...};
			}

			/* in place index constructor */
			template <xns::size_t I, typename... U>
			constexpr variant(xns::in_place_index<I>, U&&... args)
			: _storage{}, _index{I} {
				using type = xns::type_at<I, A...>;
				// construct value by emplace
				new(_storage.template to_pointer<type>()) type{xns::forward<U>(args)...};
			}

			/* copy constructor */
			constexpr variant(const self& other) {
				// not implemented yet...
			}

			/* move constructor */
			inline constexpr variant(self&& other) noexcept
			: _storage{}, _index{other._index} {
				// call indexed move constructor
				_moves[_index](other._storage._data, _storage._data);
				// invalidate other index
				other._index = NULL_INDEX;
			}

			/* destructor */
			constexpr ~variant(void) noexcept {
				// call indexed destructor
				_destructors[_index](_storage._data);
			}


			// -- default assignment operators --------------------------------

			/* copy assignment operator */
			self& operator=(const self& other) = default;

			/* move assignment operator */
			self& operator=(self&& other) = default;


			// -- public modifiers --------------------------------------------

			/* emplace value */
			template <typename T, typename... U>
			auto emplace(U&&... args) -> void {
				// check if type is in variant
				static_assert(xns::is_one_of<T, A...>,
						"): VARIANT: TYPE NOT IN CONTAINER :(");
				// check if type is same as current type
				if (_index == xns::index_of<T, A...>()) {
					_storage.template to_reference<T>() = T{xns::forward<U>(args)...};
					return; }
				// call indexed destructor
				_destructors[_index](_storage._data);
				// set index
				_index = xns::index_of<T, A...>();
				// construct value by emplace
				new(_storage.template to_pointer<T>()) T{xns::forward<U>(args)...};
			}

			/* reset value */
			inline constexpr auto reset(void) noexcept -> void {
				// call indexed destructor
				_destructors[_index](_storage._data);
				// set null index
				_index = NULL_INDEX;
			}




			// -- public accessors --------------------------------------------

			/* get reference to value */
			template <typename T>
			inline constexpr auto get(void) noexcept -> T& {
				// check if type is in variant
				static_assert(xns::is_one_of<T, A...>,
						"): VARIANT: TYPE NOT IN CONTAINER :(");
				// return reference to value
				return _storage.template to_reference<T>();
			}

			/* get const reference to value */
			template <typename T>
			inline constexpr auto get(void) const noexcept -> const T& {
				// check if type is in variant
				static_assert(xns::is_one_of<T, A...>,
						"): VARIANT: TYPE NOT IN CONTAINER :(");
				// return const reference to value
				return _storage.template to_reference<T>();
			}

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
			template <class T>
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
			static constexpr inline auto copy_construct(void* src, void* dst) -> void {
				// copy object
				new(dst) T{*static_cast<T*>(src)};
			}

			/* custom move constructor */
			template <typename T>
			static constexpr inline auto move_construct(void* src, void* dst) noexcept -> void {
				// move object
				new(dst) T{xns::move(*static_cast<T*>(src))};
			}

			/* custom copy assignment */
			template <typename T>
			static constexpr inline auto copy_assign(void* src, void* dst) -> void {
				// assign object
				*static_cast<T*>(dst) = *static_cast<T*>(src);
			}

			/* custom move assignment */
			template <typename T>
			static constexpr inline auto move_assign(void* src, void* dst) noexcept -> void {
				// move object
				*static_cast<T*>(dst) = xns::move(*static_cast<T*>(src));
			}

			/* custom destructor */
			template <typename T>
			static constexpr inline auto destruct(void* obj) noexcept -> void {
				// destroy object
				static_cast<T*>(obj)->~T();
			}


			/* empty destructor */
			static constexpr inline auto nope(void*) noexcept -> void {}

			/* empty assignment constructor */
			static constexpr inline auto nope(void*, void*) noexcept -> void {}


			// -- private members ---------------------------------------------

			/* storage */
			aligned_storage<size_of_max<A...>(),
							align_of_max<A...>()> _storage;

			/* type index */
			xns::size_t _index;


			// -- private static members --------------------------------------

			/* destructors lookup array */
			static constexpr xns::array<void(*)(void*), sizeof...(A) + 1> _destructors{
				&destruct<A>..., &nope
			};

			/* copy constructors lookup array */
			static constexpr xns::array<void(*)(void*, void*), sizeof...(A) + 1> _copies{
				&copy_construct<A>..., &nope
			};

			/* move constructors lookup array */
			static constexpr xns::array<void(*)(void*, void*), sizeof...(A) + 1> _moves{
				&move_construct<A>..., &nope
			};

			/* copy assignment lookup array */
			static constexpr xns::array<void(*)(void*, void*), sizeof...(A) + 1> _assigns{
				&copy_assign<A>..., &nope
			};

			/* move assignment lookup array */
			static constexpr xns::array<void(*)(void*, void*), sizeof...(A) + 1> _moves_assigns{
				&move_assign<A>..., &nope
			};

	};


	class variant_factory final {





	};


}


#endif
