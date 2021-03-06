/*
Configuration.cpp - Library for saving, loading,
and deleting the various configurations both
for the active profile and the physical setup
of the extruder.

Created by Matthew P. Rogge, Februrary 12, 2014.
Released into the public domain.

*/
#include "definitions.h"
#include "Arduino.h"
#include "EEPROMAnything.h"
#include "Configuration.h"

void Configuration::loadDefaultProfile() {

  //General
  profile.profileNumber = -1;
  strcpy(profile.name, "PET 1.85mm");
  profile.diaSetpoint = 3.0;
  profile.density = 1.38;
  profile.tolerance = 0.05;

  //Starve Feeder
  profile.gramsPerMin = 8.0;

  //Auger
  profile.augerRPM = 0.0;

  //Outfeed
  profile.outfeedRPM = 0;



  //Soak Time
  profile.soakTime = 8.0;// minutes for barrel to remain at set point before extruding

  //heat Zones
  profile.zone1InitialSetTemp = 0.0;
  profile.zone2InitialSetTemp = 0.0;
  profile.zone3InitialSetTemp = 0.0;
  profile.zone4InitialSetTemp = 0.0;
  profile.zone5InitialSetTemp = 0.0;
  
  profile.zone1SetTemp = 0.0;
  profile.zone2SetTemp = 0.0;
  profile.zone3SetTemp = 0.0;
  profile.zone4SetTemp = 0.0;
  profile.zone5SetTemp = 0.0;

  //Safety parameters
  profile.minExtrudeTemp = 180; //The minimum temp allowed for extrusion
  profile.maxTemp = 285; //The max temp allowed for any heating zone
  profile.maxPreheatTime = 15; // The max number of minutes allowed for the preheat state.
}


