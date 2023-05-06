#ifndef REMOVE_CV_HEADER
#define REMOVE_CV_HEADER


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- R E M O V E  C O N S T ------------------------------------------------

	/* remove const */
	template <class T>
	struct remove_const                { using type = T; };

	/* remove const for const */
	template <class T>
	struct remove_const<const T>       { using type = T; };


	// -- R E M O V E  V O L A T I L E ----------------------------------------

	/* remove volatile */
	template <class T>
	struct remove_volatile             { using type = T; };

	/* remove volatile for volatile */
	template <class T>
	struct remove_volatile<volatile T> { using type = T; };


	// -- R E M O V E  C V ----------------------------------------------------

	/* remove cv */
	template <class T>
	struct remove_cv                   { using type = T; };

	/* remove cv for const */
	template <class T>
	struct remove_cv<const T>          { using type = T; };

	/* remove cv for volatile */
	template <class T>
	struct remove_cv<volatile T>       { using type = T; };

	/* remove cv for const volatile */
	template <class T>
	struct remove_cv<const volatile T> { using type = T; };


	// -- R E M O V E  L E F T  R E F E R E N C E -----------------------------

	/* remove left reference */
	template <class T>
	struct remove_lr                   { using type = T; };

	/* remove left reference for lvalue reference */
	template <class T>
	struct remove_lr<T&>               { using type = T; };


	// -- R E M O V E  R I G H T  R E F E R E N C E ---------------------------

	/* remove right reference */
	template <class T>
	struct remove_rr                   { using type = T; };

	/* remove right reference for rvalue reference */
	template <class T>
	struct remove_rr<T&&>              { using type = T; };


	// -- R E M O V E  R E F E R E N C E --------------------------------------

	/* remove reference */
	template <class T>
	struct remove_reference            { using type = T; };

	/* remove reference for lvalue reference */
	template <class T>
	struct remove_reference<T&>        { using type = T; };

	/* remove reference for rvalue reference */
	template <class T>
	struct remove_reference<T&&>       { using type = T; };


	// -- H E L P E R S  T Y P E S --------------------------------------------

	/* remove const type */
	template <class T>
	using remove_const_t     = typename remove_const<T>::type;

	/* remove volatile type */
	template <class T>
	using remove_volatile_t  = typename remove_volatile<T>::type;

	/* remove cv type */
	template <class T>
	using remove_cv_t        = typename remove_cv<T>::type;

	/* remove left reference type */
	template <class T>
	using remove_lr_t        = typename remove_lr<T>::type;

	/* remove right reference type */
	template <class T>
	using remove_rr_t        = typename remove_rr<T>::type;

	/* remove reference type */
	template <class T>
	using remove_reference_t = typename remove_reference<T>::type;

	/* remove cvr type */
	template <class T>
	using remove_cvr_t       = remove_cv_t<remove_reference_t<T>>;


}


#endif
