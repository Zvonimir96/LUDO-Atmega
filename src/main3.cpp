/*
#include <Arduino.h>

#include "gameManager.h"
#include "neopixelHandler.h"
#include "Color.h"
#include "hardwareResources.h"

AnimationManager &animationManager = AnimationManager::getInstance();
GameHandler &gameHandler2 = GameHandler::getInstance();
Button &button2 = Button::getInstance();

void setup()
{
    Serial.begin(9600);
    gameHandler2.init();
}

void loop()
{
    animationManager.update();
    button2.update();
}
*/