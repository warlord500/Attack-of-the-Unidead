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
			menuState =  main_menu(cursor);
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