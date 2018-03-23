#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H
#include "commonMenuStateInfo.h"
class MapEditorUi {
public:
	MapEditorUi();
	UiStateResult operator()(vec2 mousePos);
	static UiStateResult mapEditor(Texture& cursor);
private:
	Menu menu;
};
#endif