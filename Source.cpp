#include "ENGINE/bahamut.h"
#include "ENGINE/state.h"
#include "globals.h"
#include "level.h"
#include "menu.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
//								TODO
//////////////////////////////////////////////////////////////////////
// 1)	Finish TextArea edit code
// 2)	button MenuComponent
// 3)	ScrollPane MenuComponent
// 4)	drop-down-list MenuComponent
// 5)	progress-bar MenuComponent
//			in addition, each panel should have a framebuffer that is the 
//			size of the panel, and the components should be drawn onto that,
//			that way if components are drawn off the panel, they will disappear
//			instead of going off the panel into places they shouldn't.
//			doing this means that we can also have a scroll bar to scroll down
//			to see components too far down (or up) to see on the panel.
// 6)	create an autotile system that figures out if it's an edge tile 
//			or not and adjusts to the correct image.
// 7)	create simple map editor with the autotile system (also using
//			MenuComponents for things like selecting the tile type
//			and units and placing them)
// 8)	create cutscene (or trigger) system to have more dynamic and 
//			interesting levels.
// 9)	levels (at least later in the game when this ability is unlocked)
//			should have two maps. One for the present, one for the past.
//			(the game will have a time-travel mechanic)
// 10)	copy level related stuff (such as pathfinding) over from other
//			iterations of this game.
// 11)	every unit will only have an idle animation (and the idle animation
//			will only have 2 frames) for simplicity. However, I should
//			create a generic melee animation (like a swiping effect) and
//			simple projectiles (probably also only 2 frame animations)
// 12)	add 'new', 'save', and 'load' functions to map editor. Map editor
//			should allow you to choose size of map.
// 13)	design overworld using the map editor
// 14)	create menus for towns. Player will be able to recruit units and heroes
//			from towns, in addition to maybe being able to do quests to
//			upgrade the town.
// 15)	create quest system. (keep track of objectives, etc.)
// 16)	create system to send idle recruits to do quests on their own.
// 17)	MAYBE create random attacks on towns (?)
// 18)	add basic abilities for heroes
// 19)	add time travel mechanic. If all friendly units (maybe only heroes?) are on
//			tiles that are not blocked in the past, they can time travel to the past
//			which changes the environment and enemies (and will be required sometimes
//			to advance)
// 20)	
// 21)	
// 22)	
//////////////////////////////////////////////////////////////////////

void main() {
	init_globals();
	init_context("Crappy SRPG thingy");
	load_game_object_types();

	int pos_x = 0;
	int pos_y = 0;

	setMouseHidden(true);
	Texture cursor = loadTexture("data/art/cursor.png", TEXTURE_PARAM);

	Map map;

	while (!isWindowClosed()) {
		beginDrawing();

		if (isKeyDown(KEY_RIGHT))	pos_x -= SCROLL_SPEED;
		if (isKeyDown(KEY_LEFT))	pos_x += SCROLL_SPEED;
		if (isKeyDown(KEY_DOWN))	pos_y -= SCROLL_SPEED;
		if (isKeyDown(KEY_UP))		pos_y += SCROLL_SPEED;

		begin2D();
		drawTexture(cursor, getMousePos().x, getMousePos().y);
		end2D();
		endDrawing();
	}
	disposeWindow();
}