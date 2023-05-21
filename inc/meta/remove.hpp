#ifndef REMOVE_CV_HEADER
#define REMOVE_CV_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  C O N S T ------------------------------------------------

	/* remove const */
	template <class T>
	struct _remove_const                { using type = T; };

	/* remove const for const */
	template <class T>
	struct _remove_const<const T>       { using type = T; };


	// -- R E M O V E  V O L A T I L E ----------------------------------------

	/* remove volatile */
	template <class T>
	struct _remove_volatile             { using type = T; };

	/* remove volatile for volatile */
	template <class T>
	struct _remove_volatile<volatile T> { using type = T; };


	// -- R E M O V E  C V ----------------------------------------------------

	/* remove cv */
	template <class T>
	struct _remove_cv                   { using type = T; };

	/* remove cv for const */
	template <class T>
	struct _remove_cv<const T>          { using type = T; };

	/* remove cv for volatile */
	template <class T>
	struct _remove_cv<volatile T>       { using type = T; };

	/* remove cv for const volatile */
	template <class T>
	struct _remove_cv<const volatile T> { using type = T; };


	// -- R E M O V E  L E F T  R E F E R E N C E -----------------------------

	/* remove left reference */
	template <class T>
	struct _remove_left_reference       { using type = T; };

	/* remove left reference for lvalue reference */
	template <class T>
	struct _remove_left_reference<T&>   { using type = T; };


	// -- R E M O V E  R I G H T  R E F E R E N C E ---------------------------

	/* remove right reference */
	template <class T>
	struct _remove_right_reference      { using type = T; };

	/* remove right reference for rvalue reference */
	template <class T>
	struct _remove_right_reference<T&&> { using type = T; };


	// -- R E M O V E  R E F E R E N C E --------------------------------------

	/* remove reference */
	template <class T>
	struct _remove_reference            { using type = T; };

	/* remove reference for lvalue reference */
	template <class T>
	struct _remove_reference<T&>        { using type = T; };

	/* remove reference for rvalue reference */
	template <class T>
	struct _remove_reference<T&&>       { using type = T; };


	// -- H E L P E R S  T Y P E S --------------------------------------------

	/* remove const type */
	template <class T>
	using remove_const                 = typename _remove_const<T>::type;

	/* remove volatile type */
	template <class T>
	using remove_volatile              = typename _remove_volatile<T>::type;

	/* remove left reference type */
	template <class T>
	using remove_left_reference        = typename _remove_left_reference<T>::type;

	/* remove right reference type */
	template <class T>
	using remove_right_reference       = typename _remove_right_reference<T>::type;

	/* remove reference type */
	template <class T>
	using remove_reference             = typename _remove_reference<T>::type;

	/* remove cv type */
	template <class T>
	using remove_cv                    = typename _remove_cv<T>::type;

	/* remove const volatile reference type */
	template <class T>
	using remove_cvr                   = remove_cv<remove_reference<T>>;


}


#endif
