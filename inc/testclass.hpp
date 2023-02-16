#ifndef TESTCLASS_HEADER
#define TESTCLASS_HEADER

#include <iostream>
#include "move.hpp"

#define TESTCLASS_DEBUG

#ifdef TESTCLASS_DEBUG
#define debug(msg) std::cout << msg << std::endl;
#else
#define debug(msg)
#endif


template <typename T>
class Test {

	public:

		/* default constructor */
		Test(void)
		: _value{} {
			debug("DEFAULT CONSTRUCTOR");
		}

		/* value constructor */
		Test(const T& value) noexcept
		: _value{value} {
			debug("VALUE CONSTRUCTOR");
		}

		/* copy constructor */
		Test(const Test& other)
		: _value{other._value} {
			debug("COPY CONSTRUCTOR");
		}

		/* move constructor */
		Test(Test&& other) noexcept
		: _value{Xf::move(other._value)} {
			debug("MOVE CONSTRUCTOR");
		}

		/* destructor */
		~Test(void) {
			debug("DESTRUCTOR");
		}

		/* copy operator */
		Test& operator=(const Test& t) {
			debug("COPY ASSIGNMENT");
			if (this != &t) {
				_value = t._value;
			} return *this;
		}

		/* move operator */
		Test& operator=(Test&& t) noexcept {
			debug("MOVE ASSIGNMENT");
			if (this != &t) {
				_value = Xf::move(t._value);
			} return *this;
		}

		/* print operator */
		friend std::ostream& operator<<(std::ostream& os, const Test& t) {
			os << t._value;
			return os;
		}

		void function(void) {
			std::cout << "Hello World!" << std::endl;
		}


	private:

		T _value;


};

#endif
