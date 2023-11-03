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

//UInt32 msg = MIDICLOCKTICK;
/*
msg = on ? 0x20900000 : 0x20800000; // note on or off
msg = msg | ((note & 0x7F) << 8); // note
msg = msg | 127; // velocity
*/


#if defined(__APPLE__) && defined(__MACH__)

// -- M I D I  N A M E S P A C E ----------------------------------------------

namespace midi {

	/* common midi messages */
	enum : xns::u32 {
		CLOCK = 0x10F80000,
		START = 0x10FA0000, STOP  = 0x10FC0000,
		ON    = 0x20900000, OFF   = 0x20800000
	};

	/* forward declaration */
	class server;

	/* unique server type */
	using weak_server = xns::weak_ptr<midi::server>;


	// -- M I D I  C L A S S --------------------------------------------------

	class server final {


		friend class xns::memory::pool<midi::server>;

		private:

			template <class>
			friend class xns::allocator;


			// -- P R I V A T E  T Y P E S ------------------------------------

			/* unique server type */
			using unique_server = xns::unique_ptr<midi::server>;

			/* time stamp type */
			using timestamp = MIDITimeStamp;


			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			server(void);

			/* non-copyable class */
			NON_ASSIGNABLE(server);

			/* destructor */
			~server(void);




			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* singleton instance */
			static unique_server _instance;


		public:

			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------

			/* instance getter */
			static server& shared(void);

			/* delete server */
			static void delete_server(void);



			/* add midi message */
			void add_midi(const xns::u32, const timestamp = 0);

			/* send midi message */
			void send_midi(void);



			void get_sources(void);
			void get_devices(void);


		private:

			// -- P R I V A T E  M E T H O D S --------------------------------

			/* setup midi */
			void setup_server(void);




			// -- P R I V A T E  M E M B E R S --------------------------------

			/* client */
			midi::client _client;

			/* source */
			midi::source _source;

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
