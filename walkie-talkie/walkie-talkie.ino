#include <RF24.h>
#include <SPI.h>
#include <RF24Audio.h>

RF24 radio(7,8);
RF24Audio rfAudio(radio,1);	

void setup() {			
  rfAudio.begin();		// The only thing to do is initialize the library.

}

void loop() {
  
}
