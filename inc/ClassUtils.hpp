#ifndef CLASSUTILS_HEADER
#define CLASSUTILS_HEADER


#define MOVE(Obj)							\
	static_cast<decltype(Obj)&&>(Obj)


/*template <typename T>
constexpr typename std::remove_reference<T>::type&& my_move(T&& t) noexcept {
  return static_cast<typename std::remove_reference<T>::type&&>(t);
}*/

/*
// remove_reference
template<typename T>
struct removeRef		{ using Type = T; };

template<typename T>
struct removeRef<T&>	{ using Type = T; };

template<typename T>
struct removeRef<T&&>	{ using Type = T; };

template<typename T>
constexpr inline typename removeRef<T>::Type&& MOVE(T&& var) noexcept {
	return static_cast<typename removeRef<T>::Type&&>(var);
}
*/


#endif

