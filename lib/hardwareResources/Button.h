#pragma once

#include "utils.h"
#include "PCF8575.h"

#include <Arduino.h>

typedef void (*ButtonCallback)(uint16_t buttonBitMask);

class Button
{
public:
    static Button &getInstance()
    {
        static Button instance;
        return instance;
    }

    void init(ButtonCallback callback);
    void update();
    void enablePlayerButtons(uint8_t player);
    void enableSubmitButtons(uint8_t player);
    void disablePlayerButtons(uint8_t player);
    void enablePlayersButtons();
    void enableDice();
    void disableDice();
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
    ButtonCallback callback;

    static volatile bool canUpdate;
    static void isr();

    // TODO: this will need rework. This is blocking funtion, this should be ticker
    void buzzerTone();
};
