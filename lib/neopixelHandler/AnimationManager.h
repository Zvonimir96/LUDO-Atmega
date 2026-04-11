#pragma once

#include "AnimationType.h"
#include "hardwareResources.h"
#include "AnimationInfo.h"

typedef void (*AnimatorCallback)();

/**
 * @brief Manages all active LED animations
 * 
 * Singleton class that coordinates multiple concurrent animations.
 * Supports fade effects and movement animations with callback on completion.
 */
class AnimationManager
{
public:
    /**
     * @brief Get singleton instance
     * @return Reference to the single AnimationManager instance
     */
    static AnimationManager &getInstance()
    {
        static AnimationManager instance;
        return instance;
    }

    /**
     * @brief Initialize animation system
     * @param callback Function to call when move animation completes
     */
    void init(AnimatorCallback callback);
    
    /**
     * @brief Add new animation(s)
     * @param pixels Array of AnimationInfo describing LEDs to animate
     * @param numPixels Number of elements in pixels array
     * @param type Type of animation (GLOBAL_FADE or MOVE)
     */
    void add(AnimationInfo *pixels, uint8_t numPixels, AnimationType type);
    
    /**
     * @brief Remove animation(s)
     * @param pixels Array of AnimationInfo to remove (matched by position)
     * @param numPixels Number of elements in pixels array
     * @param type Type of animation to remove
     */
    void remove(AnimationInfo *pixels, uint8_t numPixels, AnimationType type);
    
    /**
     * @brief Update all active animations
     * 
     * Called every loop iteration. Updates animation states,
     * applies colors to strips, and triggers callbacks.
     * Uses UPDATE_ANIMATION_INTERVAL for timing.
     */
    void update();

    /**
     * @brief Complete move animation and trigger callback
     * 
     * Removes all MOVE animations and calls the registered callback.
     */
    void endMoveAnimation();
    
    /**
     * @brief Cancel move animation without callback
     * 
     * Removes all MOVE animations but does not trigger callback.
     */
    void removeMoveAnimation();

    Color globalFade;  ///< Global fade color state (used for button/dice animations)

private:
    // Prevent instantiation
    AnimationManager() {}
    // Prevent copying
    AnimationManager(const AnimationManager &) = delete;
    void operator=(const AnimationManager &) = delete;

    AnimationInfo pixels[15];          ///< Active animations (max 15)
    AnimationType pixelsAnimation[15]; ///< Type for each animation slot
    uint8_t animationCount = 0;        ///< Number of active animations
    unsigned long updateTime = 0;      ///< Last update timestamp (for timing)

    Strip &strip = Strip::getInstance();  ///< LED strip controller reference

    AnimatorCallback callback;  ///< Callback function for move completion
};
