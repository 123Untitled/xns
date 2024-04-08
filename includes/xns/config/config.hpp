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


#ifndef XNS_CPP_VERSION
#	if __cplusplus <= 201103L
#		define XNS_CPP_VERSION 11
#	elif __cplusplus <= 201402L
#		define XNS_CPP_VERSION 14
#	elif __cplusplus <= 201703L
#		define XNS_CPP_VERSION 17
#	elif __cplusplus <= 202002L
#		define XNS_CPP_VERSION 20
#	elif __cplusplus <= 202302L
#		define XNS_CPP_VERSION 23
#	else
#		define _LIBCPP_STD_VER 26
#	endif
#endif // XNS_CPP_VERSION

// check if __always_inline__
#if not defined(XNS_FORCE_INLINE)
	#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
		#define XNS_FORCE_INLINE __attribute__((__always_inline__))
	#elif defined(_MSC_VER)
		#define XNS_FORCE_INLINE __forceinline
	#else
		#define XNS_FORCE_INLINE inline
	#endif
#endif

// check for 'has_builtin'
#if not defined(XNS_HAS_BUILTIN)
#	if not defined(__has_builtin)
#		define XNS_HAS_BUILTIN(x) 0
#	else
#		define XNS_HAS_BUILTIN(x) __has_builtin(x)
#	endif
#endif


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



/* check if exceptions are enabled */
#if defined(__cpp_exceptions) || defined(__EXCEPTIONS)

	/* exceptions enabled */
	#define XNS_HAS_NOEXCEPT false
	#define XNS_NOEXCEPT(__cond) noexcept(__cond)
	#define __XNS_THROW(__exception) throw __exception
	#define __XNS_TRY try
	#define __XNS_CATCH(__exception) catch (__exception)

	namespace xns {
		/* for template programming */
		enum : bool {
			has_noexcept = false
		};
	}

#else

	/* exceptions disabled */
	#define XNS_HAS_NOEXCEPT true
	#define XNS_NOEXCEPT(__cond) noexcept
	#define __XNS_THROW(__exception)
	#define __XNS_TRY
	#define __XNS_CATCH(__exception)

	namespace xns {
		/* for template programming */
		enum : bool {
			has_noexcept = true
		};
	}

#endif


// check for clang
#if defined(__clang__)
#	define XNS_CLANG
#endif

// check for gcc
#if defined(__GNUC__)
#	define XNS_GCC
#endif


#endif // CONFIG_HEADER
