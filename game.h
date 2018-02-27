#pragma once
#include "states.h"

class Game : public State {
public:
	void init();
	void draw();
	void update();
	void dispose();
private:

};