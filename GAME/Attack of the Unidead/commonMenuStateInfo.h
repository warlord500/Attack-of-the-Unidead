#pragma once
#include <functional>
#include "gui.h"
#include <bahamut.h>
enum class UiStateResult {
	mainMenu,
	startGame,
	options,
	mapEditor,
	exitAndClose,
	continueProcessing,
};

UiStateResult frameUpdate(std::function<UiStateResult (vec2)> frameUpdate);
UiStateResult mainMenu(Texture& cursor);