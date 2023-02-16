#include "escape.hpp"
#include "macro.hpp"
#include "types.hpp"
#include "xfunc.hpp"
#include "unit_tests.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <stack>
#include <any>

#include "numeric_limits.hpp"



void loop(void) { /*std::cout << "start LOOP !" << std::endl;*/ }
void exit(void) { Xf::Input::stop_loop(); }

void resize(void) {
	Xf::Term::Wsize width, height;
	Xf::Term::instance().get_terminal_size(width, height);
	std::cout << "RESIZE: " << width << "x" << height << std::endl;
}

struct BTest {

	static void borderleft(void) {
		x-=!!x;
		Xf::Escape::draw<Xf::Escape::erase_screen_t>();
		_border.set({x, y, w, h});
		_border.draw();
		Xf::Escape::draw<Xf::Escape::move_position_t>(0, 0);
		Buffer::render();
		std::cout << "x = " << x << std::endl;
	}
	static void borderright(void) {
		x+=1;
		Xf::Escape::draw<Xf::Escape::erase_screen_t>();
		_border.set({x, y, w, h});
		_border.draw();

		Xf::Escape::draw<Xf::Escape::move_position_t>(0, 0);
		Buffer::render();
		std::cout << "x = " << x << std::endl;

	}
	static void borderup(void) {
		y-=!!y;
		Xf::Escape::draw<Xf::Escape::erase_screen_t>();
		_border.set({x, y, w, h});
		_border.draw();

		Xf::Escape::draw<Xf::Escape::move_position_t>(0, 0);
		Buffer::render();
		std::cout << "y = " << y << std::endl;
	}
	static void borderdown(void) {
		y+=1;
		Xf::Escape::draw<Xf::Escape::erase_screen_t>();
		_border.set({x, y, w, h});
		_border.draw();
		Xf::Escape::draw<Xf::Escape::move_position_t>(0, 0);
		Buffer::render();
		std::cout << "y = " << y << std::endl;
	}

	static inline UInt32 x = 3;
	static inline UInt32 y = 3;
	static inline UInt32 w = 10;
	static inline UInt32 h = 4;

	//static inline Xf::Border _border{};
	static inline Xf::Window _border{};
};

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif


void getinput(const Xf::String<char>& input) {
	write(1, input.pointer(), input.size());
}

#include "is_integral.hpp"

#include "file.hpp"

template <typename T>
concept c_signed = true;

template <Xf::integral_c T>
void func_for_integral(T x) {
	std::cout << "integral" << std::endl;
}

void numeric_limits_debug(void) {
	// avoid namespace pollution
	using namespace std;

	//cout << "bool MIN:                " << Xf::min<bool>() << endl;
	//cout << "bool MAX:                " << Xf::max<bool>() << endl;
	cout << "char8_t MIN:             " << Xf::min<char8_t>() << endl;
	cout << "char8_t MAX:             " << Xf::max<char8_t>() << endl;
	cout << "char16_t MIN:            " << Xf::min<char16_t>() << endl;
	cout << "char16_t MAX:            " << Xf::max<char16_t>() << endl;
	cout << "char32_t MIN:            " << Xf::min<char32_t>() << endl;
	cout << "char32_t MAX:            " << Xf::max<char32_t>() << endl;
	cout << "wchar_t MIN:             " << Xf::min<wchar_t>() << endl;
	cout << "wchar_t MAX:             " << Xf::max<wchar_t>() << endl;
	cout << "char MIN:                " << Xf::min<char>() << endl;
	cout << "char MAX:                " << Xf::max<char>() << endl;
	cout << "short MIN:               " << Xf::min<short>() << endl;
	cout << "short MAX:               " << Xf::max<short>() << endl;
	cout << "int MIN:                 " << Xf::min<int>() << endl;
	cout << "int MAX:                 " << Xf::max<int>() << endl;
	cout << "long MIN:                " << Xf::min<long>() << endl;
	cout << "long MAX:                " << Xf::max<long>() << endl;
	cout << "long long MIN:           " << Xf::min<long long>() << endl;
	cout << "long long MAX:           " << Xf::max<long long>() << endl;
	cout << "unsigned char MIN:       " << Xf::min<unsigned char>() << endl;
	cout << "unsigned char MAX:       " << Xf::max<unsigned char>() << endl;
	cout << "unsigned short MIN:      " << Xf::min<unsigned short>() << endl;
	cout << "unsigned short MAX:      " << Xf::max<unsigned short>() << endl;
	cout << "unsigned int MIN:        " << Xf::min<unsigned int>() << endl;
	cout << "unsigned int MAX:        " << Xf::max<unsigned int>() << endl;
	cout << "unsigned long MIN:       " << Xf::min<unsigned long>() << endl;
	cout << "unsigned long MAX:       " << Xf::max<const unsigned long>() << endl;
	cout << "unsigned long long MIN:  " << Xf::min<unsigned long long>() << endl;
	cout << "unsigned long long MAX:  " << Xf::max<unsigned long long>() << endl;
}

