#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include "states.h"

class MapEditor : public State {
public:
	//is called when the state is added
	void init();
	//is called whenever the state is switched to
	void ready();
	//is called every frame
	void update();
	//is called when state is removed
	void dispose();
private:
	
};

#endif