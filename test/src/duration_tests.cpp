#include "unit_tests.hpp"
#include "duration.hpp"
#include "string.hpp"
#include "output.hpp"

#include <chrono>


consteval xns::size_t max_len(void) {
	const char* types[] = {
		"nanoseconds", "microseconds", "milliseconds", "seconds",
		"minutes", "hours", "days", "weeks", "months", "years", nullptr };
	xns::size_t max = 0;
	xns::size_t idx = 0;
	while (types[idx] != nullptr) {
		xns::size_t len = 0;
		while (types[idx][len] != '\0') { ++len; }
		if (len > max) { max = len; }
		++idx;
	} return max;
}


template <xns::is_duration from, xns::is_duration to, xns::umax expected>
void test(const xns::string_view& from_name, const xns::string_view& to_name) {

	xns::out::write(from_name.data(), from_name.size());
	for (xns::size_t x = from_name.size(); x < max_len(); ++x) {
		xns::out::write(" ");
	}
	xns::out::write("-> ");
	xns::out::write(to_name.data(), to_name.size());
	for (xns::size_t x = to_name.size(); x < max_len(); ++x) {
		xns::out::write(" ");
	}
	xns::out::write(" : ");

	to _to = xns::duration_cast<to>(from{1});

	if (_to.count() != expected) {
		xns::out::write("\x1b[31mfailed:\x1b[0m ");
		xns::out::write(_to.count());
		xns::out::write(" != [");
		xns::out::write(expected);
		xns::out::write("]\n");
	}
	else {
		xns::out::write("\x1b[32msuccess\x1b[0m ");
		xns::out::write(_to.count());
		xns::out::write(" == [");
		xns::out::write(expected);
		xns::out::write("]\n");
	}
	xns::out::render();

}

template <class from, class to, xns::umax expected>
void std_test(const xns::string_view& from_name, const xns::string_view& to_name) {

	xns::out::write(from_name.data(), from_name.size());
	for (xns::size_t x = from_name.size(); x < max_len(); ++x) {
		xns::out::write(" ");
	}
	xns::out::write("-> ");
	xns::out::write(to_name.data(), to_name.size());
	for (xns::size_t x = to_name.size(); x < max_len(); ++x) {
		xns::out::write(" ");
	}
	xns::out::write(" : ");

	to _to = std::chrono::duration_cast<to>(from{1});

	if (_to.count() != expected) {
		xns::out::write("\x1b[31mfailed:\x1b[0m ");
		xns::out::write(_to.count());
		xns::out::write(" != [");
		xns::out::write(expected);
		xns::out::write("]\n");
	}
	else {
		xns::out::write("\x1b[32msuccess\x1b[0m ");
		xns::out::write(_to.count());
		xns::out::write(" == [");
		xns::out::write(expected);
		xns::out::write("]\n");
	}
	xns::out::render();

}


void ratio_ut(void) {

	using namespace xns;

	if constexpr (ratio_less<ratio<1, 1000>, ratio<1, 100>>) {
		std::cout << "ratio<1, 1000> < ratio<1, 100>" << std::endl;
	}
	else {
		std::cout << "ratio<1, 1000> >= ratio<1, 100>" << std::endl;

	}

	if constexpr (ratio_less<ratio<1, 1000>, ratio<1, 1000>>) {
		std::cout << "ratio<1, 1000> < ratio<1, 1000>" << std::endl;
	}
	else {
		std::cout << "ratio<1, 1000> >= ratio<1, 1000>" << std::endl;

	}

	if constexpr (ratio_less<ratio<2, 4>, ratio<1, 2>>) {
		std::cout << "ratio<2, 4> < ratio<1, 2>" << std::endl;
	}
	else {
		std::cout << "ratio<2, 4> >= ratio<1, 2>" << std::endl;

	}


}

