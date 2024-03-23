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

#ifndef XNS_COLOR_HEADER
#define XNS_COLOR_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/math/math.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {




	// using hexcolor = xns::u32;

	struct rgb final {
		xns::u8 r;
		xns::u8 g;
		xns::u8 b;
	};

	struct rgba final {
		xns::u8 r;
		xns::u8 g;
		xns::u8 b;
		xns::u8 a;
	};


	auto lch_to_rgb(const xns::f64, const xns::f64, const xns::f64) -> xns::rgb;



	class hexcolor final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = hexcolor;

			/* integer type */
			using integer = xns::u32;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr hexcolor(void) noexcept
			: _color{0} {}

			/* integer constructor */
			inline constexpr hexcolor(const integer color) noexcept
			: _color{color} {}

			/* rgb constructor */
			inline constexpr hexcolor(const xns::rgb& color) noexcept
			: _color{static_cast<integer>((color.r << 16) | (color.g << 8) | (color.b))} {}

			/* rgba constructor */
			inline constexpr hexcolor(const xns::rgba& color) noexcept
			: _color{static_cast<integer>((color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b))} {}

			/* copy constructor */
			inline constexpr hexcolor(const self& other) noexcept
			: _color{other._color} {}

			/* destructor */
			inline ~hexcolor(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline auto operator=(const self& other) noexcept -> hexcolor& {
				_color = other._color;
				return *this;
			}

			// -- public conversion operators ---------------------------------

			/* integer conversion operator */
			inline constexpr operator integer(void) const noexcept {
				return _color;
			}

			/* rgb conversion operator */
			inline constexpr operator xns::rgb(void) const noexcept {
				return xns::rgb{static_cast<xns::u8>((_color >> 16) & 0xFF),
								static_cast<xns::u8>((_color >> 8 ) & 0xFF),
								static_cast<xns::u8>( _color        & 0xFF)
				};
			}

			/* rgba conversion operator */
			inline constexpr operator xns::rgba(void) const noexcept {
				return xns::rgba{static_cast<xns::u8>((_color >> 24) & 0xFF),
								 static_cast<xns::u8>((_color >> 16) & 0xFF),
								 static_cast<xns::u8>((_color >> 8 ) & 0xFF),
								 static_cast<xns::u8>( _color        & 0xFF)
				};
			}


		private:

			// -- private members ---------------------------------------------

			/* color */
			integer _color;

	};







	// -- C O L O R  C L A S S ------------------------------------------------

	class color final {

		public:

			// -- A L I A S E S -----------------------------------------------


			enum : xns::u32 {

				LOWLIGHT_COLOR		= 0x414868,
				DARK_GREY_COLOR		= 0x636363,
				BCKGRND_COLOR		= 0x1F1F1F,
				GREY_COLOR			= 0x7F7F7F,
				WHITE_COLOR			= 0xE5E5E5,
				GREEN_COLOR			= 0x37FFDA,
				RED_COLOR			= 0xFF8BA5
			};


			// -- public static methods ---------------------------------------

			/* to hexcolor */
			// template <bool alpha = false>
			// static inline auto to_hex(const xns::u8 red, const xns::u8 green, const xns::u8 blue) noexcept -> xns::hexcolor {
			// 	// check if alpha is true
			// 	if constexpr (alpha == true) {
			// 		// bitshift the values to the correct position
			// 		return (0xFF << 24) | (red << 16) | (green << 8) | blue;
			// 	} // else return the color without alpha
			// 	else { return (red << 16) | (green << 8) | blue; }
			// }
			//
			// /* to hexcolor */
			// static inline auto to_hex(const xns::u8 red,
			// 						  const xns::u8 green,
			// 						  const xns::u8 blue,
			// 						  const xns::u8 alpha) noexcept -> xns::hexcolor {
			// 	// bitshift the values to the correct position
			// 	return (alpha << 24) | (red << 16) | (green << 8) | blue;
			// }
			//
			// /* to hexcolor */
			// static inline auto to_hex(const rgb& color) noexcept -> xns::hexcolor {
			// 	// bitshift the values to the correct position
			// 	return (color.r << 16) | (color.g << 8) | color.b;
			// }
			//
			// /* to hexcolor */
			// static inline auto to_hex(const rgba& color) noexcept -> xns::hexcolor {
			// 	// bitshift the values to the correct position
			// 	return (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
			// }
			//
			// /* to rgb */
			// static inline auto to_rgb(const hexcolor color) noexcept -> xns::rgb {
			// 	// bitshift the values to the correct position
			// 	return xns::rgb{static_cast<xns::u8>((color >> 16) & 0xFF),
			// 					static_cast<xns::u8>((color >> 8 ) & 0xFF),
			// 					static_cast<xns::u8>( color        & 0xFF)
			// 	};
			// }
			//
			// /* to rgba */
			// static inline auto to_rgba(const hexcolor color) noexcept -> xns::rgba {
			// 	// bitshift the values to the correct position
			// 	return xns::rgba{static_cast<xns::u8>((color >> 24) & 0xFF),
			// 					 static_cast<xns::u8>((color >> 16) & 0xFF),
			// 					 static_cast<xns::u8>((color >> 8 ) & 0xFF),
			// 					 static_cast<xns::u8>( color        & 0xFF)
			// 	};
			// }




	};
}



#endif
