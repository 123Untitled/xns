#ifndef OPTIONAL_HEADER
#define OPTIONAL_HEADER

// local headers
#include "aligned_storage.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "in_place.hpp"
#include "is_constructible.hpp"
#include "is_destructible.hpp"
#include "is_trivially_destructible.hpp"
#include "allocator.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- N U L L O P T  S T R U C T ------------------------------------------

	struct nullopt { constexpr nullopt(void) = default; };


	// -- O P T I O N A L  C L A S S ------------------------------------------

	template <class T>
	class optional {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = optional<T>;

			/* value type */
			using value_type = T;

			/* allocator type */
			using allocator = xns::allocator<value_type>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr optional(void) noexcept
			: _storage{}, _active{false} {}

			/* nullopt constructor */
			constexpr optional(nullopt) noexcept
			: _storage{}, _active{false} {}

			/* value copy constructor */
			constexpr optional(const value_type& value) noexcept
			: _storage{}, _active{true} {

				/* copy construct */
				allocator::construct(
					_storage.template to_pointer<value_type>(),
					value
				);
			}

			/* value move constructor */
			constexpr optional(value_type&& value) noexcept
			: _storage{}, _active{true} {

				/* move construct */
				allocator::construct(
					_storage.template to_pointer<value_type>(),
					xns::move(value)
				);
			}

			/* emplace constructor */
			template <class... A>
			constexpr optional(A&&... args) noexcept
			: _storage{}, _active{true} {

				/* emplace construct */
				allocator::construct(
					_storage.template to_pointer<value_type>(),
					xns::forward<A>(args)...
				);
			}

			/* copy constructor */
			constexpr optional(const self& other) noexcept
			: _storage{}, _active{other._active} {

				if (_active == false) { return; }

				/* copy construct */
				allocator::construct(
					_storage.template to_pointer<value_type>(),
					other._storage.template to_reference<value_type>()
				);
			}

			/* move constructor */
			constexpr optional(self&& other) noexcept
			: _storage{}, _active{other._active} {

				if (_active == false) { return; }

				/* move construct */
				allocator::construct(
					_storage.template to_pointer<value_type>(),
					xns::move(other._storage.template to_reference<value_type>())
				);
			}

			/* destructor */
			constexpr ~optional(void) noexcept {

				if (_active == false) { return; }

				allocator::destroy(
					_storage.template to_pointer<value_type>()
				);

			}


		private:

			// -- private members ---------------------------------------------

			/* storage */
			xns::aligned_storage<sizeof(T),
								alignof(T)> _storage;

			/* is active */
			bool _active;


	};







	inline void fu() {



		xns::optional<int> o;

		xns::optional<int> o2{xns::nullopt{}};


	}

}

#endif // OPTIONAL_HEADER
