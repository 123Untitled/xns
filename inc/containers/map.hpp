#ifndef MAP_HEADER
#define MAP_HEADER

#include "types.hpp"
#include "allocator.hpp"
#include "unique_ptr.hpp"
#include "weak_ptr.hpp"
#include "tree.hpp"
#include "literal_map.hpp"
#include "tuple.hpp"
#include "is_comparable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M A P  C L A S S ----------------------------------------------------

	template <typename K, typename V>
	class map final {


		// assert that K is comparable
		static_assert(xns::is_comparable<K>,
				"): MAP: KEY TYPE MUST BE COMPARABLE :(");


		private:

			// -- forward declarations ----------------------------------------

			/* key value */
			class key_value;


		public:

			// -- public types ------------------------------------------------

			/* key type */
			using key_type = K;

			/* value type */
			using value_type = V;

			/* size type */
			using size_type = xns::size_t;

			/* reference type */
			using reference = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* move reference type */
			using move_reference = value_type&&;

			/* pointer type */
			using mutable_pointer = value_type*;

			/* const pointer type */
			using const_pointer = const value_type*;


			/* tree type */
			using tree_type = xns::tree<key_value>;

			/* node type */
			using node = typename tree_type::node;

			/* node pointer type */
			using node_pointer = typename tree_type::node_pointer;



		private:

			// -- private members ---------------------------------------------

			/* tree */
			tree_type _tree;



			// -- private classes ---------------------------------------------

			class key_value final {


				public:

					// -- public types ----------------------------------------

					/* self type */
					using self = xns::map<K, V>::key_value;


					// -- public lifecycle ------------------------------------

					/* default constructor */
					inline constexpr key_value(void)
					: _key{}, _value{} {}

					/* copy key_value constructor */
					inline constexpr key_value(const key_type& key, const value_type& value)
					: _key{key}, _value{value} {}

					/* forward constructor */
					template <typename T = key_type, typename U = value_type>
					inline constexpr key_value(T&& key, U&& value)
					: _key{xns::forward<T>(key)}, _value{xns::forward<U>(value)} {}

					/* copy constructor */
					inline constexpr key_value(const self& other)
					: _key{other._key}, _value{other._value} {}

					/* move constructor */
					inline constexpr key_value(self&& other) noexcept
					: _key{xns::move(other._key)}, _value{xns::move(other._value)} {}

					/* destructor */
					inline constexpr ~key_value(void) noexcept = default;


					// -- public assignment operators -------------------------

					/* copy operator */
					inline constexpr auto operator=(const self& other) -> self& {
						// copy key object
						_key = other._key;
						// copy value object
						_value = other._value;
						// return self reference
						return *this;
					}

					/* move operator */
					inline constexpr auto operator=(self&& other) noexcept -> self& {
						// move key object
						_key = xns::move(other._key);
						// move value object
						_value = xns::move(other._value);
						// return self reference
						return *this;
					}


					// -- public comparison operators -------------------------

					/* equality operator */
					inline constexpr auto operator==(const self& other) const -> bool {
						// return equality
						return _key == other._key;
					}

					/* inequality operator */
					inline constexpr auto operator!=(const self& other) const -> bool {
						// return inequality
						return _key != other._key;
					}

					/* less than operator */
					inline constexpr auto operator<(const self& other) const -> bool {
						// return less than
						return _key < other._key;
					}

					/* greater than operator */
					inline constexpr auto operator>(const self& other) const -> bool {
						// return greater than
						return _key > other._key;
					}

					/* less than or equal to operator */
					inline constexpr auto operator<=(const self& other) const -> bool {
						// return less than or equal to
						return _key <= other._key;
					}

					/* greater than or equal to operator */
					inline constexpr auto operator>=(const self& other) const -> bool {
						// return greater than or equal to
						return _key >= other._key;
					}


					// -- public accessors ------------------------------------

					/* key accessor */
					inline constexpr auto key(void) -> key_type& {
						// return key
						return _key;
					}

					/* const key accessor */
					inline constexpr auto key(void) const -> const key_type& {
						// return key
						return _key;
					}

					/* value accessor */
					inline constexpr auto value(void) -> value_type& {
						// return value
						return _value;
					}

					/* const value accessor */
					inline constexpr auto value(void) const -> const value_type& {
						// return value
						return _value;
					}


				private:

					// -- private members -------------------------------------

					/* key */
					key_type _key;

					/* value */
					value_type _value;

			};




		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline map(void)
			: _tree{} {}

			/* copy constructor */
			inline map(const map& other)
			: _tree{other._tree} {}

			/* move constructor */
			inline map(map&& other) noexcept
			: _tree{xns::move(other._tree)} {}

			/* destructor */
			inline ~map(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const map& other) -> map& {
				// copy tree
				_tree = other._tree;
				// return self reference
				return *this;
			}

			/* move assignment operator */
			inline auto operator=(map&& other) noexcept -> map& {
				// move tree
				_tree = xns::move(other._tree);
				// return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			inline auto size(void) const -> size_type {
				// return size
				return _tree.size();
			}

			/* empty */
			inline auto empty(void) const -> bool {
				// return empty
				return _tree.empty();
			}

			/* find */
			inline auto find(const key_type& key) -> node_pointer {
				return nullptr;
			}

			inline auto contains(const key_type& key) -> bool {
				return false;
			}


			// -- public modifiers --------------------------------------------

			/* insert */
			inline auto insert(const key_type& key, const value_type& value) -> void {
				_tree.insert(key_value{key, value});
			}


			/* move insert */
			void move_insert(const key_type& key, move_reference value) {
				// code here...
			}

			/* emplace insert */
			template <class... A>
			void emplace_insert(const key_type& key, A&&... args) {
				// code here...
			}




			auto clear(void) -> void {
			}

			auto insert_or_assign(const key_type& key, const value_type& value) -> void {
			}

			template <typename... A>
			auto emplace(const key_type& key, A&&... args) -> void {
			}

			auto erase(const key_type& key) -> void {
			}

			auto swap(map& other) -> void {
			}


			auto operator[](const key_type& key) -> void {
			}



			static xns::string vcall(const key_value& data) {
				xns::string str;
				str.to_string(data.key());
				return str;
			}

			static xns::size_t scall(const key_value& data) {
				xns::string str;
				str.to_string(data.key());
				return str.size();
			}

		void print(void) {
			_tree.print(scall, vcall);
		}




		private:

	};




	template <typename T, typename U = T>
	class value_compare {

		public:

			// -- public types --------------------------------------------

			static inline auto compare(const T& lhs, const U& rhs) -> bool {
				return lhs < rhs;
			}


	};



};

#endif
