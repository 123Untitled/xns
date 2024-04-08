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

#ifndef XNS_TYPE_MODIFICATIONS_HEADER
#define XNS_TYPE_MODIFICATIONS_HEADER


/* remove_cv */
#include "xns/type_traits/type_modifications/remove_cv.hpp"

/* remove_const */
#include "xns/type_traits/type_modifications/remove_const.hpp"

/* remove_pointer */
#include "xns/type_traits/type_modifications/remove_pointer.hpp"

/* remove_volatile */
#include "xns/type_traits/type_modifications/remove_volatile.hpp"

/* remove_reference */
#include "xns/type_traits/type_modifications/remove_reference.hpp"

/* add_cv */
#include "xns/type_traits/type_modifications/add_cv.hpp"

/* add_const */
#include "xns/type_traits/type_modifications/add_const.hpp"

/* add_pointer */
#include "xns/type_traits/type_modifications/add_pointer.hpp"

/* add_volatile */
#include "xns/type_traits/type_modifications/add_volatile.hpp"

/* add_lvalue_reference */
#include "xns/type_traits/type_modifications/add_lvalue_reference.hpp"

/* add_rvalue_reference */
#include "xns/type_traits/type_modifications/add_rvalue_reference.hpp"

/* make_signed */
#include "xns/type_traits/type_modifications/make_signed.hpp"

/* make_unsigned */
#include "xns/type_traits/type_modifications/make_unsigned.hpp"

/* remove_extent */
#include "xns/type_traits/type_modifications/remove_extent.hpp"

/* remove_all_extents */
#include "xns/type_traits/type_modifications/remove_all_extents.hpp"


#endif // XNS_TYPE_MODIFICATIONS_HEADER
