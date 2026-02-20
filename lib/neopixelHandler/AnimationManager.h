#pragma once

#include "AnimationType.h"
#include "hardwareResources.h"
#include "AnimationInfo.h"

typedef void (*AnimatorCallback)();

class AnimationManager
{
public:
    static AnimationManager &getInstance()
    {
        static AnimationManager instance;
        return instance;
    }

    void init(AnimatorCallback callback);
    void add(AnimationInfo *pixels, uint8_t numPixels, AnimationType type);
    void remove(AnimationInfo *pixels, uint8_t numPixels, AnimationType type);
    void update();

    void endMoveAnimation();
    void removeMoveAnimation();

    Color globalFade; // TODO: This shoult be somethingelse

private:
    // Prevent instantiation
    AnimationManager() {}
    // Prevent copying
    AnimationManager(const AnimationManager &) = delete;
    void operator=(const AnimationManager &) = delete;

    // TODO: This should be one entity
    AnimationInfo pixels[15];
    AnimationType pixelsAnimation[15];
    uint8_t animationCount = 0;
    unsigned long updateTime = 0;

    Strip &strip = Strip::getInstance();

    AnimatorCallback callback;
};
