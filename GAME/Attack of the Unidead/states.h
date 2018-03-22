#ifndef STATES_H
#define STATES_H

#include <string>

struct State {
	virtual void init() = 0;
	virtual void ready() = 0;
	virtual void update() = 0;
	virtual void dispose() = 0;
	std::string name;
};

void set_state(std::string name);
void add_state(State* state, std::string name);
void remove_state(std::string name);
void update_current_state();

#endif