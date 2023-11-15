#ifndef XNS_LITERAL_MAP_HEADER
#define XNS_LITERAL_MAP_HEADER

#include "is_char.hpp"
#include "is_all_unique.hpp"
#include "char_sequence.hpp"
#include "string_literal.hpp"
#include "forward.hpp"
#include "move.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I T E R A L  M A P ------------------------------------------------

	template <class T, xns::basic_string_literal... L>
	class literal_map final {


		private:

			// -- private types -----------------------------------------------

			/* key helper */
			template <xns::basic_string_literal l>
			using key = xns::make_character_seq<typename decltype(l)::char_t, l>;


		// -- assertions ------------------------------------------------------

		/* check all string literals are unique */
		static_assert(xns::is_all_unique
					 <key<L>...>,
					 "): STRING LITERALS MUST BE UNIQUE :(");

		/* check for map size */
		static_assert(sizeof...(L) > 0, "): MAP MUST HAVE AT LEAST 1 KEY :(");


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = T;

			/* self type */
			using self = literal_map<value_type, L...>;

			/* reference type */
			using reference = value_type&;

			/* move reference type */
			using move_reference = value_type&&;

			/* const reference type */
			using const_reference = const value_type&;


		private:



			// -- private element struct --------------------------------------

			template <typename SEQ>
			struct element {

				/* value */
				value_type data;

			};


			// -- implementation ----------------------------------------------

			struct impl final : public element<key<L>>... {


				// -- constructors --------------------------------------------

				/* default constructor */
				inline constexpr impl(void)
				: element<key<L>>{ }... {
					// nothing to do...
				}

				/* variadic constructor */
				template <class... A>
				inline constexpr impl(A&&... args) requires (sizeof...(A) > 1)
				: element<key<L>>{xns::forward<A>(args)}... {
					// forward arguments to elements
				}

				/* copy constructor */
				inline constexpr impl(const impl& other)
				: element<key<L>>{other}... {
					// copy other elements
				}

				/* move constructor */
				inline constexpr impl(impl&& other) noexcept
				: element<key<L>>{xns::move(other)}... {
					// move other elements
				}

				/* destructor */
				inline ~impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				inline impl& operator=(const impl& other) {
					// copy other elements
					((element<key<L>>::operator=(other)), ...);
					// return self reference
					return *this;
				}

				/* move assignment operator */
				inline impl& operator=(impl&& other) noexcept {
					// move other elements
					((element<key<L>>::operator=(xns::move(other))), ...);
					// return self reference
					return *this;
				}


			};


			// -- private members ---------------------------------------------

			/* implementation */
			impl _impl;


		public:

			// -- public constructors -----------------------------------------

			/* default constructor */
			constexpr literal_map(void)
			: _impl{ } {
				// nothing to do...
			}

			/* variadic constructor */
			template <class... A>
			constexpr literal_map(A&&... args) requires (sizeof...(A) > 1)
			: _impl{xns::forward<A>(args)...} {
				static_assert(sizeof...(A) == sizeof...(L),
							  "): INCORRECT NUMBER OF ARGUMENTS :(");
				// forward arguments to implementation
			}

			/* copy constructor */
			constexpr literal_map(const self& other)
			: _impl{other._impl} {
				// nothing to do...
			}

			/* move constructor */
			constexpr literal_map(self&& other) noexcept
			: _impl{xns::move(other._impl)} {
				// nothing to do...
			}

			/* destructor */
			~literal_map(void) noexcept = default;


			// -- assignment operators ----------------------------------------

			/* copy assignment operator */
			constexpr self& operator=(const self& other) {
				// check for self assignment
				if (this != &other) {
					// copy other implementation
					_impl = other._impl;
				} // return self reference
				return *this;
			}

			/* move assignment operator */
			constexpr self& operator=(self&& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// move other implementation
					_impl = xns::move(other._impl);
				} // return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* get size */
			consteval size_t size(void) const noexcept {
				// return number of elements
				return sizeof...(L);
			}

			/* get element */
			template <xns::basic_string_literal l>
			constexpr reference get(void) {
				// return element indexed by key
				return _impl.element<key<l>>::data;
			}

			/* const get element */
			template <xns::basic_string_literal l>
			constexpr const_reference get(void) const {
				// return const element indexed by key
				return _impl.element<key<l>>::data;
			}


			// -- public setters ----------------------------------------------

			/* set element by copy */
			template <xns::basic_string_literal l>
			constexpr void set(const_reference value) {
				// set element by copy
				_impl.element<key<l>>::data = value;
			}

			/* set element by move */
			template <xns::basic_string_literal l>
			constexpr void set(move_reference value) {
				// set element by move
				_impl.element<key<l>>::data = xns::move(value);
			}

			/* emplace element */
			template <xns::basic_string_literal l, class... A>
			constexpr void emplace(A&&... args) {
				// forward arguments to element
				_impl.element<key<l>>::data = value_type{xns::forward<A>(args)...};
			}

			/* clear */
			constexpr void clear(void) {
				// clear all elements
				((_impl.element<key<L>>::data = value_type{}), ...);
			}


			// -- public loopers ----------------------------------------------

			/* for each element */
			constexpr void for_each(void (*f)(reference)) {
				(f(_impl.element<key<L>>::data), ...);
			}

			/* for each const element */
			constexpr void for_each(void (*f)(const_reference)) const {
				(f(_impl.element<key<L>>::data), ...);
			}

			/* contains element */
			constexpr bool contains(const_reference value) const {
				return ((value == _impl.element<key<L>>::data) || ...);
			}

	};


}

#endif
