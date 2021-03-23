//Send message//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sendMessage(String message)
{
  Serial2.print("AT+CIPSEND=0," + (String)(message.length() + 1) + "\r\n");
  if (!confirmation())
    return;
  Serial2.print(message + "&\r\n");
  if (!confirmation())
    return;
}

//esp8266 server setup//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool espSetup(String ssid, String password, int port)
{
  //Connect to Access Point
  Serial2.print("AT+CWJAP=" + (String)'"' + ssid + (String)'"' + "," + (String)'"' + password + (String)'"' + "\r\n");
  //return false if failed
  if (!confirmation())
    return false;

  //Allow multiple conections
  Serial2.print("AT+CIPMUX=1\r\n");
  //return false if failed
  if (!confirmation())
    return false;

  //Create server
  Serial2.print("AT+CIPSERVER=1," + (String)port + "\r\n");
  //return false if failed
  if (!confirmation())
    return false;

  //If everything succesful
  return true;
}

//Received command confiramtion/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool confirmation()
{
  String message = "";
  bool confirmation = false;

  while (!confirmation)
  {
    //Read esp output
    char ch = Serial2.read();
    if (ch >= 0)
    {
      Serial.print(ch);
      message += (char)ch;
    }

    //Check if esp return OK or ERROR
    if (ch == '\n')
    {
      if (message.indexOf("OK") >= 0)
      {
        confirmation = true;
      }
      else if (message.indexOf("ERROR") >= 0)
        break;
      else
        message = "";

      message = "";
    }
  }

  //Return if command received succesfully
  return confirmation;
}

//Message catcher and esp-user communication////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void espCom()
{
  int bytes = 0;
  //From user to esp
  while (Serial.available())
  {
    char ch = Serial.read();
    Serial2.print(ch);
    bytes++;

    if (bytes > 30)
      return;
  }

  //From esp to user and command catcher
  while (Serial2.available())
  {
    char ch = Serial2.read();
    command += (char)ch;

    Serial.print(ch);

    if (ch == '\n')
      command = "";

    if (ch == '&')
    {
      command.trim();

      String message;

      if (command.indexOf("time") > 0)
      {
        sendMessage("Current Time: " + (String)now.hour() + ":" + (String)now.minute());

        String message;

        if (hour1 >= 10)
          message = "hour1" + (String)hour1;
        else
          message = "hour10" + (String)hour1;
        sendMessage(message);

        if (hour2 >= 10)
          message = "hour2" + (String)hour2;
        else
          message = "hour20" + (String)hour2;
        sendMessage(message);

        if (hour3 >= 10)
          message = "hour3" + (String)hour3;
        else
          message = "hour30" + (String)hour3;
        sendMessage(message);

        if (hour4 >= 10)
          message = "hour4" + (String)hour4;
        else
          message = "hour40" + (String)hour4;
        sendMessage(message);

        if (minute1 >= 10)
          message = "minute1" + (String)minute1;
        else
          message = "minute10" + (String)minute1;
        sendMessage(message);

        if (minute2 >= 10)
          message = "minute2" + (String)minute2;
        else
          message = "minute20" + (String)minute2;
        sendMessage(message);

        if (minute3 >= 10)
          message = "minute3" + (String)minute3;
        else
          message = "minute30" + (String)minute3;
        sendMessage(message);

        if (minute4 >= 10)
          message = "minute4" + (String)minute4;
        else
          message = "minute40" + (String)minute4;
        sendMessage(message);

        sendMessage("rep" + (String)rep);

        switch (lightStatus)
        {
          case -1:
            sendMessage("OFF");
            break;
          case 0:
            sendMessage("NIGHT");
            break;
          case 1:
            sendMessage("ON");
            break;
          case 2:
            sendMessage("MIDDLE");
            break;
        }

        sendMessage((String)change);
        sendMessage("reset" + (String)resetTime);
        rtc.adjust(DateTime(command.substring(20, 24).toInt(), command.substring(14, 16).toInt(), command.substring(17, 19).toInt(), command.substring(25, 27).toInt(), command.substring(28, 30).toInt(), command.substring(31, 33).toInt()));
      }
      else if (command.indexOf("hour1") > 0)
      {
        hour1 = command.substring(14, 16).toInt();
        if (hour1 >= 10)
          message = "hour1" + (String)hour1;
        else
          message = "hour10" + (String)hour1;
        sendMessage(message);
      }
      else if (command.indexOf("hour2") > 0)
      {
        hour2 = command.substring(14, 16).toInt();
        if (hour2 >= 10)
          message = "hour2" + (String)hour2;
        else
          message = "hour20" + (String)hour2;
        sendMessage(message);
      }
      else if (command.indexOf("hour3") > 0)
      {
        hour3 = command.substring(14, 16).toInt();
        if (hour3 >= 10)
          message = "hour3" + (String)hour3;
        else
          message = "hour30" + (String)hour3;
        sendMessage(message);
      }
      else if (command.indexOf("hour4") > 0)
      {
        hour4 = command.substring(14, 16).toInt();
        if (hour4 >= 10)
          message = "hour4" + (String)hour4;
        else
          message = "hour40" + (String)hour4;
        sendMessage(message);
      }
      else if (command.indexOf("minute1") > 0)
      {
        minute1 = command.substring(17, 19).toInt();
        if (minute1 >= 10)
          message = "minute1" + (String)minute1;
        else
          message = "minute10" + (String)minute1;
        sendMessage(message);
      }
      else if (command.indexOf("minute2") > 0)
      {
        minute2 = command.substring(17, 19).toInt();
        if (minute2 >= 10)
          message = "minute2" + (String)minute2;
        else
          message = "minute20" + (String)minute2;
        sendMessage(message);
      }
      else if (command.indexOf("minute3") > 0)
      {
        minute3 = command.substring(17, 19).toInt();
        if (minute3 >= 10)
          message = "minute3" + (String) minute3;
        else
          message = "minute30" + (String)minute3;
        sendMessage(message);
      }
      else if (command.indexOf("minute4") > 0)
      {
        minute4 = command.substring(17, 19).toInt();
        if (minute1 >= 40)
          message = "minute4" + (String)minute4;
        else
          message = "minute40" + (String)minute4;
        sendMessage(message);
      }
      else if (command.indexOf("repetit") > 0)
      {
        rep = command.substring(16, 17).toInt();
        sendMessage("rep" + (String)rep);
      }
      else if (command.indexOf("reset") > 0)
      {
        resetTime = command.substring(14, 16).toInt();
        sendMessage("reset" + (String)resetTime);
      }
      else if (command.indexOf("change") > 0)
      {
        lightChange((lightStatus + 1) % 2);
      }
      else if (command.indexOf("dont") > 0)
      {
        change = !change;
        sendMessage((String)change);
      }

      command = ""; // Clear the string ready for the next command.
    }
    bytes++;

    if (bytes > 30)
      return;
  }
}
