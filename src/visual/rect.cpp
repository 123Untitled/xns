#include "rect.hpp"

/* default constructor */
xns::rect::rect(void) noexcept
: x{0}, y{0}, w{0}, h{0} {
	// code here...
}

/* size and position constructor */
xns::rect::rect(const size_type x, const size_type y, const size_type w, const size_type h) noexcept
: x{x}, y{y}, w{w}, h{h} {
	// code here...
}

/* copy constructor */
xns::rect::rect(const rect& other) noexcept
: x{other.x}, y{other.y}, w{other.w}, h{other.h} {
	// code here...
}

/* move constructor */
xns::rect::rect(rect&& other) noexcept
: rect{other} {
	// code here...
}

/* destructor */
xns::rect::~rect(void) noexcept {
	// code here...
}

/* copy assignment operator */
xns::rect& xns::rect::operator=(const rect& other) noexcept {
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
xns::rect& xns::rect::operator=(rect&& other) noexcept {
	// return copy assignment
	return operator=(other);
}

/* bool operator */
xns::rect::operator bool(void) const noexcept {
	// check if empty
	return !empty();
}

/* bool not operator */
bool xns::rect::operator!(void) const noexcept {
	// check if empty
	return empty();
}

/* equality operator */
bool xns::rect::operator==(const rect& other) const noexcept {
	// check if equal
	return x == other.x && y == other.y && w == other.w && h == other.h;
}

/* empty */
bool xns::rect::empty(void) const noexcept {
	// check if empty
	return w == 0 || h == 0;
}




