/**
 * @file main.cpp
 * @brief Main application entry point for LUDO game
 * 
 * Initializes game system and runs main loop that updates
 * animations and processes button inputs.
 */

#include <Arduino.h>
#include "gameManager.h"
#include "neopixelHandler.h"


/**
 * @brief Arduino setup function - runs once at startup
 * 
 * Initializes serial communication and game handler.
 */
void setup()
{
    Serial.begin(9600); // TODO: Remove after development is done
    GameHandler::getInstance().init();
}

/**
 * @brief Arduino loop function - runs continuously
 * 
 * Updates animation system and processes button inputs.
 */
void loop()
{
    AnimationManager::getInstance().update();
    Button::getInstance().update();
}
