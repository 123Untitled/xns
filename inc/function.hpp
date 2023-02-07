#ifndef FUNCTION_HEADER
#define FUNCTION_HEADER

#include "type_traits.hpp"
#include "event.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- F U N C T I O N  C L A S S --------------------------------------------

	template <typename R, typename... A>
	class Function final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* function pointer type */
			using Prototype = R(*)(A...);

			/* return type */
			using Return = R;

			// -- C O N S T R U C T O R S -------------------------------------

			/* deleted default constructor */
			Function(void) = delete;

			/* function pointer constructor */
			Function(Prototype function)
			// initializations
			: _function{function} { }

			/* destructor */
			~Function(void) { /* nothing to do */ }


			// -- O P E R A T O R S -------------------------------------------

			/* function call operator */
			Return operator()(A... args) const {
				// call function
				return _function(args...);
			}

			/* assignment operator */
			Function& operator=(const Function& other) {
				// copy function pointer
				_function = other._function;
				// return self reference
				return *this;
			}

			// -- P U B L I C  M E T H O D S ----------------------------------

			/* call method */
			Return call(A... args) const {
				// call function
				return _function(args...);
			}

		private:

			// -- P R I V A T E  M E M B E R S ----------------------------

			/* function to call */
			Prototype _function;

	};


	// -- M E T H O D  C L A S S ----------------------------------------------

	template <typename R, typename C, typename... A>
	class Method final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* method pointer type */
			using Prototype = R(C::*)(A...);

			/* instance reference type */
			using Reference = C&;

			/* instance pointer type */
			using Pointer = C*;

			/* return type */
			using Return = R;


			// -- C O N S T R U C T O R S -------------------------------------

			/* deleted default constructor */
			Method(void) = delete;

			/* method pointer constructor */
			Method(Prototype method, Reference instance)
			// initializations
			: _method{method}, _instance{&instance} { }

			Method(Prototype method, Pointer instance)
			// initializations
			: _method{method}, _instance{instance} { }

			/* copy constructor */
			Method(const Method& other)
			// initializations
			: _method{other._method}, _instance{other._instance} { }

			/* destructor */
			~Method(void) { }


			// -- O P E R A T O R S -------------------------------------------

			/* assignment operator */
			Method& operator=(const Method& other) {
				// check for self assignment
				if (this != &other) {
					// copy method pointer
					_method = other._method;
					// copy instance reference
					_instance = other._instance;
				} // return self reference
				return *this;
			}


			/* function call operator */
			Return operator()(A... args) const {
				// call method
				return (_instance->*_method)(args...);
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* call method */
			Return call(A... args) const {
				// call method
				return (_instance->*_method)(args...);
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* method to call */
			Prototype _method;

			/* instance to call method on */
			Pointer   _instance;

	};

};

#endif

