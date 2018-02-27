#include "game_objects.h"
#include <string>
#include <SOIL.h>

int NUM_UNIT_TYPES;
Unit* UNIT_TYPES;
int NUM_BUILDING_TYPES;
Building* BUILDING_TYPES;

int get_unit_ID(const char* identifier) {
	for (int i = 0; i < NUM_UNIT_TYPES; ++i) {
		if (strcmp(UNIT_TYPES[i].identifier, identifier) == 0) {
			return i;
		}
	}
	return -1;
}

void process_building_line(std::vector <std::string> tokens, std::vector<Building>& buildings, int line_num) {
	if (tokens[0] == "BUILDING") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tBUILDING should only have one argument\n", "data/buildings.txt", line_num);
		Building building;
		building.identifier = (char*)malloc(tokens[1].size() + 1);
		for (int i = 0; i < tokens[1].size(); ++i)
			building.identifier[i] = tokens[1].at(i);
		building.identifier[tokens[1].size()] = 0;

		building.construction_time = 0;
		building.cost = 0;
		building.happiness_change = 0;
		building.population_change = 0;
		building.population_growth_change = 0;

		buildings.push_back(building);
	}
	if (tokens[0] == "NAME") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tNAME should only have one argument\n", "data/buildings.txt", line_num);
		buildings.back().name = (char*)malloc(tokens[1].size() + 1);
		for (int i = 0; i < tokens[1].size(); ++i)
			buildings.back().name[i] = tokens[1].at(i);
		buildings.back().name[tokens[1].size()] = 0;
	}
	if (tokens[0] == "COST") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tCOST should only have one argument\n", "data/buildings.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			buildings.back().cost = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tCOST must be a whole number\n", "data/buildings.txt", line_num);
		}
	}
	if (tokens[0] == "DAYS_TO_BUILD") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tDAYS_TO_BUILD should only have one argument\n", "data/buildings.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			buildings.back().construction_time = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tDAYS_TO_BUILD must be a whole number\n", "data/buildings.txt", line_num);
		}
	}
	if (tokens[0] == "POPULATION_GROWTH_CHANGE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tPOPULATION_GROWTH_CHANGE should only have one argument\n", "data/buildings.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			buildings.back().population_growth_change = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tPOPULATION_GROWTH_CHANGE must be a whole number\n", "data/buildings.txt", line_num);
		}
	}
	if (tokens[0] == "POPULATION_CHANGE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tPOPULATION_CHANGE should only have one argument\n", "data/buildings.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			buildings.back().population_change = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tPOPULATION_CHANGE must be a whole number\n", "data/buildings.txt", line_num);
		}
	}
	if (tokens[0] == "HAPPINESS_CHANGE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tHAPPINESS_CHANGE should only have one argument\n", "data/buildings.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			buildings.back().happiness_change = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tHAPPINESS_CHANGE must be a whole number\n", "data/buildings.txt", line_num);
		}
	}
	if (tokens[0] == "UNITS_TO_ENABLE") {
		if (tokens.size() < 2) printf("ERROR IN FILE '%s', line #%i:\tUNITS_TO_ENABLE should have more than one argument\n", "data/buildings.txt", line_num);
		for (int i = 1; i < tokens.size(); ++i) {
			int ID = get_unit_ID(tokens[i].c_str());
			if (ID != -1) buildings.back().units_to_enable.push_back(ID);
		}
	}
}

