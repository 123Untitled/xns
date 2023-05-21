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


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- B O R D E R  C L A S S ----------------------------------------------

	class border final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* size type */
			using size_type = xns::size_t;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			border(void);

			/* size and position constructor */
			border(const xns::rect& rect);

			/* copy constructor */
			border(const border& other);

			/* move constructor */
			border(border&& other) noexcept;

			/* destructor */
			~border(void);


			// -- O P E R A T O R S -------------------------------------------

			/* copy assignment operator */
			border& operator=(const border& other);

			/* move assignment operator */
			border& operator=(border&& other) noexcept;

			/* bool operator */
			explicit operator bool(void) const;

			/* bool not operator */
			bool operator!(void) const;


			// -- M E T H O D S -----------------------------------------------

			/* draw border */
			void draw(void);

			/* set size and position */
			void set(const xns::rect& rect,
					const xns::hexcolor color = xns::color::GREY_COLOR);

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
			using symbol = xns::array<const char*, BORDER_MAX>;

			/* allocator type */
			using allocator = xns::allocator<char>;


			// -- M E M B E R S -----------------------------------------------

			/* cached border sequence */
			xns::cstring _border;


			// -- S T A T I C  M E M B E R S ----------------------------------

			/* symbol array */
			static constinit symbol _symb;



	};

};


#endif
