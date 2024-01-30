/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_SUPPORTED_OPERATIONS_HPP
#define XNS_SUPPORTED_OPERATIONS_HPP


// -- S U P P O R T E D  O P E R A T I O N S ----------------------------------

/* constructible */
#include "is_constructible.hpp"
#include "is_trivially_constructible.hpp"
#include "is_nothrow_constructible.hpp"

/* default constructible */
#include "is_default_constructible.hpp"
#include "is_trivially_default_constructible.hpp"
#include "is_nothrow_default_constructible.hpp"

/* copy constructible */
#include "is_copy_constructible.hpp"
#include "is_trivially_copy_constructible.hpp"
#include "is_nothrow_copy_constructible.hpp"

/* move constructible */
#include "is_move_constructible.hpp"
#include "is_trivially_move_constructible.hpp"
#include "is_nothrow_move_constructible.hpp"

/* assignable */
#include "is_assignable.hpp"
#include "is_trivially_assignable.hpp"
#include "is_nothrow_assignable.hpp"

/* copy assignable */
#include "is_copy_assignable.hpp"
#include "is_trivially_copy_assignable.hpp"
#include "is_nothrow_copy_assignable.hpp"

/* move assignable */
#include "is_move_assignable.hpp"
#include "is_trivially_move_assignable.hpp"
#include "is_nothrow_move_assignable.hpp"

/* destructible */
#include "is_destructible.hpp"
#include "is_trivially_destructible.hpp"
#include "is_nothrow_destructible.hpp"

/* virtual destructor */
//#include "has_virtual_destructor.hpp"

/* swappable */
//#include "is_swappable_with.hpp"
//#include "is_swappable.hpp"
//#include "is_nothrow_swappable_with.hpp"
//#include "is_nothrow_swappable.hpp"

#endif // XNS_SUPPORTED_OPERATIONS_HPP
