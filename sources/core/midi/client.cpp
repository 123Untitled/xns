#include "client.hpp"

#if defined(XNS_APPLE)


/* initialize */
auto midi::client::initialize(const xns::string& name) noexcept -> void {

	self::reset();



	CFStringRef cstr =
	::CFStringCreateWithCString(kCFAllocatorDefault,
			name.data(), kCFStringEncodingASCII);

	// create client
	OSStatus status = ::MIDIClientCreate(cstr, notification, this, &_client);

	// check if there was an error
	if (status != noErr) {
		std::cerr << "error creating midi client: " << status << std::endl;
		return;
	}
	std::cout << "created midi client" << std::endl;


	//midi::set_string_property(_client, kMIDIPropertyName, name);
	//midi::set_string_property(_client, kMIDIPropertyModel, "model_1.0");
	//midi::set_string_property(_client, kMIDIPropertyManufacturer, "TMS_Industry");
	//
	//// capabilities
	//
	//midi::set_integer_property(_client, kMIDIPropertySupportsMMC, 0);
	//midi::set_integer_property(_client, kMIDIPropertySupportsGeneralMIDI, 0);
	//midi::set_integer_property(_client, kMIDIPropertySupportsShowControl, 0);
	//
	//// banks
	//
	//midi::set_integer_property(_client, kMIDIPropertyReceivesBankSelectLSB, 0);
	//midi::set_integer_property(_client, kMIDIPropertyTransmitsBankSelectLSB, 0);
	//midi::set_integer_property(_client, kMIDIPropertyReceivesBankSelectMSB, 0);
	//midi::set_integer_property(_client, kMIDIPropertyTransmitsBankSelectMSB, 0);
	//
	//// notes
	//
	//midi::set_integer_property(_client, kMIDIPropertyReceivesNotes, 1);
	//midi::set_integer_property(_client, kMIDIPropertyTransmitsNotes, 1);
	//
	//
	//// program changes
	//
	//midi::set_integer_property(_client, kMIDIPropertyReceivesProgramChanges, 0);
	//midi::set_integer_property(_client, kMIDIPropertyTransmitsProgramChanges, 0);
	//
	//// channels
	//
	//// The maximum number of MIDI channels on which a device may simultaneously receive channel messages.
	//midi::set_integer_property(_client, kMIDIPropertyMaxReceiveChannels, 0x7F);
	//// The maximum number of MIDI channels on which a device may simultaneously transmit channel messages.
	//midi::set_integer_property(_client, kMIDIPropertyMaxTransmitChannels, 0x7F);
	//// The bitmap of channels on which the object receives messages.
	//midi::set_integer_property(_client, kMIDIPropertyReceiveChannels, 0x7F);
	//// The bitmap of channels on which the object transmits messages.
	//midi::set_integer_property(_client, kMIDIPropertyTransmitChannels, 0x7F);
	//
	//
	//// connections
	//
	//// A Boolean value that indicates whether the device or entity can route messages to or from external MIDI devices.
	//midi::set_integer_property(_client, kMIDIPropertyCanRoute, 0);
	//// A Boolean value that indicates whether the endpoint broadcasts messages to all of the other endpoints in the device.
	//midi::set_integer_property(_client, kMIDIPropertyIsBroadcast, 0);
	//// The unique identifier of an external device attached to this connection.
	//midi::set_integer_property(_client, kMIDIPropertyConnectionUniqueID, 0);
	//// A Boolean value that indicates whether this entity or endpoint has external MIDI connections.
	//midi::set_integer_property(_client, kMIDIPropertyIsEmbeddedEntity, 0);
	//// The 0-based index of the entity on which incoming real-time messages from the device appear to have originated.
	//midi::set_integer_property(_client, kMIDIPropertySingleRealtimeEntity, 0);
	//
}




#define HINT_(what) std::cout << "\x1b[33m" << what << "\x1b[0m" << std::endl;


/* client notification callback */
auto midi::client::notification(const MIDINotification *message, void* data) -> void {

	// get client reference
	self& client = *static_cast<self*>(data);

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

