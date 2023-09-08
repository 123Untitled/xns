#ifndef REFERENCE_HEADER
#define REFERENCE_HEADER

// local headers
#include "move.hpp"
#include "is_same.hpp"
#include "remove.hpp"
#include "conditional.hpp"
#include "is_const.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E F E R E N C E ---------------------------------------------------

	template <typename T>
	class reference final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::reference<T>;

			/* value type */
			using type = T;

			/* reference type */
			using meta_ref = xns::conditional<xns::is_const<type>,
											  const type&,
											  type&>;

			/* pointer type */
			using meta_ptr = xns::conditional<xns::is_const<type>,
											  const type*,
											  type*>;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			reference(void) = delete;

			/* lvalue reference constructor */
			explicit inline reference(meta_ref ref) noexcept
			: _ref{&ref} {}

			/* deleted rvalue reference constructor */
			reference(type&&) = delete;

			/* copy constructor */
			inline reference(const self& other) noexcept
			: _ref{other._ref} {
				std::cout << "copy constructor" << std::endl;
			}

			/* move constructor */
			inline reference(self&&) noexcept = default;

			/* destructor */
			inline ~reference(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			inline auto operator=(const type& value) -> self& {
				static_assert(!xns::is_const<type>, "cannot assign to const reference");
				*_ref = value;
				return *this;
			}

			inline auto operator=(type&& value) noexcept -> self& {
				static_assert(!xns::is_const<type>, "cannot assign to const reference");
				*_ref = xns::move(value);
				return *this;
			}


			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = delete;


			// -- public conversion operators ---------------------------------

			/* conversion to reference */
			inline operator meta_ref(void) const noexcept {
				return *_ref;
			}


		private:

			// -- private members ---------------------------------------------

			/* pointer */
			self::meta_ptr _ref;

	};


	template <typename T>
	using mut_ref = xns::reference<T>;

	template <typename T>
	using const_ref = xns::reference<const T>;



	// -- ref function --------------------------------------------------------

	/* create mutable reference */
	template <typename T>
	inline constexpr auto make_reference(T& ref) noexcept -> xns::mut_ref<T> {
		return xns::mut_ref<T>{ref};
	}

	/* create const reference */
	template <typename T>
	inline constexpr auto ref(const T& ref) noexcept -> xns::const_ref<T> {
		return xns::const_ref<T>{ref};
	}

	/* deleted rvalue ref */
	template <typename T>
	auto ref(T&&) noexcept -> xns::mut_ref<T> = delete;

	/* deleted const rvalue ref */
	template <typename T>
	auto ref(const T&&) noexcept -> xns::const_ref<T> = delete;







};

#endif
