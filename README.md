# Arduino RC receiving dongle

## Info

This project creates the possibility for everyone with
an Arduino (currently only tested on uno) to use
his or her favorite RC transmitter and play games on
their pc with it. This eliminates the need for 
expensive external rc dongles. 

The arduino system even has a higher controller sample
rate than the normal dongle I used. :)
(external dongle: 70-80 FPS, arduino dongle: 80-90 FPS) 

**IMPORTANT: if you are thinking of buying an arduino uno 
for driving with your rc transmitter on your computer instead
of buying a RX dongle don't buy an arduino UNO. Buy an arduino
MICRO.** The Arduino Micro will be a lot less hassle and will
work out of the box once I write the sketch and you install it.
Until then you could still use the same setup as this, just with
the MICRO instead of the UNO.

## Table of contents

* [System specifications](#system-specifications)
* [How it works](#how-it-works)
* [Get it running](#get-it-running)
	* [What you'll need](#what-youll-need)
	* [Build process](#build-process)
* [Configuration](#configuration)
* [I'm finished, now how do I use it](#im-done-reading-and-building-now-how-do-i-use-this-in-game)
* [Known bugs](#known-bugs)
* [What else is on the agenda](#what-else-is-on-the-agenda)
* [Communicate with me](#communicate-with-me)
* [Development updates](#development-updates)

## System specifications

This project is currently tested on a windows 10 64 bit pc
but it probably works on regular x86 pc's too. The vJoy
driver that this project uses works from windows XP and up
so I guess it works on older pc's as well.

I would write this for Linux and mac as well but I don't
think anyone actually needs that. If you do, just open a
github issue, ask for it and I'll look into it.

## How it works

The Arduino uno can't normally be used to emulate a HID
device such as a joysticks or a keyboards. What it can do
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
Arduino sketch.
I'd recommend to only change stuff if you know 
what you are doing but there are some things
that might be worth looking into.

The config.py file specifies the 
THROTTLE_MIN, THROTTLE_MAX, STEERING_MIN
and STEERING_MAX constants.
I figured those values out by some testing. 
To make it easy for you all I wrote a third python
script that shows you the values that are being sent
over the Arduino in real time. So if you think your 
throttle and/or steering values differ from mine. 
Run the script test-values.bat (this will automatically
start the valuetest.py script for you). And note the different
values and change them in the config file.

**Please know that changing your THROTTLE_MAX won't necessarily make you driver faster it might even make you slower**
You will drive slower if you set this value higher then the
value your transmitter actually sends out because if you were
to push the throttle back completely the python script will
think your max value still isn't reached and it won't actually
push the joystick value all the way up to the max.

The same goes for steering.


## I'm done reading and building, now how do I use this in game

Pretty simple. Locate the run.bat file, it will 
launch the python script for you. Now just leave
that black command prompt open in the background.
It is constantly translating serial to joystick.
Just run any program you want where you can you 
use a joystick and select the vJoy joystick :)

## Known bugs

- vJoy driver stops receiving input after a while
...For some unknown reason after letting my pc sit here idle for some time
...the vJoy driver just stops receiving input from anywhere. I don't know
...why it happens and the only way I've been able to reproduce the bug is
...by waiting. Currently the only fix I have found to work is rebooting the
...computer.

## What else is on the agenda

I just received my Arduino Micro so now I am also
working on a plug an play version of this. So no
driver installs and programs would be needed. Doesn't
that sound great?

Add multiple channels to make it possible for drone
or airplane pilots to use this software.

## Communicate with me

If you have any questions about this project, any other project
of mine, or want to see something else implemented don't 
hesitate to contact me

my email: robbedegreef@gmail.com

And if you like what I'm doing here you can always
leave a star on the repository to let me know you like
it ;)

## Development updates

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

### Update 0.2

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

### Update 0.3

Tested the Arduino UNO system in game and everything works perfectly.
I didn't even detect any latency so it works better then expected. Now
I also received my Arduino Micro in the mail so a PnP version is in the 
making.