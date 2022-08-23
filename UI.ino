void connection_lost(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connection lost!");
  lcd.setCursor(0,1);
  lcd.print("Reconnecting...");
}

bool is_selected()
{
  if (selected_preset == current_preset)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void show_preset_screen(int preset, String name)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Preset");
  lcd.setCursor(0,1);
  lcd.print("------");
  
  big.writeint(0, 7, preset, 2, true);

  lcd.setCursor(0, 3);
  if (is_selected() == true)
  {
    lcd.print("> ");
    lcd.print(name);
    lcd.setCursor(18,3);
    lcd.print(" <");
  }
  else
  {
    lcd.print("- ");
    lcd.print(name);
    lcd.setCursor(18,3);
    lcd.print(" -");
  }
}

void show_splash_screen()
{
  lcd.init();
  big.begin();

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(prog_name);
  lcd.setCursor(0, 1);
  lcd.print("Version ");
  lcd.print(version);
}

void show_tuner_screen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tuner");
  lcd.setCursor(0, 1);
  lcd.print("-----");
}

void update_tuner(SparkMessage msg)
{
  lcd.setCursor(9, 1);
  if (msg.val == -1.0)
  {
    if (ignoreTuner == false)
    {
      lcd.print("  ");
      lcd.setCursor(6, 3);
      lcd.print("          ");
      ignoreTuner = true;
    }
  }
  else
  {
    lcd.print(note_names[constrain(msg.param1 + 1, 0, 13)]);
    lcd.print(" ");
    lcd.setCursor(6, 3);
    if (msg.val < 0.48)
    {
      lcd.print("< FLAT    ");
    }
    else if (msg.val > 0.54)
    {
      lcd.print("  SHARP > ");
    }
    else
    {
      lcd.print("< GOOD >  ");
    }

    ignoreTuner = false;
  }
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

    if (spark_state == SPARK_DISCONNECTED){
      return;
    }

    // GPIO process
    for (int i = 0; i < NUM_SWITCHES; i++)
    {
      if (digitalRead(switchPins[i]) == 0)
      {
        Serial.print("Got a switch ");
        Serial.println(i);

        switch (i)
        {

        case DRIVE_SWITCH_PRESSED:
          if (isTunerMode == true)
            break;
          if (driveOn == true)
          {
            driveOn = false;
            digitalWrite(DRIVE_LED, LOW);
          }
          else
          {
            driveOn = true;
            digitalWrite(DRIVE_LED, HIGH);
          }
          change_drive_onoff(driveOn);
          break;

        case DELAY_SWITCH_PRESSED:
          if (isTunerMode == true)
            break;
          if (delayOn == true)
          {
            delayOn = false;
            digitalWrite(DELAY_LED, LOW);
          }
          else
          {
            delayOn = true;
            digitalWrite(DELAY_LED, HIGH);
          }
          change_delay_onoff(delayOn);
          break;

        case MOD_SWITCH_PRESSED:
          if (isTunerMode == true)
            break;
          if (modOn == true)
          {
            modOn = false;
            digitalWrite(MOD_LED, LOW);
          }
          else
          {
            modOn = true;
            digitalWrite(MOD_LED, HIGH);
          }
          change_mod_onoff(modOn);
          break;

        case REVERB_SWITCH_PRESSED:
          if (isTunerMode == true)
            break;
          if (reverbOn == true)
          {
            reverbOn = false;
            digitalWrite(REVERB_LED, LOW);
          }
          else
          {
            reverbOn = true;
            digitalWrite(REVERB_LED, HIGH);
          }
          change_reverb_onoff(reverbOn);
          break;

        case PRESET_UP_SWITCH_PRESSED:
          if (isTunerMode == true)
            break;
          selected_preset++;
          if (selected_preset > 3)
          {
            selected_preset = 0;
          }
          DEB("selected_preset ");
          DEBUG(selected_preset);
          show_preset_screen(selected_preset + 1, presets[selected_preset].Name);
          break;

        case PRESET_DOWN_SWITCH_PRESSED:
          if (isTunerMode == true)
            break;
          selected_preset--;
          if (selected_preset < 0)
          {
            selected_preset = 3;
          }
          DEB("selected_preset ");
          DEBUG(selected_preset);
          show_preset_screen(selected_preset + 1, presets[selected_preset].Name);
          break;

        case PRESET_SELECT_SWITCH_PRESSED:
          if (isTunerMode == true)
            break;
          current_preset = selected_preset;
          change_hardware_preset(selected_preset);
          update_leds(presets[current_preset]);
          show_preset_screen(selected_preset + 1, presets[current_preset].Name);
          break;

        case TUNER_SWITCH_PRESSED:
          if (isTunerMode == true)
          {
            tuner_on_off(false);
          }
          else
          {
            tuner_on_off(true);
          }

          break;
        }
      }
    }
  }
}

void update_leds(SparkPreset preset)
{

  if (preset.effects[2].OnOff == true)
  {
    driveOn = true;
    digitalWrite(DRIVE_LED, HIGH);
  }
  else
  {
    driveOn = false;
    digitalWrite(DRIVE_LED, LOW);
  }

  if (preset.effects[4].OnOff == true)
  {
    modOn = true;
    digitalWrite(MOD_LED, HIGH);
  }
  else
  {
    modOn = false;
    digitalWrite(MOD_LED, LOW);
  }

  if (preset.effects[5].OnOff == true)
  {
    delayOn = true;
    digitalWrite(DELAY_LED, HIGH);
  }
  else
  {
    delayOn = false;
    digitalWrite(DELAY_LED, LOW);
  }

  if (preset.effects[6].OnOff == true)
  {
    reverbOn = true;
    digitalWrite(REVERB_LED, HIGH);
  }
  else
  {
    reverbOn = false;
    digitalWrite(REVERB_LED, LOW);
  }
}
