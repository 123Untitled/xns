#ifndef XNS_REMOVE_HEADER
#define XNS_REMOVE_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- detail --------------------------------------------------------------

	namespace impl {


		// -- remove const ----------------------------------------------------

		/* remove const */
		template <class T>
		struct remove_const                { using type = T; };

		/* remove const specialization */
		template <class T>
		struct remove_const<const T>       { using type = T; };


		// -- remove volatile -------------------------------------------------

		/* remove volatile */
		template <class T>
		struct remove_volatile             { using type = T; };

		/* remove volatile specialization */
		template <class T>
		struct remove_volatile<volatile T> { using type = T; };


		// -- remove reference ------------------------------------------------

		/* remove reference */
		template <class T>
		struct remove_reference            { using type = T; };

		/* remove reference lvalue specialization */
		template <class T>
		struct remove_reference<T&>        { using type = T; };

		/* remove reference rvalue specialization */
		template <class T>
		struct remove_reference<T&&>       { using type = T; };


		// -- remove pointer --------------------------------------------------

		/* remove pointer */
		template <class T>
		struct remove_pointer              { using type = T; };

		/* remove pointer specialization */
		template <class T>
		struct remove_pointer<T*>          { using type = T; };

		/* remove pointer specialization */
		template <class T>
		struct remove_pointer<T* const>    { using type = T; };

		/* remove pointer specialization */
		template <class T>
		struct remove_pointer<T* volatile> { using type = T; };

		/* remove pointer specialization */
		template <class T>
		struct remove_pointer<T* const volatile> { using type = T; };

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


	// -- R E M O V E  P O I N T E R ------------------------------------------

	/* remove pointer */
	template <class T>
	using remove_pointer   = typename impl::remove_pointer<T>::type;


	// -- R E M O V E  C V ----------------------------------------------------

	/* remove cv */
	template <class T>
	using remove_cv        = remove_volatile<remove_const<T>>;


	// -- R E M O V E  C V R --------------------------------------------------

	/* remove cvr */
	template <class T>
	using remove_cvr       = remove_cv<remove_reference<T>>;


	// -- R E M O V E  C V R P ------------------------------------------------

	/* remove cvrp */
	template <class T>
	using remove_cvrp      = remove_pointer<remove_cvr<T>>;


}


#endif
