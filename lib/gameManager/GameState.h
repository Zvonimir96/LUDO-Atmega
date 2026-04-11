#pragma once

/**
 * @brief Game state machine states
 * 
 * Defines all possible states in the game flow.
 */
enum class GameState
{
    INIT = 0,              ///< Initial state during setup
    COLOR_SELECTION = 1,   ///< Players selecting their colors
    GAME = 2,              ///< Active gameplay - player selecting figure to move
    DICE_ROLL = 3,         ///< Waiting for player to roll dice
    WAIT_FOR_CALLBACK = 4  ///< Animation playing, waiting for completion
};
