# CJNS Kontroler - Electronic LUDO Game

An embedded C++ implementation of the classic LUDO board game for ATmega328, featuring NeoPixel LED visualization and interactive gameplay.

<p align="center">
  <img src="https://github.com/Zvonimir96/LUDO-Atmega/assets/46999608/c2aaefed-f4bf-4d62-9d88-4fd29494dac7" width="70%">
</p>

## About

This project brings the traditional LUDO board game to life through electronics, promoting interest in STEM fields. The development followed a structured approach:

1. **Software Prototype** - Initial Python implementation to validate game mechanics and control logic ([Python Repository](https://github.com/Zvonimir96/LUDO-Python))
2. **Hardware Design** - Complete electronic board with schematics and PCB design ([Hardware Repository](https://github.com/jkordek1/Man-Don-t-Get-Angry-Board-game))
3. **Embedded Firmware** - This repository contains the ATmega328 firmware that integrates software and hardware into a fully functional game

## Features

- **Visual Feedback** - 5 NeoPixel LED strips displaying houses, safe zones, game path, dice, and button states
- **Interactive Controls** - 13 buttons (4 players × 3 buttons + dice button) via PCF8575 I2C IO expander
- **Smooth Animations** - LED animations for dice rolls, piece movements, and player selections
- **Full Game Logic** - Complete LUDO rules implementation with move validation
- **Multi-player Support** - Up to 4 players with customizable colors

## Hardware Components

- **Microcontroller**: ATmega328 (Arduino compatible)
- **LED Strips**: 5× NeoPixel strips (total 105 LEDs)
  - House strip: 16 LEDs (starting positions)
  - Safe House strip: 16 LEDs (goal zones)
  - Path strip: 52 LEDs (main game board)
  - Dice strip: 9 LEDs (dice display)
  - Button strip: 12 LEDs (button backlighting)
- **Input**: PCF8575 I2C IO expander (16-bit, 13 buttons used)
- **Feedback**: Buzzer for button press confirmation

## Software Architecture

The firmware is organized into modular components:

```
CJNS_kontroler/
├── src/
│   └── main.cpp              # Main application loop
├── lib/
│   ├── gameManager/          # Game logic and state management
│   ├── neopixelHandler/      # LED animation system
│   ├── hardwareResources/    # Hardware abstraction (buttons, LED strips)
│   └── utils/                # Configuration and helper classes
└── platformio.ini            # PlatformIO configuration
```

### Key Components

- **GameHandler** - Manages game states, player turns, dice rolls, and move validation
- **AnimationManager** - Handles concurrent LED animations with fade and movement effects
- **Strip** - Abstracts 5 NeoPixel strips with unified interface
- **Button** - Interrupt-driven button reading with enable/disable control
- **Player** - Tracks player state (4 figures, color, active status)

### State Transitions

| From State | To State | Trigger | Condition |
|------------|----------|---------|-----------|
| COLOR_SELECTION | DICE_ROLL | Dice button | ≥2 players active |
| DICE_ROLL | GAME | Dice rolled | Has valid moves |
| DICE_ROLL | DICE_ROLL | Dice rolled | No valid moves → next player |
| GAME | WAIT_FOR_CALLBACK | Submit button | Valid move selected |
| WAIT_FOR_CALLBACK | DICE_ROLL | Animation complete | Rolled 6 → same player |
| WAIT_FOR_CALLBACK | DICE_ROLL | Animation complete | Not 6 → next player |


## Dependencies

- **Adafruit NeoPixel** - LED strip control
- **PCF8575** - I2C IO expander library
