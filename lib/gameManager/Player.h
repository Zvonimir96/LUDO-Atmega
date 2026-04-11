#pragma once

#include "utils.h"

/**
 * @brief Represents a single player in the LUDO game
 * 
 * Manages player state including figure positions, color selection,
 * active status, and figure selection for moves.
 */
class Player
{
public:
    /**
     * @brief Default constructor - initializes player with default values
     * 
     * All figures start in HOUSE positions (indices 0-3).
     * Player is inactive by default.
     */
    Player();

    /**
     * @brief Set player's color index
     * @param index Index into availableColors array (0-5)
     */
    void setColorIndex(uint8_t index);
    
    /**
     * @brief Get player's current color
     * @return Color object with player's hue
     */
    Color getPlayerColor();
    
    /**
     * @brief Get player's color index
     * @return Index into availableColors array
     */
    uint8_t getPlayerColorIndex();
    
    /**
     * @brief Get position of currently selected figure
     * @return StripPosition of the selected figure
     */
    StripPosition getSelectedFigure();
    
    /**
     * @brief Get index of currently selected figure
     * @return Figure index (0-3)
     */
    uint8_t getSelectedFigureIndex();
    
    /**
     * @brief Set which figure is currently selected
     * @param figureIndex Figure index (0-3)
     * @return The selected figure index
     */
    uint8_t setSelectedFigure(uint8_t figureIndex);

    StripPosition figures[NUMBER_OF_FIGURES];    ///< Positions of all 4 figures
    bool figuresPassZeroMark[NUMBER_OF_FIGURES]; ///< Track if figure passed zero mark (required for entering safe house)

    /**
     * @brief Mark player as active in the game
     */
    void setActive();
    
    /**
     * @brief Check if player is active
     * @return true if player is participating in the game
     */
    bool isActive();
    
    /**
     * @brief Check if player has a figure at given position
     * @param position Position to check
     * @return true if any of player's figures is at this position
     */
    bool hasFigureOnPosition(StripPosition position);
    
    /**
     * @brief Check if all figures are in starting house
     * @return true if all 4 figures are in HOUSE strip
     */
    bool allFiguresInHouse();
    
    /**
     * @brief Check if specific figure has passed the zero mark
     * @param figureIndex Figure index (0-3)
     * @return true if figure has completed a full lap
     */
    bool didFigurePassedZeroMark(uint8_t figureIndex);
    
    /**
     * @brief Set zero mark pass status for a figure
     * @param figureIndex Figure index (0-3)
     * @param pass true if figure has passed zero mark
     */
    void setFigurePassedZeroMark(uint8_t figureIndex, bool pass);

private:
    static Color availableColors[NUMBER_OF_AVAILABLE_COLORS]; ///< Available colors for player selection
    uint8_t playerColorIndex;  ///< Currently selected color index
    uint8_t selectedFigure;    ///< Currently selected figure (0-3)
    bool active;               ///< Whether player is active in game
};