/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/steve_black_spare/Dropbox/PhotonDnD-Receiver-NeoPixelRing/src/PhotonDnD-Receiver-NeoPixelRing.ino"
/*
 * Project PhotonDnD-Receiver-NeoPixelRing
 * Description: 
 * Author: Steve Black
 * Date:
 */

#include <../lib/neopixel/src/neopixel.h>
 
void setup();
void onHandler(String event, String data);
void onMasterHandler(String event, String data);
void loop();
#line 10 "/Users/steve_black_spare/Dropbox/PhotonDnD-Receiver-NeoPixelRing/src/PhotonDnD-Receiver-NeoPixelRing.ino"
#define PIXEL_COUNT 12// 24 Pixels on our ring
#define PIXEL_PIN D5						// Ring uses D5 as default pin
#define PIXEL_TYPE WS2812B					// Ring uses WS2812 Pixels
 
Adafruit_NeoPixel ring(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);	// Create our “ring” object	
 
int pixelCounter = 0;  // Can be used for choosing a specific LED in the ring
int toggle = 0;
String memoryState;
bool overrideDisplay = true;


void setup() 
{
    // Start the NeoPixel object
    ring.begin();       
    ring.setBrightness(5);                      	// Turn the brightness way down!!!
    Particle.subscribe("LedColor", onHandler, MY_DEVICES);
    Particle.subscribe("MasterPower", onMasterHandler, MY_DEVICES);
}


void onHandler(String event, String data)
{
    if(data == "green") {
        for(int i = 0; i < PIXEL_COUNT; i ++)
        {
            ring.setPixelColor(i, 0, 220, 0); 
            memoryState = "green";  // save the colour so that when the user turns master status back to 'on' we know what colour to resume to
        }
        
    }
        
    if(data == "red") {
       for(int i = 0; i < PIXEL_COUNT; i ++)
        {
            ring.setPixelColor(i, 220, 0, 0); 
            memoryState = "red";
        } 
    }

     // Update the NeoPixel only if power is on
    if(overrideDisplay == false) {
            ring.show();     
    }
}  

//used where we have a switch that overrides colours and sets a master on/off event
void onMasterHandler(String event, String data) 
{
    if(data == "MasterOn"){
        overrideDisplay = false;
        onHandler("callIt",memoryState);
    }
    
    if(data == "MasterOff") {
        //clear the colour and update the NeoPixel
        ring.clear();
        ring.show();   
        overrideDisplay = true;
    }
}

 
void loop() 
{
    //nothing needed here as it only acts on events it has suscribed to      
}