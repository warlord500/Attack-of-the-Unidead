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
#include "MapEditor.h"
#include "window.h"
#include <bahamut.h>
#include "commonMenuStateInfo.h"
#include <sstream>

void map_options(MapEditorUi& map, Texture& cursor);

MapEditorUi::MapEditorUi() {
	this->menu.xPos = CENTER_HORIZONTAL;
	this->menu.yPos = CENTER_VERTICAL;
	this->menu.width = 4;
}

//this contains the looped code for MapEditorUi!
UiStateResult MapEditorUi::operator()(vec2 mousePos) {
	menu.row(3);
	menu.background();
	menu.title("Map Editor");
	
#if 0
	const int key = get_key_pressed();
	this->roomSize = std::move(text_input(std::move(this->roomSize),key));
	
	std::stringstream displayRoomSizeStream;
	displayRoomSizeStream << "room Size: ";
	displayRoomSizeStream << this->roomSize;
	const auto displayRoomSizeString = displayRoomSizeStream.str();

	draw_text(BODY_FONT, displayRoomSizeString.c_str() , 50, 50);
#endif

	if (menu.push_button("New Map")) {
		return UiStateResult::NEW_MAP;
	}
	if (menu.push_button("Load Map")) {
		//load map then put it into the map editor
		return UiStateResult::MAP_EDITOR;
	}
	if (menu.push_button("Back")) {
		return UiStateResult::MAIN_MENU;
	}
	return UiStateResult::CONTINUE;
}

UiStateResult MapEditorUi::map_edit_menu(Texture& cursor) {
	MapEditorUi map;
	UiStateResult res = UiStateResult::MAIN_MENU;
	do { //specialize the options for map!
		res = frame_update(map, cursor);
		if (res == UiStateResult::NEW_MAP) {
			map_options(map, cursor);
		}
		if (res == UiStateResult::MAP_EDITOR) {
			//go to map editor instead of the map edit menu.
		}
		
	} while (res != UiStateResult::MAIN_MENU);
	return UiStateResult::MAIN_MENU;
}

void map_options(MapEditorUi& map, Texture& cursor) {
	frame_update(
		[&map](vec2 mouse) {
		const int START_Y = 100;

		if (draw_text_button("Back", 50, 50)) {
			return UiStateResult::MAIN_MENU;
		}
		if (draw_text_button("Create", 290, START_Y + 110)) {
			return UiStateResult::MAP_EDITOR;
		}
		draw_text(HEADER_FONT, "Mouse over the text fields to type your input", 150, 300, RED.x, RED.y, RED.z);
		draw_text(BODY_FONT, "Room Width", 290, START_Y);
		draw_text(BODY_FONT, "Room Height", 285, START_Y + 50);
		text_input_field(&map.roomWidth, 280, START_Y + 20, INPUT_NUMBERS_ONLY);
		text_input_field(&map.roomHeight, 280, START_Y + 70, INPUT_NUMBERS_ONLY);
		return UiStateResult::CONTINUE;
	}, cursor);
}