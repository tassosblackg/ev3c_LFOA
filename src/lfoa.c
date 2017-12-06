/**Main programm of Line Following & Obstacle Avoidance  (aka lfoa ) project
**is based on ev3dev os developed by ev3dev.org
**it's implements basic functionallity of different components(color sensor,servo,dc-motors)
**author:soyliK <soylis.k@gmail.com>
**/

/**set address for each controller in Daisy Chain connection**
**-----------------------------------------------------------------------------
**!!!IMPORTANT: set mode on the ev3 port ,where you have connected controllers
** set ev3 input4(in our case) mode :ntx-i2c
**-----------------------------------------------------------------------------
**Cross-Compile with Docker: docker run --rm --it -v /c/Users/myname/example/:/src -w /src ev3cc
**look at : HitechnicDoc folder
**for More abut I2C **/

#define dc_addr 0x01    //unshifted address (else 0x02/0x03)
#define servo_addr 0x02 //unshifted address (else 0x04/0x05)
#define PWM_1 0x30  //Pulse Width Modulation ,motors value
#include "ev3_all.h"
void line_follow();
void obstacle_avoidance();


int main()
{
    dc_m *motors_node=(dc_m *)malloc(sizeof(dc_m)); //one node for motors controler(2motors)
    servo *servo_node=(servo*)malloc(sizeof(servo)); //one node for servo controller(up to 6 servos)
    sensor *sensor_list=NULL; //lego sensor nodes list

    if( (motors_node!=NULL)&&(servo_node!=NULL) )
    {
      /*initialize motors , servos and sensors*/
      init_m(&motors_node,dc_addr);
      init_s(&servo_node,1,PWM_en_toff,servo_addr);
      append2list(&sensor_list);
      if (sensor_list!=NULL)
      {
        //yeah
        printf("everything is fine\n");
      }
      else
        printf("sensor_list not allocated..\n");



    }
    else
      printf("ERROR:ALLOCATION MEMORY FAILED..\n");

    getchar();
    return 0;
}

/**functions bodies'****************/

void line_follow(dc_m *m,servo *s)
{


}

void obstacle_avoidance(dc_m *m,servo *s)
{

}
