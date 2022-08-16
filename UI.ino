void show_preset_screen(int preset) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Preset ");
  lcd.print(preset);
}

void show_splash_screen() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(prog_name);
  lcd.setCursor(0, 1);
  lcd.print("Version ");
  lcd.print(version);
}

void show_tuner_screen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tuner");
  lcd.setCursor(9, 1);
  lcd.print("E");
  lcd.setCursor(9, 2);
  lcd.print("^");
  lcd.setCursor(0, 3);
  lcd.print("<--------|-------->");
}

void switch_scan()
{
  if (millis() - t1 > 5000)
  {
    t1 = millis();
    // time process
    //    new_preset++;
    //    if (new_preset > 3) new_preset = 0;
  }

  if (millis() - t2 > 100)
  {
    t2 = millis();
    // GPIO process
    for (int i = 0; i < NUM_SWITCHES; i++)
    {
      if (digitalRead(switchPins[i]) == 0)
      {
        Serial.print("Got a switch ");
        Serial.println(i);

        switch (i) {

          case DRIVE_SWITCH_PRESSED:
            if (tunerOn == true) break;
            if (driveOn == true) {
              driveOn = false;
              digitalWrite(DRIVE_LED, LOW);
            } else {
              driveOn = true;
              digitalWrite(DRIVE_LED, HIGH);
            }
            change_drive_onoff(driveOn);
            break;

          case DELAY_SWITCH_PRESSED:
            if (tunerOn == true) break;
            if (delayOn == true) {
              delayOn = false;
              digitalWrite(DELAY_LED, LOW);
            } else {
              delayOn = true;
              digitalWrite(DELAY_LED, HIGH);
            }
            change_delay_onoff(delayOn);
            break;

          case MOD_SWITCH_PRESSED:
            if (tunerOn == true) break;
            if (modOn == true) {
              modOn = false;
              digitalWrite(MOD_LED, LOW);
            } else {
              modOn = true;
              digitalWrite(MOD_LED, HIGH);
            }
            change_mod_onoff(modOn);
            break;

          case REVERB_SWITCH_PRESSED:
            if (tunerOn == true) break;
            if (reverbOn == true) {
              reverbOn = false;
              digitalWrite(REVERB_LED, LOW);
            } else {
              reverbOn = true;
              digitalWrite(REVERB_LED, HIGH);
            }
            change_reverb_onoff(reverbOn);
            break;

          case PRESET_UP_SWITCH_PRESSED:
            if (tunerOn == true) break;
            new_preset++;
            if (new_preset > 3) {
              new_preset = 0;
            }
            show_preset_screen(new_preset + 1);
            break;

          case PRESET_DOWN_SWITCH_PRESSED:
            if (tunerOn == true) break;
            new_preset--;
            if (new_preset < 0) {
              new_preset = 3;
            }
            show_preset_screen(new_preset + 1);
            break;

          case PRESET_SELECT_SWITCH_PRESSED:
            if (tunerOn == true) break;
            change_hardware_preset(new_preset);
            break;

          case TUNER_SWITCH_PRESSED:
            if (tunerOn == true) {
              tunerOn = false;
              show_preset_screen(display_preset_num);
            } else {
              tunerOn = true;
              show_tuner_screen();
            }

            tuner_on_off(tunerOn);
            break;
        }
      }
    }
  }
}

void update_leds(SparkPreset preset) {

  if (preset.effects[2].OnOff == true) {
    driveOn = true;
    digitalWrite(DRIVE_LED, HIGH);
  } else {
    driveOn = false;
    digitalWrite(DRIVE_LED, LOW);
  }

  if (preset.effects[4].OnOff == true) {
    modOn = true;
    digitalWrite(MOD_LED, HIGH);
  } else {
    modOn = false;
    digitalWrite(MOD_LED, LOW);
  }

  if (preset.effects[5].OnOff == true) {
    delayOn = true;
    digitalWrite(DELAY_LED, HIGH);
  } else {
    delayOn = false;
    digitalWrite(DELAY_LED, LOW);
  }

  if (preset.effects[6].OnOff == true) {
    reverbOn = true;
    digitalWrite(REVERB_LED, HIGH);
  } else {
    reverbOn = false;
    digitalWrite(REVERB_LED, LOW);
  }
}
