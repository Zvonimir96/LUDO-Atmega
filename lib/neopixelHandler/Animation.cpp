#include "Animation.h"

Animation::Animation(PixelInfo *pixels, uint8_t numPixels, AnimationType type) : numPixels(numPixels), type(type)
{
    if (numPixels > 7)
    {
        Serial.println("ABN: animation contains more then 7 pixels");
        numPixels = 6;
    }

    for (uint8_t i = 0; i < numPixels; i++)
    {
        this->pixels[i] = pixels[i];
    }
}

Animation &Animation::operator=(const Animation &obj)
{
    numPixels = obj.numPixels;
    type = obj.type;

    for (uint8_t i = 0; i < numPixels; i++)
    {
        this->pixels[i] = obj.pixels[i];
    }

    return *this;
}

void Animation::update()
{
    for (uint8_t i = 0; i < numPixels; i++)
    {
        pixels[i].primary.fade();
        strip.setColor(pixels[i].position, pixels[i].primary, false);
    }
}

bool Animation::operator==(const Animation &other) const
{
    for (uint8_t i = 0; i < numPixels; i++)
    {
        if (pixels[i] != other.pixels[i])
        {
            return false;
        }
    }
    return true;
}

bool Animation::operator!=(const Animation &other) const
{
    return !(*this == other);
}