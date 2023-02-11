#ifndef FUNCTION_HEADER
#define FUNCTION_HEADER

#include "type_traits.hpp"
#include "forward.hpp"


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
			//Function(void) = delete;
			Function() { }

			/* function pointer constructor */
			Function(Prototype function)
			// initializations
			: _function{function} { }

			/* destructor */
			~Function(void) { /* nothing to do */ }


			// -- O P E R A T O R S -------------------------------------------

			/* copy operator */
			Function& operator=(const Function& other) {
				// copy function pointer
				_function = other._function;
				// return self reference
				return *this;
			}

			/* function call operator */
			Return operator()(A&&... arguments) {
				// call function
				return _function(Xf::forward<A>(arguments)...);
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* call method */
			Return call(A&&... arguments) const {
				// call function
				return _function(Xf::forward<A>(arguments)...);
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
			//Method(void) = delete;
			Method() { }

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

			/* copy operator */
			Method& operator=(const Method& other) {
				// copy method pointer
				_method = other._method;
				// copy instance reference
				_instance = other._instance;
				// return self reference
				return *this;
			}


			/* function call operator */
			Return operator()(A&&... arguments) const {
				// call method
				return (_instance->*_method)(Xf::forward<A>(arguments)...);
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* call method */
			Return call(A&&... arguments) const {
				// call method
				return (_instance->*_method)(Xf::forward<A>(arguments)...);
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* method to call */
			Prototype _method;

			/* instance to call method on */
			Pointer   _instance;

	};



	// -- P O L Y  M E T H O D  C L A S S -------------------------------------

	template <typename R, typename... A>
	class PolyMethod final {

		public:

			// -- A L I A S E S -----------------------------------------------

			/* method pointer type */
			template <typename C>
			using Prototype = R(C::*)(A...);

			/* instance reference type */
			template <typename C>
			using Reference = C&;

			/* instance pointer type */
			template <typename C>
			using Pointer = C*;

			/* return type */
			using Return = R;


			// -- C O N S T R U C T O R S -------------------------------------

			/* [default constructor] */
			PolyMethod(void)
			: _base{nullptr} {
				// code here...
			}

			/* [prototype reference constructor] */
			template <typename C>
			explicit PolyMethod(Prototype<C> method, Reference<C> instance)
			: _base{new Derived<C>{method, instance}} {
				// code here...
			}

			/* [prototype pointer constructor] */
			template <typename C>
			explicit PolyMethod(Prototype<C> method, Pointer<C> instance)
			: _base{new Derived<C>{method, instance}} {
				// code here...
			}

			/* [copy constructor] */
			PolyMethod(const PolyMethod& other)
			: _base{other._base ? other._base->clone() : nullptr} {
				// code here...
			}

			/* [move constructor] */
			PolyMethod(PolyMethod&& other) noexcept
			: _base{other._base} {
				// invalidate other base pointer
				other._base = nullptr;
			}

			/* [destructor] */
			~PolyMethod(void) {
				// deallocate base
				if (_base) { delete _base; }
			}


			// -- O P E R A T O R S -------------------------------------------

			/* [copy assignment operator] */
			PolyMethod& operator=(const PolyMethod& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate base
					if (_base) { delete _base; }
					// copy base
					_base = other._base ? other._base->clone() : nullptr;
				} // return self reference
				return *this;
			}

			/* [move assignment operator] */
			PolyMethod& operator=(PolyMethod&& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// deallocate base
					if (_base) { delete _base; }
					// move base pointer
					_base = other._base;
					// invalidate other base pointer
					other._base = nullptr;
				} // return self reference
				return *this;
			}

			/* [function call operator] */
			Return operator()(A&&... arguments) const {
				// call base method
				return _base->call(Xf::forward<A>(arguments)...);
			}


			// -- M E T H O D S -----------------------------------------------

			/* [call method] */
			Return call(A&&... arguments) const {
				// call base method
				return _base->call(Xf::forward<A>(arguments)...);
			}


		private:

			// -- P R I V A T E  N E S T E D  S T R U C T S -------------------

			struct Base {

					Base(void) = default;

					virtual ~Base(void) = default;

					virtual R call(A&&...) const = 0;

					virtual R operator()(A&&...) const = 0;

					virtual Base* clone(void) const = 0;

			};


			template <typename C>
			struct Derived final : public Base {

				// -- A L I A S E S -------------------------------------------

				/* value type */
				using Value = C;

				/* method pointer type */
				using Prototype = R(C::*)(A...);

				/* instance reference type */
				using Reference = Reference<C>;

				/* instance pointer type */
				using Pointer = Pointer<C>;


				// -- C O N S T R U C T O R S ---------------------------------

				/* [default constructor] */
				Derived(void)
				: _method{nullptr}, _instance{nullptr} {
					// code here...
				}

				/* [prototype reference constructor] */
				Derived(Prototype method, Reference instance)
				: _method{method}, _instance{&instance} {
					// code here...
				}

				/* [prototype pointer constructor] */
				Derived(Prototype method, Pointer instance)
				: _method{method}, _instance{instance} {
					// code here...
				}

				/* [copy constructor] */
				Derived(const Derived& other)
				: _method{other._method}, _instance{other._instance} {
					// code here...
				}

				/* [move constructor] */
				Derived(Derived&& other)
				: Derived{other} {
					// code here...
				}

				/* [destructor] */
				~Derived(void) override = default;


				// -- O P E R A T O R S ---------------------------------------

				/* [copy assignment operator] */
				Derived& operator=(const Derived& other) {
					// copy method pointer
					_method = other._method;
					// copy instance pointer
					_instance = other._instance;
					// return self reference
					return *this;
				}

				/* [move assignment operator] */
				Derived& operator=(Derived&& other) {
					// call copy assignment operator
					return Derived::operator=(other);
				}

				/* [function call operator] */
				Return operator()(A&&... arguments) const override {
					// call method on instance
					return (_instance->*_method)(Xf::forward<A>(arguments)...);
				}


				// -- M E T H O D S -------------------------------------------

				/* [call method] */
				Return call(A&&... arguments) const override {
					// call method on instance
					return (_instance->*_method)(Xf::forward<A>(arguments)...);
				}

				/* [clone method] */
				Base* clone(void) const override {
					// return new dynamic copy of self
					return new Derived(*this);
				}


				// -- M E M B E R S -------------------------------------------

				/* method pointer */
				Prototype _method;

				/* instance pointer */
				Pointer   _instance;

			};


			// -- P R I V A T E  M E M B E R S --------------------------------

			Base* _base;

	};







};

#endif

