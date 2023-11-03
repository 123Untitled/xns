#ifndef XNS_MIDI_PLATEFORM_HPP
#define XNS_MIDI_PLATEFORM_HPP

#include "os.hpp"
#include "is_same.hpp"

// preprocessor check for operating system
#if defined(XNS_APPLE)

	#include <CoreMIDI/CoreMIDI.h>
	#include <CoreFoundation/CoreFoundation.h>
	#include <mach/mach_time.h>

#elif defined(XNS_LINUX)

	//#warning "linux is not implemented yet"

#elif defined(_WIN32) || defined(_WIN64)

	#error "windows is not implemented yet"
 	#include <windows.h>

#endif

/* macosx midi */
struct core_midi {};

/* linux midi */
struct alsa_midi {};

/* windows midi */
struct win_midi {};

/* is midi */
template <class T>
concept is_midi =  xns::is_same<T, core_midi>
				|| xns::is_same<T, alsa_midi>
				|| xns::is_same<T, win_midi>;


template <class T>
class interface;



#endif
