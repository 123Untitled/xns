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
#include "unique_ptr.hpp"
#include "stack.hpp"
#include "debug.hpp"


#include "poly_method.hpp"

//class Input;
//#include "input.hpp"



#include <iostream>


// -- N A M E S P A C E -------------------------------------------------------

namespace xns {

	/* forward declaration */
	class evntmode;

	/* event options enum */
	enum class evntopt : unsigned int {
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

	class event final {

		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* object pointer */
			template <typename C>
			using pointer = C*;

			/* event prototype */
			template <typename C>
			using event_method = void(C::*)(void);

			/* event function prototype */
			using event_function = void(*)(void);

			/* input prototype */
			template <typename C>
			using input_method = void(C::*)(const xns::string&);

			/* input function prototype */
			using input_function = void(*)(const xns::string&);



			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			event(void);

			/* non-assignable class */
			NON_ASSIGNABLE(event);

			/* destructor */
			~event(void);

			/* friend class */
			friend class evntmode;





		public:


			/* string type */
			using string = xns::string;

			/* character type */
			using char_t = typename string::char_t;

			/* size type */
			using size_type = typename string::size_type;

			/* signed type */
			using signed_type = typename string::signed_type;

			/* start loop */
			static void start_loop(void);

			/* stop input loop */
			static void stop_loop(void);

			/* parameters */
			static void parameters(const bool windowed);





			// -- S T A T I C  M E T H O D S ----------------------------------

			/* get singleton instance */
			static event& instance(void);


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* add mode */
			evntmode new_mode(void);

			/* remove mode */
			void remove_mode(evntmode&);

			/* set mode by name */
			void set_mode(const evntmode&, const evntopt = evntopt::WAIT);

			/* apply mode */
			void next_mode(void);

			/* is mode active */
			bool is_mode(void) const;

			/* is mode active */
			bool is_mode(const evntmode&) const;

			/* stack current mode */
			void stack_mode(void);

			/* stack mode */
			void stack_mode(const evntmode&, const evntopt = evntopt::WAIT);

			/* unstack mode */
			void unstack_mode(void);




			/* call all event subscribers */
			void call_event(const xns::evntype);

			/* call all input subscribers */
			void call_input(const xns::string&);


		private:

			enum { BUFFER_SIZE = 1024 };

			/* read input while available */
			static void read_input(void);

			/* read input from stdin */
			static signed_type read_stdin(void);

			/* dispatch to subscribers */
			static void dispatch(void);


			/* input string */
			static string _input;

			/* buffer */ // TODO: implement resize method in string class
			static char_t _buff[BUFFER_SIZE + 1];

			/* readed bytes */
			static signed_type _readed;


			static bool _is_running;
			static bool _windowed;




			// -- P R I V A T E  A L I A S E S --------------------------------

			/* input vector type */
			using input_vector = xns::vector<xns::poly_method<void(const xns::string&)>>;

			/* event vector type */
			using event_vector = xns::vector<xns::poly_method<void(void)>>;

			/* event array type */
			using event_array = xns::array<event_vector, IDX(evntype::EVNT_MAX)>;


			/* mode type */
			using mode = xns::pair<input_vector, event_array>;

			/* mode list type */
			using mode_list = xns::vector<mode>;


			/* optional type */
			using optional = xns::unique_ptr<xns::size_t>;


			// -- P R I V A T E  M E T H O D S --------------------------------

			/* subscribe function to event */
			void _subscribe(const evntmode&, const evntype, event_function);

			/* subscribe function to input */
			void _subscribe(const evntmode&, input_function);

			/* subscribe method to event */
			template <typename C>
			void _subscribe(const evntmode&, const evntype, event_method<C>, pointer<C>);

			/* subscribe method to input */
			template <typename C>
			void _subscribe(const evntmode&, input_method<C>, pointer<C>);


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* mode list */
			mode_list _modes;

			/* current mode index */
			optional _current;

			/* mode to apply next loop */
			optional _next;

			/* mode index stack */
			xns::stack<xns::size_t> _stack;
			//Xf::Stack<Optional> _stack;

			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			/* singleton instance */
			static event _instance;


	};



	// -- E V N T M O D E  C L A S S ------------------------------------------

	// this class purpose to be the interface for the user to add events in a mode
	// add event with string name is deprecated
	// this class will store an index to the vector of modes in the event class
	// this class cannot be instantiated outside the event class

	class evntmode {

		private:

			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* deleted default constructor */
			evntmode(void) = delete;

			/* index constructor */
			evntmode(const xns::size_t idx);

			/* non-copyable */
			NON_COPYABLE(evntmode);

			/* friend class */
			friend class event;


			// -- P R I V A T E  M E M B E R S --------------------------------

			/* mode index */
			xns::size_t _idx;

			/* state */
			bool _state;


		public:

			// -- P U B L I C  C O N S T R U C T O R S ------------------------

			/* move constructor */
			evntmode(evntmode&&) noexcept;

			/* destructor */
			~evntmode(void);


			// -- P U B L I C  O P E R A T O R S ------------------------------

			/* move assignment operator */
			evntmode& operator=(evntmode&&) noexcept;


			// -- A C C E S S O R S -------------------------------------------

			/* get mode index */
			inline xns::size_t idx(void) const { return _idx; }


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* subscribe function to event */
			void subscribe(const evntype, event::event_function);

			/* subscribe function to input */
			void subscribe(event::input_function);

			/* subscribe method to event */
			template <typename C>
			void subscribe(const evntype, event::event_method<C>, event::pointer<C>);

			/* subscribe method to input */
			template <typename C>
			void subscribe(event::input_method<C>, event::pointer<C>);
			// !!!
			//void subscribe(Event::EventMethod<C>, Event::Pointer<C>);

	};


	/* subscribe method to event */
	template <typename C>
	void xns::evntmode::subscribe(const evntype type, event::event_method<C> method, event::pointer<C> instance) {
		// exit if not in a valid mode
		if (!_state) { return; }
		// call event class method
		event::instance()._subscribe(*this, type, method, instance);
	}

	/* subscribe method to input */
	template <typename C>
	//void Xf::Evntmode::subscribe(Event::EventMethod<C> method, Event::Pointer<C> instance) {
	void xns::evntmode::subscribe(event::input_method<C> method, event::pointer<C> instance) {
		// exit if not in a valid mode
		if (!_state) { return; }
		// call event class method
		event::instance()._subscribe(*this, method, instance);
	}

	/* subscribe method to event */
	template <typename C>
	void xns::event::_subscribe(const evntmode& mode, const evntype type, event_method<C> method, pointer<C> instance) {
		// check invalid pointers and event type
		if (!method || !instance || type >= evntype::EVNT_MAX) { return; }
		// get event subscriber vector
		event_vector& subscribers = _modes[mode._idx]._second[IDX(type)];
		// add new subscriber
		subscribers.emplace_back(method, instance);
	}

	/* subscribe method to input */
	template <typename C>
	void xns::event::_subscribe(const evntmode& mode, input_method<C> method, pointer<C> instance) {
		// check invalid pointers
		if (!method || !instance) { return; }
		// get input subscriber vector
		input_vector& subscribers = _modes[mode._idx]._first;
		// add new subscriber
		subscribers.emplace_back(method, instance);
	}

};




#endif
