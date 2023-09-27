#ifndef OS_HEADER
#define OS_HEADER


// -- operating system check --------------------------------------------------

/* linux */
#if defined(__linux__)
	#define XNS_LINUX
/* bsd */
#elif defined(__unix__) || (!defined(__APPLE__) && defined(__MACH__))
	#if defined(BSD)
		#define XNS_BSD
	#endif
/* apple */
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
	#define XNS_APPLE
#endif


// -- architecture check ------------------------------------------------------

/* x86_64 */
#if defined(__x86_64__) || defined(_M_X64)
	#define XNS_X86_64
/* arm64 */
#elif defined(__aarch64__)
	#define XNS_ARM64
#endif


#endif // OS_HEADER
