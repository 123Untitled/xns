#ifndef OS_HEADER
#define OS_HEADER


#if defined(__linux__)
    #define LINUX_OS
	#define XNS_LINUX
#elif defined(__unix__) || (!defined(__APPLE__) && defined(__MACH__))
    #if defined(BSD)
		#define BSD_OS
		#define XNS_BSD
    #endif
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
	#define APPLE_OS
	#define XNS_APPLE
#endif


#endif
