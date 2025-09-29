#include "Handler.h"

void Handler::init()
{
    strip.init();
}

void Handler::setHouse(uint8_t player, const Color &color)
{
    player *= 4;

    for (uint8_t i = 0; i < 4; i++)
    {
        strip.setColor(StripE::HOUSE, player + i, color, false);
    }

    strip.show(StripE::HOUSE);
}

void Handler::setSafeHouse(uint8_t player, const Color &color)
{
    player *= 4;

    for (uint8_t i = 0; i < 4; i++)
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

void Handler::setPath(const Color &color, const uint8_t index)
{
    strip.setColor(StripE::PATH, index * 13 + 1, color, 1);
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

    PixelInfo pixels[3];
    for (uint8_t i = 0; i < 3; i++)
    {
        pixels[i] = PixelInfo(StripPosition(StripE::BUTTONS, i + player), Color(color));
    }

    animationManager.add(pixels, 3, AnimationType::GLOBAL_FADE);
}

void Handler::removeButtonAnimation(uint8_t player)
{
    player *= 3;

    PixelInfo pixels[3];
    Color blackColor;
    blackColor.setVal(0);

    for (uint8_t i = 0; i < 3; i++)
    {
        pixels[i] = PixelInfo(StripPosition(StripE::BUTTONS, i + player));
        strip.setColor(StripE::BUTTONS, i + player, blackColor, false);
    }

    strip.show(StripE::BUTTONS);
    animationManager.remove(pixels, 3);
}

void Handler::setDiceAnimation(const Color &color)
{
    PixelInfo pixels[9];
    for (uint8_t i = 0; i < 9; i++)
    {
        pixels[i] = PixelInfo(StripPosition(StripE::DICE, i), Color(color));
    }

    animationManager.add(pixels, 9, AnimationType::GLOBAL_FADE);
}

void Handler::removeDiceAnimation()
{
    PixelInfo pixels[9];
    for (uint8_t i = 0; i < 9; i++)
    {
        pixels[i] = PixelInfo(StripPosition(StripE::DICE, i));
    }

    animationManager.remove(pixels, 9);
    strip.clear(StripE::DICE);
    strip.show(StripE::DICE);
}