# define F_CPU 16000000UL

#ifndef __AVR_ATmega32U4__
#define __AVR_ATmega32U4__ 1
#endif

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

void pwmBegin(void) {
  clock_prescale_set(clock_div_1);

  DDRC = 1 << 7;

  TC4H = (F_CPU / 25000 - 1) >> 8;
  OCR4C = (F_CPU / 25000 - 1) & 0xFF;

  TCCR4A = (1 << COM4A1) | (1 << PWM4A);
  TCCR4B = (1 << CS40);
}

void setDutyCycle(float fraction) {
  TC4H = (F_CPU / 25000 * 3 / 4) >> 8;
  OCR4A = (F_CPU / 25000 * 3 / 4) & 0xFF;
}

unsigned long tick = 0;
unsigned long ones = 0;

int main(void) {
  DDRD = 1 << 4;
  DDRC = 1 << 7;

  pwmBegin();
  setDutyCycle(1 / 5);

  while (1) {
    for (tick = 0; tick < 1000; ++tick) {
      if (PIND & (1 << PD4)) {
        ones++;
      }

      _delay_us(1);
    }

    setDutyCycle(ones / (float)tick);

    tick = 0;
    ones = 0;
  }

  return 0;
}