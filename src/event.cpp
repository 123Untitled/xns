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

	// check if mode already exists
	if (mode_exists(name)) { return; }


	Size idx = 0;
	// find index of current mode
	if (_current) { idx = get_current_idx(); }

	_observers.emplace_back(Xf::move(Pair{
				Xf::move(name), Xf::move(Obslist{})
			}
		)
	);

	// set new current mode
	if (_current) {
		// INFO: reason of this is when vector is resized,
		// all pointers are invalidated
		_current = &_observers[idx]._second;
	}
}

/* [PRIVATE] mode exists */
bool Xf::Event::mode_exists(const std::string& mode) const {
	// loop through all modes
	for (Size x = 0; x < _observers.size(); ++x) {
		// compare mode name
		if (_observers[x]._first == mode) {
			// exit method
			return true; }
	} // mode not found
	return false;
}

/* [PRIVATE] get current mode index */
Size Xf::Event::get_current_idx(void) const {
	// loop through all modes
	for (Size x = 0; x < _observers.size(); ++x) {
		// check mode name
		if (&_observers[x]._second == _current) {
			// exit method
			return x; }
	} // else return 0
	return 0;
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



