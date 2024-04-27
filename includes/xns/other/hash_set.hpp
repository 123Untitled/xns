#ifndef XNS_UNORDERED_SET_HPP
#define XNS_UNORDERED_SET_HPP

// local headers
#include "xns/containers/vector.hpp"
#include "xns/other/hash.hpp"
#include "xns/memory/memory.hpp"
#include "xns/containers/variant.hpp"

#include "xns/memory/allocator.hpp"
#include "xns/memory/lifecycle.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- U N O R D E R E D  S E T --------------------------------------------

	template <typename ___key,
			//class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>,
			  typename ___allocator = xns::allocator<___key>>
	class unordered_set final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::unordered_set<___key, ___allocator>;

			/* key type */
			using key_type = ___key;

			/* value type */
			using value_type = ___key;

			/* size type */
			using size_type = xns::size_t;

			/* difference type */
			using difference_type = xns::ptrdiff_t;

			/* hasher type */
			//using hasher = Hash;

			/* key equal type */
			//using key_equal = KeyEqual;

			/* allocator type */
			using allocator_type = xns::allocator<xns::variant<___key>>;
			//using allocator_type = ___allocator;

			/* reference type */
			using reference = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* pointer type */
			using pointer = xns::allocator_traits<allocator_type>::pointer;

			/* const pointer type */
			using const_pointer = xns::allocator_traits<allocator_type>::const_pointer;

			/* iterator type */
			//using iterator = ...

			/* const iterator type */
			//using const_iterator = ...

			/* local iterator type */
			//using local_iterator = ...

			/* const local iterator type */
			//using const_local_iterator = ...

			/* node type */
			//using node_type = ...

			/* insert return type */
			//using insert_return_type = ...

			/* vector type */
			using vector = xns::variant<___key>*;


		private:

			// -- private types -----------------------------------------------

			/* allocator traits type */
			using ___alloc_traits = xns::allocator_traits<allocator_type>;

			/* lifecycle type */
			using ___lifecycle = xns::lifecycle<typename ___alloc_traits::value_type>;


			// -- private members ---------------------------------------------

			/* buckets */
			vector _buckets;

			/* capacity */
			size_type _capacity;

			/* size */
			size_type _size;

			/* max load factor */
			xns::f32 _max_load;

			/* allocator */
			[[no_unique_address]] allocator_type _allocator;

//template<class Iter, class NodeType>
//struct /*unspecified*/
//{
//    Iter     position;
//    bool     inserted;
//    NodeType node;
//};
//instantiated with template arguments iterator and node_type.

		public:

			// -- public constructors -----------------------------------------

		//	/* default constructor */
		//	unordered_set(void) noexcept
		//	: _buckets{}, _capacity{DEFAULT_BUCKET_SIZE}, _size{0}, _max_load{DEFAULT_LOAD_FACTOR}, _allocator{} {
		//
		//
		//		_buckets = ___alloc_traits::allocate(_allocator, _capacity);
		//
		//		for (size_type i = 0; i < _capacity; ++i)
		//			___lifecycle::construct(_buckets + i);
		//
		//	}
		//
		//	/* copy constructor */
		//	unordered_set(const self& other) noexcept
		//	{}
		//
		//	/* move constructor */
		//	unordered_set(self&& other) noexcept
		//	{}
		//
		//	/* destructor */
		//	~unordered_set(void) noexcept {
		//		for (size_type i = 0; i < _capacity; ++i) {
		//			___lifecycle::destroy(_buckets + i);
		//		}
		//		___alloc_traits::deallocate(_allocator, _buckets);
		//	}
		//
		//
		//	// -- public assignment operators ---------------------------------
		//
		//	/* copy assignment operator */
		//	auto operator=(const self& other) -> self& {
		//		// check for self assignment
		//		if (this != &other) {
		//		} // return self reference
		//		return *this;
		//	}
		//
		//	/* move assignment operator */
		//	auto operator=(self&& other) noexcept -> self& {
		//		// check for self assignment
		//		if (this != &other) {
		//		} // return self reference
		//		return *this;
		//	}


			// -- public accessors --------------------------------------------

			/* size */
			auto size(void) const noexcept -> size_type {
				return _size;
			}

			/* capacity */
			auto capacity(void) const noexcept -> size_type {
				return _capacity;
			}

			/* max load factor */
			auto max_load_factor(void) const noexcept -> xns::f32 {
				return _max_load;
			}


			// -- public modifiers --------------------------------------------

			/* max load factor */
			auto max_load_factor(const xns::f32 factor) noexcept -> void {
				_max_load = factor;
			}


		//	/* insert */
		//	auto insert(const value_type& value) -> void {
		//
		//		if (need_resize() == true) {
		//			//std::cout << "need resize" << std::endl;
		//			vector tmp;
		//			const size_type ncaps = _capacity * 2;
		//
		//			tmp = ___alloc_traits::allocate(_allocator, ncaps);
		//
		//			for (size_type i = 0; i < ncaps; ++i)
		//				___lifecycle::construct(tmp + i);
		//
		//			for (size_type i = 0; i < _capacity; ++i) {
		//
		//				if (_buckets[i].contains() == true) {
		//					size_type hash = std::hash<___key>{}(xns::get<___key>(_buckets[i])) % ncaps;
		//
		//					// quadratic probing
		//					//size_type step = 1;
		//					while (tmp[hash].contains() == true) {
		//						//hash = (hash + (step * step)) % ncaps;
		//						hash = (hash + 1) % ncaps;
		//						//++step;
		//					}
		//					tmp[hash].template emplace<___key>(xns::move(xns::get<___key>(_buckets[i])));
		//				}
		//			}
		//
		//			for (size_type i = 0; i < _capacity; ++i)
		//				___lifecycle::destroy(_buckets + i);
		//			___alloc_traits::deallocate(_allocator, _buckets);
		//			_buckets = tmp;
		//			_capacity = ncaps;
		//		}
		//
		//		size_type hash = std::hash<___key>{}(value) % _capacity;
		//
		//		// quadratic probing
		//		//size_type step = 1;
		//
		//		while (_buckets[hash].contains() == true) {
		//
		//			if (xns::get<___key>(_buckets[hash]) == value)
		//				return;
		//
		//			//hash = (hash + (step * step)) % _capacity;
		//			hash = (hash + 1) % _capacity;
		//			//++step;
		//		}
		//
		//		_buckets[hash].template emplace<___key>(value);
		//		++_size;
		//	}
		//
		//	/* contains */
		//	auto contains(const value_type& value) const noexcept -> bool {
		//
		//		size_type hash = std::hash<___key>{}(value) % _capacity;
		//
		//		// quadratic probing
		//		size_type step = 1;
		//		while (_buckets[hash] != nullptr) {
		//			if (*_buckets[hash] == value)
		//				return true;
		//			hash = (hash + (step * step)) % _capacity;
		//		}
		//		return false;
		//	}

		private:

			// -- private enums -----------------------------------------------

			/* default bucket size */
			enum : size_type {
				DEFAULT_BUCKET_SIZE = 16
			};

			static constexpr xns::f32 DEFAULT_LOAD_FACTOR = 0.75f;


			// -- private accessors -------------------------------------------

			/* get load factor */
			auto _load_factor(void) const noexcept -> xns::f32 {
				return static_cast<xns::f32>(_size) / static_cast<xns::f32>(_capacity);
			}

			/* need resize */
			auto _need_resize(void) const noexcept -> bool {
				return _load_factor() >= _max_load;
			}

	};

}

#endif // XNS_UNORDERED_SET_HPP
