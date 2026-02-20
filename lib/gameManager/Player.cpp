#include "Player.h"

Color Player::availableColors[6] = {Color(0), Color(10000), Color(20000), Color(30000), Color(35000), Color(40000)};

Player::Player()
{
    playerColorIndex = 0;
    active = false;

    for (uint8_t i; i < NUMBER_OF_FIGURES; i++)
    {
        figures[i].strip = StripE::HOUSE;
        figures[i].index = i;
        figuresPassZeroMark[i] = false;
    }
}

void Player::setColorIndex(uint8_t index)
{
    playerColorIndex = index;
}

Color Player::getPlayerColor()
{
    return Color(availableColors[playerColorIndex].getHue());
}

bool Player::isActive()
{
    return active;
}

void Player::setActive()
{
    active = true;
}

uint8_t Player::getPlayerColorIndex()
{
    return playerColorIndex;
}

StripPosition Player::getSelectedFigure()
{
    return figures[selectedFigure];
}

uint8_t Player::getSelectedFigureIndex()
{
    return selectedFigure;
}

uint8_t Player::setSeletedFigre(uint8_t figureIndex)
{
    selectedFigure = figureIndex;
}

bool Player::hasFigureOnPosition(StripPosition position)
{
    for (uint8_t i = 0; i < NUMBER_OF_FIGURES; i++)
    {
        if (figures[i] == position)
        {
            return true;
        }
    }

    return false;
}

bool Player::allFiguresInHouse()
{
    for (uint8_t i = 0; i < NUMBER_OF_FIGURES; i++)
    {
        if (figures[i].strip != StripE::HOUSE)
        {
            return false;
        }
    }

    return true;
}

bool Player::didFigurePassedZeroMark(uint8_t figureIndex){
    return figuresPassZeroMark[figureIndex];
}

void Player::setFigurePassedZeroMark(uint8_t figureIndex, bool pass){
    figuresPassZeroMark[figureIndex] = pass;
}