void Configuration::loadDefaultConfig()
{

  //load the physical with the default parameters.
  //EEPROM storage
  physical.loadAutomatically = false;

  //StarveFeeder
  physical.starveFeederSlaveAddress = 2;
  physical.starveFeederLumpMass = 1.00;
  physical.starveFeederHomePosition = 100;
  physical.starveFeederDumpPosition = 1600;
  physical.starveFeederStepDelay = 75;
  physical.starveFeederHomingStepDelay = 2000;
  physical.starveFeederOverRotation = 90;
  physical.starveFeederDirection = 1;
  physical.starveFeederVibDutyCycle = 95;
  physical.starveFeederStartupDutyCycle = 110;
  physical.starveFeederMaxDutyCycle = 160;
  physical.starveFeederMinFillTime = 1000;
  physical.starveFeederMaxFillTime = 10000;
  physical.starveFeederStartupTime = 200;
  physical.starveFeederDebounceTime = 80;


  //auger
  physical.augerPinSet = 0;
  physical.augerStepMode = 8;
  physical.augerDirection = 1;
  physical.augerEnable = 1;
  physical.augerGearRatio = 3.0;

  //Outfeed
  physical.outfeedPinSet = 1;
  physical.outfeedStepMode = 16;
  physical.outfeedDirection = 0;
  physical.outfeedEnable = 0;
  physical.outfeedRollerRadius = 72.13; //
  physical.outfeedMaxRPM = 200.0;
  physical.outfeedMinRPM = 0.0;

  //Spooler
  physical.spoolerPinSet = 2;
  physical.spoolerStepMode = 16;
  physical.spoolerDirection = 0;
  physical.spoolerEnable = 0;
  physical.spoolerDiskRadius = 20.53; //Estimated radius of big wheel roller//Radius of wooden disk relative to motor roller radius
  physical.spoolerCoreRadius = 30.0; //Radius of spool core
  physical.spoolerTraverseLength = 75.00;
  physical.spoolerMotorRollerRadius = 20.34/2;//relative to wooden disk radius

  //Zone 1 heater
#ifdef OLD_PINS
  physical.zone1.heaterPin = 7;
#else  
  physical.zone1.heaterPin = 12;
#endif
  physical.zone1.Kd = 0.0;
  physical.zone1.Ki = 0.15;
  physical.zone1.Kp = 3.4;
  physical.zone1.maxDutyCycle = 100;
  physical.zone1.minDutyCycle = 0;
  physical.zone1.thermistorBCoefficient = 3950;
  physical.zone1.thermistorNumSamples = 20;
  physical.zone1.thermistorPin = 1;
  physical.zone1.thermistorRNom = 100000;
  physical.zone1.thermistorSeriesResistor = 1000;
  physical.zone1.timeBase = 2000;
  physical.zone1.setTemp = 0.0;
  physical.zone1.PWM = false;
  physical.zone1.activeCooling = false;

  //Zone 2 heater
#ifdef OLD_PINS
  physical.zone2.heaterPin = 2;
#else  
  physical.zone2.heaterPin = 11;
#endif
  physical.zone2.Kd = 0.0;
  physical.zone2.Ki = 0.15;
  physical.zone2.Kp = 3.4;
  physical.zone2.maxDutyCycle = 100;
  physical.zone2.minDutyCycle = 0;
  physical.zone2.thermistorBCoefficient = 3950;
  physical.zone2.thermistorNumSamples = 20;
  physical.zone2.thermistorPin = 2;
  physical.zone2.thermistorRNom = 100000;
  physical.zone2.thermistorSeriesResistor = 1000;
  physical.zone2.timeBase = 2000;
  physical.zone2.setTemp = 0.0;
  physical.zone2.PWM = false;
  physical.zone2.activeCooling = false;

  //Zone 3 heater
#ifdef OLD_PINS
  physical.zone3.heaterPin = 3;
#else  
  physical.zone3.heaterPin = 10;
#endif
  physical.zone3.heaterPin = 10;//Was D3
  physical.zone3.Kd = 0.0;
  physical.zone3.Ki = 0.15;
  physical.zone3.Kp = 3.4;
  physical.zone3.maxDutyCycle = 255;
  physical.zone3.minDutyCycle = 0;
  physical.zone3.thermistorBCoefficient = 3950;
  physical.zone3.thermistorNumSamples = 20;
  physical.zone3.thermistorPin = 3;
  physical.zone3.thermistorRNom = 100000;
  physical.zone3.thermistorSeriesResistor = 1000;
  physical.zone3.timeBase = 2000;
  physical.zone3.setTemp = 0.0;
  physical.zone3.PWM = true;
  physical.zone3.activeCooling = false;

  //Zone 4 heater
#ifdef OLD_PINS
  physical.zone4.heaterPin = 4;
#else  
  physical.zone4.heaterPin = 9;
#endif
  physical.zone4.Kd = 0.0;
  physical.zone4.Ki = 0.15;
  physical.zone4.Kp = 3.4;
  physical.zone4.maxDutyCycle = 255;
  physical.zone4.minDutyCycle = 4;
  physical.zone4.thermistorBCoefficient = 3950;
  physical.zone4.thermistorNumSamples = 20;
  physical.zone4.thermistorPin = 4;
  physical.zone4.thermistorRNom = 100000;
  physical.zone4.thermistorSeriesResistor = 1000;
  physical.zone4.timeBase = 2000;
  physical.zone4.setTemp = 0.0;
  physical.zone4.PWM = true;
  physical.zone4.activeCooling = false;

  //Zone 5 heater
#ifdef OLD_PINS
  physical.zone5.heaterPin = 5;
#else  
  physical.zone5.heaterPin = 8;
#endif  
  physical.zone5.Kd = 0.0;
  physical.zone5.Ki = 0.15;
  physical.zone5.Kp = 3.4;
  physical.zone5.maxDutyCycle = 255;
  physical.zone5.minDutyCycle = 0;
  physical.zone5.thermistorBCoefficient = 3950;
  physical.zone5.thermistorNumSamples = 20;
  physical.zone5.thermistorPin = 5;
  physical.zone5.thermistorRNom = 100000;
  physical.zone5.thermistorSeriesResistor = 1000;
  physical.zone5.timeBase = 2000;
  physical.zone5.setTemp = 0.0;
  physical.zone5.PWM = true;
  physical.zone5.activeCooling = false;

  //Diameter Sensor
  physical.diaSensorRegMap.s.kp = 10;
  physical.diaSensorRegMap.s.ki = .01;
  physical.diaSensorRegMap.s.kd = 0.0;
  physical.diaSensorRegMap.s.sampleTime = 100;
  physical.diaSensorRegMap.s.mode = 0;//0 is MANUAL and 1 is AUTOMATIC
  physical.diaSensorRegMap.s.laserOn = true;
  physical.diaSensorRegMap.s.outputMin = 0;
  physical.diaSensorRegMap.s.outputMax = 60;
  
  //QC Diameter Sensor
  //Nothing to configure
  
  //Safety Parameters for the different states
  physical.maxTemp = 280;//the max temp any heater is allowed to achieve
  physical.loadFilamentTime = 2; //The number of minutes allowed for loading the filament.

}

Configuration::Configuration()
{
  loadProfileNames();
  loadDefaultConfig();
  //loadConfig();
}


void Configuration::saveConfig()
{
  Serial.println(F("Saving Config."));
  physical.configStored = true;//Make sure that the config is marked as stored
  EEPROM_writeAnything(0, physical); //Write to EEPROM
}


void Configuration::deleteConfig()
{
  physical.configStored = false;//Mark config as not stored
  EEPROM_writeAnything(0, physical.configStored); //Just update the configStored variable the rest is irrelevant
}


void Configuration::loadConfig()
{
  EEPROM_readAnything(0, physical);
}


void Configuration::saveProfile()
{
  EEPROM_writeAnything(calculateOffset(profile.profileNumber), profile);
}

void Configuration::deleteProfile(int profileNum)
{
}

boolean Configuration::loadProfile(int profileNum)
{
  EEPROM_readAnything(calculateOffset(profileNum), profile);
}

int Configuration::calculateOffset(int profileNum)
{
  return sizeof(PhysicalConfig) + profileNum * sizeof(Profile); //Will padding in the struct cause problems with this?
}

void Configuration::loadProfileName(char* namePtr, int profile) {
  EEPROM_readAnything(calculateOffset(profile), tempProfile);
  strcpy(namePtr, tempProfile.name);
}

void Configuration::loadProfileNames() {
  for (int i = 0; i < 10; i++) {
    loadProfileName(profileNames[i], i);
  }
}
