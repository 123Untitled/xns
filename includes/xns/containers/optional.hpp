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

#ifndef XNS_OPTIONAL_HEADER
#define XNS_OPTIONAL_HEADER

// local headers
#include "xns/containers/aligned_storage.hpp"
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"
#include "xns/type_traits/other/in_place.hpp"

#include "xns/type_traits/supported_operations/is_constructible.hpp"
#include "xns/type_traits/supported_operations/is_destructible.hpp"
#include "xns/type_traits/supported_operations/is_trivially_destructible.hpp"

#include "xns/memory/allocator.hpp"
#include "xns/memory/lifecycle.hpp"

// c++ standard headers library
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	class optional_bad_access final {

		public:

	};


	// -- N U L L O P T -------------------------------------------------------

	struct nullopt { constexpr nullopt(void) = default; };


	// -- O P T I O N A L -----------------------------------------------------

	template <typename T>
	class optional {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::optional<T>;

			/* value type */
			using type = T;

			/* reference type */
			using mut_ref = type&;

			/* move reference type */
			using move_ref = type&&;

			/* const reference type */
			using const_ref = const type&;

			/* const move reference type */
			using const_move_ref = const type&&;


			using ___lifecycle = xns::lifecycle<type>;

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr optional(void) noexcept
			: _storage{}, _active{INACTIVE} {}

			/* nullopt constructor */
			explicit inline constexpr optional(xns::nullopt) noexcept
			: _storage{}, _active{INACTIVE} {}

			/* value copy constructor */
			explicit inline constexpr optional(const_ref value)
			: _storage{}, _active{ACTIVE} {
				// construct value by copy
				___lifecycle::construct(
					xns::ptr<type>(_storage), value
				);
			}

			/* value move constructor */
			explicit inline constexpr optional(move_ref value) noexcept
			: _storage{}, _active{ACTIVE} {
				// construct value by move
				___lifecycle::construct(
					xns::ptr<type>(_storage), xns::move(value)
				);
			}

			/* emplace constructor */
			template <typename... A>
			inline constexpr optional(A&&... args)
			: _storage{}, _active{ACTIVE} {
				// construct value in place
				___lifecycle::construct(
					xns::ptr<type>(_storage), xns::forward<A>(args)...
				);
			}

			/* copy constructor */
			inline constexpr optional(const self& other)
			: _storage{}, _active{other._active} {
				// check state
				switch (_active) {
					case ACTIVE:
						// construct value by copy
						___lifecycle::construct(
							xns::ptr<type>(_storage), xns::ref<type>(other._storage)
						);
					default: break;
				}

			}

			/* move constructor */
			inline constexpr optional(self&& other) noexcept
			: _storage{}, _active{other._active} {
				// check state
				switch (_active) {
					case ACTIVE:
						// construct value by move
						___lifecycle::construct(
							xns::ptr<type>(_storage), xns::move(xns::ref<type>(other._storage))
						);
					default: break;
				}
			}

			/* destructor */
			inline constexpr ~optional(void) noexcept {
				// check state
				switch (_active) {
					case ACTIVE:
						// destroy value
						___lifecycle::destroy(
							xns::ptr<type>(_storage)
						);
					default: break;
				}
			}


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self& other) -> self& = delete;


			/* deleted move assignment operator */
			auto operator=(self&& other) noexcept -> self& = delete;



			// -- public accessors --------------------------------------------

			/* has value */
			constexpr auto has_value(void) const noexcept -> bool {
				return _active == ACTIVE;
			}

			/* get lvalue reference */
			inline constexpr auto value(void) & -> mut_ref {
				return xns::ref<type>(_storage);
			}

			/* get const lvalue reference */
			inline constexpr auto value(void) const & -> const_ref {
				return xns::ref<type>(_storage);
			}

			/* get rvalue reference */
			inline constexpr auto value(void) && -> move_ref {
				return xns::move(xns::ref<type>(_storage));
			}

			/* get const rvalue reference */
			inline constexpr auto value(void) const && -> const_move_ref {
				return xns::move(xns::ref<type>(_storage));
			}


		private:

			// -- private enums -----------------------------------------------

			/* active state */
			enum state : xns::size_t { INACTIVE = 0, ACTIVE = 1 };


			// -- private types -----------------------------------------------

			/* storage type */
			using storage = xns::aligned_storage<sizeof(T), alignof(T)>;

			/* allocator type */
			using allocator = xns::allocator<type>;




			// -- private members ---------------------------------------------

			/* storage */
			self::storage _storage;

			/* is active */
			self::state _active;


	};







	inline void fu() {



		xns::optional<int> o;

		xns::optional<int> o2{xns::nullopt{}};


	}

}

#endif // OPTIONAL_HEADER
