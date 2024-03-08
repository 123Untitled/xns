#ifndef XNS_METHOD_HPP
#define XNS_METHOD_HPP

#include "types.hpp"
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
			: _method{nullptr} {}

			/* nullptr constructor */
			inline constexpr method(xns::null) noexcept
			: _method{nullptr} {}

			/* method pointer constructor */
			inline constexpr method(const prototype method) noexcept
			: _method{method} {}

			/* copy constructor */
			inline constexpr method(const self& other) noexcept
			: _method{other._method} {}

			/* move constructor */
			inline constexpr method(self&& other) noexcept
			: method{other} {}

			/* destructor */
			inline constexpr ~method(void) noexcept = default;


			// -- public assignments ------------------------------------------

			/* nullptr assignment */
			inline constexpr auto assign(xns::null) noexcept -> void {
				_method = nullptr;
			}

			/* method pointer assignment */
			inline constexpr auto assign(const prototype method) noexcept -> void {
				_method = method;
			}

			/* copy assignment */
			inline constexpr auto assign(const self& other) noexcept -> void {
				_method = other._method;
			}

			/* move assignment */
			inline constexpr auto assign(self&& other) noexcept -> void {
				assign(other);
			}


			// -- public assignment operators ---------------------------------

			/* nullptr assignment operator */
			inline constexpr auto operator=(xns::null) noexcept -> self& {
				assign(nullptr);
				return *this;
			}

			/* method pointer assignment operator */
			inline constexpr auto operator=(const prototype method) noexcept -> self& {
				assign(method);
				return *this;
			}

			/* copy assignment operator */
			inline constexpr auto operator=(const self& other) noexcept -> self& {
				assign(other);
				return *this;
			}

			/* move assignment operator */
			inline constexpr auto operator=(self&& other) noexcept -> self& {
				operator=(other);
				return *this;
			}


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
