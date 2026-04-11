/**
 * @file Handler.cpp
 * @brief Implementation of Handler high-level LED control interface
 */
#include "Handler.h"

void Handler::init(AnimatorCallback callback)
{
    strip.init();
    animationManager.init(callback);
}

void Handler::setHouse(uint8_t player, const Color &color)
{
    player *= NUMBER_OF_PLAYERS;

    for (uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        strip.setColor(StripE::HOUSE, player + i, color, false);
    }

    strip.show(StripE::HOUSE);
}

void Handler::setSafeHouse(uint8_t player, const Color &color)
{
    player *= NUMBER_OF_PLAYERS;

    for (uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        strip.setColor(StripE::S_HOUSE, player + i, color, false);
    }

    strip.show(StripE::S_HOUSE);
}

void Handler::setPath(const Color &color)
{
    for (uint8_t i = 0; i < PATH_COUNT; i++)
    {
        strip.setColor(StripE::PATH, i, color, false);
    }

    strip.show(StripE::PATH);
}

void Handler::setHouseExit(const uint8_t index, const Color &color)
{
    strip.setColor(StripE::PATH, index * PATH_QUATER + HOUSE_EXIT, color);
}

void Handler::setDiceNumber(uint8_t player, uint8_t number, Color color)
{
    strip.clear(StripE::DICE);

    switch (number)
    {
    case 1:
        strip.setColor(StripPosition(StripE::DICE, 8), color, false);
        break;
    case 3:
        strip.setColor(StripPosition(StripE::DICE, 8), color, false);
    case 2:
        strip.setColor(StripPosition(StripE::DICE, applyDiceRotation(2, player)), color, false);
        strip.setColor(StripPosition(StripE::DICE, applyDiceRotation(6, player)), color, false);
        break;
    case 5:
        strip.setColor(StripPosition(StripE::DICE, 8), color, false);
    case 4:
        strip.setColor(StripPosition(StripE::DICE, 0), color, false);
        strip.setColor(StripPosition(StripE::DICE, 2), color, false);
        strip.setColor(StripPosition(StripE::DICE, 4), color, false);
        strip.setColor(StripPosition(StripE::DICE, 6), color, false);
        break;
    case 6:
        strip.setColor(StripPosition(StripE::DICE, applyDiceRotation(0, player)), color, false);
        strip.setColor(StripPosition(StripE::DICE, applyDiceRotation(1, player)), color, false);
        strip.setColor(StripPosition(StripE::DICE, applyDiceRotation(2, player)), color, false);
        strip.setColor(StripPosition(StripE::DICE, applyDiceRotation(4, player)), color, false);
        strip.setColor(StripPosition(StripE::DICE, applyDiceRotation(5, player)), color, false);
        strip.setColor(StripPosition(StripE::DICE, applyDiceRotation(6, player)), color, false);
        break;
    }

    strip.show(StripE::DICE);
}

uint8_t Handler::applyDiceRotation(uint8_t pixel, uint8_t player)
{
    pixel += 2 * player;
    pixel = pixel % 8;

    return pixel;
}

void Handler::setButtonAnimation(uint8_t player, const Color &color)
{
    player *= 3;

    AnimationInfo pixels[3];
    for (uint8_t i = 0; i < 3; i++)
    {
        pixels[i] = AnimationInfo(StripPosition(StripE::BUTTONS, i + player), color);
    }

    animationManager.add(pixels, 3, AnimationType::GLOBAL_FADE);
}

void Handler::setSubmitAnimation(uint8_t player, const Color &color)
{
    player *= 3;

    AnimationInfo pixels[] = {AnimationInfo(StripPosition(StripE::BUTTONS, 1 + player), color)};

    animationManager.add(pixels, 1, AnimationType::GLOBAL_FADE);
}

void Handler::removeButtonAnimation(uint8_t player)
{
    player *= 3;

    AnimationInfo pixels[3];
    Color blackColor;
    blackColor.setVal(0);

    for (uint8_t i = 0; i < 3; i++)
    {
        pixels[i] = AnimationInfo(StripPosition(StripE::BUTTONS, i + player));
        strip.setColor(StripE::BUTTONS, i + player, blackColor, false);
    }

    strip.show(StripE::BUTTONS);
    animationManager.remove(pixels, 3, AnimationType::GLOBAL_FADE);
}

void Handler::removeSubmitAnimation(uint8_t player)
{
    player *= 3;

    AnimationInfo pixels[1] = {AnimationInfo(StripPosition(StripE::BUTTONS, 1 + player))};
    Color blackColor;
    blackColor.setVal(0);

    strip.show(StripE::BUTTONS);
    animationManager.remove(pixels, 3, AnimationType::GLOBAL_FADE);
}

void Handler::setDiceAnimation(const Color &color)
{
    AnimationInfo pixels[9];
    for (uint8_t i = 0; i < 9; i++)
    {
        pixels[i] = AnimationInfo(StripPosition(StripE::DICE, i), Color(color));
    }

    animationManager.add(pixels, 9, AnimationType::GLOBAL_FADE);
}

void Handler::removeDiceAnimation()
{
    AnimationInfo pixels[9];
    for (uint8_t i = 0; i < 9; i++)
    {
        pixels[i] = AnimationInfo(StripPosition(StripE::DICE, i));
    }

    animationManager.remove(pixels, 9, AnimationType::GLOBAL_FADE);
    strip.clear(StripE::DICE);
    strip.show(StripE::DICE);
}

void Handler::setPixelsColor(AnimationInfo *pixel, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        strip.setColor(pixel[i].position.strip, pixel[i].position.index, pixel[i].primary, false);
    }

    strip.show();
}

void Handler::setPixelColor(StripPosition position, Color color)
{
    strip.setColor(position.strip, position.index, color);
}

void Handler::setMoveAnimation(AnimationInfo *pixels, uint8_t size)
{
    setPixelsColor(pixels, size);
    animationManager.add(pixels, size, AnimationType::MOVE);
}

void Handler::removeMoveAnimation()
{
    animationManager.removeMoveAnimation();
}

void Handler::endMoveAnimation()
{
    animationManager.endMoveAnimation();
}

uint8_t Handler::diceRollAnimation(uint8_t playerOnTurn, Color playerColor, uint8_t diceNumber)
{
    setDiceNumber(playerOnTurn, diceNumber, playerColor);

    // Dice animation
    int sleep = DICE_ANIMATION_START_DELAY;
    for (uint8_t i = 0; i < DICE_ANIMATION_NUMBER_OF_ITERATIONS; i++)
    {
        diceNumber++;
        if (diceNumber > 6)
            diceNumber = 1;

        setDiceNumber(playerOnTurn, diceNumber, playerColor);
        delay(sleep);

        sleep += DICE_ANIMATION_DELAY_INCREMENT;
    }

    return diceNumber;
}
