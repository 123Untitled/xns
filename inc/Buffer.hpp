#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include "Macro.hpp"
#include "Types.hpp"

#include <cstdlib>
#include <unistd.h>
#include <iostream>


// -- B U F F E R  C L A S S --------------------------------------------------

class Buffer final {

	public:

		// -- C O N S T R U C T O R S -----------------------------------------

		/* non-instanciable class */
		NON_INSTANCIABLE(Buffer);


		// -- P U B L I C  M E T H O D S --------------------------------------

		/* draw */
		static void draw(const void* ptr, const UInt size);

		/* render */
		static int render(const int fd = STDOUT_FILENO);


	private:

		// -- P R I V A T E  M E T H O D S ------------------------------------

		/* initialize buffer */
		static char* initialize_buffer(void);

		/* static destructor */
		static void static_destructor(void);


		static void extend(const UInt bytes);


		static char*	_buff;
		static UInt		_size;
		static UInt		_pos;


};

#endif
