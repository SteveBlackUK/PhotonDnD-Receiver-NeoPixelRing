/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/steve_black_spare/Dropbox/PhotonDnD-Receiver-NeoPixelRing/src/PhotonDnD-Receiver-NeoPixelRing.ino"
/*
 * Project PhotonDnD-Receiver-NeoPixelRing
 * Description:
 * Author:
 * Date:
 */
#include <../lib/neopixel/src/neopixel.h>



 
void setup();
void onHandler(String event, String data);
void onMasterHandler(String event, String data);
void loop();
#line 12 "/Users/steve_black_spare/Dropbox/PhotonDnD-Receiver-NeoPixelRing/src/PhotonDnD-Receiver-NeoPixelRing.ino"
#define PIXEL_COUNT 12// 24 Pixels on our ring
#define PIXEL_PIN D5						// Ring uses D6 as default pin
#define PIXEL_TYPE WS2812B					// Ring uses WS2812 Pixels
 
Adafruit_NeoPixel ring(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);	// Create out “ring” object	
 
int pixelCounter = 0;                       // Used for choosing a specific LED
int toggle = 0;
String memoryState;
bool overrideDisplay = true;


void setup() 
{
    // Start the NeoPixel object
    ring.begin();       
    ring.setBrightness(5);                      	// Turn the brightness way down!!!
    Particle.subscribe("LedOn", onHandler, MY_DEVICES);
    Particle.subscribe("LedOff", onHandler, MY_DEVICES);
    Particle.subscribe("MasterPower", onMasterHandler, MY_DEVICES);

}


void onHandler(String event, String data)
{

    Particle.publish("Inside onHandler", PRIVATE);
    if(data == "on") {
        for(int i = 0; i < PIXEL_COUNT; i ++)
        {
            ring.setPixelColor(i, 0, 220, 0); 
            memoryState = "on";

        }
        
    }
        
    if(data == "off") {
       for(int i = 0; i < PIXEL_COUNT; i ++)
        {
            ring.setPixelColor(i, 220, 0, 0); 
            memoryState = "off";
        } 
    }

     // Update the NeoPixel
    if(overrideDisplay == false) {
            ring.show();     

    }
}  

void onMasterHandler(String event, String data) 
{
    
    if(data == "MasterOn"){
        overrideDisplay = false;
        onHandler("callIt",memoryState);

    }
    
    if(data == "MasterOff") {
        ring.clear();
        ring.show();   
        overrideDisplay = true;

    }
}

 
void loop() 
{
    
    
    // Update the NeoPixel
    // ring.show();        
}