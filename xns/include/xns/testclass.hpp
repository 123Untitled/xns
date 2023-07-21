#ifndef TESTCLASS_HEADER
#define TESTCLASS_HEADER

#include <iostream>
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





#endif
