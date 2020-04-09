import serial
from serial_receiver import open_serial, translate_throttle, translate_steering, remap
from config import STEERING_AXIS, THROTTLE_AXIS, CONNECTIONPORT

def main():
    ser = open_serial()
    print("Serial connected to ", CONNECTIONPORT)

    while True:
        startbyte = ser.read(1)
        if startbyte != b'\x00':
            continue

        steering = int.from_bytes(ser.read(2), "big")
        throttle = int.from_bytes(ser.read(2), "big")

        translate_s = translate_steering(steering)
        translate_t = translate_throttle(throttle)

        print("Throttle in: {0} steering in: {1} - translates to throttle axis {2}: {3} and steering axis {4} {5}".format(
                throttle, steering, THROTTLE_AXIS, translate_t, STEERING_AXIS, translate_s))

if __name__ == '__main__':
    main()