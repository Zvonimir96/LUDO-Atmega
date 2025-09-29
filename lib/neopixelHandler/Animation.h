#pragma once

#include "PixelInfo.h"
#include "AnimationType.h"
#include "hardwareResources.h"

#include <Arduino.h>

class Animation
{
public:
    Animation(){};
    Animation(PixelInfo *pixels, uint8_t numPixels, AnimationType type);
    Animation &operator=(const Animation &obj);

    void update();
    bool operator==(const Animation &other) const;
    bool operator!=(const Animation &other) const;

    // private:
    PixelInfo pixels[7];
    uint8_t numPixels;
    AnimationType type;

    Strip &strip = Strip::getInstance();
};