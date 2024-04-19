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


	// -- B O X ---------------------------------------------------------------

	class box final {

		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::box;


		public:

			// -- public types ------------------------------------------------

			/* size type */
			using size_type = xns::size_t; // before was term_size

			/* rect type */
			using rect_type = xns::rect<size_type>;

			/* string type */
			using string = xns::string;


			// -- public constructors -----------------------------------------

			/* default constructor */
			box(void) = default;

			/* rect constructor */
			box(const rect_type&);

			/* copy constructor */
			box(const ___self&) = default;

			/* move constructor */
			box(___self&&) noexcept = default;

			/* destructor */
			~box(void) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) -> self&;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> self&;


			// -- public methods ----------------------------------------------

			/* draw */
			void draw(void);

			/* set */
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


			// -- private static members --------------------------------------

			/* symbol array */
			static constexpr symbol _symb {
				"\xe2\x94\x80",
				"\xe2\x94\x82",
				"\xe2\x95\xad",
				"\xe2\x95\xae",
				"\xe2\x95\xb0",
				"\xe2\x95\xaf"
			};

	}; // class box

} // namespace xns

#endif // XNS_BOX_HEADER
