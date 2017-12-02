/**ev3_servo.h is the header file from servo-motor FUNCTIONS**
**part of ev3c_LFOA project
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
**!!Important: Check how you have connected your Servos on the controller
**!!Because addressing is made by the connection position(chanel) of servos on the controller
**--------------------------------------------------------------------
**|address of the controller: is based -> on how we connect the controller's to the brick/
**->DC_motors + Servos connection Daisy Chain. in our case we use input4
**and set input4 mode to :nxt-i2c
**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
**___________________________________
**author:soylisK <soylis.k@gmail.com>
**-----------------------------------
**controller register {address,channel1-value,chanel2_value...} //up to 6 values and one addressing
** address is the starting point of writing in the register..writing is sequential
**More infos about Hitechnic Controllers addressing, modes, values check :HitechnicDoc
**More infos about i2c :ev3dev.org drivers,sensors appendix
**/

#ifndef EV3_SRV
#define EV3_SRV
/**i2c-6 stands for i2c-(port_number+2), im my case my input port is 4**/
#define dev_path "/dev/i2c-6" //!! changes in depend of which port you have connected your controller
#define init_pos 0xA6 //position of servo that we want to have at start ..straight forward (166)
#define turn_l 0x37   //left position to rotate(55)
#define turn_r 0xFF   //right position to rotate(255)
#define PWM_en_close 0xFF //close servo controller--stops
#define PWM_en_toff 0xAA  //close timer mode
#define PWM_en_ton 0x00   //open timer mode

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct servo_motors{

  char chanel_address[6];  //one char for address of each chanel ,Hex --up to 6 servos/controller
  int8_t fd;              //file descriptor for device, where to write
  char buf[7];           //buffer address ,value to write--6values +1 register's address
  char value[6];         //one value per channel of servos
  int8_t status;        //for reading purpose if its necessary
  char step_time;       //step time for the furthest to move servo
}servo;

/**initialize servo node*
**Args: &s, servo node's address
**      -numbOfservos how many sensors have you connected on the controller ---up to 6
**      -mode ,servo mode you want PWM_en_toff or PWM_en_ton
**      - controller ,servo's controller address
**/
void init_s(servo **s,int8_t numbOfservos,char mode,char controller);
/**turn servo to wanted position
**ARgs: s servo node of struct typedef
**      channel_i which servo you want to set from 0..5 (6servos)
**      position value of servo to been set
**      controller address of servo controller
**/
void turn(servo *s,int8_t chanel_i,char postion,char controller);

void stop();
/**free allocate memory of servo's node*/
void delete(servo *s);

#endif
