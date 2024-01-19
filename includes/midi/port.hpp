#ifndef XNS_MIDI_PORT_HPP
#define XNS_MIDI_PORT_HPP


#include "macros.hpp"
#include "string.hpp"
#include "platform.hpp"

#include <iostream>

#include "midi/client.hpp"
#include "midi/source.hpp"


#if defined(XNS_APPLE)

namespace midi {




	class port final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = midi::port;

			
			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline port(void) noexcept
			: _port{0} {
			}

			/* client constructor */
			inline port(const midi::client& client)
			: _port{0} {

				OSStatus status = ::MIDIInputPortCreateWithProtocol(client.get(),
																	CFSTR("MIDI port"),
																	kMIDIProtocol_1_0,
																	&_port,
																	^(const MIDIEventList* evtlist, void* data) {
																		self::read_midi(evtlist, data);
																	});

				if (status != noErr) {
					std::cerr << "error creating midi input port: " << status << std::endl;
					return;
				}
				std::cout << "created midi input port" << std::endl;

			}

			/* destructor */
			inline ~port(void) noexcept {

				if (_port == 0) { return; }

				OSStatus status = ::MIDIPortDispose(_port);

				if (status != noErr) {
					std::cerr << "error disposing midi port: " << status << std::endl;
				}
				else {
					std::cout << "disposed midi port" << std::endl;
				}

			}


			template <xns::basic_string_literal type>
			inline auto connect(const midi::endpoint<type>& source) -> void {

				if (_port == 0 || source.get() == 0) { return; }

				OSStatus status = ::MIDIPortConnectSource(_port, source.get(), nullptr);

				if (status != noErr) {
					std::cerr << "error connecting midi source to port: " << status << std::endl;
					return;
				}
				std::cout << "connected midi source to port" << std::endl;
			}

			template <xns::basic_string_literal type>
			inline auto disconnect(const midi::endpoint<type>& source) -> void {

				if (_port == 0 || source.get() == 0) { return; }

				OSStatus status = ::MIDIPortDisconnectSource(_port, source.get());

				if (status != noErr) {
					std::cerr << "error disconnecting midi source from port: " << status << std::endl;
					return;
				}
				std::cout << "disconnected midi source from port" << std::endl;
			}


		private:

			static inline auto read_midi(const MIDIEventList* evtlist, void* data) -> void {
				std::cout << "read midi" << std::endl;

				if (evtlist == nullptr) { return; }


				for (xns::size_t i = 0; i < evtlist->numPackets; ++i) {

					const MIDIEventPacket* packet = evtlist->packet + i;

					for (xns::size_t j = 0; j < packet->wordCount; ++j) {

						const UInt32 word = packet->words[j];

						const UInt8 status = word & 0xFF;
						const UInt8 data1 = (word >> 8) & 0xFF;
						const UInt8 data2 = (word >> 16) & 0xFF;

						std::cout << "status: " << static_cast<int>(status) << std::endl;

						std::cout << "data1: " << static_cast<int>(data1) << std::endl;

						std::cout << "data2: " << static_cast<int>(data2) << std::endl;

					}

				}

				// get packet list




			}

			// -- private data ------------------------------------------------

			/* port reference */
			::MIDIPortRef _port;

	};

}

#endif

#endif
