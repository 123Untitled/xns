#include "draw.hpp"

void xns::draw::clear_line(const xns::u32 posX, const xns::u32 posY, const xns::u32 size) {
	/*
	xns::ubyte	*clear = new xns::ubyte[size];
	xns::u32 i = 0;
	while (i < size) {
		clear[i] = ' ';
		i++;
	}
	//Escape::move_position(posX, posY);
	write(STDOUT_FILENO, clear, size);
	delete[] clear;
	*/
}


/* drawLine */
//void Draw::drawLine(const xns::u32 x, const xns::u32 y, const void *ptr, const xns::u32 size) {
	//Escape::move_position(x, y);
	//Buffer::draw(ptr, size);
//}

/* draw string */
void xns::draw::draw_string(const xns::u32 x, const xns::u32 y, const xns::string& str) {
	// move to position
	//Escape::move_position(x, y);
	// draw string
	//Buffer::draw(str.data(), str.size());
}

/* vertivalDraw */
void xns::draw::vertival_draw(const xns::u32 x, xns::u32 y, const void* ptr, const xns::u32 size, xns::u32 line) {
	/*
	(void)y;
	while (line) {
		//Escape::move_position(x, y);
		//Buffer::draw(ptr, size);
		--line;
		++y;
	}
	*/
}

void xns::draw::draw_integer(xns::u32 number) {
	(void)number;
}


/* int Draw::drawStringNl(const Str& string) {
	return (write(STDOUT_FILENO, string.getPointer(), string.getLen())
		+ write(STDOUT_FILENO, "\n", 1)); }*/

/*void Draw::animateDraw(const Str& string) {
	animateDraw(string, RED_COLOR, GREY_COLOR); }*/

/*void Draw::animateDrawNl(const Str& string) {
	animateDraw(string, RED_COLOR, GREY_COLOR);
	write(STDOUT_FILENO, "\n", 1); }*/

/* void Draw::animateDraw(const Str& id, const xns::u32 colorIn, const xns::u32 colorOut) {
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
		xns::u32 dl = PDELAY / (*ptr - 32);
		// enable color
		//setColor(colorIn, FOREGROUND);
		// iterate until target character
		for (xns::ubyte x = '\x20'; x != *ptr;) {
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
