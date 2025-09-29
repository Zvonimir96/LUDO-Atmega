#pragma once
#include "Define.h"
#include "PCF8575.h"
#include "Player.h"
#include "Dice.h"

enum game_state
{
  player1,
  player2,
  player3,
  player4,
  select_color_state
};

class Controller
{
  // static int16_t buttons16;
  // static PCF8575 PCF;
  // static bool can_update;

  static void isr();
  static void change_player_color_left(int);
  static void change_player_color_right(int);
  static void select_color(int);
  static void start_game();
  static void next_player();
  static game_state state;
  static void player_left(int);
  static void player_right(int);
  static void player_submit(int);
  static void dice();
  static uint8_t playeble_players();

public:
  static Player players[];

  static void init();
  static void update();
};
