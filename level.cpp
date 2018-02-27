#include "level.h"
#include "globals.h"
#include <SOIL.h>

void Map::create(int width, int height) {
	this->width = width;
	this->height = height;
	map = new int[width * height];
}

void Map::load(char* path) {

}

void Map::save(char* path) {

}

void Map::draw(int xPos, int yPos) {
	for (int x = 0; x < width; ++x) 
		for (int y = 0; y < height; ++y) 
			drawTexture(tiles[map[x + y * width]], (x * TILE_SIZE) + xPos, (y * TILE_SIZE) + yPos);
}

void Map::dispose() {
	delete map;
}
