#include "globals.h"
#include <bahamut.h>
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
#include "states.h"
#include "MapEditor.h"

int main() {
	init_globals();
	init_context("Attack of the Unidead");

	set_stretch_mode(STRETCH_VIEWPORT);
	set_aspect_mode(ASPECT_KEEP);

	set_mouse_hidden(true);
	Texture cursor = load_texture("data/art/cursor.png",   TEXTURE_PARAM);

	Menu menu;
	menu.xPos = 260;
	menu.yPos = 90;
	menu.width = 3;

	add_state(new MapEditor(), "mapEditor");
	set_state("mapEditor");
	
	while (!is_window_closed()) {
		vec2 mousePos = get_mouse_pos();

		begin_drawing();
		begin2D();

		update_current_state();

		/*
		//TEXT DEMONSTRATION
		draw_text(HEADER_FONT, "Hello World!", 100, 100);
		draw_text(BODY_FONT, "This is a test!", 100, 120);

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
		*/

		draw_texture(cursor, mousePos.x, mousePos.y);

		end2D();
		end_drawing();
	}
	dispose_texture(cursor);
	dispose_window();
	return 0;
}