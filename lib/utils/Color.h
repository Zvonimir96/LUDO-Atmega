#pragma once

#include "utils.h"

#include <Arduino.h>

class Color
{
    uint16_t hue;
    uint8_t sat;
    uint8_t val;
    bool fade_up;

public:
    Color();
    Color(uint16_t);
    Color &operator=(const Color &obj);

    uint16_t getHue();
    uint8_t getSat();
    uint8_t getVal();

    void setHue(uint16_t);
    void setVal(uint8_t);
    void setSat(uint8_t);
    void fade();
};