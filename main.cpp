#include "Term.hpp"
#include "String.hpp"
#include "Input.hpp"
#include "event.hpp"
#include "function.hpp"
#include "list.hpp"
#include "allocator.hpp"
#include "vector.hpp"
#include "array.hpp"
#include "testclass.hpp"
#include "stack.hpp"
#include "unique.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <stack>
#include <any>


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




#define NB 100000

class Toto {
	public:
		Toto() = default;
		~Toto() = default;

		void print1(const std::string& input) {
			std::cout << "TOTO METHOD: " << input << std::endl;
		}
};

class Tutu {
	public:
		Tutu() = default;
		~Tutu() = default;

		void print2(const std::string& input) {
			std::cout << "TUTU METHOD: " << input << std::endl;
		}
};






int main(int ac, char** av) {

	Toto t;
	Tutu u;

	Term::setRaw();

	auto& evnt = Xf::Event::instance();

	evnt.add_mode("NORMAL");

	evnt.set_mode("NORMAL");

	evnt.add_mode("INSERT");

	using Ev = Xf::Evntype;

	evnt.subscribe("NORMAL", Ev::ESCAPE, &Toto::print1, &t);
	evnt.subscribe("NORMAL", Ev::ESCAPE, &Tutu::print2, &u);

	Xf::Input::start_loop();





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







