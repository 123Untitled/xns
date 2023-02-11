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


	// -- E V E N T  C L A S S ------------------------------------------------

	class Event final {

		private:

			// -- P R I V A T E  A L I A S E S --------------------------------

			/* object pointer */
			template <typename C>
			using Pointer = C*;

			/* prototype */
			template <typename C>
			using Prototype = void(C::*)(const std::string&);


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
			void add_mode(std::string&&);

			/* set mode by name */
			void set_mode(const std::string&);

			/* subscribe to event */
			template <typename C>
			void subscribe(const std::string& mode, const Evntype type, Prototype<C> method, Pointer<C> instance) {
				// check invalid type and method pointer
				if (type >= Evntype::EVNT_MAX || !method || !instance) { return; }
				// check invalid method
				if (!method) { return; }
				// get observer list
				PolyVector* obs = get_observers(mode, type);
				// check observer list
				if (!obs) { return; }
				// create new observer
				obs->emplace_back(method, instance);
			}

			/* unsubscribe to event */
			template <typename C>
			void unsubscribe(const std::string& mode, const Evntype type, Prototype<C> method, Pointer<C> instance) {
				// check invalid type
				if (type >= Evntype::EVNT_MAX) { return; }
				// get observer list
				PolyVector* obs = get_observers(mode, type);
				// check observer list
				if (!obs) { return; }
				// loop through all observers
				for (Size x = 0; x < obs->size(); ++x) { }
			}

			/* call all observers */
			void call(const Evntype, const std::string&);


		private:

			using LocalMethod = Xf::PolyMethod<void, const std::string&>;

			using PolyVector = Xf::Vector<LocalMethod>;

			using Obslist = Xf::Array<PolyVector, IDX(Evntype::EVNT_MAX)>;

			using Pair = Xf::Pair<std::string, Obslist>;


			// -- P R I V A T E  M E T H O D S --------------------------------

			/* get mode */
			Obslist* get_mode(const std::string& mode);

			/* get observer list */
			PolyVector* get_observers(const std::string& mode, const Evntype type);



			// -- P R I V A T E  M E M B E R S --------------------------------

			Xf::Vector<Pair> _observers;

			Obslist* _current;

			// -- S T A T I C  P R I V A T E  M E M B E R S -------------------

			/* singleton instance */
			static Event _instance;

	};


};




#endif
