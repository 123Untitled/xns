#ifndef INHERITANCE_HEADER
#define INHERITANCE_HEADER

#include "integral_constant.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E R I V E D  F R O M -----------------------------------------

	template <class D, class B>
	struct is_derived_from {

		private:

			/* base type */
			using Base    = xns::remove_cvr<B>;

			/* derived type */
			using Derived = xns::remove_cvr<D>;


			/* test for derived */
			static consteval auto test(Base*) -> xns::yes;

			/* test for other */
			static consteval auto test(...)   -> xns::no;


		public:

			/* value */
			static constexpr bool value = decltype(test(static_cast<Derived*>(nullptr)))::value;

	};


	// -- I S  B A S E  O F ---------------------------------------------------

	template <class B, class D>
	struct is_base_of : xns::is_derived_from<D, B> {};


	// -- H E L P E R S -------------------------------------------------------

	/* is derived from value */
	template <class D, class B>
	static constexpr bool is_derived_from_v = is_derived_from<D, B>::value;

	/* is base of value */
	template <class B, class D>
	static constexpr bool is_base_of_v = is_base_of<B, D>::value;

	/* is derived from concept */
	template <class D, class B>
	concept is_derived_from_c = is_derived_from_v<D, B>;

	/* is base of concept */
	template <class B, class D>
	concept is_base_of_c = is_base_of_v<B, D>;




}


#endif
