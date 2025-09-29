#include "Color.h"

Color::Color()
{
    hue = 0;
    sat = 255;
    val = 255;
}

Color::Color(uint16_t hue)
{
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

void Color::fade()
{
    if (fade_up)
        val += UPDATE_FADE_STEP;
    else
        val -= UPDATE_FADE_STEP;

    if (val <= UPDATE_FADE_MIN)
    {
        fade_up = true;
        val = UPDATE_FADE_MIN;
    }
    else if (val >= 255)
    {
        fade_up = false;
        val = 255;
    }
}

Color &Color::operator=(const Color &obj)
{
    hue = obj.hue;
    sat = obj.sat;
    val = obj.val;
    fade_up = obj.fade_up;

    return *this;
}