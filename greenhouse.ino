#include "AppStat.h"

int tempSensorValue = 0;

//TMP36 Pin Variables
const int tempPin = A4;        //the analog pin the TMP36's Vout (sense) pin is connected to
const int tempPwr = D6;        //Set a digital pin high to provide steady power supply to the temperature sensor.
const int pinRelay1 = D3;
const int pinRelay2 = D4;

                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
int tempReading;        // the analog reading from the sensor
double tempC = 0;
double tempF = 0;

// Values to determine the temperature raing for the device attached to relay #1.
int relay1High = 60; 
int relay1Low = 40;  

// Values to determine the temperature raing for the device attached to relay #2.
int relay2High = 90;
int relay2Low = 70;

//Values that hold the current state of the relays
int relay1State = 0;
int relay2State = 0;


//Set functions to adjust relay temperature ranges.
int SetRelay1High(String value)
{
    relay1High = atoi(value);
    EEPROM.put(10, relay1High);
    return 0;
}
int SetRelay1Low(String value)
{
    relay1Low = atoi(value);
    EEPROM.put(20, relay1Low);
    return 0;
}
int SetRelay2High(String value)
{
    relay2High = atoi(value);
    EEPROM.put(30, relay2High);
    return 0;
}
int SetRelay2Low(String value)
{
    relay2Low = atoi(value);
    EEPROM.put(40, relay2Low);
    return 0;
}


void setup() 
{
    //Call to handle the standard stuff.
    AppStat::GetInstance().setup();
    
    //Setup pins.
    pinMode(tempPin,INPUT);
    pinMode(pinRelay1,OUTPUT);
    pinMode(pinRelay2,OUTPUT);
    
    //This is the pin that will supply the temperature sensor power.
    pinMode(tempPwr,OUTPUT);
    digitalWrite(tempPwr, HIGH);
    
    //Variable that will report the temperature.
    Particle.variable("tempC", &tempC, DOUBLE);
    Particle.variable("tempF", &tempF, DOUBLE);

    //Variable that will report the temperature ranges for the 2 relays.
    Particle.variable("Relay1High", &relay1High, INT);
    Particle.variable("Relay1Low", &relay1Low, INT);
    Particle.variable("Relay2High", &relay2High, INT);
    Particle.variable("Relay2Low", &relay2Low, INT);
    
    //Reports the current status of each relay.
    Particle.variable("Relay1State", &relay1State, INT);
    Particle.variable("Relay2State", &relay2State, INT);
    
    
    //Register functions for remote access with the cloud.
    Particle.function("SetR1High", SetRelay1High);
    Particle.function("SetR1Low", SetRelay1Low);
    Particle.function("SetR2High", SetRelay2High);
    Particle.function("SetR2Low", SetRelay2Low);

    //Grab previously saved data from the EPROM
    EEPROM.get(10, relay1High);
    EEPROM.get(20, relay1Low);
    EEPROM.get(30, relay2High);
    EEPROM.get(40, relay2Low);
    
}
 
void loop() 
{
    //Call to handle the standard stuff.
    AppStat::GetInstance().loop();
    
    //Read the raw analog value from the TMP36 sensor.
    tempSensorValue = analogRead(tempPin);  
 
    //Convert the reading into degree celcius
    tempC = (((tempSensorValue * 3.3)/4095) - 0.5) * 100;
    tempF = (tempC * 9.0/5.0) + 32.0;

    //Check to see if relay 1 needs to be toggled.
    if(tempF < relay1Low)
    {
        digitalWrite(pinRelay1, HIGH);
        relay1State = 1;
    }
    else if(tempF > relay1High)
    {
        digitalWrite(pinRelay1, LOW);
        relay1State = 0;
    }

    //Check to see if relay 2 needs to be toggled.
    if(tempF > relay2High)
    {
        digitalWrite(pinRelay2, HIGH);
        relay2State = 1;
    }
    else if(tempF < relay2Low)
    {
        digitalWrite(pinRelay2, LOW);
        relay2State = 0;
    }

    delay(1000);
}