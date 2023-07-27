#include "unit_tests.hpp"
#include "window.hpp"
#include "event.hpp"
#include "output.hpp"

static void exit(void) { xns::event::stop_loop(); }
static void render(void) { xns::out::flush(); }
static void press_enter(void) { xns::debug::print("enter\n"); }

static xns::evntmode build_events(void) {

	using ev = xns::evntype;

	auto mode = xns::event::instance().new_mode();

	mode.subscribe(ev::ETX,   exit);
	mode.subscribe(ev::MIN_Q, exit);
	mode.subscribe(ev::ESC,   exit);
	mode.subscribe(ev::LOOP,  render);
	mode.subscribe(ev::CR, press_enter);

	//Event::instance().set_mode(mode);
	xns::event::instance().stack_mode(mode, xns::evntopt::FORCE);
	//Event::instance().stack_mode(mode);

	return mode;
}

template <>
bool UT::unit_tests<"window">(void) {
	using namespace Xf;

	auto mode = build_events();

	//WindowManager::new_root();
	//WindowManager::new_split<Xf::vsplit_t>();
	//WindowManager win;

	xns::event::start_loop();
	return true;
}

