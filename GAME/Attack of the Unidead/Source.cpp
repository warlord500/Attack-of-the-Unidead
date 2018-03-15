#include "globals.h"
#include <bahamut.h>
#include <state.h>
#include <audio.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////
//								TODO
//////////////////////////////////////////////////////////////////////
// 1)	
// 2)	
// 3)	
// 4)	
// 5)	
//////////////////////////////////////////////////////////////////////

#include "gui.h"

void main() {
	init_globals();
	init_context("Attack of the Unidead");

	setStretchMode(STRETCH_VIEWPORT);
	setAspectMode (ASPECT_KEEP);

	setMouseHidden(true);
	Texture cursor = loadTexture("data/art/cursor.png",   TEXTURE_PARAM);

	Menu menu;
	menu.xPos = 260;
	menu.yPos = 90;
	menu.width = 3;
	
	while (!isWindowClosed()) {
		vec2f mouse_pos = getMousePos();

		beginDrawing();
		begin2D();

		//TEXT DEMONSTRATION
		drawText(HEADER_FONT, "Hello World!", 100, 100);
		drawText(BODY_FONT, "This is a test!", 100, 120);

		//MENU DEMONSTRATION
		menu.row(3);
		menu.background();
		menu.title("Menu!");
		if (menu.push_button("Button One")) {
			printf("Button One has been pressed!\n");
		}
		if (menu.push_button("Button Two")) {
			printf("Button Two has been pressed!\n");
		}
		if (menu.push_button("Button Three")) {
			printf("Button Three has been pressed!\n");
		}

		drawTexture(cursor, mouse_pos.x, mouse_pos.y);

		end2D();

		endDrawing();
	}
	disposeTexture(cursor);
	disposeWindow();
}