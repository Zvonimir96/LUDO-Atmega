#include "Animator.h"
/*
void Animator::start_house_exit(Position start_position, Position exit_position, Color *color, House *house){
    positions_to_update = 2;
    animation = exit_house_animation;
    Animator::house = house;
    positions[0] = start_position;
    positions[1] = exit_position;
    colors[0] = *color;
    colors[1] = *color;
    colors[1].set_val(UPDATE_FADE_MIN);
}

void Animator::start_path(Position start_position, Color *color){
    positions_to_update = Dice::number + 1;
    animation = path_animation;
    uint8_t fade_step = (255 - UPDATE_FADE_MIN)/positions_to_update;

    for(int i=0; i<positions_to_update; i++){
        positions[i].index = start_position.index + i;
        positions[i].component = start_position.component;
        colors[i] = *color;
        colors[i].set_val(UPDATE_FADE_MIN + fade_step*i);
    }
}

void Animator::stop(){
    animation = none;

    for(int i=0; i<positions_to_update; i++)
        turn_off_pixel(positions[i]);
}

void Animator::update(){
    if(animation != none && time_to_update <= millis()){
        for(int i=0; i<positions_to_update; i++){
            colors[i].fade();
            update_pixel(positions[i], colors[i]);
        }

        time_to_update = millis() + UPDATE_TIME_MS;
    }
}

void Animator::turn_off_pixel(Position position){
    switch(position.component){
        case component_house:
            house->turn_off(position.index);
            break;
        case component_path:
            Path::turn_off(position.index);
            break;
        case component_safe_house:
            break;
        default:
            break;
    }
}

void Animator::update_pixel(Position position, Color color){
    switch(position.component){
        case component_house:
            house->turn_on(position.index, color);
            break;
        case component_path:
            Path::turn_on(position.index, color);
            break;
        case component_safe_house:
            break;
        default:
            break;
    }
}*/
