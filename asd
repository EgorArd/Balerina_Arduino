#include <GyverStepper2.h>
#include <GyverEncoder.h>
#include <FastLED.h>

#define led 14 // кол-во светодиодов в ленте
#define led_pin 6 // пин ленты
CRGB leds[led]; // массив светодиодов

#define right_enc1 A0 
#define left_enc1 A1 
#define button1 2

#define right_enc2 A2 
#define left_enc2 A3 
#define button2 3

Encoder enc1(right_enc1, left_enc1, button1);
Encoder enc2(right_enc2, left_enc2, button2);

GStepper2< STEPPER4WIRE> stepper(2038, 8, 10, 9, 11); // пины шаговика (8, 10, 9, 11)

void setup()
{ 
  FastLED.addLeds<WS2812, led_pin, BGR>(leds, led); // инициализация
  FastLED.setBrightness(255); // яркость ленты
  
  stepper.setSpeedDeg(90); // скорость шаговика в градусах/в сек.

  enc1.setType(TYPE2);
  enc2.setType(TYPE2);
}

unsigned long tmr; // переменная для millis
byte color_rgb = 0;
byte counter;

void rainbow()
{
  for (int i=0; i<led; i++) 
  {
    leds[i].setHue(counter + i * 255 / led);
  }
  counter++;        
  FastLED.show();
  delay(30);        // скорость движения радуги
}



void loop()
{
  enc1.tick();
  enc2.tick();

  stepper.tick(); // движение шаговика

  if(enc1.isRight()) color_rgb+=10;
  else if(enc1.isFastR()) color_rgb+=20;

  else if(enc1.isLeft()) color_rgb-=10;
  else if(enc1.isFastL()) color_rgb-=20;

  if(enc1.isClick()){
    rainbow();
  }

  if (millis() - tmr >= 2) {
    tmr = millis();
    for(int i=0; i<=led; i++)
    {
      leds[i].setHue(color_rgb);
    }
    FastLED.show();
  }
}
