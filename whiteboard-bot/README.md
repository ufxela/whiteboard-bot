# Whiteboard Bot [WIP: status - works/sketchy]

A whiteboard robot which you can command in several intuitive ways and draw what you want.

See a video demo [here](unimplemented).

Inspired by [this](https://www.youtube.com/watch?v=T0jwdrgVBBc&vl=en), and a never completed robotics project that I started with the Stanford Robotics Club. 

## Tech
Built to run on bcm2835 (raspberry pi a+ or raspberry pi zero).

## Run
plug in raspberry pi, plug in stepper motor power supply
```
make run
```
follow the prompts to see what you can do. 

## Setup
### Materials
- raspberry pi a+ or raspberry pi zero
- 2 nema 17 stepper motors
- 2 a4988's
- power supply for stepper motors
- 1 hobby servo w/ 3.3v inputs (cheap 9g servos will do the job)
- 1 LSM6DS3 
- 1 esp8266
- cp2102
- 3D printed gondola
- 3D printed motor mounts
- various hardware (like a whiteboard, screws, belt/gears, etc.)

### Wiring
Wire up cp2102, esp8266, LSM6DS3, servo, and a4988's in the same way that the `#define`'d constants specify. Also hook up steppers and power to a4988's. Hookup 5v and 3.3v pins respectively. 

### Preparation
Get SD card, and copy `bootcode.bin`, `config.txt`, `kernel.img` and `start.elf` onto it, then mount onto Pi. 