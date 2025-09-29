#pragma once
/*#include "Elements.h"
#include "Color.h"
#include "Position.h"
#include "House.h"
#include "Path.h"
#include "Define.h"
#include "Dice.h"

enum Animation {exit_house_animation, path_animation, none};

class Animator{
    static Color colors[7];
    static Position positions[7];
    static uint8_t positions_to_update;
    static Animation animation;
    static unsigned long time_to_update;
    static House *house;

    static void update_pixel(Position, Color);
    static void turn_off_pixel(Position);
public:
    static void start_house_exit(Position, Position, Color *, House *);
    static void start_path(Position, Color *);
    static void stop();
    static void update();
};*/