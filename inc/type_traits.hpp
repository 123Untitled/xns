#ifndef TYPE_TRAITS_HEADER
#define TYPE_TRAITS_HEADER

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- R E M O V E  R E F E R E N C E --------------------------------------

	/* remove reference */
	template <typename T>
	struct remove_reference {
		// alias type to T
		using type = T;
	};

	/* remove reference for lvalue reference */
	template <typename T>
	struct remove_reference<T&> {
		// alias type to T
		using type = T;
	};

	/* remove reference for rvalue reference */
	template <typename T>
	struct remove_reference<T&&> {
		// alias type to T
		using type = T;
	};

	/* remove reference for const lvalue reference */
	template <typename T>
	struct remove_reference<const T&> {
		// alias type to const T
		using type = const T;
	};


	// -- E N A B L E  I F ----------------------------------------------------

	/* enable if */
	template <bool B, typename T = void>
	struct enable_if { /* empty */ };

	/* enable if for true */
	template <typename T>
	struct enable_if<true, T> {
		// alias type to T
		using type = T;
	};

	/* enable if for false */
	template <typename T>
	struct enable_if<false, T> { /* empty */ };






	// -- I S  S A M E --------------------------------------------------------

	/* is same */
	template <typename T, typename U>
	struct is_same {
		// alias value to false
		static constexpr bool value = false;
	};

	/* is same for same types */
	template <typename T>
	struct is_same<T, T> {
		// alias value to true
		static constexpr bool value = true;
	};


	// -- A L L  O F ----------------------------------------------------------

	/* all of */
	template <bool...>
	struct all_of {
		// alias value to true
		static constexpr bool value = true;
	};

	/* all of for false */
	template <bool B, bool... Bs>
	struct all_of<B, Bs...> {
		// alias value to false
		static constexpr bool value = false;
	};

	/* all of for true */
	template <bool... Bs>
	struct all_of<true, Bs...> {
		// alias value to all of Bs
		static constexpr bool value = all_of<Bs...>::value;
	};




} // end of namespace Xf







#endif
