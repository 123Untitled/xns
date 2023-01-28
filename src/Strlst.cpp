#include <Str.hpp>

bool Strlst::_debug = false;

void Strlst::debug(const char *message) const {
	if (_debug) {
		printf("%s::", typeid(*this).name());
		//puts(message);
		printf("%s -> ", message);
		fflush(stdout);
		printf("\n");
	}
}

void Strlst::debugOn(void) {
	_debug = true;
}

void Strlst::debugOff(void) {
	_debug = false;
}

//////////////////////////////////////////////////////////////
Strlst::Strlst()
: _head{nullptr}, _tail{nullptr}, _size{0}, _node{0} {
	debug(DEFAULT_CONSTRUCTOR);
	// default constructor
}


/* DELETED COPY CONSTRUCTOR */
Strlst::Strlst(const Strlst& copy)
: Strlst{} {
	debug(COPY_CONSTRUCTOR);
	// Strlst copy constructor
	STRNode* node = copy._head;
	while (node) {
		addBack(*node);
		node = node->_nxt;
	}
}

// destructor
Strlst::~Strlst() {
	// destructor
	debug(DESTRUCTOR);
	deleteList();
}

Strlst::Strlst(Strlst&& move) noexcept
: _head{move._head}, _tail{move._tail}, _size{move._size}, _node{move._node} {
	// Strlst move constructor
	debug(MOVE_CONSTRUCTOR);
	move.init();
}

void Strlst::operator=(Strlst&& move) {
	debug(MOVE_OPERATOR);
	freeLst();
	_head = move._head;
	_tail = move._tail;
	_size = move._size;
	_node = move._node;
	move.init();
}

void Strlst::operator=(Strlst& copy) {
	debug(COPY_OPERATOR);
	*this = Strlst{copy};
}

Str* Strlst::operator[](const UInt32 index) const {

	STRNode* node = _head;

	for (UInt32 x = 0; node; x++) {
		if (x == index)
			return (node);
		node = node->_nxt;
	} return (nullptr);
}


/*STRNode*	Strlst::getHead(void) {
	return (_head);
}*/


void Strlst::init() {
	_head = _tail = nullptr;
	_size = _node = 0;
}

void Strlst::deleteList() {
	freeLst();
	init();
}

void Strlst::freeLst() {
	STRNode *del;
	while (_head) {
		del = _head;
		_head = _head->_nxt;
		delete del;
	}
}


void Strlst::separator(Str&& sep) {
	STRNode* node = _head;
	if (!node)
		return;
	//while (node->_nxt) {
	while (node) {
		node->append(sep);
		node = node->_nxt;
	}
}


void Strlst::print() const {
	STRNode *node = _head;

	while (node) {
		node->print();
		node = node->_nxt;
	} printf("size::%u, node::%u\n\n", _size, _node);
}



void Strlst::deleteNode(STRNode *del) {

	if (del->_nxt)
		del->_nxt->_prv = del->_prv;
	else _tail = del->_prv;

	if (del->_prv)
		del->_prv->_nxt = del->_nxt;
	else _head = del->_nxt;
	_node--;
	_size -= del->getLen();

	delete (del);
}

void Strlst::deleteAt(const UInt32 index) {
	STRNode *del = _head;
	UInt32 x = 0;

	while (del) {
		if (x++ == index)
			deleteNode(del);
		del = del->_nxt;
	}
}

void Strlst::frontLink(STRNode *add) {

	if (!_head)
		_tail = add;
	else {
		_head->_prv	= add;
		add->_nxt	= _head;
	} _head = add;
}

void Strlst::backLink(STRNode *add) {

	if (!_tail) {
		_head = add;
	} else {
		_tail->_nxt	= add;
		add->_prv	= _tail;
	} _tail = add;
}

// ADD FRONT
void Strlst::addFront(Str&& string) {

	if (string.getLen()) {
		// call string rvalue move STRNode constructor
		STRNode *add = new STRNode{static_cast<Str &&>(string)};
		// make link
		frontLink(add);
		// update class data
		_size += add->getLen();
		_node++;
	}
}

void Strlst::addFront(const Str& string) {

	if (string.getLen()) {
		// call string copy Node constructor
		STRNode *add = new STRNode{string};
		// make link
		frontLink(add);
		// update class data
		_size += add->getLen();
		_node++;
	}
}


// ADD BACK
void Strlst::addBack(Str&& string) {

	if (string.getLen()) {
		// call string rvalue move Node constructor
		STRNode *add = new STRNode{static_cast<Str &&>(string)};
		// make link
		backLink(add);
		// update class data
		_size += add->getLen();
		_node++;
	}
}

void Strlst::addBack(const Str& string) {

	if (string.getLen()) {
		// call string copy Node constructor
		STRNode *add = new STRNode{string};
		// make link
		backLink(add);
		// update class data
		_size += add->getLen();
		_node++;
	}
}


Str Strlst::release() {
	// local variable to return
	Str merged{_size};
	// local node initialized with head list
	STRNode *node = _head;
	// run over list and append string
	while (node) {
		merged.append(*node);
		node = node->_nxt;
	} // move return local object
	return (merged);
}



//////////////////////////////// STRNode class


Strlst::STRNode::STRNode(const Str& string)
: Str{string._str, string._len}, _nxt{nullptr}, _prv{nullptr} {
	// string copy constructor
}

Strlst::STRNode::STRNode(Str &&string)
: Str{static_cast<Str &&>(string)}, _nxt{nullptr}, _prv{nullptr} {
	// string move constructor
}

Strlst::STRNode::~STRNode(void) {
	// destructor
}






////////////////////////////// ITERATOR
Strlst::Iterator::Iterator(Strlst& lst)
: _ptr{&(lst._head)} {
}

Strlst::Iterator::Iterator(STRNode** node)
: _ptr{node} {
}

bool Strlst::Iterator::operator!(void) {
	return (!(*_ptr));
}

void Strlst::Iterator::start(Strlst& lst) {
	_ptr = &lst._head;
}

void Strlst::Iterator::end(Strlst& lst) {
	_ptr = &lst._tail;
}

// Prefix increment operator.
Strlst::Iterator& Strlst::Iterator::operator++(void) {
	if (*_ptr)
		_ptr = &(*_ptr)->_nxt;
		//*_ptr = (*_ptr)->_nxt;
	return (*this);
}
Strlst::Iterator::operator bool() {
	return (*_ptr);
}

// Postfix increment operator.
Strlst::Iterator Strlst::Iterator::operator++(int) {
	Iterator tmp{_ptr};
	if (*_ptr)
		_ptr = &(*_ptr)->_nxt;
		//*_ptr = (*_ptr)->_nxt;
	return (tmp);
}

// Postfix increment operator.
Strlst::Iterator Strlst::Iterator::operator--(int) {
	Iterator tmp{_ptr};
	if (*_ptr)
		_ptr = &(*_ptr)->_prv;
		//*_ptr = (*_ptr)->_prv;
	return (tmp);
}

Str& Strlst::Iterator::operator*(void) {
	return (**_ptr);
}

