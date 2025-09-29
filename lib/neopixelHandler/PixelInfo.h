#pragma once

#include "utils.h"

struct PixelInfo
{
public:
    PixelInfo() {}
    PixelInfo(StripPosition position) : position(position) {}
    PixelInfo(StripPosition position, Color primary) : position(position), primary(primary) {}
    PixelInfo(StripPosition position, Color primary, Color secondary, Color defaultColor)
        : position(position), primary(primary), secondary(secondary), defaultColor(defaultColor) {}

    bool operator==(const PixelInfo &other) const;
    bool operator!=(const PixelInfo &other) const;
    PixelInfo &operator=(const PixelInfo &obj);

    StripPosition position;
    Color primary;
    Color secondary;
    Color defaultColor;
};