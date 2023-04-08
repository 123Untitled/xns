
// path: src/visual/border.hpp
#include "border.hpp"
#include <iostream>


constinit Xf::Border::SymbolArray Xf::Border::_symbols = { {
		{ 0xe2, 0x94, 0x80 },
		{ 0xe2, 0x94, 0x82 },
		{ 0xe2, 0x95, 0xad },
		{ 0xe2, 0x95, 0xae },
		{ 0xe2, 0x95, 0xb0 },
		{ 0xe2, 0x95, 0xaf }
} };

constexpr const char* _symb[] = {
	"\xe2\x94\x80",
	"\xe2\x94\x82",
	"\xe2\x95\xad",
	"\xe2\x95\xae",
	"\xe2\x95\xb0",
	"\xe2\x95\xaf"
};

/* default constructor */
Xf::Border::Border(void)
: _border{} {
	// code here...
}

/* size and position constructor */
Xf::Border::Border(const Xf::Rect& rect)
: _border{} {
	// call set method
	set(rect);
}

/* copy constructor */
Xf::Border::Border(const Border& other)
: _border{other._border} {
	// code here...
}

/* move constructor */
Xf::Border::Border(Border&& other) noexcept
: _border{Xf::move(other._border)} {
	// code here...
}

/* destructor */
Xf::Border::~Border(void) {
	// code here...
}

/* copy assignment operator */
Xf::Border& Xf::Border::operator=(const Border& other) {
	// check for self assignment
	if (this != &other) {
		// copy border
		_border.operator=(other._border);
	} // return self reference
	return *this;
}

/* move assignment operator */
Xf::Border& Xf::Border::operator=(Border&& other) noexcept {
	// check for self assignment
	if (this != &other) {
		// move border
		_border.operator=(Xf::move(other._border));
	} // return self reference
	return *this;
}

/* bool operator */
Xf::Border::operator bool(void) const {
	// check if border is empty
	return !_border.empty();
}

/* bool not operator */
bool Xf::Border::operator!(void) const {
	// check if border is empty
	return _border.empty();
}

/* draw border */
void Xf::Border::draw(void) {
	// check if border is empty
	if (_border.empty()) { return; }
	// draw border
	Buffer::draw(_border.pointer(), _border.size());
}


void Xf::Border::set(const Xf::Rect& rect) {
	// avoid namespace pollution
	using Esc = Xf::Escape;

	if (rect.empty()) { _DBG("empty rect in border set method"); return;}

	// clear previous border
	_border.clear();

	Xf::Rect::Size x = rect.x;
	Xf::Rect::Size y = rect.y;
	Xf::Rect::Size w = rect.w;
	Xf::Rect::Size h = rect.h;



	// append move position top left corner
	_border.append(Esc::get<Xf::move_position_t>(x, y));
	// append top left corner
	_border.append(_symb[CORNER_TL], 3);
	// append top border
	for (Size i = 1; i < w - 1; ++i) {
		_border.append(_symb[LINE_H], 3);
	}
	// append top right corner
	_border.append(_symb[CORNER_TR], 3);

	// append move position bottom left corner
	_border.append(Esc::get<Xf::move_position_t>(x, y + h - 1));

	// append bottom left corner
	_border.append(_symb[CORNER_BL], 3);

	// append bottom border
	for (Size i = 1; i < w - 1; ++i) {
		_border.append(_symb[LINE_H], 3);
	}
	// append bottom right corner
	_border.append(_symb[CORNER_BR], 3);

	UInt32 y_pos = y + h - 1;
	// append left vertical border
	for (Size i = y + 1; i < y_pos; ++i) {
		// append move position left border
		_border.append(Esc::get<Xf::move_position_t>(x, i));
		// append left vertical border
		_border.append(_symb[LINE_V], 3);
	}

	UInt32 x_pos = x + w - 1;
	// append right vertical border
	for (Size i = y + 1; i < y_pos; ++i) {
		// append move position right border
		_border.append(Esc::get<Xf::move_position_t>(x_pos, i));
		// append right vertical border
		_border.append(_symb[LINE_V], 3);
	}
}


