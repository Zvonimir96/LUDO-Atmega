/*#include "Elements.h"
#include "Dice.h"
#include "Path.h"
#include "Controller.h"
#include "Player.h"
#include "Color.h"
#include "SafeHouse.h"
#include "Animator.h"

Animation Animator::animation = none;
House *Animator::house = NULL;
Color Animator::colors[7];
Position Animator::positions[7];
uint8_t Animator::positions_to_update = 0;
unsigned long Animator::time_to_update = millis() + UPDATE_TIME_MS;

Strip Elements::house_strip = Strip(HOUSE_COUNT, HOUSE_PIN);
Strip Elements::safe_house_strip = Strip(SAFE_HOUSE_COUNT, SAFE_HOUSE_PIN);
Strip Elements::path_strip = Strip(PATH_COUNT, PATH_PIN);
Strip Elements::dice_strip = Strip(DICE_COUNT, DICE_PIN);
Strip Elements::touch_strip = Strip(TOUCH_COUNT, TOUCHPAD_PIN);

uint8_t Dice::rotation = 0;
int8_t Dice::number = -1;
bool Dice::animation = false;
Color Dice::color = Color();
unsigned long Dice::time_to_update = millis() + UPDATE_TIME_MS;

PCF8575 Controller::PCF(0x20);
int16_t Controller::buttons16 = 65535;
Player Controller::players[4];
bool Controller::can_update = false;
game_state Controller::state = select_color_state;

Color Player::available_colors[] = {Color(0), Color(10000), Color(20000), Color(30000), Color(35000), Color(40000)};
Color Path::default_color = Color();

Figure *Figure::figures[16];
uint8_t Figure::figure_number = 0;

void setup2()
{
  Serial.begin(9600);
  Serial.println("Test");

  Elements::init();
  Path::init();
  Controller::init();
}

void loop2()
{
  Controller::update();
  Dice::update();
  Animator::update();
}*/