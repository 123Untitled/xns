#ifndef XNS_BORDER_HEADER
#define XNS_BORDER_HEADER

#include "array.hpp"
#include "types.hpp"
#include "macros.hpp"
#include "rect.hpp"
#include "escape.hpp"
#include "allocator.hpp"
#include "color.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B O R D E R  C L A S S ----------------------------------------------

	class border final {

		// -- assertions ------------------------------------------------------

		/* check string size vs terminal size */
		static_assert(sizeof(xns::term_size) <= sizeof(xns::string::size_type),
					"): TERMINAL SIZE IS BIGGER THAN STRING SIZE");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::border;

			/* terminal size type */
			using term_size = xns::term_size;

			/* rect type */
			using rect_type = xns::rect<term_size>;

			/* string type */
			using string = xns::string;


			// -- public constructors -----------------------------------------

			/* default constructor */
			border(void) = default;

			/* size and position constructor */
			border(const rect_type&);

			/* copy constructor */
			border(const self&) = default;

			/* move constructor */
			border(self&&) noexcept = default;

			/* destructor */
			~border(void) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) -> self&;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self&;


			// -- public boolean operators ------------------------------------

			/* bool operator */
			explicit operator bool(void) const;

			/* not operator */
			bool operator!(void) const;


			// -- M E T H O D S -----------------------------------------------

			/* draw border */
			void draw(void);

			/* set size and position */
			void set(const rect_type&,
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


			// -- private types -----------------------------------------------

			/* symbol type */
			using symbol = xns::array<const char*, BORDER_MAX>;

			/* allocator type */
			using allocator = xns::allocator<char>;


			// -- private members ---------------------------------------------

			/* cached border sequence */
			string _border;


			// -- S T A T I C  M E M B E R S ----------------------------------

			/* symbol array */
			static constinit symbol _symb;

	};

}

#endif
