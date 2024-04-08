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

#ifndef XNS_TYPE_CATEGORIES_HEADER
#define XNS_TYPE_CATEGORIES_HEADER

// is_void
// is_null_pointer
// is_array
// is_pointer
// is_enum
// is_union
// is_class
// is_function
// is_object
// is_scalar
// is_compound
// is_integral
// is_floating_point
// is_fundamental
// is_arithmetic
// is_reference
// is_lvalue_reference
// is_rvalue_reference
// is_member_pointer
// is_member_object_pointer
// is_member_function_pointer

#include "xns/type_traits/type_categories/is_void.hpp"
#include "xns/type_traits/type_categories/is_null_pointer.hpp"
#include "xns/type_traits/type_categories/is_array.hpp"
#include "xns/type_traits/type_categories/is_pointer.hpp"
#include "xns/type_traits/type_categories/is_enum.hpp"
#include "xns/type_traits/type_categories/is_union.hpp"
#include "xns/type_traits/type_categories/is_class.hpp"
#include "xns/type_traits/type_categories/is_function.hpp"
//#include "xns/type_traits/type_categories/is_object.hpp"
#include "xns/type_traits/type_categories/is_scalar.hpp"
//#include "xns/type_traits/type_categories/is_compound.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_categories/is_floating_point.hpp"
#include "xns/type_traits/type_categories/is_fundamental.hpp"
#include "xns/type_traits/type_categories/is_arithmetic.hpp"
#include "xns/type_traits/type_categories/is_reference.hpp"
#include "xns/type_traits/type_categories/is_lvalue_reference.hpp"
#include "xns/type_traits/type_categories/is_rvalue_reference.hpp"
#include "xns/type_traits/type_categories/is_member_pointer.hpp"
//#include "xns/type_traits/type_categories/is_member_object_pointer.hpp"
//#include "xns/type_traits/type_categories/is_member_function_pointer.hpp"

#endif // XNS_TYPE_CATEGORIES_HEADER
