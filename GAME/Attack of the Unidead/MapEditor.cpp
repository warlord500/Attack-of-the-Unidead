#include "MapEditor.h"

MapEditorUi::MapEditorUi()
{
	this->menu.xPos = 100;
	this->menu.yPos = 60;
	this->menu.width = 6;
}

//this contains the main code for MapEditorUi!
UiStateResult MapEditorUi::operator()(vec2 mousePos)
{
	menu.row(1);
	menu.background();
	menu.title("sorry!");
	if (menu.push_button("the map editor is unimplemented!")) {
		return UiStateResult::main_menu;
	}
	return UiStateResult::continueProcessing;
}

UiStateResult MapEditorUi::mapEditor(Texture& cursor)
{
	MapEditorUi map;
	return frame_update(map,cursor);
}
