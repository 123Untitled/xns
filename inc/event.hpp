#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <iostream>
#include "Macro.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "Types.hpp"
#include "list.hpp"
#include "vector.hpp"
#include <string>
#include "pair.hpp"
#include "array.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	/* forward declaration */
	class Evntmode;

	/* event */
	enum class Evntype {
		ESCAPE, ENTER, BACKSPACE, DELETE, TAB, RETURN,
		LEFT, RIGHT, UP, DOWN,
		CHAR,
		CTRL_C,
		EVNT_MAX
	};


	// -- A L I A S E S -------------------------------------------------------

	/* function pointer */
	using Evntfunc = void*(*)(void*);

	/* object pointer */
	using Object = void*;


	// -- E V E N T  C L A S S ------------------------------------------------

	class Event final {

		public:

			// -- F O R W A R D  D E C L A R A T I O N S ----------------------

			/* mode forward declaration */
			class Mode;


		private:

			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			Event(void);

			/* non-assignable class */
			NON_ASSIGNABLE(Event);

			/* destructor */
			~Event(void);


			// -- P R I V A T E  F O R W A R D  D E C L A R A T I O N S -------

			/* observer forward declaration */
			class Observer;


		public:

			// -- S T A T I C  M E T H O D S ----------------------------------

			/* get singleton instance */
			static Event& instance(void);


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* add mode */
			void add_mode(std::string&&);

			/* set mode by name */
			void set_mode(const std::string&);

			/* subscribe to event */
			void subscribe(const Evntype, Evntfunc, Object);

			/* unsubscribe to event */
			void unsubscribe(const Evntype, Evntfunc, Object);

			/* call all observers */
			void call(const Evntype);

			/* clean up */
			void clear(void);


		private:


			// -- S T A T I C  P R I V A T E  A C C E S S O R S ---------------

			/* get head observer */
			//static Observer* head(const Evntype);


			// -- S T A T I C  P R I V A T E  M U T A T O R S -----------------

			/* set head observer */
			//static void head(const Evntype, Observer*);


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* modes vector */
			Xf::Vector<Mode> _modes;

			/* current mode */
			Mode* _current;

			using Obslist = Xf::Vector<Observer>[IDX(Evntype::EVNT_MAX)];

			using Pair = Xf::Pair<std::string, Obslist>;

			Xf::Vector<Pair> _observers;

			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			/* singleton instance */
			static Event _instance;




	};



	// -- M O D E  P R I V A T E  N E S T E D  S T R U C T --------------------

//	class Event::Mode final {
//
//		public:
//
//			// -- C O N S T R U C T O R S -------------------------------------
//
//			/* deleted default constructor */
//			Mode(void) = delete;
//
//			/* copy name constructor */
//			Mode(const std::string&);
//
//			/* move name constructor */
//			Mode(std::string&&) noexcept;
//
//			/* copy constructor */
//			Mode(const Mode&);
//
//			/* move constructor */
//			Mode(Mode&&) noexcept;
//
//			/* destructor */
//			~Mode(void);
//
//
//			// -- O P E R A T O R S -------------------------------------------
//
//			/* copy operator */
//			Mode& operator=(const Mode&);
//
//			/* move operator */
//			Mode& operator=(Mode&&);
//
//
//			// -- A C C E S S O R S -------------------------------------------
//
//			/* get name */
//			const std::string& name(void) const;
//
//			/* subscribe */
//			void subscribe(const Evntype, Evntfunc, Object);
//
//			/* unsubscribe */
//			void unsubscribe(const Evntype, Evntfunc, Object);
//
//
//
//
//		private:
//
//			// -- P R I V A T E  A L I A S E S --------------------------------
//
//			/* observer list */
//			using Obslist = Xf::Vector<Observer>;
//
//			// -- P R I V A T E  M E M B E R S --------------------------------
//
//			/* mode name */
//			std::string _name;
//
//			Obslist _observers[IDX(Evntype::EVNT_MAX)];
//
//
//	};


	// -- O B S E R V E R  C L A S S ------------------------------------------

	class Event::Observer final {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* deleted default constructor */
			Observer(void) = delete;

			/* initialize constructor */
			Observer(Evntfunc, Object);

			Observer(const Observer&) { }

			Observer(Observer&&) { }

			Observer& operator=(const Observer&) { return *this; }

			Observer& operator=(Observer&&) { return *this; }


			/* destructor */
			~Observer(void);


			// -- O P E R A T O R S -------------------------------------------

			/* equality operator */
			bool operator==(const Observer&) const;


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* call method on instance */
			void call(void);


			// -- A C C E S S O R S -------------------------------------------


			/* get method */
			Evntfunc method(void) const;

			/* get instance */
			const Object& instance(void) const;


		private:

			// -- P R I V A T E  M E M B E R S --------------------------------

			/* method to call */
			Evntfunc  _method;

			/* object to call method on */
			Object    _instance;


	};

};




#endif
