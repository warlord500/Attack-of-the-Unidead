#include "MapEditor.h"
#include "window.h"
#include <bahamut.h>

void mapOptions(MapEditorUi& map, Texture& cursor);
MapEditorUi::MapEditorUi()
{
	this->menu.xPos = 100;
	this->menu.yPos = 60;
	this->menu.width = 8;
	
	
}

//this contains the main code for MapEditorUi!
UiStateResult MapEditorUi::operator()(vec2 mousePos)
{
	menu.row(2);
	menu.background();
	menu.title("sorry!");
	const int key = get_key_pressed();
	if (key >= 32 && key <= 125) this->room_size.push_back(key);
	if (key == KEY_BACKSPACE) this->room_size.pop_back();
	draw_text(BODY_FONT, room_size.c_str(), 50, 50);
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