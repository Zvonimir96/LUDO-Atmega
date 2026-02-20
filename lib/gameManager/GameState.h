#pragma once

enum class GameState
{
    INIT = 0,
    COLOR_SELECTION = 1,
    GAME = 2,
    DICE_ROLL = 3,
    WAIT_FOR_CALLBACK = 4
};
