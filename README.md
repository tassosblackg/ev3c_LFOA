# ev3c_LFOA :oncoming_taxi:

An Implementation for Lego EV3 Mindstorm & Hitechnic Kit.

Libs for each sensor, motor etc and an simple example of line following and obstacle avoidance code.

:large_orange_diamond: Implemented Modules:
---------------------
:ballot_box_with_check: **Hitechnic DC Motors** (***I2C protocol***)

:ballot_box_with_check: **Hitechnic Servo Motor** (***I2C protocol***)

:ballot_box_with_check: **Lego Sensors** like color sesnor, sonar, etc.

---------------------------------------------------------------------------------------------
:large_orange_diamond: Main Project (ALL you need):
---------------------------
 * include/
 * src/
 * Makefile
 to run the programm
 
 :large_orange_diamond: Modules that you can use for any purpose:
 ------------------------------------------------------------------

 Name                 | Description
 :---:                | :---
 [ev3_dcmotor.c]      | Module with functionality of Hitechnic DC motors
 [ev3_servo.c]        | Module with functionality of Hitechnic Servo motors
 [ev3_sensor.c]       | Module for read Lego sensors like IR
 [ev3_file.c]         | Module for reading/writing from/to files
 [test_count.c]       | Test to count connected sensors on EV3 brick
 [lfoa.c]             | An example of using the above module to solve lfoa

 [ev3_dcmotor.c]: https://github.com/tassosblackg/ev3c_LFOA/blob/master/src/ev3_dcmotor.c
 [ev3_servo.c]:   https://github.com/tassosblackg/ev3c_LFOA/blob/master/src/ev3_servo.c
 [ev3_sensor.c]:  https://github.com/tassosblackg/ev3c_LFOA/blob/master/src/ev3_sensor.c
 [ev3_file.c]:    https://github.com/tassosblackg/ev3c_LFOA/blob/master/src/ev3_file.c
 [test_count.c]:  https://github.com/tassosblackg/ev3c_LFOA/blob/master/src/test_count.c
 [lfoa.c]:        https://github.com/tassosblackg/ev3c_LFOA/blob/master/src/lfoa.c
 
  :large_orange_diamond: Hitechnic Documentation (read this first):
 --------------------------------------------------------------------
 Name                 | Description
 :---:                | :---
 [dc-motor]           | Documentation of Hitechnic DC motors
 [servo-motor]        | Documentation of Hitechnic Servo motors

 [dc-motor]:    https://github.com/tassosblackg/ev3c_LFOA/blob/master/HitechnicDoc/HiTechnic-Motor-Controller-Specification.pdf
 [servo-motor]: https://github.com/tassosblackg/ev3c_LFOA/blob/master/HitechnicDoc/HiTechnic-Servo-Controller-Specification.pdf
 
:bangbang: Notice :bangbang: :
-------
You can re-write LineFollowning and obstacle avoidance code as you wish (just ignore ~~***lfoa.c***~~ file).

***lfoa.c*** is a sample code to guide you through using libs for building a project on ev3. See it as an example on how to use the different modules.

:small_red_triangle_down: To Do List :construction: :
-----------
 - [ ] ev3_button

 - [ ] ev3_LCD
 
 :large_orange_diamond: Show Room :tv::tada: :
 ------------
 ![Vehicle View Top Down](media-files/IMG_20180702_190654.jpg)
 
 :sparkles:***Example Sonar-Obstacle Avoid -->***
 
 ![Moving-Stop](media-files/Tdgu2fSVTr.gif)
 
 :sparkles:***ARM Servo Motion***
 
 ![Axis-Motion-ARM](media-files/oVXPALLY5k.gif)

______________________________________________

:warning: **READ quick guide for a fast set up and use.**

:warning: **READ carefully the block comments in each file.**

:fax: *Feel free to contact through discussions' section.*

:mailbox_with_mail: *soylis.k@gmail.com*

More infos for ev3dev see: https://www.ev3dev.org

 # :godmode: PEACE OUT! :sunglasses:
---------------------------------------------------------------------------------------------
