#pragma once
#include "globals.h"
#include <vector>
//I have an Entity-Component-System I could use for dynamic objects but these aren't too complicated
//so I'll just jam all possible data for a unit/building in one struct and use them as needed.

struct Unit {
	inline void dispose() {
		disposeTexture(image_1);
		disposeTexture(image_2);
		disposeTexture(projectile);
		free(identifier);
		free(name);
	}
	int x;
	int y;
	std::vector<vec2f> path;

	char* identifier;
	char* name;
	int damage;
	int max_health;
	int health;
	int speed;
	bool active;
	int move_range;
	int attack_range;
	int cost;
	//I doubt I'd ever need more than 255 players on one map at a time...
	unsigned char owner;
	//there are only 2 frames of animation, and only one animation. to keep simple.
	Texture image_1;
	Texture image_2;
	Texture projectile;
};

struct Squad {
	inline void dispose() {
		free(units);
	}
	Unit leader;
	Unit* units;
	int unit_count;
	int speed;
};

struct Building {
	inline void dispose() {
		free(identifier);
		free(name);
	}
	char* identifier;
	char* name;
	int cost;
	int construction_time;
	int population_change;
	int population_growth_change;
	int happiness_change;
	std::vector<int> units_to_enable;
};

struct Hub {
	Texture tex;
};

struct Town {
	Texture tex;
	std::vector<Unit> garrison;
	std::vector<Building> buildings;
	int happiness;
	int population;
	int population_growth;
};

void load_game_object_types();

global_var int NUM_UNIT_TYPES;
global_var Unit* UNIT_TYPES;
global_var int NUM_BUILDING_TYPES;
global_var Building* BUILDING_TYPES;