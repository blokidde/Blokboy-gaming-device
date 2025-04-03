# Concept & Design prototype

## Main goal
the main goal of this project is:  
create a handheld gaming device for playing snake with physical inputs and automatic data tracking, that is fully 3d-printable and works wirelessly. 

## concept
im going to try to make the design look a little like an old gameboy. for designing i used the tool Freecad.

## user description
the user is someone who wants to play a classic snake game on a physical, handheld gaming devie. the user wants to get instant feedback from joystick and button inputs and view scores after a game. the device needs to be small, portable, and easy to charge.

## user needs
- the device must be compact and handheld
- it must feel like an oldschool gameboy
- it must be possible to track gameplay stats
- scores must be sent to a database
- the data should be viewable in a simple online dashboard
- the device must be easy to assemble without tools or glue
- a battery must fit inside so it's fully portable

## product requirements
- the joystick must fit perfectly in the joystickhole
- the screen must be fully visible and centered
- the screen must fit well into the hole, wihtout falling out
- two breadboards with ESP32 and battery must fit inside the case
- the buzzer must fit perfectly in the buzzer hole
- the power button must be accessible from the outside
- all components must be powered by a single li-ion 18650 battery

## first design

frontpanel design:

![frontpanel design](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/designfrontpicture.png)

in the design for the frontpanel i created several holes. one for the screen, one for the joystick, two push buttons, and an on off button. 

backpanel design:

![frontpanel design](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/designbackpicture.png)

on the backpannel you can see two indents, these indents are for 2 breadboards with an esp32 on it and for a li-ion 18650 battery. 

the front and backpanel are suposed to slot together without any glue or screws.

## current design
after 5 iterations of the frontpanel and 2 iterations of the backpanel, all the 3d prints are done and they fit.
the changes that were made are:
- screw pillars
- smaller joystick hole
- bigger on off hole
- direction of screen has changed
- size of screen has changed
- bigger buzzer hole
- bigger battery placement hole


this is the frontpanel:

![frontpanel design](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/frontpanel_v5.png)

this is the backpanel:

![frontpanel design](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/backpanel_v2.png)

## tools used
for the design part of the project, the following tools and settings were used:

- Freecad for 3d modeling
- exported as STL for slicing
- printed using an Ultimaker 2+  (standard settings)
- filament used: PLA
- layer height: 0.2 mm
- infill: 20%
- supports: only for frontpanel, using the tree support style

## recreatability
the device is designed to be fully recreatable:
- freecad files include all versions
- printed with standard PLA and normal 3d printer
- component placement is visible in the 3d model