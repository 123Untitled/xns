#ifndef XNS_MIDI_SERVER_HPP
#define XNS_MIDI_SERVER_HPP

// xns headers

#include "weak_ptr.hpp"
#include "unique_ptr.hpp"
#include "make_unsigned.hpp"

#include <iostream>

#include "platform.hpp"
#include "client.hpp"
#include "source.hpp"
#include "message.hpp"
#include "port.hpp"

//UInt32 msg = MIDICLOCKTICK;
/*
msg = on ? 0x20900000 : 0x20800000; // note on or off
msg = msg | ((note & 0x7F) << 8); // note
msg = msg | 127; // velocity
*/


#if defined(XNS_APPLE)

// -- M I D I  N A M E S P A C E ----------------------------------------------

namespace midi {

	/* common midi messages */
	enum : xns::u32 {
		CLOCK = 0x10F80000,
		START = 0x10FA0000, STOP  = 0x10FC0000,
		ON    = 0x20900000, OFF   = 0x20800000
	};


	// -- S E R V E R  C L A S S ----------------------------------------------

	class server final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = midi::server;

			/* time stamp type */
			using timestamp = MIDITimeStamp;


			// -- public lifecycle --------------------------------------------

			/* non-copyable class */
			non_assignable(server);

			/* destructor */
			~server(void) noexcept = default;


			// -- public static methods ---------------------------------------

			/* instance getter */
			static server& shared(void);



			/* add midi message */
			void add_midi(const xns::u32, const timestamp = 0);

			/* send midi message */
			void send_midi(void);



			void get_sources(void);
			void get_devices(void);


		private:


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			server(void);


			// -- private methods ---------------------------------------------

			/* setup midi */
			void setup_server(void);


			// -- private members ---------------------------------------------

			/* client */
			midi::client _client;

			/* source */
			midi::endpoint<"source"> _source;

			/* destination */
			midi::endpoint<"destination"> _destination;

			/* packet */
			midi::packet _packet;


			//UInt				_data;
			//Devicelist _devicelist;

	};

}










class Devicelist final {
	public:
		Devicelist(void);
		~Devicelist(void);
	private:
		class Device;
		Device** _devices;
		class Device final {
			public:
				Device(void);
				~Device(void);
			private:
				class Entity;
				MIDIDeviceRef _device;
				UInt64        _index;
				Entity**      _entities;
				class Entity final {
					public:
						Entity(void);
						~Entity(void);
					private:
						class Source;
						MIDIEntityRef _entity;
						UInt64        _index;
						Source**      _sources;
						class Source final {
							public:
								Source(void);
								~Source(void);
							private:
								MIDIEndpointRef _source;
								UInt64          _index;
						};
				};
		};
};

#endif

#endif
