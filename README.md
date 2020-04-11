# Arduino RC receiving dongle

![RCtoPC logo](https://github.com/RobbeDGreef/RCtoPC/raw/master/extras/rctopclogo_small.png "RCtoPC logo")

## Info

This project creates the possibility for everyone with
nearly any type of Arduino to connect his or her favorite RC 
transmitter to a pc and play games with it. This eliminates 
the need for expensive external RC dongles. 

The Arduino system even has a higher controller sample
rate than the normal dongle I used. :)
(external dongle: 70-80 FPS, Arduino uno dongle: 80-90 FPS) 

**IMPORTANT: if you are thinking of buying an Arduino uno 
specifically for driving with your RC transmitter on your computer instead
of buying a RX dongle DON'T, read**[what Arduino would be perfect for this project alone](#What-Arduino-to-buy-specifically-for-this-project)

## Table of contents

* [Info](#info)
* [Table of contents](#table-of-contents)
* [System specifications](#system-specifications)
* [How it works](#how-it-works)
* [What Arduino to buy specifically for this project](#What-Arduino-to-buy-specifically-for-this-project)
* [Get it running](#get-it-running)
	* [Arduino UNO and other derivatives](#arduino-uno-and-other-derivatives)
		* [What you'll need](#what-youll-need)
		* [Build process](#build-process)
		* [Configuration](#configuration)
		* [I'm finished, now how do I use it](#im-done-reading-and-building-now-how-do-i-use-this-in-game)
	* [Arduino MICRO and other USB emulation Arduinos](#arduino-micro-and-other-usb-emulation-arduinos)
		* [What you'll need](#what-youll-need)
		* [Build process](#build-process)
		* [Configuration](#configuration)
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

Some Arduinos like the Arduino Micro and the Arduino 
leonardo have a chip in them that is able to emulate 
HID's (human interface devices). Note that not only
the micro is able to do so, the micro pro, digisparks,
micro ss, and loads more can do this. 

Now this means that you can connect your RC receiver to 
your Arduino via the pins on the board. Connect the Arduino
to the pc, load in a sketch that translates the commands 
from the RC receiver to joystick commands and sends them 
to the pc and boom. You have yourself a DIY RC to USB dongle.

However the most common Arduino, the Arduino uno is not able
to do this (without changing firmware etc.). Luckily for you
I found a workaround. The Arduino uno can, like nearly all 
Arduinos to my knowledge, work as a serial device and send
data over a serial connection. So just like before you connect
your RC receiver to the Arduino via the pins and load in the 
correct sketch. The only difference is that this time instead
of letting the Arduino emulate a joystick, we will send the
received RC data to the pc over a serial connection and have
a script running on the pc that translates them to joystick data.
The script then creates a virtual joystick to trick the pc
into thinking there is an actual joystick attached and feeds
the RC data to the virtual joystick. 


## What Arduino to buy specifically for this project

This project will normally work with most if not all Arduinos.
(although currently only tested with an Arduino Micro and a Arduino uno)

But if you are thinking of buying an Arduino specifically for this project
and nothing else, don't buy an uno. Go for a cheap Arduino and maybe even
one without header pins so that you can solder the wires directly. Also
make sure that the Arduino you buy is capable of USB HID emulation. 
Because it's the easiest solution (no running scripts and software etc).

Personally I would recommend an Arduino Micro because it's a versatile
little board and is well documented and supported. However you could
go for something cheap like a standard digispark (although the sketches 
don't currently work on the digispark I tested, working on it though)
or an Arduino micro SS. Maybe some cheap clones will even work (no guarantee here).

If you have some old standard Arduino lying around chances are it's supported
and if it isn't, [hit me up](#communicate-with-me) we'll look into it together. 

## Get it running

### Arduino UNO and other derivatives

#### What you'll need

The hardware you'll need for this system:
- [Arduino](https://store.arduino.cc/arduino-uno-rev3)
- Your favorite RC transmitter and receiver
- The wires to connect the two (see diagram)
- Cable to connect the Arduino to the pc

Software you'll need for this system:
- [Arduino IDE](https://www.arduino.cc/en/main/software) to upload the sketch
- [python](https://www.python.org/downloads/) to run the script
- the [vjoy](http://vjoystick.souRCeforge.net/site/index.php/component/weblinks/weblink/13-uncategorised/14-latest-download?Itemid=435&task=weblink.go) driver
- pyserial
- pyvjoy

Note that those last two can be installed by running the install-python-dependencies.bat file.

And of course this repository.

#### Build process

So now that you have all the hardware and installed
all the software. We can begin building this setup
it's actually pretty simple.

We will start with connecting the RC receiver to 
the Arduino. It's a matter of connecting some wires.
You can probably just use the wires that came with 
your receiver.

I wrote an [instructables article](https://www.instructables.com/id/RC-Receiver-to-Pc-With-Arduino/) to make it
easier for you.

#### Configuration

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

**Please know that changing your THROTTLE_MAX won't necessarily make you drive faster it might even make you slower**
You will drive slower if you set this value higher then the
value your transmitter actually sends out because if you were
to push the throttle back completely the python script will
think your max value still isn't reached and it won't actually
push the joystick value all the way up to the max.

The same goes for steering.

### I'm done reading and building, now how do I use this in game

Pretty simple. Locate the run.bat file, it will 
launch the python script for you. Now just leave
that black command prompt open in the background.
It is constantly translating serial to joystick.
Just run any program you want where you can you 
use a joystick and select the vJoy joystick :)


### Arduino MICRO and other USB emulation Arduinos

#### What you'll need

The hardware you'll need for this system:
- Arduino capable of USB HID emulation
- Your favorite RC transmitter and receiver
- The wires to connect the two
- Cable to connect the Arduino to the pc

Software you'll need for this system:
- [Arduino IDE](https://www.arduino.cc/en/main/software) to upload the sketch

And obviously this repository's code.

That's it, easy right?

#### Build process

The build process is pretty much the [same as before](https://www.instructables.com/id/RC-Receiver-to-Pc-With-Arduino/)
only this time we upload a different sketch and 
you need to [configure](#configuration) the project before uploading the sketch.

**Please note what pins are selected in the config.h file**
when you connect up the pins of the receiver to the Arduino.

I know I haven't made a separate instructable for this part of the
project but here you see a photo of an Arduino micro all connected up.

![Arduino Micro all connected up](https://github.com/RobbeDGreef/RCtoPC/raw/master/extras/arduino_micro_connected.jpg)

If you have any questions about how it should be wired up on your Arduino
or really want me to make a separate instructable about it. [Just ask me](#communicate-with-me)

#### Configuration

This project can be configured completely in the [config.h](../blob/master/ArduinoMicro/ArduinoRCDongle/config.h) file
in the sketch folder. You can configure the pin, axis, joystick, minimum
and maximum values in here. It's pretty self explanatory but more info
is found in the comment in the header file.

This project currently supports up to 4 channels.


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

### Update 0.4

Arduino Micro RC dongle 0.1 works!
It currently supports 4 channels and works by emulating 2
joysticks. The system is a bit too unstable to release right
now though. It will probably be ready in a day or so. 

Possible improvements:
- replace pulseIn() function with interrupts to improve sample rate
- replace double joystick setup with a gamepad setup or maybe add
...extra z axis and rotation axises.

### Update 0.5

Arduino Micro RC dongle 0.2 is pretty configurable. It's still not 
perfect but it does the job so it's now ready to be released in the
wild.

I also created a joysticktest.exe file. It's a simple window where
you can select any of the joysticks connected to your pc and see their
X and Y axes output. It's a simple python script that can be found in the
extras folder but I converted it to a exe so that you don't need to 
download more python libraries. I might convert the other scripts too
but the problem is that that breaks the configurability.