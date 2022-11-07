#include <Arduino.h>

#define BUTTON_PIN PB8
#define LED_PIN PB1

static int output_pins[] = {LED_PIN /* led pin */, PB3, PB4, PB5};

void setup()
{
  for (int pin : output_pins)
  {
    pinMode(pin, OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT);
}

uint32_t interval_ms = 1000;
uint32_t slept_ms = 0;
uint32_t clock_ms = 100;
uint32_t status = 0;

void toggle()
{
  for (int pin : output_pins) {
    digitalWrite(pin, status);
  }
  status = !status;
}

void loop()
{
  int button_state = digitalRead(BUTTON_PIN);

  if (button_state == HIGH)
  {
    interval_ms += clock_ms;
  }

  delay(clock_ms);
  slept_ms += clock_ms;

  if (slept_ms > interval_ms)
  {
    toggle();
    slept_ms = 0;
  }
}