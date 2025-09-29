#include "Button.h"

volatile bool Button::canUpdate = false;

void Button::init(CallbackFunction callback)
{
    this->callback = callback;
    PCF.begin();

    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), isr, FALLING);
}

void Button::isr()
{
    canUpdate = true;
}

void Button::buzzerTone()
{
    tone(BUZZER, 500);
    delay(50);
    noTone(BUZZER);
}

void Button::update()
{
    if (canUpdate)
    {
        canUpdate = false;
        uint16_t temp = PCF.read16();
        buttonsBitMask -= temp;

        if ((buttonsBitMask <= 4096) && (availableBitMask & buttonsBitMask))
        {
            buzzerTone();
            callback(buttonsBitMask);
        }

        buttonsBitMask = temp;
    }
}

void Button::enablePlayerButtons(uint8_t player)
{
    availableBitMask = 7 << 3 * player;
}

void Button::disablePlayerButtons(uint8_t player)
{
    availableBitMask &= ~(7 << (3 * player));
}

void Button::enablePlayersButtons()
{
    availableBitMask = 4095;
}

void Button::enableDice()
{
    availableBitMask &= ~(1 << 7);
}

void Button::disable()
{
    availableBitMask = 0;
}