#ifndef JOYSTICK_EMULATOR_H
#define JOYSTICK_EMULATOR_H

#include <stdint.h>
#include "HID.h"
#include <Arduino.h>

#define JOYSTICK_MIN   -127
#define JOYSTICK_MAX   127

class Joystick
{
private:
	int 		  m_reportID;		/* Joystick id, just to know he difference between the two */
	int8_t		m_xAxis;	    /* X-Axis value (1 - 255) */
	int8_t		m_yAxis;	    /* Y-Axis value (1 - 255) */
	uint16_t	m_buttons;	  /* I'm not sure why I would want to support sending buttons but okay */
	
public:
  Joystick();
	Joystick(int id);

	void setButton(int button, bool value);
	void setXAxis(int value);
	void setYAxis(int value);
	void update();
	int8_t getXAxis() { return m_xAxis; } /* dummy test function */
 
};

typedef void (Joystick::*setAxisFunction)(int value);
#define JOYSTICK_1  &js[0]
#define JOYSTICK_2  &js[1]
#define X           &Joystick::setXAxis
#define Y           &Joystick::setYAxis

struct channel
{
    int               pin;
    setAxisFunction   axis;
    Joystick          *joystick;
    int               min;
    int               max;
};

extern Joystick js[2];

#endif /* JOYSTICK_EMULATOR_H */
