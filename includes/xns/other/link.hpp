/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_LINK_HEADER
#define XNS_LINK_HEADER

// local headers
#include "xns/containers/vector.hpp"
#include "xns/type_traits/type_operations/move.hpp"


#include <type_traits>
// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	template <class O, class T>
	class link;


	// -- L I N K  C L A S S --------------------------------------------------

	/* bidirectional observer design pattern */
	/* do not use observer and observable directly */
	/* use:
	 * class A : public link<A, B> {};
	 * class B : public link<B, A> {};
	 */

	template <class O, class T> // O = observer, T = target
	class link {


		// -- assertions ------------------------------------------------------

		/* INFO: cannot assert because of circular dependency
		 * c++ does not allow inheritance forward declarations
		 * i love you anyway c++ <3
		 */


		public:
		private:

			// -- public types ------------------------------------------------

			/* self type */
			using self = link<O, T>;

			/* inverse type */
			using inverse = link<T, O>;

			/* observer type */
			using observer = O;

			/* observable type */
			using observable = T;


			// -- friends -----------------------------------------------------

			/* friend inverse */
			friend inverse;

			/* friend observer */
			friend observer;

			/* friend observable */
			friend observable;


		private:

			// -- private members ---------------------------------------------

			/* observers */
			xns::vector<inverse*> _observers;


		protected:
		private:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			link(void) noexcept
			: _observers{} {
			}

			/* copy constructor */
			link(const self& other)
			: _observers{other._observers} {}

			/* move constructor */
			link(self&& other) noexcept
			: _observers{xns::move(other._observers)} {}

			/* destructor */
			~link(void) noexcept {
				// goodbye
				for (auto& o : _observers) {
					o->detach(*this);
				}
			}

			// -- public modifiers --------------------------------------------

			/* attach observer */
			void attach(inverse& observ) noexcept {
				// WARNING: need to check if observer is already attached (very important !!!)
				std::cout << "link[" << this << "] attach: " << &observ << std::endl;
				// add observer
				_observers.copy_back(&observ);
				std::cout << "link[" << &observ << "] attach: " << this << std::endl;
				// also add self to observer
				observ._observers.copy_back(this);
			}

			/* detach observer */
			void detach(inverse& observ) noexcept {
				std::cout << "in detach of: " << this << std::endl;
				// remove observer
				//_observers.filter(&observ); temporary comment for avoid new vector errors
				// also remove self from observer
				//observ._observers.filter(this); temporary comment for avoid new vector errors
			}

			/* notify observers */
			void notify(void) noexcept {
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			self& operator=(const self& other) noexcept {
				// copy members
				_observers.operator=(other._observers);
				// return self reference
				return *this;
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// move members
				_observers.operator=(xns::move(other._observers));
				// return self reference
				return *this;
			}



	};

} // namespace xns

#endif // XNS_LINK_HEADER
