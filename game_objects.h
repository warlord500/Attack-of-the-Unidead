#pragma once
#include "globals.h"
#include <vector>
//I have an Entity-Component-System I could use for dynamic objects but these aren't too complicated
//so I'll just jam all possible data for a unit/building in one struct and use them as needed.

struct Unit {
	inline void dispose() {
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

void load_game_object_types();

global_var int NUM_UNIT_TYPES;
global_var Unit* UNIT_TYPES;