void process_unit_line(std::vector <std::string> tokens, std::vector<Unit>& units, int line_num) {
	if (tokens[0] == "UNIT") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tUNIT should only have one argument\n", "data/units.txt", line_num);
		Unit unit;
		unit.identifier = (char*)malloc(tokens[1].size() + 1);
		for (int i = 0; i < tokens[1].size(); ++i)
			unit.identifier[i] = tokens[1].at(i);
		unit.identifier[tokens[1].size()] = 0;

		unit.active = false;
		unit.owner = 0;
		unit.x = 0;
		unit.y = 0;
		units.push_back(unit);
	}
	if (tokens[0] == "NAME") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tNAME should only have one argument\n", "data/units.txt", line_num);
		units.back().name = (char*)malloc(tokens[1].size() + 1);
		for (int i = 0; i < tokens[1].size(); ++i)
			units.back().name[i] = tokens[1].at(i);
		units.back().name[tokens[1].size()] = 0;
	}
	if (tokens[0] == "DAMAGE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tDAMAGE should only have one argument\n", "data/units.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			units.back().damage = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tDAMAGE must be a whole number\n", "data/units.txt", line_num);
		}
	}
	if (tokens[0] == "HEALTH") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tHEALTH should only have one argument\n", "data/units.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			units.back().health = stoi(tokens[1]);
			units.back().max_health = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tHEALTH must be a whole number\n", "data/units.txt", line_num);
		}
	}
	if (tokens[0] == "SPEED") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tSPEED should only have one argument\n", "data/units.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			units.back().speed = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tSPEED must be a whole number\n", "data/units.txt", line_num);
		}
	}
	if (tokens[0] == "MOVE_RANGE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tMOVE_RANGE should only have one argument\n", "data/units.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			units.back().move_range = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tMOVE_RANGE must be a whole number\n", "data/units.txt", line_num);
		}
	}
	if (tokens[0] == "ATTACK_RANGE") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tATTACK_RANGE should only have one argument\n", "data/units.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			units.back().attack_range = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tATTACK_RANGE must be a whole number\n", "data/units.txt", line_num);
		}
	}
	if (tokens[0] == "COST") {
		if (tokens.size() > 2) printf("ERROR IN FILE '%s', line #%i:\tCOST should only have one argument\n", "data/units.txt", line_num);
		if (is_a_number(tokens[1].at(0))) {
			units.back().cost = stoi(tokens[1]);
		}
		else {
			printf("ERROR IN FILE '%s', line #%i:\tCOST must be a whole number\n", "data/units.txt", line_num);
		}
	}
	if (tokens[0] == "IMAGE_1") {
		if (tokens.size() != 6) printf("ERROR IN FILE '%s', line #%i:\tIMAGE_1 should have five arguments\n", "data/units.txt", line_num);
		std::string path = "data/art/";
		path.append(tokens[1]);
		char* cpath = (char*)malloc(path.size() + 1);
		for (int i = 0; i < path.size(); ++i)
			cpath[i] = path[i];
		cpath[path.size()] = 0;

		int w;
		int h;
		unsigned char* pixels = SOIL_load_image(path.c_str(), &w, &h, 0, SOIL_LOAD_RGBA);
		if (pixels == NULL) {
			printf("The image '%s' doesn't exist.\n", cpath);
			free(pixels);
			free(cpath);
			return;
		}
		units.back().image_1 = getSubImage(pixels, w, stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
		free(pixels);
		free(cpath);
	}
	if (tokens[0] == "IMAGE_2") {
		if (tokens.size() != 6) printf("ERROR IN FILE '%s', line #%i:\tIMAGE_2 should have five arguments\n", "data/units.txt", line_num);
		std::string path = "data/art/";
		path.append(tokens[1]);
		char* cpath = (char*)malloc(path.size() + 1);
		for (int i = 0; i < path.size(); ++i)
			cpath[i] = path[i];
		cpath[path.size()] = 0;

		int w;
		int h;
		unsigned char* pixels = SOIL_load_image(path.c_str(), &w, &h, 0, SOIL_LOAD_RGBA);
		if (pixels == NULL) {
			printf("The image '%s' doesn't exist.\n", cpath);
			free(pixels);
			free(cpath);
			return;
		}
		units.back().image_2 = getSubImage(pixels, w, stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
		free(pixels);
		free(cpath);
	}
}

void load_game_object_types() {
	//LOADING UNITS DATA
	FILE* units_file = fopen("data/units.txt", "r");
	int i = 0;
	char buffer[255];
	std::vector<Unit> units;
	std::vector<Building> buildings;
	while (true) {
		i++;
		buffer[0] = 0;
		fgets(buffer, 255, units_file);
		if (buffer[0] == 0) break;
		std::vector<std::string> tokens = decipher_line(buffer, "data/units.txt", i);

		if (tokens.size() > 0) {
			process_unit_line(tokens, units, i);
		}
	}
	fclose(units_file);

	NUM_UNIT_TYPES = units.size();
	UNIT_TYPES = new Unit[NUM_UNIT_TYPES];
	for (int i = 0; i < NUM_UNIT_TYPES; ++i) {
		UNIT_TYPES[i] = units.at(i);
	}

	//LOADING BUILDING DATA
	FILE* buildings_file = fopen("data/buildings.txt", "r");
	i = 0;
	while (true) {
		i++;
		buffer[0] = 0;
		fgets(buffer, 255, buildings_file);
		if (buffer[0] == 0) break;
		std::vector<std::string> tokens = decipher_line(buffer, "data/buildings.txt", i);

		if (tokens.size() > 0) {
			process_building_line(tokens, buildings, i);
		}
	}
	fclose(buildings_file);

	NUM_BUILDING_TYPES = buildings.size();
	BUILDING_TYPES = new Building[NUM_BUILDING_TYPES];
	for (int i = 0; i < NUM_UNIT_TYPES; ++i) {
		BUILDING_TYPES[i] = buildings.at(i);
	}
}