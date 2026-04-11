/**
 * @file GameHandler.cpp
 * @brief Implementation of GameHandler - main game logic and state machine
 *
 * Handles player turns, dice rolls, move validation, figure capturing,
 * animation coordination, and state transitions for the LUDO game.
 */
#include "GameHandler.h"

void GameHandler::buttonCallback(uint16_t button)
{
    GameHandler &instance = GameHandler::getInstance();
    uint8_t player = 0;
    uint16_t temp = button;

    // Determine which player pressed a button by shifting 3 bits at a time
    // (each player has 3 buttons: submit, left, right)
    while (temp >>= 3)
    {
        ++player;
    }

    // Bit 12 (4096) = dice button, mapped to player index >= 4
    if (player >= NUMBER_OF_PLAYERS)
    {
        instance.diceAction();
        return;
    }

    // Extract the 3-bit button group for this player:
    // bit 0 = submit, bit 1 = left, bit 2 = right
    switch (button >> player * 3)
    {
    case 1:
        instance.playerActionSubmit(player);
        break;
    case 2:
        instance.playerActionLeft(player);
        break;
    case 4:
        instance.playerActionRight(player);
        break;
    default:
        break;
    }
}

void GameHandler::animationCallback()
{
    GameHandler::getInstance().nextPlayer();
}

void GameHandler::init()
{
    // Initialize hardware
    neopixelHandler.init(&animationCallback);
    button.init(&buttonCallback);

    // Set hardware initial state
    Color pathColor;
    pathColor.setSat(PATH_SAT);
    pathColor.setVal(PATH_VAL);

    neopixelHandler.setPath(pathColor);

    // Set players initial state
    for (uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        players[i].setColorIndex(i);
        setPlayerColor(i, players[i].getPlayerColor());
    }

    playerOnTurn = 0;

    button.enablePlayersButtons();

    gameState = GameState::COLOR_SELECTION;
}

uint8_t GameHandler::getNumberOfActivePlayers()
{
    uint8_t numberOfActivePlayers = 0;

    for (uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        if (players[i].isActive())
        {
            numberOfActivePlayers++;
        }
    }

    return numberOfActivePlayers;
}

void GameHandler::setPlayerColor(uint8_t player, Color color)
{
    neopixelHandler.setHouse(player, color);
    neopixelHandler.removeButtonAnimation(player);
    neopixelHandler.setButtonAnimation(player, color);

    color.setSat(SAFE_HOUSE_SAT);
    neopixelHandler.setSafeHouse(player, color);
    neopixelHandler.setHouseExit(player, color);
}

