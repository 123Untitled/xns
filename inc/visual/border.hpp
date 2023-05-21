#ifndef BORDER_HEADER
#define BORDER_HEADER

#include "array.hpp"
#include "types.hpp"
#include "macro.hpp"
#include "rect.hpp"
#include "escape.hpp"
#include "allocator.hpp"
#include "color.hpp"

#include <iostream>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- B O R D E R  C L A S S ----------------------------------------------

	class Border final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* size type */
			using Size = UInt64;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			Border(void);

			/* size and position constructor */
			Border(const Xf::Rect& rect);

			/* copy constructor */
			Border(const Border& other);

			/* move constructor */
			Border(Border&& other) noexcept;

			/* destructor */
			~Border(void);


			// -- O P E R A T O R S -------------------------------------------

			/* copy assignment operator */
			Border& operator=(const Border& other);

			/* move assignment operator */
			Border& operator=(Border&& other) noexcept;

			/* bool operator */
			explicit operator bool(void) const;

			/* bool not operator */
			bool operator!(void) const;


			// -- M E T H O D S -----------------------------------------------

			/* draw border */
			void draw(void);

			/* set size and position */
			void set(const Xf::Rect& rect,
					const Xf::Hexcolor color = Xf::Color::GREY_COLOR);

			/* set border color */
			// INFO: not defined yet


		private:

			// -- E N U M S ---------------------------------------------------

			/* symbol enum */
			enum {
				LINE_H, LINE_V,
				CORNER_TL, CORNER_TR, CORNER_BL, CORNER_BR,
				BORDER_MAX
			};


			// -- A L I A S E S -----------------------------------------------

			/* symbol type */
			using Symbol = xns::array<const char*, BORDER_MAX>;

			/* allocator type */
			using Allocator = xns::allocator<char>;


			// -- M E M B E R S -----------------------------------------------

			/* cached border sequence */
			xns::cstring _border;


			// -- S T A T I C  M E M B E R S ----------------------------------

			/* symbol array */
			static constinit Symbol _symb;



	};

};


#endif
