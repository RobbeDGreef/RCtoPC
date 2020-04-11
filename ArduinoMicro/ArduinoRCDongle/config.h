#ifndef CONFIG_H
#define CONFIG_H

#include "joystick_emulator.h"

/**
 * Every channel can be configured with this list
 *  .pin        is the pin where the arduino will listen for PWM values
 *  .axis       is the axis where the arduino will write the pin to (X or Y)
 *  .joystick   is the joystick the arduino will send the commands to (JOYSTICK_1 / JOYSTICK_2)
 *  .min        is the minimum pwm value (the minimum value your transmitter sends out)
 *  .max        is the maximum pwm value (the maximum value your transmitter sends out)
 *  
 *  note that your min and max values might be different from these
 */
static struct channel channels[] = 
            {
              {.pin = 2, .axis = X, .joystick = JOYSTICK_1, .min = 1070, .max = 1900},
              {.pin = 3, .axis = Y, .joystick = JOYSTICK_1, .min = 1070, .max = 1900},
              {.pin = 0 },
              {.pin = 0 }
            };

#endif
