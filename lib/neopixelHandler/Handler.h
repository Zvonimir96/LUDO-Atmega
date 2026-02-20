#pragma once

#include "utils.h"
#include "hardwareResources.h"
#include "AnimationManager.h"

class Handler
{
public:
    static Handler &getInstance()
    {
        static Handler instance;
        return instance;
    }

    void init(AnimatorCallback callback);

    void setHouse(uint8_t player, const Color &color);
    void setSafeHouse(uint8_t player, const Color &color);
    void setPath(const Color &color);
    void setHouseExit(const uint8_t index, const Color &color);

    void setButtonAnimation(uint8_t player, const Color &color);
    void setSubmitAnimation(uint8_t player, const Color &color);
    void removeButtonAnimation(uint8_t player);
    void removeSubmitAnimation(uint8_t player);

    void setDiceNumber(uint8_t player, uint8_t number, Color color);
    void setDiceAnimation(const Color &color);
    void removeDiceAnimation();
    uint8_t diceRollAnimation(uint8_t playerOnTurn, Color playerColor, uint8_t diceNumber);

    void setMoveAnimation(AnimationInfo *pixels, uint8_t size);
    void removeMoveAnimation();
    void endMoveAnimation();

    void setPixelsColor(AnimationInfo *pixel, uint8_t size);

    // TODO: remove, just for test puspuse
    void setPixelColor(StripPosition position, Color color);

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