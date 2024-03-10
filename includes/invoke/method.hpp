#ifndef XNS_METHOD_HPP
#define XNS_METHOD_HPP

#include "forward.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E T H O D ---------------------------------------------------------

	/* empty declaration */
	template <typename, typename, typename...>
	class method;


	template <typename O, typename R, typename... A>
	class method<O, R(A...)> final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self        = xns::method<O, R(A...)>;

			/* object type */
			using object      = O;

			/* prototype type */
			using prototype   = R(O::*)(A...);

			/* return type */
			using return_type = R;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr method(void) noexcept
			: _method{nullptr} {
			}

			/* nullptr constructor */
			inline constexpr method(decltype(nullptr)) noexcept
			: _method{nullptr} {
			}

			/* method pointer constructor */
			inline constexpr method(const prototype m) noexcept
			: _method{m} {
			}

			/* copy constructor */
			constexpr method(const self&) noexcept = default;

			/* move constructor */
			constexpr method(self&&) noexcept = default;

			/* destructor */
			~method(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* nullptr assignment operator */
			inline constexpr auto operator=(decltype(nullptr)) noexcept -> self& {
				_method = nullptr;
				return *this;
			}

			/* method pointer assignment operator */
			inline constexpr auto operator=(const prototype m) noexcept -> self& {
				_method = m;
				return *this;
			}

			/* copy assignment operator */
			constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline constexpr explicit operator bool(void) const noexcept {
				return _method != nullptr;
			}

			/* not operator */
			inline constexpr auto operator!(void) const noexcept -> bool {
				return _method == nullptr;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline constexpr auto operator==(const self& other) const noexcept -> bool {
				return _method == other._method;
			}

			/* inequality operator */
			inline constexpr auto operator!=(const self& other) const noexcept -> bool {
				return _method != other._method;
			}


			// -- public methods ----------------------------------------------

			/* method call operator */
			inline constexpr auto operator()(object& instance, A&&... arguments) const -> return_type {
				return (instance.*_method)(xns::forward<A>(arguments)...);
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* call */
			inline constexpr auto call(object& instance, A&&... arguments) const -> return_type {
				return (instance.*_method)(xns::forward<A>(arguments)...);
			}

			/* reset */
			inline constexpr auto reset(void) noexcept -> void {
				_method = nullptr;
			}


		private:

			// -- private members ---------------------------------------------

			/* method pointer */
			prototype _method;

	};


	// -- deduction guides ----------------------------------------------------

	/* method deduction guide */
	template <typename O, typename R, typename... A>
	method(R(O::*)(A...)) -> method<O, R(A...)>;

}

#endif // XNS_METHOD_HPP
