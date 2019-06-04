#ifndef __AVR_ATmega32U4__
#define __AVR_ATmega32U4__ 1
#endif

#define setbit(port, bit) (port) |= (1 << (bit))
#define clearbit(port, bit) (port) &= ~(1 << (bit))

#include <avr/delay.h>
#include <avr/io.h>

int main(void) {
  DDRD = 0b00001000;

  while (1) {
    if (PIND & PIND4) {
      setbit(PORTD, PD7);
    } else {
      clearbit(PORTD, PD7);
    }
    
    _delay_us(1);
  }
  return 0;
}