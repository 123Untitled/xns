#include "string.hpp"


// -- C O N S T R U C T O R S -------------------------------------------------

/* default constructor */
LString::LString(void)
// initializations
: _head{nullptr}, _tail{nullptr}, _size{0}, _node{0} {
	// nothing to do
}

/* copy constructor */ // !!! not implemented
LString::LString(const LString& copy)
: LString{} {
	// LString copy constructor
	Node* node = copy._head;
	while (node) {
		add_back(*node);
		node = node->_nxt;
	}
}

/* move constructor */
LString::LString(LString&& move) noexcept
// initializations
: _head{move._head}, _tail{move._tail}, _size{move._size}, _node{move._node} {
	// initialize members
	move.initialize_members();
}

/* destructor */
LString::~LString() {
	deleteList();
}


// -- O P E R A T O R S -------------------------------------------------------

/* move operator */
LString& LString::operator=(LString&& move) noexcept {
	freeLst();
	_head = move._head;
	_tail = move._tail;
	_size = move._size;
	_node = move._node;
	move.initialize_members();
	return *this;
}

/* assignment operator */
LString& LString::operator=(const LString& copy) {
	*this = LString{copy};
	return *this;
}

String* LString::operator[](const UInt32 index) const {

	Node* node = _head;

	for (UInt32 x = 0; node; x++) {
		if (x == index)
			return (node);
		node = node->_nxt;
	} return (nullptr);
}



/* initialize members */
void LString::initialize_members(void) {
	_head = _tail = nullptr;
	_size = _node = 0;
}

void LString::deleteList() {
	freeLst();
	initialize_members();
}

void LString::freeLst() {
	Node *del;
	while (_head) {
		del = _head;
		_head = _head->_nxt;
		delete del;
	}
}


void LString::separator(String&& sep) {
	Node* node = _head;
	if (!node)
		return;
	//while (node->_nxt) {
	while (node) {
		node->append(sep);
		node = node->_nxt;
	}
}


void LString::print() const {
	Node *node = _head;

	while (node) {
		node->print_string();
		node = node->_nxt;
	}
	printf("size::%llu, node::%llu\n\n", _size, _node);
}



void LString::deleteNode(Node *del) {

	if (del->_nxt)
		del->_nxt->_prv = del->_prv;
	else _tail = del->_prv;

	if (del->_prv)
		del->_prv->_nxt = del->_nxt;
	else _head = del->_nxt;
	_node--;
	_size -= del->length();

	delete (del);
}

void LString::deleteAt(const UInt32 index) {
	Node *del = _head;
	UInt32 x = 0;

	while (del) {
		if (x++ == index)
			deleteNode(del);
		del = del->_nxt;
	}
}

/* front link */
void LString::front_link(Node* add) {

	if (!_head) { _tail = add; }
	else {
		_head->_prv	= add;
		add->_nxt	= _head;
	} _head = add;
}

/* back link */
void LString::back_link(Node* add) {

	if (!_tail) { _head = add; }
	else {
		_tail->_nxt	= add;
		add->_prv	= _tail;
	} _tail = add;
}


/* add front */
void LString::add_front(String&& str) {

	if (str.length()) {
		// call string rvalue move Node constructor
		Node *add = new Node{Xf::move(str)};
		// make link
		front_link(add);
		// update class data
		_size += add->length();
		_node++;
	}
}

void LString::add_front(const String& str) {

	if (str.length()) {
		// call string copy Node constructor
		Node *add = new Node{str};
		// make link
		front_link(add);
		// update class data
		_size += add->length();
		_node++;
	}
}


// ADD BACK
void LString::add_back(String&& str) {

	if (str.length()) {
		// call string rvalue move Node constructor
		Node *add = new Node{Xf::move(str)};
		// make link
		back_link(add);
		// update class data
		_size += add->length();
		_node++;
	}
}

void LString::add_back(const String& str) {

	if (str.length()) {
		// call string copy Node constructor
		Node *add = new Node{str};
		// make link
		back_link(add);
		// update class data
		_size += add->length();
		_node++;
	}
}


String LString::merge(void) {
	// local variable to return
	String merged{_size};
	// local node initialized with head list
	Node *node = _head;
	// run over list and append string
	while (node) {
		merged.append(*node);
		node = node->_nxt;
	} // move return local object
	return (merged);
}




// -- N O D E  C L A S S ------------------------------------------------------


// -- C O N S T R U C T O R S -------------------------------------------------

/* string copy constructor */
LString::Node::Node(const String& str)
// initializations
: String{str._str, str._size}, _nxt{nullptr}, _prv{nullptr} {
	// nothing to do
}

/* string move constructor */
LString::Node::Node(String&& str)
// initializations
: String{Xf::move(str)}, _nxt{nullptr}, _prv{nullptr} {
	// nothing to do
}

/* destructor */
LString::Node::~Node(void) {
	// nothing to do
}






////////////////////////////// ITERATOR
LString::Iterator::Iterator(LString& lst)
: _ptr{&(lst._head)} {
}

LString::Iterator::Iterator(Node** node)
: _ptr{node} {
}

bool LString::Iterator::operator!(void) {
	return (!(*_ptr));
}

void LString::Iterator::start(LString& lst) {
	_ptr = &lst._head;
}

void LString::Iterator::end(LString& lst) {
	_ptr = &lst._tail;
}

// Prefix increment operator.
LString::Iterator& LString::Iterator::operator++(void) {
	if (*_ptr)
		_ptr = &(*_ptr)->_nxt;
		//*_ptr = (*_ptr)->_nxt;
	return (*this);
}
LString::Iterator::operator bool() {
	return (*_ptr);
}

// Postfix increment operator.
LString::Iterator LString::Iterator::operator++(int) {
	Iterator tmp{_ptr};
	if (*_ptr)
		_ptr = &(*_ptr)->_nxt;
		//*_ptr = (*_ptr)->_nxt;
	return (tmp);
}

// Postfix increment operator.
LString::Iterator LString::Iterator::operator--(int) {
	Iterator tmp{_ptr};
	if (*_ptr)
		_ptr = &(*_ptr)->_prv;
		//*_ptr = (*_ptr)->_prv;
	return (tmp);
}

String& LString::Iterator::operator*(void) {
	return (**_ptr);
}

