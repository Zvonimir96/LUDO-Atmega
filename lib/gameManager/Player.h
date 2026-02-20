#pragma once

#include "utils.h"

class Player
{
public:
    Player();

    void setColorIndex(uint8_t index);
    Color getPlayerColor();
    uint8_t getPlayerColorIndex();
    StripPosition getSelectedFigure();
    uint8_t getSelectedFigureIndex();
    uint8_t setSeletedFigre(uint8_t figureIndex);

    StripPosition figures[NUMBER_OF_FIGURES];    // TODO: private
    bool figuresPassZeroMark[NUMBER_OF_FIGURES]; // TODO: private

    void setActive();
    bool isActive();
    bool hasFigureOnPosition(StripPosition position);
    bool allFiguresInHouse();
    bool didFigurePassedZeroMark(uint8_t figureIndex);
    void setFigurePassedZeroMark(uint8_t figureIndex, bool pass);

private:
    static Color availableColors[NUMBER_OF_AVAILABLE_COLORS];
    uint8_t playerColorIndex;
    uint8_t selectedFigure;
    bool active;
};