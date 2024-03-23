/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_FUNCTION_HEADER
#define XNS_FUNCTION_HEADER

#include "xns/type_traits/type_operations/forward.hpp"
#include "xns/type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F U N C T I O N -----------------------------------------------------

	/* forward declaration */
	template <typename, typename...>
	class function;

	/* specialization */
	template <typename R, typename... A>
	class function<R(A...)> final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::function<R(A...)>;

			/* prototype type */
			using prototype = R(*)(A...);

			/* return type */
			using return_type = R;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			inline constexpr function(void) noexcept
			: _function{nullptr} {
			}

			/* nullptr constructor */
			inline constexpr function(decltype(nullptr)) noexcept
			: _function{nullptr} {
			}

			/* function pointer constructor */
			inline constexpr function(const prototype func) noexcept
			: _function{func} {
			}

			/* copy constructor */
			inline constexpr function(const self&) noexcept = default;

			/* move constructor */
			inline constexpr function(self&&) noexcept = default;

			/* destructor */
			~function(void) noexcept = default;


			// -- public assignments ------------------------------------------

			/* nullptr assignment */
			inline constexpr auto assign(decltype(nullptr)) noexcept -> void {
				_function = nullptr;
			}

			/* function pointer assignment */
			inline constexpr auto assign(const prototype func) noexcept -> void {
				_function = func;
			}

			/* copy assignment */
			inline constexpr auto assign(const self& other) noexcept -> void {
				_function = other._function;
			}

			/* move assignment */
			inline constexpr auto assign(self&& other) noexcept -> void {
				_function = other._function;
			}


			// -- public assignment operators ---------------------------------

			/* nullptr assignment operator */
			inline constexpr auto operator=(decltype(nullptr)) noexcept -> self& {
				return assign(nullptr), *this;
			}


			/* function pointer assignment operator */
			inline constexpr auto operator=(const prototype func) noexcept -> self& {
				_function = func;
				return *this;
			}

			/* copy assignment operator */
			inline constexpr auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			inline constexpr auto operator=(self&&) noexcept -> self& = default;


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline constexpr explicit operator bool(void) const noexcept {
				return _function != nullptr;
			}

			/* not operator */
			inline constexpr auto operator!(void) const noexcept -> bool {
				return _function == nullptr;
			}



			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline constexpr auto operator==(const self& other) const noexcept -> bool {
				return _function == other._function;
			}

			/* inequality operator */
			inline constexpr auto operator!=(const self& other) const noexcept -> bool {
				return _function != other._function;
			}


			// -- public function call operators ------------------------------

			/* function call operator */
			inline constexpr auto operator()(A&&... args) const -> return_type {
				return _function(xns::forward<A>(args)...);
			}


			// -- public methods ----------------------------------------------

			/* call */
			inline constexpr auto call(A&&... args) const -> return_type {
				return _function(xns::forward<A>(args)...);
			}

			/* reset */
			inline constexpr auto reset(void) noexcept -> void {
				_function = nullptr;
			}


		private:

			// -- private members ---------------------------------------------

			/* function pointer */
			prototype _function;

	}; // class function


	// -- deduction guides ----------------------------------------------------

	/* deduction guide for default constructor */
	function(void) -> function<void(void)>;

	/* deduction guide for function pointers */
	template <typename R, typename... A>
	function(R(*)(A...)) -> function<R(A...)>;


} // namespace xns

#endif // XNS_FUNCTION_HEADER
