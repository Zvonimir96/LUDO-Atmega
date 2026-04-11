/**
 * @file AnimationInfo.cpp
 * @brief Implementation of AnimationInfo animation data structure
 */
#include "AnimationInfo.h"

bool AnimationInfo::operator==(const AnimationInfo &other) const
{
    return position == other.position;
}

bool AnimationInfo::operator!=(const AnimationInfo &other) const
{
    return !(*this == other);
}

AnimationInfo &AnimationInfo::operator=(const AnimationInfo &obj)
{
    position = obj.position;
    primary = obj.primary;
    secondary = obj.secondary;
    normal = obj.normal;

    return *this;
}