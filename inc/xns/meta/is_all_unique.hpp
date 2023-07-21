#ifndef IS_ALL_UNIQUE_HEADER
#define IS_ALL_UNIQUE_HEADER

#include "integral_constant.hpp"
#include "is_one_of.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L L  D I F F E R E N T --------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {


		/* is all unique */
		template <class...>
		struct is_all_unique;

		/* is all unique specialization */
		template <class T, class... A>
		struct is_all_unique<T, A...> : public xns::bool_constant<
		(!xns::is_one_of<T, A...> && (is_all_unique<A...>::value)) > {};

		/* end of recursion */
		template <class T>
		struct is_all_unique<T> : public xns::yes {};

	}


	/* is all unique concept */
	template <class... A>
	concept is_all_unique = impl::is_all_unique<A...>::value;


	// -- U N I Q U E  T Y P E S ----------------------------------------------

	/* unique types */
	template <class... A>
	struct unique_types {

		// -- assertions -------------------------------------------------------
		static_assert(is_all_unique<A...>, "): TYPES MUST BE UNIQUE :(");
	};


}

#endif
