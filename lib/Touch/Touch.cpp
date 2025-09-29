/*#include "Touch.h"

void Touch::init(uint8_t playerNumber, Color *color)
{
    this->color = color;
    for (uint8_t i = 0; i < 3; i++)
        pixels[i] = playerNumber * 3 + i;
}

void Touch::turn_on()
{
    for (int i = 0; i < 3; i++)
        Elements::touch_strip.set_pixel_color(pixels[i], *color);

    Elements::touch_strip.show();
}

void Touch::turn_off()
{
    for (int i = 0; i < 3; i++)
        Elements::touch_strip.turn_off(pixels[i]);

    Elements::touch_strip.show();
}*/
