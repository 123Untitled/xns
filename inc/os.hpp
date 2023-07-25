#ifndef OS_HEADER
#define OS_HEADER


#if defined(__linux__)
    #define LINUX_OS
#elif defined(__unix__) || (!defined(__APPLE__) && defined(__MACH__))
    #if defined(BSD)
		#define BSD_OS
    #endif
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
	#define APPLE_OS
#endif


#endif
