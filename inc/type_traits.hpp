#ifndef TYPE_TRAITS_HEADER
#define TYPE_TRAITS_HEADER


// -- R E M O V E  R E F E R E N C E ------------------------------------------

/* remove_reference */
template <typename T>
struct remove_reference {
	// alias type to T
	using type = T;
};

/* remove_reference for lvalue reference */
template <typename T>
struct remove_reference<T&> {
	// alias type to T
	using type = T;
};

/* remove_reference for rvalue reference */
template <typename T>
struct remove_reference<T&&> {
	// alias type to T
	using type = T;
};

/* remove_reference for const lvalue reference */
template <typename T>
struct remove_reference<const T&> {
	// alias type to const T
	using type = const T;
};




#endif
