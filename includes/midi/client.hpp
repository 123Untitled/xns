#ifndef XNS_MIDI_CLIENT_HPP
#define XNS_MIDI_CLIENT_HPP


#include "macros.hpp"
#include "string.hpp"
#include "platform.hpp"

#include <iostream>


#if defined(XNS_APPLE)


namespace midi {

	/* client notification callback */
	static void notification(const MIDINotification*, void*);


	// -- C L I E N T  C L A S S ----------------------------------------------

	class client final {

		private:

			// -- P R I V A T E  T Y P E S ------------------------------------

			/* client type */
			using midi_client = ::MIDIClientRef;


		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			client(void);

			/* non-assignable class */
			NON_ASSIGNABLE(client);

			/* destructor */
			~client(void);


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* create */
			auto create(const xns::string& name) noexcept -> void;


			// -- P U B L I C  B O O L E A N S  O P E R A T O R S -------------

			/* boolean operator */
			operator bool(void) const noexcept;

			/* not operator */
			auto operator!(void) const noexcept -> bool;


			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* get client */
			auto get(void) noexcept -> midi_client&;

			/* get const client */
			auto get(void) const noexcept -> const midi_client&;


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* client */
			midi_client _client;


	};

}

#endif // XNS_APPLE

#endif // MIDI_CLIENT_HPP
