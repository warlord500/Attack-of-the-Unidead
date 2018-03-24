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
#pragma once
#include <vector>
#include <entity.h>

struct Node {
	Node();
	Node(int x, int y, Node* parent, double gCost, double hCost);
	int x;
	int y;
	Node* parent;
	int gCost;
	int hCost;
	int fCost;
};

struct Map {
	int* grid;
	int width;
	int height;
};

struct Room;

struct Exit {
	Room* exitTo;
	int x;
	int y;
};

struct Room {
	Map* map;
	std::vector<Exit> exits;
	std::vector<Entity*> entities;
};