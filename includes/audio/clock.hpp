#ifndef XNS_AUDIO_CLOCK_HPP
#define XNS_AUDIO_CLOCK_HPP

#include "os.hpp"

#if defined(XNS_APPLE)

#include <coreaudio/coreaudio.h>
#include <AudioToolbox/AudioToolbox.h>


// create a high precision clock using audio callbacks

namespace xns {



	class clock final {


		public:

			clock(void) noexcept {

			}


		private:

			:: AudioDeviceID _device;

	};

}


#endif // XNS_APPLE

#endif // XNS_AUDIO_CLOCK_HPP
