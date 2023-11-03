#include "client.hpp"

#if defined(XNS_APPLE)

/* default constructor */
midi::client::client(void)
: _client{0} {}

/* destructor */
midi::client::~client(void) {
	// check client validity
	if (_client) {
		// dispose client
		OSStatus status = MIDIClientDispose(_client);
		// check if there was an error
		if (status != noErr) {
			// INFO: print error
		}
		// reset client
		_client = 0;
	}
}

/* create */
auto midi::client::create(const xns::string& name) noexcept -> void {
	// dispose previous client
	this->~client();

	CFStringRef cstr =
	CFStringCreateWithCString(kCFAllocatorDefault,
			name.data(), kCFStringEncodingASCII);

	// create client
	OSStatus status = MIDIClientCreate(cstr, notification, nullptr, &_client);
	// check if there was an error
	if (status != noErr) {
		// INFO: print error
	}
}

/* boolean operator */
midi::client::operator bool(void) const noexcept {
	// return client validity
	return _client ? true : false;
}

/* not operator */
auto midi::client::operator!(void) const noexcept -> bool {
	// return client validity
	return _client ? false : true;
}

/* get client */
auto midi::client::get(void) noexcept -> midi::client::midi_client& {
	// return client reference
	return _client;
}

/* get const client */
auto midi::client::get(void) const noexcept -> const midi::client::midi_client& {
	// return const client reference
	return _client;
}



#define HINT_(what) std::cout << "\x1b[33m" << what << "\x1b[0m" << std::endl;


/* client notification callback */
static void midi::notification(const MIDINotification *message, void *refCon) {
	// avoid unused parameter warning
	static_cast<void>(refCon);

	switch (message->messageID) {
		// Some aspect of the current MIDI setup changed.
		case kMIDIMsgSetupChanged:
			HINT_("setup changed"); break;
		// The system added a device, entity, or endpoint.
		case kMIDIMsgObjectAdded:
			HINT_("object added"); break;
		// The system removed a device, entity, or endpoint.
		case kMIDIMsgObjectRemoved:
			HINT_("object removed"); break;
		// An object’s property value changed.
		case kMIDIMsgPropertyChanged:
			HINT_("property changed"); break;
		// The system created or disposed of a persistent MIDI Thru connection.
		case kMIDIMsgThruConnectionsChanged:
			HINT_("thru connection changed"); break;
		// The system changed a serial port owner.
		case kMIDIMsgSerialPortOwnerChanged:
			HINT_("serial port owner changed"); break;
		// An I/O error occurred.
		case kMIDIMsgIOError:
			HINT_("io error"); break;

		default: std::cout << "UNKNOWN NOTIFICATION" << std::endl;
	}
	std::cout << "notification: " << message->messageID << std::endl;
}

#endif // XNS_APPLE

