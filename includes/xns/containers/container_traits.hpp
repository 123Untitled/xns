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

#ifndef XNS_CONTAINERS_TRAITS_HEADER
#define XNS_CONTAINERS_TRAITS_HEADER

#include "xns/type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C O N T A I N E R  T R A I T S --------------------------------------

	/* container traits */
	template <typename ___container>
	class container_traits {


		public:

			// -- public types ------------------------------------------------

			/* container type */
			using container_type         = xns::remove_cvref<___container>;

			/* value type */
			using value_type             = typename ___container::value_type;

			/* reference type */
			using reference              = typename ___container::reference;

			/* const reference type */
			using const_reference        = typename ___container::const_reference;

			/* pointer type */
			using pointer                = typename ___container::pointer;

			/* const pointer type */
			using const_pointer          = typename ___container::const_pointer;

			/* iterator type */
			using iterator               = typename ___container::iterator;

			/* const iterator type */
			using const_iterator         = typename ___container::const_iterator;

			/* reverse iterator type */
			using reverse_iterator       = typename ___container::reverse_iterator;

			/* const reverse iterator type */
			using const_reverse_iterator = typename ___container::const_reverse_iterator;

			/* difference type */
			using difference_type        = typename ___container::difference_type;

			/* size type */
			using size_type              = typename ___container::size_type;


			// -- public static methods ---------------------------------------

			/* size */
			static constexpr auto size(const container_type& container) noexcept -> size_type {
				return container.size();
			}

			/* empty */
			static constexpr auto empty(const container_type& container) noexcept -> bool {
				return container.empty();
			}

			/* begin */
			static constexpr auto begin(container_type& container) noexcept -> iterator {
				return container.begin();
			}

			/* const begin */
			static constexpr auto begin(const container_type& container) noexcept -> const_iterator {
				return container.begin();
			}

			/* end */
			static constexpr auto end(container_type& container) noexcept -> iterator {
				return container.end();
			}

			/* const end */
			static constexpr auto end(const container_type& container) noexcept -> const_iterator {
				return container.end();
			}

			/* cbegin */
			static constexpr auto cbegin(const container_type& container) noexcept -> const_iterator {
				return container.cbegin();
			}

			/* cend */
			static constexpr auto cend(const container_type& container) noexcept -> const_iterator {
				return container.cend();
			}

	};

	/* specialisation for arrays */
	template <typename ___type, xns::size_t ___size>
	class container_traits<___type[___size]> {

		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type             = xns::remove_cvref<___type>;

			/* container type */
			using container_type         = value_type[___size];

			/* reference type */
			using reference              = value_type&;

			/* const reference type */
			using const_reference        = const value_type&;

			/* pointer type */
			using pointer                = value_type*;

			/* const pointer type */
			using const_pointer          = const value_type*;

			/* iterator type */
			using iterator               = pointer;

			/* const iterator type */
			using const_iterator         = const_pointer;

			/* reverse iterator type */
			using reverse_iterator       = pointer;

			/* const reverse iterator type */
			using const_reverse_iterator = const_pointer;

			/* difference type */
			using difference_type        = xns::ptrdiff_t;

			/* size type */
			using size_type              = xns::size_t;


			// -- public static methods ---------------------------------------

			/* size */
			static constexpr auto size(const container_type&) noexcept -> size_type {
				return ___size;
			}

			/* empty */
			static constexpr auto empty(const container_type&) noexcept -> bool {
				return ___size == 0U;
			}

			/* begin */
			static constexpr auto begin(container_type& container) noexcept -> iterator {
				return container;
			}

			/* const begin */
			static constexpr auto begin(const container_type& container) noexcept -> const_iterator {
				return container;
			}

			/* end */
			static constexpr auto end(container_type& container) noexcept -> iterator {
				return container + ___size;
			}

			/* const end */
			static constexpr auto end(const container_type& container) noexcept -> const_iterator {
				return container + ___size;
			}

			/* cbegin */
			static constexpr auto cbegin(const container_type& container) noexcept -> const_iterator {
				return container;
			}

			/* cend */
			static constexpr auto cend(const container_type& container) noexcept -> const_iterator {
				return container + ___size;
			}

	};

	/* have begin */
	template <typename ___type>
	concept have_begin = requires (___type&& ___container) {
		{ xns::container_traits<___type>::begin(___container) } -> xns::same_as<typename xns::container_traits<___type>::iterator>;
	};

	/* have const begin */
	template <typename ___type>
	concept have_const_begin = requires (___type&& ___container) {
		{ xns::container_traits<___type>::begin(___container) } -> xns::same_as<typename xns::container_traits<___type>::const_iterator>;
	};

	/* have end */
	template <typename ___type>
	concept have_end = requires (___type&& ___container) {
		{ xns::container_traits<___type>::end(___container) } -> xns::same_as<typename xns::container_traits<___type>::iterator>;
	};

	/* have const end */
	template <typename ___type>
	concept have_const_end = requires (___type&& ___container) {
		{ xns::container_traits<___type>::end(___container) } -> xns::same_as<typename xns::container_traits<___type>::const_iterator>;
	};

	/* have cbegin */
	template <typename ___type>
	concept have_cbegin = requires (___type&& ___container) {
		{ xns::container_traits<___type>::cbegin(___container) } -> xns::same_as<typename xns::container_traits<___type>::const_iterator>;
	};

	/* have cend */
	template <typename ___type>
	concept have_cend = requires (___type&& ___container) {
		{ xns::container_traits<___type>::cend(___container) } -> xns::same_as<typename xns::container_traits<___type>::const_iterator>;
	};

	/* have size */
	template <typename ___type>
	concept have_size = requires (___type&& ___container) {
		{ xns::container_traits<___type>::size(___container) } -> xns::same_as<typename xns::container_traits<___type>::size_type>;
	};

	/* have empty */
	template <typename ___type>
	concept have_empty = requires (___type&& ___container) {
		{ xns::container_traits<___type>::empty(___container) } -> xns::same_as<bool>;
	};



	/* is container */
	template <typename ___type>
	concept is_container = (xns::have_begin<___type> && (xns::have_const_begin<___type> || xns::have_cbegin<___type>))
						&& (xns::have_end<___type>   && (xns::have_const_end<___type>   || xns::have_cend<___type>))
						&&  xns::have_size<___type>
						&&  xns::have_empty<___type>;


	/* size */
	template <xns::is_container ___container>
	constexpr auto size(const ___container& container) noexcept -> typename xns::container_traits<___container>::size_type {
		return xns::container_traits<___container>::size(container);
	}

	/* empty */
	template <xns::is_container ___container>
	constexpr auto empty(const ___container& container) noexcept -> bool {
		return xns::container_traits<___container>::empty(container);
	}

	/* begin */
	template <xns::is_container ___container>
	constexpr auto begin(___container& container) noexcept -> typename xns::container_traits<___container>::iterator {
		return xns::container_traits<___container>::begin(container);
	}

	/* const begin */
	template <xns::is_container ___container>
	constexpr auto begin(const ___container& container) noexcept -> typename xns::container_traits<___container>::const_iterator {
		return xns::container_traits<___container>::begin(container);
	}

	/* end */
	template <xns::is_container ___container>
	constexpr auto end(___container& container) noexcept -> typename xns::container_traits<___container>::iterator {
		return xns::container_traits<___container>::end(container);
	}

	/* const end */
	template <xns::is_container ___container>
	constexpr auto end(const ___container& container) noexcept -> typename xns::container_traits<___container>::const_iterator {
		return xns::container_traits<___container>::end(container);
	}

	/* cbegin */
	template <xns::is_container ___container>
	constexpr auto cbegin(const ___container& container) noexcept -> typename xns::container_traits<___container>::const_iterator {
		return xns::container_traits<___container>::cbegin(container);
	}

	/* cend */
	template <xns::is_container ___container>
	constexpr auto cend(const ___container& container) noexcept -> typename xns::container_traits<___container>::const_iterator {
		return xns::container_traits<___container>::cend(container);
	}





} // namespace xns

#endif // XNS_CONTAINERS_TRAITS_HEADER
