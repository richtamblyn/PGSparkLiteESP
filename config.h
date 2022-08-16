#ifndef _CONFIG_H
#define _CONFIG_H

String prog_name = "PGSparkLite ESP";
String version = "1.0.0";

// Comment this line out for a production build
#define DEBUG_ON

// GPIO Pins for LEDs
#define BT_LED 2
#define DRIVE_LED 17
#define DELAY_LED 16
#define MOD_LED 4
#define REVERB_LED 15

#define NUM_SWITCHES 8

// GPIO Pins for Switches
#define DRIVE_SWITCH 26
#define DELAY_SWITCH 27
#define MOD_SWITCH 14
#define REVERB_SWITCH 12
#define PRESET_UP 33
#define PRESET_DOWN 32
#define PRESET_SELECT 13
#define TUNER_SWITCH 25

const uint8_t switchPins[]{DRIVE_SWITCH, DELAY_SWITCH, MOD_SWITCH, REVERB_SWITCH, PRESET_UP, PRESET_DOWN, PRESET_SELECT, TUNER_SWITCH};

#define DRIVE_SWITCH_PRESSED 0
#define DELAY_SWITCH_PRESSED 1
#define MOD_SWITCH_PRESSED 2
#define REVERB_SWITCH_PRESSED 3
#define PRESET_UP_SWITCH_PRESSED 4
#define PRESET_DOWN_SWITCH_PRESSED 5
#define PRESET_SELECT_SWITCH_PRESSED 6
#define TUNER_SWITCH_PRESSED 7

#endif
