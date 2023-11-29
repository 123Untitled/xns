#include "unit_tests.hpp"
#include "bjorklund.hpp"

#include "midi.hpp"
#include "benchmark.hpp"
#include "random.hpp"

std::vector<xns::size_t> bjorklund_github(xns::size_t step, xns::size_t pulse) {
	xns::size_t back = step - pulse;
	xns::size_t remainder = back % pulse;
	xns::size_t per_pulse = (xns::size_t) floor(back / pulse);
	xns::size_t noskip = (remainder == 0) ? 0 : (xns::size_t) floor(pulse / remainder);
	xns::size_t skipXTime = (noskip == 0) ? 0 : (xns::size_t) floor((pulse - remainder)/noskip);

	std::vector<xns::size_t> rhythm;

	xns::size_t count = 0;
	xns::size_t skipper = 0;

	for (xns::size_t i = 1; i <= step; i++) {
		if (count == 0) {
			rhythm.push_back(1);
			count = per_pulse;
			if (remainder > 0 && skipper == 0) {
				count++;
				remainder--;
				skipper = (skipXTime > 0) ? noskip : 0;
				skipXTime--;
			} else {
				skipper--;
			}
		} else {
			rhythm.push_back(0);
			count--;
		}
	}
	return rhythm;
}

void printv(const std::vector<int>& v) {
	for (auto& i : v) {
		std::cout << (i ? "\x1b[32mx\x1b[0m" : "-");
	}
	std::cout << std::endl;
}
void printv(const xns::vector<xns::size_t>& v) {
	for (auto& i : v) {
		std::cout << (i ? "\x1b[32mx\x1b[0m" : "-");
	}
	std::cout << std::endl;
}

/* unit test */
template <>
int UT::unit_tests<"bjorklund">(void) {

	//auto x = xns::bjorklund::generate(13, 5);
	//printv(x);
	//return 0;



	xns::benchmark<5> bench;

	xns::size_t checksum = 0;
	xns::size_t ite      = 10000;
	xns::size_t range    = 500;

	std::vector<std::pair<xns::size_t, xns::size_t>> params;

	for (xns::size_t i = 0; i < ite; ++i) {
		std::pair<xns::size_t, xns::size_t> p;
		p.first = (xns::random::integral<xns::size_t>() % (range   - 1)) + 1;
		p.second = xns::random::integral<xns::size_t>() % (p.first - 1)  + 1;
		params.push_back(p);
		//std::cout << "step = " << p.first << ", pulse = " << p.second << std::endl;
	}

	//xns::size_t err = 0;
	//
	//for (auto& [step, pulse] : params) {
	//	auto bgit = bjorklund_github(step, pulse);
	//	auto xnsb = xns::bjorklund::generate(step, pulse);
	//	std::vector<int> xnsb2;
	//	for (auto v : xnsb)
	//		xnsb2.push_back(v);
	//
	//	if (bgit != xnsb2) {
	//		++err;
	//		std::cout << "step = " << step << ", pulse = " << pulse << std::endl;
	//		std::cout << "bjorklund_github         = ";
	//		printv(bgit);
	//		std::cout << "xns::bjorklund::generate = ";
	//		printv(xnsb2);
	//		std::cout << std::endl;
	//	}
	//
	//}

	//std::cout << "errors = " << err << " on " << ite << std::endl;



	bench.run("git bjork", [&](void) {

		for (auto& [step, pulse] : params) {
			auto bgit = bjorklund_github(step, pulse);
			checksum += bgit.size();
		}

	});

	bench.run("xns bjork", [&](void) {

		for (auto& [step, pulse] : params) {
			auto xnsb = xns::bjorklund::generate(step, pulse);
			checksum += xnsb.size();
		}

	});

	bench.result("bjorklund");
	std::cout << "checksum = " << checksum << std::endl;



	return 0;
}





#if defined(XNS_TEST_BJORKLUND)
int main(int argc, char** argv) {

	//return UT::unit_tests<"bjorklund">();


	using seq_t = xns::vector<xns::size_t>;

	if (argc != 4) return 1;

	auto seq = xns::bjorklund::generate((xns::size_t)std::atoi(argv[1]), (xns::size_t)std::atoi(argv[2]), (xns::size_t)std::atoi(argv[3]));
	//auto seq = xns::bjorklund::generate(13, 5, 2);
	printv(seq);
	return 0;

	//return 0;

	seq_t kick = xns::make_vector<xns::size_t>(1U,0U,0U,0U,1U,0U,0U,0U,  1U,0U,0U,0U,1U,0U,0U,0U);
	seq_t hit  = xns::make_vector<xns::size_t>(1U,0U,0U,1U);

	auto& md = midi::server::shared();

	sleep(2);

	xns::terminal::raw(xns::VFlag::NON_BLOCKING);

	xns::size_t i = 0;
	xns::size_t j = 0;
	xns::size_t l = 0;

	while (true) {
		if (i == seq.size())
			i = 0;
		if (j == kick.size())
			j = 0;
		if (l == hit.size())
			l = 0;

		char c = '\0';
		::read(0, &c, 1);
		if (c == 'q') {
			xns::terminal::restore();
			return 0;
		}
		if (kick[j]) {
			md.add_midi(MIDI1UPNoteOn(0, 0, 60, 100));
			md.add_midi(MIDI1UPNoteOff(0, 0, 60, 0));
		}
		if (hit[l]) {
			md.add_midi(MIDI1UPNoteOn(0, 0, 62, 100));
			md.add_midi(MIDI1UPNoteOff(0, 0, 62, 0));
		}
		if (seq[i]) {
			md.add_midi(MIDI1UPNoteOn(0, 0, 61, 100));
			md.add_midi(MIDI1UPNoteOff(0, 0, 61, 0));
		}
		if (seq[i] || kick[j] || hit[l])
			md.send_midi();
		++i; ++j; ++l;
		usleep(120000);
	}

	xns::terminal::restore();

	return 0;


}
#endif

