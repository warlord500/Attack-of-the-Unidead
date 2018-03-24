/*
Copyright (C) 2018, corbin stark, jadon belezos, josiah Baldwin
Steven Schulze

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/
#include "globals.h"
#include <bahamut.h>
#include <audio.h>
#include <iostream>
#include "commonMenuStateInfo.h"
#include <utility>

std::string textInput(std::string data, int key)
{
	if (key >= 32 && key <= 125) {
		data.push_back(key);
	}
	else if (key == KEY_BACKSPACE && data.size() > 0){ //delete char if there is one 
		data.pop_back();
	}
	return std::move(data);
}

UiStateResult frame_update(std::function<UiStateResult(vec2)> frameUpdate,Texture& cursor)
{	
	UiStateResult res = UiStateResult::main_menu;
	while (!is_window_closed() & res == UiStateResult::continueProcessing) {
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
		
		draw_text(BODY_FONT, "The performance of the above could be better.", 50, 80);
		return UiStateResult::continueProcessing;
	},cursor);
}