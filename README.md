# Arduino RC receiving dongle

## Info

This project creates the possibility for everyone with
an Arduino (currently only tested on uno) to use
his or her favorite RC transmitter and play games on
their pc with it. This eliminates the need for 
external RC dongles that cost a lot. 

## System specifications

This project is currently tested on a windows 10 64 bit pc
but it probably works on regular x86 pc's too. The vJoy
driver that this project uses works from windows XP and up
so I guess it works on older pc's as well.

I would write this for Linux and mac as well but
the thing is I don't think anyone actually needs that
if you do, just open a issue, ask for it and I'll look 
into it.

## How it works

The Arduino uno can't normally be used to emulate a HID
device such as a joystick or a keyboard. What it can do
is work as a serial device. So I simply wrote an Arduino
sketch that sends the [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation) value it reads
over the specified pins to the pc via a serial connection.
See the Arduino sketch for more details. So then on the pc
you run a python script I wrote that listens to the serial
connection and reads the sent values from it. Then it 
translates those values and sends them via pyvjoy
(which is a python library) over to the vJoy driver. This 
driver emulates a joystick to trick the pc into thinking
a real joystick is attached.

## Get it running

### What you'll need

The hardware you'll need for this system:
- [Arduino](https://store.arduino.cc/arduino-uno-rev3)
- Your favorite RC transmitter and receiver
- The wires to connect the two (see diagram)

Software you'll need for this system:
- [Arduino IDE](https://www.arduino.cc/en/main/software) to upload the sketch
- [python](https://www.python.org/downloads/) to run the script
- the [vjoy](http://vjoystick.sourceforge.net/site/index.php/component/weblinks/weblink/13-uncategorised/14-latest-download?Itemid=435&task=weblink.go) driver
- pyserial
- pyvjoy

Note that those last two can be installed by running the install-python-dependencies.bat file.

And of course this repository.

### Build process

So now that you have all the hardware and installed
all the software. We can begin building this setup
it's actually pretty simple.

We will start with connecting the RC receiver to 
the Arduino. It's a matter of connecting some wires.
You can probably just use the wires that came with 
your receiver.

I wrote an [instructables article](https://www.instructables.com/id/RC-Receiver-to-Pc-With-Arduino/) to make it
easier for you.

## Configuration

This project can be configured in the python
config file (config.py) and in the top of the
arduino sketch. Only change stuff if you know 
what you are doing.

## I'm done now how do I use it in game

Pretty simple. Locate the run.bat file, it will 
launch the python script for you. Now just leave
that black command prompt open in the background.
It is constantly translating serial to joystick.
Just run any program you want where you can you 
use a joystick and select the vJoy joystick :) 

## What else is coming?

I just received my Arduino Micro so now I am also
working on a plug an play version of this.

Add multiple channels to make it possible for drone
or airplane pilots to use this software.

## Development updates:

### Update 0.1

Reverse engineered the 9TURBO RC-USB RX4 SS dongle 
it works pretty simple really, it just takes the PWM
signal from the receiver (via the white or yellow wire)
and translates it to joystick controls. It just emulates
a joystick and sends those controls to windows so you
can use it in game. This can be done with an Arduino micro
as well, because their chips can work in 'slave' mode. 
But I don't have a Arduino micro right now (it is arriving
in a few days but there are delays). So I wrote a sketch
that sends the throttle and steering controls to windows
over serial connection. Now I have two options, I can either
constantly emulate a joystick in user space or write a 
windows kernel driver. I think I am going for the second
option because the first will probably have terrible latency.

## Update 0.2

Got it working :) I haven't tested it in game yet so I don't
know if the latency is good but it seems to work fine and snappy.
The solution I use right now is just receiving the throttle 
and steering values over serial. Translating them to joystick
values and then use pyvjoy which uses a custom vJoy driver
(virtual joystick driver) everything in good 'ol python :)

I do however right now only support steering and throttle axises 
so I'll probably make an update for the software that can support
up to multiple channels and thus making this software work for drone
and airplane drivers too.
