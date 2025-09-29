#include "Figure.h"
/*
Figure::Figure() = default;

void Figure::init(Color *color, House *house, uint8_t index)
{
    this->color = color;
    this->house = house;

    position.component = component_house;
    position.index = index;

    next_position.component = component_none;

    figures[figure_number] = this;
    figure_number++;

    update_color();
}

void Figure::move()
{
    position = next_position;
    next_position.component = component_none;

    update_color();
}

bool Figure::can_move()
{
    switch (position.component)
    {
    case component_house:
        Serial.println((uint16_t)&house);
        next_position.component = component_path;
        next_position.index = house->exit_index;
        if (Dice::number == 6 && figure_on_index(next_position)->house != house)
        {
            Animator::start_house_exit(position, next_position, color, house);
            return true;
        }
        return false;
    case component_path:
        next_position.component = component_path;
        next_position.index = position.index + Dice::number;
        Animator::start_path(position, color);
        return true;
    case component_safe_house:
        return false;
    default:
        return false;
    }
}

void Figure::update_color()
{
    color->set_val(255);

    switch (position.component)
    {
    case component_house:
        house->turn_on(position.index, *color);
        break;
    case component_path:
        Path::turn_on(position.index, *color);
        break;
    case component_safe_house:
        break;
    default:
        break;
    }
}

void Figure::disable()
{
    if (position.component == component_house)
        house->turn_off(position.index);
}

Figure *Figure::figure_on_index(Position position)
{
    for (int i = 0; i < 16; i++)
    {
        if (figures[i]->position.component == position.component && figures[i]->position.index == position.index)
            return figures[i];
    }

    return NULL;
}
*/