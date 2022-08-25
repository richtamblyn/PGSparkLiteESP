#ifndef UI_h
#define UI_h

#include "config.h"
#include "Spark.h"
#include <LiquidCrystal_I2C.h>
#include <BigFont02_I2C.h>

// Set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
BigFont02_I2C     big(&lcd);

unsigned long switch_timer, debounce_timer;

bool driveOn = false;
bool delayOn = false;
bool modOn = false;
bool reverbOn = false;

const String note_names[] = {"...","C","C#","D","D#","E","F","F#","G","G#","A","A#","B","..."};
bool ignoreTuner = false;

int last_pressed;

#endif
