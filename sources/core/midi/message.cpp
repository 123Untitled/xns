#include "midi/message.hpp"

#if defined(__APPLE__) && defined(__MACH__)

/* default constructor */
midi::packet::packet(void)
: _buffer{ }, _packet{nullptr}, _list{nullptr} {
	// reserve default buffer size
	_buffer.reserve(BUFFSIZE);
	// initialize the event list
	_list = reinterpret_cast<MIDIEventList*>(_buffer.data());
	// initialize the event packet
	_packet = MIDIEventListInit(_list, kMIDIProtocol_1_0);

}

/* destructor */
midi::packet::~packet(void) {
	// nothing to do here
}



void midi::packet::send_midi(const midi::source& source) {

	// check packet validity
	if (_packet == nullptr) { return; }

	// WARNING: need to check if the source is valid

	// send midi to source device
	const OSStatus err = MIDIReceivedEventList(source.get(), _list);

	// check if the midi was sent. INFO: not implemented
	_packet = MIDIEventListInit(_list, kMIDIProtocol_1_0);
}


void midi::packet::add_midi(UInt32 msg, MIDITimeStamp time) {

	// check packet validity
	if (_packet == nullptr) { return; }

	addmsg:
	// add the midi message to the packet
	_packet = MIDIEventListAdd(_list, _buffer.capacity() , _packet, 0, 1, &msg);

	// check packet validity
	if (!_packet) {
		// check if the buffer can be resized
		if (resize_buffer() == false) { return; }
		// try again
		goto addmsg;
	}
}

bool midi::packet::resize_buffer(void) {

	// check if the max number of events has been reached
	if ((_buffer.capacity() * 2) > MAXEVENT) { return false; }

	// else resize the buffer
	_buffer.resize(_buffer.capacity() * 2);

	// update the list and packet pointers
	_list = reinterpret_cast<MIDIEventList*>(_buffer.data());

	// update the packet pointer
	const xns::size_t idx = _list->numPackets ? (_list->numPackets - 1) : 0;

	_packet = &(_list->packet[idx]);

	return true;
}

#endif
