#include "unit_tests.hpp"
#include "midi.hpp"

/* unit test */

auto unit_tests_midi(void) -> int {

	midi::server::shared();
	//midi::port port{};

	return 0;
}

#if defined(XNS_TEST_MIDI)
int main(void) {
	return unit_tests_midi();
}
#endif

