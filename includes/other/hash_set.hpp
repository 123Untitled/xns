#ifndef XNS_UNORDERED_SET_HPP
#define XNS_UNORDERED_SET_HPP

// local headers
#include "vector.hpp"
#include "hash.hpp"
#include "memory.hpp"
#include "variant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- U N O R D E R E D  S E T --------------------------------------------

	template <typename T>
	class unordered_set final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::unordered_set<T>;

			/* value type */
			using value_type = T;

			/* pointer type */
			using mut_ptr = value_type*;

			/* size type */
			using size_type = xns::size_t;

			/* allocator type */
			using allocator = xns::allocator<xns::variant<T>>;

			/* vector type */
			using vector = xns::variant<T>*;


			// -- public constructors -----------------------------------------

			/* default constructor */
			unordered_set(void) noexcept
			: _buckets{}, _capacity{DEFAULT_BUCKET_SIZE}, _size{0}, _max_load{DEFAULT_LOAD_FACTOR} {

				_buckets = allocator::allocate(_capacity);

				for (size_type i = 0; i < _capacity; ++i)
					allocator::construct(_buckets + i);

			}

			/* copy constructor */
			unordered_set(const self& other) noexcept
			{}

			/* move constructor */
			unordered_set(self&& other) noexcept
			{}

			/* destructor */
			~unordered_set(void) noexcept {
				for (size_type i = 0; i < _capacity; ++i) {
					allocator::destroy(_buckets + i);
				}
				allocator::deallocate(_buckets);
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self& other) -> self& {
				// check for self assignment
				if (this != &other) {
				} // return self reference
				return *this;
			}

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& {
				// check for self assignment
				if (this != &other) {
				} // return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			inline auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			inline auto capacity(void) const noexcept -> size_type {
				return _capacity;
			}

			/* max load factor */
			inline auto max_load_factor(void) const noexcept -> xns::f32 {
				return _max_load;
			}


			// -- public modifiers --------------------------------------------

			/* max load factor */
			inline auto max_load_factor(const xns::f32 factor) noexcept -> void {
				_max_load = factor;
			}


			/* insert */
			auto insert(const value_type& value) -> void {

				if (need_resize() == true) {
					//std::cout << "need resize" << std::endl;
					vector tmp;
					const size_type ncaps = _capacity * 2;

					tmp = allocator::allocate(ncaps);

					for (size_type i = 0; i < ncaps; ++i)
						allocator::construct(tmp + i);

					for (size_type i = 0; i < _capacity; ++i) {

						if (_buckets[i].contains() == true) {
							size_type hash = std::hash<T>{}(xns::get<T>(_buckets[i])) % ncaps;

							// quadratic probing
							//size_type step = 1;
							while (tmp[hash].contains() == true) {
								//hash = (hash + (step * step)) % ncaps;
								hash = (hash + 1) % ncaps;
								//++step;
							}
							tmp[hash].template emplace<T>(xns::move(xns::get<T>(_buckets[i])));
						}
					}

					for (size_type i = 0; i < _capacity; ++i)
						allocator::destroy(_buckets + i);
					allocator::deallocate(_buckets);
					_buckets = tmp;
					_capacity = ncaps;
				}

				size_type hash = std::hash<T>{}(value) % _capacity;

				// quadratic probing
				//size_type step = 1;

				while (_buckets[hash].contains() == true) {

					if (xns::get<T>(_buckets[hash]) == value)
						return;

					//hash = (hash + (step * step)) % _capacity;
					hash = (hash + 1) % _capacity;
					//++step;
				}

				_buckets[hash].template emplace<T>(value);
				++_size;
			}

			/* contains */
			auto contains(const value_type& value) const noexcept -> bool {

				size_type hash = std::hash<T>{}(value) % _capacity;

				// quadratic probing
				size_type step = 1;
				while (_buckets[hash] != nullptr) {
					if (*_buckets[hash] == value)
						return true;
					hash = (hash + (step * step)) % _capacity;
				}
				return false;
			}

		private:

			// -- private enums -----------------------------------------------

			/* default bucket size */
			enum : size_type {
				DEFAULT_BUCKET_SIZE = 16
			};

			static constexpr xns::f32 DEFAULT_LOAD_FACTOR = 0.75f;


			// -- private accessors -------------------------------------------

			/* get load factor */
			inline auto load_factor(void) const noexcept -> xns::f32 {
				return static_cast<xns::f32>(_size) / static_cast<xns::f32>(_capacity);
			}

			/* need resize */
			inline auto need_resize(void) const noexcept -> bool {
				return load_factor() >= _max_load;
			}


			// -- private members ---------------------------------------------

			/* buckets */
			vector _buckets;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;

			/* max load factor */
			xns::f32 _max_load;

	};

}

#endif // XNS_UNORDERED_SET_HPP
