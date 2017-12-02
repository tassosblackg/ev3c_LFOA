/**ev3_dcmotor.h is the header file from dc-motor FUNCTIONS**
**part of ev3c_LFOA project
**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
**!!Important: Check how you have connected your motors on the controller
**!!Because addressing is made by the connection position of motors on the controller
**!!so Motor1 and Motor2 matches the address for Left and Right motor
**--------------------------------------------------------------------
**->DC_motors + Servos connection Daisy Chain.
**|address of the controller: is based -> on how we connect the controller's to the brick/
**in our case we use input4 for controllers
**and set input4 mode to :nxt-i2c 
**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
**___________________________________
**author:soylisK <soylis.k@gmail.com>
**-----------------------------------
**/

#ifndef EV3_DC
#define EV3_DC

/**i2c-6 stands for i2c-(port_number+2), im my case my input port is 4**/
#define dev_path "/dev/i2c-6" //!!changes it depends in which port you have connected your controller!!
#define PWM_val 0x07    //value to run --for small distances 0x07-0x09 //speed set pwm
#define PWM_brake 0x00 //brake value
#define PWM_float -128//FFFF FFFF FFFF FF80???

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

typedef struct vehicle_dc_motors{

  char mode_motor[2];      //mode address to motor1,2    ,Hex
  char motors[2];         // "left or right" motor address Motor1,2 ,Hex
  int8_t fd;         // fd file to write/read in device
  char buf[5];      // buffer where we write motorAddress, and value in Hex

}dc_m;

/**initial function ,opens  device's file**
**and sets motor's mode**
**Args: &m (dc_motor node's address)
**      controller, dc_motor's controller address
**MODES:
**________________________
**|0x00 |PWM             |
**|0x01 |Speed controller|
**|0x10 |Position Control|
**|_____|________________|
**/
void init_m(dc_m **m,char controller);

/**Run motor ,rotate**
**Args: -m pass a dc_motor node of struct type dc_m
**      -value what PWM value to set to the motor
** if value is >0 motor runs forwards
** elsif value<0 motors runs backwards
** -100<value<100 (value is PWM)
**---------------------------------------------------
**for tuning left or right change PWM value of motor side,
**where you want to turn ,so it will be smaller than the other
**ex.: turn_left -> left_motor_value < right_motor_value
**/
void run(dc_m *m,char value1,char value2,char controller);


/**Brake-stops the motor**
**set PWM value to 0**/
void stop(dc_m *m,char controller);

/**deletes a node of dc_motor
**by free() its allocate memory
**/
void delete(dc_m *m);


#endif
