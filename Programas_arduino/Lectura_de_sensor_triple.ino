/*
  Read the 18 channels of spectral light over I2C using the Spectral Triad
  By: Nathan Seidle
  SparkFun Electronics
  Date: October 25th, 2018
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example takes all 18 readings, 372nm to 966nm, over I2C and outputs
  them to the serial port.
  
  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/15050

  Hardware Connections:
  Plug a Qwiic cable into the Spectral Triad and a BlackBoard
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic Breadboard Jumper (https://www.sparkfun.com/products/14425)
  Open the serial monitor at 115200 baud to see the output
*/

#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;

int led = -1;

void setup()
{
  Serial.begin(115200);
  //Serial.println("AS7265x Spectral Triad Example");

  if (sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while (1)
      ;
  }
  Wire.setClock(400000);
  sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_100MA, AS7265x_LED_WHITE);
  sensor.setGain(AS7265X_GAIN_64X);
  sensor.setIntegrationCycles(187);
  sensor.disableIndicator();

  //Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W,K,L");
}

void loop()
{
  while (Serial.available() == false)
  {
  }              //Do nothing while we wait for user to press a key
  Serial.read(); //Throw away the user's button
  led++;
  if(!led == 0){
    sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_100MA, AS7265x_LED_WHITE); //This is a hard wait while all 18 channels are measured
  }
  if(led == 1)
  {
    sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_50MA, AS7265x_LED_WHITE); //This is a hard wait while all 18 channels are measured
  }
  if(led == 2)
  {
    sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_25MA, AS7265x_LED_WHITE); //This is a hard wait while all 18 channels are measured
  }
  if(led == 3)
  {
    sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_12_5MA, AS7265x_LED_WHITE); //This is a hard wait while all 18 channels are measured
  }
  else{
    led == -1;
  }
  sensor.enableBulb(AS7265x_LED_WHITE);
  sensor.takeMeasurements();
  sensor.disableBulb(AS7265x_LED_WHITE);

  /* Serial.print(sensor.getCalibratedA()); //410nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedB()); //435nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedC()); //460nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedD()); //485nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedE()); //510nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedF()); //535nm
  Serial.print(","); */

  Serial.print(0.0); //410nm
  Serial.print(",");
  Serial.print(0.0); //435nm
  Serial.print(",");
  Serial.print(0.0); //460nm
  Serial.print(",");
  Serial.print(0.0); //485nm
  Serial.print(",");
  Serial.print(0.0); //510nm
  Serial.print(",");
  Serial.print(0.0); //535nm
  Serial.print(",");

  Serial.print(sensor.getCalibratedG()); //560nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedH()); //585nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedR()); //610nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedI()); //645nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedS()); //680nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedJ()); //705nm
  Serial.print(",");

  Serial.print(sensor.getCalibratedT()); //730nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedU()); //760nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedV()); //810nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedW()); //860nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedK()); //900nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedL()); //940nm

  Serial.println();
}
