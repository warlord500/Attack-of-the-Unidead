/*
Copyright (C) 2018, corbin stark, jadon belezos, josiah Baldwin
Steven Schulze

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/
#ifndef GUI2_H
#define GUI2_H

#include <defines.h>
#include "globals.h"

#define CENTER_HORIZONTAL  0xFFFF
#define CENTER_VERTICAL    0xFFFF

enum InputRestrictions {
	INPUT_CHARS_ONLY,
	INPUT_NUMBERS_ONLY,
	INPUT_ALL_ALLOWED
};

bool draw_text_button(const char* const text, const u16 xPos, const u16 yPos);
void text_input_field(std::string* output, const u16 xPos, const u16 yPos, InputRestrictions restriction);

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