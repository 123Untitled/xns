#include "draw.hpp"

void Draw::clearLine(UInt32 posX, UInt32 posY, UInt32 size) {
	UInt8	*clear = new UInt8[size];
	UInt32 i = 0;
	while (i < size) {
		clear[i] = ' ';
		i++;
	}
	Escape::move_position(posX, posY);
	write(STDOUT_FILENO, clear, size);
	delete[] clear;
}


/* drawLine */
void Draw::drawLine(const UInt x, const UInt y, const void *ptr, const UInt size) {
	Escape::move_position(x, y);
	Buffer::draw(ptr, size);
}

/* draw string */
void Draw::draw_string(const UInt x, const UInt y, const std::string& str) {
	// move to position
	Escape::move_position(x, y);
	// draw string
	Buffer::draw(str.data(), str.size());
}

/* vertivalDraw */
void Draw::vertivalDraw(const UInt x, UInt y, const void *ptr, const UInt size, UInt line) {
	while (line) {
		Escape::move_position(x, y);
		Buffer::draw(ptr, size);
		--line;
		++y;
	}
}

void Draw::drawInteger(UInt number) {

	constexpr UInt BUFFSIZE = 64;

	static char seq[BUFFSIZE];

	char* ptr = &(seq[BUFFSIZE]);

	while (number) {

		std::cout << "loop" << std::endl;
		*(--ptr) = (number % 10) + '0';
		number /= 10;
	}
	UInt size = (seq + BUFFSIZE) - ptr;
	Buffer::draw(ptr, size);


}


/* int Draw::drawStringNl(const Str& string) {
	return (write(STDOUT_FILENO, string.getPointer(), string.getLen())
		+ write(STDOUT_FILENO, "\n", 1)); }*/

/*void Draw::animateDraw(const Str& string) {
	animateDraw(string, RED_COLOR, GREY_COLOR); }*/

/*void Draw::animateDrawNl(const Str& string) {
	animateDraw(string, RED_COLOR, GREY_COLOR);
	write(STDOUT_FILENO, "\n", 1); }*/

/* void Draw::animateDraw(const Str& id, const UInt32 colorIn, const UInt32 colorOut) {
	if (id.getLen() > 30) {
		drawString(id);
		return;
	}
	// get Str * pointer
	Char*	ptr = id.getPointer();
	// run over string
	while (*ptr) {
		// check character type
		if (!Str::isSymb(*ptr)) {
			// print unprintable character
			write(STDOUT_FILENO, ptr++, 1);
			// run loop again
			continue;
		} // else speed print calculation
		UInt32 dl = PDELAY / (*ptr - 32);
		// enable color
		//setColor(colorIn, FOREGROUND);
		// iterate until target character
		for (UInt8 x = '\x20'; x != *ptr;) {
			// print stages
			write(STDOUT_FILENO, &(++x), 1);
			// wait delay
			usleep(dl);
			// move left to erase previous character
			//moveLeft();
		} // disable color
		//setColor(colorOut, FOREGROUND);
		// print target character
		write(STDOUT_FILENO, ptr++, 1);
	}
	//resetColor();
} */
