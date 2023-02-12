#ifndef EVENT_HEADER
#define EVENT_HEADER

#include "Macro.hpp"
#include "move.hpp"
#include "forward.hpp"
#include "Types.hpp"
#include "list.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "array.hpp"
#include "function.hpp"

#include <iostream>
#include <string>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	/* event */
	enum class Evntype {
		ESCAPE, ENTER, BACKSPACE, DELETE, TAB, RETURN,
		LEFT, RIGHT, UP, DOWN,
		CHAR,
		CTRL_C,
		EVNT_MAX
	};

	/* method type */
	enum class MethodType { INPUT, EVENT, METHOD_TYPE_MAX };


	// -- E V E N T  C L A S S ------------------------------------------------

	class Event final {

		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* string type */
			using String = std::string;

			/* object pointer */
			template <typename C>
			using Pointer = C*;

			/* event prototype */
			template <typename C>
			using EventPrototype = void(C::*)(void);

			/* input prototype */
			template <typename C>
			using InputPrototype = void(C::*)(const String&);



			// -- P R I V A T E  C O N S T R U C T O R S ----------------------

			/* default constructor */
			Event(void);

			/* non-assignable class */
			NON_ASSIGNABLE(Event);

			/* destructor */
			~Event(void);


		public:

			// -- S T A T I C  M E T H O D S ----------------------------------

			/* get singleton instance */
			static Event& instance(void);


			// -- P U B L I C  M E T H O D S ----------------------------------

			/* add mode */
			void add_mode(String&&);

			/* set mode by name */
			bool set_mode(const String&);

			/* subscribe to event */
			template <typename C>
			void subscribe_event(const String& mode, const Evntype type, EventPrototype<C> method, Pointer<C> instance) {
				// check invalid pointers
				if (!method || !instance) { return; }
				// check event type
				if (type < Evntype::EVNT_MAX) {
					// get event subscriber vector
					EventVector* subscribers = get_event_subscribers(mode, type);
					// check pointer
					if (!subscribers) { return; }
					// add new subscriber
					subscribers->emplace_back(method, instance);
				}
			}

			/* subscribe to input */
			template <typename C>
			void subscribe_input(const String& mode, InputPrototype<C> method, Pointer<C> instance) {
				// check invalid pointers
				if (!method || !instance) { return; }
				// get input subscriber vector
				InputVector* subscribers = get_input_subscribers(mode);
				// check pointer
				if (!subscribers) { return; }
				// add new subscriber
				subscribers->emplace_back(method, instance);
			}

			/* unsubscribe to event */
			template <typename C>
			void unsubscribe_event(const String& mode, const Evntype type, EventPrototype<C> method, Pointer<C> instance) {

				/* -> */ return; // INFO: this method is not implemented yet

				//// check invalid type
				//if (type >= Evntype::EVNT_MAX) { return; }
				//// get subscriber vector
				//EventVector* subscribers = get_event_subscribers(mode, type);
				//// check pointer
				//if (!subscribers) { return; }
				//// loop through all observers
				//for (Size x = 0; x < subscribers->size(); ++x) { }
			}

			/* call all event subscribers */
			void call_event(const Evntype);

			/* call all input subscribers */
			void call_input(const String&);



		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* input method type */
			using InputMethod = Xf::PolyMethod<void(const std::string&)>;

			/* input vector type */
			using InputVector = Xf::Vector<InputMethod>;


			/* event method type */
			using EventMethod = Xf::PolyMethod<void(void)>;

			/* event vector type */
			using EventVector = Xf::Vector<EventMethod>;

			/* event array type */
			using EventArray = Xf::Array<EventVector, IDX(Evntype::EVNT_MAX)>;


			/* mode type */
			using Mode = Xf::Pair<InputVector, EventArray>;

			/* mode pair type */
			using Modepair = Xf::Pair<std::string, Mode>;

			/* mode list type */
			using Modelist = Xf::Vector<Modepair>;


			// -- P R I V A T E  M E T H O D S --------------------------------

			/* get mode */
			Mode* get_mode(const std::string& mode);

			/* get event subscribers */
			EventVector* get_event_subscribers(const String& mode, const Evntype type);

			/* get input subscribers */
			InputVector* get_input_subscribers(const String& mode);

			/* mode exists */
			bool mode_exists(const std::string& mode) const;

			/* get current mode index */
			Size get_current_idx(void) const;



			// -- P R I V A T E  M E M B E R S --------------------------------

			/* mode list */
			Modelist _modes;

			/* current mode */
			Mode* _current;


			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			/* singleton instance */
			static Event _instance;

	};


};




#endif
