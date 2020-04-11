#include "joystick_emulator.h"
#include "config.h"

/* Simple array calculator */
#define SIZE(x) (sizeof(x) / sizeof(x[0]))

void setup()
{
    /* Setting up the receiving pins */
    for (int i = 0; i < SIZE(channels); i++)
    {
        if (channels[i].pin)
            pinMode(channels[i].pin, INPUT);
        
    }
}

void loop()
{
    for (int i = 0; i < SIZE(channels); i++)
    {
        if (channels[i].pin)
        {
            int len = pulseIn(channels[i].pin, HIGH);
            (channels[i].joystick->*channels[i].axis)(map(len, channels[i].min, channels[i].max, JOYSTICK_MIN, JOYSTICK_MAX));
            js[0].update();
        }
    }
}
