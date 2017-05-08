/* Roseanne Wakely 7/5/2017:
 *  
 *  This code is a mix of the AdaFruit BNO055 example code, the Arduino cap sense libary code, and some code from Digital Electronics class. 
 *  
 *  This codes function is to read the data from an Ada Fruit BNO055 accelerometer and two capacitive sensors and feed them to the serial port. 
 *  This code is designed to fuction with a processing sketch that takes that data and turns it into beutiful music. 
 *  
 *  The sensors are all mounted onto a hat which makes music as the user moves and touches the capacitive sensors.  
 *  
 *  
 *  
 *  
 */




// This part of the code is from the Arduino Cap sense libary:*************************************************************************************************************

#include <CapacitiveSensor.h>
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // The capacitive sensors are on pins 4 and 2, and 8 and 6. 
CapacitiveSensor   cs_8_6 = CapacitiveSensor(8,6);        // 

//**************************************************************************************************************************************************************************


// The following code is from the Adafruit BNO055 example. Allot of the start up for this sensor is just to show its working properly. It prints all the details of how the sensor is functioning. 
// 




#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

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
#define BNO055_SAMPLERATE_DELAY_MS (10)

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

*/
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Optional: Display current status */
  displaySensorStatus();

  bno.setExtCrystalUse(true);


// cap sense code:****************************************************************************************************************************************************

  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 -





}




void loop(void)
{


// acelometer code *******************************************************************************************************************************************************

// This is the most important part of the code for me. This is where the arduino sends the data to the serial port. 


  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
 // Serial.print("X: ");
  Serial.print(event.orientation.x, 0);
  Serial.print("\t");
  Serial.print(event.orientation.y, 0);
  Serial.print("\t");
  Serial.print(event.orientation.z, 0);
    Serial.print("\t");

  
  
  

 //VV This is more data I could print from the accelerometer, in the future I might add more functions.

  /* Optional: Display calibration status */
 // displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  // displaySensorStatus();



  /* Wait the specified delay before requesting nex data */
  delay(BNO055_SAMPLERATE_DELAY_MS);

  //^^^Some times I use this delay, if the data is too fast. But the cap sensing tends to slow it down a little any way. 
 // In fact the data tended to come in at different rates based on how strong the resistors were on the cap sense! It needed regular fiddling.


// cap code**********************************************VV tbis is the part where I get the cap sense data and print it to serial port. VV

   long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    long total2 =  cs_8_6.capacitiveSensor(30);


    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
  
   
   /* New line for the next sample */
  Serial.println("");   
    
  
  
}
