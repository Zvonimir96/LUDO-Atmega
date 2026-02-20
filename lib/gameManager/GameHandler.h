#pragma once

#include "utils.h"
#include "neopixelHandler.h"
#include "hardwareResources.h"
#include "AnimationInfo.h"
#include "Player.h"
#include "GameState.h"

class GameHandler
{
public:
    static GameHandler &getInstance()
    {
        static GameHandler instance;
        return instance;
    }

    void init();
    
    void playerActionLeft(uint8_t player);
    void playerActionRight(uint8_t player);
    void playerActionSubmit(uint8_t player);
    void diceAction();

    static void animationCallback();
    static void buttonCallback(uint16_t button);

private:
    // Prevent instantiation
    GameHandler() {}
    // Prevent copying
    GameHandler(const GameHandler &) = delete;
    void operator=(const GameHandler &) = delete;

    void changeColorLeft(uint8_t player);
    void changeColorRight(uint8_t player);
    void changeFigureLeft();
    void changeFigureRight();
    void setPlayerColor(uint8_t player, Color color);

    void startGame();
    void nextPlayer();
    void rollDice();

    void setMoveAnimation();

    bool playerFigureOnPosition(StripPosition position, uint8_t *playerIndex);

    bool canFigureMove(uint8_t selectedFigure);
    uint8_t getNumberOfActivePlayers();
    uint8_t diceNumber;

    Handler &neopixelHandler = Handler::getInstance();
    Button &button = Button::getInstance();

    StripPosition moveEndPosition;
    uint8_t playerOnTurn;
    uint8_t numberOfPlayerRolls;
    GameState gameState;

    Player players[NUMBER_OF_PLAYERS];
};