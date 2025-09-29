/*#include "SafeHouse.h"

void SafeHouse::init(uint8_t playerNumber, Color *color)
{
    this->color = color;

    if(playerNumber==0){
        for (uint8_t i = 0; i < 4; i++)
            pixels[i] = 12 + i;
    }else{
        for (uint8_t i = 0; i < 4; i++)
            pixels[i] = (playerNumber-1) * 4 + i;
    }
}

void SafeHouse::turn_on()
{
    Color c;

    c.set_hue(color->get_hue());
    c.set_sat(color->get_sat());
    c.set_val(color->get_val()-100);

    for (int i = 0; i < 4; i++)
        Elements::safe_house_strip.set_pixel_color(pixels[i], c);

    Elements::safe_house_strip.show();
}

void SafeHouse::turn_off()
{
    for (int i = 0; i < 4; i++)
        Elements::safe_house_strip.turn_off(pixels[i]);

    Elements::safe_house_strip.show();
}
*/