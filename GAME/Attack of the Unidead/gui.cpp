#include "gui.h"
#include <font.h>

INTERNAL
bool draw_text_button(const char* text, u32 text_width, u16 xPos, u16 yPos) {
	Rect button = rect(xPos, yPos, button_tex_n.width, button_tex_n.height);
	vec2 mouse_pos = get_mouse_pos();
	if (colliding(button, mouse_pos.x, mouse_pos.y)) {
		draw_texture(button_tex_h, xPos, yPos);
		if (is_button_released(MOUSE_BUTTON_LEFT)) {
			return true;
		}
	}
	else {
		draw_texture(button_tex_n, xPos, yPos);
	}

	draw_text(BODY_FONT, text, xPos + (button_tex_n.width / 2) - (text_width / 2),
		yPos + (button_tex_n.height / 2) - (BODY_FONT.characters['P']->texture.height / 2), 
		255, 255, 255
	);
	return false;
}

void Menu::background() {
	assert(width >= 0);
	assert(height >= 0);

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

void Menu::row(u16 num_columns) {
	assert(num_columns > 0);
	height = num_columns;
	curr_x = xPos;
	curr_y = yPos + 40;
}

bool Menu::push_button(const char* text) {
	u32 text_width = get_string_width(BODY_FONT, text);
	u16 start_width = button_tex_n.width;
	if (text_width + 25 > start_width) {
		button_tex_n.width = text_width + 25;
		button_tex_h.width = text_width + 25;
	}

	bool pushed = draw_text_button(text, text_width, xPos + (((width+1) * menu_tex[0].width) / 2) - (button_tex_n.width / 2), curr_y);
	curr_y += button_tex_n.height * 1.5f;

	button_tex_n.width = start_width;
	button_tex_h.width = start_width;
	return pushed;
}

void Menu::title(const char* title) {
	u32 title_width = get_string_width(HEADER_FONT, title);
	draw_text(HEADER_FONT, title, xPos + (((width+1)*menu_tex[0].width) / 2) - (title_width / 2),
		yPos + (menu_tex[0].width / 2) - (HEADER_FONT.characters['T']->texture.height),
		255, 255, 255
	);
}

void Splash::begin(Texture* tex_ptr, double fade_speed) {
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