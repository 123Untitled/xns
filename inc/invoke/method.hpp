#ifndef METHOD_HEADER
#define METHOD_HEADER

#include "types.hpp"
#include "forward.hpp"
#include "move.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E T H O D  C L A S S ----------------------------------------------

	/* empty declaration */
	template <class, class, class...>
	class method;

	template <class O, class R, class... A>
	class method<O, R(A...)> final {

		public:

			// -- P U B L I C  T Y P E S --------------------------------------

			/* self type */
			using self        = method<O, R(A...)>;

			/* object type */
			using object      = O;

			/* prototype type */
			using prototype   = R(O::*)(A...);

			/* return type */
			using return_type = R;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			method(void) noexcept
			: _method{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			method(xns::null) noexcept
			: _method{nullptr} {
				// code here...
			}

			/* method pointer constructor */
			method(const prototype method) noexcept
			: _method{method} {
				// code here...
			}

			/* copy constructor */
			method(const self& other) noexcept
			: _method{other._method} {
				// code here...
			}

			/* move constructor */
			method(self&& other) noexcept
			: _method{xns::move(other._method)} {
				// code here...
			}

			/* destructor */
			~method(void) noexcept = default;


			// -- P U B L I C  A S S I G N M E N T ----------------------------

			/* nullptr assignment */
			self& assign(xns::null) noexcept {
				// set method pointer to null
				_method = nullptr;
				// return self reference
				return *this;
			}

			/* method pointer assignment */
			self& assign(const prototype method) noexcept {
				// set method pointer
				_method = method;
				// return self reference
				return *this;
			}

			/* copy assignment */
			self& assign(const self& other) noexcept {
				// copy method pointer
				_method = other._method;
				// return self reference
				return *this;
			}

			/* move assignment */
			self& assign(self&& other) noexcept {
				// move method pointer
				_method = xns::move(other._method);
				// return self reference
				return *this;
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* nullptr assignment operator */
			self& operator=(xns::null) noexcept {
				// return nullptr assignment
				return assign(nullptr);
			}

			/* method pointer assignment operator */
			self& operator=(const prototype method) noexcept {
				// return method pointer assignment
				return assign(method);
			}

			/* copy assignment operator */
			self& operator=(const self& other) noexcept {
				// return copy assignment
				return assign(other);
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// return move assignment
				return assign(xns::move(other));
			}


			// -- P U B L I C  B O O L E A N  O P E R A T O R S ---------------

			/* boolean operator */
			explicit operator bool(void) const noexcept {
				// return method pointer validity
				return _method != nullptr;
			}

			/* not operator */
			bool operator!(void) const noexcept {
				// return method pointer invalidity
				return _method == nullptr;
			}


			// -- P U B L I C  C O M P A R I S O N  O P E R A T O R S ---------

			/* equality operator */
			bool operator==(const self& other) const noexcept {
				// return true if method pointers are equal
				return _method == other._method;
			}

			/* inequality operator */
			bool operator!=(const self& other) const noexcept {
				// return true if function pointers are not equal
				return _method != other._method;
			}


			// -- P U B L I C  C A L L  O P E R A T O R -----------------------

			/* method call operator */
			return_type operator()(object& instance, A&&... arguments) {
				// call method
				return (instance.*_method)(xns::forward<A>(arguments)...);
				//return _method(Xf::forward<A>(arguments)...);
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* call */
			return_type call(object& instance, A&&... arguments) const {
				// call method
				return (instance.*_method)(xns::forward<A>(arguments)...);
				//return _method(Xf::forward<A>(arguments)...);
			}

			/* reset */
			void reset(void) noexcept {
				// set function pointer to null
				_method = nullptr;
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* method pointer */
			prototype _method;


	};



}

#endif
