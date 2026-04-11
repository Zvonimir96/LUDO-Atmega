#pragma once

#include "utils.h"
#include "hardwareResources.h"
#include "AnimationManager.h"

/**
 * @brief High-level LED control interface
 * 
 * Singleton class providing convenient methods for setting colors
 * and animations on different game elements (houses, path, buttons, dice).
 * Abstracts the complexity of strip positions and animation management.
 */
class Handler
{
public:
    /**
     * @brief Get singleton instance
     * @return Reference to the single Handler instance
     */
    static Handler &getInstance()
    {
        static Handler instance;
        return instance;
    }

    /**
     * @brief Initialize LED handler
     * @param callback Function to call when animations complete
     */
    void init(AnimatorCallback callback);

    /**
     * @brief Set color for player's starting house
     * @param player Player index (0-3)
     * @param color Color to set
     */
    void setHouse(uint8_t player, const Color &color);
    
    /**
     * @brief Set color for player's safe house (goal zone)
     * @param player Player index (0-3)
     * @param color Color to set
     */
    void setSafeHouse(uint8_t player, const Color &color);
    
    /**
     * @brief Set color for entire game path
     * @param color Color to set
     */
    void setPath(const Color &color);
    
    /**
     * @brief Set color for specific house exit position
     * @param index Exit index (0-3, one per player)
     * @param color Color to set
     */
    void setHouseExit(const uint8_t index, const Color &color);

    /**
     * @brief Start fade animation for player's left/right buttons
     * @param player Player index (0-3)
     * @param color Base color for animation
     */
    void setButtonAnimation(uint8_t player, const Color &color);
    
    /**
     * @brief Start fade animation for player's submit button
     * @param player Player index (0-3)
     * @param color Base color for animation
     */
    void setSubmitAnimation(uint8_t player, const Color &color);
    
    /**
     * @brief Stop button animation for player
     * @param player Player index (0-3)
     */
    void removeButtonAnimation(uint8_t player);
    
    /**
     * @brief Stop submit button animation for player
     * @param player Player index (0-3)
     */
    void removeSubmitAnimation(uint8_t player);

    /**
     * @brief Display dice number for player
     * @param player Player index (0-3) - affects rotation
     * @param number Dice value (1-6)
     * @param color Color to display
     */
    void setDiceNumber(uint8_t player, uint8_t number, Color color);
    
    /**
     * @brief Start fade animation on dice display
     * @param color Base color for animation
     */
    void setDiceAnimation(const Color &color);
    
    /**
     * @brief Stop dice animation
     */
    void removeDiceAnimation();
    
    /**
     * @brief Animate dice rolling with visual effect
     * @param playerOnTurn Player rolling (0-3)
     * @param playerColor Player's color
     * @param diceNumber Final dice value (1-6)
     * @return The dice number rolled
     * 
     * @warning Uses blocking delay() calls - should be refactored
     */
    uint8_t diceRollAnimation(uint8_t playerOnTurn, Color playerColor, uint8_t diceNumber);

    /**
     * @brief Start move animation sequence
     * @param pixels Array of AnimationInfo for each step
     * @param size Number of steps in animation
     */
    void setMoveAnimation(AnimationInfo *pixels, uint8_t size);
    
    /**
     * @brief Cancel move animation
     */
    void removeMoveAnimation();
    
    /**
     * @brief Complete move animation and trigger callback
     */
    void endMoveAnimation();

    /**
     * @brief Set colors for multiple pixels at once
     * @param pixel Array of AnimationInfo with positions and colors
     * @param size Number of pixels to set
     */
    void setPixelsColor(AnimationInfo *pixel, uint8_t size);

    /**
     * @brief Set color for single pixel (test/debug)
     * @param position LED position
     * @param color Color to set
     */
    void setPixelColor(StripPosition position, Color color);

private:
    // Prevent instantiation
    Handler() {}
    // Prevent copying
    Handler(const Handler &) = delete;
    void operator=(const Handler &) = delete;

    Strip &strip = Strip::getInstance();                        ///< LED strip controller
    AnimationManager &animationManager = AnimationManager::getInstance();  ///< Animation manager

    /**
     * @brief Apply rotation to dice pixel based on player position
     * @param pixel Dice LED index (0-8)
     * @param player Player index (0-3)
     * @return Rotated pixel index
     */
    uint8_t applyDiceRotation(uint8_t pixel, uint8_t player);
};