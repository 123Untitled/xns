/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_REFERENCE_WRAPPER_HEADER
#define XNS_REFERENCE_WRAPPER_HEADER

// local headers
#include "move.hpp"
#include "is_same.hpp"
#include "remove.hpp"
#include "forward.hpp"
#include "addressof.hpp"
#include "invoke.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* is lvalue convertible */
	template <typename T, typename U>
	concept is_lvalue_convertible = requires(U&& u) {
		{ static_cast<U&&>(u) } -> xns::is_same<T&>;
	};


	// -- R E F E R E N C E  W R A P P E R ------------------------------------

	template <typename T>
	class reference_wrapper final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::reference_wrapper<T>;

			/* type */
			using type = T;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			reference_wrapper(void) = delete;

			/* lvalue reference constructor */
			template <typename U> requires xns::is_not_same<xns::remove_cvr<U>, self> 
			inline constexpr reference_wrapper(U&& ref) noexcept
			: _ptr{xns::addressof(ref)} {
				// check if U is not a rvalue reference
				static_assert(xns::is_lvalue_convertible<type, U>,
						"reference_wrapper cannot be constructed from rvalue reference.");
			}

			/* copy constructor */
			reference_wrapper(const self&) noexcept = default;

			/* move constructor */
			reference_wrapper(self&&) noexcept = default;

			/* destructor */
			~reference_wrapper(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&& other) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* get */
			auto get(void) const noexcept -> type& {
				return *_ptr;
			}


			// -- public conversion operators ---------------------------------

			/* conversion to reference */
			inline operator type&(void) const noexcept {
				return *_ptr;
			}


			// -- public function operators -----------------------------------

			// invoke
			template <typename... A>
			auto operator()(A&&... args) const noexcept(/* is no throw invocable */ true) -> decltype(auto) {
				return xns::invoke(*_ptr, xns::forward<A>(args)...);
			}


		private:

			// -- private members ---------------------------------------------

			/* pointer */
			type* _ptr;

	}; // class reference_wrapper


	// -- deduction guides ----------------------------------------------------

	/* deduction guide for lvalue reference */
	template <typename T>
	reference_wrapper(T&) -> reference_wrapper<T>;


	// -- ref function --------------------------------------------------------

	/* create mutable reference */
	template <typename T>
	inline constexpr auto ref(T& ref) noexcept -> xns::reference_wrapper<T> {
		return xns::reference_wrapper<T>{ref};
	}

	/* create const reference */
	template <typename T>
	inline constexpr auto cref(const T& ref) noexcept -> xns::reference_wrapper<const T> {
		return xns::reference_wrapper<const T>{ref};
	}

	/* deleted rvalue ref */
	template <typename T>
	auto ref(T&&) noexcept -> void = delete;

	/* deleted const rvalue ref */
	template <typename T>
	auto cref(const T&&) noexcept -> void = delete;


	/* create mutable reference */
	template <typename T>
	inline constexpr auto ref(xns::reference_wrapper<T> ref) noexcept -> xns::reference_wrapper<T> {
		return ref;
	}

	/* create const reference */
	template <typename T>
	constexpr auto cref(xns::reference_wrapper<T> ref) noexcept -> xns::reference_wrapper<const T> {
		return ref;
	}


} // namespace xns

#endif // XNS_REFERENCE_WRAPPER_HPP
