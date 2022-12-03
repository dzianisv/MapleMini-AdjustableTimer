#include <Arduino.h>

#define ONBOARD_BUTTON_PIN PB8
#define CUSTOM_BUTTON_PIN PB5
#define LED_PIN PB1

static int output_pins[] = {LED_PIN /* led pin */, PB3, PB4};

const uint32_t clock_ms = 100;
uint32_t interval_ms = 5000;
uint32_t activity_time_ms = 1000;
uint32_t slept_ms = 0;
uint32_t previous_tick_ms = 0;

bool status = false;

void toggle()
{
  status = !status;
  digitalWrite(LED_PIN, status);
  digitalWrite(PB3, status);
  digitalWrite(PB4, !status);
}

void setup()
{
  for (int pin : output_pins)
  {
    pinMode(pin, OUTPUT);
  }
  pinMode(CUSTOM_BUTTON_PIN, INPUT);
  pinMode(ONBOARD_BUTTON_PIN, INPUT);
  toggle();
}


void loop()
{
  if (digitalRead(ONBOARD_BUTTON_PIN) == HIGH)
  {
    interval_ms += 2*clock_ms;
  }
  if (digitalRead(CUSTOM_BUTTON_PIN) == HIGH)
  {
    activity_time_ms += 2*clock_ms;
  }

  // This number will overflow in 50 days
  delay(clock_ms);
  uint32_t now = millis();
  slept_ms += (now - previous_tick_ms);
  previous_tick_ms = now;

  if ((!status && (slept_ms > interval_ms))
      || (status && (slept_ms > activity_time_ms)))
  {
    toggle();
    slept_ms = 0;
  }
}