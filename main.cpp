#include "Term.hpp"
#include "String.hpp"
#include "Input.hpp"
#include "event.hpp"
#include "function.hpp"
#include "list.hpp"
#include "allocator.hpp"
#include "vector.hpp"
#include "array.hpp"

#include "stack.hpp"
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




void print_array(const Xf::Array<int, 10>& a) {
	for (Size x = 0; x < a.size(); ++x) {
		std::cout << a[x] << " ";
	}
	std::cout << std::endl;
}


enum class Ev {
	ESCAPE        = 0,
	ENTER         = 1,
	BACKSPACE     = 2,
};

#define N 0

template <typename... A>
class Base {
	public:
		virtual void print(A&&... a) = 0;
		~Base() = default;
};

class Derived1 : public Base<int, bool> {
	public:
		void print(int&& i, bool&& b) override {
			std::cout << "i: " << i << "\nb: " << b << std::endl;
		}

};

class Derived2 : public Base<float, bool> {
	public:
		void print(float&& f, bool&& b) override {
			std::cout << "f: " << f << "\nb: " << b << std::endl;
		}
};

#include "testclass.hpp"

#include <stack>

#define NB 100000

#include "unique.hpp"

class Int {

	public:
		Int(Int* i) { }
		~Int() { }

	private:
		int _i;

};
#include "allocator.hpp"

int main(int ac, char** av) {


	//Xf::UniquePtr<Test<int>> u{2};








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







