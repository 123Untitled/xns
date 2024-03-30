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

#ifndef XNS_MACROS_HEADER
#define XNS_MACROS_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	#define NON_COPYABLE(_) \
		_(const _&) = delete; \
		_& operator=(const _&) = delete

	#define NON_MOVABLE(_) \
		_(_&&) = delete; \
		_& operator=(_&&) = delete

	#define NON_INSTANCIABLE(_) \
		_(void) = delete; \
		~_(void) = delete; \
		NON_COPYABLE(_); \
		NON_MOVABLE(_)

	#define NON_ASSIGNABLE(_) \
		NON_COPYABLE(_); \
		NON_MOVABLE(_)


	#define XNS_NOT_INSTANTIABLE(_) NON_INSTANCIABLE(_)
	#define XNS_NOT_COPYABLE(_) NON_COPYABLE(_)
	#define XNS_NOT_MOVABLE(_) NON_MOVABLE(_)
	#define XNS_NOT_ASSIGNABLE(_) NON_ASSIGNABLE(_)

	#define ___xns_not_instantiable(_) NON_INSTANCIABLE(_)
	#define ___xns_not_copyable(_)     NON_COPYABLE(_)
	#define ___xns_not_movable(_)      NON_MOVABLE(_)
	#define ___xns_not_assignable(_)   NON_ASSIGNABLE(_)


	#define non_instanciable(obj) NON_INSTANCIABLE(obj)
	#define non_instantiable(obj) NON_INSTANCIABLE(obj)
	#define non_copyable(obj) NON_COPYABLE(obj)
	#define non_movable(obj) NON_MOVABLE(obj)
	#define non_assignable(obj) NON_ASSIGNABLE(obj)

	#define not_instantiable(obj) NON_INSTANCIABLE(obj)

	#define uninstantiable(obj) NON_INSTANCIABLE(obj)
	#define uncopyable(obj) NON_COPYABLE(obj)
	#define unmovable(obj) NON_MOVABLE(obj)
	#define unassignable(obj) NON_ASSIGNABLE(obj)


} // namespace xns

#endif // XNS_MACROS_HEADER
