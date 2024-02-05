#include <FastLED.h>
#include <GyverEncoder.h>
#include <Stepper.h>

#define led_pin 6
#define led_num 10

#define enc_but 7
#define enc_right 9
#define enc_left 10

byte color = 0;
byte bright = 255;
byte counter;
int speed = 60;
const int stepsPerRevolution = 200;

CRGB leds[led_num];
Encoder enc(enc_but, enc_right, enc_left);
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);


void setup()
{
  Serial.begin(9600);

  myStepper.setSpeed(speed); 
  
  enc.setType(TYPE2);
  enc.setFastTimeout(10);
  
  FastLED.addLeds<WS2812, led_pin, BGR>(leds, led_num);
  FastLED.setBrightness(bright);

  for(int i=0; i<=3; i++)
  {
    for(int i=0; i<=led_num; i++)
    {
      leds[i] = CRGB::White;
      delay(40);
      FastLED.show();
    }
    delay(150);

    for(int i=led_num; i>=0; i--)
    {
      leds[i] = CRGB::Black;
      delay(40);
      FastLED.show();
    }
    delay(150);
  }
}


void encoders()
{
  if(enc.isRight()) color += 10;
  else if(enc.isLeft()) color -= 10;

  if(enc.isFastR()) color += 30;
  else if(enc.isFastL()) color -= 30;

  if(enc.isRightH()){
    bright += 25;
    FastLED.setBrightness(bright);}
  else if(enc.isLeftH()){
    bright -= 25;
    FastLED.setBrightness(bright);}
}



void loop()
{
  enc.tick();

  if(enc.isClick())
  {
    myStepper.step(stepsPerRevolution);
    delay(500);

    encoders();
  }

  else if(enc.isDouble())
  {
    for (int i = 0; i < led_num; i++) 
    {
      leds[i].setHue(counter + i * 255 / led_num);
    }
    counter++;        
    FastLED.show();
    delay(30); 

    encoders();
  }
  encoders();
}