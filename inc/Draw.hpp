#ifndef DRAW_HEADER
#define DRAW_HEADER

#include <unistd.h>

#include <Str.hpp>



// libxfunc
#include "Escape.hpp"
#include "Types.hpp"
#include "Ascii.hpp"
#include "Macro.hpp"
#include "Buffer.hpp"


#define PDELAY		40000

class Draw {

public:

	NON_INSTANCIABLE(Draw);

	/* -------------------------------- */

	static void drawLine(const UInt x, const UInt y, const void *ptr, const UInt size);

	static void drawStr(const UInt x, const UInt y, const Str& str);

	static void vertivalDraw(const UInt x, UInt y, const void *ptr, const UInt size, UInt line);

	static void clearLine(UInt32 posX, UInt32 posY, UInt32 size);

	static void drawInteger(UInt number);

	//static int drawStringNl(const Str& string);

	//static void animateDraw(const Str& string);
	//static void animateDrawNl(const Str& string);
	//static void animateDraw(const Str& string, const UInt32 colorIn, const UInt32 colorOut);

};


#endif