template <Xf::is_8bit_c T>
void func_for_8bit(T x) {
	std::cout << "8bit" << std::endl;
}


int main(int ac, char** av) {

	Xf::String<char16_t> sss;
   // sss.forward_remove_duplicates();

	auto max = Xf::max_digits<unsigned char>();
	std::cout << "max digits: " << (int)max << std::endl;
	auto min = Xf::min_digits<unsigned char>();
	std::cout << "min digits: " << (int)min << std::endl;
	return 0;

	goto start;
	//static_assert(wchar_t(-1) < 0, "wchar_t is unsigned");



	//numeric_limits_debug();


start:

	// char min in hex: 0x80
	// short min in hex: 0x8000
	// int min in hex: 0x80000000
	// long min in hex: 0x8000000000000000
	// long long min in hex: 0x8000000000000000
	// long long max in hex: 0x7FFFFFFFFFFFFFFF



	//UInt64 a = Xf::max<UInt64>();

	Xf::String<char> s;
	const unsigned char c = 'a';

	s.to_string(c);
	return 0;
	for(char x = -11; x < +5'0; ++x) {
		s.to_string(x);
		//write(1, "final: ", 7);
		write(1, s.pointer(), s.size());
		write(1, "\n", 1);
	}

	return 0;



	Xf::File file{"Makefile"};
	file.open();
	file.content();
	return 0;


   // Xf::Escape::rgb_color c;

	//using Esc = Xf::Escape;
	//UInt32 x, y;
	//Esc::draw<Esc::rgb_color_t>(200, 100, 188, false);
	//Esc::draw<Esc::hex_color_t>(0x00FF00, true);
	//Esc::get<Esc::move_position_t>(x, y);
	//Xf::Escape::request_position(x, y);
	//Buffer::render();
	//write(1, "hello world", 11);



	//return 0;



	//Xf::String s1{""};
	//Xf::String s2{"hello world---"};
	//Xf::String s3{"*this is a test"};
	//Xf::String s4{"*for my append method---"};
	//Xf::String s5{"*with variadic template-"};
	//Xf::String s6{"*-!!!---"};

	//s1.append(s2, s3, s4, s5, s6);


	/*
	s1._debug_();

	auto vec = s1.divide(Xf::String{"*-"});

	for (unsigned int x = 0; x < vec.size(); ++x) {
		std::cout << "vec[" << x << "] = " << vec[x].pointer() << std::endl;
	}
	*/
	// char max


	//Xf::String s7{"hello"};
	//s7.insert(s7.size()-1, '*', 2);

	//s7._debug_();


	//Xf::Tests::test_string();
	//return 0;


	//Xf::Window win{10, 10, 10, 10};

	//win.render();

	//Xf::Border::draw(10, 10, 10, 10);




	//return 0;






	auto& evnt = Xf::Event::instance();

	Xf::Evntmode mode = evnt.new_mode();
	Xf::Evntmode mode2 = evnt.new_mode();


	evnt.set_mode(mode2);

	using Ev = Xf::Evntype;

	mode.subscribe(Ev::UP,    &BTest::borderup);
	mode.subscribe(Ev::DOWN,  &BTest::borderdown);
	mode.subscribe(Ev::LEFT,  &BTest::borderleft);
	mode.subscribe(Ev::RIGHT, &BTest::borderright);
	mode.subscribe(Ev::ETX,   exit);
	mode.subscribe(Ev::MIN_Q, exit);
	mode.subscribe(Ev::ESC,   exit);
	mode.subscribe(Ev::LOOP, loop);
	mode.subscribe(Ev::TERMINAL_RESIZE, resize);

	mode.subscribe(getinput);
	evnt.set_mode(mode);


	Xf::Input::start_loop();


	return 0;
}





	//Xf::UniquePtr<Test<int>> u{2};
	//Base* b = new Derived1<int>{};
	//Xf::Vector<Base<int>*> v;
	//v.push_back(new Derived1<void, Toto, int>{});
	//Xf::Method m{&Derived1::print, d1};
	//m.call(2, true);
	//Xf::Vector<Xf::MethodPointer<void, Derived1>> v;
	/*
	Xf::Stack<int> s;

	for (int x = 0; x < 10; ++x) {
		s.push(x);
	}
	s.print();
	for (int x = 0; x < 5; ++x) {
		s.pop();
	}
	s.print();

	s.clear();
	s.print();
	*/

	//std::cout << __cplusplus << std::endl;



