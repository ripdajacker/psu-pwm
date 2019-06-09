#define F_CPU 16000000UL

#ifndef __AVR_ATmega32U4__
#define __AVR_ATmega32U4__ 1
#endif

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

struct interval {
  uint16_t min;
  uint16_t max;
  uint16_t numerator;
  uint16_t denominator;
};

const uint16_t PWM_CONSTANT = F_CPU / 25000;
const struct interval INTERVALS[] = {
    {0, 800, 1, 5}, {800, 850, 2, 5}, {850, 900, 3, 5}, {900, 950, 4, 5}, {950, 1024, 5, 5}};

void pwmBegin(void) {
  clock_prescale_set(clock_div_2);

  DDRC = 1 << 7;

  TC4H = (PWM_CONSTANT - 1) >> 8;
  OCR4C = (PWM_CONSTANT - 1) & 0xFF;

  TCCR4A = (1 << COM4A1) | (1 << PWM4A);
  TCCR4B = (1 << CS40);
}

void setDutyCycle(uint16_t numerator, uint16_t denominator) {
  TC4H = (PWM_CONSTANT * numerator / denominator) >> 8;
  OCR4A = (PWM_CONSTANT * numerator / denominator) & 0xFF;
}

int main(void) {
  DDRD = 0;

  ADMUX = 0;                             // reference is AREF
  ADCSRA = (1 << ADPS2) | (1 << ADPS1);  // ADC prescaler 1/64
  ADCSRA |= 1 << ADEN;

  pwmBegin();
  setDutyCycle(1, 5);

  while (1) {
    ADCSRA |= 1 << ADSC;
    while ((ADCSRA & (1 << ADSC)) != 0) {
      // wait for ADC
    }

    uint8_t low = ADCL;
    uint8_t high = ADCH;
    uint16_t value = (high << 8) | low;

    for (uint8_t i = 0; i < 5; ++i) {
      struct interval current = INTERVALS[i];
      if (current.min <= value && current.max > value) {
        setDutyCycle(current.numerator, current.denominator);
      }
    }
  }
}