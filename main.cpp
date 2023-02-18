#include "xfunc.hpp"
#include "unit_tests.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <stack>
#include <any>




void loop(void) { /*std::cout << "start LOOP !" << std::endl;*/ }
void exit(void) { Xf::Input::stop_loop(); }

void resize(void) {
	Xf::Term::Wsize width, height;
	Xf::Term::instance().get_terminal_size(width, height);
	std::cout << "RESIZE: " << width << "x" << height << std::endl;
}

//struct BTest {
//
//	static void borderleft(void) {
//		x-=!!x;
//		Xf::Escape::draw<Xf::Escape::erase_screen_t>();
//		_border.set({x, y, w, h});
//		_border.draw();
//		Xf::Escape::draw<Xf::Escape::move_position_t>(0, 0);
//		Buffer::render();
//		std::cout << "x = " << x << std::endl;
//	}
//	static void borderright(void) {
//		x+=1;
//		Xf::Escape::draw<Xf::Escape::erase_screen_t>();
//		_border.set({x, y, w, h});
//		_border.draw();
//
//		Xf::Escape::draw<Xf::Escape::move_position_t>(0, 0);
//		Buffer::render();
//		std::cout << "x = " << x << std::endl;
//
//	}
//	static void borderup(void) {
//		y-=!!y;
//		Xf::Escape::draw<Xf::Escape::erase_screen_t>();
//		_border.set({x, y, w, h});
//		_border.draw();
//
//		Xf::Escape::draw<Xf::Escape::move_position_t>(0, 0);
//		Buffer::render();
//		std::cout << "y = " << y << std::endl;
//	}
//	static void borderdown(void) {
//		y+=1;
//		Xf::Escape::draw<Xf::Escape::erase_screen_t>();
//		_border.set({x, y, w, h});
//		_border.draw();
//		Xf::Escape::draw<Xf::Escape::move_position_t>(0, 0);
//		Buffer::render();
//		std::cout << "y = " << y << std::endl;
//	}
//
//	static inline UInt32 x = 3;
//	static inline UInt32 y = 3;
//	static inline UInt32 w = 10;
//	static inline UInt32 h = 4;
//
//	//static inline Xf::Border _border{};
//	static inline Xf::Window _border{{x, y, w, h}};
//};



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


template <Xf::is_8bit_c T>
void func_for_8bit(T x) {
	std::cout << "8bit" << std::endl;
}


int main(int ac, char** av) {


	Xf::Tests::window_tests();
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

//	mode.subscribe(Ev::UP,    &BTest::borderup);
//	mode.subscribe(Ev::DOWN,  &BTest::borderdown);
//	mode.subscribe(Ev::LEFT,  &BTest::borderleft);
//	mode.subscribe(Ev::RIGHT, &BTest::borderright);
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



