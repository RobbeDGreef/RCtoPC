import serial
import pyvjoy
from config import *

_running = True


def remap(value, min1, max1, min2, max2):
    return int(min2 + (value - min1) * (max2 - min2) / (max1 - min1))


def translate_throttle(value):
    return remap(value, THROTTLE_MIN, THROTTLE_MAX, JOYSTICK_MIN, JOYSTICK_MAX)


def translate_steering(value):
    return remap(value, STEERING_MIN, STEERING_MAX, JOYSTICK_MIN, JOYSTICK_MAX)


def set_axisX(joystick, value):
    joystick.data.wAxisX = value


def set_axisY(joystick, value):
    joystick.data.wAxisY = value


def main():
    # First setup the serial connection
    try:
        ser = serial.Serial(port=CONNECTIONPORT, baudrate=BAUDRATE, bytesize=BYTESIZE, parity=PARITY, stopbits=STOPBITS)
    except serial.SerialException as e:
        print("Failed to open a serial connection to the arduino.")
        print("Is the correct COM port selected in the config.py file?")
        print("Error message:\n", e)
        exit(1)

    print("Serial connected to ", CONNECTIONPORT)

    # Then create the joystick
    try:
        joystick = pyvjoy.VJoyDevice(1)
    except pyvjoy.vJoyNotEnabledException as e:
        print("Failed to create virtual joystick device.")
        print("Are the vJoy drivers installed?")
        print("Error message:\n", e)
        exit(1)

    # Resetting the joystick to make sure all states are default and no buttons are pressed
    joystick.reset()
    print("Virtual joystick connection made")

    # Now interpret the config file
    throttle_axis = None
    steering_axis = None
    if THROTTLE_AXIS == 'X':
        throttle_axis = set_axisX
        steering_axis = set_axisY

    elif THROTTLE_AXIS == 'Y':
        throttle_axis = set_axisY
        steering_axis = set_axisX

    else:
        print("ERROR: Throttle axis is not valid")
        exit(1)

    print("Mainloop started without any problems")
    print("\n")
    print("Now translating serial data to joystick controls\nDo not close the window unless you want to stop the dirver or unplugged your arduino")

    while _running:
        startbyte = ser.read(1)
        if startbyte != b'\x00':
            continue

        steering = int.from_bytes(ser.read(2), "big")
        throttle = int.from_bytes(ser.read(2), "big")

        #print("steering: %i throttle: %i" % (steering, throttle))

        steering_axis(joystick, translate_steering(steering))
        throttle_axis(joystick, translate_throttle(throttle))

        joystick.update()


if __name__ == '__main__':
    main()
