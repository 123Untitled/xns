#ifndef INHERITANCE_HEADER
#define INHERITANCE_HEADER

#include "integral_constant.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {

		template <class D, class B>
		struct is_derived_from {

			private:

				/* base type */
				using base    = xns::remove_cvr<B>;

				/* derived type */
				using derived = xns::remove_cvr<D>;


				/* test for derived */ // INFO: constevel doesn't compile on linux
				static constexpr auto test(base*) -> xns::yes;

				/* test for other */ // INFO: constevel doesn't compile on linux
				static constexpr auto test(...)   -> xns::no;


			public:

				/* value */
				static constexpr bool value = decltype(test(static_cast<derived*>(nullptr)))::value;

		};

	}


	// -- H E L P E R S -------------------------------------------------------


	/* is derived from concept */
	template <class D, class B>
	concept is_derived_from = impl::is_derived_from<D, B>::value;

	/* is base of concept */
	template <class B, class D>
	concept is_base_of = impl::is_derived_from<D, B>::value;





}


#endif
