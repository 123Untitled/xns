#ifndef HASH_SET_HEADER
#define HASH_SET_HEADER

// local headers
#include "vector.hpp"
#include "hash.hpp"
#include "list.hpp"

// c++ standard library headers
#include <set>
#include <vector>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- H A S H  S E T ------------------------------------------------------

	template <typename T>
	class hash_set final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = hash_set<T>;

			/* value type */
			using value_type = T;



			// -- public constructors -----------------------------------------

			/* default constructor */
			hash_set(void) noexcept
			: _buckets{}, _size{0} {
				_buckets.resize(DEFAULT_BUCKET_SIZE);
			}

			/* copy constructor */
			hash_set(const self& other) noexcept
			//:
			{
				// code here...
			}

			/* move constructor */
			hash_set(self&& other) noexcept
			//:
			{
				// code here...
			}

			/* destructor */
			~hash_set(void) noexcept {
				// code here...
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			self& operator=(const self& other) noexcept {
				// check for self assignment
				if (this != &other) {
				} // return self reference
				return *this;
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// check for self assignment
				if (this != &other) {
				} // return self reference
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* size */
			inline auto size(void) const noexcept -> xns::size_t {
				return _size;
			}


			// -- public modifiers --------------------------------------------

			/* insert */
			auto insert(const value_type& value) -> void {
				auto hash = xns::hash(value) % _buckets.size();
				auto& list = _buckets[hash];

				/* if (list.empty() == false) {
					std::cout << "collision" << std::endl;
				} */
				return ;

				_buckets[hash].push_front(value);
				++_size;

				if (need_resize()) {

					 //std::cout << "RESIZE: " << _buckets.size() * 2 << std::endl;
					// resize
					xns::vector<xns::list<value_type>> tmp;
					tmp.resize(_buckets.size() * 2);
					// rehash
					for (auto& list : _buckets) {
						for (auto& value : list) {
							auto hash = xns::hash(value) % tmp.size();
							tmp[hash].push_front(xns::move(value));
						}
					}
					// swap
					_buckets = xns::move(tmp);
				}
			}

			/* contains */
			auto contains(const value_type& value) const noexcept -> bool {
				auto hash = xns::hash(value) % _buckets.size();
				auto& list = _buckets[hash];
				return list.contains(value);
			}

			auto print(void) -> void {
				std::cout << "HASH SET" << std::endl;
				std::cout << "size: " << _size << std::endl;
				std::cout << "buckets: " << _buckets.size() << std::endl;
				for (const auto& bucket : _buckets) {
					std::cout << bucket.size() << " ";
				}
				std::cout << std::endl;
			}

		private:

			// -- private enums -----------------------------------------------

			/* default bucket size */
			enum : xns::size_t {
				DEFAULT_BUCKET_SIZE = 16
			};

			constexpr static xns::f32 LOAD_FACTOR_THRESHOLD = 0.75f;

			// -- private accessors -------------------------------------------

			/* get load factor */
			inline auto load_factor(void) const noexcept -> double {
				// std::cout << "load factor: " << (double)_size / (double)_buckets.size() << std::endl;
				// std::cout << "buckets: " << _buckets.size() << std::endl;
				// std::cout << "size: " << _size << std::endl;
				return _size / _buckets.size();
			}

			/* need resize */
			inline auto need_resize(void) const noexcept -> bool {
				return load_factor() > LOAD_FACTOR_THRESHOLD;
			}


			// -- private members ---------------------------------------------

			/* buckets */
			xns::vector<xns::list<value_type>> _buckets;

			/* size */
			xns::size_t _size;



	};



}

#endif // HASH_SET_HEADER
