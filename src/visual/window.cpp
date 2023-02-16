#include "window.hpp"



/* default constructor */
Xf::Window::Window(void)
:
	_visible{false},
	_active{false},
	_selected{false},
	_depth{0},
	_rect{},
	_parent{nullptr},
	_border{},
	_children{},
	_mode{Xf::Event::instance().new_mode()} {
	// code here...
}

/* rect constructor */
Xf::Window::Window(const Xf::Rect& rect)
:
	_visible{false},
	_active{false},
	_selected{false},
	_depth{0},
	_rect{rect},
	_parent{nullptr},
	_border{rect},
	_children{},
	_mode{Xf::Event::instance().new_mode()} {
	// code here...
}

/* window constructor */
Xf::Window::Window(Window* parent)
:
	_visible{false},
	_active{false},
	_selected{false},
	_depth{0},
	_rect{},
	_parent{parent},
	_border{},
	_children{},
	_mode{Xf::Event::instance().new_mode()} {



	using Ev = Xf::Evntype;

	// set event callback
	_mode.subscribe(Ev::ESC, &Window::exit, this);
}



/* destructor */
Xf::Window::~Window(void) {
	// code here...
}

/* set window */
void Xf::Window::set(const Xf::Rect& rect) {
	// set rect
	_rect = rect;
	// set border
	_border.set(rect);
}

/* exit window */
void Xf::Window::exit(void) {
	std::cout << "exit" << std::endl;
}

/* select left window */
void Xf::Window::select_left(void) {
	if (_parent != nullptr) {
		auto& children = _parent->_children;
		Xf::Event::instance().unstack_mode();
	}
}

/* update window */
void Xf::Window::update(void) {
	// get parent size
	if (_parent != nullptr) {
		_rect.w = _parent->_rect.w * 0.5;
		_rect.h = _parent->_rect.h * 0.5;
		_rect.x = _parent->_rect.x + _parent->_rect.w * 0.25;
		_rect.y = _parent->_rect.y + _parent->_rect.h * 0.25;
		_border.set(_rect);
	}
}

/* draw window */
void Xf::Window::draw(void) {
	// draw border
	_border.draw();


}


