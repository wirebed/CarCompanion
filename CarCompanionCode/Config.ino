/*This file is part of CarCompanion.

Copyright (C) 2015 Jaimyn Mayer (Known as "Jabelone" online)

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

#include <SoftwareSerial.h> //Include our software serial library

//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ START USER CONFIG /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
//Pin Definitions//
SoftwareSerial BTserial(2, 3); // Define our software serial pins (RX, TX)
const int ledPin =  13; //Status LED
const int clutchPedalPin = 12; //Button connected to the clutch pedal on manual cars
//Headlights, brakelights and indicators are connected to PWM pins.  On newer cars you will be able to control the brightness of these lights once it's implemented in the code.
const int headLightsPin = 11; //The pin that is connected to the headlights relay.
const int brakeLightsPin = 10; //The pin that is connected to the brakelights relay.
const int indicatorPin = 9; //Pin that controls transistor connected to indicators.
const int lockPin = 8;  //The pin connected to the "locking" wire
const int unlockPin = 7;  //The pin connected to the "unlocking" wire
const int manualLockPin = 6; //Button that will do a manual lock/unlock (not implemented yet)
const int futurePWMusePin = 5; //Reserved for future use (last PWM pin left)
const int brakePedalPin = 4; //A button connected to the brake pedal
//                        3  //Used for the bluetooth soft serial tx port
//                        2  //Used for the bluetooth soft serial rx port
const int bluetoothPowerPin = A0; //A pin the bluetooth module VCC is connected to
const int bluetoothKeyPin = A1; //A pin connected to the key pin on bluetooth module


///Timing///
const int heartBeatTimeOut = 2000; //How long to wait after we don't get a heartbeat message before locking car. (in milliseconds)
const int indicatorFlashDelay = 1000; //How long the lights stay on (and off) for when flashing indicator lights. (in milliseconds)
const int headLightsFlashDelay = 1000; //How long the lights stay on (and off) for when flashing head lights. (in milliseconds)
const int brakeLightsFlashDelay = 1000; //How long the lights stay on (and off) for when flashing brake lights. (in milliseconds)

///Other Options///
const String carUnlockType = "LOW"; //"LOW" car locks/unlocks when pins pulled low, "HIGH" when pins pulled high. (if none work open a feature request in github)
                                    //NOTE: HIGH only works at 5V logic!  If it needs 12v, hook up a transistor or relay.
const boolean indicatorFlashOnLock = true; //true - indicators flash on lock/unlock, false - indicators don't flash on lock/unlock.
const boolean headLightsFlashOnLock = true;  ////true - headlights flash on lock/unlock, false - headlights don't flash on lock/unlock.
const boolean brakeLightsFlashOnLock = true;  ////true - headlights flash on lock/unlock, false - headlights don't flash on lock/unlock.
//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ END USER CONFIG /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//

//-/-/-/-/-/-/-/-/ Declare our variables - do not modify unless you know what you're doing! /-/-/-/-/-/-/-/-/
String btVal; //Where we store what we got via Bluetooth
unsigned long lastHeartBeat; //For timing of heartbeat message
unsigned long headLightsMillis; //For timing of headlights
boolean headLightsState = false; //For keeping track of headlights state
unsigned long brakeLightsMillis; //For timing of brakelights (currently not used)
boolean brakeLightsState = false; //For keeping track of brakelights state (currently not used)
unsigned long indicatorLightsMillis; //For timing of indicators
boolean indicatorLightsState = false; //For keeping track of indicators state
unsigned long interiorLightsMillis;  //For timing of the interior light(s) (currently not used)
boolean interiorLightsState = false; //For keeping track of interior light(s) state (currently not used)
boolean dontunLock = false; //A flag to check if we manually locked it
boolean carLocked; //A flag to keep track of the lock status