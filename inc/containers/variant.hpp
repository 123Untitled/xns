#ifndef VARIANT_HEADER
#define VARIANT_HEADER

// local headers
#include "move.hpp"
#include "forward.hpp"
#include "aligned_storage.hpp"
#include "in_place.hpp"
#include "index_of.hpp"
#include "type_at.hpp"
#include "is_all_unique.hpp"
#include "is_const.hpp"
#include "allocator.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- V A R I A N T  C L A S S --------------------------------------------

	template <class... A>
	class variant final {


		// -- assertions ------------------------------------------------------

		/* check unique types */
		static_assert(xns::is_all_unique<A...>,
				"): TYPES MUST BE UNIQUE IN VARIANT :(");

		/* disallow const types */
		static_assert(((xns::is_const<A> == false) && ...),
				"): CONST TYPES ARE NOT ALLOWED IN VARIANT :(");


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
			: _storage{}, _index{NULL_INDEX} {}

			/* type constructor */
			template <typename T>
			explicit constexpr variant(const T& value) requires xns::is_one_of<T, A...>
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// call allocator constructor
				xns::allocator<T>::construct(
						_storage.template to_pointer<T>(),
						value
				);
			}

			/* type move constructor */
			template <typename T>
			explicit constexpr variant(T&& value) requires xns::is_one_of<T, A...>
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// call allocator constructor
				xns::allocator<T>::construct(
						_storage.template to_pointer<T>(),
						xns::move(value)
				);
			}

			/* in place type constructor */
			template <typename T, typename... U>
			constexpr variant(xns::in_place_type<T>, U&&... args)
			: _storage{}, _index{xns::index_of<T, A...>()} {
				// call allocator constructor
				xns::allocator<T>::construct(
						_storage.template to_pointer<T>(),
						xns::forward<U>(args)...
				);
			}

			/* in place index constructor */
			template <xns::size_t I, typename... U>
			constexpr variant(xns::in_place_index<I>, U&&... args)
			: _storage{}, _index{I} {
				// get type at index
				using T = xns::type_at<I, A...>;
				// call allocator constructor
				xns::allocator<T>::construct(
						_storage.template to_pointer<T>(),
						xns::forward<U>(args)...
				);
			}

			/* copy constructor */
			constexpr variant(const self& other)
			: _storage{}, _index{other._index} {
				// call indexed copy constructor
				_copies[CONSTRUCT][_index](other._storage._data, _storage._data);
			}

			/* move constructor */
			inline constexpr variant(self&& other) noexcept
			: _storage{}, _index{other._index} {
				// call indexed move constructor
				_moves[CONSTRUCT][_index](other._storage._data, _storage._data);
			}

			/* destructor */
			inline constexpr ~variant(void) noexcept {
				// call indexed destructor
				_destructors[_index](_storage._data);
			}


			// -- default assignment operators --------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const self& other) -> self& {
				// check if type is same as current type
				if (_index == other._index) {
					// call indexed copy assignment
					_copies[ASSIGN][_index](other._storage._data, _storage._data);
					return *this; }
				// call indexed destructor
				_destructors[_index](_storage._data);
				// set index
				_index = other._index;
				// call indexed copy constructor
				_copies[CONSTRUCT][_index](other._storage._data, _storage._data);

				return *this;
			}

			/* move assignment operator */
			constexpr auto operator=(self&& other) noexcept -> self& {
				// check if type is same as current type
				if (_index == other._index) {
					// call indexed move assignment
					_moves[ASSIGN][_index](other._storage._data, _storage._data);
					return *this; }
				// call indexed destructor
				_destructors[_index](_storage._data);
				// set index
				_index = other._index;
				// call indexed move constructor
				_moves[CONSTRUCT][_index](other._storage._data, _storage._data);

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
				_destructors[_index](_storage._data);
				// set index
				_index = xns::index_of<T, A...>();

				// call allocator emplace constructor
				xns::allocator<T>::construct(
						_storage.template to_pointer<T>(),
						xns::forward<U>(args)...
				);
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
			static constexpr inline auto copy_construct(const void* src, void* dst) -> void {
				// call allocator copy constructor
				xns::allocator<T>::construct(static_cast<T*>(dst), *static_cast<const T*>(src));
			}

			/* custom move constructor */
			template <typename T>
			static constexpr inline auto move_construct(void* src, void* dst) noexcept -> void {
				// call allocator move constructor
				xns::allocator<T>::construct(static_cast<T*>(dst), xns::move(*static_cast<T*>(src)));
			}

			/* custom copy assignment */
			template <typename T>
			static constexpr inline auto copy_assign(const void* src, void* dst) -> void {
				// call allocator copy assignment
				xns::allocator<T>::assign(*static_cast<T*>(dst), *static_cast<const T*>(src));
			}

			/* custom move assignment */
			template <typename T>
			static constexpr inline auto move_assign(void* src, void* dst) noexcept -> void {
				// call allocator move assignment
				xns::allocator<T>::assign(*static_cast<T*>(dst), xns::move(*static_cast<T*>(src)));
			}

			/* custom destructor */
			template <typename T>
			static constexpr inline auto destructor(void* obj) noexcept -> void {
				// call allocator destructor
				xns::allocator<T>::destroy(static_cast<T*>(obj));
			}


			/* empty destructor */
			static inline constexpr auto nope(void*) noexcept -> void {}

			/* empty assignment */
			static inline constexpr auto nope(void*, void*) noexcept -> void {}

			/* empty const assignment */
			static inline constexpr auto nope(const void*, void*) noexcept -> void {}


			// -- private members ---------------------------------------------

			/* storage */
			aligned_storage<size_of_max<A...>(),
							align_of_max<A...>()> _storage;

			/* type index */
			xns::size_t _index;


			// -- private types -----------------------------------------------

			/* copy prototype */
			using copy_proto = void(*)(const void*, void*);

			/* move prototype */
			using move_proto = void(*)(void*, void*);

			/* destructor prototype */
			using kill_proto = void(*)(void*);


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


	};





}


#endif
