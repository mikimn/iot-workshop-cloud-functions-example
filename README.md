
# Workshop Example – Project in IoT (Winter 2021)

This repository contains an example of Firebase Cloud Functions + Arduino.

The arduino increments a value in Cloud Firestore by calling the `changeData` cloud function with an index `i`,
which sets the 

## Structure

* `functions/`- Contains the Firebase Cloud Functions source code and configuration.
The functions are defined at `src/index.ts`.
* `arduino/` - Contains the sample code that runs on the Arduino board.

This code was tested against a WeMos D1 Mini chip with ESP8266 support.

## Environment setup

1. Add this link to the **Additional Boards Manager URL** in the Arduino IDE Preferences: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
2. Go to Boards Manager and download the `esp8266` boards.
3. Go to `Boards` and select `WeMos D1 R1` from the `ESP8266 Boards` section.
