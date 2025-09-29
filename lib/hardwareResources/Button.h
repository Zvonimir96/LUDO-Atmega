#pragma once

#include "utils.h"
#include "PCF8575.h"

#include <Arduino.h>

typedef void (*CallbackFunction)(uint16_t buttonBitMask);

class Button
{
public:
    static Button &getInstance()
    {
        static Button instance;
        return instance;
    }

    void init(CallbackFunction callback);
    void update();
    void enablePlayerButtons(uint8_t player);
    void disablePlayerButtons(uint8_t player);
    void enablePlayersButtons();
    void enableDice();
    void disable();

private:
    // Prevent instantiation
    Button() {}
    // Prevent copying
    Button(const Button &) = delete;
    void operator=(const Button &) = delete;

    uint16_t buttonsBitMask;
    uint16_t availableBitMask;
    PCF8575 PCF;
    CallbackFunction callback;

    static volatile bool canUpdate;
    static void isr();
    void buzzerTone();
};
