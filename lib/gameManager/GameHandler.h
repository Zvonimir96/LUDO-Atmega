#pragma once

#include "utils.h"
#include "neopixelHandler.h"
#include "hardwareResources.h"
#include "Player.h"

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

    void changeColorLeft(uint8_t player);
    void changeColorRight(uint8_t player);

private:
    // Prevent instantiation
    GameHandler() {}
    // Prevent copying
    GameHandler(const GameHandler &) = delete;
    void operator=(const GameHandler &) = delete;

    Color availableColors[6] = {Color(0), Color(10000), Color(20000), Color(30000), Color(35000), Color(40000)};
    uint8_t playerColors[4];
    Handler &handler = Handler::getInstance();
    Button &button = Button::getInstance();

    void setPlayerColor(uint8_t player, Color color);
    // Player *players;
    uint8_t playerNumber;
};