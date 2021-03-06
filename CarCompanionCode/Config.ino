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

#include <SoftwareSerial.h> //Include our software serial library

/*
 *All* of the user configurable options currently have to be set in the firmware, 
 then uploaded to the CarCompanion.  
 Please see this webpage for more info about configuring CarCompanion:
 https://jabelone.com.au/carcompanion/documentation/software-configuration/
*/
//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ START USER CONFIG /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
//Pin Definitions//
const int ledPin =  13; //Status LED
const int D12 = 12; //Reserved for future use (button input)
//Headlights, brakelights and indicators are connected to PWM pins.  On cars that use SSRs or some sort of FET you may be able to control the brightness once it's implemented.
const int headLightsPin = 11; //The pin that is connected to the headlights relay.
const int brakeLightsPin = 10; //The pin that is connected to the brakelights relay.
const int indicatorLightsPin = 9; //Pin that controls transistor connected to indicators.
const int lockPin = 8;  //The pin connected to the "locking" wire
const int unlockPin = 7;  //The pin connected to the "unlocking" wire
const int manualLockPin = 6; //Button that will do a manual lock/unlock (not implemented yet)
const int D5 = 5; //Reserved for future use (last PWM pin left)
const int D4 = 4; //Reserved for future use (button input)
const int btTX = 3; //Define our software serial pin for Bluetooth TX
const int btRX = 2; // Define our software serial pin for Bluetooth RX
const int breakTapButton = A7; // Define our break tap button input pin
const int bluetoothPowerPin = A1; //A pin the bluetooth module VCC is connected to
const int bluetoothKeyPin = A0; //A pin connected to the key pin on bluetooth module

///Timing///
const int heartBeatTimeOut = 5000; //How long to wait after we don't get a heartbeat message before locking car. (in milliseconds)
const int indicatorLightsFlashDelay = 1000; //How long the lights stay on (and off) for when flashing indicator lights. (in milliseconds)
const int headLightsFlashDelay = 1000; //How long the lights stay on (and off) for when flashing head lights. (in milliseconds)

///Other Options///
const String carUnlockType = "LOW"; //"LOW" car locks/unlocks when pins pulled low, "HIGH" when pins pulled high. (if none work open a feature request in github)
                                    //NOTE: HIGH only works at 5V logic!  If it needs 12v, hook up a transistor or relay.
const boolean indicatorFlashOnLock = true; //true - indicators flash on lock/unlock, false - indicators don't flash on lock/unlock.
const boolean headLightsFlashOnLock = true;  ////true - headlights flash on lock/unlock, false - headlights don't flash on lock/unlock.
const boolean brakeLightsFlashOnLock = true;  ////true - headlights flash on lock/unlock, false - headlights don't flash on lock/unlock.
//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ END USER CONFIG /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
