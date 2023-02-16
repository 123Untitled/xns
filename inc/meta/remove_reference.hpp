#ifndef REMOVE_REFERENCE_HEADER
#define REMOVE_REFERENCE_HEADER

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- R E M O V E  R E F E R E N C E ----------------------------------------

	/* remove reference */
	template <class T>
	struct remove_reference { using type = T; };

	/* remove reference for lvalue reference */
	template <class T>
	struct remove_reference<T&> { using type = T; };

	/* remove reference for rvalue reference */
	template <class T>
	struct remove_reference<T&&> { using type = T; };

	/* remove reference type */
	template <class T>
	using remove_reference_t = typename remove_reference<T>::type;


	/* remove reference for const lvalue reference */ // INFO: ???
	//template <typename T>
	//struct remove_reference<const T&> {
	//	// alias type to const T
	//	using type = const T;
	//};


}

#endif
