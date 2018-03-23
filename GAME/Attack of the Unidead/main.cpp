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
#include "MapEditor.h"
#include "commonMenuStateInfo.h"
int main() {
	init_globals();
	init_context("Attack of the Unidead");
	set_stretch_mode(STRETCH_VIEWPORT);
	set_aspect_mode(ASPECT_KEEP);
	set_mouse_hidden(true);
	Texture cursor = load_texture("data/art/cursor.png", TEXTURE_PARAM);

	UiStateResult menuState = UiStateResult::main_menu;
	while (menuState != UiStateResult::exitAndClose) {
		switch (menuState) {
		case UiStateResult::main_menu:
			menuState = main_menu(cursor);
			break;
		case UiStateResult::startGame:
			//menuState = startGame();
			break;
		case UiStateResult::options:
			// menuState = options();
			break;
		case UiStateResult::mapEditor:
			menuState = MapEditorUi::mapEditor(cursor);
			break;
		case UiStateResult::continueProcessing:
			printf("we have a bug in frame update!");
			menuState = UiStateResult::exitAndClose;
			break;
		}

	}
	//global destruction
	dispose_texture(cursor);
	dispose_window();
	return 0;
}