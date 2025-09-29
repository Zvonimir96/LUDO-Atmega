#pragma once

#include "utils.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Strip
{
public:
    static Strip &getInstance()
    {
        static Strip instance;
        return instance;
    }

    void init();
    void setColor(const StripPosition stripPosition, Color color, bool update = true);
    void setColor(const StripE strip, const uint8_t index, Color color, bool update = true);
    void setColor(const StripE strip, uint8_t indexs[], Color colors[], uint8_t size, bool update = true);
    void clear(const StripE strip);
    void show();
    void show(const StripE strip);

private:
    // Prevent instantiation
    Strip() {}
    // Prevent copying
    Strip(const Strip &) = delete;
    void operator=(const Strip &) = delete;

    Adafruit_NeoPixel *strips[STRIPS_COUNT];
};
