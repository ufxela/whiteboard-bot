# Stepper Docs

# Stepper/stepper-int/stepper-music.h

## Hardware
- [nema 17 sized stepper](https://www.amazon.com/gp/product/B01N30ISYC)
- [TB6612 dual h bridge](https://www.amazon.com/gp/product/B00VY32VU4 ), can also use l298n, or any h dual h bridge of suitable size with 3.3v logic input
- [12v, 5a AC to DC power supply](https://www.amazon.com/gp/product/B01461MOGQ/)

## Hardware Setup
I'm using these gpio pins:
```c
#define A1_pin 26
#define A2_pin 19
#define B1_pin 13
#define B2_pin 6
```
`A1_pin` is wired to `A1_in` on the TB6612, `A2_pin` to `A2_in` etc.
TB6612's VCC and PWM1 and PWM2 are all connected to pi's 3.3v.
the four pins labeled MotorA and MotorB on TB6612 are connected to the stepper. You can use trial and error to figure this out, and I should write a more detailed explanation of how to find out which pins to use, and there's good docs online. For my specific motor, the color order from the farthest motorB output to the farthest motorA output is red, yellow, green, grey.

## Notes
If you delay for too short a time between steps, you will skip steps

## Todo
Add docs explaining how steppers work, different hardware details and things to be weary about (i.e. it shouldn't damage the stepper motor if you wire it wrong, stepper tend to get hot, 3.3v vs 5v output, how to chose stepper and drive etc)

# Stepper-a4988.h 

## hardware
- a4988
- [nema 17 sized stepper](https://www.amazon.com/gp/product/B01N30ISYC)
- [12v, 5a AC to DC power supply](https://www.amazon.com/gp/product/B01461MOGQ/)

## Resource
for connecting the a4988 https://projectiot123.com/2019/02/01/raspberry-pi-gpio-interface-with-a4988/