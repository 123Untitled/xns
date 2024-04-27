/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_ITERATOR_TRAITS_HEADER
#define XNS_ITERATOR_TRAITS_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/other/is_one_of.hpp"
#include "xns/type_traits/type_categories/is_object.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I T E R A T O R  T A G S --------------------------------------------

	/* input iterator tag */
	struct input_iterator_tag {};

	/* output iterator tag */
	struct output_iterator_tag {};

	/* forward iterator tag */
	struct forward_iterator_tag : public input_iterator_tag {};

	/* bidirectional iterator tag */
	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	/* random access iterator tag */
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/* contiguous iterator tag */
	struct contiguous_iterator_tag : public random_access_iterator_tag {};


	template <typename ___type>
	concept input_iterator = xns::is_same<___type, xns::input_iterator_tag>;

	template <typename ___type>
	concept forward_iterator = xns::is_same<___type, xns::forward_iterator_tag>;

	template <typename ___type>
	concept bidirectional_iterator = xns::is_same<___type, xns::bidirectional_iterator_tag>;

	template <typename ___type>
	concept random_access_iterator = xns::is_same<___type, xns::random_access_iterator_tag>;

	template <typename ___type>
	concept contiguous_iterator = xns::is_same<___type, xns::contiguous_iterator_tag>;





	// -- I T E R A T O R  T R A I T S ----------------------------------------

	template <typename ___type>
	struct iterator_traits {


		// -- types -----------------------------------------------------------

		/* difference type */
		using difference_type   = typename ___type::difference_type;

		/* value type */
		using value_type        = typename ___type::value_type;

		/* pointer type */
		using pointer           = typename ___type::pointer;

		/* reference type */
		using reference         = typename ___type::reference;

		/* iterator category */
		using iterator_category = typename ___type::iterator_category;

	}; // struct iterator_traits


	/* pointer specialization */
	template <typename ___type> requires xns::is_object<___type>
	struct iterator_traits<___type*> {

		/* difference type */
		using difference_type   = xns::ptrdiff_t;

		/* value type */
		using value_type        = xns::remove_cv<___type>;

		/* pointer type */
		using pointer           = ___type*;

		/* reference type */
		using reference         = ___type&;

		/* iterator category */
		using iterator_category = xns::random_access_iterator_tag;

	}; // struct iterator_traits

} // namespace xns

#endif // XNS_ITERATOR_TRAITS_HEADER