void GameHandler::changeColorLeft(uint8_t player)
{
    int8_t playerColorIndex = players[player].getPlayerColorIndex();
    bool colorAvailable;

    // Cycle forward through colors, skipping any already taken by other players
    do
    {
        if (++playerColorIndex >= NUMBER_OF_AVAILABLE_COLORS)
        {
            playerColorIndex = 0;
        }

        colorAvailable = false;
        for (uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
        {
            if (players[i].getPlayerColorIndex() == playerColorIndex)
            {
                colorAvailable = true;
                break;
            }
        }
    } while (colorAvailable);

    players[player].setColorIndex(playerColorIndex);
    setPlayerColor(player, players[player].getPlayerColor());
}

void GameHandler::changeColorRight(uint8_t player)
{
    int8_t playerColorIndex = players[player].getPlayerColorIndex();
    bool colorAvailable;

    // Cycle backward through colors, skipping any already taken by other players
    do
    {
        if (--playerColorIndex < 0)
        {
            playerColorIndex = NUMBER_OF_AVAILABLE_COLORS - 1;
        }

        colorAvailable = false;
        for (uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
        {
            if (players[i].getPlayerColorIndex() == playerColorIndex)
            {
                colorAvailable = true;
                break;
            }
        }
    } while (colorAvailable);

    players[player].setColorIndex(playerColorIndex);
    setPlayerColor(player, players[player].getPlayerColor());
}

void GameHandler::changeFigureLeft()
{
    uint8_t selectedFigure = players[playerOnTurn].getSelectedFigureIndex();

    for (uint8_t i = 0; i < NUMBER_OF_FIGURES; i++)
    {
        if (selectedFigure == 0)
        {
            selectedFigure = NUMBER_OF_FIGURES - 1;
        }
        else
        {
            selectedFigure--;
        }

        if (canFigureMove(selectedFigure))
        {
            players[playerOnTurn].setSelectedFigure(selectedFigure);
            setMoveAnimation();
            return;
        }
    }
}

void GameHandler::changeFigureRight()
{
    uint8_t selectedFigure = players[playerOnTurn].getSelectedFigureIndex();

    for (uint8_t i = 0; i < NUMBER_OF_FIGURES; i++)
    {
        selectedFigure++;
        if (selectedFigure >= NUMBER_OF_FIGURES)
        {
            selectedFigure = 0;
        }

        if (canFigureMove(selectedFigure))
        {
            players[playerOnTurn].setSelectedFigure(selectedFigure);
            setMoveAnimation();
            return;
        }
    }
}

void GameHandler::playerActionLeft(uint8_t player)
{
    switch (gameState)
    {
    case GameState::COLOR_SELECTION:
        changeColorLeft(player);
        break;
    case GameState::GAME:
        neopixelHandler.removeMoveAnimation();
        changeFigureLeft();
        break;
    default:
        break;
    }
}

void GameHandler::playerActionRight(uint8_t player)
{
    switch (gameState)
    {
    case GameState::COLOR_SELECTION:
        changeColorRight(player);
        break;
    case GameState::GAME:
        neopixelHandler.removeMoveAnimation();
        changeFigureRight();
        break;
    default:
        break;
    }
}

void GameHandler::playerActionSubmit(uint8_t player)
{
    switch (gameState)
    {
    case GameState::COLOR_SELECTION:
    {
        button.disablePlayerButtons(player);
        neopixelHandler.removeButtonAnimation(player);
        players[player].setActive();

        uint8_t numOfActivePlayers = getNumberOfActivePlayers();

        if (numOfActivePlayers == 4)
        {
            // Start game if all players are avtive
            startGame();
        }
        else if (numOfActivePlayers >= 2)
        {
            // Game can start with atleast two players
            // Dice button will start game
            neopixelHandler.removeDiceAnimation();
            neopixelHandler.setDiceAnimation(players[player].getPlayerColor());
            button.enableDice();
        }
        break;
    }

    case GameState::GAME:
    {
        // Check if an opponent's figure occupies the target position (capture rule)
        uint8_t playerIndex;
        if (playerFigureOnPosition(moveEndPosition, &playerIndex))
        {
            // Find figure on this exact position
            for (uint8_t i = 0; i < NUMBER_OF_FIGURES; i++)
            {
                if (players[playerIndex].figures[i] == moveEndPosition)
                {
                    // Send captured figure back to its house
                    players[playerIndex].figures[i].index = i;
                    players[playerIndex].figures[i].strip = StripE::HOUSE;

                    // Update LED to show figure back in house
                    StripPosition figurePosition = players[playerIndex].figures[i];
                    figurePosition.index += playerIndex * NUMBER_OF_FIGURES;
                    neopixelHandler.setPixelColor(figurePosition, players[playerIndex].getPlayerColor());

                    break;
                }
            }
        }

        // Update current player's figure to the new position
        players[playerOnTurn].figures[players[playerOnTurn].getSelectedFigureIndex()].strip = moveEndPosition.strip;
        players[playerOnTurn].figures[players[playerOnTurn].getSelectedFigureIndex()].index = moveEndPosition.index;

        neopixelHandler.endMoveAnimation();

        if (diceNumber == 6)
        {
            // Rolling 6 grants another turn for the same player
            // Disable buttons from player
            button.disablePlayerButtons(playerOnTurn);
            neopixelHandler.removeButtonAnimation(playerOnTurn);

            // Set initial dice state for new player
            neopixelHandler.removeDiceAnimation();
            neopixelHandler.setDiceAnimation(players[playerOnTurn].getPlayerColor());
            button.enableDice();

            // Set game state so that next dice click will roll the dice
            gameState = GameState::DICE_ROLL;
        }
        else
        {
            nextPlayer();
        }
        break;

        // TODO: Fully implement animation
        // stopMoveAnimation();
        // gameState = GameState::WAIT_FOR_CALLBACK;
    }
    case GameState::DICE_ROLL:
        // Rule: if all figures are in house, player gets up to 3 total rolls
        // to try for a 6 (initial roll + 2 extra attempts)
        if (players[playerOnTurn].allFiguresInHouse() && numberOfPlayerRolls < 2)
        {
            numberOfPlayerRolls++;

            // Disable submit button
            button.disablePlayerButtons(playerOnTurn);
            neopixelHandler.removeButtonAnimation(playerOnTurn);

            // Set initial dice state for new player
            neopixelHandler.removeDiceAnimation();
            neopixelHandler.setDiceAnimation(players[playerOnTurn].getPlayerColor());
            button.enableDice();
        }
        else
        {
            nextPlayer();
        }
        break;

    default:
        break;
    }
}

void GameHandler::diceAction()
{
    switch (gameState)
    {
    case GameState::COLOR_SELECTION:
        startGame();
        break;
    case GameState::DICE_ROLL:
        rollDice();
        break;
    default:
        break;
    }
}

void GameHandler::startGame()
{
    neopixelHandler.removeDiceAnimation();

    // Disable non-active players
    for (uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        button.disablePlayerButtons(i);

        if (!players[i].isActive())
        {
            Color blackColor;
            blackColor.setVal(0);

            neopixelHandler.removeButtonAnimation(i);
            neopixelHandler.setHouse(i, blackColor);
            neopixelHandler.setSafeHouse(i, blackColor);

            // Clear safe house entrance
            Color pathColor;
            pathColor.setSat(PATH_SAT);
            pathColor.setVal(PATH_VAL);

            neopixelHandler.setHouseExit(i, pathColor);
        }
    }

    nextPlayer();
}

void GameHandler::nextPlayer()
{
    numberOfPlayerRolls = 0;

    uint8_t previousPlayer = playerOnTurn;

    do
    {
        if (++playerOnTurn >= NUMBER_OF_PLAYERS)
        {
            playerOnTurn = 0;
        }

        if (players[playerOnTurn].isActive())
        {
            break;
        }
    } while (true);

    // Disable buttons from previous player
    button.disablePlayerButtons(previousPlayer);
    neopixelHandler.removeButtonAnimation(previousPlayer);

    // Set initial dice state for new player
    neopixelHandler.removeDiceAnimation();
    neopixelHandler.setDiceAnimation(players[playerOnTurn].getPlayerColor());
    button.enableDice();

    // Set game state so that next dice click will roll the dice
    gameState = GameState::DICE_ROLL;
}

void GameHandler::rollDice()
{
    // Do dice roll animation
    diceNumber = random(1, 7);

    neopixelHandler.removeDiceAnimation();
    neopixelHandler.diceRollAnimation(playerOnTurn, players[playerOnTurn].getPlayerColor(), diceNumber);

    // Check if player can move any of its figures
    for (uint8_t i = 0; i < NUMBER_OF_FIGURES; i++)
    {
        if (canFigureMove(i))
        {
            players[playerOnTurn].setSelectedFigure(i);
            setMoveAnimation();
            gameState = GameState::GAME;

            // Enable player buttons
            neopixelHandler.setButtonAnimation(playerOnTurn, players[playerOnTurn].getPlayerColor());
            button.enablePlayerButtons(playerOnTurn);
            return;
        }
    }

    // No figures can move — enable only submit button to skip turn
    neopixelHandler.setSubmitAnimation(playerOnTurn, players[playerOnTurn].getPlayerColor());
    button.enableSubmitButtons(playerOnTurn);
    players[playerOnTurn].setSelectedFigure(-1);
}

void GameHandler::setMoveAnimation()
{
    AnimationInfo *movePixels = nullptr;
    uint8_t numberOfAnimations;

    //  Build animation sequence based on figure's current strip
    switch (players[playerOnTurn].getSelectedFigure().strip)
    {
    case StripE::HOUSE:
        // HOUSE -> PATH exit: 2-step animation (leave house + appear on path)
        numberOfAnimations = 2;
        movePixels = new AnimationInfo[numberOfAnimations];

        movePixels[0].position = players[playerOnTurn].getSelectedFigure();
        movePixels[0].position.index += playerOnTurn * NUMBER_OF_PLAYERS;

        movePixels[0].primary = players[playerOnTurn].getPlayerColor();
        movePixels[0].normal = players[playerOnTurn].getPlayerColor();
        movePixels[0].secondary = Color();
        movePixels[0].secondary.setVal(0); // Black color

        movePixels[1].position.index = playerOnTurn * PATH_QUATER + 1;
        movePixels[1].position.strip = StripE::PATH;

        movePixels[1].primary = players[playerOnTurn].getPlayerColor();
        movePixels[1].primary.setVal(UPDATE_FADE_MIN);
        movePixels[1].secondary = players[playerOnTurn].getPlayerColor();

        uint8_t playerFigure;
        if (playerFigureOnPosition(movePixels[1].position, &playerFigure))
        {
            movePixels[1].normal = players[playerFigure].getPlayerColor(); // TODO: test
        }
        else
        {
            Color playerOnTurnHouseExitColor = players[playerOnTurn].getPlayerColor();
            playerOnTurnHouseExitColor.setSat(SAFE_HOUSE_SAT);
            movePixels[1].normal = playerOnTurnHouseExitColor;
        }

        moveEndPosition = movePixels[1].position;

        break;

    case StripE::PATH:
    case StripE::S_HOUSE:
    {
        // PATH/S_HOUSE move: animate each step along the path (1 origin + diceNumber steps)
        numberOfAnimations = 1 + diceNumber;
        movePixels = new AnimationInfo[numberOfAnimations];
        movePixels[0].position = players[playerOnTurn].getSelectedFigure();

        movePixels[0].primary = players[playerOnTurn].getPlayerColor();
        movePixels[0].primary.setVal(UPDATE_FADE_MIN);

        movePixels[0].normal = players[playerOnTurn].getPlayerColor();

        if (movePixels[0].position.strip == StripE::PATH)
        {
            // Check if player is on house entrance
            if ((movePixels[0].position.index - HOUSE_EXIT) % PATH_QUATER == 0)
            {
                uint8_t playerHouse = (movePixels[0].position.index - HOUSE_EXIT) / PATH_QUATER;

                // Check if player is active
                if (players[playerHouse].isActive())
                {
                    Color playerSafeHouseColor = players[playerHouse].getPlayerColor();
                    playerSafeHouseColor.setSat(SAFE_HOUSE_SAT);
                    movePixels[0].secondary = playerSafeHouseColor;
                }
                else
                {
                    Color pathColor;
                    pathColor.setSat(PATH_SAT);
                    pathColor.setVal(PATH_VAL);
                    movePixels[0].secondary = pathColor;
                }
            }
            else
            {
                Color pathColor;
                pathColor.setSat(PATH_SAT);
                pathColor.setVal(PATH_VAL);
                movePixels[0].secondary = pathColor;
            }
        }
        else
        {
            // Safe house case
            movePixels[0].position.index += playerOnTurn * NUMBER_OF_PLAYERS;
            movePixels[0].secondary = players[playerOnTurn].getPlayerColor();
            movePixels[0].secondary.setSat(SAFE_HOUSE_SAT);
        }

        // Gradually increase brightness for each step along the path
        uint8_t fadeStep = (COLOR_MAX_VALUE - UPDATE_FADE_MIN) / diceNumber;

        for (uint8_t i = 1; i <= diceNumber; i++)
        {
            movePixels[i].primary = players[playerOnTurn].getPlayerColor();
            movePixels[i].primary.setVal(UPDATE_FADE_MIN + fadeStep * i);

            movePixels[i].position = players[playerOnTurn].getSelectedFigure();
            movePixels[i].position.index += i;

            // Wrap around if position exceeds path length
            if (movePixels[i].position.index >= PATH_COUNT)
            {
                movePixels[i].position.index -= PATH_COUNT;
                players[playerOnTurn].setFigurePassedZeroMark(players[playerOnTurn].getSelectedFigureIndex(), true);
            }

            // Transition from PATH to S_HOUSE if figure has completed a full lap
            uint8_t playerSafeHouseEntrance = playerOnTurn * PATH_QUATER;

            if (movePixels[i].position.strip == StripE::PATH &&
                players[playerOnTurn].didFigurePassedZeroMark(players[playerOnTurn].getSelectedFigureIndex()) &&
                movePixels[i].position.index > playerSafeHouseEntrance)
            {
                movePixels[i].position.strip = StripE::S_HOUSE;
                movePixels[i].position.index = movePixels[i].position.index - playerSafeHouseEntrance - 1;
            }

            if (movePixels[i].position.strip == StripE::PATH)
            {
                uint8_t playerFigure;
                if (playerFigureOnPosition(movePixels[i].position, &playerFigure))
                {
                    movePixels[i].normal = players[playerFigure].getPlayerColor();
                    movePixels[i].secondary = players[playerFigure].getPlayerColor();
                }

                // House entrance of active player
                else if ((movePixels[i].position.index - HOUSE_EXIT) % PATH_QUATER == 0)
                {
                    uint8_t playerHouse = (movePixels[i].position.index - HOUSE_EXIT) / PATH_QUATER;

                    if (players[playerHouse].isActive())
                    {
                        Color playerColor = players[playerHouse].getPlayerColor();
                        playerColor.setSat(SAFE_HOUSE_SAT);
                        movePixels[i].normal = playerColor;
                        movePixels[i].secondary = playerColor;
                    }
                    else
                    {
                        Color pathColor;
                        pathColor.setSat(PATH_SAT);
                        pathColor.setVal(PATH_VAL);
                        movePixels[i].normal = pathColor;
                        movePixels[i].secondary = pathColor;
                    }
                }
                else
                {
                    Color pathColor;
                    pathColor.setSat(PATH_SAT);
                    pathColor.setVal(PATH_VAL);
                    movePixels[i].normal = pathColor;
                    movePixels[i].secondary = pathColor;
                }
            }
            else
            {
                // SafeHouse case
                Color playerOnTurnHouseExitColor = players[playerOnTurn].getPlayerColor();
                playerOnTurnHouseExitColor.setSat(SAFE_HOUSE_SAT);
                movePixels[i].normal = playerOnTurnHouseExitColor;
                movePixels[i].secondary = playerOnTurnHouseExitColor;
                movePixels[i].position.index += playerOnTurn * NUMBER_OF_PLAYERS;
            }

            if (i == diceNumber)
            {
                movePixels[i].secondary = players[playerOnTurn].getPlayerColor();
                moveEndPosition = movePixels[i].position;
            }
        }
        break;
    }
    default:
        break;
    }

    // Enable move animation
    neopixelHandler.setMoveAnimation(movePixels, numberOfAnimations);
    delete[] movePixels;
}

bool GameHandler::canFigureMove(uint8_t selectedFigure)
{
    StripPosition position = players[playerOnTurn].figures[selectedFigure];

    switch (position.strip)
    {
    case StripE::HOUSE:
    {
        // Rule: figure can only leave house with a roll of 6,
        // and the exit position must not be occupied by own figure
        StripPosition endPosition;

        endPosition.strip = StripE::PATH;
        endPosition.index = playerOnTurn * PATH_QUATER + HOUSE_EXIT;

        if (diceNumber == 6 && !players[playerOnTurn].hasFigureOnPosition(endPosition))
        {
            return true;
        }
        break;
    }
    case StripE::S_HOUSE:
    {
        // Rule: cannot overshoot the safe house end
        if (position.index + diceNumber >= NUMBER_OF_FIGURES)

        {
            return false;
        }

        // Rule: cannot jump over own figures inside safe house
        for (uint8_t i = 0; i < diceNumber; i++)
        {
            StripPosition nextPosition = StripPosition(StripE::S_HOUSE, position.index + i + 1);

            if (players[playerOnTurn].hasFigureOnPosition(nextPosition))
            {
                return false;
            }
        }

        return true;
    }
    case StripE::PATH:
    {
        StripPosition endPosition = position;
        endPosition.index += diceNumber;

        uint8_t playerSafeHouseEntrance = playerOnTurn * PATH_QUATER;

        // Rule: figure must have completed a full lap (passed zero mark)
        // before it can enter the safe house
        if (endPosition.index > playerSafeHouseEntrance && players[playerOnTurn].didFigurePassedZeroMark(selectedFigure))
        {
            uint8_t numberOfSteps = endPosition.index - playerSafeHouseEntrance;

            if (numberOfSteps > NUMBER_OF_FIGURES)
            {
                return false;
            }

            // Rule: cannot jump over own figures when entering safe house
            for (uint8_t i = 0; i < numberOfSteps; i++)
            {
                StripPosition nextPosition = StripPosition(StripE::S_HOUSE, i);

                if (players[playerOnTurn].hasFigureOnPosition(nextPosition))
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            // Check if end position overflows path length (wrap around)
            if (endPosition.index >= PATH_COUNT)
            {
                endPosition.index -= PATH_COUNT;
            }

            // Rule: cannot land on own figure
            for (uint8_t figure = 0; figure < NUMBER_OF_FIGURES; figure++)
            {
                if (players[playerOnTurn].figures[figure] == endPosition)
                {
                    return false;
                }
            }
        }
        return true;
    }
    default:
        break;
    }

    return false;
}

bool GameHandler::playerFigureOnPosition(StripPosition position, uint8_t *playerIndex)
{
    for (uint8_t player = 0; player < NUMBER_OF_PLAYERS; player++)
    {
        for (uint8_t figure = 0; figure < NUMBER_OF_FIGURES; figure++)
        {
            if (players[player].figures[figure] == position)
            {
                *playerIndex = player;
                return true;
            }
        }
    }

    return false;
}