#include "PixelInfo.h"

bool PixelInfo::operator==(const PixelInfo &other) const
{
    return position == other.position;
}

bool PixelInfo::operator!=(const PixelInfo &other) const
{
    return !(*this == other);
}

PixelInfo &PixelInfo::operator=(const PixelInfo &obj)
{
    position = obj.position;
    primary = obj.primary;
    secondary = obj.secondary;
    defaultColor = obj.defaultColor;

    return *this;
}