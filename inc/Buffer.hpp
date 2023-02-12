#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include "Macro.hpp"
#include "Types.hpp"
#include "allocator.hpp"

#include <cstdlib>
#include <unistd.h>
#include <iostream>


// -- B U F F E R  C L A S S --------------------------------------------------

class Buffer final {

	private:

		// -- P R I V A T E  A L I A S E S ------------------------------------

		/* char type */
		using Char = char;

		/* reference type */
		using Reference = Char&;

		/* pointer type */
		using Pointer = Char*;

		/* size type */
		using Size = UInt64;

		/* allocator type */
		using Allocator = Xf::Allocator<Char>;


		// -- P R I V A T E  C O N S T R U C T O R S --------------------------

		/* [PRIVATE] default constructor */
		Buffer(void);

		/* deleted copy constructor */
		Buffer(const Buffer&) = delete;

		/* deleted move constructor */
		Buffer(Buffer&&) = delete;


	public:

		// -- D E S T R U C T O R ---------------------------------------------

		/* [PUBLIC] destructor */
		~Buffer(void);


		// -- S T A T I C  M E T H O D S --------------------------------------

		/* [PUBLIC] draw */
		static void draw(const void* ptr, const Size size);

		/* [PUBLIC] render */
		static int render(const int fd = STDOUT_FILENO);


	private:

		// -- P R I V A T E  M E T H O D S ------------------------------------

		/* get instance */
		static Buffer& get_instance(void);



		static void extend(const UInt bytes);


		// -- P R I V A T E  E N U M S ----------------------------------------

		/* buffer size */
		enum : Size { DEFAULT_BUFFER_SIZE = 1024 };


		// -- P R I V A T E  S T A T I C  M E M B E R S -----------------------

		/* singleton instance */
		static Buffer _instance;


		// -- P R I V A T E  M E M B E R S ------------------------------------

		Pointer _buff;
		Size    _size;
		Size    _pos;


};

#endif
