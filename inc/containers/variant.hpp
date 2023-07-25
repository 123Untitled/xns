#ifndef VARIANT_HEADER
#define VARIANT_HEADER

#include "type_traits.hpp"
#include "allocator.hpp"
#include "index_of.hpp"
#include "is_all_unique.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* get max size of parameter pack */
	template <class... A>
	consteval xns::size_t size_of_max(void) {
		xns::size_t size = 0;
		((size = (sizeof(A) > size ? sizeof(A) : size)), ...);
		return size;
	}

	/* get max alignment of parameter pack */
	template <class... A>
	consteval xns::size_t align_of_max(void) {
		xns::size_t align = 0;
		((align = (alignof(A) > align ? alignof(A) : align)), ...);
		return align;
	}



	// -- A L I G N E D  S T O R A G E ----------------------------------------

	template <xns::size_t L, xns::size_t A>
	struct aligned_storage final {


		// -- public members --------------------------------------------------

		alignas(A) xns::ubyte data[L];


		// -- public conversion -----------------------------------------------

		/* cast to type pointer */
		template <class T>
		inline T* to_pointer(void) {
			return static_cast<T*>(static_cast<void*>(data));
		}

		/* cast to type reference */
		template <class T>
		inline T& to_reference(void) {
			return *static_cast<T*>(static_cast<void*>(data));
		}

		/* cast to const type pointer */
		template <class T>
		inline const T* to_pointer(void) const {
			return static_cast<const T*>(static_cast<const void*>(data));
		}

		/* cast to const type reference */
		template <class T>
		inline const T& to_reference(void) const {
			return *static_cast<const T*>(static_cast<const void*>(data));
		}

	};




	// -- S A F E  U N I O N --------------------------------------------------

	template <class... A>
	class safe_union final : xns::unique_types<A...> {


		// -- assertions ------------------------------------------------------

		/* check if all types are scalar */
		static_assert((xns::is_scalar<A> && ...), "ALL TYPES MUST BE SCALAR");


		public:

			// -- public types ------------------------------------------------

			/* self */
			using self = safe_union<A...>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			safe_union(void) : _storage{} { /* init storage */ }

			/* copy constructor */
			safe_union(const self& other) = default;

			/* move constructor */
			safe_union(self&& other) = default;

			/* destructor */
			~safe_union(void) = default;


			// -- default assignment operators --------------------------------

			/* copy assignment operator */
			self& operator=(const self& other) = default;

			/* move assignment operator */
			self& operator=(self&& other) = default;


			// -- setters -----------------------------------------------------

			/* set value */
			template <class T>
			void set(T value) {
				// check if type is in union
				static_assert(xns::is_one_of<T, A...>, "TYPE NOT IN VARIANT");
				// set value
				_storage.template to_reference<T>() = value;
			}


			// -- accessors ---------------------------------------------------

			/* get reference to value */
			template <class T>
			T& get(void) {
				// check if type is in union
				static_assert(xns::is_one_of<T, A...>, "TYPE NOT IN VARIANT");
				// return reference to value
				return _storage.template to_reference<T>();
			}

			/* get const reference to value */
			template <class T>
			const T& get(void) const {
				// check if type is in union
				static_assert(xns::is_one_of<T, A...>, "TYPE NOT IN VARIANT");
				// return const reference to value
				return _storage.template to_reference<T>();
			}


			// -- public methods ----------------------------------------------

			/* reset */
			void reset(void) {
				// reset storage
				_storage = aligned_storage<size, align>{};
			}


			// -- comparison operators ----------------------------------------

			/* equality operator */
			bool operator==(const self& other) const {
				// return equality
				return _storage.template to_reference<max_type>() ==
					other._storage.template to_reference<max_type>();
			}

			/* inequality operator */
			bool operator!=(const self& other) const {
				// return inequality
				return !(*this == other);
			}

			/* type equality operator */
			template <class T>
			bool operator==(const T& value) const {
				// check if type is in union
				static_assert(xns::is_one_of<T, A...>, "TYPE NOT IN VARIANT");
				// return type equality
				return _storage.template to_reference<T>() == value;
			}

			/* type inequality operator */
			template <class T>
			bool operator!=(const T& value) const {
				// check if type is in union
				static_assert(xns::is_one_of<T, A...>, "TYPE NOT IN VARIANT");
				// return type inequality
				return !(*this == value);
			}

			// -- boolean operators -------------------------------------------

			/* boolean operator */
			operator bool(void) const {
				// return boolean
				return _storage.template to_reference<max_type>();
			}

			/* not operator */
			bool operator!(void) const {
				// return not
				return !_storage.template to_reference<max_type>();
			}


		private:

			// -- private constants -------------------------------------------

			/* size */
			static constexpr xns::size_t size = size_of_max<A...>();

			/* alignment */
			static constexpr xns::size_t align = align_of_max<A...>();


			// -- private types -----------------------------------------------

			/* max size type */
			using max_type = xns::unsign<size>;


			// -- private members ---------------------------------------------

			/* storage */
			aligned_storage<size, align> _storage;


	};



}


#endif
