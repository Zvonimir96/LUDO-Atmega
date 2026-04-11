/**
 * @file AnimationManager.cpp
 * @brief Implementation of AnimationManager LED animation coordinator
 */
#include "AnimationManager.h"

void AnimationManager::init(AnimatorCallback callback)
{
    this->callback = callback;
}

void AnimationManager::add(AnimationInfo *pixels, uint8_t numPixels, AnimationType type)
{
    for (uint8_t i = 0; i < numPixels; ++i)
    {
        this->pixels[animationCount + i] = pixels[i];
        pixelsAnimation[animationCount + i] = type;
    }

    animationCount += numPixels;
}

void AnimationManager::remove(AnimationInfo *animations, uint8_t numberOfAnimations, AnimationType type)
{
    for (uint8_t i = 0; i < animationCount; i++)
    {
        for (uint8_t j = 0; j < numberOfAnimations; j++)
        {
            if (pixels[i] == animations[j])
            {
                for (uint8_t x = i; x < animationCount - 1; x++)
                {
                    pixels[x] = pixels[x + 1];
                    pixelsAnimation[x] = pixelsAnimation[x + 1];
                }

                animationCount--;
                i--;
                break;
            }
        }
    }
}

void AnimationManager::endMoveAnimation()
{
    // TODO: dont remove animation. Just set color
    for (uint8_t i = 0; i < animationCount; i++)
    {
        if (pixelsAnimation[i] == AnimationType::MOVE)
        {
            strip.setColor(pixels[i].position, pixels[i].secondary, false);

            for (uint8_t x = i; x < animationCount - 1; x++)
            {
                pixels[x] = pixels[x + 1];
                pixelsAnimation[x] = pixelsAnimation[x + 1];
            }
            animationCount--;
            i--;
        }
    }

    strip.show();

    // TODO: Raise flag
}

void AnimationManager::removeMoveAnimation()
{
    for (uint8_t i = 0; i < animationCount; i++)
    {
        if (pixelsAnimation[i] == AnimationType::MOVE)
        {
            strip.setColor(pixels[i].position, pixels[i].normal, false);

            for (uint8_t x = i; x < animationCount - 1; x++)
            {
                pixels[x] = pixels[x + 1];
                pixelsAnimation[x] = pixelsAnimation[x + 1];
            }
            animationCount--;
            i--;
        }
    }

    strip.show();
}

void AnimationManager::update()
{
    if (animationCount > 0 && updateTime <= millis())
    {
        globalFade.fade();

        // Apply animation
        for (uint8_t i = 0; i < animationCount; ++i)
        {
            switch (pixelsAnimation[i])
            {
            case AnimationType::GLOBAL_FADE:
                pixels[i].primary.setVal(globalFade.getVal());
                strip.setColor(pixels[i].position, pixels[i].primary, false);
                break;

            case AnimationType::MOVE:
                // TODO:
                pixels[i].primary.fade();
                strip.setColor(pixels[i].position, pixels[i].primary, false);

                // He knows how much neopixels are in animation

                // Reach start color.
                // Activate next.

                // If fade to min and if has secondary color change color

                // If cancle animation true -> go ro desired color

                // If desired color reached -> cancle yourself

                break;

            default:
                break;
            }
        }

        // Show animation
        strip.show();

        updateTime = millis() + UPDATE_TIME_MS;
    }
}