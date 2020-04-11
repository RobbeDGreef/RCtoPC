#include "joystick_emulator.h"

#define JOYSTICK_ID_1	3
#define JOYSTICK_ID_2	4

struct hid_data_s
{
	uint16_t	buttons;
	int8_t 		xAxis;
	int8_t 		yAxis;
};

/**
 * Thanks to https://www.usb.org/hid 
 * and https://github.com/NicoHood/HID
 */
static const uint8_t hid_report_desciptor[] PROGMEM = 
{
	/* Joystick 1 */
	0x05, 0x01,             /* USAGE_PAGE (Generic Desktop) */
	0x09, 0x04,             /* USAGE (Joystick) */
	0xa1, 0x01,             /* COLLECTION (Application) */
	0x85, JOYSTICK_ID_1,	/* REPORT_ID (3) */

	/* Enable all 16 Buttons */
	0x05, 0x09,            /* USAGE_PAGE (Button) */
	0x19, 0x01,            /* USAGE_MINIMUM (Button 1) */
	0x29, 0x10,            /* USAGE_MAXIMUM (Button 16) */
	0x15, 0x00,            /* LOGICAL_MINIMUM (0) */
	0x25, 0x01,            /* LOGICAL_MAXIMUM (1) */
	0x75, 0x01,            /* REPORT_SIZE (1) */
	0x95, 0x10,            /* REPORT_COUNT (16) */
	0x55, 0x00,            /* UNIT_EXPONENT (0) */
	0x65, 0x00,            /* UNIT (None) */
	0x81, 0x02,            /* INPUT (Data,Var,Abs) */

	/* Configure X and Y Axis */
	0x05, 0x01,            /* USAGE_PAGE (Generic Desktop) */
	0x09, 0x01,            /* USAGE (Pointer) */
	0x15, (uint8_t) JOYSTICK_MIN,    /* LOGICAL_MINIMUM (0) */
	0x25, (uint8_t) JOYSTICK_MAX,    /* LOGICAL_MAXIMUM (255) */
	0xA1, 0x00,            /* COLLECTION (Physical) */
	0x09, 0x30,            /* USAGE (x) */
	0x09, 0x31,            /* USAGE (y) */
	0x75, 0x08,            /* REPORT_SIZE (8) */
	0x95, 0x02,            /* REPORT_COUNT (2) */
	0x81, 0x02,            /* INPUT (Data,Var,Abs) */
	0xc0,                  /* END_COLLECTION */
	0xc0,                  /* END_COLLECTION */

	/* Joystick 2 */
	0x05, 0x01,            /* USAGE_PAGE (Generic Desktop) */
	0x09, 0x04,            /* USAGE (Joystick) */
	0xa1, 0x01,            /* COLLECTION (Application) */
	0x85, JOYSTICK_ID_2,   /* REPORT_ID (4) */

	/* Enable all 16 Buttons */
	0x05, 0x09,            /* USAGE_PAGE (Button) */
	0x19, 0x01,            /* USAGE_MINIMUM (Button 1) */
	0x29, 0x10,            /* USAGE_MAXIMUM (Button 16) */
	0x15, 0x00,            /* LOGICAL_MINIMUM (0) */
	0x25, 0x01,            /* LOGICAL_MAXIMUM (1) */
	0x75, 0x01,            /* REPORT_SIZE (1) */
	0x95, 0x10,            /* REPORT_COUNT (16) */
	0x55, 0x00,            /* UNIT_EXPONENT (0) */
	0x65, 0x00,            /* UNIT (None) */
	0x81, 0x02,            /* INPUT (Data,Var,Abs) */

	/* Configure X and Y Axis */
	0x05, 0x01,            /* USAGE_PAGE (Generic Desktop) */
	0x09, 0x01,            /* USAGE (Pointer) */
  0x15, (uint8_t) JOYSTICK_MIN,    /* LOGICAL_MINIMUM (0) */
  0x25, (uint8_t) JOYSTICK_MAX,    /* LOGICAL_MAXIMUM (255) */
	0xA1, 0x00,            /* COLLECTION (Physical) */
	0x09, 0x30,            /* USAGE (x) */
	0x09, 0x31,            /* USAGE (y) */
	0x75, 0x08,            /* REPORT_SIZE (8) */
	0x95, 0x02,            /* REPORT_COUNT (2) */
	0x81, 0x02,            /* INPUT (Data,Var,Abs) */
	0xc0,                  /* END_COLLECTION */
	0xc0                   /* END_COLLECTION */
};

static int CURJSAMOUNT = 0;
static bool setup_hid = true;

Joystick::Joystick()
{ 
    Joystick(CURJSAMOUNT++);
}

Joystick::Joystick(int id)
{
	 m_reportID = JOYSTICK_ID_1 + id;
	 m_buttons = 0;
	 m_xAxis = 0;
	 m_yAxis = 0;

	 if (setup_hid)
	 {
	 	/* This is bad practice but it will work for this small project */
	 	static HIDSubDescriptor node(hid_report_desciptor, sizeof(hid_report_desciptor));
	 	HID().AppendDescriptor(&node);
	 	setup_hid = false;
	 }
}

void Joystick::setButton(int button, bool value)
{
	if (value)
		m_buttons |= value << button;
	
	else
		m_buttons &= value << button;
}

void Joystick::setXAxis(int value)
{
	m_xAxis = value;
  Serial.print("Value x: "); Serial.print(value); Serial.print('\n');
}

void Joystick::setYAxis(int value)
{
	m_yAxis = value;
  Serial.print("y: "); Serial.print(value); Serial.print('\n');
}

void Joystick::update()
{
	static struct hid_data_s hid_data;

	hid_data.buttons = m_buttons;
	hid_data.xAxis = m_xAxis;
	hid_data.yAxis = m_yAxis;

	HID().SendReport(m_reportID, (char*) &hid_data, sizeof(struct hid_data_s));
}

Joystick js[2] = { Joystick(0), Joystick(1)};
