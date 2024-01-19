#ifndef XNS_MIDI_SOURCE_HPP
#define XNS_MIDI_SOURCE_HPP

#include "midi/client.hpp"
#include "midi/platform.hpp"

#include "string_literal.hpp"


#include <string>
#include <iostream>


#if defined(XNS_APPLE)


// -- M I D I  N A M E S P A C E ----------------------------------------------

namespace midi {


	// -- E N D P O I N T  C L A S S ------------------------------------------

	template <xns::basic_string_literal type>
	class endpoint final {

		// -- assertions ------------------------------------------------------

		static_assert( type == "source"
					or type == "destination", "): ENDPOINT: invalid type :(");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = midi::endpoint<type>;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			endpoint(void) = delete;

			/* client constructor */
			inline endpoint(const midi::client& client, const xns::string& name) requires (type == "source")
			: _endpoint{0} {

				if (not client) {
					std::cerr << "error creating midi source: client is invalid" << std::endl;
					return;
				}

				// create a new source
				const OSStatus err = MIDISourceCreateWithProtocol(client.get(),
															CFSTR("xns midi source"),
															kMIDIProtocol_1_0,
															&_endpoint);
				// check if there was an error
				if (err != noErr) {
					std::cerr << "error creating midi source: " << err << std::endl;
				}
				else {
					std::cout << "created midi source" << std::endl;
				}
			}

			/* client constructor */
			inline endpoint(const midi::client& client, const xns::string& name) requires (type == "destination")
			: _endpoint{0} {

				if (not client) {
					std::cerr << "error creating midi destination: client is invalid" << std::endl;
					return;
				}

				// create a new source
				const OSStatus err = MIDIDestinationCreateWithProtocol(client.get(),
															CFSTR("xns midi destination"),
															kMIDIProtocol_1_0,
															&_endpoint,
															^(const MIDIEventList* evtlist, void*) {
																self::read_midi(evtlist);
															});
				// check if there was an error
				if (err != noErr) {
					std::cerr << "error creating midi destination: " << err << std::endl;
				}
				else {
					std::cout << "created midi destination" << std::endl;
				}
			}


			/* non-copyable class */
			non_copyable(endpoint);

			/* move constructor */
			endpoint(self&& other) noexcept
			: _endpoint{other._endpoint} {
				other._endpoint = 0;
			}

			/* destructor */
			inline ~endpoint(void) noexcept {
				// dispose endpoint
				dispose();
			}


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// check if the source is the same
				if (this == &other) { return *this; }
				// dispose endpoint
				dispose();
				// move source
				_endpoint = other._endpoint;
				// invalidate other
				other._endpoint = 0;
				// return self
				return *this;
			}


			// -- public modifiers --------------------------------------------

			/* model */
			auto model(const xns::string&) -> void {
				static_cast<void>(model);
				::MIDIObjectSetStringProperty(_endpoint, kMIDIPropertyModel, CFSTR("model_1.0"));
			}

			/* manufacturer */
			auto manufacturer(const xns::string&) -> void {
				static_cast<void>(manufacturer);
				::MIDIObjectSetStringProperty(_endpoint, kMIDIPropertyManufacturer, CFSTR("TMS_Industry"));
			}


			// -- public accessors --------------------------------------------

			/* get endpoint */
			inline auto get(void) noexcept -> MIDIEndpointRef& {
				return _endpoint;
			}

			/* get const endpoint */
			inline auto get(void) const noexcept -> const MIDIEndpointRef& {
				return _endpoint;
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
				// return endpoint validity
				return _endpoint ? true : false;
			}

			/* not operator */
			inline auto operator!(void) const noexcept -> bool {
				// return endpoint validity
				return _endpoint ? false : true;
			}


		private:

			// -- private static methods --------------------------------------

			/* read midi */
			static auto read_midi(const MIDIEventList* evtlist) -> void requires (type == "destination") {

				if (evtlist == nullptr) { return; }

				std::cout << "numPackets: " << evtlist->numPackets << std::endl;
				for (xns::size_t i = 0; i < evtlist->numPackets; ++i) {

					const MIDIEventPacket* packet = evtlist->packet + i;

					std::cout << "wordCount: " << packet->wordCount << std::endl;
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

			}

			/* dispose endpoint */
			auto dispose(void) noexcept {

				if (_endpoint == 0) { return; }

				OSStatus status = ::MIDIEndpointDispose(_endpoint);

				if (status != noErr)
					std::cerr << "error disposing midi endpoint: " << status << std::endl;
				else
					std::cout << "disposed midi endpoint" << std::endl;

			}

			/* init */
			auto init(void) noexcept -> void {
				_endpoint = 0;
			}


			// -- private members ---------------------------------------------

			/* source */
			::MIDIEndpointRef _endpoint;

	};



	class map final {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = midi::map;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline map(void) noexcept
			: _data{} {
			}


		private:

			// -- private types -----------------------------------------------

			/* type per channel */
			using data = xns::tuple<xns::array<bool,    128>,
									xns::array<xns::u8, 128>,
									xns::array<xns::u8, 128>>;


			// -- private members ---------------------------------------------

			/* channel data */
			xns::array<data, 16> _data;


	};



}

#endif

#endif
