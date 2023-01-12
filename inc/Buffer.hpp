#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include "Macro.hpp"
#include "Types.hpp"

#include <cstdlib>
#include <unistd.h>
#include <iostream>

class Buffer {

public:

	NON_INSTANCIABLE(Buffer);

	static void draw(const void* ptr, const UInt size);
	static int render(const int fd = STDOUT_FILENO);

private:

	static char* initBuffer(void);
	static void staticDestructor(void);
	static void extend(const UInt bytes);


	static char*	_buff;
	static UInt		_size;
	static UInt		_pos;


};

#endif
