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

#ifndef XNS_ESCAPE_HEADER
#define XNS_ESCAPE_HEADER

#include "xns/config/macros.hpp"

#include "xns/type_traits/types.hpp"
#include "xns/color/color.hpp"
#include "xns/terminal/output.hpp"
#include "xns/containers/array.hpp"
#include "xns/string/string.hpp"
#include "xns/utility/numeric_limits.hpp"

// operating system headers
#include <unistd.h>


// include for struct winsize
#include <sys/ioctl.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	/* term size type */
	using term_size = decltype(xns::declval<struct winsize>().ws_col);

	struct move_home {
		___xns_not_instantiable(move_home);
		static constexpr xns::array esc {'\x1b' , '[', 'H'};
	};

	struct erase_screen {
		___xns_not_instantiable(erase_screen);
		static constexpr xns::array esc {'\x1b', '[', '2', 'J'};
	};

	struct erase_line {
		___xns_not_instantiable(erase_line);
		static constexpr xns::array esc {'\x1b', '[', '2', 'K'};
	};



	template <typename ___type = char>
	struct move_up {


		private:

			enum : unsigned {
				___digits = xns::limits<___type>::digits(),
				___size   = ___digits + 3
			};


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::move_up<___type>;

			/* array type */
			using array = xns::array<___type, ___size>;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr move_up(void) noexcept
			: _esc{'\x1b', '[', '0', 'A'} {
			}

			/* value constructor */
			constexpr move_up(const ___type ___n)
			: _esc{_init()} {
				// here implment itoa...
			}

			/* copy constructor */
			constexpr move_up(const self&) noexcept = default;

			/* move constructor */
			constexpr move_up(self&&) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) noexcept -> self& = default;

			/* move assignment operator */
			auto operator=(self&&) noexcept -> self& = default;


			// -- public accessors --------------------------------------------

			/* data */
			constexpr auto data(void) const noexcept -> const char* {
				return _esc.data();
			}

			/* size */
			constexpr auto size(void) const noexcept -> typename array::size_type {
				return _esc.size();
			}


		private:

			static constexpr auto _init(void) -> xns::array<char, xns::limits<___type>::digits() + 3> {
				// move up escape sequence: \x1b[0A
				constexpr auto ___lm = xns::limits<___type>::digits();
				xns::array<char, ___lm + 3> ___esc {'\x1b', '['};
				___esc[2 + ___lm] = 'A';
				return ___esc;
			}


			// -- private members ---------------------------------------------

			/* escape */
			xns::array<char, ___size> _esc;
	};


	enum : unsigned {
		move_home,
		erase_screen,
		erase_line,
		erase_to_end,
		erase_from_start,
		enter_screen,
		exit_screen,
		save_screen,
		restore_screen,
		reset_style,
		show_cursor,
		hide_cursor,
		request_position,
		cursor_beam,
		cursor_underline,
		cursor_block,
		color_rgb,
		color_hex,
		move_position,
		move_x,
		move_left,
		move_right,
	};

	template <typename... ___escs>
	class esc final {
	};


	//inline xns::esc<xns::move_up> a{};





	// -- E S C A P E ---------------------------------------------------------

	class escape final {


		private:

			// -- private types -----------------------------------------------

			/* string type */
			using string = xns::string;

			/* string view type */
			using view = xns::string_view;

			/* character type */
			using char_t = typename string::value_type;

			/* terminal size */
			using size_type = xns::size_t;


		public:

			// -- private types -----------------------------------------------



			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			___xns_not_instantiable(escape);


			// -- public static methods ---------------------------------------

			/* move home */
			static consteval auto move_home(void) noexcept -> xns::string_view {
				return {"\x1b[H"};
			}

			/* erase screen */
			static consteval auto erase_screen(void) noexcept -> xns::string_view {
				return {"\x1b[2J"};
			}

			/* erase line */
			static consteval auto erase_line(void) noexcept -> xns::string_view {
				return {"\x1b[2K"};
			}

			/* erase to end of line */
			static consteval auto erase_to_end(void) noexcept -> xns::string_view {
				return {"\x1b[0K"};
			}

			/* erase from start of line */
			static consteval auto erase_from_start(void) noexcept -> xns::string_view {
				return {"\x1b[1K"};
			}

			/* enter screen */
			static consteval auto enter_screen(void) noexcept -> xns::string_view {
				return {"\x1b[?1049h"};
			}

			/* exit screen */
			static consteval auto exit_screen(void) noexcept -> xns::string_view {
				return {"\x1b[?1049l"};
			}

			/* save screen */
			static consteval auto save_screen(void) noexcept -> xns::string_view {
				return {"\x1b[?47h"};
			}

			/* restore screen */
			static consteval auto restore_screen(void) noexcept -> xns::string_view {
				return {"\x1b[?47l"};
			}

			/* reset style */
			static consteval auto reset_style(void) noexcept -> xns::string_view {
				return {"\x1b[0m"};
			}


			/* show cursor */
			static consteval auto show_cursor(void) noexcept -> xns::string_view {
				return {"\x1b[?25h"};
			}

			/* hide cursor */
			static consteval auto hide_cursor(void) noexcept -> xns::string_view {
				return {"\x1b[?25l"};
			}

			/* request position */
			static constexpr auto request_position(void) noexcept -> xns::string_view {
				return {"\x1b[6n"};
			}


			/* cursor beam */
			static consteval auto cursor_beam(void) noexcept -> xns::string_view {
				return {"\x1b[5 q"};
			}

			/* cursor underline */
			static consteval auto cursor_underline(void) noexcept -> xns::string_view {
				return {"\x1b[3 q"};
			}

			/* cursor block */
			static consteval auto cursor_block(void) noexcept -> xns::string_view {
				return {"\x1b[1 q"};
			}



			// -- S P E C I A L  E S C A P E  S E Q U E N C E S ---------------

			/* request position */
			static bool request_position(size_type&, size_type&);


			/* move position */
			static xns::string move_position(size_type, size_type);

			/* move x position */
			static const string& move_x(size_type);

			/* move left */
			static string move_left(const size_type = 1);

			/* move right */
			static string move_right(const size_type = 1);

			/* move up */
			static string move_up(const size_type = 1);

			/* move down */
			static string move_down(const size_type = 1);


		private:

			/* move direction */
			static string _move_direction(size_type, const char_t);


		public:

			/* hex color */
			static string hex_color(const xns::hexcolor, const bool = true);

			/* rgb color */
			static string rgb_color(xns::u8, xns::u8, xns::u8, const bool = true);

			/* rgb color */
			static string rgb_color(const xns::rgb&, const bool = true);


		private:




			class req_pos final {

				public:

					static bool request(size_type& x, size_type& y) {

						// create request
						req_pos req{x, y};


						// return success
						return true;
					}



				private:

					// -- private enums ---------------------------------------

					//enum : size_type {
					//	BASE = 10,
					//	ZERO = 48
					//};

					// -- private lifecycle -----------------------------------

					/* size constructor */
					req_pos(size_type& x, size_type& y)
					: _state{nullptr}, _c{0}, _n{&y}, _x{x}, _y{y} {
					};

					/* destructor */
					~req_pos(void) = default;

					bool escape(void) {
						return _c == '\x1b'
							? _state = &req_pos::bracket, true
							: false;
					}

					bool bracket(void) {
						return _c == '['
							? _state = &req_pos::number, true
							: false;
					}

					bool number(void) {
						if ((_c ^ 48) < 10) {
							*_n = (*_n * 10) + (static_cast<size_type>(_c) - 48);
							return true;
						}
						else if (_c == ';') {
							_n = &_x;
							return true;
						}
						return false;
					}

					using proto = bool(req_pos::*)(void);


					// -- private members -------------------------------------

					proto _state;

					/* current character */
					char _c;

					/* current number */
					size_type* _n;

					/* x position */
					size_type& _x;

					/* y position */
					size_type& _y;



			};




	};

}





#endif
