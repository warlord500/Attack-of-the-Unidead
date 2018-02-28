#include <bahamut.h>
#include <state.h>
#include "globals.h"
#include "level.h"
#include "menu.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
//				TODO
//////////////////////////////////////////////////////////////////////
//1)	
//2)	
//3)	
//////////////////////////////////////////////////////////////////////

void main() {
	init_globals();
	init_context("Attack of the Unidead");
	load_game_object_types();

	setMouseHidden(true);
	Texture cursor = loadTexture("data/art/cursor.png", TEXTURE_PARAM);

	while (!isWindowClosed()) {
		beginDrawing();
		begin2D();

		drawTexture(cursor, getMousePos().x, getMousePos().y);

		end2D();
		endDrawing();
	}
	disposeTexture(cursor);
	disposeWindow();
}