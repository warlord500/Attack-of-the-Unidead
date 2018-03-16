#include "globals.h"
#include <cstdarg>
#include <SOIL.h>
#include <string>
#include <random>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <audio.h>

//VAR DEFAULTS (if they aren't defined in the config files for some reason)
bool DISPLAY_FPS = false;
bool COMPRESS_SAVES = false;
bool SOUND_ON = true;
bool VSYNC = false;
bool RESIZABLE = false;
bool PRIMARY_MONITOR = true;
u32 TEXTURE_PARAM = GL_NEAREST;
u8 MUSIC_VOLUME = 200;
u8 SOUND_VOLUME = 200;
u8 MASTER_VOLUME = 200;
Font HEADER_FONT;
Font BODY_FONT;

int TILE_SIZE = 32;
float SCALE = 1.0f;
vec4f COLORSCHEME[16];

//textures
Texture button_tex_n;
Texture button_tex_h;
Texture menu_tex[9];

//internal variables
INTERNAL int BODY_FONT_SIZE;
INTERNAL int HEADER_FONT_SIZE;
INTERNAL int FPS_CAP = 100;
INTERNAL int WINDOW_WIDTH = 800;
INTERNAL int WINDOW_HEIGHT = 600;
INTERNAL bool FULLSCREEN = false;
INTERNAL char* BODYFONTPATH;
INTERNAL char* HEADERFONTPATH;

//FUNCTION PROTOTYPES
std::vector<std::string> decipher_line(char* line, const char* filename, int line_num);
void process_init_line(std::vector<std::string> tokens, int line_num);

void init_globals() {
	printf("Loading launch data from configuration files...\n");

	//LOADING COLORSCHEME
	FILE* colors_file = fopen("data/colorscheme.txt", "r");
	char buffer[255];
	int i = 0;
	while (true) {
		i++;
		buffer[0] = 0;
		fgets(buffer, 255, colors_file);
		if (buffer[0] == 0) break;
		std::vector<std::string> tokens = decipher_line(buffer, "data/colorscheme.txt", i);

		if (tokens.size() > 0) {
			char* identifier = (char*)malloc(tokens[0].size() + 1);
			for (int i = 0; i < tokens[0].size(); ++i)
				identifier[i] = tokens[0].at(i);
			identifier[tokens[0].size()] = 0;

			std::vector<std::string> split = tokenize_str(identifier, '_');
			free(identifier);

			if (split[0] == "COLOR") {
				COLORSCHEME[stoi(split[1]) - 1] = vec4f(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]), 255.0f);
			}
			else {
				printf("ERROR: There is an entry in data/colorscheme.txt not related to colors. Did you mispell COLOR or is this in the wrong file?\n");
			}
		}
	}
	fclose(colors_file);

	//LOADING INIT DATA
	FILE* init_file = fopen("data/init.txt", "r");
	i = 0;
	while (true) {
		i++;
		buffer[0] = 0;
		fgets(buffer, 255, init_file);
		if (buffer[0] == 0) break;
		std::vector<std::string> tokens = decipher_line(buffer, "data/init.txt", i);

		if (tokens.size() > 0) {
			process_init_line(tokens, i);
		}
	}
	fclose(init_file);

	printf("DONE\n");
}

void init_context(const char* title) {
	initWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, FULLSCREEN, RESIZABLE, PRIMARY_MONITOR);
	//initAudio();

	printf("Loading font into VRAM...\n");
	BODY_FONT = loadFont(BODYFONTPATH, BODY_FONT_SIZE);
	HEADER_FONT = loadFont(HEADERFONTPATH, HEADER_FONT_SIZE);

	if (BODY_FONT.characters[0] == NULL) printf("BODY_FONT was not loaded correctly. The file (%s) is not valid.\n", BODYFONTPATH);
	if (HEADER_FONT.characters[0] == NULL) printf("HEADER_FONT was not loaded correctly. The file (%s) is not valid.\n", HEADERFONTPATH);
	free(BODYFONTPATH);
	free(HEADERFONTPATH);

	setFPSCap(FPS_CAP);
	setVSync(VSYNC);
	setMasterVolume(MASTER_VOLUME);

	TILE_SIZE *= SCALE;

	setClearColor(COLORSCHEME[0]);

	button_tex_n = loadTexture("data/art/button_n.png", TEXTURE_PARAM);
	button_tex_h = loadTexture("data/art/button_h.png", TEXTURE_PARAM);
	int w;
	int h;
	int i = 0;
	unsigned char* image = SOIL_load_image("data/art/menu.png", &w, &h, 0, SOIL_LOAD_RGBA);
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			menu_tex[i++] = getSubImage(image, w, x * (w / 3), y * (h / 3), w / 3, h / 3);
	free(image);
}

