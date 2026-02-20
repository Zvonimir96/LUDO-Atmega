#include <Arduino.h>

#include "gameManager.h"
#include "neopixelHandler.h"

AnimationManager &animationManager = AnimationManager::getInstance();

// TODO: rename, ovarijable ovakvog imena se vec negdje koriste
GameHandler &gameHandler2 = GameHandler::getInstance();
Button &button2 = Button::getInstance();

extern int __heap_start, *__brkval;

unsigned long updateTime = 0;

int freeMemory()
{
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void setup()
{
    Serial.begin(9600);
    gameHandler2.init();
}

void loop()
{
    // TODO: this should be ticker
    animationManager.update();
    button2.update();

    /*if (updateTime <= millis())
    {
        Serial.print(F("Free RAM: "));
        Serial.println(freeMemory());

        updateTime += 1000;
    }*/
}
