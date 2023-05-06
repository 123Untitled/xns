#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include "macro.hpp"
#include "types.hpp"
#include "allocator.hpp"
#include "string.hpp"
#include "vector.hpp"

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- O U T P U T  C L A S S ----------------------------------------------

	class Output final {

		private:

			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			Output(void);

			/* non-assignable class */
			NON_ASSIGNABLE(Output);


		public:

			// -- P U B L I C  D E S T R U C T O R S --------------------------

			/* destructor */
			~Output(void);


			// -- P U B L I C  S T A T I C  M E T H O D S ---------------------

			/* write unknown bytes */
			static void write(const char* str);

			/* write bytes */
			static void write(const char* str, const Xf::CString::Size size);

			/* write string */
			static void write(const CString& str);

			/* render */
			static void render(const int = STDOUT_FILENO);



		private:

			// -- P R I V A T E  E N U M S ------------------------------------

			/* buffer size */
			enum : Size { DEFAULT_BUFFER_SIZE = 1024 };


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* buffers */
			Xf::CString _buffer;


			// -- P R I V A T E  S T A T I C  M E M B E R S -------------------

			/* instance */
			static Output _instance;


	};




}




// -- B U F F E R  C L A S S --------------------------------------------------

//class Buffer final {
//
//	public:
//
//		// -- P U B L I C  A L I A S E S --------------------------------------
//
//		/* string type */
//		using BString = Xf::CString;
//
//		/* character type */
//		using CharT = BString::CharT;
//
//		/* reference type */
//		using Reference = CharT&;
//
//		/* pointer type */
//		using Pointer = CharT*;
//
//		/* size type */
//		using Size = BString::Size;
//
//		/* allocator type */
//		using Allocator = Xf::Allocator<CharT>;
//
//
//	private:
//
//		// -- P R I V A T E  C O N S T R U C T O R S --------------------------
//
//		/* default constructor */
//		Buffer(void);
//
//		/* non-assignable class */
//		NON_ASSIGNABLE(Buffer);
//
//
//	public:
//
//		// -- P U B L I C  D E S T R U C T O R --------------------------------
//
//		/* destructor */
//		~Buffer(void);
//
//
//		// -- S T A T I C  M E T H O D S --------------------------------------
//
//		/* write bytes */
//		static void write(const void* ptr, const Size size);
//
//		/* write string */
//		static void write(const BString& str);
//
//
//
//
//		/* draw */
//		static void draw(const void* ptr, const Size size);
//
//		/* render */
//		static void render(const int);
//
//		static void render(void);
//
//
//	private:
//
//		// -- P R I V A T E  M E T H O D S ------------------------------------
//
//		/* draw */
//		void _draw(const void* ptr, const Size size);
//
//		/* render */
//		int _render(const int fd = STDOUT_FILENO);
//
//		/* get instance */
//		static Buffer& get_instance(void);
//
//
//
//		static void extend(const UInt bytes);
//
//
//		// -- P R I V A T E  E N U M S ----------------------------------------
//
//		/* buffer size */
//		enum : Size { DEFAULT_BUFFER_SIZE = 1024 };
//
//
//		// -- P R I V A T E  S T A T I C  M E M B E R S -----------------------
//
//		/* singleton instance */
//		static Buffer _instance;
//
//
//		// -- P R I V A T E  M E M B E R S ------------------------------------
//
//		Pointer _buff;
//		Size    _capacity;
//		Size    _size;
//		bool	_exit_render;
//
//
//
//};

#endif
