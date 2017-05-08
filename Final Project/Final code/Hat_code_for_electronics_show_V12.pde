/**
 Roseanne Wakely 07/05/17
 
 This is a mix of a minim example created by Damien Di Fede, the drum beat example from minim, and an example of using minim from arduino from digital electronics class. 
 
 
 */

// This is for the serial port. 
import processing.serial.*;    // Serial port for communication with Arduino
Serial myPort;     


import ddf.minim.*;
import ddf.minim.signals.*;  // Minim library that provides sine wave
import ddf.minim.spi.*; // for AudioRecordingStream
import ddf.minim.ugens.*; // this is to do with making generator sounds. Or replicating generators.
import processing.opengl.*;

// declare everything we need to play our file
Minim minim;
FilePlayer filePlayer; // This is for the MP3 track.
AudioOutput out;    // Its really important to declare where you want the mucic to go. In this case, out the laptop speakers. 
// vv this is for the drums. I used "sampler" as this allows for really quick repeat plays, and you can play more than one at a time. Like a drum machine. 

Sampler kick;
Sampler snare;
Sampler hat;
Sampler cowbell;
Sampler horn;
Sampler twang;

float freq;           // sine wave frequency. Making a sine wave is different from playing a sample or track. Minim is actualy creating the sound live using the data. 
float amp;            // sine wave amplitude
SineWave sine;        // a function to generate the values of a sine wave

// The following boolean's were created so that when you stand with your head in one place the sample does not just play again and again and again. 

boolean hatPlayed = false;
boolean hornPlayed = false;
boolean cowbellPlayed = false;
boolean kickPlayed = false;
boolean snarePlayed = false;
boolean twangPlayed = false;


// this is the track processing will play when triggered by movment in the X plane.

String fileName = "Wintergatan.mp3";

void setup()
{


  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');

  // setup the size of the app
  size(640, 240);

  // create our Minim object for loading audio
  minim = new Minim(this);

  out = minim.getLineOut(Minim.STEREO);  

  // This is for creating a new Sine wave. 

  sine = new SineWave(440, 0.5, out.sampleRate()); 

  // This is for loading the MP3

  filePlayer = new FilePlayer( minim.loadFileStream(fileName) );

  sine.portamento(200); // sneeky bit of smoothing code from Michael's lessons on minim 
  //connect the sine wave generator to my audio output
  out.addSignal(sine);


  //************************************************************************
  // get a line out from Minim. It's important that the file is the same audio format 
  // as our output (i.e. same sample rate, number of channels, etc).

  out = minim.getLineOut();

  // patch the file player to the output
  filePlayer.patch(out);
  kick  = new Sampler( "BD.wav", 7, minim );
  snare = new Sampler( "SD.wav", 7, minim );
  hat   = new Sampler( "CHH.wav", 7, minim );
  cowbell = new Sampler( "cowbell.aiff", 7, minim );
  horn = new Sampler( "horn.wav", 7, minim );
  twang = new Sampler( "twang.wav", 7, minim );

  // patch samplers to the output
  kick.patch( out );
  snare.patch( out );
  hat.patch( out );
  cowbell.patch( out );
  horn.patch( out );
  twang.patch( out );
}

// keyPressed is called whenever a key on the keyboard is pressed. This is for deBugging. This is the code I wrote before adding the sensor data, but I keep it so I can 
// continue to test the sounds idependantly. 


void keyPressed()
{
  if ( key == 'a' ) {  
    hat.trigger();
  }
  if ( key == 's' ) {  
    kick.trigger();
  }
  if ( key == 'd' ) {  
    snare.trigger();
  }
  if ( key == 'z' ) {  
    cowbell.trigger();
  }
  if ( key == 'x' ) {  
    horn.trigger();
  }
  if ( key == 'c' ) {  
    twang.trigger();
  }
}



