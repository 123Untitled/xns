#include "midi/server.hpp"


#if defined(XNS_APPLE)



/* default constructor */
midi::server::server(void)
:	_client{xns::string{"xns midi client"}},
	_source{_client, xns::string{"xns midi source"}},
	_destination{_client, xns::string{"xns midi destination"}} {
	setup_server();
}

/* shared */
auto midi::server::shared(void) -> self& {
	static self instance;
	return instance;
}

void midi::server::setup_server(void) {

	//_source.model("model_1.0");
	//_source.manufacturer("TMS_Industry");

	//midi::port port{_client};
	//port.connect(_source);

	std::cout << "press enter to disconnect" << std::endl;
	//CFRunLoopRun();
	while (true) {
	int c = std::getchar();
	if (c == 'q') { break; }
	}

	//port.disconnect(_source);

	//midiGetDevices();
	//create_port();
}


/* add midi */
void midi::server::add_midi(const xns::u32 msg, const timestamp time) {
	// add midi to packet
	_packet.add_midi(msg, time);
}

/* send midi */
void midi::server::send_midi(void) {
	// send midi to source device
	_packet.send_midi(_source);
}



char* getStringProperty(const MIDIObjectRef& obj, const CFStringRef& propertyID) {
	// buffer declaration
	CFStringRef cfstring;
	// get string property
	if (MIDIObjectGetStringProperty(obj, propertyID, &cfstring) == noErr) {
		// get property length
		CFIndex len = CFStringGetLength(cfstring);
		// check if length is not null
		if (len) {
			using cfindex = xns::make_unsigned<decltype(len)>;
			// new string allocation
			char* property = new char[static_cast<cfindex>(len) + 1]();
			// copy property to cstring
			CFStringGetCString(cfstring, property, len + 1, kCFStringEncodingUTF8);
			// free CFString
			CFRelease(cfstring);
			// return allocated string
			//return property;
			std::cout << property << std::endl;
		}
	}
	return nullptr;
}


void midi::server::get_devices(void) {

	// number of devices declaration
	ItemCount deviceNbr = 0;
	// get number of devices, if 0, return
	if (!(deviceNbr = MIDIGetNumberOfDevices())) { return; }


	// source list declaration
	//char **list = new char*[deviceNbr + 1];
	// add null pointer at end of list
	//list[deviceNbr] = nullptr;
	// buffer declaration
	// iteration over sources
	//
	for (xns::size_t x = 0; x < deviceNbr; ++x) {
		std::cout << "\x1b[34mdevice:\x1b[0m " << x << std::endl;

		MIDIDeviceRef device          = MIDIGetDevice(x);
		getStringProperty(device, kMIDIPropertyName);
		getStringProperty(device, kMIDIPropertyModel);
		getStringProperty(device, kMIDIPropertyManufacturer);

		ItemCount     entityDeviceNbr = MIDIDeviceGetNumberOfEntities(device);

		for (xns::size_t z = 0; z < entityDeviceNbr; ++z) {
			std::cout << "\x1b[34mentity:\x1b[0m " << z << std::endl;
			MIDIEntityRef entity = MIDIDeviceGetEntity(device, z);

			getStringProperty(entity, kMIDIPropertyName);
			getStringProperty(entity, kMIDIPropertyModel);
			getStringProperty(entity, kMIDIPropertyManufacturer);

			ItemCount     sourceNbr = MIDIEntityGetNumberOfSources(entity);
			for (xns::size_t y = 0; y < sourceNbr; ++y) {
				std::cout << "\x1b[34msource:\x1b[0m " << y << std::endl;
				MIDIEndpointRef source = MIDIEntityGetSource(entity, y);

				getStringProperty(source, kMIDIPropertyName);
				getStringProperty(source, kMIDIPropertyModel);
				getStringProperty(source, kMIDIPropertyManufacturer);

				//midiObjectGetIntegerProperty(source, kmidiPropertyUniqueID, &id);
				//std::cout << "source id: " << id << std::endl;
			}
		}
		std::cout << std::endl;
	}


	/*
	for (UInt x = 0; list[x]; ++x) {
		std::cout << list[x] << std::endl;
		delete[] list[x];
	}
	delete[] list;
	*/
}

// kmidiPropertyName
// kmidiPropertyOffline
// kmidiPropertyTransmitsClock
// kmidiPropertyAdvanceScheduleTimeMuSec
// kmidiPropertyManufacturer
void midi::server::get_sources(void) {

	ItemCount src = MIDIGetNumberOfSources();

	for (xns::size_t x = 0; x < src; ++x) {
		std::cout << "\x1b[34msource:\x1b[0m " << x << std::endl;
		MIDIEndpointRef source = MIDIGetSource(x);
		getStringProperty(source, kMIDIPropertyName);
		getStringProperty(source, kMIDIPropertyModel);
		getStringProperty(source, kMIDIPropertyManufacturer);
	}

	ItemCount dst = MIDIGetNumberOfDestinations();

	for (xns::size_t x = 0; x < dst; ++x) {
		std::cout << "\x1b[34mdestination:\x1b[0m " << x << std::endl;
		MIDIEndpointRef destination = MIDIGetDestination(x);
		getStringProperty(destination, kMIDIPropertyName);
		getStringProperty(destination, kMIDIPropertyModel);
		getStringProperty(destination, kMIDIPropertyManufacturer);
	}

}




#endif

