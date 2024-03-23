#include "unit_tests.hpp"
#include "xns/visual/window.hpp"
#include "xns/event/event.hpp"
#include "xns/terminal/output.hpp"

static void exit(void) { xns::event::stop_loop(); }
static void render(void) { xns::out::render(); }
static void press_enter(void) { xns::debug::print("enter\n"); }

static xns::evntmode build_events(void) {

	using ev = xns::evntype;

	auto mode = xns::event::shared().new_mode();

	mode.subscribe(ev::ETX,   exit);
	mode.subscribe(ev::MIN_Q, exit);
	mode.subscribe(ev::ESC,   exit);
	mode.subscribe(ev::LOOP,  render);
	mode.subscribe(ev::CR, press_enter);

	//Event::shared().set_mode(mode);
	//xns::event::shared().stack_mode(mode, xns::evntopt::FORCE);
	//Event::shared().stack_mode(mode);

	return mode;
}


auto unit_tests_window(void) -> int {

	auto mode = build_events();

	//WindowManager::new_root();
	//WindowManager::new_split<Xf::vsplit_t>();
	//WindowManager win;

	xns::event::start_loop();
	return 0;
}

#if defined(XNS_TEST_WINDOW)
int main(void) {
	return unit_tests_window();
}
#endif

