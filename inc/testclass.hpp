#ifndef TESTCLASS_HEADER
#define TESTCLASS_HEADER

#include <iostream>
#include "string_literal.hpp"
#include "move.hpp"

#define TESTCLASS_DEBUG

#ifdef TESTCLASS_DEBUG
#define test_debug(msg) std::cout << msg << std::endl;
#else
#define test_debug(msg)
#endif

#undef TESTCLASS_DEBUG

template <class T>
class Base {

	public:

		Base(void) {}
		virtual ~Base(void) {}

		virtual void echo(void) const = 0;

};


template <class T, class U, class V>
class Class final : public Base<T> {

	public:

		/* default constructor */
		Class(void)
		:	_value_1{},
			_value_2{},
			_value_3{} {
			test_debug("class default constructor");
		}

		/* value constructor */
		Class(const T& value_1, const U& value_2, const V& value_3)
		:	_value_1{value_1},
			_value_2{value_2},
			_value_3{value_3} {
			test_debug("class value constructor");
		}

		/* copy constructor */
		Class(const Class& other)
		:	_value_1{other._value_1},
			_value_2{other._value_2},
			_value_3{other._value_3} {
			test_debug("class copy constructor");
		}

		/* move constructor */
		Class(Class&& other) noexcept
		:	_value_1{xns::move(other._value_1)},
			_value_2{xns::move(other._value_2)},
			_value_3{xns::move(other._value_3)} {
			test_debug("class move constructor");
		}

		/* destructor */
		~Class(void) {
			test_debug("class destructor");
		}

		/* copy operator */
		Class& operator=(const Class& other) {
			if (this != &other) {
				_value_1 = other._value_1;
				_value_2 = other._value_2;
				_value_3 = other._value_3;
			}
			test_debug("class copy assignment");
			return *this;
		}

		/* move operator */
		Class& operator=(Class&& other) noexcept {
			if (this != &other) {
				_value_1 = xns::move(other._value_1);
				_value_2 = xns::move(other._value_2);
				_value_3 = xns::move(other._value_3);
			}
			test_debug("class move assignment");
			return *this;
		}

		/* echo */
		void echo(void) const override {
			std::cout << "echo class" << std::endl;
		}

		/* print operator */
		friend std::ostream& operator<<(std::ostream& os, const Class& t) {
			os << t._value_1 << " " << t._value_2 << " " << t._value_3;
			return os;
		}


	private:

		T _value_1;
		U _value_2;
		V _value_3;


};


// -- T E S T  N A M E S P A C E ----------------------------------------------

namespace tests {


	// -- B A S E  C L A S S --------------------------------------------------

	class base {

		public:

			// -- constructors ------------------------------------------------

			/* virtual destructor */
			virtual ~base(void) { /* empty */ }


			// -- virtual methods ---------------------------------------------

			/* echo */
			virtual void echo(void) const {
				std::cout << "echo base" << std::endl;
			}

	};


	// -- D E R I V E D  C L A S S --------------------------------------------

	class derived final : public base {

		public:

			// -- constructors ------------------------------------------------

			/* default constructor */
			derived(void) = default;

			/* destructor */
			~derived(void) override = default;


			// -- override methods --------------------------------------------

			/* echo */
			void echo(void) const override {
				std::cout << "echo derived" << std::endl;
			}


	};



}



template <typename T, xns::basic_string_literal CLASS_NAME,
					  xns::basic_string_literal TYPE_NAME>
class X {
	public:

		X(void)
		: _x{} {
			std::cout << CLASS_NAME.runtime_data()
					  << " default constructor" << std::endl;
		}

		X(const T& x)
		: _x{x} {
			std::cout << CLASS_NAME.runtime_data()
					  << " "
					  << TYPE_NAME.runtime_data()
					  << " constructor" << std::endl;
		}

		X(const X& other)
		: _x{other._x} {
			std::cout << CLASS_NAME.runtime_data()
					  << " copy constructor" << std::endl;
		}

		X(X&& other)
		: _x{xns::move(other._x)} {
			std::cout << CLASS_NAME.runtime_data()
					  << " move constructor" << std::endl;
		}

		X& operator=(const X& other) {
			std::cout << CLASS_NAME.runtime_data()
					  << " copy assignment" << std::endl;
			_x = other._x;
			return *this;
		}

		X& operator=(X&& other) {
			std::cout << CLASS_NAME.runtime_data()
					  << " move assignment" << std::endl;
			_x = xns::move(other._x);
			return *this;
		}

		~X(void) {
			std::cout << CLASS_NAME.runtime_data()
					  << " destructor" << std::endl;
		}

	private:
		T _x;

	template <typename U, xns::basic_string_literal CNAME,
					      xns::basic_string_literal TNAME>
	friend std::ostream& operator<<(std::ostream& os, const X& x);
};


template <typename U, xns::basic_string_literal CNAME,
					  xns::basic_string_literal TNAME>
inline std::ostream& operator<<(std::ostream& os, const X<U, CNAME, TNAME>& x) {
	return os << CNAME.runtime_data() << " " << TNAME.runtime_data() << " " << x._x;
}


using B = X<bool,  "B", "bool">;
using C = X<char,  "C", "char">;
using I = X<int,   "I", "int">;
using L = X<long,  "L", "long">;
using F = X<float, "F", "float">;
using D = X<double,"D", "double">;
using S = X<std::string, "S", "string">;




#endif
