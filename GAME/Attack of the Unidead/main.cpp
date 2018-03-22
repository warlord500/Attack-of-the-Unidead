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

enum class uiStateResult {
	mainMenu,
	startGame,
	options,
	mapEditor,
	exitAndClose,
};

uiStateResult mainMenu(Texture& cursor);
int main() {
	init_globals();
	init_context("Attack of the Unidead");
	set_stretch_mode(STRETCH_VIEWPORT);
	set_aspect_mode(ASPECT_KEEP);
	set_mouse_hidden(true);
	Texture cursor = load_texture("data/art/cursor.png", TEXTURE_PARAM);

	uiStateResult menuState = uiStateResult::mainMenu;
	while (menuState != uiStateResult::exitAndClose) {
		switch (menuState) {
		case uiStateResult::mainMenu:
			menuState = mainMenu(cursor);
			break;
		case uiStateResult::startGame:
			//menuState = startGame();
			break;
		case uiStateResult::options:
			// menuState = options();
			break;
		case uiStateResult::mapEditor:
			//menuState = mapEditor();
			break;
		}

	}
	//global destruction
	dispose_texture(cursor);
	dispose_window();
	return 0;
}


/**
	this runs the main menu, 
	returns, what next menu state to run
	
	cursor is only passed in this case because it
	gets shared against all states(assumedly)

	if any menu needs to load special textures it will have to 
	in the loop and be reloaded for next ui state!

*/
uiStateResult mainMenu(Texture& cursor) {

	Menu menu;
	menu.xPos = 260;
	menu.yPos = 90;
	menu.width = 6;
	//loaded custom textures here!
	while (!is_window_closed()) {
		vec2 mousePos = get_mouse_pos();

		begin_drawing();
		begin2D();

		//Main menu! 
		menu.row(4);
		menu.background();
		menu.title("Main Menu!");

		if (menu.push_button("start game")) {
			//return uiStateResult::startGame;
		}
		if (menu.push_button("options")) {
			//return uiStateResult::options;
		}
		if (menu.push_button("map editor")) {
			//return uiStateResult::mapEditor;
		}
		if (menu.push_button("close game")) {
			return uiStateResult::exitAndClose;
		}
		draw_texture(cursor, mousePos.x, mousePos.y);

		end2D();
		end_drawing();
	}

	//at this point we are ending the program!
	return uiStateResult::exitAndClose;
}