// draw is run many times
void draw()
{

  
  // I leanrt that this is a better way of creating the sound. The sounds are being created here in the Draw loop. The data that feeds into the viariables "Freq" and 
  // "amp" are being collected further down, but this is where the action is. 
  
  // In future iterations I might move all the code for the sounds being triggered into the draw loop. 
  
  
  sine.setFreq( freq ); // it takes the data from one of the cap sensors and uses it to control the fequency of the sine wave. 
  sine.setAmp( amp );  // it takes the data from one of the cap sensors and uses it to control the amplitude of the sine wave. 
  // println(freq + ',' + amp);

// the following just drawers the sign wave of the sounds that are being created. This was really helpful visual for debugging and testing. 

  // erase the window to black
  background( 0 );
  // draw using a white stroke
  stroke( 255 );
  // draw the waveforms
  for ( int i = 0; i < out.bufferSize() - 1; i++ )
  {
    // find the x position of each buffer value
    float x1  =  map( i, 0, out.bufferSize(), 0, width );
    float x2  =  map( i+1, 0, out.bufferSize(), 0, width );
    // draw a line from one buffer position to the next for both channels
    line( x1, 50 + out.left.get(i)*50, x2, 50 + out.left.get(i+1)*50);
    line( x1, 150 + out.right.get(i)*50, x2, 150 + out.right.get(i+1)*50);
  }  

  float songPos = map( filePlayer.position(), 0, filePlayer.length(), 0, width );

  stroke( 255, 0, 0 );
  line( songPos, 0, songPos, height );

  text( "loopCount: " + filePlayer.loopCount(), 15, 15 );
}

// The following is where processing takes in the serial port data, cleans it up, and uses it to make music. 

void serialEvent (Serial myPort) { // this using an interupt. It pauses the loop, and then returns to it. It is often better to do all actions in the loop. 
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    //   println(inString);
    // trim off any whitespace:
    inString = trim(inString);
    // split the input string at the commas
    // and convert the sections into integers:
    int sensors[] = int(split(inString, '\t'));

    // if we have received all the sensor values, use them:
    if (sensors.length == 5) {

      println(sensors[0], sensors[1], sensors[2], sensors[3], sensors[4]);


/* 

   Sensor 0 - 2 = accelerometer data. 
   
     sensor 0 = X orientation. (turning around)
     sensor 1 = head noding 
     sensor 2 = head tilting side to side. 
   
   Sensor 3 + 4 = Cap sense data

*/

// this maps the cap sense data into some thing useful. 

      amp = map(sensors[3], 80, 3000, 0, 1); // this needs to be edited at every new location! Cap sense tends to change. 
      freq = map(sensors[4], 80, 3000, 110, 880);

      
      
      
      // X turning round.  This plays a tune if you turn to face a certain direction. 
      
      if ((sensors[0] > 200) && (sensors[0] <350)) {

        filePlayer.loop();
      }

// The following trigger a drum sound based on head noding or tilting. The Boolean makes sure that they only trigger one time that you are in that spot.

      if ((sensors[2] < -35) && (sensors[2] > -40)) {
        if (!twangPlayed) {
          twang.trigger();
          twangPlayed = true;
        }
      } else {
        twangPlayed = false;
      }



      if ((sensors[1] > 52) && (sensors[1] < 57)) {
        if (!kickPlayed) {
          kick.trigger();
          kickPlayed = true;
        }
      } else { 
        kickPlayed = false;
      }

      if ((sensors[1] <= -29) && (sensors[1] >= -34)) {
        if (!snarePlayed) {
          snare.trigger();
          snarePlayed = true;
        }
      } else {
        snarePlayed = false;
      }



      if ((sensors[2] > 34) && (sensors[2] <39)) {
        if (!cowbellPlayed) {
          cowbell.trigger();
          cowbellPlayed = true;
        }
      } else {
        cowbellPlayed = false;
      }

      if ((sensors[1] < -75) && (sensors[1] >-80)) {
        if (!hornPlayed) {
          horn.trigger();
          hornPlayed = true;
        }
      } else {
        hornPlayed = false;
      }
      if ((sensors[1] >= 15) && (sensors[1] <= 20)) {
        if (!hatPlayed) {
          hat.trigger();
          hatPlayed = true;
        }
      } else {
        hatPlayed = false;
      }
    }
  }
}