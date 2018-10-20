#include             <ESP8266WiFi.h>
#include "FastLED.h"
#define NUM_LEDS 10
CRGB leds[NUM_LEDS];
void setup() 
{
  FastLED.addLeds<NEOPIXEL, 0>(leds, NUM_LEDS); 
  
  Serial.begin(9600);
  Serial.println("test");          
}
int Red=0;   
int Green=0;
int Blue=0;
void fadeColor(int R,int G,int B)
{
  while((R!=Red)||(G!=Green)||(B!=Blue)){
    if(R<Red)
    Red=Red-1;
    else if (R>Red)
    Red=Red+1;
    if(G<Green)
    Green=Green-1;
    else if (G>Green)
    Green=Green+1;
    if(B<Blue)
    Blue=Blue-1;
    else if (B>Blue)
    Blue=Blue+1;
    stripeColor(Red,Green,Blue);
    delay(1);
    }
  }
void loop() 
{
fadeColor(255,0,0);
fadeColor(0,255,0);
fadeColor(0,0,255);
fadeColor(255,0,255);
fadeColor(0,255,255);
fadeColor(255,255,0);

}

void stripeColor(int R,int G,int B)
{
    int i;
 for(i=0;i<NUM_LEDS;i++)
    {
      leds[i] = CRGB(R,G,B);
    }
    FastLED.show();
}
