#ifndef XNS_CONFIG_HEADER
#define XNS_CONFIG_HEADER

#ifndef __has_builtin
#define __has_builtin(__x) 0
#endif

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


#endif // CONFIG_HEADER
