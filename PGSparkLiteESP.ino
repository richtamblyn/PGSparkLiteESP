#include "config.h"
#include "UI.h"
#include "Spark.h"
#include "SparkIO.h"

uint8_t display_preset_num;
bool setting_modified = false;
char param_str[50];
int param = -1;
bool isTunerMode;
bool tunerScreenVisible = false;
bool scan_result = false;

int new_preset;
int current_preset;

void setup()
{
#ifdef DEBUG_ON
  Serial.begin(115200);
#endif

  // Setup LEDs
  pinMode(BT_LED, OUTPUT);
  pinMode(DRIVE_LED, OUTPUT);
  pinMode(DELAY_LED, OUTPUT);
  pinMode(MOD_LED, OUTPUT);
  pinMode(REVERB_LED, OUTPUT);

  show_splash_screen();

  for (int i = 0; i < NUM_SWITCHES; i++)
    pinMode(switchPins[i], INPUT_PULLUP);

  lcd.setCursor(0, 3);
  lcd.print("Connecting...");

  while (!scan_result)
  {
    scan_result = spark_state_tracker_start();
  }

  lcd.setCursor(0, 3);
  lcd.print("Loading Presets...");

  switch_timer = millis();

  while (spark_state != SPARK_SYNCED)
  {
    update_spark_state();
  }
}

void loop()
{
  switch_scan();
  update_spark_state();
}
