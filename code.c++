#include <GyverStepper2.h>
#include <FastLED.h>

#define led 6 // кол-во светодиодов в ленте
#define led_pin 5 // пин ленты
CRGB leds[led]; // массив светодиодов

GStepper2< STEPPER4WIRE> stepper(2038, 8, 10, 9, 11); // пины шаговика (8, 10, 9, 11)
int pin_pot = A1; // пин потенциометра

void setup()
{ 
  FastLED.addLeds<WS2812, led_pin, BGR>(leds, led); // инициализация
  FastLED.setBrightness(255); // яркость ленты

  stepper.setSpeedDeg(90); // скорость шаговика в градусах/в сек.
}

unsigned long tmr; // переменная для millis

void loop()
{
  int pot = analogRead(pin_pot); // чтение потенциометра
  pot = map(pot, 0, 1024, 0, 255); // преобразование из 1024 в 255

  stepper.tick(); // движение шаговика

  if (millis() - tmr >= 2) {
    tmr = millis();
    for(int i=0; i<=led; i++)
    {
      leds[i].setHue(pot);
    }
    FastLED.show();
  }
}
