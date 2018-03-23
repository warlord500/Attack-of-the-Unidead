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