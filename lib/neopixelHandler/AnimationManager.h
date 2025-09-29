#pragma once

#include "Animation.h"

#include <Arduino.h>

class AnimationManager
{
public:
    static AnimationManager &getInstance()
    {
        static AnimationManager instance;
        return instance;
    }

    void add(PixelInfo *pixels, uint8_t numPixels, AnimationType type);
    void remove(PixelInfo *pixels, uint8_t numPixels);
    void update();

private:
    // Prevent instantiation
    AnimationManager() {}
    ~AnimationManager() {}
    // Prevent copying
    AnimationManager(const AnimationManager &) = delete;
    void operator=(const AnimationManager &) = delete;

    Animation animations[4];
    uint8_t animationCount = 0;
    unsigned long updateTime = 0;

    Strip &strip = Strip::getInstance();
};
