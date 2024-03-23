#ifndef XNS_ITERATOR_TRAITS_HEADER
#define XNS_ITERATOR_TRAITS_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/type_traits/type_categories/is_pointer.hpp"
#include "xns/type_traits/other/is_one_of.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I T E R A T O R  T A G S --------------------------------------------


	/* unidirectional iterator tag */
	struct unidirectional_iterator_tag {};

	/* bidirectional iterator tag */
	struct bidirectional_iterator_tag : public unidirectional_iterator_tag {};

	/* random access iterator tag */
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	/* is iterator tag */
	template <class T>
	concept is_iterator_tag = xns::is_one_of<T,
							  unidirectional_iterator_tag,
							  bidirectional_iterator_tag,
							  random_access_iterator_tag>;


	// -- I T E R A T O R  T R A I T S ----------------------------------------

	/* iterator traits */
	template <class T>
	struct iterator_traits {


		// -- types -----------------------------------------------------------

		/* iterator category */
		using tag        = typename T::tag;

		/* value type */
		using value_type = typename T::value_type;

		/* difference type */
		using diff_type  = typename T::diff_type;

		/* pointer type */
		using pointer    = xns::conditional<xns::is_pointer<T>,
										    T*,
										    typename T::pointer>;

		/* reference type */
		using reference  = xns::conditional<xns::is_pointer<T>,
										    T&,
										    typename T::reference>;

	};


	// -- I T E R A T O R -----------------------------------------------------

	/* iterator */
	template <class T, class tag>
	class iterator {};



}



#endif
