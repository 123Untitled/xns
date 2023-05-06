#ifndef ITERATOR_TRAITS_HEADER
#define ITERATOR_TRAITS_HEADER

#include "conditional.hpp"
#include "types.hpp"
#include "integral_constant.hpp"
#include "is_pointer.hpp"

namespace Xf {

	// -- I T E R A T O R  T A G S --------------------------------------------


	/* unidirectional iterator tag */
	struct Unidirectional_iterator_tag {};

	/* bidirectional iterator tag */
	struct Bidirectional_iterator_tag : public Unidirectional_iterator_tag {};

	/* random access iterator tag */
	struct Random_access_iterator_tag : public Bidirectional_iterator_tag {};


	/* is iterator tag false type */
	template <class T>
	struct is_iterator_tag : public false_t {};

	/* is iterator tag true type */
	template <>
	struct is_iterator_tag<Unidirectional_iterator_tag> : public true_t {};

	/* is iterator tag true type */
	template <>
	struct is_iterator_tag<Bidirectional_iterator_tag> : public true_t {};

	/* is iterator tag true type */
	template <>
	struct is_iterator_tag<Random_access_iterator_tag> : public true_t {};





	// -- I T E R A T O R  T R A I T S ----------------------------------------

	/* iterator traits */
	template <class T>
	struct IteratorTraits {

		// -- A L I A S E S ---------------------------------------------------

		/* iterator category */
		using Category  = typename T::Category;

		/* value type */
		using Value     = typename T::Value;

		/* difference type */
		using Diff      = typename T::Diff;

		/* pointer type */
		using Pointer   = Xf::conditional_t<Xf::is_pointer<T>::value, T*, typename T::Pointer>;

		/* reference type */
		using Reference = Xf::conditional_t<Xf::is_pointer<T>::value, T&, typename T::Reference>;

	};


	// -- I T E R A T O R -----------------------------------------------------

	/* iterator */
	template <class T, class Category>
	class Iterator {};



}



#endif
