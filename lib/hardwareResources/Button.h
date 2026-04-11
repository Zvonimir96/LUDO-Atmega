#pragma once

#include "utils.h"
#include "PCF8575.h"

#include <Arduino.h>

typedef void (*ButtonCallback)(uint16_t buttonBitMask);

/**
 * @brief Button input handler using PCF8575 I2C IO expander
 * 
 * Singleton class managing 13 buttons (4 players × 3 buttons + dice).
 * Uses interrupt-driven reading for efficiency and provides enable/disable
 * control for individual buttons or groups.
 */
class Button
{
public:
    /**
     * @brief Get singleton instance
     * @return Reference to the single Button instance
     */
    static Button &getInstance()
    {
        static Button instance;
        return instance;
    }

    /**
     * @brief Initialize button system
     * @param callback Function to call when button is pressed
     * 
     * Sets up I2C communication, configures interrupt pin (pin 2),
     * and initializes buzzer (pin 10).
     */
    void init(ButtonCallback callback);
    
    /**
     * @brief Check for button presses and trigger callbacks
     * 
     * Should be called in main loop. Only reads I2C when interrupt flag is set.
     */
    void update();
    
    /**
     * @brief Enable left/right buttons for a player
     * @param player Player index (0-3)
     */
    void enablePlayerButtons(uint8_t player);
    
    /**
     * @brief Enable submit button for a player
     * @param player Player index (0-3)
     */
    void enableSubmitButtons(uint8_t player);
    
    /**
     * @brief Disable left/right buttons for a player
     * @param player Player index (0-3)
     */
    void disablePlayerButtons(uint8_t player);
    
    /**
     * @brief Enable left/right buttons for all players
     */
    void enablePlayersButtons();
    
    /**
     * @brief Enable dice button
     */
    void enableDice();
    
    /**
     * @brief Disable dice button
     */
    void disableDice();
    
    /**
     * @brief Disable all buttons
     */
    void disable();

private:
    // Prevent instantiation
    Button() {}
    // Prevent copying
    Button(const Button &) = delete;
    void operator=(const Button &) = delete;

    uint16_t buttonsBitMask;     ///< Current button states (bit per button)
    uint16_t availableBitMask;   ///< Mask of enabled buttons
    PCF8575 PCF;                 ///< I2C IO expander object
    ButtonCallback callback;     ///< Function to call on button press

    static volatile bool canUpdate;  ///< Flag set by ISR when button pressed
    
    /**
     * @brief Interrupt service routine
     * 
     * Sets canUpdate flag when PCF8575 interrupt pin goes low.
     */
    static void isr();

    /**
     * @brief Play buzzer feedback tone
     * 
     * @warning Uses blocking tone() call - should be refactored to non-blocking
     */
    void buzzerTone();
};
