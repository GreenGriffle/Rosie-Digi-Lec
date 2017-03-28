###This is a really handy link on capacity sensing. 

http://www.instructables.com/id/How-To-Use-Touch-Sensors-With-Arduino/

###Info on Resistor Choice:

Here are some guidelines for resistors but be sure to experiment for a desired response.

Use a 1 megohm resistor (or less maybe) for absolute touch to activate.
With a 10 megohm resistor the sensor will start to respond 4-6 inches away.
With a 40 megohm resistor the sensor will start to respond 12-24 inches away (dependent on the foil size). Common resistor sizes usually end at 10 megohm so you may have to solder four 10 megohm resistors end to end.
One tradeoff with larger resistors is that the sensor's increased sensitivity means that it is slower. Also if the sensor is exposed metal, it is possible that the send pin will never be able to force a change in the receive (sensor) pin, and the sensor will timeout.
Also experiment with small capacitors (100 pF - .01 uF) to ground, on the sense pin. They improve stability of the sensor.
Note that the hardware can be set up with one sPin and several resistors and rPin's for calls to various capacitive sensors. See the example sketch.

###I Found the singing plant how to:

http://www.instructables.com/id/Singing-plant-Make-your-plant-sing-with-Arduino-/

###It relies on a home made "Touche Sheild" that was originally made by Disney

http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/
