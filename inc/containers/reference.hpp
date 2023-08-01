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
			reference(const self&) noexcept = default;

			/* move constructor */
			reference(self&& other) noexcept = default;

			/* destructor */
			~reference(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			self& operator=(const self&) noexcept = default;

			/* move assignment operator */
			self& operator=(self&&) noexcept = default;


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


	// -- ref function --------------------------------------------------------

	/* create reference */
	template <class T>
	inline constexpr auto ref(T& ref) noexcept -> reference<T> {
		return reference<T>{ref};
	}

	/* deleted rvalue ref */
	template <class T>
	auto ref(T&&) noexcept -> reference<T> = delete;



	// -- cref function -------------------------------------------------------

	/* create const reference */
	template <class T>
	inline constexpr auto cref(const T& ref) noexcept -> reference<const T> {
		return reference<const T>{ref};
	}

	/* deleted rvalue cref */
	template <class T>
	auto cref(const T&&) noexcept -> reference<const T> = delete;



};

#endif
