#include "event.hpp"


// -- P R I V A T E  C O N S T R U C T O R S ----------------------------------

/* default constructor */
Xf::Event::Event(void)
: _modes{} {
}

/* destructor */
Xf::Event::~Event(void) {
	// clean up observer list
	//clear();
}


// -- S T A T I C  P U B L I C  M E T H O D S ---------------------------------

/* get singleton instance */
Xf::Event& Xf::Event::instance(void) {
	// return instance
	return _instance;
}


// -- P U B L I C  M E T H O D S ----------------------------------------------

/* add mode */
Xf::Event::Mode* Xf::Event::add_mode(std::string&& name) {
	std::cout << "----------------------\n\n" << std::endl;
	// check invalid name
	if (name.empty()) { return nullptr; }
	// loop through all modes
	for (Size x = 0; x < _modes.size(); ++x) {
		// check mode already exists
		if (_modes[x].name() == name) {
			std::cout << "Mode already exists" << std::endl;
			// exit method
			return &_modes[x];
		} // add mode
	}
	_modes.push_back(Xf::move(name));
	std::cout << "Mode added-> " << _modes.back().name() << std::endl;
	// return new mode
	return &_modes.back();
}

/* set mode */
void Xf::Event::set_mode(Mode* mode) {
	// check invalid mode
	if (!mode) { return; }
	_current = mode;
}


/* subscribe to event */
void Xf::Event::subscribe(const Evntype type, Evntfunc method, Object instance) {
	// check invalid type and method pointer
/*	if (type >= Evntype::EVNT_MAX || !method) { return; }
	// allocate new observer
	Observer* observer = new Observer(method, instance);
	// set next observer
	observer->next(head(type));
	// set head observer
	head(type, observer);*/
}

/* unsubscribe to event */
void Xf::Event::unsubscribe(const Evntype type, Evntfunc method, Object instance) {
	// check invalid type
/*	if (type >= Evntype::EVNT_MAX) { return; }
	// create new observer to be compared
	Observer search{method, instance};
	// get observers indexed by type
	Observer* observer = head(type);
	// initialize previous observer
	Observer* prev = nullptr;
	// loop through all observers
	while (observer) {
		// check observer
		if (*observer != search) {
			// get next observer
			observer = observer->next();
			// get previous observer
			prev = observer;
			// continue loop
			continue;
		} // check previous observer
		if (prev != nullptr) {
			// set previous observer's next
			prev->next(observer->next());
		} // else
		else {
			// set head observer
			head(type, observer->next());
		} // delete observer
		delete observer;
		// exit method
		return;
	}*/
}

/* call all observers */
void Xf::Event::call(const Evntype type) {
	// check invalid type
/*	if (type >= Evntype::EVNT_MAX) { return; }
	// get observers indexed by type
	Observer* observer = head(type);
	// loop through all observers
	while (observer) {
		// call observer
		observer->call();
		// get next observer
		observer = observer->next();
	}*/
}

/* clean up */
void Xf::Event::clear(void) {
	// loop through all events
/*	for (Size x = 0; x < IDX(Evntype::EVNT_MAX); ++x) {
		// loop through all observers
		while (_observers[x]) {
			// get next observer
			Observer* next = _observers[x]->next();
			// delete current observer
			delete _observers[x];
			// set next observer
			_observers[x] = next;
		}
	}*/
}


// -- S T A T I C  P R I V A T E  A C C E S S O R S ---------------------------

/* get head observer */ // NOTE: type is not checked
/*Xf::Event::Observer* Xf::Event::head(const Evntype type) {
	// return head observer
	//return _observers[IDX(type)];
	return nullptr;
} */


// -- S T A T I C  P R I V A T E  M U T A T O R S -----------------------------

/* set head observer */ // NOTE: type is not checked
/*void Xf::Event::head(const Evntype type, Observer* observer) {
	// set head observer
	//_observers[IDX(type)] = observer;
} */


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

/* singleton instance */
Xf::Event Xf::Event::_instance;

/* observers list */
//Xf::Event::Observer* Xf::Event::_observers[IDX(Evntype::EVNT_MAX)] = { nullptr };



// -- M O D E  N E S T E D  C L A S S -----------------------------------------


/* name copy constructor */
Xf::Event::Mode::Mode(const std::string& name)
: _name{name}, _events{} {
	// code here...
}

/* name move constructor */
Xf::Event::Mode::Mode(std::string&& name) noexcept
: _name{Xf::move(name)}, _events{} {
	// code here...
}

/* copy constructor */
Xf::Event::Mode::Mode(const Mode& other)
: _name{other._name}, _events{other._events} {
	// code here...
}

/* move constructor */
Xf::Event::Mode::Mode(Mode&& other) noexcept
: _name{Xf::move(other._name)}, _events{Xf::move(other._events)} {
	// code here...
}

/* destructor */
Xf::Event::Mode::~Mode(void) {
	// code here...
}


// -- O P E R A T O R S -------------------------------------------------------

/* copy operator */
Xf::Event::Mode& Xf::Event::Mode::operator=(const Mode& other) {
	// check for self assignment
	if (this != &other) {
		// copy name
		_name = other._name;
		// copy events
		_events = other._events;
	} // return self reference
	return *this;
}

/* move operator */
Xf::Event::Mode& Xf::Event::Mode::operator=(Mode&& other) {
	// check for self assignment
	if (this != &other) {
		// move name
		_name = Xf::move(other._name);
		// move events
		_events = Xf::move(other._events);
	} // return self reference
	return *this;
}


// -- A C C E S S O R S -------------------------------------------------------

/* get name */
const std::string& Xf::Event::Mode::name(void) const {
	// return name
	return _name;
}

/* subscribe */
void Xf::Event::Mode::subscribe(const Evntype type, Evntfunc method, Object instance) {
}

/* unsubscribe */
void Xf::Event::Mode::unsubscribe(const Evntype type, Evntfunc method, Object instance) {
}






// -- O B S E R V E R  C L A S S ----------------------------------------------


// -- C O N S T R U C T O R S -------------------------------------------------

/* initialize constructor */
Xf::Event::Observer::Observer(Evntfunc method, Object instance)
// initializations
: _method{method}, _instance{instance} {
	// code here...
}

/* destructor */
Xf::Event::Observer::~Observer(void) {
	// code here...
}


// -- O P E R A T O R S -------------------------------------------------------

/* equality operator */
bool Xf::Event::Observer::operator==(const Observer& other) const {
	// check equality
	return _method == other._method && _instance == other._instance;
}


// -- P U B L I C  M E T H O D S ----------------------------------------------

/* call */
void Xf::Event::Observer::call(void) {
	// call method on instance
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



