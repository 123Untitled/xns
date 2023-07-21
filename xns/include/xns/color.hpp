#ifndef COLOR_HEADER
#define COLOR_HEADER

#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	using hexcolor = xns::u32;

	// -- C O L O R  C L A S S ------------------------------------------------

	class color final {

		public:

			// -- A L I A S E S -----------------------------------------------


			enum : hexcolor {

				LOWLIGHT_COLOR		= 0x414868,
				DARK_GREY_COLOR		= 0x636363,
				BCKGRND_COLOR		= 0x1F1F1F,
				GREY_COLOR			= 0x7F7F7F,
				WHITE_COLOR			= 0xE5E5E5,
				GREEN_COLOR			= 0x37FFDA,
				RED_COLOR			= 0xFF8BA5
			};

	};
}

/*
#define LOWLIGHT_COLOR		0x414868
#define DARK_GREY_COLOR		0x636363
#define BCKGRND_COLOR		0x1F1F1F
#define GREY_COLOR			0x7F7F7F
#define WHITE_COLOR			0xE5E5E5
#define GREEN_COLOR			0x37FFDA
#define RED_COLOR			0xFF8BA5
*/



#endif
