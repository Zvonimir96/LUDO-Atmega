#include "Color.h"

Color::Color()
{
    fadeUp = false;
    hue = 0;
    sat = 255;
    val = 255;
}

Color::Color(uint16_t hue)
{
    fadeUp = false;
    this->hue = hue;
    sat = 255;
    val = 255;
}

void Color::setHue(uint16_t hue)
{
    this->hue = hue;
}

void Color::setVal(uint8_t val)
{
    this->val = val;
}

void Color::setSat(uint8_t sat)
{
    this->sat = sat;
}

uint16_t Color::getHue()
{
    return hue;
}

uint8_t Color::getSat()
{
    return sat;
}

uint8_t Color::getVal()
{
    return val;
}

Color &Color::operator=(const Color &obj)
{
    hue = obj.hue;
    sat = obj.sat;
    val = obj.val;
    fadeUp = obj.fadeUp;

    return *this;
}

void Color::fade()
{
    if (fadeUp)
        val += UPDATE_FADE_STEP;
    else
        val -= UPDATE_FADE_STEP;

    if (val <= UPDATE_FADE_MIN)
    {
        fadeUp = true;
        val = UPDATE_FADE_MIN;
    }
    else if (val >= 255)
    {
        fadeUp = false;
        val = 255;
    }
}