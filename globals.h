#pragma once
#include "ENGINE/texture.h"
#include "ENGINE/vec4f.h"
#include "ENGINE/bahamut.h"
#include <vector>
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
global_var bool SOUND_ON;
global_var bool VSYNC;
global_var char MUSIC_VOLUME;
global_var char SOUND_VOLUME;
global_var int TEXTURE_PARAM;
global_var Font FONT;

global_var int TILE_SIZE;

//colors for the colorscheme. Loaded from a file and should be treated as const after that point.
global_const int MAX_COLORS = 16;
global_var vec4f COLORSCHEME[MAX_COLORS];
global_var Texture select_cursor;

global_const int SCROLL_SPEED = 5;
global_const int PLAYER = 0;

//global functions

void init_globals();
void init_context(const char* title);

std::vector<std::string> decipher_line(char* line, const char* filename, int line_num);
std::vector<std::string> tokenize_str(char* string, char seperator);
bool is_a_number(char c);
void remove_characters(char* string, char to_remove);
void remove_leading_characters(char* string, char to_remove);
bool character_exists(char* string, char to_check);

Texture getSubImage(unsigned char* pixels, int pixels_width, int x, int y, int width, int height);