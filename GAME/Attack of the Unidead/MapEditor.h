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
#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H
#include "commonMenuStateInfo.h"
#include <string>
class MapEditorUi {
public:
	MapEditorUi();
	UiStateResult operator()(vec2 mousePos);
	static UiStateResult mapEditor(Texture& cursor);
private:
	Menu menu;
	std::string room_size;
};
#endif