#include "ENGINE/bahamut.h"
#include "ENGINE/state.h"
#include "globals.h"
#include "level.h"
#include "menu.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
//				TODO
//////////////////////////////////////////////////////////////////////
1)	
2)	
3)	
//////////////////////////////////////////////////////////////////////

void main() {
	init_globals();
	init_context("Attack of the Unidead");
	load_game_object_types();

	int pos_x = 0;
	int pos_y = 0;

	setMouseHidden(true);
	Texture cursor = loadTexture("data/art/cursor.png", TEXTURE_PARAM);

	while (!isWindowClosed()) {
		beginDrawing();

		if (isKeyDown(KEY_RIGHT))	pos_x -= SCROLL_SPEED;
		if (isKeyDown(KEY_LEFT))	pos_x += SCROLL_SPEED;
		if (isKeyDown(KEY_DOWN))	pos_y -= SCROLL_SPEED;
		if (isKeyDown(KEY_UP))		pos_y += SCROLL_SPEED;

		begin2D();
		drawTexture(cursor, getMousePos().x, getMousePos().y);
		end2D();
		endDrawing();
	}
	disposeWindow();
}
