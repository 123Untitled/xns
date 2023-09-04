#ifndef FUNCTION_HEADER
#define FUNCTION_HEADER

#include "forward.hpp"
#include "macro.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F U N C T I O N  C L A S S ------------------------------------------

	/* empty declaration */
	template <class, class...>
	class function;

	template <class R, class... A>
	class function<R(A...)> final {

		public:

			// -- P U B L I C  T Y P E S --------------------------------------

			/* self type */
			using self = function<R(A...)>;

			/* prototype type */
			using prototype = R(*)(A...);

			/* return type */
			using return_type = R;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			function(void) noexcept
			: _function{nullptr} {
				// code here...
			}

			/* nullptr constructor */
			function(xns::null) noexcept
			: _function{nullptr} {
				// code here...
			}

			/* function pointer constructor */
			function(const prototype function) noexcept
			: _function{function} {
				// code here...
			}

			/* copy constructor */
			function(const self& other) noexcept
			: _function{other._function} {
				// code here...
			}

			/* move constructor */
			function(self&& other) noexcept
			: _function{xns::move(other._function)} {
				// code here...
			}

			/* destructor */
			~function(void) noexcept = default;


			// -- P U B L I C  A S S I G N M E N T ----------------------------

			/* nullptr assignment */
			self& assign(xns::null) noexcept {
				// set function pointer to null
				_function = nullptr;
				// return self reference
				return *this;
			}

			/* function pointer assignment */
			self& assign(const prototype function) noexcept {
				// set function pointer
				_function = function;
				// return self reference
				return *this;
			}

			/* copy assignment */
			self& assign(const self& other) noexcept {
				// copy function pointer
				_function = other._function;
				// return self reference
				return *this;
			}

			/* move assignment */
			self& assign(self&& other) noexcept {
				// move function pointer
				_function = xns::move(other._function);
				// return self reference
				return *this;
			}


			// -- P U B L I C  A S S I G N M E N T  O P E R A T O R S ---------

			/* nullptr assignment operator */
			self& operator=(xns::null) noexcept {
				// return assign method
				return assign(nullptr);
			}


			/* function pointer assignment operator */
			self& operator=(const prototype function) noexcept {
				// return assign method
				return assign(function);
			}

			/* copy assignment operator */
			self& operator=(const self& other) noexcept {
				// return assign method
				return assign(other);
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// return assign method
				return assign(xns::move(other));
			}


			// -- P U B L I C  B O O L E A N  O P E R A T O R S ---------------

			/* boolean operator */
			explicit operator bool(void) const noexcept {
				// return function pointer validity
				return _function != nullptr;
			}

			/* not operator */
			bool operator!(void) const noexcept {
				// return function pointer invalidity
				return _function == nullptr;
			}


			// -- P U B L I C  C O M P A R I S O N  O P E R A T O R S ---------

			/* equality operator */
			bool operator==(const self& other) const noexcept {
				// return true if function pointers are equal
				return _function == other._function;
			}

			/* inequality operator */
			bool operator!=(const self& other) const noexcept {
				// return true if function pointers are not equal
				return _function != other._function;
			}


			// -- P U B L I C  C A L L  O P E R A T O R -----------------------

			/* function call operator */
			return_type operator()(A&&... arguments) {
				// call function
				return _function(xns::forward<A>(arguments)...);
			}


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* call */
			return_type call(A&&... arguments) const {
				// call function
				return _function(xns::forward<A>(arguments)...);
			}

			/* reset */
			void reset(void) noexcept {
				// set function pointer to null
				_function = nullptr;
			}


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* function pointer */
			prototype _function;

	};


}

#endif

