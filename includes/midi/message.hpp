#ifndef MIDI_PACKET_HEADER
#define MIDI_PACKET_HEADER

// xns headers

#include "midi/platform.hpp"
#include "midi/source.hpp"

#include <vector>

#if defined(__APPLE__) && defined(__MACH__)

// -- M I D I  N A M E S P A C E ----------------------------------------------

namespace midi {


	// -- P A C K E T  C L A S S ----------------------------------------------

	class packet {

		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			packet(void);

			/* copy constructor */
			packet(const packet&) = delete;

			/* move constructor */
			packet(packet&&) = delete;

			/* destructor */
			~packet(void);


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* send midi */
			void send_midi(const midi::source&);

			/* add midi */
			void add_midi(UInt32, MIDITimeStamp = 0);

			/* resize buffer */
			bool resize_buffer(void);


		private:

			// -- P R I V A T E  E N U M S ------------------------------------

			/* capacity limits */
			enum { BUFFSIZE = sizeof(MIDIEventList), MAXEVENT = 65'536 };

			// The maximum size of an event list is 65,536 bytes.


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* buffer */
			std::vector<UInt8> _buffer;

			/* A series of simultaneous MIDI events in Universal MIDI packets (UMP) format. */
			/*       - timeStamp (UInt64) -> The event packet timestamp. */
			/*       - wordCount (UInt32) -> The number of valid MIDI 32-bit words in this event packet. */
			/*       - words (UInt32 []) -> A variable-length stream of native-endian 32-bit Universal MIDI packets (UMP). */
			MIDIEventPacket* _packet;

			/* A variable-length list of MIDI event packets. */
			/*       - protocol (MIDIProtocolID) -> The MIDI protocol variant of the events in the list. */
			/*       - numpackets (UInt32) -> The number of MIDI event packet structures in the list. */
			/*       - packet (MIDIEventpacket) -> An array of variable-length MIDI event packet structures. */
			MIDIEventList* _list;



	};


};




#endif

#endif
