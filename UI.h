#ifndef UI_h
#define UI_h

#include "config.h"
#include "Spark.h"
#include <LiquidCrystal_I2C.h>

// Set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

unsigned long t1, t2;

bool tunerOn = false;
bool driveOn = false;
bool delayOn = false;
bool modOn = false;
bool reverbOn = false;

#endif
