#include "states.h"

#define MAX_STATES 20

State* states[MAX_STATES];
int numStates = 0;
int currState = 0;

void set_state(std::string name) {
	bool found = false;
	for (int i = 0; i < numStates; ++i) {
		if (states[i]->name == name) {
			currState = i;
			states[i]->ready();
			found = true;
		}
	}
	if (!found)
		printf("ERROR: STATES: State '%s' doesn't exist!\n", name.c_str());
}

void add_state(State* state, std::string name) {
	if (numStates >= MAX_STATES)
		printf("ERROR: STATES: TOO MANY STATES!\n");
	else {
		state->name = name;
		states[numStates] = state;
		numStates++;
		state->init();
	}
}

void remove_state(std::string name) {
	bool found = false;
	for (int i = 0; i < numStates; ++i) {
		if (states[i]->name == name) {
			states[i]->dispose();
			//move everything down 
			//i is the item to remove
			for (int j = i + 1; j < numStates; ++j) {
				states[j - 1] = states[j];
			}
			numStates--;
			found = true;
		}
	}
	if (!found)
		printf("ERROR: STATES: State '%s' doesn't exist!\n", name.c_str());
}

void update_current_state() {
	states[currState]->update();
}