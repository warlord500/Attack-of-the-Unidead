#pragma once
#include <functional>
#include "gui.h"
#include <bahamut.h>
enum class UiStateResult {
	main_menu,
	startGame,
	options,
	mapEditor,
	exitAndClose,
	//sadly c++ doesnt support enums 
	//with data, so include this for frame_update
	continueProcessing,
};

UiStateResult frame_update(std::function<UiStateResult(vec2)> frameUpdate,Texture& cursor);
UiStateResult main_menu(Texture& cursor);