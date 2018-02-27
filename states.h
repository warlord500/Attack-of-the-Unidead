#pragma once
#include "ENGINE\entity.h"

class State {
public:
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void dispose() = 0;

	std::string name;
protected:
	Entity* data;
};

void add_state(State* state, std::string name);
void remove_state(std::string name);
void set_state(std::string name);
void update_curr_state();
void draw_curr_state();