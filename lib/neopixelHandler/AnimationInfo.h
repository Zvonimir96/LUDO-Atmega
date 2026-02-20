#pragma once

#include "utils.h"

struct AnimationInfo
{
public:
    AnimationInfo() {}
    AnimationInfo(StripPosition position) : position(position) {}
    AnimationInfo(StripPosition position, Color primary) : position(position), primary(primary) {}

    bool operator==(const AnimationInfo &other) const;
    bool operator!=(const AnimationInfo &other) const;
    AnimationInfo &operator=(const AnimationInfo &obj);

    StripPosition position;
    Color primary;
    Color secondary;
    Color normal;
};