Texture getSubImage(unsigned char* pixels, int pixels_width, int x, int y, int width, int height) {
	Texture subimage;
	glPixelStorei(GL_UNPACK_ROW_LENGTH, pixels_width);
	unsigned char* subimage_pixels = pixels + (x + y * pixels_width) * 4;
	subimage = loadTexture(subimage_pixels, width, height, TEXTURE_PARAM);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	return subimage;
}

std::vector<std::string> tokenize_str(char* str, char seperator) {
	std::vector<std::string> result;
	do {
		char *begin = str;
		while (*str != seperator && *str) {
			str++;
		}
		result.push_back(std::string(begin, str));
	} while (0 != *str++);
	return result;
}

bool is_a_number(char c) {
	switch (c) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;
	default:
		return false;
	}
}

//essentially just a list of possible configuration statements and handling errors
//pretty much has to be hardcoded
void process_init_line(std::vector<std::string> tokens, int line_num) {
	if (tokens[0] == "SOUND") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tSOUND should only have one argument\n", "data/init.txt", line_num);
		if (tokens[1] == "YES") SOUND_ON = true;
		else if (tokens[1] == "NO") SOUND_ON = false;
		else {
			printf("ERROR IN FILE '%s', line #%i:\tSOUND can only equal YES or NO\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "FULLSCREEN") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tFULLSCREEN should only have one argument\n", "data/init.txt", line_num);
		if (tokens[1] == "YES") FULLSCREEN = true;
		else if (tokens[1] == "NO") FULLSCREEN = false;
		else {
			printf("ERROR IN FILE '%s', line #%i:\tFULLSCREEN can only equal YES or NO\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "RESIZABLE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tRESIZABLE should only have one argument\n", "data/init.txt", line_num);
		if (tokens[1] == "YES") RESIZABLE = true;
		else if (tokens[1] == "NO") RESIZABLE = false;
		else {
			printf("ERROR IN FILE '%s', line #%i:\tRESIZABLE can only equal YES or NO\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "DISPLAY_FPS") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tDISPLAY_FPS should only have one argument\n", "data/init.txt", line_num);
		if (tokens[1] == "YES") DISPLAY_FPS = true;
		else if (tokens[1] == "NO") DISPLAY_FPS = false;
		else {
			printf("ERROR IN FILE '%s', line #%i:\tDISPLAY_FPS can only equal YES or NO\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "VSYNC") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tVSYNC should only have one argument\n", "data/init.txt", line_num);
		if (tokens[1] == "YES") VSYNC = true;
		else if (tokens[1] == "NO") VSYNC = false;
		else {
			printf("ERROR IN FILE '%s', line #%i:\tVSYNC can only equal YES or NO\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "COMPRESS_SAVES") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tCOMPRESS_SAVES should only have one argument\n", "data/init.txt", line_num);
		if (tokens[1] == "YES") COMPRESS_SAVES = true;
		else if (tokens[1] == "NO") COMPRESS_SAVES = false;
		else {
			printf("ERROR IN FILE '%s', line #%i:\tCOMPRESS_SAVES can only equal YES or NO\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "MONITOR") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tMONITOR should only have one argument\n", "data/init.txt", line_num);
		if (tokens[1] == "PRIMARY") PRIMARY_MONITOR = true;
		else if (tokens[1] == "SECONDARY") PRIMARY_MONITOR = false;
		else {
			printf("ERROR IN FILE '%s', line #%i:\tVMONITOR can only equal YES or NO\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "SOUND_VOLUME") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tSOUND_VOLUME should only have one argument\n", "data/init.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			SOUND_VOLUME = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tSOUND_VOLUME must be a whole number\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "MUSIC_VOLUME") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tMUSIC_VOLUME should only have one argument\n", "data/init.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			MUSIC_VOLUME = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tMUSIC_VOLUME must be a whole number\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "MASTER_VOLUME") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tMUSIC_VOLUME should only have one argument\n", "data/init.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			MUSIC_VOLUME = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tMUSIC_VOLUME must be a whole number\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "WINDOW_WIDTH") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tWINDOW_WIDTH should only have one argument\n", "data/init.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			WINDOW_WIDTH = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tWINDOW_WIDTH must be a whole number\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "WINDOW_HEIGHT") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tWINDOW_HEIGHT should only have one argument\n", "data/init.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			WINDOW_HEIGHT = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tWINDOW_HEIGHT must be a whole number\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "FPS_CAP") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tFPS_CAP should only have one argument\n", "data/init.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			FPS_CAP = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tFPS_CAP must be a whole number\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "BODY_FONT_SIZE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tBODY_FONT_SIZE should only have one argument\n", "data/init.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			BODY_FONT_SIZE = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tBODY_FONT_SIZE must be a whole number\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "HEADER_FONT_SIZE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tHEADER_FONT_SIZE should only have one argument\n", "data/init.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			HEADER_FONT_SIZE = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tHEADER_FONT_SIZE must be a whole number\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "TEXTURE_PARAMETER") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tFPS_CAP should only have one argument\n", "data/init.txt", line_num);
		if (tokens[1] == "NEAREST") {
			TEXTURE_PARAM = GL_NEAREST;
		}
		else if (tokens[1] == "LINEAR") {
			TEXTURE_PARAM = GL_LINEAR;
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tTEXTURE_PARAMETER must be NEAREST or LINEAR\n", "data/init.txt", line_num);
		}
	}

	if (tokens[0] == "BODY_FONT") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tBODY_FONT should only have one argument\n", "data/init.txt", line_num);
		std::string path = "data/art/";
		path.append(tokens[1]);
		BODYFONTPATH = (char*)malloc(path.size() + 1);
		for (int i = 0; i < path.size(); ++i)
			BODYFONTPATH[i] = path[i];
		BODYFONTPATH[path.size()] = 0;
	}
	if (tokens[0] == "HEADER_FONT") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tHEADER_FONT should only have one argument\n", "data/init.txt", line_num);
		std::string path = "data/art/";
		path.append(tokens[1]);
		HEADERFONTPATH = (char*)malloc(path.size() + 1);
		for (int i = 0; i < path.size(); ++i)
			HEADERFONTPATH[i] = path[i];
		HEADERFONTPATH[path.size()] = 0;
	}
}

std::vector<std::string> decipher_line(char* line, const char* filename, int line_num) {
	std::vector<std::string> tokens;
	remove_characters(line, '\n');
	remove_characters(line, '\t');
	remove_characters(line, ' ');
	if (line[0] == '(') {
		remove_characters(line, '(');
		remove_characters(line, ')');
		tokens = tokenize_str(line, '=');
		if (tokens[0].empty()) {
			if (tokens.size() > 1)
				printf("ERROR IN FILE '%s', line #%i:\tNo identifier in parenthesis.\n", filename, line_num);
			else
				printf("ERROR IN FILE '%s', line #%i:\tEmpty parenthesis!\n", filename, line_num);
		}
		else if (tokens.size() == 1) return tokens; //only 1 is fine, it's a flag if there is only one. (If there was SUPPOSED to be an = sign
													//then that will be discovered later and an error presented then.)
		else if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tMultiple '=' present inside parenthesis.\n", filename, line_num);
		else {
			std::vector<std::string> parameters;
			char* second_part = (char*)malloc(tokens[1].size() + 1);
			for (int i = 0; i < tokens[1].size(); ++i)
				second_part[i] = tokens[1].at(i);
			second_part[tokens[1].size()] = 0;

			if (character_exists(second_part, ',')) {
				tokens.pop_back();
				parameters = tokenize_str(second_part, ',');
				for (int i = 0; i < parameters.size(); ++i)
					tokens.push_back(parameters.at(i));
			}
			free(second_part);
		}
	}
	return tokens;
}

void remove_characters(char* string, char to_remove) {
	char* i = string;
	char* j = string;
	while (*j != NULL) {
		*i = *j++;
		if (*i != to_remove) i++;
	}
	*i = 0;
}

void remove_leading_characters(char* string, char to_remove) {
	char* i = string;
	char* j = string;
	while (*j == to_remove) {
		*i = *j++;
		if (*i != to_remove) i++;
	}
	*i = 0;
}

bool character_exists(char* string, char to_check) {
	int len = strlen(string);
	for (int i = 0; i < len; ++i)
		if (string[i] == to_check) return true;
	return false;
}

//TODO: Make this work.
void message(char* message) {
	char* ptr = message;
	//loop until null termination
	while (*ptr != 0) {
		if (*ptr == '%') {
			//handle formats like printf does
		}
		//[C#] sample text [/C#] will draw 'sample text' with a color in the colorscheme 
		//(replace # with a num, that is the index of colorscheme that will be used)
		if (*ptr == '[') {
			ptr++;
			if (*ptr == 'C') {
				ptr++;
				if (is_a_number(*ptr)) {
					//vec4f color = color_scheme[stoi(*ptr)];
					//drawTexture(draw with color);
				}
				ptr++;
				ptr++;
			}
			else {
				//if there is no 'C' after the bracket then it is a normal bracket. Print the bracket in the message as normal
				//drawTexture('[');
			}
		}
	}
	//drawTexture();

	ptr++;
}