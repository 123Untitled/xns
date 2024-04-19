#include "xns/terminal/box.hpp"


/* rect constructor */
xns::box::box(const rect_type& rect)
: _box{} {
	// call set method
	set(rect);
}

/* draw */
void xns::box::draw(void) {
	// check if box is empty
	if (_box.empty()) { return; }
	// draw box
	xns::out::write(_box);
}

/* set */
void xns::box::set(const rect_type& rect, const xns::hexcolor color) {
	// avoid namespace pollution
	using esc = xns::escape;

	if (rect.empty()) { return; }

	// clear previous box
	_box.clear();

	auto x = rect.x();
	auto y = rect.y();
	auto w = rect.w();
	auto h = rect.h();


	_box.append(esc::hex_color(color));

	// append move position top left corner
	_box.append(esc::move_position(x, y));
	// append top left corner
	_box.append(_symb[CORNER_TL], 3);
	// append top box
	for (size_type i = 1; i < w - 1; ++i) {
		_box.append(_symb[LINE_H], 3);
	}
	// append top right corner
	_box.append(_symb[CORNER_TR], 3);

	// append move position bottom left corner
	//_box.append(Esc::get<Xf::move_position_t>(x, y + h - 1));
	_box.append(esc::move_position(x, y + h - 1));

	// append bottom left corner
	_box.append(_symb[CORNER_BL], 3);

	// append bottom box
	for (size_type i = 1; i < w - 1; ++i) {
		_box.append(_symb[LINE_H], 3);
	}
	// append bottom right corner
	_box.append(_symb[CORNER_BR], 3);

	size_type y_pos = y + h - 1;
	// append left vertical box
	for (size_type i = y + 1; i < y_pos; ++i) {
		// append move position left box
		//_box.append(Esc::get<Xf::move_position_t>(x, i));
		_box.append(esc::move_position(x, i));
		// append left vertical box
		_box.append(_symb[LINE_V], 3);
	}

	size_type x_pos = x + w - 1;
	// append right vertical box
	for (size_type i = y + 1; i < y_pos; ++i) {
		// append move position right box
		//_box.append(Esc::get<Xf::move_position_t>(x_pos, i));
		_box.append(esc::move_position(x_pos, i));
		// append right vertical box
		_box.append(_symb[LINE_V], 3);
	}

	_box.append(esc::reset_style());
}

