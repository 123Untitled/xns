//#pragma once

#ifndef XNS_CONFIG_HEADER
#define XNS_CONFIG_HEADER

#ifndef __has_builtin
#define __has_builtin(__x) 0
#endif


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


#if defined(__SIZEOF_INT128__)
#	define XNS_128BIT_INTEGERS
#endif



#endif // CONFIG_HEADER
