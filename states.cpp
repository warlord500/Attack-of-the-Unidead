#include "states.h"

#define MAX_STATES 15
State* states[MAX_STATES];
int curr_state;
int num_states;

void add_state(State* state, std::string name) {
	if (num_states >= MAX_STATES)
		printf("ERROR: STATES: TOO MANY STATES!\n");
	else {
		states[num_states] = state;
		num_states++;
		state->init();
	}
}

void remove_state(std::string name) {
	bool found = false;
	for (int i = 0; i < num_states; ++i) {
		if (states[i]->name == name) {
			states[i]->dispose();
			//move everything down 
			//i is the item to remove
			for (int j = i + 1; j < num_states; ++j) {
				states[j - 1] = states[j];
			}
			num_states--;
			found = true;
		}
	}
	if (!found)
		printf("ERROR: STATES: State '%s' doesn't exist!\n", name.c_str());
}

void set_state(std::string name) {
	bool found = false;
	for (int i = 0; i < num_states; ++i) {
		if (states[i] != NULL && states[i]->name == name) {
			curr_state = i;
			found = true;
		}
	}
	if (!found)
		printf("ERROR: STATES: State '%s' doesn't exist!\n", name.c_str());
}

void update_curr_state() {
	states[curr_state]->update();
}

void draw_curr_state() {
	states[curr_state]->draw();
}