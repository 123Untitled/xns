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


void* print(void* instance) {
	std::cout << *(int*)instance << std::endl;
	return nullptr;
}

void* escape(void* instance) {
	std::cout << "ESCAPE" << std::endl;
	return nullptr;
}

void* arrow(void* instance) {
	std::cout << "ARROW" << std::endl;
	return nullptr;
}

void* _return(void* instance) {
	std::cout << "RETURN" << std::endl;
	//Xf::Input::stop_loop();
	return nullptr;
}

int _int(void) {
	std::cout << "_INT" << std::endl;
	return 42;
}

class Test {

	public:

		Test(void) : _f{1} { std::cout << "CONSTRUCTOR" << std::endl; }

		Test(float f) : _f(f) { std::cout << "FLOAT CONSTRUCTOR" << std::endl; }

		Test(const Test& t) : _f(t._f) { std::cout << "COPY" << std::endl; }

		~Test(void) noexcept { std::cout << "DESTRUCTOR" << std::endl; }

		Test(Test&& t) noexcept : _f(t._f) { std::cout << "MOVE" << std::endl; }

		Test& operator=(const Test& t) {
			std::cout << "ASSIGNMENT" << std::endl;
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


int main(void) {

	using namespace Xf;

	Evntmode normal = Event::instance().add_mode("NORMAL");

	Evntmode insert = Event::instance().add_mode("world");

	if (!normal) {
		std::cout << "NORMAL MODE" << std::endl;
	}

	int a = 42;

	loop();

	normal.subscribe(Xf::Evntype::ESCAPE, escape, &a);

	return 0;
}







