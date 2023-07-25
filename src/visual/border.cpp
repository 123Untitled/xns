// path: src/visual/border.hpp
#include "border.hpp"


constinit xns::border::symbol xns::border::_symb = {
	"\xe2\x94\x80",
	"\xe2\x94\x82",
	"\xe2\x95\xad",
	"\xe2\x95\xae",
	"\xe2\x95\xb0",
	"\xe2\x95\xaf"
};


/* default constructor */
xns::border::border(void)
: _border{} {
	// code here...
}

/* size and position constructor */
xns::border::border(const rect& rect)
: _border{} {
	// call set method
	set(rect);
}

/* copy constructor */
xns::border::border(const border& other)
: _border{other._border} {
	// code here...
}

/* move constructor */
xns::border::border(border&& other) noexcept
: _border{xns::move(other._border)} {
	// code here...
}

/* destructor */
xns::border::~border(void) {
	// code here...
}

/* copy assignment operator */
xns::border& xns::border::operator=(const border& other) {
	// check for self assignment
	if (this != &other) {
		// copy border
		_border.operator=(other._border);
	} // return self reference
	return *this;
}

/* move assignment operator */
xns::border& xns::border::operator=(border&& other) noexcept {
	// check for self assignment
	if (this != &other) {
		// move border
		_border.operator=(xns::move(other._border));
	} // return self reference
	return *this;
}

/* bool operator */
xns::border::operator bool(void) const {
	// check if border is empty
	return !_border.empty();
}

/* bool not operator */
bool xns::border::operator!(void) const {
	// check if border is empty
	return _border.empty();
}

/* draw border */
void xns::border::draw(void) {
	// check if border is empty
	if (_border.empty()) { return; }
	// draw border
	//Buffer::draw(_border.pointer(), _border.size());
	xns::output::write(_border);
}


void xns::border::set(const rect& rect, const xns::hexcolor color) {
	// avoid namespace pollution
	using esc = xns::escape;

	if (rect.empty()) { _DBG("empty rect in border set method"); return;}

	// clear previous border
	_border.clear();

	auto x = rect.x;
	auto y = rect.y;
	auto w = rect.w;
	auto h = rect.h;


	_border.append(esc::hex_color(color));

	// append move position top left corner
	_border.append(esc::move_position(x, y));
	// append top left corner
	_border.append(_symb[CORNER_TL], 3);
	// append top border
	for (term_size i = 1; i < w - 1; ++i) {
		_border.append(_symb[LINE_H], 3);
	}
	// append top right corner
	_border.append(_symb[CORNER_TR], 3);

	// append move position bottom left corner
	//_border.append(Esc::get<Xf::move_position_t>(x, y + h - 1));
	_border.append(esc::move_position(x, y + h - 1));

	// append bottom left corner
	_border.append(_symb[CORNER_BL], 3);

	// append bottom border
	for (term_size i = 1; i < w - 1; ++i) {
		_border.append(_symb[LINE_H], 3);
	}
	// append bottom right corner
	_border.append(_symb[CORNER_BR], 3);

	term_size y_pos = y + h - 1;
	// append left vertical border
	for (term_size i = y + 1; i < y_pos; ++i) {
		// append move position left border
		//_border.append(Esc::get<Xf::move_position_t>(x, i));
		_border.append(esc::move_position(x, i));
		// append left vertical border
		_border.append(_symb[LINE_V], 3);
	}

	term_size x_pos = x + w - 1;
	// append right vertical border
	for (term_size i = y + 1; i < y_pos; ++i) {
		// append move position right border
		//_border.append(Esc::get<Xf::move_position_t>(x_pos, i));
		_border.append(esc::move_position(x_pos, i));
		// append right vertical border
		_border.append(_symb[LINE_V], 3);
	}

	_border.append(esc::reset_style());
}


