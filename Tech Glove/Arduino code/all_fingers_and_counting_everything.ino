/* How to use a flex sensor/resistro - Arduino Tutorial
   code combined with button from arduino examples.
  This code has been repurposed by ROsie and Iris for making a glove that can
  detect the thumb being touched to each finer.
  With flex sensors to show how close finger is to its goal.
*/
// from button codeVVV:
const int fingSwitch1 = 2;     // the number of the switch on finger one
const int fingSwitch2 = 7;   // switch finger two
const int fingSwitch3 = 8;     //switch finger three
const int fingSwitch4 = 9;     //switch finger four

const int ledTouch1 =  10;     // LED that shows index finger hass been touched With thumb
const int ledTouch2 =  11;   // LED that shows middle finger hass been touched
const int ledTouch3 =  12;   // LED that shows forth finger hass been touched
const int ledTouch4 =  13;  // LED that shows little finger hass been touched

// variables will change:
int fingState1 = 0;         // variable for reading the finger switch status
int fingState2 = 0;
int fingState3 = 0;
int fingState4 = 0;

//counting codeVV
// Finger one
int fingCounter1 = 0; //counts how many times index finger has been pressed.
int lastFingState1 = 0; // previous state of the index finger
int lightMode1 = 0;

//Finger two
int fingCounter2 = 0; //counts how many times index finger has been pressed.
int lastFingState2 = 0; // previous state of the index finger
int lightMode2 = 0;

//Finger three
int fingCounter3 = 0; //counts how many times index finger has been pressed.
int lastFingState3 = 0; // previous state of the index finger
int lightMode3 = 0;

//Finger four
int fingCounter4 = 0; //counts how many times index finger has been pressed.
int lastFingState4 = 0; // previous state of the index finger
int lightMode4 = 0;


// from flex sensor codeVV

//Constants:
const int ledPin = 3;   //
const int ledPin2 = 4;
const int ledPin3 = 5;
const int ledPin4 = 6;



const int flexPin = A0; //pin A0 to read analog input

//Variables:
int value; //save analog value


void setup() {


  // from buttonVV
  // initialize the LEDs that show when finger touchedn as an output:
  pinMode(ledTouch1, OUTPUT);
  pinMode(ledTouch2, OUTPUT);
  pinMode(ledTouch3, OUTPUT);
  pinMode(ledTouch4, OUTPUT);




  // initialize the pushbutton pin as an input:
  pinMode(fingSwitch1, INPUT);
  pinMode(fingSwitch2, INPUT);
  pinMode(fingSwitch3, INPUT);
  pinMode(fingSwitch4, INPUT);


  //from Flex codeVV

  pinMode(ledPin, OUTPUT);  //Set pin 3 as 'output'
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  Serial.begin(9600);       //Begin serial communication

}

void loop() {

  //from button VV
  //re mixed for counting.

  fingState1 = digitalRead(fingSwitch1);
  if (fingState1 != lastFingState1) { // // if the state has changed, increment the counter
    if (fingState1 == HIGH) { // if the current state is HIGH then the button
      // went from off to on:
      fingCounter1++;
      //delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastFingState1 = fingState1;
  }

  // VV same for other
  //fingers:

  fingState2 = digitalRead(fingSwitch2);
  if (fingState2 != lastFingState2) { // // if the state has changed, increment the counter
    if (fingState2 == HIGH) { // if the current state is HIGH then the button
      // went from off to on:
      fingCounter2++;
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastFingState2 = fingState2;
  }

  fingState3 = digitalRead(fingSwitch3);
  if (fingState3 != lastFingState3) { // // if the state has changed, increment the counter
    if (fingState3 == HIGH) { // if the current state is HIGH then the button
      // went from off to on:
      fingCounter3++;
      // delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastFingState3 = fingState3;
  }





  fingState4 = digitalRead(fingSwitch4);
  if (fingState4 != lastFingState4) { // // if the state has changed, increment the counter
    if (fingState4 == HIGH) { // if the current state is HIGH then the button
      // went from off to on:
      fingCounter4++;
      // delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastFingState4 = fingState4;
  }





  //from flexVV

  value = analogRead(flexPin);         //Read and save analog value from potentiometer
  Serial.print(value);    //Print value
  Serial.print ("\t");
  Serial.print(fingCounter1);
  Serial.print ("\t");
  Serial.print(fingCounter2);
  Serial.print ("\t");
  Serial.print(fingCounter3);
  Serial.print ("\t");
  Serial.println(fingCounter4);

  if (value <= 966) {
    digitalWrite (ledPin, HIGH);
  }
  else {
    digitalWrite (ledPin, LOW);
  }
  if ((value >= 967) && (value <= 986)) {
    digitalWrite (ledPin2, HIGH);
  }
  else {
    digitalWrite (ledPin2, LOW);
  }

  if ((value >= 987) && (value <= 999)) {
    digitalWrite (ledPin3, HIGH);
  }
  else {
    digitalWrite (ledPin3, LOW);
  }

  if ((value >= 1000) && (value <= 1008)) {
    digitalWrite (ledPin4, HIGH);
  }
  else {
    digitalWrite (ledPin4, LOW);
  }

  // finger one

  if (fingCounter1 < 10) {
    lightMode1 = 0;
  } else {
    lightMode1 = 1;
  }
  if (lightMode1 == 0) {
    fingState1 = digitalRead(fingSwitch1);
    if (fingState1 == HIGH) {
      // turn LED on:
      digitalWrite(ledTouch1, HIGH);
    } else {
      // turn LED off:
      digitalWrite(ledTouch1, LOW);
    }
  }
  if (lightMode1 == 1) {
    // turn LED on:
    digitalWrite(ledTouch1, HIGH);
  }
  //finger two
  if (fingCounter2 < 10) {
    lightMode2 = 0;
  } else {
    lightMode2 = 1;
  }
  if (lightMode2 == 0) {
    fingState2 = digitalRead(fingSwitch2);
    if (fingState2 == HIGH) {
      // turn LED on:
      digitalWrite(ledTouch2, HIGH);
    } else {
      // turn LED off:
      digitalWrite(ledTouch2, LOW);
    }
  }

  if (lightMode2 == 1) {
    // turn LED on:
    digitalWrite(ledTouch2, HIGH);
  }


  //finger three

  if (fingCounter3 < 10) {
    lightMode3 = 0;
  } else {
    lightMode3 = 1;
  }

  if (lightMode3 == 0) {
    fingState3 = digitalRead(fingSwitch3);
    if (fingState3 == HIGH) {
      // turn LED on:
      digitalWrite(ledTouch3, HIGH);
    } else {
      // turn LED off:
      digitalWrite(ledTouch3, LOW);
    }

  }
  if (lightMode3 == 1) {
    // turn LED on:
    digitalWrite(ledTouch3, HIGH);
  }
  //finger four
  if (fingCounter4 < 10) {
    lightMode4 = 0;
  } else {
    lightMode4 = 1;
  }
  if (lightMode4 == 0) {
    fingState4 = digitalRead(fingSwitch4);
    if (fingState4 == HIGH) {
      // turn LED on:
      digitalWrite(ledTouch4, HIGH);
    } else {
      // turn LED off:
      digitalWrite(ledTouch4, LOW);
    }
  }
  if (lightMode4 == 1) {
    // turn LED on:
    digitalWrite(ledTouch4, HIGH);
  }
}


// if (value > 966
//  value = map(value, 940, 1000, 0, 255);//Map value 0-1023 to 0-255 (PWM)
// analogWrite(ledPin, value);          //Send PWM value to led
//Small delay





