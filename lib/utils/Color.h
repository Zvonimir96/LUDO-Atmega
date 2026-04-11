#pragma once

#include <Arduino.h>
#include "Conf.h"

/**
 * @brief Represents a color in HSV (Hue, Saturation, Value) color space
 * 
 * This class provides color representation and manipulation for LED animations.
 * HSV color space is used for easier color transitions and brightness control.
 */
class Color
{
    uint16_t hue;  ///< Hue component (0-65535)
    uint8_t sat;   ///< Saturation component (0-255)
    uint8_t val;   ///< Value/Brightness component (0-255)
    bool fadeUp;   ///< Internal state for fade animation direction

public:
    /**
     * @brief Default constructor - creates black color (hue=0, sat=255, val=255)
     */
    Color();
    
    /**
     * @brief Constructor with hue parameter
     * @param hue Hue value (0-65535)
     */
    Color(uint16_t);
    
    /**
     * @brief Assignment operator
     * @param obj Source color object
     * @return Reference to this object
     */
    Color &operator=(const Color &obj);

    /**
     * @brief Get hue component
     * @return Hue value (0-65535)
     */
    uint16_t getHue();
    
    /**
     * @brief Get saturation component
     * @return Saturation value (0-255)
     */
    uint8_t getSat();
    
    /**
     * @brief Get value/brightness component
     * @return Value (0-255)
     */
    uint8_t getVal();

    /**
     * @brief Set hue component
     * @param hue Hue value (0-65535)
     */
    void setHue(uint16_t);
    
    /**
     * @brief Set value/brightness component
     * @param val Value (0-255)
     */
    void setVal(uint8_t);
    
    /**
     * @brief Set saturation component
     * @param sat Saturation value (0-255)
     */
    void setSat(uint8_t);
    
    /**
     * @brief Animate brightness with fade effect
     * 
     * Oscillates brightness between UPDATE_FADE_MIN and 255.
     * Changes by UPDATE_FADE_STEP each call. Direction automatically reverses at limits.
     */
    void fade();
};