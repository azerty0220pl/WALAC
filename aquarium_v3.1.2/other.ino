//Light change//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lightChange(int lightMode)
{
  if (lightStatus == lightMode)
    return;

  switch (lightMode)
  {
    case -1:
      digitalWrite(light, LOW);
      digitalWrite(lightMain, LOW);
      sendMessage("OFF");
      break;
    case 0:
      digitalWrite(light, LOW);
      sendMessage("NIGHT");
      break;
    case 1:
      if (lightStatus == 2)
      {
        digitalWrite(light, LOW);
        delay(resetTime * 1000);
        digitalWrite(light, HIGH);
      }
      else if (lightStatus == -1)
      {
        digitalWrite(light, HIGH);
        digitalWrite(lightMain, HIGH);
      }
      else
        digitalWrite(light, HIGH);
      sendMessage("ON");
      break;
    case 2:
      for (byte i = 0; i < rep; i++)
      {
        digitalWrite(light, LOW);
        delay(500);
        digitalWrite(light, HIGH);
        delay(500);
      }
      sendMessage("MIDDLE");
      break;
  }

  lightStatus = lightMode;
}

//Print on LCD//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printTime()
{
  now = rtc.now();

  //lcd.clear();
  lcd.setCursor(0, 0);

  if (now.hour() < 10)
    lcd.print("0");
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if (now.minute() < 10)
    lcd.print("0");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  if (now.second() < 10)
    lcd.print("0");
  lcd.print(now.second(), DEC);
  lcd.print("    ");
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);

  lcd.setCursor(0, 1);
  if (digitalRead(light))
    lcd.print("Lights  ON ");
  else
    lcd.print("Lights  OFF");
}

//Welcome "screen"//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void welcomeScreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("><> AQUARIUM <><");
  lcd.setCursor(0, 1);
  lcd.print("loading...");
}

//Time To Float (hh:mm -> hh,mm)///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float TimeToFloat(float x, float y)
{
  return x + (y * 0.01);
}
