#pragma once

#include "utils.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

/**
 * @brief Low-level LED strip controller
 * 
 * Singleton class that manages 5 NeoPixel LED strips.
 * Provides unified interface for setting colors and updating displays.
 */
class Strip
{
public:
    /**
     * @brief Get singleton instance
     * @return Reference to the single Strip instance
     */
    static Strip &getInstance()
    {
        static Strip instance;
        return instance;
    }

    /**
     * @brief Initialize all LED strips
     * 
     * Creates and configures 5 Adafruit_NeoPixel objects:
     * - HOUSE (16 LEDs)
     * - S_HOUSE (16 LEDs)
     * - PATH (52 LEDs)
     * - DICE (9 LEDs)
     * - BUTTONS (12 LEDs)
     */
    void init();
    
    /**
     * @brief Set color for LED at StripPosition
     * @param stripPosition Position specifying strip and index
     * @param color Color to set (HSV)
     * @param update If true, immediately update display (default: true)
     */
    void setColor(const StripPosition stripPosition, Color color, bool update = true);
    
    /**
     * @brief Set color for LED by strip and index
     * @param strip Strip type
     * @param index LED index on that strip
     * @param color Color to set (HSV)
     * @param update If true, immediately update display (default: true)
     */
    void setColor(const StripE strip, const uint8_t index, Color color, bool update = true);
    
    /**
     * @brief Set multiple colors on a strip at once
     * @param strip Strip type
     * @param indexs Array of LED indices
     * @param colors Array of colors (parallel to indexs)
     * @param size Number of LEDs to set
     * @param update If true, immediately update display (default: true)
     */
    void setColor(const StripE strip, uint8_t indexs[], Color colors[], uint8_t size, bool update = true);
    
    /**
     * @brief Turn off all LEDs on a strip
     * @param strip Strip to clear
     */
    void clear(const StripE strip);
    
    /**
     * @brief Update all LED strips to show current colors
     */
    void show();
    
    /**
     * @brief Update specific LED strip to show current colors
     * @param strip Strip to update
     */
    void show(const StripE strip);

private:
    // Prevent instantiation
    Strip() {}
    // Prevent copying
    Strip(const Strip &) = delete;
    void operator=(const Strip &) = delete;

    Adafruit_NeoPixel *strips[STRIPS_COUNT];  ///< Array of 5 NeoPixel strip objects
};
