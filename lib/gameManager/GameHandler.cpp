#include "GameHandler.h"

GameHandler &gameHandler = GameHandler::getInstance();

void buttonCallback(uint16_t button)
{
    uint8_t player = 0;
    uint16_t temp = button;

    while (temp >>= 3)
    {
        ++player;
    }

    Serial.print("INFO: player ");
    Serial.println(player);

    switch (button >> player * 3)
    {
    case 1:
        gameHandler.playerActionSubmit(player);
        break;
    case 2:
        gameHandler.playerActionLeft(player);
        break;
    case 4:
        gameHandler.playerActionRight(player);
        break;
    default:
        gameHandler.diceAction();
        break;
    }
}

void GameHandler::init()
{
    handler.init();
    button.init(&buttonCallback);

    Color pathColor;
    pathColor.setSat(PATH_SAT);
    pathColor.setVal(PATH_VAL);

    handler.setPath(pathColor);

    for (uint8_t i = 0; i < 4; i++)
    {
        playerColors[i] = i;
        Color playerColor(availableColors[i].getHue());
        setPlayerColor(i, playerColor);
    }

    button.enablePlayersButtons();

    playerNumber = 0;
}

void GameHandler::setPlayerColor(uint8_t player, Color color)
{
    handler.setHouse(player, color);
    // handler.removeButtonAnimation(player);
    handler.setButtonAnimation(player, color);

    color.setSat(SAFE_HOUSE_SAT);
    handler.setSafeHouse(player, color);

    handler.setPath(color, player);
}

void GameHandler::changeColorLeft(uint8_t player)
{
    int8_t playerColorIndex = playerColors[player];
    bool colorAvailable;

    do
    {
        if (++playerColorIndex >= 6)
        {
            playerColorIndex = 0;
        }

        colorAvailable = false;
        for (uint8_t i = 0; i < 4; i++)
        {
            if (playerColors[i] == playerColorIndex)
            {
                colorAvailable = true;
                break;
            }
        }
    } while (colorAvailable);

    playerColors[player] = playerColorIndex;
    Color playerColor(availableColors[playerColorIndex].getHue());

    setPlayerColor(player, playerColor);
}

void GameHandler::changeColorRight(uint8_t player)
{
    int8_t playerColorIndex = playerColors[player];
    bool colorAvailable;

    do
    {
        if (--playerColorIndex < 0)
        {
            playerColorIndex = 5;
        }

        colorAvailable = false;
        for (uint8_t i = 0; i < 4; i++)
        {
            if (playerColors[i] == playerColorIndex)
            {
                colorAvailable = true;
                break;
            }
        }
    } while (colorAvailable);

    playerColors[player] = playerColorIndex;
    Color playerColor(availableColors[playerColorIndex].getHue());

    setPlayerColor(player, playerColor);
}

void GameHandler::playerActionLeft(uint8_t player)
{
    changeColorLeft(player);
}

void GameHandler::playerActionRight(uint8_t player)
{
    changeColorRight(player);
}

void GameHandler::playerActionSubmit(uint8_t player)
{
    button.disablePlayerButtons(player);
    handler.removeButtonAnimation(player);
    playerNumber++;

    if (playerNumber == 2)
    {
        handler.setDiceAnimation(playerColors[player]);
        button.enableDice();
    }
}

void GameHandler::diceAction()
{
}
