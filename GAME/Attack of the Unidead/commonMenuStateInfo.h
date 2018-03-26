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
#ifndef _COMMON_MENU_STATE_
#define _COMMON_MENU_STATE_
#include <functional>
#include "gui.h"
#include <bahamut.h>
enum class UiStateResult {
	MAIN_MENU,
	GAME,
	NEW_MAP,
	MAP_EDITOR,
	MAP_EDIT_MENU,
	EXIT_AND_CLOSE,
	//sadly c++ doesnt support enums 
	//with data, so include this for frame_update
	CONTINUE,
};
//noo! i really wish i could make this pure!
std::string text_input(std::string data, int key);

UiStateResult frame_update(std::function<UiStateResult(vec2)> frameUpdate,Texture& cursor);
UiStateResult main_menu(Texture& cursor);
#endif