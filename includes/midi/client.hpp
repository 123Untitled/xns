#ifndef XNS_MIDI_CLIENT_HPP
#define XNS_MIDI_CLIENT_HPP


#include "macros.hpp"
#include "string.hpp"
#include "platform.hpp"

#include <iostream>


#if defined(XNS_APPLE)


namespace midi {


	inline auto set_string_property(const MIDIObjectRef& obj,
									const CFStringRef& property,
									const xns::string& name) -> void {

		CFStringRef cstr = ::CFStringCreateWithCString( kCFAllocatorDefault,
														name.data(),
														kCFStringEncodingASCII);

		if (cstr == nullptr) {
			std::cerr << "error creating cfstring" << std::endl;
			return;
		}

		// set name
		OSStatus status = ::MIDIObjectSetStringProperty(obj, property, cstr);

		// check if there was an error
		if (status != noErr) {
			std::cerr << "error setting name: " << status << std::endl;
		}

		// release cfstring
		::CFRelease(cstr);
	}

	inline auto set_integer_property(const MIDIObjectRef& obj,
									 const CFStringRef& property,
									 const SInt32& value) -> void {

		// set value
		OSStatus status = ::MIDIObjectSetIntegerProperty(obj, property, value);

		// check if there was an error
		if (status != noErr) {
			std::cerr << "error setting name: " << status << std::endl;
		}
	}


	// -- C L I E N T  C L A S S ----------------------------------------------

	class client final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = midi::client;



			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			inline client(void) noexcept
			: _client{0} {}

			/* name constructor */
			inline client(const xns::string& name) noexcept
			: _client{0} {
				initialize(name);
			}

			/* non-copyable class */
			non_copyable(client);

			/* move constructor */
			inline client(client&& other) noexcept
			: _client{other._client} {
				other._client = 0;
			}

			/* destructor */
			inline ~client(void) noexcept {
				// check client validity
				if (_client == 0) { return; }
				// dispose client
				if (::MIDIClientDispose(_client) != noErr) {
					std::cout << "error disposing midi client" << std::endl;
					return;
				} // print success
				std::cout << "client midi disposed" << std::endl;
			}


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			inline auto operator=(client&& other) noexcept -> client& {
				// check self assignment
				if (this == &other) { return *this; }
				// dispose client
				this->~client();
				// move client
				_client = other._client;
				other._client = 0;
				// return self reference
				return *this;
			}


			inline auto reset(void) noexcept -> void {
				this->~client();
				_client = 0;
			}

			// -- P U B L I C  M E T H O D S ----------------------------------

			/* initialyze client */
			auto initialize(const xns::string&) noexcept -> void;


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
				// return client validity
				return _client ? true : false;
			}

			/* not operator */
			auto operator!(void) const noexcept -> bool {
				// return client validity
				return _client ? false : true;
			}


			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* get client */
			inline auto get(void) noexcept -> ::MIDIClientRef& {
				return _client;
			}

			/* get const client */
			inline auto get(void) const noexcept -> const ::MIDIClientRef& {
				return _client;
			}


		private:

			// -- private static methods --------------------------------------

			/* client notification callback */
			static auto notification(const MIDINotification*, void*) -> void;


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* client */
			::MIDIClientRef _client;


	};

}

#endif // XNS_APPLE

#endif // MIDI_CLIENT_HPP
