---------------------------------------------------------------WALAC---------------------------------------------------------------
My website: https://azerty0220pl.jimdosite.com/
My email: azerty0220pl@gmail.com
Feel free to ask me a question.

1. About WALAC
2. Features
3. Code and app
4. Schematic and components
-----------------------------------------------------------------------------------------------------------------------------------

1. About WALAC---------------------------------------------------------------------------------------------------------------------
WiFi Aquarium Light Arduino Control is meant to automatically turn aquarium lights on and off. To make life easier, you can change 
the turn on/off ours through an Android app. 
-----------------------------------------------------------------------------------------------------------------------------------

2. Features------------------------------------------------------------------------------------------------------------------------
- Two turn on times, two turn off times. If you want to turn the lights on and off only once a day, just set an impossible hour for
the second on and off times
- Enable/Disable automatic turn lights on/off
- LCD Display with time, day of week and light status
- Manual turn lights on/off through Android app or physical switch
-----------------------------------------------------------------------------------------------------------------------------------

3. Code and app--------------------------------------------------------------------------------------------------------------------
IMPORTANT: WALAC needs both Arduino and mobile phone connected to the same local network. In the Arduino code write down SSID and 
password to your router so Arduino can connect properly. Then check Arduino's IP, you will need it so the app will be able to 
connect to the Arduino

Arduino code available in the repository.

Download app for Android: https://play.google.com/store/apps/details?id=com.Azerty0220pl.Aquarium

Note that some features were designed for my specific needs. You may ignore MIDDLE lights rep or repetitions and reset time. If you 
want to turn the lights on and off only once a day, just set an impossible hour for the second on and off times.
-----------------------------------------------------------------------------------------------------------------------------------

4. Scematic and components---------------------------------------------------------------------------------------------------------
Schematic available in the repository.

- Arduino Mega2560
- ESP8266
- RTC ds1307
- LCD display 16x2
- Optocoupler
- Triac
- 2x Switches or push buttons
- Wires, resistors, etc.