template <>
bool UT::unit_tests<"duration">(void) {


	//ratio_ut();

	std::chrono::milliseconds ms{2000};

	auto s = std::chrono::duration_cast<std::chrono::seconds>(ms);

	std::cout << "s: " << s.count() << std::endl;

	using namespace xns;

	start_ut<"duration_cast">();


	start_ut<"nanoseconds">();

	test<nanoseconds, nanoseconds, 1>("nanoseconds", "nanoseconds");
	test<nanoseconds, microseconds, 0>("nanoseconds", "microseconds");
	test<nanoseconds, milliseconds, 0>("nanoseconds", "milliseconds");
	test<nanoseconds, seconds, 0>("nanoseconds", "seconds");
	test<nanoseconds, minutes, 0>("nanoseconds", "minutes");
	test<nanoseconds, hours, 0>("nanoseconds", "hours");
	test<nanoseconds, days, 0>("nanoseconds", "days");
	test<nanoseconds, weeks, 0>("nanoseconds", "weeks");
	test<nanoseconds, months, 0>("nanoseconds", "months");
	test<nanoseconds, years, 0>("nanoseconds", "years");

	start_ut<"microseconds">();

	test<microseconds, nanoseconds, 1000>("microseconds", "nanoseconds");
	test<microseconds, microseconds, 1>("microseconds", "microseconds");
	test<microseconds, milliseconds, 0>("microseconds", "milliseconds");
	test<microseconds, seconds, 0>("microseconds", "seconds");
	test<microseconds, minutes, 0>("microseconds", "minutes");
	test<microseconds, hours, 0>("microseconds", "hours");
	test<microseconds, days, 0>("microseconds", "days");
	test<microseconds, weeks, 0>("microseconds", "weeks");
	test<microseconds, months, 0>("microseconds", "months");
	test<microseconds, years, 0>("microseconds", "years");

	start_ut<"milliseconds">();

	test<milliseconds, nanoseconds, 1000000>("milliseconds", "nanoseconds");
	test<milliseconds, microseconds, 1000>("milliseconds", "microseconds");
	test<milliseconds, milliseconds, 1>("milliseconds", "milliseconds");
	test<milliseconds, seconds, 0>("milliseconds", "seconds");
	test<milliseconds, minutes, 0>("milliseconds", "minutes");
	test<milliseconds, hours, 0>("milliseconds", "hours");
	test<milliseconds, days, 0>("milliseconds", "days");
	test<milliseconds, weeks, 0>("milliseconds", "weeks");
	test<milliseconds, months, 0>("milliseconds", "months");
	test<milliseconds, years, 0>("milliseconds", "years");

	start_ut<"seconds">();

	test<seconds, nanoseconds, 1000000000>("seconds", "nanoseconds");
	test<seconds, microseconds, 1000000>("seconds", "microseconds");
	test<seconds, milliseconds, 1000>("seconds", "milliseconds");
	test<seconds, seconds, 1>("seconds", "seconds");
	test<seconds, minutes, 0>("seconds", "minutes");
	test<seconds, hours, 0>("seconds", "hours");
	test<seconds, days, 0>("seconds", "days");
	test<seconds, weeks, 0>("seconds", "weeks");
	test<seconds, months, 0>("seconds", "months");
	test<seconds, years, 0>("seconds", "years");

	start_ut<"minutes">();

	test<minutes, nanoseconds, 60000000000>("minutes", "nanoseconds");
	test<minutes, microseconds, 60000000>("minutes", "microseconds");
	test<minutes, milliseconds, 60000>("minutes", "milliseconds");
	test<minutes, seconds, 60>("minutes", "seconds");
	test<minutes, minutes, 1>("minutes", "minutes");
	test<minutes, hours, 0>("minutes", "hours");
	test<minutes, days, 0>("minutes", "days");
	test<minutes, weeks, 0>("minutes", "weeks");
	test<minutes, months, 0>("minutes", "months");
	test<minutes, years, 0>("minutes", "years");

	start_ut<"hours">();

	test<hours, nanoseconds, 3600000000000>("hours", "nanoseconds");
	test<hours, microseconds, 3600000000>("hours", "microseconds");
	test<hours, milliseconds, 3600000>("hours", "milliseconds");
	test<hours, seconds, 3600>("hours", "seconds");
	test<hours, minutes, 60>("hours", "minutes");
	test<hours, hours, 1>("hours", "hours");
	test<hours, days, 0>("hours", "days");
	test<hours, weeks, 0>("hours", "weeks");
	test<hours, months, 0>("hours", "months");
	test<hours, years, 0>("hours", "years");

	start_ut<"days">();

	test<days, nanoseconds, 86400000000000>("days", "nanoseconds");
	test<days, microseconds, 86400000000>("days", "microseconds");
	test<days, milliseconds, 86400000>("days", "milliseconds");
	test<days, seconds, 86400>("days", "seconds");
	test<days, minutes, 1440>("days", "minutes");
	test<days, hours, 24>("days", "hours");
	test<days, days, 1>("days", "days");
	test<days, weeks, 0>("days", "weeks");
	test<days, months, 0>("days", "months");
	test<days, years, 0>("days", "years");


	start_ut<"weeks">();

	test<weeks, nanoseconds, 604800000000000>("weeks", "nanoseconds");
	test<weeks, microseconds, 604800000000>("weeks", "microseconds");
	test<weeks, milliseconds, 604800000>("weeks", "milliseconds");
	test<weeks, seconds, 604800>("weeks", "seconds");
	test<weeks, minutes, 10080>("weeks", "minutes");
	test<weeks, hours, 168>("weeks", "hours");
	test<weeks, days, 7>("weeks", "days");
	test<weeks, weeks, 1>("weeks", "weeks");
	test<weeks, months, 0>("weeks", "months");
	test<weeks, years, 0>("weeks", "years");

	start_ut<"months">();

	test<months, nanoseconds, 2628000000000000>("months", "nanoseconds");
	std_test<std::chrono::months, std::chrono::nanoseconds, 2628000000000000>("months", "nanoseconds");

	test<months, microseconds, 2628000000000>("months", "microseconds");
	std_test<std::chrono::months, std::chrono::microseconds, 2628000000000>("months", "microseconds");

	test<months, milliseconds, 2628000000>("months", "milliseconds");
	std_test<std::chrono::months, std::chrono::milliseconds, 2628000000>("months", "milliseconds");

	test<months, seconds, 2628000>("months", "seconds");
	std_test<std::chrono::months, std::chrono::seconds, 2628000>("months", "seconds");

	test<months, minutes, 43800>("months", "minutes");
	std_test<std::chrono::months, std::chrono::minutes, 43800>("months", "minutes");

	test<months, hours, 730>("months", "hours");
	std_test<std::chrono::months, std::chrono::hours, 730>("months", "hours");

	test<months, days, 30>("months", "days");
	std_test<std::chrono::months, std::chrono::days, 30>("months", "days");

	test<months, weeks, 4>("months", "weeks");
	std_test<std::chrono::months, std::chrono::weeks, 4>("months", "weeks");

	test<months, months, 1>("months", "months");
	std_test<std::chrono::months, std::chrono::months, 1>("months", "months");

	test<months, years, 0>("months", "years");
	std_test<std::chrono::months, std::chrono::years, 0>("months", "years");

	start_ut<"years">();



	test<years, nanoseconds, 31536000000000000>("years", "nanoseconds");
	test<years, microseconds, 31536000000000>("years", "microseconds");
	test<years, milliseconds, 31536000000>("years", "milliseconds");
	test<years, seconds, 31536000>("years", "seconds");
	test<years, minutes, 525600>("years", "minutes");
	test<years, hours, 8760>("years", "hours");
	test<years, days, 365>("years", "days");
	test<years, weeks, 52>("years", "weeks");
	test<years, months, 12>("years", "months");
	test<years, years, 1>("years", "years");














	return 0;
}
