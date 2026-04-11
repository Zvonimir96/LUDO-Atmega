#pragma once

#include <Arduino.h>

/**
 * @brief Enumeration of available LED strip types
 */
enum class StripE
{
    HOUSE = 0,    ///< Starting house positions (16 LEDs)
    S_HOUSE = 1,  ///< Safe house/goal zones (16 LEDs)
    PATH = 2,     ///< Main game path (52 LEDs)
    DICE = 3,     ///< Dice display (9 LEDs)
    BUTTONS = 4   ///< Button backlighting (12 LEDs)
};

/**
 * @brief Represents a position on a specific LED strip
 * 
 * Used to uniquely identify any LED in the system by combining
 * strip type and index within that strip.
 */
struct StripPosition
{
    StripE strip;    ///< Which LED strip
    uint32_t index;  ///< LED index on that strip

    /**
     * @brief Default constructor - initializes to HOUSE strip, index 0
     */
    StripPosition() : strip(StripE::HOUSE), index(0) {}
    
    /**
     * @brief Constructor with parameters
     * @param strip LED strip type
     * @param index LED index on the strip
     */
    StripPosition(StripE strip, uint32_t index) : strip(strip), index(index) {}

    /**
     * @brief Equality comparison operator
     * @param other Position to compare with
     * @return true if both strip and index match
     */
    bool operator==(const StripPosition &other) const
    {
        return index == other.index && strip == other.strip;
    }

    /**
     * @brief Inequality comparison operator
     * @param other Position to compare with
     * @return true if strip or index differ
     */
    bool operator!=(const StripPosition &other) const
    {
        return !(*this == other);
    };

    /**
     * @brief Assignment operator
     * @param obj Source position
     * @return Reference to this object
     */
    StripPosition &operator=(const StripPosition &obj)
    {
        strip = obj.strip;
        index = obj.index;

        return *this;
    }
};