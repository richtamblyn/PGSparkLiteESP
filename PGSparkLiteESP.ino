
#include "config.h"
#include "UI.h"

#include <SPI.h>
#include <Wire.h>

#include "Spark.h"
#include "SparkIO.h"

uint8_t display_preset_num;
bool setting_modified = false;
char param_str[50];
int param = -1;
bool isTunerMode;
bool scan_result = false;
int new_preset;

void setup()
{
  // Setup LEDs
  pinMode(BT_LED, OUTPUT);
  pinMode(DRIVE_LED, OUTPUT);
  pinMode(DELAY_LED, OUTPUT);
  pinMode(MOD_LED, OUTPUT);
  pinMode(REVERB_LED, OUTPUT);

  show_splash_screen();

  Wire.begin(0, 4);
  Serial.begin(115200);

  for (int i = 0; i < NUM_SWITCHES; i++)
    pinMode(switchPins[i], INPUT_PULLUP);

  Serial.println("Connecting...");
  lcd.setCursor(0, 3);
  lcd.print("Connecting...");

  while (!scan_result)
  {
    scan_result = spark_state_tracker_start();
  }

  Serial.println("Connected");
  lcd.setCursor(0, 3);
  lcd.print("Loading Presets...");

  t1 = t2 = millis();

  while (spark_state != SPARK_SYNCED) {
    update_spark_state();
  }

  new_preset = preset.curr_preset;
  show_preset_screen(preset.curr_preset + 1);
  update_leds(preset);
}

void loop()
{
  switch_scan();  
  update_spark_state();
}
