#ifndef XNS_REFERENCE_HEADER
#define XNS_REFERENCE_HEADER

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




			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			reference(void) = delete;

			/* lvalue reference constructor */
			template <typename U> requires xns::is_not_same<xns::remove_cvr<U>, self>
			explicit inline reference(U&& ref) noexcept
			: _ref{&ref} {
				std::cout << "lvalue reference constructor" << std::endl;
			}

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

			auto get(void) const noexcept -> type& {
				return *_ref;
			}

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) noexcept -> self& = delete;


			// -- public conversion operators ---------------------------------

			/* conversion to reference */
			inline operator type&(void) const noexcept {
				return *_ref;
			}


		private:

			// -- private members ---------------------------------------------

			/* pointer */
			self::type* _ref;

	};


	// -- deduction guides ----------------------------------------------------

	/* deduction guide for lvalue reference */
	template <typename T>
	reference(T&) -> reference<T>;


	// -- ref function --------------------------------------------------------

	/* create mutable reference */
	template <typename T>
	inline constexpr auto ref(T& ref) noexcept -> xns::reference<T> {
		return xns::reference<T>{ref};
	}

	/* create const reference */
	template <typename T>
	inline constexpr auto ref(const T& ref) noexcept -> xns::reference<const T> {
		return xns::reference<const T>{ref};
	}

	/* deleted rvalue ref */
	template <typename T>
	auto ref(T&&) noexcept -> xns::reference<T> = delete;

	/* deleted const rvalue ref */
	template <typename T>
	auto ref(const T&&) noexcept -> xns::reference<const T> = delete;







};

#endif
