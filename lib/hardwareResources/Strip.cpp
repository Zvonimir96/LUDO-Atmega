#include "Strip.h"

void Strip::init()
{
    strips[static_cast<int>(StripE::HOUSE)] = new Adafruit_NeoPixel(HOUSE_COUNT, HOUSE_PIN, NEO_GRB + NEO_KHZ800);
    strips[static_cast<int>(StripE::S_HOUSE)] = new Adafruit_NeoPixel(SAFE_HOUSE_COUNT, SAFE_HOUSE_PIN, NEO_GRB + NEO_KHZ800);
    strips[static_cast<int>(StripE::PATH)] = new Adafruit_NeoPixel(PATH_COUNT, PATH_PIN, NEO_GRB + NEO_KHZ800);
    strips[static_cast<int>(StripE::DICE)] = new Adafruit_NeoPixel(DICE_COUNT, DICE_PIN, NEO_GRB + NEO_KHZ800);
    strips[static_cast<int>(StripE::BUTTONS)] = new Adafruit_NeoPixel(TOUCH_COUNT, TOUCHPAD_PIN, NEO_GRB + NEO_KHZ800);

    // Initialize all strips
    for (int i = 0; i < STRIPS_COUNT; i++)
    {
        strips[i]->setBrightness(BRIGHTNESS);
        strips[i]->begin();
        strips[i]->show();
    }
}

void Strip::setColor(const StripPosition stripPosition, Color color, bool update = true)
{
    strips[static_cast<int>(stripPosition.strip)]
        ->setPixelColor(stripPosition.index,
                        strips[static_cast<int>(stripPosition.strip)]
                            ->gamma32(strips[static_cast<int>(stripPosition.strip)]->ColorHSV(color.getHue(), color.getSat(), color.getVal())));
    if (update)
    {
        strips[static_cast<int>(stripPosition.strip)]->show();
    }
}

void Strip::setColor(const StripE strip, const uint8_t index, Color color, bool update = true)
{
    strips[static_cast<int>(strip)]
        ->setPixelColor(index, strips[static_cast<int>(strip)]
                                   ->gamma32(strips[static_cast<int>(strip)]->ColorHSV(color.getHue(), color.getSat(), color.getVal())));
    if (update)
    {
        strips[static_cast<int>(strip)]->show();
    }
}

void Strip::setColor(const StripE strip, uint8_t indexs[], Color colors[], uint8_t size, bool update = true)
{
    for (uint32_t i = 0; i < size; i++)
    {
        strips[static_cast<int>(strip)]
            ->setPixelColor(indexs[i], strips[static_cast<int>(strip)]
                                           ->gamma32(strips[static_cast<int>(strip)]->ColorHSV(colors[i].getHue(), colors[i].getSat(), colors[i].getVal())));
    }
    if (update)
    {
        strips[static_cast<int>(strip)]->show();
    }
}

void Strip::clear(const StripE strip)
{
    strips[static_cast<int>(strip)]->clear();
}

void Strip::show()
{
    for (uint32_t i = 0; i < STRIPS_COUNT; i++)
    {
        strips[i]->show();
    }
}

void Strip::show(const StripE strip)
{
    strips[static_cast<int>(strip)]->show();
}