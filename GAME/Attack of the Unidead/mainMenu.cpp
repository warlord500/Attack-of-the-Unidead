
#include "globals.h"
#include <bahamut.h>
#include <audio.h>
#include <iostream>
#include "commonMenuStateInfo.h"

UiStateResult frame_update(std::function<UiStateResult(vec2)> frameUpdate,Texture& cursor)
{	
	UiStateResult res = UiStateResult::continueProcessing;
	while (!is_window_closed() && res == UiStateResult::continueProcessing) {
		vec2 mousePos = get_mouse_pos();
		begin_drawing();
		begin2D();

		res = frameUpdate(mousePos);
		//this code doesnt get called if 
		//exception occurs!
		draw_texture(cursor, mousePos.x, mousePos.y);
		end2D();
		end_drawing();
	}
	return res;
}	
/**
this runs the main menu,
returns, what next menu state to run

cursor is only passed in this case because it
gets shared against all states(assumedly)

if any menu needs to load special textures it will have to
in the loop and be reloaded for next ui state!

*/
UiStateResult main_menu(Texture& cursor) {

	Menu menu;
	menu.xPos = 260;
	menu.yPos = 90;
	menu.width = 6;
	
	 return frame_update([&menu](vec2 mousePos) {
		//Main menu! 
		menu.row(4);
		menu.background();
		menu.title("Main Menu!");
		if (menu.push_button("start game")) {
			//return UiStateResult::startGame;
		}
		if (menu.push_button("options")) {
			//return UiStateResult::options;
		}
		if (menu.push_button("map editor")) {
			return UiStateResult::mapEditor;
		}
		if (menu.push_button("close game")) {
			return UiStateResult::exitAndClose;
		}
		return UiStateResult::continueProcessing;
	},cursor);
}