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


	// -- H E L P E R S -------------------------------------------------------

	/* remove const type */
	template <class T>
	using remove_const_t = typename remove_const<T>::type;

	/* remove volatile type */
	template <class T>
	using remove_volatile_t = typename remove_volatile<T>::type;

	/* remove cv type */
	template <class T>
	using remove_cv_t = typename remove_cv<T>::type;


}


#endif
