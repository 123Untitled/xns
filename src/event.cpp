#include "event.hpp"


// -- P R I V A T E  C O N S T R U C T O R S ----------------------------------

/* default constructor */
Xf::Event::Event(void)
: _observers{}, _current{nullptr} {
	// code here...
}

/* destructor */
Xf::Event::~Event(void) {
	// code here...
}


// -- S T A T I C  M E T H O D S ----------------------------------------------

/* get singleton instance */
Xf::Event& Xf::Event::instance(void) {
	// return instance
	return _instance;
}


// -- P U B L I C  M E T H O D S ----------------------------------------------

/* add mode */
void Xf::Event::add_mode(std::string&& name) {
	// check invalid name
	if (name.empty()) { return; }
	// loop through all modes
	for (Size x = 0; x < _observers.size(); ++x) {
		// check mode already exists
		if (_observers[x]._first == name) {
			// exit method
			return;
		} // add mode
	}
	_observers.emplace_back(Xf::move(Pair{
				Xf::move(name), Xf::move(Obslist{})
			}
		)
	);
	// return new mode
	return;
}

/* set mode by name */
void Xf::Event::set_mode(const std::string& name) {
	// loop through all modes
	for (Size x = 0; x < _observers.size(); ++x) {
		// check mode name
		if (_observers[x]._first == name) {
			// set new current mode
			_current = &_observers[x]._second;
			// exit method
			return;
		}
	}
}


/* subscribe to event */
void Xf::Event::subscribe(const std::string& mode, const Evntype type, Evntfunc method, Object instance) {
	// check invalid type and method pointer
	if (type >= Evntype::EVNT_MAX || !method) { return; }
	// check invalid method
	if (!method) { return; }
	// get observer list
	Xf::Vector<Observer>* obs = get_observers(mode, type);
	// check observer list
	if (!obs) { return; }
	// create new observer
	//obs->emplace_back(Observer(method, instance));
	obs->emplace_back(method, instance);

}

/* unsubscribe to event */
void Xf::Event::unsubscribe(const std::string& mode, const Evntype type, Evntfunc method, Object instance) {
	// check invalid type
	if (type >= Evntype::EVNT_MAX) { return; }
	// get observer list
	Xf::Vector<Observer>* obs = get_observers(mode, type);
	// check observer list
	if (!obs) { return; }
	// create new observer to be compared
	Observer search{method, instance};
	// loop through all observers
	for (Size x = 0; x < obs->size(); ++x) {
		// check observer
		if ((*obs)[x] == search) {
			// remove observer
			//obs->erase(x);
			// exit method
			return;
		}
	}


}

/* call all observers */
void Xf::Event::call(const Evntype type) {
	// check current mode
	if (!_current) { return; }
	// check invalid type
	if (type >= Evntype::EVNT_MAX) { return; }
	// get observers indexed by type
	Xf::Vector<Observer>& evntobs = (*_current)[(IDX(type))];
	// loop through all observers
	for (Size x = 0; x < evntobs.size(); ++x) {
		// call observer
		evntobs[x].call();
	}
}


// -- P R I V A T E  M E T H O D S --------------------------------------------

/* get mode */
Xf::Event::Obslist* Xf::Event::get_mode(const std::string& name) {
	// loop through all modes
	for (Size x = 0; x < _observers.size(); ++x) {
		// check mode name
		if (_observers[x]._first == name) {
			// return mode
			return &_observers[x]._second;
		} // return null
	} return nullptr;
}

/* get observer list */
Xf::Vector<Xf::Event::Observer>* Xf::Event::get_observers(const std::string& mode, const Evntype type) {
	// check invalid type
	if (type >= Evntype::EVNT_MAX) { return nullptr; }
	// get mode
	Obslist* obslist = get_mode(mode);
	// check mode
	if (!obslist) { return nullptr; }
	// return observers
	return &obslist->idx(type);
}


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

/* singleton instance */
Xf::Event Xf::Event::_instance;







// -- O B S E R V E R  C L A S S ----------------------------------------------


// -- C O N S T R U C T O R S -------------------------------------------------

/* initialize constructor */
Xf::Event::Observer::Observer(Evntfunc method, Object instance)
// initializations
: _method{method}, _instance{instance} {
	// code here...
}

/* copy constructor */
Xf::Event::Observer::Observer(const Observer& other)
// initializations
: _method{other._method}, _instance{other._instance} {
	// code here...
}

/* move constructor */
Xf::Event::Observer::Observer(Observer&& other) noexcept
// initializations
: Observer{other} {
	// code here...
}


/* destructor */
Xf::Event::Observer::~Observer(void) {
	// code here...
}


// -- O P E R A T O R S -------------------------------------------------------

/* copy operator */
Xf::Event::Observer& Xf::Event::Observer::operator=(const Observer& other) {
	// copy method pointer
	_method = other._method;
	// copy instance pointer
	_instance = other._instance;
	// return this
	return *this;
}

/* move operator */
Xf::Event::Observer& Xf::Event::Observer::operator=(Observer&& other) noexcept {
	// call copy operator
	return operator=(other);
}

/* equality operator */
bool Xf::Event::Observer::operator==(const Observer& other) const {
	// check equality
	return _method == other._method && _instance == other._instance;
}


// -- P U B L I C  M E T H O D S ----------------------------------------------

/* call */
void Xf::Event::Observer::call(void) {
	// call method on instance
//	if (!_method) { std::cout << "method is null" << std::endl; return;}
	_method(_instance);
}


// -- A C C E S S O R S -------------------------------------------------------


/* get method */
Xf::Evntfunc Xf::Event::Observer::method(void) const {
	// return method
	return _method;
}

/* get instance */
const Xf::Object& Xf::Event::Observer::instance(void) const {
	// return instance
	return _instance;
}



