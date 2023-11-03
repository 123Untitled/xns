#include "midi/source.hpp"

#if defined(__APPLE__) && defined(__MACH__)

/* default constructor */
midi::source::source(void)
:	_source{0} {
	//_index{0} {
}

/* destructor */
midi::source::~source(void) {
	// check source validity
	if (_source) {
		// dispose source
		OSStatus status = MIDIEndpointDispose(_source);
		// check if there was an error
		if (status != noErr) {
			// INFO: print error
		} // reset source
		_source = 0;
	}
}

/* create */
void midi::source::create(const midi::client& client, const std::string& name) {

	if (client == false) {
		// INFO: print error
		return;
	}

	// create a new source
	const OSStatus err = MIDISourceCreateWithProtocol(client.get(),
												CFSTR("MIDI_Engine"),
												kMIDIProtocol_1_0,
												&_source);
	// check if there was an error
	if (err != noErr) {
		// INFO: print error
	}
}

/* set model */
void midi::source::set_model(const std::string& model) {
	static_cast<void>(model);
	MIDIObjectSetStringProperty(_source, kMIDIPropertyModel, CFSTR("model_1.0"));
}

/* set manufacturer */
void midi::source::set_manufacturer(const std::string& manufacturer) {
	static_cast<void>(manufacturer);
	MIDIObjectSetStringProperty(_source, kMIDIPropertyManufacturer, CFSTR("TMS_Industry"));
}

/* get source */
MIDIEndpointRef& midi::source::get(void) noexcept {
	// return source reference
	return _source;
}

/* get const source */
const MIDIEndpointRef& midi::source::get(void) const noexcept {
	// return source reference
	return _source;
}


#endif

