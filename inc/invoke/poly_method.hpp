#ifndef POLY_METHOD_HEADER
#define POLY_METHOD_HEADER

#include "type_traits.hpp"
#include "forward.hpp"
#include "macro.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- P O L Y  M E T H O D  C L A S S -------------------------------------

	/* empty definition */
	template <class>
	class poly_method;

	template <class R, class... A>
	class poly_method<R(A...)> final {

		public:

			// -- T Y P E S ---------------------------------------------------

			/* method pointer type */
			template <class C>
			using method_prototype = R(C::*)(A...);

			/* function pointer type */
			using function_prototype = R(*)(A...);

			/* return type */
			using return_type = R;

			/* instance reference type */
			template <class C>
			using reference = C&;

			/* instance pointer type */
			template <class C>
			using pointer = C*;



			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			poly_method(void)
			: _base{nullptr} {
				// code here...
			}

			/* method reference constructor */
			template <typename C>
			explicit poly_method(method_prototype<C> method, reference<C> instance)
			: _base{new Method<C>{method, instance}} { // WARNING: NEED RENAME METHOD SUBCLASS !!!!!!
				// code here...
			}

			/* method pointer constructor */
			template <typename C>
			explicit poly_method(method_prototype<C> method, pointer<C> instance)
			: _base{new Method<C>{method, instance}} {
				// code here...
			}

			/* function pointer constructor */
			explicit poly_method(function_prototype function)
			: _base{new Function{function}} {
				// code here...
			}

			/* [copy constructor] */
			poly_method(const poly_method& other)
			: _base{other._base ? other._base->clone() : nullptr} {
				// code here...
			}

			/* [move constructor] */
			poly_method(poly_method&& other) noexcept
			: _base{other._base} {
				// invalidate other base pointer
				other._base = nullptr;
			}

			/* [destructor] */
			~poly_method(void) {
				// deallocate base
				if (_base) { delete _base; }
			}


			// -- O P E R A T O R S -------------------------------------------

			/* [copy assignment operator] */
			poly_method& operator=(const poly_method& other) {
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
			poly_method& operator=(poly_method&& other) noexcept {
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

			/* nullptr assignment operator */
			poly_method& operator=(xns::null) noexcept {
				// deallocate base
				if (_base) { delete _base; }
				// invalidate base pointer
				_base = nullptr;
				// return self reference
				return *this;
			}

			/* [function call operator] */
			return_type operator()(A&&... arguments) const {
				// call base method
				return _base->call(Xf::forward<A>(arguments)...);
			}


			// -- M E T H O D S -----------------------------------------------

			/* [call method] */
			return_type call(A&&... arguments) const {
				// call base method
				return _base->call(Xf::forward<A>(arguments)...);
			}


		private:

			// -- P R I V A T E  N E S T E D  S T R U C T S -------------------

			struct Base {

				/* default constructor */
				Base(void) = default;

				/* non-assignable struct */
				NON_ASSIGNABLE(Base);

				/* default destructor */
				virtual ~Base(void) = default;

				/* virtual operator() method */
				virtual R operator()(A&&...) const = 0;

				/* virtual call method */
				virtual R call(A&&...) const = 0;

				/* virtual clone method */
				virtual Base* clone(void) const = 0;

			};


			template <typename C>
			struct Method final : public Base {

				// -- A L I A S E S -------------------------------------------

				/* value type */
				using Value = C;

				/* method pointer type */
				using prototype = poly_method::method_prototype<C>;

				/* instance reference type */
				using reference = poly_method::reference<C>;

				/* instance pointer type */
				using pointer = poly_method::pointer<C>;


				// -- C O N S T R U C T O R S ---------------------------------

				/* [default constructor] */
				Method(void)
				: _method{nullptr}, _instance{nullptr} {
					// code here...
				}

				/* [prototype reference constructor] */
				Method(prototype method, reference instance)
				: _method{method}, _instance{&instance} {
					// code here...
				}

				/* [prototype pointer constructor] */
				Method(prototype method, pointer instance)
				: _method{method}, _instance{instance} {
					// code here...
				}

				/* [copy constructor] */
				Method(const Method& other)
				: _method{other._method}, _instance{other._instance} {
					// code here...
				}

				/* [move constructor] */
				Method(Method&& other)
				: Method{other} {
					// code here...
				}

				/* [destructor] */
				~Method(void) override = default;


				// -- O P E R A T O R S ---------------------------------------

				/* [copy assignment operator] */
				Method& operator=(const Method& other) {
					// copy method pointer
					_method = other._method;
					// copy instance pointer
					_instance = other._instance;
					// return self reference
					return *this;
				}

				/* [move assignment operator] */
				Method& operator=(Method&& other) {
					// call copy assignment operator
					return Method::operator=(other);
				}

				/* [function call operator] */
				return_type operator()(A&&... arguments) const override {
					// call method on instance
					return (_instance->*_method)(Xf::forward<A>(arguments)...);
				}


				// -- M E T H O D S -------------------------------------------

				/* [call method] */
				return_type call(A&&... arguments) const override {
					// call method on instance
					return (_instance->*_method)(Xf::forward<A>(arguments)...);
				}

				/* [clone method] */
				Base* clone(void) const override {
					// return new dynamic copy of self
					return new Method(*this);
				}


				// -- M E M B E R S -------------------------------------------

				/* method pointer */
				prototype _method;

				/* instance pointer */
				pointer   _instance;

			};


			struct Function final : public Base {

				// -- A L I A S E S -------------------------------------------

				/* function pointer type */
				using prototype = poly_method::function_prototype;


				// -- C O N S T R U C T O R S ---------------------------------

				/* default constructor */
				Function(void)
				: _function{nullptr} {
					// code here...
				}

				/* function pointer constructor */
				Function(prototype function)
				: _function{function} {
					// code here...
				}

				/* copy constructor */
				Function(const Function& other)
				: _function{other._function} {
					// code here...
				}

				/* move constructor */
				Function(Function&& other)
				: Function{other} {
					// code here...
				}

				/* destructor */
				~Function(void) override = default;


				// -- O P E R A T O R S ---------------------------------------

				/* copy assignment operator */
				Function& operator=(const Function& other) {
					// copy function pointer
					_function = other._function;
					// return self reference
					return *this;
				}

				/* move assignment operator */
				Function& operator=(Function&& other) {
					// call copy assignment operator
					return Function::operator=(other);
				}

				/* function call operator */
				return_type operator()(A&&... arguments) const override {
					// call function
					return _function(Xf::forward<A>(arguments)...);
				}


				// -- M E T H O D S -------------------------------------------

				/* call function */
				return_type call(A&&... arguments) const override {
					// call function
					return _function(Xf::forward<A>(arguments)...);
				}

				/* clone function */
				Base* clone(void) const override {
					// return new dynamic copy of self
					return new Function(*this);
				}


				// -- M E M B E R S -------------------------------------------

				/* function pointer */
				prototype _function;

			};


			// -- P R I V A T E  M E M B E R S --------------------------------

			Base* _base;

	};



}

#endif
