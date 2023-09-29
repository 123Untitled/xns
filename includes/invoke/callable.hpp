#ifndef XNS_CALLABLE_HEADER
#define XNS_CALLABLE_HEADER

// local headers
#include "forward.hpp"
#include "macros.hpp"
#include "allocator.hpp"
#include "unique_ptr.hpp"


// c++ standard library headers
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C A L L A B L E  C L A S S ------------------------------------------

	// -- forward declaration -------------------------------------------------

	template <class>
	class callable;


	// -- specialization ------------------------------------------------------

	template <class R, class... A>
	class callable<R(A...)> final {

		public:

			// -- public types ------------------------------------------------

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


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			callable(void)
			: _base{nullptr} {}

			/* method reference constructor */
			template <typename C>
			explicit callable(method_prototype<C> method, reference<C> instance)
			: _base{xns::allocator<method_impl<C>>::allocate()} {
				// construct
				xns::allocator<method_impl<C>>::construct(_base, method, instance);
			}

			/* method pointer constructor */
			template <typename C>
			explicit callable(method_prototype<C> method, pointer<C> instance)
			: _base{xns::allocator<method_impl<C>>::allocate()} {
				// construct
				xns::allocator<method_impl<C>>::construct(
					static_cast<method_impl<C>*>(_base), method, instance);
			}

			/* function pointer constructor */
			explicit callable(function_prototype function)
			: _base{xns::allocator<function_impl>::allocate()} {
				// construct
				xns::allocator<function_impl>::construct(
					static_cast<function_impl*>(_base), function);
			}

			/* copy constructor */
			callable(const callable& other)
			: _base{other._base ? other._base->clone() : nullptr} {}

			/* move constructor */
			callable(callable&& other) noexcept
			: _base{other._base} {
				// invalidate other
				other._base = nullptr;
			}

			/* destructor */
			~callable(void) {
				// deallocate base
				if (_base) {
					// destroy base
					xns::allocator<base>::destroy(_base);
					// deallocate memory
					xns::allocator<base>::deallocate(_base);
				}
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			callable& operator=(const callable& other) {
				// check for self assignment
				if (this != &other) {
					// deallocate base
					if (_base) {
						// destroy base
						xns::allocator<base>::destroy(_base);
						// deallocate memory
						xns::allocator<base>::deallocate(_base);
					}
					// copy base
					_base = other._base ? other._base->clone() : nullptr;
				} // return self reference
				return *this;
			}

			/* move assignment operator */
			callable& operator=(callable&& other) noexcept {
				// check for self assignment
				if (this != &other) {
					// deallocate base
					if (_base) {
						// destroy base
						xns::allocator<base>::destroy(_base);
						// deallocate memory
						xns::allocator<base>::deallocate(_base);
					}
					// move base pointer
					_base = other._base;
					// invalidate other base pointer
					other._base = nullptr;
				} // return self reference
				return *this;
			}

			/* nullptr assignment operator */
			callable& operator=(xns::null) noexcept {
				// deallocate base
				if (_base) {
					// destroy base
					xns::allocator<base>::destroy(_base);
					// deallocate memory
					xns::allocator<base>::deallocate(_base);
				}
				// invalidate base pointer
				_base = nullptr;
				// return self reference
				return *this;
			}


			/* function call operator */
			return_type operator()(A&&... arguments) const {
				// call base method
				return _base->call(xns::forward<A>(arguments)...);
			}

			/* call method */
			return_type call(A&&... arguments) const {
				// call base method
				return _base->call(xns::forward<A>(arguments)...);
			}


		private:

			// -- private structs ---------------------------------------------

			struct base {

				/* default constructor */
				base(void) = default;

				/* non-assignable struct */
				NON_ASSIGNABLE(base);

				/* default destructor */
				virtual ~base(void) = default;

				/* virtual operator() method */
				virtual R operator()(A&&...) const = 0;

				/* virtual call method */
				virtual R call(A&&...) const = 0;

				/* virtual clone method */
				virtual base* clone(void) const = 0;

			};


			template <class C>
			struct method_impl final : public base {

				// -- types ---------------------------------------------------

				/* value type */
				using value = C;

				/* method pointer type */
				using prototype = callable::method_prototype<value>;

				/* instance reference type */
				using reference = callable::reference<value>;

				/* instance pointer type */
				using pointer = callable::pointer<value>;


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				method_impl(void)
				: _method{nullptr}, _instance{nullptr} {}

				/* method reference constructor */
				method_impl(prototype method, reference instance)
				: _method{method}, _instance{&instance} {}

				/* method pointer constructor */
				method_impl(prototype method, pointer instance)
				: _method{method}, _instance{instance} {}

				/* non-assignable struct */
				NON_ASSIGNABLE(method_impl);

				/* destructor */
				~method_impl(void) override = default;


				// -- overrides -----------------------------------------------

				/* function call operator */
				return_type operator()(A&&... arguments) const override {
					// call method on instance
					return (_instance->*_method)(xns::forward<A>(arguments)...);
				}

				/* call method */
				return_type call(A&&... arguments) const override {
					// call method on instance
					return (_instance->*_method)(xns::forward<A>(arguments)...);
				}

				/* clone method */
				base* clone(void) const override {
					// allocate memory
					method_impl* copy = xns::allocator<method_impl>::allocate();
					// construct copy
					xns::allocator<method_impl>::construct(copy, _method, _instance);
					// return copy
					return copy;
				}


				// -- members -------------------------------------------------

				/* method pointer */
				prototype _method;

				/* instance pointer */
				pointer   _instance;

			};


			struct function_impl final : public base {


				// -- types ---------------------------------------------------

				/* function pointer type */
				using prototype = callable::function_prototype;


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				function_impl(void)
				: _function{nullptr} {}

				/* function pointer constructor */
				function_impl(prototype function)
				: _function{function} {}

				/* non-assignable struct */
				NON_ASSIGNABLE(function_impl);

				/* destructor */
				~function_impl(void) override = default;


				// -- overrides -----------------------------------------------

				/* function call operator */
				return_type operator()(A&&... arguments) const override {
					// call function
					return _function(xns::forward<A>(arguments)...);
				}

				/* call function */
				return_type call(A&&... arguments) const override {
					// call function
					return _function(xns::forward<A>(arguments)...);
				}

				/* clone function */
				base* clone(void) const override {
					// allocate memory
					function_impl* copy = xns::allocator<function_impl>::allocate();
					// construct copy
					xns::allocator<function_impl>::construct(copy, _function);
					// return copy
					return copy;
				}


				// -- members -------------------------------------------------

				/* function pointer */
				prototype _function;

			};


			// -- private members ---------------------------------------------

			base* _base;

	};



}

#endif
