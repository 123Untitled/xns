#ifndef XNS_MIDI_SOURCE_HPP
#define XNS_MIDI_SOURCE_HPP

#include "midi/client.hpp"
#include "midi/platform.hpp"


#include <string>
#include <iostream>


#if defined(__APPLE__) && defined(__MACH__)

// -- M I D I  N A M E S P A C E ----------------------------------------------

namespace midi {


	// -- S O U R C E  C L A S S ----------------------------------------------

	class source final {

		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* default constructor */
			source(void);

			/* deleted copy constructor */
			source(const source&) = delete;

			/* deleted move constructor */
			source(source&&) = delete;

			/* destructor */
			~source(void);


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* create */
			void create(const midi::client& client, const std::string& name);


			// -- P U B L I C  S E T T E R S ----------------------------------

			/* set model */
			void set_model(const std::string&);

			/* set manufacturer */
			void set_manufacturer(const std::string&);


			// -- P U B L I C  A C C E S S O R S ------------------------------

			/* get source */
			MIDIEndpointRef& get(void) noexcept;

			/* get const source */
			const MIDIEndpointRef& get(void) const noexcept;



		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* source */
			MIDIEndpointRef _source;


	};





}

#endif

#endif
