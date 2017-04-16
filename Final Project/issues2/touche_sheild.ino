


//****************************************************************************************
// Illutron take on Disney style capacitive touch sensor using only passives and Arduino
// Dzl 2012
//****************************************************************************************


//                              10n
// PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
//               |            |
//              3.3k          |
//               |            V 1N4148 diode
//              GND           |
//                            |
//Analog 0 ---+------+--------+
//            |      |
//          100pf   1MOmhm
//            |      |
//           GND    GND



#define SET(x,y) (x |=(1<<y))        //-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))           // |
#define CHK(x,y) (x & (1<<y))               // |
#define TOG(x,y) (x^=(1<<y))                //-+



#define N 160  //How many frequencies

float results[N];            //-Filtered result buffer
float freq[N];            //-Filtered result buffer
int sizeOfArray = N;





void setup()
{


  TCCR1A = 0b10000010;      //-Set up frequency generator
  TCCR1B = 0b00011001;      //-+
  ICR1 = 110;
  OCR1A = 55;

  pinMode(9, OUTPUT);       //-Signal generator pin
  pinMode(8, OUTPUT);       //-Sync (test) pin

  Serial.begin(115200);

  for (int i = 0; i < N; i++) //-Preset results
    results[i] = 0;       //-+
}

void loop()
{
  unsigned int d;

  int counter = 0;
  for (unsigned int d = 0; d < N; d++)
  {
    int v = analogRead(0);  //-Read response signal
    CLR(TCCR1B, 0);         //-Stop generator
    TCNT1 = 0;              //-Reload new frequency
    ICR1 = d;               // |
    OCR1A = d / 2;          //-+
    SET(TCCR1B, 0);         //-Restart generator

    results[d] = results[d] * 0.5 + (float)(v) * 0.5; //Filter results . taking average, of current and previous average

    freq[d] = d;

    //   plot(v,0);              //-Display
    //   plot(results[d],1);
    // delayMicroseconds(1);
  }


  PlottArray(1, freq, results);


  TOG(PORTB, 0);           //-Toggle pin 8 after each sweep (good for scope)
}








  byte yMSB = 0, yLSB = 0, xMSB = 0, xLSB = 0, zeroByte = 128, Checksum = 0;

  void SendData(int Command, unsigned int yValue, unsigned int xValue) {



    /* >=================================================================<
        y = 01010100 11010100    (x & y are 2 Byte integers)
             yMSB      yLSB      send seperately -> reciever joins them
      >=================================================================<  */

    yLSB = lowByte(yValue);
    yMSB = highByte(yValue);
    xLSB = lowByte(xValue);
    xMSB = highByte(xValue);


    /* >=================================================================<
       Only the very first Byte may be a zero, this way allows the computer
       to know that if a Byte recieved is a zero it must be the start byte.
       If data bytes actually have a value of zero, They are given the value
       one and the bit in the zeroByte that represents that Byte is made
       high.
       >=================================================================< */

    zeroByte = 128;                                   // 10000000

    if (yLSB == 0) {
      yLSB = 1;  // Make bit 1 high
      zeroByte = zeroByte + 1;
    }
    if (yMSB == 0) {
      yMSB = 1;  // make bit 2 high
      zeroByte = zeroByte + 2;
    }
    if (xLSB == 0) {
      xLSB = 1;  // make bit 3 high
      zeroByte = zeroByte + 4;
    }
    if (xMSB == 0) {
      xMSB = 1;  // make bit 4 high
      zeroByte = zeroByte + 8;
    }


    /* >=================================================================<
       Calculate the remainder of: sum of all the Bytes divided by 255
       >=================================================================< */

    Checksum = (Command + yMSB + yLSB + xMSB + xLSB + zeroByte) % 255;

    if ( Checksum != 0 ) {
      Serial.write(byte(0));            // send start bit
      Serial.write(byte(Command));      // command eg: Which Graph is this data for

      Serial.write(byte(yMSB));         // Y value's most significant byte
      Serial.write(byte(yLSB));         // Y value's least significant byte
      Serial.write(byte(xMSB));         // X value's most significant byte
      Serial.write(byte(xLSB));         // X value's least significant byte

      Serial.write(byte(zeroByte));     // Which values have a zero value
      Serial.write(byte(Checksum));     // Error Checking Byte
    }
  }




  void PlottArray(unsigned int Cmd, float Array1[], float Array2[]) {

    SendData(Cmd + 1, 1, 1);                     // Tell PC an array is about to be sent
    delay(1);
    for (int x = 0;  x < sizeOfArray;  x++) { // Send the arrays
      SendData(Cmd, round(Array1[x]), round(Array2[x]));
      //delay(1);
    }

    SendData(Cmd + 2, 1, 1);                     // Confirm arrrays have been sent
  }







