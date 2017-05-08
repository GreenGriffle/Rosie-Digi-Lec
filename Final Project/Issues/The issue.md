I spent a long time trying to get a touche sheild working with music, to be able to get different sorts of touch to be reconised. These are the error messages I got. 

I ended up moving on from this idea, as I could get the sensor working, but I could not make it musical, which defeated the point!





## This is the error I'm getting:


"C:\Users\Owner\Documents\CCA\digital electronics\Musical hat take two\musical plant\singingPlant\Guino_library.ino:13:26: fatal error: EasyTransfer.h: No such file or directory

 #include <EasyTransfer.h>

                          ^

compilation terminated.

Using library SPI at version 1.0 in folder: C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SPI 
Using library Gameduino_midified_to_pin4 in folder: C:\Program Files (x86)\Arduino\libraries\Gameduino_midified_to_pin4 (legacy)
exit status 1
Error compiling for board Arduino/Genuino Uno.




## This is the origonal instrutable:

http://www.instructables.com/id/Singing-plant-Make-your-plant-sing-with-Arduino-/

I already made the glass of water work from his other instrucable. 
I'm pretty sure its a pretty simple libary issue. One person said this would help:

"Hi, try to go in GD.h and move this string: "typedef const unsigned char prog_uchar;"

I've attached a photo of the fix he is suggesting. But I don't have the software to go into GD.h 
I've also attached the code, and the libary. I can't even verify the code at the moment. 
