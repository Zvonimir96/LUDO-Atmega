#include "AnimationManager.h"

void AnimationManager::add(PixelInfo *pixels, uint8_t numPixels, AnimationType type)
{
    Animation animation = Animation(pixels, numPixels, type);
    for (uint8_t i = 0; i < animationCount; ++i)
    {
        Serial.println("Test");

        if (animations[i] == animation)
        {
            animations[i] = animation;
            Serial.println("INFO: animation edited");
            break;
        }
    }

    animations[animationCount++] = animation;

    Serial.println("INFO: animation added");
}

void AnimationManager::remove(PixelInfo *pixels, uint8_t numPixels)
{
    Animation animation = Animation(pixels, numPixels, AnimationType::GLOBAL_FADE);
    for (uint8_t i = 0; i < animationCount; ++i)
    {
        if (animations[i] == animation)
        {
            for (uint8_t j = i; j < animationCount - 1; ++j)
            {
                animations[j] = animations[j - 1];
            }

            --animationCount;
            Serial.println("INFO: animation removed");

            break;
        }
    }
}

void AnimationManager::update()
{
    if (animationCount > 0 && updateTime <= millis())
    {
        for (uint8_t i = 0; i < animationCount; ++i)
        {
            animations[i].update();
        }
        strip.show();
        updateTime = millis() + UPDATE_TIME_MS;
    }
}