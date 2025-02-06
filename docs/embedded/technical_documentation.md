# Technical documentation

## Blueprint
im going to be using the handheld game device as my blueprint.
my idea will look a little like a gameboy.

## idea

## parts
- microcontroller with wifi(raspberry pi, eps32, arduino)
- buttons
- joystick (5v, 2 potentiometers)
- lcd screen (240x320/320x480)
- speaker
- battery pack (18650 Li-ion)
- breadboard (turns into perfboard after prototype)
- battery charging port

## code necessities
- lcd screen library (Adafruit_ILI9341.h)

## game used

## websites used
- https://www.instructables.com/Raspberry-Pi-1-Gameboy/
- https://www.tinytronics.nl/nl/displays/tft/2.2-inch-tft-display-240*320-pixels-ili9341
- https://www.tinytronics.nl/nl/displays/tft/3.5-inch-tft-display-320*480-pixels-mega-compatible-ili9486
- https://wokwi.com/
- https://www.instructables.com/C-Snake-Game-Simple/

## failures
- i used a joystick for my project. i connected this to the 5v, ground and 2 pins. however the joystick didnt work for quite a while, i tested and the values i got were very weird. after a bit of testing i tries connecting it to 3.3v instead of 5. this was a little against the instructions given on the internet and on the joystick itself, both said to use 5v. strangely enough the 3.3v worked and now the joystick works perfectly with values ranging from x 0-4095 and y 0-4095.
## research

## differences from the blueprint

## pictures/ schematics/ 3D designs