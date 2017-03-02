#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <CapacitiveSensor.h>
#include "pitches.h"

#define BUZZER_PIN  A0

//const int buttonPin = 9;
//int buttonState = 0;

// VV New code from cap sense

#define COMMON_PIN      2    // The common 'send' pin for all keys

#define NUM_OF_SAMPLES  20   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   50  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS     1    // Number of keys that are on the keyboard

// This macro creates a capacitance "key" sensor object for each key on the piano keyboard:
#define CS(Y) CapacitiveSensor(COMMON_PIN, Y)

// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
int notes[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5}; // C-Major scale

// Defines the pins that the keys are connected to:
CapacitiveSensor keys[] = {CS(3) };


/* Roseanne Wakely: I combined the Arduino Example "Button" from basics to use a button.
  I combined that with " Capacitive-Touch Arduino Keyboard Piano"  by Tyler Crumpton and Nicholas Jones
  which can be found here: This code is released to the public domain. For information about the circuit,
  visit the Instructable tutorial at http://www.instructables.com/id/Capacitive-Touch-Arduino-Keyboard-Piano/

  This was combined with the Ada fruit example for Adafruit_BNO055 sensor.

  /* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.

   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3-5V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
   2015/AUG/27  - Added calibration and system status helpers
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

/**************************************************************************/
/*
    Display some basic info about the sensor status
*/
/**************************************************************************/
void displaySensorStatus(void)
{
  /* Get the system status values (mostly for debugging purposes) */
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  bno.getSystemStatus(&system_status, &self_test_results, &system_error);

  /* Display the results in the Serial Monitor */
  Serial.println("");
  Serial.print("System Status: 0x");
  Serial.println(system_status, HEX);
  Serial.print("Self Test:     0x");
  Serial.println(self_test_results, HEX);
  Serial.print("System Error:  0x");
  Serial.println(system_error, HEX);
  Serial.println("");
  delay(500);
}

/**************************************************************************/
/*
    Display sensor calibration status
*/
/**************************************************************************/
void displayCalStatus(void)
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  Serial.print("\t");
  if (!system)
  {
    Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.print(mag, DEC);
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  //vv new cap code
  for (int i = 0; i < NUM_OF_KEYS; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }

  // ^^


  // pinMode(buttonPin, INPUT);

  pinMode (8, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);


  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Optional: Display current status */
  displaySensorStatus();

  bno.setExtCrystalUse(true);
  pinMode(BUZZER_PIN, OUTPUT);
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{



  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  Serial.print("\tX: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);

  //I bet the 4 means to 4 desimal places.

  /* Optional: Display calibration status */
  displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  //displaySensorStatus();

  /* New line for the next sample */
  Serial.println("");

  /* Wait the specified delay before requesting nex data */
  delay(BNO055_SAMPLERATE_DELAY_MS);

  //buttonState = digitalRead(buttonPin);

  boolean silence = true;

  /* I learnt that you can't just break a circit for it to act like a switch, it has to
      return either a low or high voltage.
  */

  // Loop through each key:
  for (int i = 0; i < NUM_OF_KEYS; ++i) {

    // If the capacitance reading is greater than the threshold, :

    Serial.print("Cap Sense: ");
    Serial.print(keys[i].capacitiveSensor(NUM_OF_SAMPLES));

    if (keys[i].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {

      if (event.orientation.y > 40) {
        tone (BUZZER_PIN, NOTE_G3);
        digitalWrite(6, HIGH);
        silence = false;
      } else {
        digitalWrite(6, LOW);
      }
      if (event.orientation.x > 200) {
        tone (BUZZER_PIN, NOTE_A3);
        digitalWrite(7, HIGH);
        silence = false;
      } else {
        digitalWrite(7, LOW);
      }
      if (event.orientation.z > 40) {
        tone (BUZZER_PIN, NOTE_B3);
        digitalWrite(8, HIGH);
        silence = false;
      } else {
        digitalWrite(8, LOW);
      }
      if (silence == true) {
        noTone(BUZZER_PIN);
      }
    }
    else {
      noTone(BUZZER_PIN);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      
    }



  }


}




