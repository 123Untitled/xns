#ifndef REMOVE_CV_HEADER
#define REMOVE_CV_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {


		// -- R E M O V E  C O N S T ------------------------------------------

		/* remove const */
		template <class T>
		struct remove_const                { using type = T; };

		/* remove const specialization */
		template <class T>
		struct remove_const<const T>       { using type = T; };


		// -- R E M O V E  V O L A T I L E ------------------------------------

		/* remove volatile */
		template <class T>
		struct remove_volatile             { using type = T; };

		/* remove volatile specialization */
		template <class T>
		struct remove_volatile<volatile T> { using type = T; };


		// -- R E M O V E  R E F E R E N C E ----------------------------------

		/* remove reference */
		template <class T>
		struct remove_reference            { using type = T; };

		/* remove reference lvalue specialization */
		template <class T>
		struct remove_reference<T&>        { using type = T; };

		/* remove reference rvalue specialization */
		template <class T>
		struct remove_reference<T&&>       { using type = T; };

	}


	// -- R E M O V E  C O N S T ----------------------------------------------

	/* remove const */
	template <class T>
	using remove_const     = typename impl::remove_const<T>::type;


	// -- R E M O V E  V O L A T I L E ----------------------------------------

	/* remove volatile */
	template <class T>
	using remove_volatile  = typename impl::remove_volatile<T>::type;


	// -- R E M O V E  R E F E R E N C E --------------------------------------

	/* remove reference */
	template <class T>
	using remove_reference = typename impl::remove_reference<T>::type;


	// -- R E M O V E  C V ----------------------------------------------------

	/* remove cv */
	template <class T>
	using remove_cv        = remove_volatile<remove_const<T>>;


	// -- R E M O V E  C V R --------------------------------------------------

	/* remove cvr */
	template <class T>
	using remove_cvr       = remove_cv<remove_reference<T>>;


}


#endif
