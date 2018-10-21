#include             <ESP8266WiFi.h>
#include "FastLED.h"
#include <ESP8266HTTPClient.h>
#define NUM_LEDS 10
CRGB leds[NUM_LEDS];
void setup() 
{
  FastLED.addLeds<NEOPIXEL, 0>(leds, NUM_LEDS); 
  
  Serial.begin(9600);
  Serial.println("test");
  WiFi.begin("Jugend hackt legacy");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
          
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
void loop() {
    String redStr;
  String greenStr;
  String blueStr;
  boolean redVal = true,
          greenVal = false,
          blueVal = false;
  int red;
  int green;
  int blue;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://159.69.212.203:8080/data?token=MzMxNzYzNTc1MTYwMDcxMzpkVG5UdXA2NEVDN2pFWTlSRXFHTWhUTlJwb0JCeFpOQWJobkl1SndWakRuM2NGTHREQzpUN2xmM01qUDY0NmxyeHI3cEUzQkpCNmhWTjZieU1uZHpFVXRESVdjRUVHd1ZnVzFrNjp5S25GWXdIUDd0dzdad0VxNDF1dmtlTGZ0ZGhLblY0aXBlZkRzSTNIQ3p0YzM3bTFkWDo5dlF0dDN3aTNSVWl5YXVvRWVuYkV4RW5PUTA5dkVuUnJvbW5OT01BWk5tNWJYYUszVg==");  //Specify request destination
    int httpCode = http.GET(); //Send the request
 
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);  //Print the response payload
       char content[payload.length()];
       payload.toCharArray(content, payload.length()); 
      for(int c;c<payload.length()-1;c++){
        if(isdigit(content[c]) == 1 /*&& !redVal || !greenVal || !blueVal*/){
            if(redVal){
              redStr += (String)content[c];
              if(!(isdigit(content[c+1]) == 1)){
                red = redStr.toInt();
                Serial.println(red);
                redVal = false;
                greenVal = true;    
              }
            }
            else if(greenVal){
              greenStr += (String)content[c];
              if(!(isdigit(content[c+1]) == 1)){
                green = greenStr.toInt();
                Serial.println(green);
                greenVal = false;    
                blueVal = true;
              }
            }
            else if(blueVal){
              blueStr += (String)content[c];
              if(!(isdigit(content[c+1]) == 1)){
                blue= blueStr.toInt();
                Serial.println(blue);
                blueVal = false;    
              }
            }
        }
      }
    }
    
 
    http.end();   //Close connection
   //blinkColor(red,green,blue);
  //rainbow();                                //Die 3 eilen sind für Regenbogen 
  //stripeColor(0,255,0);                     //Wenn sie Gelöscht werden  blint eine Farbe abwechselnd mit schwarz 
  int maxArray[3] = {red, green, blue};
  maxArray[max(maxArray, 0, 2)] = 255;
  fadeColor(maxArray[0],maxArray[1],maxArray[2]);
  }
  delay(10000);
  }

void rainbow()
{
  fadeColor(255,0,0);
  fadeColor(0,255,0);
  fadeColor(0,0,255);
  fadeColor(255,0,255);
  fadeColor(0,255,255);
  fadeColor(255,255,0);
  fadeColor(187,187,187);
  fadeColor(100,0,255);
  fadeColor(98,17,229);
  fadeColor(5,25,40);
  
}

void blinkColor(int R, int G, int B)
{
  fadeColor(R,G,B);
  delay(400);
  fadeColor(0,0,0);
  delay(400);
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
