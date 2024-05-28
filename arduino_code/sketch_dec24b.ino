// <-- БИБЛИОТЕКИ и ПЕРЕМЕННЫЕ -->

#include <FastLED.h>
#include <GyverEncoder.h>

#define led 10 
#define pin_leds 6
CRGB leds[led];

#define enc_left A0
#define enc_right A1
#define enc_but 7
Encoder enc(enc_left, enc_right, enc_but);

byte randow;
byte bright = 255;
byte color = 0;

// <-- РЕЖИМ ПРИВЕТСТВИЯ --> 

void start_led()
{
  for(int i=0; i<=led; i++)
  {
    leds[i] = CRGB::White;
    delay(100);
    FastLED.show();
  }

  delay(1000);

  for(int i=0; i<=led; i++)
  {
    leds[i] = CRGB::Black;
    delay(100);
    FastLED.show();
  }
}

// <-- НАСТРОЙКА --> 

void setup()
{
  Serial.begin(9600);
  
  FastLED.addLeds<WS2812, pin_leds, BGR>(leds, led);
  FastLED.setBrightness(bright);

  enc.setType(TYPE2);
  
  start_led();
}

// <-- ОПРОСЫ --> 

void loop()
{
  enc.tick();

  if(enc.isRight())
  {
    for(int i=0; i<=led; i++)
    {
      color+=10;
      leds[i].setHue(color);
    }     
    FastLED.show();
  }

  else if(enc.isLeft())
  {
    for(int i=led; i>=led; i--)
    {
      color-=10;
      leds[i].setHue(color);
    }     
    FastLED.show();
  }

  else if(enc.isFastR())
  {
    for(int i=0; i<=led; i++)
    {
      color+=30;
      leds[i].setHue(color);
    }     
    FastLED.show();
  }

  else if(enc.isFastL())
  {
    for(int i=led; i>=led; i--)
    {
      color-=30;
      leds[i].setHue(color);
    }     
    FastLED.show();
  }

  else if(enc.isRightH())
  {
    bright+=15;
    FastLED.setBrightness(bright);
  }

  else if(enc.isLeftH())
  {
    bright-=15;
    FastLED.setBrightness(bright);
  }
}








