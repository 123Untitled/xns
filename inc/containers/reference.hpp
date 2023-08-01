#ifndef REFERENCE_HEADER
#define REFERENCE_HEADER

// local headers
#include "is_same.hpp"
#include "remove.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E F E R E N C E  C L A S S ----------------------------------------

	template <class T>
	class reference final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = reference<T>;

			/* value type */
			using value_type = T;


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			reference(void) = delete;

			/* lvalue reference constructor */
			reference(value_type& ref) noexcept
			: _ref{&ref} {}

			/* deleted rvalue reference constructor */
			reference(value_type&&) = delete;

			/* copy constructor */
			reference(const self& other) noexcept
			: _ref{other._ref} {}

			/* move constructor */
			reference(self&& other) noexcept
			: reference{other} {}

			/* destructor */
			~reference(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			self& operator=(const self& other) noexcept {
				_ref = other._ref;
				return *this;
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				return operator=(other);
			}


			// -- public accessors --------------------------------------------

			/* get value */
			inline value_type& get(void) const noexcept {
				return *_ref;
			}

			/* implicit conversion operator */
			inline operator value_type&(void) const noexcept {
				return *_ref;
			}


		private:

			// -- private members ---------------------------------------------

			/* pointer */
			value_type* _ref;

	};

};

#endif
