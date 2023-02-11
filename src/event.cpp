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

/* call all observers */
void Xf::Event::call(const Evntype type, const std::string& data) {
	// check current mode
	if (!_current) { return; }
	// check invalid type
	if (type >= Evntype::EVNT_MAX) { return; }
	// get observers indexed by type
	PolyVector& evntobs = (*_current)[(IDX(type))];
	// loop through all observers
	for (Size x = 0; x < evntobs.size(); ++x) {
		// call observer
		evntobs[x].call(data);
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
Xf::Event::PolyVector* Xf::Event::get_observers(const std::string& mode, const Evntype type) {
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



