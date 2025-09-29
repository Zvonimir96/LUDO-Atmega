#include "Player.h"
/*
Player::Player() = default;

void Player::init(uint8_t player_number)
{
    time_to_update = millis() + UPDATE_TIME_MS;
    playable = false;
    selected_figure_index = -1;
    color_number = player_number;
    this->player_number = player_number;
    color = available_colors[color_number];

    house.init(player_number);
    touch.init(player_number, &color);
    sHouse.init(player_number, &color);

    set_start_pat();

    touch.turn_on();
    sHouse.turn_on();

    for (uint8_t i = 0; i < 4; i++)
        figures[i].init(&color, &house, i);
}

void Player::set_start_pat()
{
    Color c;

    c.set_hue(color.get_hue());
    c.set_sat(color.get_sat());
    c.set_val(color.get_val() - 100);

    // Path::turn_on(player_number * 13 + 1, c);
}

void Player::change_color_number_right()
{
    color_number++;

    if (color_number >= COLORS)
        color_number = 0;

    color = available_colors[color_number];

    sHouse.turn_on();
    touch.turn_on();
    set_start_pat();

    Serial.print("Color number: ");
    Serial.println(color_number);
}

void Player::change_color_number_left()
{
    color_number--;

    if (color_number < 0)
        color_number = COLORS - 1;

    color = available_colors[color_number];

    sHouse.turn_on();
    touch.turn_on();
    set_start_pat();

    Serial.print("Color number: ");
    Serial.println(color_number);
}

void Player::set_figures_color()
{
    for (uint8_t i = 0; i < 4; i++)
        figures[i].update_color();
}

void Player::action()
{
    Animator::stop();
    figures[selected_figure_index].move();

    selected_figure_index = -1;
}

void Player::select_figure()
{
    for (int i = 0; i < 4; i++)
    {
        if (figures[i].can_move())
        {
            selected_figure_index = i;
            return;
        }
    }
}

void Player::next_figure_left()
{
    figures[selected_figure_index].update_color();

    for (int i = 0; i < 4; i++)
    {
        selected_figure_index--;

        if (selected_figure_index < 0)
            selected_figure_index = 3;

        if (figures[selected_figure_index].can_move())
        {
            break;
        }
    }
}

void Player::next_figure_right()
{
    figures[selected_figure_index].update_color();

    for (int i = 0; i < 4; i++)
    {
        selected_figure_index++;

        if (selected_figure_index >= 4)
            selected_figure_index = 0;

        if (figures[selected_figure_index].can_move())
        {
            break;
        }
    }
}

Color Player::get_color()
{
    return color;
}

uint8_t Player::get_color_number()
{
    return color_number;
}

void Player::disable()
{
    touch.turn_off();
    sHouse.turn_off();
    // Path::turn_off(player_number * 13 + 1);

    for (uint8_t i = 0; i < 4; i++)
        figures[i].disable();
}*/