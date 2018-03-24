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

void mapOptions(MapEditorUi& map, Texture& cursor);

MapEditorUi::MapEditorUi()
{
	this->menu.xPos = 100;
	this->menu.yPos = 60;
	this->menu.width = 8;
	
	
}

//this contains the looped code for MapEditorUi!
UiStateResult MapEditorUi::operator()(vec2 mousePos)
{
	
	menu.row(2);
	menu.background();
	menu.title("sorry!");
	
	const int key = get_key_pressed();
	this->room_size = std::move(textInput(std::move(this->room_size),key));
	
	std::stringstream display_room_size_stream;
	display_room_size_stream << "room Size: ";
	display_room_size_stream << this->room_size;
	const auto display_room_size_string = display_room_size_stream.str();

	draw_text(BODY_FONT, display_room_size_string.c_str() , 50, 50);




	if (menu.push_button("the map editor is unimplemented!")) {
		printf("why doesnt this work!");
		return UiStateResult::main_menu;
	}
	if (menu.push_button("options")) {
		return UiStateResult::options;
	}
	return UiStateResult::continueProcessing;
}

   
UiStateResult MapEditorUi::mapEditor(Texture& cursor)
{
	MapEditorUi map;
	UiStateResult res = UiStateResult::main_menu;
	do { //specialize the options for map!
		res = frame_update(map, cursor);
		if (res == UiStateResult::options){
			mapOptions(map, cursor);
		}
		
	} while (res != UiStateResult::main_menu);
	return UiStateResult::main_menu;
}

void mapOptions(MapEditorUi& map,Texture& cursor) {

	Menu menu;
	menu.xPos = 100;
	menu.yPos = 60;
	menu.width = 8;
	frame_update([&menu](vec2 mouse){
		menu.row(1);
		menu.background();
		menu.title("map options doesnt work sorry!");
		if (menu.push_button("back to main menu via mapOptions!")) {
			printf("options button pushed");
			return UiStateResult::main_menu;
		}
		return UiStateResult::continueProcessing;
	},cursor);

}