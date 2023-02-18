#include "window.hpp"

// -- W I N D O W  B A S E  C L A S S -----------------------------------------

/* rect constructor */
Xf::WindowBase::WindowBase(const Xf::Rect& rect)
: _rect{rect}, _border{rect} {
	// code here...
}


// -- W I N D O W  M A N A G E R ----------------------------------------------

Xf::UniquePtr<Xf::WindowBase> Xf::WindowManager::_root{};

/* new root window */
void Xf::WindowManager::new_root(void) noexcept {
	// code here...
	Term::Wsize width, height;
	Term::get_terminal_size(width, height);

	//_root.set_pointer(new Window<pane_one_t, hsplit_t>{{0, 0, width, height}});
	_root.set_pointer(new Window<pane_one_t, vsplit_t>{{0, 0, width, height}});
}


/* draw all */
void Xf::WindowManager::draw_all(void) noexcept {
	// code here...
	int i = 0;
	_root->draw(i);
	Xf::Debug::print("draw win: %d\n", i);
}

/* debug window */
void Xf::WindowManager::debug_window(void) noexcept {
	// code here...
	int i = 0;
	_root->debug(i);
}

