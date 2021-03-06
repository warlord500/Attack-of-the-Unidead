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
#ifndef GLOBALS_H
#define GLOBALS_H

#include <texture.h>
#include <maths.h>
#include <bahamut.h>
#include <render2D.h>
#include <vector>
#include <random>
//just for clarity. It should be immediately obvious these are globals and you should be VERY careful with them
//and by that I mean never change them. They are only changeable because they must be loaded from disk at runtime.
//NOTE: Originally I thought that static would work for globals but as it turns out I was wrong and static gives each
//	source file it's own copy of the variable. It's still fine for consts though. Defines could be better but I'm not in any
//	panic to reduce memory usage.
#define global_var extern
#define global_const const static

//initialization data. Loaded from a file and should be treated as const after that point.
global_var bool DISPLAY_FPS;
global_var bool COMPRESS_SAVES;
global_var bool SOUND;
global_var bool VSYNC;
global_var u8 MUSIC_VOLUME;
global_var u8 SOUND_VOLUME;
global_var u8 MASTER_VOLUME;
global_var u32 TEXTURE_PARAM;
global_var Font HEADER_FONT;
global_var Font BODY_FONT;

global_var int TILE_SIZE;

//colors for the colorscheme. Loaded from a file and should be treated as const after that point.
global_const int MAX_COLORS = 16;
global_var vec4 COLORSCHEME[MAX_COLORS];

global_const int SCROLL_SPEED = 5;
global_const int PLAYER = 0;

//textures
global_var Texture button_tex_n;
global_var Texture button_tex_h;
global_var Texture menu_tex[9];

//global functions

void init_globals();
void init_context(const char* title);

//std::vector<std::string> decipher_line(char* line, const char* filename, int line_num);
std::vector<std::string> tokenize_str(const char* string, char seperator);

void remove_characters(char* string, char to_remove);
void remove_leading_characters(char* string, char to_remove);
Texture getSubImage(unsigned char* pixels, int pixels_width, int x, int y, int width, int height);

namespace {
	std::random_device rd;
	std::mt19937 mt(rd());

	//================================================
	//Description: Generates a random integer from 0
	//	to a value.
	//================================================
	int inline randomInt(const int exclusiveMax) {
		std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
		return dist(mt);
	}

	//================================================
	//Description: Generates a random integer between
	//	two values.
	//================================================
	int inline randomInt(const int min, const int max) {
		std::uniform_int_distribution<> dist(0, max - min);
		return dist(mt) + min;
	}
}

#endif