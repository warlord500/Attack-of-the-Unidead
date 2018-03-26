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
#include "gui.h"
#include <font.h>
#include <bahamut.h>

INTERNAL
bool draw_text_button(const char* const text, const u32 text_width, const u16 xPos,const u16 yPos) {
	const Rect button = rect(xPos, yPos, button_tex_n.width, button_tex_n.height);
	const vec2 mouse_pos = get_mouse_pos();
	const bool collided = colliding(button, mouse_pos.x, mouse_pos.y);
	const bool buttonReleased = is_button_released(MOUSE_BUTTON_LEFT);

	if(collided)
		draw_texture(button_tex_h, xPos, yPos);
	else
		draw_texture(button_tex_n, xPos, yPos); //highlight if mouse is on button

	draw_text(BODY_FONT, text, xPos + (button_tex_n.width / 2) - (text_width / 2),
		yPos + (button_tex_n.height / 2) - (BODY_FONT.characters['P']->texture.height / 2), 
		255, 255, 255
	);

	return collided & buttonReleased;
}

bool draw_text_button(const char* const text, const u16 xPos, const u16 yPos) {
	const u32 text_width = get_string_width(BODY_FONT, text);
	return draw_text_button(text, text_width, xPos, yPos);
}

void text_input_field(std::string* output, const u16 xPos, const u16 yPos, InputRestrictions restriction) {
#define TEMP_WIDTH  80
#define TEMP_HEIGHT 20

	const Rect button = rect(xPos, yPos, TEMP_WIDTH, TEMP_HEIGHT);
	const vec2 mouse_pos = get_mouse_pos();
	const bool collided = colliding(button, mouse_pos.x, mouse_pos.y);

	if (collided) {
		const int key = get_key_pressed();
		if(restriction == INPUT_CHARS_ONLY)
			if (key >= 'a' && key <= 'z')
				output->push_back(key);

		if (restriction == INPUT_NUMBERS_ONLY)
			if (key >= '0' && key <= '9')
				output->push_back(key);

		if (restriction == INPUT_ALL_ALLOWED)
			if (key >= '!' && key <= '~')
				output->push_back(key);

		if (key == KEY_BACKSPACE && output->size() > 0)
			output->pop_back();
	}

	if (collided)
		draw_texture(button_tex_h, xPos, yPos, TEMP_WIDTH, TEMP_HEIGHT);
	else
		draw_texture(button_tex_n, xPos, yPos, TEMP_WIDTH, TEMP_HEIGHT); //highlight if mouse is on button
	draw_text(BODY_FONT, *output, xPos + 3, yPos + (TEMP_HEIGHT / 2) - (BODY_FONT.characters['T']->texture.height / 2));

#undef TEMP_WIDTH
#undef TEMP_HEIGHT
}

void Menu::background() {
	assert(width >= 1);
	assert(height >= 1);

	draw_texture(menu_tex[0], xPos, yPos);
	draw_texture(menu_tex[2], xPos, yPos + (height * menu_tex[0].height));
	draw_texture(menu_tex[6], xPos + (width * menu_tex[0].width), yPos);
	draw_texture(menu_tex[8], xPos + (width * menu_tex[0].width), yPos + (height * menu_tex[0].height));

	for (int x = 1; x < width; ++x) {
		draw_texture(menu_tex[3], (x * menu_tex[0].width) + xPos, yPos);
		draw_texture(menu_tex[5], (x * menu_tex[0].width) + xPos, yPos + (height * menu_tex[0].height));
	}
	for (int y = 1; y < height; ++y) {
		draw_texture(menu_tex[1], xPos, (y * menu_tex[0].height) + yPos);
		draw_texture(menu_tex[7], xPos + (width * menu_tex[0].width), (y * menu_tex[0].height) + yPos);
	}
	for (int x = 1; x < width; ++x) {
		for (int y = 1; y < height; ++y) {
			draw_texture(menu_tex[4], (x * menu_tex[0].width) + xPos, (y * menu_tex[0].height) + yPos);
		}
	}
}

void Menu::row(const u16 num_columns) {
	assert(num_columns > 0);
	assert(width >= 1);
	height = num_columns;

	if (xPos == CENTER_HORIZONTAL) {
		xPos = get_virtual_width() / 2;
		xPos -= ((width * menu_tex[0].width) / 2);
	}
	if (yPos == CENTER_VERTICAL) {
		yPos = get_virtual_height() / 2;
		yPos -= ((height * menu_tex[0].height) / 2);
	}

	curr_x = xPos;
	curr_y = yPos + 40;
}

bool Menu::push_button(const char* text) {
	const u32 text_width = get_string_width(BODY_FONT, text);
	const u16 start_width = button_tex_n.width;
	if (text_width + 25 > start_width) {
		button_tex_n.width = text_width + 25;
		button_tex_h.width = text_width + 25;
	}

	const bool pushed = draw_text_button(text, 
				text_width, xPos + (((width+1) * menu_tex[0].width) / 2) - (button_tex_n.width / 2), curr_y);
	curr_y += button_tex_n.height * 1.5f;

	button_tex_n.width = start_width;
	button_tex_h.width = start_width;
	return pushed;
}

void Menu::title(const char* const title) {
	const u32 title_width = get_string_width(HEADER_FONT, title);
	draw_text(HEADER_FONT, title, xPos + (((width+1)*menu_tex[0].width) / 2) - (title_width / 2),
		yPos + (menu_tex[0].width / 2) - (HEADER_FONT.characters['T']->texture.height),
		255, 255, 255
	);
}

void Splash::begin(Texture* const tex_ptr,  const double fade_speed) {
	this->fade_speed = fade_speed;
	this->tex_ptr = tex_ptr;
	alpha = 1;
	done = false;
}

bool Splash::draw() {
	if (!done) {
		if (alpha <= 0) {
			end();
			return true;
		}
		else {
			alpha += fade_speed;
			if (alpha >= 330) {
				alpha = 255;
				fade_speed = -fade_speed;
			}
			draw_texture(*tex_ptr, xPos, yPos, 255, 255, 255, alpha);
		}
	}
	return false;
}

void Splash::end() {
	done = true;
	fade_speed = 0;
}
