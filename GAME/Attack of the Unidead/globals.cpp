#include "globals.h"
#include <cstdarg>
#include <SOIL.h>
#include <string>
#include <cctype>
#include <random>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <audio.h>


//VAR DEFAULTS (if they aren't defined in the config files for some reason)
bool DISPLAY_FPS = false;
bool COMPRESS_SAVES = false;
bool SOUND = true;
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
INTERNAL char* BODY_FONT_PATH;
INTERNAL char* HEADER_FONT_PATH;
const char * ART_DIRECTORY = "data/art/";

INTERNAL int FPS_CAP = 100;
INTERNAL int WINDOW_WIDTH = 800;
INTERNAL int WINDOW_HEIGHT = 600;
INTERNAL bool FULLSCREEN = false;


//FUNCTION PROTOTYPES
std::vector<std::string> decipher_line(char* line, const char* filename, int line_num);
void process_init_line(std::vector<std::string> tokens, int line_num);

//remove the commonality in error messages 
//and get type checking, instead of undefined behaivor!
void printErr(const char const* message, const int line_num) {
	printf("ERROR IN FILE 'data/init.txt', line #%i:\t%s\n", line_num, message);
};

void init_globals() {
	printf("Loading launch data from configuration files...\n");

	//LOADING COLORSCHEME
	FILE* colors_file = fopen("data/colorscheme.txt", "r");
	const int SIZE_OF_BUFFER = 255;
	char buffer[SIZE_OF_BUFFER] = {}; //set all values to 
	int i = 0;
	while (true) {
		i++;
		buffer[0] = 0;
		fgets(buffer, SIZE_OF_BUFFER, colors_file);
		if (buffer[0] == 0) break;
		std::vector<std::string> tokens = decipher_line(buffer, "data/colorscheme.txt", i);

		if (tokens.size() >= 4) {
			std::vector<std::string> split = tokenize_str(tokens[0].c_str(), '_');
			if (split.size() < 2) {
				printErr("need more tokens for colorscheme", 0);
			}
			else {
				if (split[0] == "COLOR") {
					COLORSCHEME[stoi(split[1]) - 1] = vec4f(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]), 255.0f);
				}
				else {
					printf("ERROR: There is an entry in data/colorscheme.txt not related to colors. Did you mispell COLOR or is this in the wrong file?\n");
				}
			}
		}
	}
	fclose(colors_file);

	//LOADING INIT DATA
	FILE* init_file = fopen("data/init.txt", "r");
	int j = 0;
	while (true) {
		j++;
		buffer[0] = 0;
		fgets(buffer, SIZE_OF_BUFFER, init_file);
		if (buffer[0] == 0) break;
		std::vector<std::string> tokens = decipher_line(buffer, "data/init.txt", j);

		if (tokens.size() > 0) {
			process_init_line(tokens, j);
		}
	}
	fclose(init_file);

	printf("DONE LOADING\n");
}

