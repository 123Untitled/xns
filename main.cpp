#include "Term.hpp"
#include "String.hpp"
#include "Input.hpp"
#include "event.hpp"
#include "function.hpp"
#include "list.hpp"
#include "allocator.hpp"
#include "vector.hpp"
#include "array.hpp"

#include <array>
#include <vector>
#include <iostream>


void* escape_normal(void* instance) {
	std::cout << "escape_normal" << std::endl;
	return nullptr;
}

void* escape_insert(void* instance) {
	std::cout << "escape_insert" << std::endl;
	return nullptr;
}

void* enter_insert(void* instance) {
	Xf::Event::instance().set_mode("INSERT");
	std::cout << "enter_insert" << std::endl;
	return nullptr;
}

void* exit_insert(void* instance) {
	Xf::Event::instance().set_mode("NORMAL");
	std::cout << "exit_insert" << std::endl;
	return nullptr;
}

void* exit_loop(void* instance) {
	std::cout << "exit_loop" << std::endl;
	Xf::Input::stop_loop();
	return nullptr;
}

class Test {

	public:

		Test(void) : _f{1} { std::cout << "CONSTRUCTOR" << std::endl; }

		Test(float f) : _f(f) { std::cout << "FLOAT CONSTRUCTOR" << std::endl; }

		Test(const Test& t) : _f(t._f) { std::cout << "COPY CONSTRUCTOR" << std::endl; }

		~Test(void) noexcept { std::cout << "DESTRUCTOR" << std::endl; }

		Test(Test&& t) noexcept : _f(t._f) { std::cout << "MOVE" << std::endl; }

		Test& operator=(const Test& t) {
			std::cout << "COPY ASSIGNMENT" << std::endl;
			_f = t._f;
			return *this;
		}

		Test& operator=(Test&& t) noexcept {
			std::cout << "MOVE ASSIGNMENT" << std::endl;
			_f = t._f;
			return *this;
		}

		void print(float f) {
			std::cout << "f: " << f << "\n_f: " << _f << std::endl;
		}


	float _f;

};


// overload <<
std::ostream& operator<<(std::ostream& os, const Test& t) {
	os << t._f;
	return os;
}

void print_array(const Xf::Array<int, 10>& a) {
	for (Size x = 0; x < a.size(); ++x) {
		std::cout << a[x] << " ";
	}
	std::cout << std::endl;
}

#include "initializer.hpp"
#include "stack.hpp"

enum class Ev {
	ESCAPE        = 0,
	ENTER         = 1,
	BACKSPACE     = 2,
};

#define N 0

int main(void) {



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



	/*
	using namespace Xf;

	Event& evnt = Event::instance();

	evnt.add_mode("NORMAL");
	evnt.add_mode("INSERT");

	evnt.subscribe("NORMAL", Evntype::ESCAPE, escape_normal, nullptr);


	evnt.subscribe("NORMAL", Evntype::RETURN, enter_insert, nullptr);
	evnt.subscribe("INSERT", Evntype::ESCAPE, escape_insert, nullptr);
	evnt.subscribe("INSERT", Evntype::RETURN, exit_insert, nullptr);
	evnt.subscribe("NORMAL", Evntype::TAB, exit_loop, nullptr);

	evnt.set_mode("NORMAL");

	//evnt.call(Evntype::ESCAPE);
	Term::setRaw();
	Xf::Input::start_loop();

	std::cout << __cplusplus << std::endl;
	*/



	return 0;
}







