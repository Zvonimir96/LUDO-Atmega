#pragma once

#include "utils.h"

/**
 * @brief Describes a single LED animation
 * 
 * Contains position and color information for animating an LED.
 * Used by AnimationManager to track and update active animations.
 */
struct AnimationInfo
{
public:
    /**
     * @brief Default constructor
     */
    AnimationInfo() {}
    
    /**
     * @brief Constructor with position
     * @param position LED position to animate
     */
    AnimationInfo(StripPosition position) : position(position) {}
    
    /**
     * @brief Constructor with position and primary color
     * @param position LED position to animate
     * @param primary Primary/animated color
     */
    AnimationInfo(StripPosition position, Color primary) : position(position), primary(primary) {}

    /**
     * @brief Equality operator - compares positions only
     * @param other Animation to compare with
     * @return true if positions match
     */
    bool operator==(const AnimationInfo &other) const;
    
    /**
     * @brief Inequality operator
     * @param other Animation to compare with
     * @return true if positions differ
     */
    bool operator!=(const AnimationInfo &other) const;
    
    /**
     * @brief Assignment operator
     * @param obj Source animation
     * @return Reference to this object
     */
    AnimationInfo &operator=(const AnimationInfo &obj);

    StripPosition position;  ///< LED position being animated
    Color primary;           ///< Primary/animated color (current display)
    Color secondary;         ///< Secondary/target color (for transitions)
    Color normal;            ///< Normal/base color (to restore after animation)
};