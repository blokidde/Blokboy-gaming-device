# Technical documentation

## Blueprint
im going to be using the handheld game device as my blueprint.
my idea will look a little like a gameboy.

## idea

## possible parts
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

## Bill of Materials prototype

this is a bill of materials, in this BOM is the information about all the materials used for the prototype of the Blockboy gaming device.

| Part #            | Manufacturer  | Description                           | Quantity | Price | Subtotal | website for product |
|-------------------|--------------|---------------------------------------|----------|------------------|---------------------|-------------|
| ILI9341          | Adafruit      | 320x24 lcd display       | 1        | EUR 10,95         | EUR 10,95           | [Link](https://www.otronic.nl/nl/mini-oled-display-wit-096-inch-128x64-i2c.html?source=googlebase&gad_source=1&gclid=CjwKCAiA8Lu9BhA8EiwAag16b_Jph9CQv1BluZBvTixQCd91jRLTBniL4Icb1hGrFX4vNJ3XQL2nCBoCqG0QAvD_BwE) |
| KY-023           | Keyes         | Joystick Module                       | 1        | EUR 2,50         | EUR 2,50           | [Link](https://www.otronic.nl/nl/joystick-module.html?source=googlebase&gad_source=1&gclid=CjwKCAiA8Lu9BhA8EiwAag16b5MZ5QAU0AYwHf6ouQHm258bIj7wyNn62JVDe5pnvUKXCRY8AvvwHhoC6jQQAvD_BwE) |
| PBS-110          | Omron         | Push Button Switch                    | 2        | EUR 0,10        | EUR 0,20           | [Link](https://www.tinytronics.nl/nl/schakelaars/manuele-schakelaars/printplaatschakelaars/tactile-pushbutton-switch-momentary-4pin-6*6*5mm) |
| SFM-20B       |         | Piezo Buzzer - 3900-5000 Hz                    | 1        | EUR 1,25         | EUR 1,75           | [Link](https://www.hobbyelectronica.nl/product/piezo-elektronische-zoemer-sfm-20b/?srsltid=AfmBOoqepXgzSYiDPb_LaKaF6STsayvAjp2lHWUVj7OrZ_lj305y2Ww9) |
| ESP32       |  espressif  | ESP32 microcontroller                    | 1        | EUR 11,99         | EUR 11,99           | [Link](https://www.amazon.nl/Diymore-DevKitC-ontwikkelboard-Bluetooth-gesoldeerd/dp/B0CYZVQR27/ref=asc_df_B0CYZVQR27/?tag=nlshogostdde-21&linkCode=df0&hvadid=710076811627&hvpos=&hvnetw=g&hvrand=12382446210197140232&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9065289&hvtargid=pla-2316449144058&psc=1&mcid=94e2f1f5db233a70808f378910bfa657&tag=nlshogostdde-21&linkCode=df0&hvadid=710076811627&hvpos=&hvnetw=g&hvrand=12382446210197140232&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9065289&hvtargid=pla-2316449144058&psc=1&gad_source=1) |
| Li-ion battery       |         | 3.7v battery 2600mAh                    | 1        | EUR 8,5         | EUR 8,5           | [Link](https://www.kabeldirect.nl/bse-li-on-cr-18650-batterij-3.7v-2600-mah-met-buttontop.html?utm_source=google&utm_medium=cpc&utm_campaign=21258785706&utm_term=&utm_content=&gad_source=1&gclid=CjwKCAjwtdi_BhACEiwA97y8BBGCww185BP_yp-iyhHcYfpdKgjURIKcpcUx2MgjrsxklO7V7wTc2xoC6_8QAvD_BwE) |
|on/off switch      |         | on/off switch                    | 1        | EUR 8,5         | EUR 8,5           | [Link](https://www.allekabels.nl/schakelaar/7303/1063954/wipschakelaar.html?mc=nl-nl&gad_source=1&gclid=CjwKCAjwtdi_BhACEiwA97y8BPgDKUNXh44KNkB61R5MXEbTETz7JjdjLfKD9HY7eCZJWyZE739EeBoCvOwQAvD_BwE) |



