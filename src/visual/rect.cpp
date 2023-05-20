#include "rect.hpp"

/* default constructor */
Xf::Rect::Rect(void) noexcept
: x{0}, y{0}, w{0}, h{0} {
	// code here...
}

/* size and position constructor */
Xf::Rect::Rect(const Size x, const Size y, const Size w, const Size h) noexcept
: x{x}, y{y}, w{w}, h{h} {
	// code here...
}

/* copy constructor */
Xf::Rect::Rect(const Rect& other) noexcept
: x{other.x}, y{other.y}, w{other.w}, h{other.h} {
	// code here...
}

/* move constructor */
Xf::Rect::Rect(Rect&& other) noexcept
: Rect{other} {
	// code here...
}

/* destructor */
Xf::Rect::~Rect(void) noexcept {
	// code here...
}

/* copy assignment operator */
Xf::Rect& Xf::Rect::operator=(const Rect& other) noexcept {
	// check for self assignment
	if (this != &other) {
		// copy dimension
		w = other.w; h = other.h;
		// copy position
		x = other.x; y = other.y;
	} // return self reference
	return *this;
}

/* move assignment operator */
Xf::Rect& Xf::Rect::operator=(Rect&& other) noexcept {
	// return copy assignment
	return operator=(other);
}

/* bool operator */
Xf::Rect::operator bool(void) const noexcept {
	// check if empty
	return !empty();
}

/* bool not operator */
bool Xf::Rect::operator!(void) const noexcept {
	// check if empty
	return empty();
}

/* equality operator */
bool Xf::Rect::operator==(const Rect& other) const noexcept {
	// check if equal
	return x == other.x && y == other.y && w == other.w && h == other.h;
}

/* empty */
bool Xf::Rect::empty(void) const noexcept {
	// check if empty
	return w == 0 || h == 0;
}




