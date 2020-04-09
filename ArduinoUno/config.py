# This is a configuration file
# Only change settings here if you know what you are doing and if you
# are sure it won't break the serial connection with the arduino

import serial

# Serial connection settings
CONNECTIONPORT = 'COM3'
BAUDRATE = 9600
STOPBITS = 1
PARITY = 'N'  # 'N' is off, even is 'E', odd is 'O', mark is 'M' and space is 'S'
BYTESIZE = 8

# Connection settings
THROTTLE_AXIS = 'Y'
STEERING_AXIS = 'X'

# RC Receiver settings
THROTTLE_MIN = 1090
THROTTLE_MAX = 1870
STEERING_MIN = 1090
STEERING_MAX = 1870

# PycJoy settings

# Fully left is 0x1 and fully right corresponds to 0x8000
JOYSTICK_MIN = 0x1
JOYSTICK_MAX = 0x8000

