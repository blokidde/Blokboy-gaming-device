# Learning journal

## feedback per week

## week 2

### things i learned this week
this week i learned how to 3d design and make a print. i made my own design for my handheld gaming device and we had a class about 3d printing where we needed to design and print a dice. before we could print it we had to initialize the settings for the 3d printer. this was done with a paper sheet and the springs underneath the 3d printer.
in my first try the dice was a succes, but there were some things i could inprove, like where i needed to put circles in combination with edges.

# ## feedback
feedback from ian: 

use more comments and a question about values's

feedback from peter:

code is good, nothing to say about code

feedback from nino:

code looks good, you could use more comments to make the code a bit easier to understand.

### what to change to be better?
i need to start using comments. at first i thought i would write the code first and add comments later but i noticed this makes it more difficult for myself and for readability for others. so in the class free week i will be adding comments to all my code and get everything updated for better readability.

## week 3

### things i learned this week
this week i did a workshop about lasercutting, i learned what to do with several different speeds, strengths and intervals. i also learned about the safety measures. after the workshop we had the time to make something ourselves and with the other classmates who were doing the workshop i created a design with several round curves and an infill in the design. by using the already given variables the design had a very clean cut.

in week 2 i started with the backend of my website, i created a GET.php file to get information from the database. i also created an INSERT. this is used to put stuff into the database. creating this was rather difficult because i had never really worked with php and SQL before. this meant i had to start from scratch. luckily the internet is a big help with this.

### feedback

## week 4

### HTML
this week i learned more about web development. HTML helped me build the basic structure of the page. I used different tags to organize my content and added important elements like a button and a table that shows the scores that are fethced from my database scores. I also learned how to connect an external JavaScript file and a CSS file in the head section. 

### CSS
with CSS i can control how the page looks. I set up fonts, changed background colors, and made sure that different parts of the page have the right spacing. I also tried to make sure the page is responsive, so it looks good on both big screens and small screens.

### JavaScript
JavaScript made the page interactive. For example, I used the fetch function to get data from my database, then created table rows and columns to display data. I also added an event listener to the button, so that when you click it, it sends a request to the ESP32 for debugging.

### Problems
while working on web development i ran into a problem i had some difficulties solving. the css wasnt loading on the page. i needed to clear my cache everytime i wanted to check the css. by doing a little research i found out i could use something called a cache buster. after adding this 

### feedback

## week 5
### JavaScript
i used JavaScript to make it possible for the website to communicate with the ESP32. I used the fetch function to send a request to the ESP32's local IP address. This request asks the ESP32 to execute a command, and I logged the response in the console to check if it was working. I also learned how to handle errors if the ESP32 was not responding.

### ESP32
ESP32 as a webserver. The ESP32 runs a small server that listens for requests from my website. When the site sends a request to /command, the ESP32 processes it and sends back a response.

### feedback

## week 6
### 10/3/25
my goal for today is to write more in my learning journal, i also want to create a debugging function for the ESP32, so i can be able to test the sensors for my project if necessary.

done: i have written the most important things ive learned in the last few weeks for my learning journal. 

### 12/3/25
my goal for today is to get to know more about architecture diagrams, how to create them and why you use them.

i learned how to use plantuml for automatic generation of architecture diagrams, i added all components for the esp32, i added the API files used for fetching data and the files used in the frontend. 

### 13/3/25
my goal for today is to create a working debug function which you can activate through the website.

today i fixed my debug function, it didnt work because of a few small bugs i hadnt thought about. like the fact that i needed to use display.display() and 
display.cleardisplay() after everytime i wanted to do something. i also ran into the problem that when you clicked the button for the last time in the debug, it automatically started a new game, it did this because it registered several clicks. to fix this i added a delay.

### 14/3/25
my goal for today is to write code for the ili9341, a bigger screen that will be an upgrade to the ssd1306

today i tested code fo the ili9341 in wokwi, the code worked, now i need to wait for the actual display to arrive so i can test it. i also updated the 3d design to fit the actual screen and not the entire pcb. 
## week 7
### 17/3/25
my goal for today is to start printing my 3d print in the makerslab. this will be my first time printing something i designed myself so there will probably be some problems. when i start my 3d print i will work on documentation.

today i started printing my first real 3d print with the help of a teacher in the makerslab. the first few layers looked very good and tomorrow i will see how it turned out. i also started working on my research question. this took a very long time because i didnt know what i wanted to do. at last i came up with the question: how do i make my entire system safer. i want to make every part of the system safer for now but first i will need to check with a teacher to ask if this is correct question or if it might be too big

### 18/3/25
my goal for today is to get my 3d print and test if the components i already have fit, and if not(probably), what i need to change in my next iteration to make it fit.

necessary changes to 3d design:
- bigger hole for piezo buzzer
- better buttons and bigger holes for buttons
- smaller hole for joystick
- some way to hold joystick in place
- some way to hold display in place

today i have learned a lot about 3d design and the things you dont think about before deisgning someting. my design was good but most of my meausurements were not acurate enough. because of this most parts dont fit or dont have a way to stay in place. for testing purposes i carved out a little plc to try and get the piezo buzzer to fit. this is however too much work and isnt smart to do for every part. that is why i will need to work on a better design and start a second iteration of the front of my design

### 20/3/25
my goal for today is to learn how to use the bambu printers in the makerslab, the difference between the ultimakers and the bambu's is that they are quicker. this means i can 3d print faster. 

unfortunately the bambu printers were taken, and i wont be able to use and learn about them today. however im very confident that this will not be my last iteration of 3d printing. i will be using the ultimaker 2+ for today and check on the progress tomorrow.

### 21/3/25
my goal for today is to use the bambu 3d printer. i have had an explanation on how everything works so i think i can start it all by myselft for now. the ili9341 also arrived(broken screen unfortunately), and i would really like to integrate the display into my prototype.

my print looks very good, unfortunately the screen doesnt fit well enough and the joystick screw pillars arent palced correctly. also the on off switch hole is too small i have now changed these things and will start with my next iteration.

today i learned a lot about 3d printing, my print went wrong twice because one of the printers wasnt leveled correctly. luckily i followed the advice of the teachers at the makers lab to make sure to stay with the print for at least the first layer. because of this i made sure that i started a new print within 15 minutes. i also started with the bigger ili9341 display. i tested code that i made within a simulator and this worked. it did have some problems with the backlight, this was white which made the display flicker. after turning it off the "hello world" worked perfectly. now i only need to integrate it into my project. i have planned to do this this weekend or maybe the monday after this weekend.
## week 8
### 26/3/25
my goal for today is to get my SPI display to work, right now it works but the framerate is bad which makes it look glitchy.
## week 9

## week 10