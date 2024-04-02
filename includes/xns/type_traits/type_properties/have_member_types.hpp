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

#ifndef XNS_HAVE_MEMBER_TYPES_HEADER
#define XNS_HAVE_MEMBER_TYPES_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- H A V E  M E M B E R  T Y P E S -------------------------------------

	/* have pointer */
	template <typename ___type>
	concept have_pointer = requires {
		typename ___type::pointer;
	};

	/* have const_pointer */
	template <typename ___type>
	concept have_const_pointer = requires {
		typename ___type::const_pointer;
	};

	/* have void_pointer */
	template <typename ___type>
	concept have_void_pointer = requires {
		typename ___type::void_pointer;
	};

	/* have const_void_pointer */
	template <typename ___type>
	concept have_const_void_pointer = requires {
		typename ___type::const_void_pointer;
	};

	/* have difference type */
	template <typename ___type>
	concept have_difference_type = requires {
		typename ___type::difference_type;
	};

	/* have size type */
	template <typename ___type>
	concept have_size_type = requires {
		typename ___type::size_type;
	};

	/* have propagate on container copy assignment */
	template <typename ___type>
	concept have_propagate_on_container_copy_assignment = requires {
		typename ___type::propagate_on_container_copy_assignment;
	};

	/* have propagate on container move assignment */
	template <typename ___type>
	concept have_propagate_on_container_move_assignment = requires {
		typename ___type::propagate_on_container_move_assignment;
	};

	/* have propagate on container swap */
	template <typename ___type>
	concept have_propagate_on_container_swap = requires {
		typename ___type::propagate_on_container_swap;
	};

	/* have is always equal */
	template <typename ___type>
	concept have_is_always_equal = requires {
		typename ___type::is_always_equal;
	};

	/* have rebind */
	template <typename ___type>
	concept have_rebind = requires {
		typename ___type::rebind;
	};

} // namespace xns

#endif // XNS_HAVE_MEMBER_TYPES_HEADER
