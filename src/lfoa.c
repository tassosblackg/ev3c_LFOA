/**Main programm of Line Following & Obstacle Avoidance  (aka lfoa ) project
**is based on ev3dev os developed by ev3dev.org
**it's implements basic functionallity of different components(color sensor,servo,dc-motors)
**author:soyliK <soylis.k@gmail.com>
**/

/**set address for each controller in Daisy Chain connection**
**look at :
**for More abut I2C **/
#define dc_addr 0x01    //unshifted address (else 0x02/0x03)
#define servo_addr 0x02 //unshifted address (else 0x04/0x05)
#define PWM_1 0x30  //Pulse Width Modulation ,motors value
#include "ev3_all.h"
void line_follow();
void obstacle_avoidance();


int main()
{
    dc_m *motors_node=(dc_m *)malloc(sizeof(dc_m));
    servos *servo_node=(servos*)malloc(sizeof(servos));
    sensor *sensor_list=(sensor*)malloc(sizeof(sensor));

    if( (motors_node!=NULL)&&(servo_node!=NULL) )
    {
      /*initialize motors and servos*/
      init_m(motors_node,dc_addr);
      init_s(servo_node,servo_addr);


    }
    else
      printf("ERROR:ALLOCATION MEMORY FAILED..\n");

    getchar();
    return 0;
}

/**functions bodies'****************/

void line_follow(dc_m *m,servos *s)
{


}

void obstacle_avoidance(dc_m *m,servos *s)
{

}
