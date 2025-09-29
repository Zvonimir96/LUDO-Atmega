/*#include "Dice.h"

void Dice::update()
{
    if (animation && time_to_update <= millis())
    {
        Dice::color.fade();
        Elements::dice_strip.fill(Dice::color);

        time_to_update = millis() + UPDATE_TIME_MS;
    }
}

void Dice::roll()
{
    color.set_val(255);
    number = random(1, 7);
    Serial.println(number);

    set_number();

    // Animacija bacanje kockice je zakomentirana zbog rada na kodu

    int sleep = ANIMATION_MIN_DELAY;
    for(int i=0; i<ANIMATION_ITERATIONS; i++){
        number++;
        if(number > 6)
            number = 1;

        set_number();
        delay(sleep);

        sleep += ANIMATION_DELAY_INKREMENT;
    }
}

uint8_t Dice::apply_rotation(uint8_t pixel)
{
    pixel += 2 * Dice::rotation;
    pixel = pixel % 8;

    return pixel;
}

void Dice::set_number()
{
    Elements::dice_strip.clear();

    switch (number)
    {
    case 1:
        Elements::dice_strip.set_pixel_color(8, Dice::color);
        break;
    case 2:
        Elements::dice_strip.set_pixel_color(apply_rotation(2), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(6), Dice::color);
        break;
    case 3:
        Elements::dice_strip.set_pixel_color(apply_rotation(2), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(6), Dice::color);
        Elements::dice_strip.set_pixel_color(8, Dice::color);
        break;
    case 4:
        Elements::dice_strip.set_pixel_color(apply_rotation(0), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(2), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(4), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(6), Dice::color);
        break;
    case 5:
        Elements::dice_strip.set_pixel_color(apply_rotation(0), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(2), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(4), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(6), Dice::color);
        Elements::dice_strip.set_pixel_color(8, Dice::color);
        break;
    case 6:
        Elements::dice_strip.set_pixel_color(apply_rotation(0), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(1), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(2), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(4), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(5), Dice::color);
        Elements::dice_strip.set_pixel_color(apply_rotation(6), Dice::color);
        break;
    }

    Elements::dice_strip.show();
}

void Dice::turn_on()
{
    Elements::dice_strip.fill(color);
}

void Dice::turn_off()
{
    Elements::dice_strip.clear();
}*/