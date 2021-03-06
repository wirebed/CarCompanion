/*This file is part of CarCompanion.

Copyright (C) 2016 Jaimyn Mayer (Known as "Jabelone" online)

CarCompanion is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

CarCompanion is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CarCompanion.  If not, see <http://www.gnu.org/licenses/>. */

void setup() {
  pinMode(ledPin, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(indicatorLightsPin, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(A3, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(lockPin, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(unlockPin, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(bluetoothPowerPin, OUTPUT); //Set the power control for bluetooth to an output
  pinMode(brakeLightsPin, OUTPUT);
  pinMode(breakTapButton, OUTPUT);

  //Initial Outputs
  digitalWrite(A3, LOW); //To lazy to run separate wire to GND, comment out if not needed.
  digitalWrite(ledPin, LOW);  //Make sure our LED is off
  digitalWrite(bluetoothPowerPin, HIGH); //Make sure our bluetooth is turned on!

  //Serial port settings
  BTserial.begin(9600); // HC-06 default serial speed is 38400
  Serial.begin(38400); //Enable our hardware serial ports (for debugging etc)
}

void loop() {
  while (BTserial.available() > 0)
  {
    digitalWrite(ledPin, HIGH); //Flash status LED to let us know we're recieving something via soft serial port
    btVal = BTserial.readStringUntil('\n'); //Used to separate commands
    //Serial.println(btVal); //Send whatever we got to the Arduino hardware serial port for debugging (uncomment if needed)
    digitalWrite(ledPin, LOW);
  }

  if (btVal == "Heartbeat") {
    lastHeartBeat = millis(); //If it's a heartbeat message, update the time we last received one.
    if (dontunLock == false) unlockCar();  //If we haven't manually locked it, unlock it.
  }
  else if (btVal == "Lockcar") {  //If we get a command to manually lock it.
    dontunLock = true;  //Set our flag so it won't auto unlock until we manually unlock it.
    lockCar(); //Lock car
  }
  else if (btVal == "Unlockcar") {  //If we get a command to manually unlock it.
    dontunLock = false; //Set our flag so it may auto unlock again.
    unlockCar(); //Unlock car
  }
  else if (btVal != "") Serial.println("Error: Unrecognised command received from phone!"); //If it's anything else, we aren't expecting it!
  btVal = ""; //Reset the received command before the next loop.

  if (millis() - lastHeartBeat > heartBeatTimeOut) {
    lockCar();
  }

  if (digitalRead(breakTapButton) == LOW) {
    if (buttonLastTime + debounceBrakeDelay >= millis()) {
      buttonLastTime = millis();
      if (digitalRead(breakTapButton) == LOW) {
        buttonState = true;
      }
    }
  }
  else buttonState = false;

  if (buttonState) digitalWrite(brakeLightsPin, HIGH);  //If our button has been debounced and it's down turn lights on
  else digitalWrite(brakeLightsPin, LOW);  //If our button is not down turn lights off

  //These code bits check if our lights should be on (usually to be flashed)
  //This is a complete rewrite of the logic so it probably doesn't work yet as it's untested

  if ((indicatorLightsMillis - millis()) > 0) { //If the light is meant to be on still
    digitalWrite(indicatorLightsPin, HIGH); //Set our indicator trigger pin to HIGH
    indicatorLightsState = true;
  }
  else {
    digitalWrite(indicatorLightsPin, LOW); //Set our indicator trigger pin to LOW
    indicatorLightsState = false;
  }


  if ((headLightsMillis - millis()) > 0) { //If the light is meant to be on still
    digitalWrite(headLightsPin, HIGH); //Set our indicator trigger pin to HIGH
    headLightsState = true;
  }
  else {
    digitalWrite(headLightsPin, LOW); //Set our light trigger pin to LOW
    headLightsState = false;
  }

  //Read from hardware serial port and send to bluetooth for debugging purposes (uncomment if needed)
  /*
  if (Serial.available())
  {
    digitalWrite(ledPin, HIGH); //Set the received somethiing via Bluetooth LED to on.
    BTserial.write(Serial.read()); //Send to the bluetooth serial port whatever we got.
    digitalWrite(ledPin, LOW); //Set the received somethiing via Bluetooth LED back to off.
  }*/
}
