#include "game_objects.h"
#include <string>
#include <SOIL.h>

int NUM_UNIT_TYPES;
Unit* UNIT_TYPES;

int get_unit_ID(const char* identifier) {
	for (int i = 0; i < NUM_UNIT_TYPES; ++i) {
		if (strcmp(UNIT_TYPES[i].identifier, identifier) == 0) {
			return i;
		}
	}
	return -1;
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
}

void load_game_object_types() {
	//LOADING UNITS DATA
	FILE* units_file = fopen("data/units.txt", "r");
	int i = 0;
	char buffer[255];
	std::vector<Unit> units;
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
}
