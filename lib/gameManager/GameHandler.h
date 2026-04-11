#pragma once

#include "utils.h"
#include "neopixelHandler.h"
#include "hardwareResources.h"
#include "AnimationInfo.h"
#include "Player.h"
#include "GameState.h"

/**
 * @brief Main game controller - manages game logic and state
 * 
 * Singleton class that coordinates all game operations including:
 * - Player turns and actions
 * - Dice rolling
 * - Move validation
 * - Animation coordination
 * - State transitions
 */
class GameHandler
{
public:
    /**
     * @brief Get singleton instance
     * @return Reference to the single GameHandler instance
     */
    static GameHandler &getInstance()
    {
        static GameHandler instance;
        return instance;
    }

    /**
     * @brief Initialize game system
     * 
     * Sets up hardware, initializes players, sets initial colors,
     * and transitions to COLOR_SELECTION state.
     */
    void init();
    
    /**
     * @brief Handle left button press for a player
     * @param player Player index (0-3)
     * 
     * In COLOR_SELECTION: cycles to previous color
     * In GAME: selects previous figure
     */
    void playerActionLeft(uint8_t player);
    
    /**
     * @brief Handle right button press for a player
     * @param player Player index (0-3)
     * 
     * In COLOR_SELECTION: cycles to next color
     * In GAME: selects next figure
     */
    void playerActionRight(uint8_t player);
    
    /**
     * @brief Handle submit button press for a player
     * @param player Player index (0-3)
     * 
     * In COLOR_SELECTION: confirms color choice
     * In GAME: executes move with selected figure
     * In DICE_ROLL: skips turn if no valid moves
     */
    void playerActionSubmit(uint8_t player);
    
    /**
     * @brief Handle dice button press
     * 
     * Rolls dice (1-6), checks for valid moves, and transitions state.
     */
    void diceAction();

    /**
     * @brief Callback when animation completes
     * 
     * Called by AnimationManager when move animation finishes.
     * Updates game state and transitions to next player.
     */
    static void animationCallback();
    
    /**
     * @brief Callback when button is pressed
     * @param button Button bitmask indicating which button was pressed
     * 
     * Routes button press to appropriate action handler.
     */
    static void buttonCallback(uint16_t button);

private:
    // Prevent instantiation
    GameHandler() {}
    // Prevent copying
    GameHandler(const GameHandler &) = delete;
    void operator=(const GameHandler &) = delete;

    /**
     * @brief Cycle player color to previous in COLOR_SELECTION
     * @param player Player index
     */
    void changeColorLeft(uint8_t player);
    
    /**
     * @brief Cycle player color to next in COLOR_SELECTION
     * @param player Player index
     */
    void changeColorRight(uint8_t player);
    
    /**
     * @brief Select previous figure in GAME state
     */
    void changeFigureLeft();
    
    /**
     * @brief Select next figure in GAME state
     */
    void changeFigureRight();
    
    /**
     * @brief Update player's color on LED strips
     * @param player Player index
     * @param color New color to display
     */
    void setPlayerColor(uint8_t player, Color color);

    /**
     * @brief Transition from COLOR_SELECTION to DICE_ROLL
     * 
     * Initializes game state and starts first player's turn.
     */
    void startGame();
    
    /**
     * @brief Advance to next player's turn
     * 
     * Cycles through active players and updates UI.
     */
    void nextPlayer();
    
    /**
     * @brief Execute dice roll with animation
     * 
     * Generates random number (1-6), displays animation,
     * and checks if any figures can move.
     */
    void rollDice();

    /**
     * @brief Create animation sequence for figure movement
     * 
     * Complex logic that:
     * - Calculates path from current to target position
     * - Handles transitions between strips (PATH -> S_HOUSE)
     * - Detects opponent figures to capture
     * - Creates AnimationInfo array for each step
     */
    void setMoveAnimation();

    /**
     * @brief Check if any player has a figure at position
     * @param position Position to check
     * @param playerIndex Output parameter - index of player found
     * @return true if a figure exists at position
     */
    bool playerFigureOnPosition(StripPosition position, uint8_t *playerIndex);

    /**
     * @brief Validate if selected figure can move with current dice value
     * @param selectedFigure Figure index (0-3)
     * @return true if move is legal according to LUDO rules
     * 
     * Rules checked:
     * - From HOUSE: only with 6, and exit must be free
     * - On PATH: cannot land on own figure
     * - In S_HOUSE: cannot skip own figures
     * - Entering S_HOUSE: must have passed zero mark
     */
    bool canFigureMove(uint8_t selectedFigure);
    
    /**
     * @brief Count how many players are active
     * @return Number of active players (2-4)
     */
    uint8_t getNumberOfActivePlayers();
    
    uint8_t diceNumber;  ///< Last rolled dice value (1-6)

    Handler &neopixelHandler = Handler::getInstance();  ///< LED handler reference
    Button &button = Button::getInstance();             ///< Button handler reference

    StripPosition moveEndPosition;  ///< Target position for current move
    uint8_t playerOnTurn;           ///< Index of player whose turn it is
    uint8_t numberOfPlayerRolls;    ///< Number of consecutive rolls (for rolling 6)
    GameState gameState;            ///< Current game state

    Player players[NUMBER_OF_PLAYERS];  ///< Array of all players (4)
};