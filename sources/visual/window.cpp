#include "xns/visual/window.hpp"





//// -- W I N D O W  B A S E  C L A S S -----------------------------------------
//
///* rect constructor */
//Xf::WindowBase::WindowBase(const Xf::Rect& rect)
//: _rect{rect}, _border{rect} {
//	// code here...
//}
//
//
//// -- W I N D O W  M A N A G E R ----------------------------------------------
//
//Xf::UniquePtr<Xf::WindowBase> Xf::WindowManager::_root{};
//
///* new root window */
//void Xf::WindowManager::new_root(void) noexcept {
//	// code here...
//	Term::Wsize width, height;
//	Term::get_terminal_size(width, height);
//
//	using Win = Window<pane_one_t, vsplit_t>;
//
//	_root.make<Win>(Xf::Rect{0, 0, width, height});
//}
//
//
///* draw all */
//void Xf::WindowManager::draw_all(void) noexcept {
//	// code here...
//	int i = 0;
//	_root->draw(i);
//	Xf::Debug::print("draw win: %d\n", i);
//}
//
///* debug window */
//void Xf::WindowManager::debug_window(void) noexcept {
//	// code here...
//	int i = 0;
//	_root->debug(i);
//}
//
//
//
//// -- W I N D O W  B A S E  C L A S S -----------------------------------------
//
/////* rect constructor */
////Xf::WinBase::WinBase(const Xf::Rect& rect)
////: _rect{rect}, _border{rect} {
////	// code here...
////}
////
////
////// -- W I N N O D E  C L A S S ------------------------------------------------
////
////Xf::WinNode::WinNode(const Xf::Rect& rect)
////: WinBase{rect},
////  _north{nullptr}, _south{nullptr}, _east{nullptr}, _west{nullptr},
////  _mode{Xf::Event::instance().new_mode()} {
////	// code here...
////}
////
////
/////* draw */
////void Xf::WinNode::draw(const WinNode* current) {
////	if (this == current) {
////		Xf::Escape::draw<Xf::Escape::hex_color_t>(0x37FFDA, true);
////	}
////	// draw border
////	_border.draw();
////	// draw children
////	Xf::Escape::draw<Xf::Escape::reset_style_t>();
////
////	if (_south) { _south->draw(current); }
////	if (_east ) { _east ->draw(current); }
////}
////
////void Xf::WinNode::clear(void) {
////	std::cout << "clearing node" << std::endl;
////	if (_south) { _south->clear(); }
////	if (_east)  { _east ->clear(); }
////	delete this;
////}
////
////
////// -- W I N D O W  M A N A G E R ----------------------------------------------
////
/////* default constructor */
////Xf::WindowManager::WindowManager(void)
////: _root{nullptr}, _current{nullptr}, _mode{Xf::Event::instance().new_mode()} {
////
////	// avoid namespace pollution
////	using namespace Xf;
////
////	Term::Wsize width, height;
////	Term::get_terminal_size(width, height);
////
////	_root = new Xf::WinNode{{0, 0, width, height}};
////	_current = _root;
////	_root->draw(_current);
////
////	using Ev = Evntype;
////
////	_mode.subscribe(Ev::LOOP,  &WindowManager::draw_all,   this);
////	_mode.subscribe(Ev::ESC,   &WindowManager::exit,       this);
////	_mode.subscribe(Ev::CR,    &WindowManager::vsplit,     this);
////	_mode.subscribe(Ev::SPACE, &WindowManager::hsplit,     this);
////	_mode.subscribe(Ev::LEFT,  &WindowManager::move_left,  this);
////	_mode.subscribe(Ev::RIGHT, &WindowManager::move_right, this);
////	_mode.subscribe(Ev::UP,    &WindowManager::move_up,    this);
////	_mode.subscribe(Ev::DOWN,  &WindowManager::move_down,  this);
////
////	Xf::Event::instance().stack_mode(_mode, Evntopt::FORCE);
////}
////
/////* destructor */
////Xf::WindowManager::~WindowManager(void) {
////	if (_root) { _root->clear(); }
////}
////
////void Xf::WindowManager::draw_all(void) {
////	// code here...
////	if (_root && _current) { _root->draw(_current); }
////}
////
////void Xf::WindowManager::exit(void) {
////	// code here...
////	Xf::Input::stop_loop();
////}
////
////void Xf::WindowManager::vsplit(void) {
////	if (!_current) { return; }
////
////	Rect& r = _current->_rect;
////
////	const Size p_w1 = ((r.w * 50) / 100) - 1;
////	const Size p_w2 = r.w - (p_w1 + 1);
////
////	Rect r1{r.x, r.y, p_w1, r.h};
////	Rect r2{r.x + p_w1 + 1, r.y, p_w2, r.h};
////
////	_current->_rect = r1;
////	_current->_border.set(r1);
////
////	WinNode* new_node = new WinNode{r2};
////
////
////	new_node->_east = _current->_east;
////	_current->_east = new_node;
////	if (new_node->_east) {
////		new_node->_east->_west = new_node;
////	}
////
////	new_node->_west = _current;
////	new_node->_north = _current->_north;
////	new_node->_south = _current->_south;
////
////	draw_all();
////}
////
////void Xf::WindowManager::hsplit(void) {
////	if (!_current) { return; }
////
////	Rect& r = _current->_rect;
////
////	const Size p_h1 = r.h * 50 / 100;
////	const Size p_h2 = r.h - p_h1;
////
////	Rect r1{r.x, r.y, r.w, p_h1};
////	Rect r2{r.x, r.y + p_h1, r.w, p_h2};
////
////	_current->_rect = r1;
////	_current->_border.set(r1);
////
////	WinNode* new_node = new WinNode{r2};
////
////	new_node->_south = _current->_south;
////	_current->_south = new_node;
////	if (new_node->_south) {
////		new_node->_south->_north = new_node;
////	}
////
////	new_node->_north = _current;
////	new_node->_east = _current->_east;
////	new_node->_west = _current->_west;
////
////	draw_all();
////}
////
////
/////* move left */
////void Xf::WindowManager::move_left(void) {
////	if (!_current) { return; }
////	if (!_current->_west) { return; }
////	_current = _current->_west;
////}
////
/////* move right */
////void Xf::WindowManager::move_right(void) {
////	if (!_current) { return; }
////	if (!_current->_east) { return; }
////	_current = _current->_east;
////}
////
/////* move up */
////void Xf::WindowManager::move_up(void) {
////	if (!_current) { return; }
////	if (!_current->_north) { return; }
////	_current = _current->_north;
////}
////
/////* move down */
////void Xf::WindowManager::move_down(void) {
////	if (!_current) { return; }
////	if (!_current->_south) { return; }
////	_current = _current->_south;
////}
//
//
//
//
//
//
//
//
//
//
