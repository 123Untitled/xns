#include "unit_tests.hpp"
#include "midi.hpp"

/* unit test */
template <>
int UT::unit_tests<"midi">(void) {

	midi::server::shared();
	//midi::port port{};

	return 0;
}

#if defined(XNS_TEST_MIDI)
int main(void) {
	return UT::unit_tests<"midi">();
}
#endif