void init_context(const char* title) {
	initWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, FULLSCREEN, RESIZABLE, PRIMARY_MONITOR);

	printf("Loading font into VRAM...\n");
	
	const char*  msg = "%s was not loaded correctly. The file (%s) is not valid.\n";
	#define LOAD_FONT(NAME) {\
			 NAME = loadFont(NAME ## _PATH, NAME ## _SIZE); \
			 if (NAME.characters[0] == NULL) printf(msg, #NAME, NAME ## _PATH); \
			 free(NAME ## _PATH); \
		}

	LOAD_FONT(BODY_FONT);
	LOAD_FONT(HEADER_FONT);
	#undef LOAD_FONT

	setFPSCap(FPS_CAP);
	setVSync(VSYNC);
	setMasterVolume(MASTER_VOLUME);

	TILE_SIZE *=  static_cast<float>(SCALE);

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

std::vector<std::string> tokenize_str(const char* endOfSlice,  const char seperator) {
	std::vector<std::string> result;
	bool atEndOfString = false;
	do {
		  const char *beginOfSlice = endOfSlice;
		 while (*endOfSlice != seperator && *endOfSlice) {
			endOfSlice += 1;
		}
		result.push_back(std::string(beginOfSlice, endOfSlice));
		atEndOfString = (*endOfSlice == 0);
		endOfSlice += 1; //move past current slice for next segment to not include seperator 
	} while(!atEndOfString);

	return result;
}

#define ERR_ARG(NAME) \
	if(tokens.size() > 2) { \
		printErr(#NAME "should only have one argument\n", line_num); \
     } 

#define ERR_INIT_BOOL(NAME) \
		if(tokens[0] == #NAME){  \
			ERR_ARG(NAME); \
         \
			if (tokens[1] == "YES") { \
				NAME = true;  \
			} \
			else if (tokens[1] == "NO") { \
					NAME = false; \
			} \
			else { \
				printErr(#NAME "can only equal YES or NO\n", line_num); \
			} \
			return; \
         }

#define ERR_INIT_NUMBER(NAME) \
			if (tokens[0] == #NAME) { \
					ERR_ARG(NAME) \
					\
					if (isdigit(tokens[1].at(0))) { \
						NAME = stoi(tokens[1]); \
					} \
					else { \
						printErr(#NAME "must be a whole number\n", line_num); \
					} \
				return; \
			} 

#define ERR_INIT_STRING(NAME)  \
		if (tokens[0] == #NAME)  { \
				ERR_ARG(NAME); \
				std::string path = ART_DIRECTORY; \
				path.append(tokens[1]); \
				NAME = (char*)malloc(path.size() + 1); \
				for (unsigned int i = 0; i < path.size(); ++i) \
					NAME[i] = path[i]; \
				NAME[path.size()] = 0; \
				return; \
		} 
	
//something is wrong for the code above but i dont know what it is yet!
				

		
//essentially just a list of possible configuration statements and handling errors
//pretty much has to be hardcoded
void process_init_line(const std::vector<std::string> tokens, const int line_num) {
	
	if (tokens[0] == "TEXTURE_PARAMETER") {
		ERR_ARG(TEXTURE_PARAMATER);

		if (tokens[1] == "NEAREST") {
			TEXTURE_PARAM = GL_NEAREST;
		}
		else if (tokens[1] == "LINEAR") {
			TEXTURE_PARAM = GL_LINEAR;
		}
		else {
			printErr("TEXTURE_PARAMETER must be NEAREST or LINEAR", line_num);
		}
	}

	ERR_INIT_BOOL(PRIMARY_MONITOR);
	ERR_INIT_BOOL(SOUND);
	ERR_INIT_BOOL(FULLSCREEN);
	ERR_INIT_BOOL(RESIZABLE);
	ERR_INIT_BOOL(DISPLAY_FPS);
	ERR_INIT_BOOL(VSYNC);
	ERR_INIT_BOOL(COMPRESS_SAVES);	
#undef ERR_INIT_BOOL

	ERR_INIT_NUMBER(SOUND_VOLUME);
	ERR_INIT_NUMBER(MUSIC_VOLUME);
	ERR_INIT_NUMBER(MASTER_VOLUME);
	ERR_INIT_NUMBER(WINDOW_WIDTH);
	ERR_INIT_NUMBER(WINDOW_HEIGHT);
	ERR_INIT_NUMBER(FPS_CAP);
	ERR_INIT_NUMBER(BODY_FONT_SIZE);
	ERR_INIT_NUMBER(HEADER_FONT_SIZE);
#undef ERR_INIT_NUMBER

	ERR_INIT_STRING(BODY_FONT_PATH);
	ERR_INIT_STRING(HEADER_FONT_PATH);
#undef ERR_INIT_STRING
	//at this point we have an invalid data field. 
	printf("ERROR in file 'data/init.txt' on line %i, DATA FIELD IS UNKNOWN\n",line_num);
}


std::vector<std::string> decipher_line(char* line, const char* filename, const int line_num) {
	std::vector<std::string> tokens;
	remove_characters(line, '\n');
	remove_characters(line, '\t');
	remove_characters(line, ' ');
	if (line[0] == '(') {
		remove_characters(line, '(');
		remove_characters(line, ')');
		tokens = tokenize_str(line, '=');
		if (tokens.size() < 1) {
			printErr("must have something in thats not equals in paranthesis",line_num);
		}
		else if (tokens[0].empty()) {
			if (tokens.size() > 1) {
				printErr("No identifier in parenthesis.", line_num);
			}
			else {
				printErr("Empty parenthesis!", line_num);
			}
		}
		else if (tokens.size() == 1) {
			return tokens; //only 1 is fine, it's a flag if there is only one. (If there was SUPPOSED to be an = sign
								//then that will be discovered later and an error presented then.)
		}
		else if (tokens.size() > 2) {
			printErr("Multiple '=' present inside parenthesis.", line_num);
		}
		else if (tokens[1].find(',') != std::string::npos) {
			const auto parameters = tokenize_str(tokens[1].c_str(), ',');
			tokens.pop_back();
			//push parameters on tokens
			tokens.reserve(tokens.size() + parameters.size());
			tokens.insert(tokens.end(), parameters.begin(), parameters.end());
		}
		return tokens;
	}
}

void remove_characters(char* string, const char to_remove) {
	char* i = string;
	char* j = string;
	while (*j != NULL) {
		*i = *j++;
		if (*i != to_remove) i++;
	}
	*i = 0;
}

void remove_leading_characters(char* string, const char to_remove) {
	char* i = string;
	char* j = string;
	while (*j == to_remove) {
		*i = *j++;
		if (*i != to_remove) i++;
	}
	*i = 0;
}