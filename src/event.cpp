#include "event.hpp"


// -- P R I V A T E  C O N S T R U C T O R S ----------------------------------

/* default constructor */
Xf::Event::Event(void)
: _modes{ }, _current{nullptr} {
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
void Xf::Event::add_mode(String&& name) {
	// check invalid name
	if (name.empty()) { return; }

	// check if mode already exists
	if (mode_exists(name)) { return; }


	Size idx = 0;
	// find index of current mode
	if (_current) { idx = get_current_idx(); }

	_modes.emplace_back(Pair{Xf::move(name), Mode{}});

	// set new current mode
	if (_current) {
		// INFO: reason of this is when vector is resized,
		// all pointers are invalidated
		_current = &_modes[idx]._second;
	}
}

/* [PRIVATE] mode exists */
bool Xf::Event::mode_exists(const std::string& mode) const {
	// loop through all modes
	for (Size x = 0; x < _modes.size(); ++x) {
		// compare mode name
		if (_modes[x]._first == mode) {
			// exit method
			return true; }
	} // mode not found
	return false;
}

/* [PRIVATE] get current mode index */
Size Xf::Event::get_current_idx(void) const {
	// loop through all modes
	for (Size x = 0; x < _modes.size(); ++x) {
		// check mode name
		if (&_modes[x]._second == _current) {
			// exit method
			return x; }
	} // else return 0
	return 0;
}

/* set mode by name */
bool Xf::Event::set_mode(const String& name) {
	// loop through all modes
	for (Size x = 0; x < _modes.size(); ++x) {
		// check mode name
		if (_modes[x]._first == name) {
			// set new current mode
			_current = &_modes[x]._second;
			// exit method
			return true;
		} // mode not found
	} return false;
}

/* call all event subscribers */
void Xf::Event::call_event(const Evntype type) {
	// exit if no current mode
	if (!_current) { return; }
	// check event type
	if (type < Evntype::EVNT_MAX) {
		// get subscribers index by event type
		EventVector& subscribers = _current->_second[IDX(type)];
		// loop through all observers
		for (Size x = 0; x < subscribers.size(); ++x) {

			// INFO: need to overload call for PolyMethod instance with no arguments (void)
			// call subscriber
			subscribers[x].call();
		}
	}
}

/* call all input subscribers */
void Xf::Event::call_input(const String& input) {
	// exit if no current mode
	if (!_current) { return; }
	// get subscribers
	InputVector& subscribers = _current->_first;
	// loop through all observers
	for (Size x = 0; x < subscribers.size(); ++x) {
		// call subscriber
		subscribers[x].call(input);
	}
}


// -- P R I V A T E  M E T H O D S --------------------------------------------

/* get mode */
Xf::Event::Mode* Xf::Event::get_mode(const String& name) {
	// loop through all modes
	for (Size x = 0; x < _modes.size(); ++x) {
		// check mode name
		if (_modes[x]._first == name) {
			// return mode
			return &_modes[x]._second;
		}
	} return nullptr;
}

/* get event subscribers */
Xf::Event::EventVector* Xf::Event::get_event_subscribers(const String& mode, const Evntype type) {
	// get mode
	Mode* m = get_mode(mode);
	// check mode
	if (!m) { return nullptr; }
	// check event type
	if (type < Evntype::EVNT_MAX) {
		// return subscribers
		return &m->_second[IDX(type)];
	} return nullptr;
}

/* get input subscribers */
Xf::Event::InputVector* Xf::Event::get_input_subscribers(const String& mode) {
	// get mode
	Mode* m = get_mode(mode);
	// check mode
	if (!m) { return nullptr; }
	// return subscribers
	return &m->_first;
}


// -- S T A T I C  P R I V A T E  M E M B E R S -------------------------------

/* singleton instance */
Xf::Event Xf::Event::_instance;



