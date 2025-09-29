/*#include "House.h"

House::House() = default;

void House::init(uint8_t playerNumber)
{
    for (uint8_t i = 0; i < 4; i++)
        pixels[i] = playerNumber * 4 + i;

    exit_index = playerNumber * 13 + 1;
}

void House::turn_on(uint8_t index, Color color)
{
    Elements::house_strip.set_pixel_color(pixels[index], color);
    Elements::house_strip.show();
}

void House::turn_off(uint8_t index)
{
    Elements::house_strip.turn_off(pixels[index]);
    Elements::house_strip.show();
}*/