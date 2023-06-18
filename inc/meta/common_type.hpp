#ifndef COMMON_TYPE_HEADER
#define COMMON_TYPE_HEADER

//#include <type_traits>

#include "remove.hpp"
#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C O M M O N  T Y P E ------------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* common type */
		template <class T, class... R>
		struct common_type {
			// remove reference of T
			using type = xns::remove_reference<T>;
			// check if all types are the same
			static_assert((xns::is_same<type, xns::remove_reference<R>> && ...),
						  "): ALL TYPES MUST BE THE SAME :(");
		};

		/* common type (specialization for one type) */
		template <class T>
		struct common_type<T> final {
			// remove reference of T
			using type = xns::remove_reference<T>;
		};

	}

	template <class... T>
	using common_type = typename impl::common_type<T...>::type;



	/*
	// primary template (used for zero types)
	template<class...>
		struct common_type {};

	//////// one type
	template <class T>
		struct common_type<T> : common_type<T, T> {};

	namespace detail {
		template<class...>
			using void_t = void;

		template<class T1, class T2>
			using conditional_result_t = decltype(false ? std::declval<T1>() : std::declval<T2>());

		template<class, class, class = void>
			struct decay_conditional_result {};
		template<class T1, class T2>
			struct decay_conditional_result<T1, T2, void_t<conditional_result_t<T1, T2>>>
			: std::decay<conditional_result_t<T1, T2>> {};

		template<class T1, class T2, class = void>
			struct common_type_2_impl : decay_conditional_result<const T1&, const T2&> {};

		// C++11 implementation:
		// template<class, class, class = void>
		// struct common_type_2_impl {};

		template<class T1, class T2>
			struct common_type_2_impl<T1, T2, void_t<conditional_result_t<T1, T2>>>
			: decay_conditional_result<T1, T2> {};
	}

	//////// two types
	template<class T1, class T2>
		struct common_type<T1, T2>
		: std::conditional<std::is_same<T1, typename std::decay<T1>::type>::value &&
		std::is_same<T2, typename std::decay<T2>::type>::value,
		detail::common_type_2_impl<T1, T2>,
		common_type<typename std::decay<T1>::type,
		typename std::decay<T2>::type>>::type {};

	//////// 3+ types
	namespace detail {
		template<class AlwaysVoid, class T1, class T2, class...R>
			struct common_type_multi_impl {};
		template<class T1, class T2, class...R>
			struct common_type_multi_impl<void_t<typename common_type<T1, T2>::type>, T1, T2, R...>
			: common_type<typename common_type<T1, T2>::type, R...> {};
	}

	template<class T1, class T2, class... R>
		struct common_type<T1, T2, R...>
		: detail::common_type_multi_impl<void, T1, T2, R...> {};


	template< class... T >
		using common_type_t = typename common_type<T...>::type;
		*/

}

#endif
