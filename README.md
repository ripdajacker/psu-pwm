# psu-pwm

A small Arduino program to PWM control a 1st edition Corsair HX850 PSU.

## Materials and tools

* Screwdriver
* Silent 140mm fan (Noctua or the like)
* Arduino Nano (or equivalent)
* Some wire

## Wiring

You need to run a wire from the black pin on the thermistor inside the PSU to `A0` on the Arduino with a 10k resistor. Add a 5k resistor from `A0` to ground. This acts as a voltage divider and keeps your arduino from blowing up.

Run another wire from pin `5` on the Arduino to the PWM pin of the fan you intend to use.

````
-------                      -----------
| PSU |                      | Arduino |
-------                      -----------
Black lead
from 
thermistor  ------------------->  A0
                                   5 ----------------> Blue pin on FAN
````

## Programming and tuning

1. First flash the Arduino with the sketch seen in the `psu-pwm.ino` file.
2. Start a serial monitor when the Arduino is running.
3. Look at the read/write data. Note the idle input range (it was around 300 here).
4. Run your PC with FULL LOAD meaning CPU, GPU and RAM.
5. Notice the input values are increasing. This is the temperature rising.
6. After 10-15 minutes you should have some stable temps. C
7. Check that the input does not keep increasing. If it does, increase the value of `output_max` and re-flash.
8. Enjoy a more silent PC :D