#pragma once

#include <Arduino.h>

enum class StripE
{
    HOUSE = 0,
    S_HOUSE = 1,
    PATH = 2,
    DICE = 3,
    BUTTONS = 4
};

struct StripPosition
{
    StripE strip;
    uint32_t index;

    StripPosition() : strip(StripE::HOUSE), index(0) {}
    StripPosition(StripE strip, uint32_t index) : strip(strip), index(index) {}

    bool operator==(const StripPosition &other) const
    {
        return index == other.index && strip == other.strip;
    }

    bool operator!=(const StripPosition &other) const
    {
        return !(*this == other);
    };

    StripPosition &operator=(const StripPosition &obj)
    {
        strip = obj.strip;
        index = obj.index;

        return *this;
    }
};