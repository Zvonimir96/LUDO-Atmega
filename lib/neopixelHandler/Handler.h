#pragma once

#include "hardwareResources.h"
#include "utils.h"
#include "AnimationManager.h"

class Handler
{
public:
    static Handler &getInstance()
    {
        static Handler instance;
        return instance;
    }

    void init();

    void setHouse(uint8_t player, const Color &color);
    void setSafeHouse(uint8_t player, const Color &color);
    void setPath(const Color &color);
    void setPath(const Color &color, const uint8_t index);

    void setDiceNumber(uint8_t player, uint8_t number, Color color);

    void setButtonAnimation(uint8_t player, const Color &color);
    void removeButtonAnimation(uint8_t player);
    void setDiceAnimation(const Color &color);
    void removeDiceAnimation();

private:
    // Prevent instantiation
    Handler() {}
    // Prevent copying
    Handler(const Handler &) = delete;
    void operator=(const Handler &) = delete;

    Strip &strip = Strip::getInstance();
    AnimationManager &animationManager = AnimationManager::getInstance();

    uint8_t applyDiceRotation(uint8_t pixel, uint8_t player);
};