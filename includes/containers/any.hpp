#ifndef XNS_ANY_HEADER
#define XNS_ANY_HEADER

#include "macros.hpp"
#include "allocator.hpp"
#include "unique_ptr.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A N Y  C L A S S ----------------------------------------------------

	class any {

		private:

			// -- B A S E  S T R U C T ----------------------------------------

			struct base {


				/* default constructor */
				base(void) = default;

				/* destructor */
				virtual ~base(void) = default;

				/* non-assignable class */
				NON_ASSIGNABLE(base);

				/* clone */
				virtual xns::unique_ptr<base> clone(void) const = 0;

			};


			// -- D E R I V E D  S T R U C T ----------------------------------

			template <class T>
			struct derived final : public base {


				// -- T Y P E S -----------------------------------------------

				/* value type */
				using value_type = T;


				// -- C O N S T R U C T O R S ---------------------------------

				/* default constructor */
				derived(void)
				: _value{} { }

				/* value constructor */
				derived(const T& value)
				: _value{value} { }

				/* move value constructor */
				derived(T&& value)
				: _value{xns::move(value)} {
				}

				/* destructor */
				~derived(void) override = default;

				/* non-assignable class */
				NON_ASSIGNABLE(derived);


				// -- O V E R R I D E S ---------------------------------------

				/* clone */
				xns::unique_ptr<base> clone(void) const override {
					return xns::make_unique<derived<T>>(_value);
				}


				// -- M E M B E R S -------------------------------------------

				/* value */
				T _value;

			};


		public:


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			any(void)
			: _ptr{nullptr} { }

			/* value constructor */
			template <class T>
			any(const T& value)
			: _ptr{xns::make_unique<derived<T>>(value)} {
				// nothing to do...
			}

			/* move value constructor */
			template <class T>
			any(T&& value)
			: _ptr{xns::make_unique<derived<T>>(xns::move(value))} {
				// nothing to do...
			}

			/* copy constructor */
			any(const any& other)
			: _ptr{other._ptr ? other._ptr->clone() : nullptr} {
				// nothing to do...
			}

			/* move constructor */
			any(any&& other)
			: _ptr{xns::move(other._ptr)} {
				// nothing to do...
			}

			/* destructor */
			~any(void) = default;


			// -- A S S I G N M E N T  O P E R A T O R S ----------------------

			/* copy assignment operator */
			any& operator=(const any& other) {
				// check for self-assignment
				if (this != &other) {
					// clone
					_ptr = other._ptr ? other._ptr->clone() : nullptr;
				} // return self reference
				return *this;
			}

			/* move assignment operator */
			any& operator=(any&& other) {
				// check for self-assignment
				if (this != &other) {
					// move
					_ptr = xns::move(other._ptr);
				} // return self reference
				return *this;
			}


			template <class T>
			T& s_cast(void) {
				using type = xns::remove_cvr<T>;

				derived<type>* der = reinterpret_cast<derived<type>*>(&*_ptr);

				return der->_value;
			}

			template <class T>
			T& d_cast(void) const {
				return     dynamic_cast<const derived<T>*>(&*_ptr)->_value;
			}

			template <class T>
			T& r_cast(void) const {
				return reinterpret_cast<const derived<T>*>(&*_ptr)->_value;
			}


			// -- A C C E S S O R S -------------------------------------------

			/* check if empty */
			bool has_value(void) const {
				return _ptr != nullptr;
			}


		private:

			// -- P T R -------------------------------------------------------

			/* pointer to base */
			xns::unique_ptr<base> _ptr;

	};




}

#endif
