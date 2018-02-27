#pragma once
#include "globals.h"
#include "game_objects.h"

struct Map {
	void create(int width, int height);
	void load(char* path);
	void save(char* path);
	void draw(int xPos, int yPos);
	void dispose();

	int tiles_count;
	Texture* tiles;

	int* map;
	int width;
	int height;
};

struct Level {
	void load(char* path);
	void save(char* path);
	Map map;
	Unit* units;
	int unit_count;
	unsigned int timer;
};
