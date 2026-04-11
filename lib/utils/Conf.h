/**
 * @file Conf.h
 * @brief Global configuration constants for CJNS LUDO game
 * 
 * Contains all pin definitions, hardware parameters, game constants,
 * and animation settings.
 */

#pragma once

// ============================================================================
// Hardware Pin Definitions
// ============================================================================

#define BUZZER_PIN 10          ///< Buzzer output pin for button feedback

#define PATH_PIN 4             ///< NeoPixel data pin for PATH strip
#define DICE_PIN 5             ///< NeoPixel data pin for DICE strip
#define HOUSE_PIN 6            ///< NeoPixel data pin for HOUSE strip
#define TOUCHPAD_PIN 7         ///< NeoPixel data pin for BUTTONS strip
#define SAFE_HOUSE_PIN 8       ///< NeoPixel data pin for SAFE_HOUSE strip

#define INTERRUPT_PIN 2        ///< PCF8575 interrupt pin

// ============================================================================
// LED Strip Sizes
// ============================================================================

#define PATH_COUNT 52          ///< Number of LEDs in main game path
#define DICE_COUNT 9           ///< Number of LEDs in dice display
#define HOUSE_COUNT 16         ///< Number of LEDs in starting houses (4 per player)
#define SAFE_HOUSE_COUNT 16    ///< Number of LEDs in safe houses (4 per player)
#define TOUCH_COUNT 12         ///< Number of LEDs for button backlighting
#define STRIPS_COUNT 5         ///< Total number of LED strips

#define PATH_QUATER 13         ///< LEDs per quarter of path (52/4)
#define HOUSE_EXIT 1           ///< Index of house exit position

// ============================================================================
// LED Display Settings
// ============================================================================

#define BRIGHTNESS 50          ///< Global LED brightness (0-255)

#define SAFE_HOUSE_SAT 100     ///< Saturation for safe house LEDs
#define PATH_SAT 0             ///< Saturation for path LEDs (white)
#define PATH_VAL 150           ///< Brightness for path LEDs

// ============================================================================
// Button Bit Masks (PCF8575 pins)
// ============================================================================

#define PLAYER1_LEFT 1 << 1    ///< Player 1 left button bit
#define PLAYER1_SUBMIT 1 << 0  ///< Player 1 submit button bit
#define PLAYER1_RIGHT 1 << 2   ///< Player 1 right button bit

#define PLAYER2_LEFT 1 << 4    ///< Player 2 left button bit
#define PLAYER2_SUBMIT 1 << 3  ///< Player 2 submit button bit
#define PLAYER2_RIGHT 1 << 5   ///< Player 2 right button bit

#define PLAYER3_LEFT 1 << 7    ///< Player 3 left button bit
#define PLAYER3_SUBMIT 1 << 6  ///< Player 3 submit button bit
#define PLAYER3_RIGHT 1 << 8   ///< Player 3 right button bit

#define PLAYER4_LEFT 1 << 10   ///< Player 4 left button bit
#define PLAYER4_SUBMIT 1 << 9  ///< Player 4 submit button bit
#define PLAYER4_RIGHT 1 << 11  ///< Player 4 right button bit

#define DICE_BUTTON 4096       ///< Dice button bit (1 << 12)

// ============================================================================
// Game Constants
// ============================================================================

#define NUMBER_OF_PLAYERS 4              ///< Total players in game
#define NUMBER_OF_FIGURES 4              ///< Figures per player
#define NUMBER_OF_AVAILABLE_COLORS 6     ///< Color choices for players

// ============================================================================
// Animation Settings
// ============================================================================

#define UPDATE_TIME_MS 40      ///< Animation update interval in milliseconds

#define DICE_ANIMATION_NUMBER_OF_ITERATIONS 30  ///< Number of dice roll animation iterations (must be divisor of 6)
#define DICE_ANIMATION_START_DELAY 10           ///< Initial delay between dice changes (ms)
#define DICE_ANIMATION_DELAY_INCREMENT 5        ///< Delay increment per iteration (ms)

#define UPDATE_FADE_STEP 5     ///< Brightness change per fade update
#define UPDATE_FADE_MIN 150    ///< Minimum brightness in fade animation
#define COLOR_MAX_VALUE 255    ///< Maximum color component value