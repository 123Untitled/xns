#include "unit_tests.hpp"

static void exit(void) { Xf::Input::stop_loop(); }
static void render(void) { Buffer::render(); }

static Xf::Evntmode build_events(void) {

	using namespace Xf;
	using Ev = Evntype;

	auto mode = Event::instance().new_mode();

	mode.subscribe(Ev::ETX,   exit);
	mode.subscribe(Ev::MIN_Q, exit);
	mode.subscribe(Ev::ESC,   exit);
	mode.subscribe(Ev::LOOP,  render);

	//Event::instance().set_mode(mode);
	Event::instance().stack_mode(mode, Evntopt::FORCE);

	return mode;
}


void Xf::Tests::window_tests(void) {
	using namespace Xf;

	auto mode = build_events();

	WindowManager::new_root();

	Input::start_loop();



}
