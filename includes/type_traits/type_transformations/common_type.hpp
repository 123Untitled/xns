#ifndef XNS_COMMON_TYPE_HEADER
#define XNS_COMMON_TYPE_HEADER

//#include <type_traits>

#include "remove.hpp"
#include "is_same.hpp"

#include <type_traits>

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C O M M O N  T Y P E ------------------------------------------------


	namespace __impl {

		/* common type */
		template <typename T, typename... R>
		struct common_type {
			// remove reference of T
			using type = xns::remove_cvr<T>;
			// check if all types are the same
			static_assert((xns::is_same<type, xns::remove_cvr<R>> && ...),
						  "): ALL TYPES MUST BE THE SAME :(");
		};

		/* common type (specialization for one type) */
		template <class T>
		struct common_type<T> final {
			// remove reference of T
			using type = xns::remove_reference<T>;
		};

	}

	template <typename... T>
	using common_type = std::common_type_t<T...>;
	//using common_type = typename __impl::common_type<T...>::type;


}




//
//
//
//
//
//
//	// cpp reference implementation
//
//
//	// primary template (used for zero types)
//template<class...>
//struct common_type {};
// 
//// one type
//template<class T>
//struct common_type<T> : common_type<T, T> {};
// 
//namespace detail
//{
//    template<class...>
//    using void_t = void;
// 
//    template<class T1, class T2>
//    using conditional_result_t = decltype(false ? std::declval<T1>() : std::declval<T2>());
// 
//    template<class, class, class = void>
//    struct decay_conditional_result {};
//    template<class T1, class T2>
//    struct decay_conditional_result<T1, T2, void_t<conditional_result_t<T1, T2>>>
//        : std::decay<conditional_result_t<T1, T2>> {};
// 
//    template<class T1, class T2, class = void>
//    struct common_type_2_impl : decay_conditional_result<const T1&, const T2&> {};
// 
//    // C++11 implementation:
//    // template<class, class, class = void>
//    // struct common_type_2_impl {};
// 
//    template<class T1, class T2>
//    struct common_type_2_impl<T1, T2, void_t<conditional_result_t<T1, T2>>>
//        : decay_conditional_result<T1, T2> {};
//}
// 
//// two types
//template<class T1, class T2>
//struct common_type<T1, T2> 
//    : std::conditional<std::is_same<T1, typename std::decay<T1>::type>::value &&
//                       std::is_same<T2, typename std::decay<T2>::type>::value,
//                       detail::common_type_2_impl<T1, T2>,
//                       common_type<typename std::decay<T1>::type,
//                                   typename std::decay<T2>::type>>::type {};
// 
//// 3+ types
//namespace detail
//{
//    template<class AlwaysVoid, class T1, class T2, class... R>
//    struct common_type_multi_impl {};
//    template<class T1, class T2, class...R>
//    struct common_type_multi_impl<void_t<typename common_type<T1, T2>::type>, T1, T2, R...>
//        : common_type<typename common_type<T1, T2>::type, R...> {};
//}
// 
//template<class T1, class T2, class... R>
//struct common_type<T1, T2, R...>
//    : detail::common_type_multi_impl<void, T1, T2, R...> {};
//
//}
//
//
//
//
//
//
//
//
//
//
//
//// llvm implementation
//
//
//#if _LIBCPP_STD_VER >= 20
//
//// Let COND_RES(X, Y) be:
//template <class _Tp, class _Up>
//using __cond_type = decltype(false ? std::declval<_Tp>() : std::declval<_Up>());
//
//template <class _Tp, class _Up, class = void>
//struct __common_type3 {
//};
//
//// sub-bullet 4 - "if COND_RES(CREF(D1), CREF(D2)) denotes a type..."
//template <class _Tp, class _Up>
//struct __common_type3<_Tp, _Up, void_t<__cond_type<const _Tp&, const _Up&>>> {
//	using type = remove_cvref_t<__cond_type<const _Tp&, const _Up&>>;
//};
//
//template <class _Tp, class _Up, class = void>
//struct __common_type2_imp : __common_type3<_Tp, _Up> {
//};
//
//#else
//
//template <class _Tp, class _Up, class = void>
//struct __common_type2_imp {
//};
//
//#endif
//
//// sub-bullet 3 - "if decay_t<decltype(false ? declval<D1>() : declval<D2>())> ..."
//template <class _Tp, class _Up>
//struct __common_type2_imp<_Tp, _Up, __void_t<decltype(true ? std::declval<_Tp>() : std::declval<_Up>())> > {
//	typedef __decay_t<decltype(true ? std::declval<_Tp>() : std::declval<_Up>())> type;
//};
//
//template <class, class = void>
//struct __common_type_impl {
//};
//
//template <class... _Tp>
//struct __common_types;
//template <class... _Tp>
//struct _LIBCPP_TEMPLATE_VIS common_type;
//
//template <class _Tp, class _Up>
//struct __common_type_impl< __common_types<_Tp, _Up>, __void_t<typename common_type<_Tp, _Up>::type> > {
//  typedef typename common_type<_Tp, _Up>::type type;
//};
//
//template <class _Tp, class _Up, class _Vp, class... _Rest>
//struct __common_type_impl<__common_types<_Tp, _Up, _Vp, _Rest...>, __void_t<typename common_type<_Tp, _Up>::type> >
//    : __common_type_impl<__common_types<typename common_type<_Tp, _Up>::type, _Vp, _Rest...> > {};
//
//// bullet 1 - sizeof...(Tp) == 0
//
//template <>
//struct common_type<> {
//};
//
//// bullet 2 - sizeof...(Tp) == 1
//
//template <class _Tp>
//struct common_type<_Tp> : public common_type<_Tp, _Tp> {
//};
//
//// bullet 3 - sizeof...(Tp) == 2
//
//// sub-bullet 1 - "If is_same_v<T1, D1> is false or ..."
//template <class _Tp, class _Up>
//struct common_type<_Tp, _Up> : conditional<_IsSame<_Tp, __decay_t<_Tp> >::value && _IsSame<_Up, __decay_t<_Up> >::value,
//                  __common_type2_imp<_Tp, _Up>,
//                  common_type<__decay_t<_Tp>, __decay_t<_Up> > >::type {};
//
//// bullet 4 - sizeof...(Tp) > 2
//
//template <class _Tp, class _Up, class _Vp, class... _Rest>
//struct common_type<_Tp, _Up, _Vp, _Rest...>
//: __common_type_impl<__common_types<_Tp, _Up, _Vp, _Rest...> > {
//};
//
//
//
//
//template <class... _Tp>
//using common_type_t = typename common_type<_Tp...>::type;
//
//
//








#endif
