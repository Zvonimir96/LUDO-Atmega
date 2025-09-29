#include "Controller.h"
/*
void Controller::init()
{
    PCF.begin();

    pinMode(BUZZER, OUTPUT);

    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), isr, FALLING);

    for (int i = 0; i < 4; i++)
        players[i].init(i);
}

void buzzer_tone()
{
    tone(BUZZER, 500);
    delay(50);
    noTone(BUZZER);
}

void Controller::isr()
{
    can_update = true;
}

void Controller::change_player_color_right(int player_number)
{
    players[player_number].change_color_number_right();

    for (int i = 0; i < 4; i++)
    {
        if (players[player_number].get_color_number() == players[i].get_color_number() && player_number != i)
        {
            change_player_color_right(player_number);
            break;
        }
    }
}

void Controller::change_player_color_left(int player_number)
{
    players[player_number].change_color_number_left();

    for (int i = 0; i < 4; i++)
    {
        if (players[player_number].get_color_number() == players[i].get_color_number() && player_number != i)
        {
            change_player_color_left(player_number);
            break;
        }
    }
}

void Controller::start_game()
{
    randomSeed(millis());
    buzzer_tone();

    for (uint8_t i = 0; i < 4; i++)
    {
        if (!players[i].playable)
            players[i].disable();

        else if (state == select_color_state)
        {
            state = static_cast<game_state>(i);

            Dice::color = players[i].get_color();
            Dice::turn_on();
            Dice::animation = true;
        }
    }
}

void Controller::next_player()
{
    uint8_t player_number = state;
    buzzer_tone();

    for (uint8_t i = 0; i < 4; i++)
    {
        player_number++;
        if (player_number >= 4)
            player_number = 0;

        if (players[player_number].playable)
            break;
    }

    state = static_cast<game_state>(player_number);

    // Dice::turn_off();
    Dice::color = players[player_number].get_color();
    Dice::animation = true;
    Dice::turn_on();
}

void Controller::select_color(int playerNumber)
{
    if (playeble_players() >= 1)
    {
        Dice::color = players[playerNumber].get_color();
        Dice::turn_on();
        Dice::animation = true;
    }

    players[playerNumber].playable = true;
    players[playerNumber].touch.turn_off();

    if (playeble_players() >= 4)
        start_game();
}

void Controller::player_left(int player_number)
{
    Serial.print("Player number: ");
    Serial.println(player_number);
    Serial.print("State: ");
    Serial.println(state);

    if (state == select_color_state && !players[player_number].playable)
    {
        change_player_color_left(player_number);
        players[player_number].set_figures_color();
        buzzer_tone();
    }
    else if (state == player_number && Dice::number != -1)
    {
        Animator::stop();
        players[player_number].next_figure_left();
        buzzer_tone();
    }
}

void Controller::player_right(int player_number)
{
    Serial.print("Player number: ");
    Serial.println(player_number);
    Serial.print("State: ");
    Serial.println(state);

    if (state == select_color_state && !players[player_number].playable)
    {
        change_player_color_right(player_number);
        players[player_number].set_figures_color();
        buzzer_tone();
    }
    else if (state == player_number && Dice::number != -1)
    {
        Animator::stop();
        players[player_number].next_figure_right();
        buzzer_tone();
    }
}

void Controller::player_submit(int player_number)
{
    Serial.print("Player number: ");
    Serial.println(player_number);
    Serial.print("State: ");
    Serial.println(state);

    if (state == select_color_state && !players[player_number].playable)
        select_color(player_number);

    else if ((state == player_number || players[player_number].selected_figure_index == -1) && player_number == state)
    {
        if (Dice::number != -1)
        {
            players[player_number].action();
            players[player_number].touch.turn_off();
            next_player();
            Dice::number = -1;
        }
    }
}

void Controller::dice()
{
    if (state == select_color_state)
    {
        if (playeble_players() >= 2)
            start_game();
    }
    else
    {
        if (Dice::number == -1)
        {
            Dice::animation = false;
            buzzer_tone();
            Dice::roll();
            players[state].touch.turn_on();
            players[state].select_figure();
        }
    }
}

uint8_t Controller::playeble_players()
{
    uint8_t playeble_players = 0;
    for (uint8_t i = 0; i < 4; i++)
        if (players[i].playable)
            playeble_players++;

    return playeble_players;
}

void Controller::update()
{
    if (can_update)
    {
        can_update = false;
        uint16_t temp = PCF.read16();
        buttons16 -= temp;

        Serial.print("Pritisnut gumb: ");
        Serial.println(buttons16);

        if (buttons16 > 0)
        {
            switch (buttons16)
            {
            case PLAYER1_LEFT:
                player_left(0);
                break;
            case PLAYER1_SUBMIT:
                player_submit(0);
                break;
            case PLAYER1_RIGHT:
                player_right(0);
                break;
            case PLAYER2_LEFT:
                player_left(1);
                break;
            case PLAYER2_SUBMIT:
                player_submit(1);
                break;
            case PLAYER2_RIGHT:
                player_right(1);
                break;
            case PLAYER3_LEFT:
                player_left(2);
                break;
            case PLAYER3_SUBMIT:
                player_submit(2);
                break;
            case PLAYER3_RIGHT:
                player_right(2);
                break;
            case PLAYER4_LEFT:
                player_left(3);
                break;
            case PLAYER4_SUBMIT:
                player_submit(3);
                break;
            case PLAYER4_RIGHT:
                player_right(3);
                break;
            case DICE_BUTTON:
                dice();
                break;
            }
        }

        buttons16 = temp;
    }
}*/