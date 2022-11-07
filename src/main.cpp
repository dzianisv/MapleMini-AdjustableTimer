#include <Arduino.h>

#define ONBOARD_BUTTON_PIN PB8
#define CUSTOM_BUTTON_PIN PB5
#define LED_PIN PB1

static int output_pins[] = {LED_PIN /* led pin */, PB3, PB4};

void setup()
{
  for (int pin : output_pins)
  {
    pinMode(pin, OUTPUT);
  }
  pinMode(CUSTOM_BUTTON_PIN, INPUT);
  pinMode(ONBOARD_BUTTON_PIN, INPUT);
}

uint32_t interval_ms = 1000;
uint32_t interval2_ms = 1000;
uint32_t slept_ms = 0;
uint32_t clock_ms = 100;
uint32_t status = 0;

void toggle()
{
  for (int pin : output_pins)
  {
    digitalWrite(pin, pin % 2);
  }
  status = !status;
}

void loop()
{
  if (digitalRead(ONBOARD_BUTTON_PIN) == HIGH)
  {
    interval_ms += clock_ms;
  }
  if (digitalRead(CUSTOM_BUTTON_PIN) == HIGH)
  {
    interval2_ms += clock_ms;
  }

  delay(clock_ms);
  slept_ms += clock_ms;

  if (!status && slept_ms > interval_ms)
  {
    toggle();
    slept_ms = 0;
  }
  else if (status && slept_ms > interval2_ms)
  {
    toggle();
    slept_ms = 0;
  }
}