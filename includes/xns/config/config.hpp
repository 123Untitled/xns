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

#ifndef XNS_CONFIG_HEADER
#define XNS_CONFIG_HEADER


// -- check for c++ language --------------------------------------------------

#ifdef __cplusplus


// -- cxx version -------------------------------------------------------------

/* cxx version */
#ifndef ___xns_cxx_version

#	if   __cplusplus <= 199711L
#		define ___xns_cxx_version 98

#	elif __cplusplus <= 201103L
#		define ___xns_cxx_version 11

#	elif __cplusplus <= 201402L
#		define ___xns_cxx_version 14

#	elif __cplusplus <= 201703L
#		define ___xns_cxx_version 17

#	elif __cplusplus <= 202002L
#		define ___xns_cxx_version 20

#	elif __cplusplus <= 202302L
#		define ___xns_cxx_version 23

#	else
#		define ___xns_cxx_version 26
#	endif
#endif // ___xns_cxx_version



// -- has builtin -------------------------------------------------------------

#ifndef XNS_HAS_BUILTIN
#	ifndef __has_builtin
#		define XNS_HAS_BUILTIN(x) 0
#	else
#		define XNS_HAS_BUILTIN(x) __has_builtin(x)
#	endif
#endif

#ifndef ___xns_has_builtin
#	ifndef __has_builtin
#		define ___xns_has_builtin(x) 0
#	else
#		define ___xns_has_builtin(x) __has_builtin(x)
#	endif
#endif


// -- endian ------------------------------------------------------------------

#ifdef __LITTLE_ENDIAN__
#	if __LITTLE_ENDIAN__
#		define XNS_LITTLE_ENDIAN
#	endif
#endif // __LITTLE_ENDIAN__

#ifdef __BIG_ENDIAN__
#	if __BIG_ENDIAN__
#		define XNS_BIG_ENDIAN
#	endif
#endif // __BIG_ENDIAN__

#ifdef __BYTE_ORDER__
#	if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#		define XNS_LITTLE_ENDIAN
#	elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#		define XNS_BIG_ENDIAN
#	endif
#endif // __BYTE_ORDER__

#if !defined(XNS_LITTLE_ENDIAN) && !defined(XNS_BIG_ENDIAN)
#	error "unknown endian"
	static_assert(false, "unknown endian");
#endif



// -- integer sizes -----------------------------------------------------------

// check for 128-bit integers
#if defined(__SIZEOF_INT128__)
#	define XNS_128BIT_INTEGERS
#endif

// check for 32-bit / 64-bit integers
#if defined(__i386__) || defined(__arm__)
#	define XNS_32BIT_INTEGERS
#elif defined(__x86_64__) || defined(__ppc64__) || defined(__aarch64__)
#	define XNS_64BIT_INTEGERS
#endif



// -- exceptions --------------------------------------------------------------

/* check if exceptions are enabled */
#if defined(__cpp_exceptions) || defined(__EXCEPTIONS)

	/* exceptions enabled */
	#define XNS_HAS_NOEXCEPT false
	#define XNS_HAS_EXCEPTIONS true
	#define XNS_NOEXCEPT(__cond) noexcept(__cond)

	#define __XNS_THROW(__exception) throw __exception
	#define __XNS_TRY try
	#define __XNS_CATCH(__exception) catch (__exception)

#	define ___xns_throw(___e) throw ___e
#	define ___xns_try try
#	define ___xns_catch(___e) catch (___e)

	namespace xns {
		/* for template programming */
		enum : bool {
			has_noexcept = false
		};
	}

	#define ___xns_noexcept(___expr) noexcept(___expr)

#else

	/* exceptions disabled */
	#define XNS_HAS_NOEXCEPT true
	#define XNS_HAS_EXCEPTIONS false
	#define XNS_NOEXCEPT(__cond) noexcept
	#define __XNS_THROW(__exception)
	#define __XNS_TRY
	#define __XNS_CATCH(__exception)

#	define ___xns_throw()
#	define ___xns_try
#	define ___xns_catch()

	namespace xns {
		/* for template programming */
		enum : bool {
			has_noexcept = true
		};
	}

	#define ___xns_noexcept() noexcept(true)

#endif


// -- compiler ----------------------------------------------------------------

// check for clang
#if defined(__clang__)
#	define XNS_CLANG
#endif

// check for gcc
#if defined(__GNUC__)
#	define XNS_GCC
#endif


// -- if consteval ------------------------------------------------------------






// check for cxx version
#if ___xns_cxx_version >= 23
#	define ___xns_if_consteval if consteval
#else
#	if ___xns_has_builtin(__builtin_is_constant_evaluated)
#		define ___xns_if_consteval if (__builtin_is_constant_evaluated())
#	else
#		error "compiler does not support __builtin_is_constant_evaluated"
#	endif
#endif


#endif // __cplusplus

#endif // XNS_CONFIG_HEADER
