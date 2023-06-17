#ifndef EVENT_HEADER
#define EVENT_HEADER

#include "macro.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "types.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "array.hpp"
#include "function.hpp"
#include "string.hpp"
#include "evntype.hpp"
#include "unique_pointer.hpp"
#include "stack.hpp"
#include "debug.hpp"

#include "poly_method.hpp"

class Input;
#include "input.hpp"



#include <iostream>


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	/* forward declaration */
	class Evntmode;

	/* event options enum */
	enum class Evntopt : unsigned int {
		/* force mode change */
		FORCE = 0x01,
		/* wait next loop */
		WAIT = 0x02,
		/* ignore mode change until next loop */
		IGNORE = 0x04,
		/* remove subscriber after event */
		ONE_SHOT = 0x08,
	};


	// -- E V E N T  C L A S S ------------------------------------------------

	class Event final {

		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* object pointer */
			template <typename C>
			using Pointer = C*;

			/* event prototype */
			template <typename C>
			using EventMethod = void(C::*)(void);

			/* event function prototype */
			using EventFunction = void(*)(void);

			/* input prototype */
			template <typename C>
			using InputMethod = void(C::*)(const xns::string&);

			/* input function prototype */
			using InputFunction = void(*)(const xns::string&);



			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			Event(void);

			/* non-assignable class */
			NON_ASSIGNABLE(Event);

			/* destructor */
			~Event(void);

			/* friend class */
			friend class Evntmode;


		public:

			// -- S T A T I C  M E T H O D S ----------------------------------

			/* get singleton instance */
			static Event& instance(void);


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* add mode */
			Evntmode new_mode(void);

			/* remove mode */
			void remove_mode(Evntmode&);

			/* set mode by name */
			void set_mode(const Evntmode&, const Evntopt = Evntopt::WAIT);

			/* apply mode */
			void next_mode(void);

			/* is mode active */
			bool is_mode(void) const;

			/* is mode active */
			bool is_mode(const Evntmode&) const;

			/* stack current mode */
			void stack_mode(void);

			/* stack mode */
			void stack_mode(const Evntmode&, const Evntopt = Evntopt::WAIT);

			/* unstack mode */
			void unstack_mode(void);




			/* call all event subscribers */
			void call_event(const Evntype);

			/* call all input subscribers */
			void call_input(const xns::string&);


		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* input vector type */
			using InputVector = xns::vector<xns::poly_method<void(const xns::string&)>>;

			/* event vector type */
			using EventVector = xns::vector<xns::poly_method<void(void)>>;

			/* event array type */
			using EventArray = xns::array<EventVector, IDX(Evntype::EVNT_MAX)>;


			/* mode type */
			using Mode = xns::pair<InputVector, EventArray>;

			/* mode list type */
			using Modelist = xns::vector<Mode>;


			/* optional type */
			using Optional = xns::unique_ptr<xns::size_t>;


			// -- P R I V A T E  M E T H O D S --------------------------------

			/* subscribe function to event */
			void _subscribe(const Evntmode&, const Evntype, EventFunction);

			/* subscribe function to input */
			void _subscribe(const Evntmode&, InputFunction);

			/* subscribe method to event */
			template <typename C>
			void _subscribe(const Evntmode&, const Evntype, EventMethod<C>, Pointer<C>);

			/* subscribe method to input */
			template <typename C>
			void _subscribe(const Evntmode&, InputMethod<C>, Pointer<C>);


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* mode list */
			Modelist _modes;

			/* current mode index */
			Optional _current;

			/* mode to apply next loop */
			Optional _next;

			/* mode index stack */
			xns::stack<xns::size_t> _stack;
			//Xf::Stack<Optional> _stack;

			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			/* singleton instance */
			static Event _instance;


	};



	// -- E V N T M O D E  C L A S S ------------------------------------------

	// this class purpose to be the interface for the user to add events in a mode
	// add event with string name is deprecated
	// this class will store an index to the vector of modes in the event class
	// this class cannot be instantiated outside the event class

	class Evntmode {

		private:

			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* deleted default constructor */
			Evntmode(void) = delete;

			/* index constructor */
			Evntmode(const xns::size_t idx);

			/* non-copyable */
			NON_COPYABLE(Evntmode);

			/* friend class */
			friend class Event;


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* mode index */
			xns::size_t _idx;

			/* state */
			bool _state;


		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* move constructor */
			Evntmode(Evntmode&&) noexcept;

			/* destructor */
			~Evntmode(void);


			// -- P U B L I C  O P E R A T O R S ------------------------------

			/* move assignment operator */
			Evntmode& operator=(Evntmode&&) noexcept;


			// -- A C C E S S O R S -------------------------------------------

			/* get mode index */
			inline xns::size_t idx(void) const { return _idx; }


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* subscribe function to event */
			void subscribe(const Evntype, Event::EventFunction);

			/* subscribe function to input */
			void subscribe(Event::InputFunction);

			/* subscribe method to event */
			template <typename C>
			void subscribe(const Evntype, Event::EventMethod<C>, Event::Pointer<C>);

			/* subscribe method to input */
			template <typename C>
			void subscribe(Event::InputMethod<C>, Event::Pointer<C>);
			// !!!
			//void subscribe(Event::EventMethod<C>, Event::Pointer<C>);

	};


	/* subscribe method to event */
	template <typename C>
	void Xf::Evntmode::subscribe(const Evntype type, Event::EventMethod<C> method, Event::Pointer<C> instance) {
		// exit if not in a valid mode
		if (!_state) { return; }
		// call event class method
		Event::instance()._subscribe(*this, type, method, instance);
	}

	/* subscribe method to input */
	template <typename C>
	//void Xf::Evntmode::subscribe(Event::EventMethod<C> method, Event::Pointer<C> instance) {
	void Xf::Evntmode::subscribe(Event::InputMethod<C> method, Event::Pointer<C> instance) {
		// exit if not in a valid mode
		if (!_state) { return; }
		// call event class method
		Event::instance()._subscribe(*this, method, instance);
	}

	/* subscribe method to event */
	template <typename C>
	void Xf::Event::_subscribe(const Evntmode& mode, const Evntype type, EventMethod<C> method, Pointer<C> instance) {
		// check invalid pointers and event type
		if (!method || !instance || type >= Evntype::EVNT_MAX) { return; }
		// get event subscriber vector
		EventVector& subscribers = _modes[mode._idx]._second[IDX(type)];
		// add new subscriber
		subscribers.emplace_back(method, instance);
	}

	/* subscribe method to input */
	template <typename C>
	void Xf::Event::_subscribe(const Evntmode& mode, InputMethod<C> method, Pointer<C> instance) {
		// check invalid pointers
		if (!method || !instance) { return; }
		// get input subscriber vector
		InputVector& subscribers = _modes[mode._idx]._first;
		// add new subscriber
		subscribers.emplace_back(method, instance);
	}

};




#endif
