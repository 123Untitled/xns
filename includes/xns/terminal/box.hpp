/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_BOX_HEADER
#define XNS_BOX_HEADER

#include "xns/containers/array.hpp"
#include "xns/type_traits/types.hpp"
#include "xns/config/macros.hpp"
#include "xns/graphic/rect.hpp"
#include "xns/terminal/escape.hpp"
#include "xns/memory/allocator.hpp"
#include "xns/color/color.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B O R D E R  C L A S S ----------------------------------------------

	class box final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::box;

			/* size type */
			using size_type = xns::size_t; // before was term_size

			/* rect type */
			using rect_type = xns::rect<size_type>;

			/* string type */
			using string = xns::string;


			// -- public constructors -----------------------------------------

			/* default constructor */
			box(void) = default;

			/* size and position constructor */
			box(const rect_type&);

			/* copy constructor */
			box(const self&) = default;

			/* move constructor */
			box(self&&) noexcept = default;

			/* destructor */
			~box(void) = default;


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

			/* draw box */
			void draw(void);

			/* set size and position */
			void set(const rect_type&,
					const xns::hexcolor color = xns::color::GREY_COLOR);

			/* set box color */
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

			/* cached box sequence */
			string _box;


			// -- S T A T I C  M E M B E R S ----------------------------------

			/* symbol array */
			static constinit symbol _symb;

	};

} // namespace xns

#endif // XNS_BOX_HEADER
