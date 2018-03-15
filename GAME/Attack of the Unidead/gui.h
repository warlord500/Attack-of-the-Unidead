#ifndef GUI2_H
#define GUI2_H

#include <defines.h>
#include "globals.h"

struct Menu {
	u16 width;
	u16 height;
	u16 xPos;
	u16 yPos;
	u16 curr_x;
	u16 curr_y;

	void background();
	void title(const char* title);
	void row(u16 num_columns);
	bool push_button(const char* text);
};

//TODO: make this opaque
struct Splash {
	u16 xPos;
	u16 yPos;
	double fade_speed;
	double alpha;
	Texture* tex_ptr;
	bool done;

	void begin(Texture* tex_ptr, double fade_time);
	bool draw();
	void end();
};

#endif