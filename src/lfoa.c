/**Main programm of Line Following & Obstacle Avoidance  (aka lfoa ) project
**is based on ev3dev os developed by ev3dev.org
**it's implements basic functionallity of different components(color sensor,servo,dc-motors)
** testing for white line Following ...if you change color line you must change conditions in line_follow()
** change thresholds so to fit in your case see (*) points in code
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

#define dc_addr 0x01        //unshifted address (else 0x02/0x03)
#define servo_addr 0x02    //unshifted address (else 0x04/0x05)
#define PWM_max 0x9        //Pulse Width Modulation ,dc-motors value
#define error_code -127  //error return value
#define crash_dist 28   //minimum distance to avoid Obstacle
#define threshold_intensity 77 //color of line to follow --white (*)
#define left_thres 32 //greater than 32 but way less than 70 (*)
#define right_thres 26 // less than that                      (*)
#include "ev3_all.h"
void line_follow(dc_m *m,servo *s,sensor *slist);
void obstacle_avoidance(dc_m *m,servo *s,sensor *slist);
int8_t take_measurement(sensor *slist,char *input_name);
float pid_controll();

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

void line_follow(dc_m *m,servo *s,sensor *slist)
{
    float Kp,Ki,Kd,turn_factor,Mr,Ml;
    Mr=Ml=PWM_max; //set maximum motors' value
    /**set this parameters according your conditions**/
    Kp=0.3;        //(*)
    Ki=0.2;       //(*)
    Kd=0.013;    //(*)
    int8_t error=0,intergral=0,dirivative=0,last_error=0;
    while (1)
    {

      int8_t dinstance =take_measurement(slist,"in3");  //sonar sensor
      if(distance>crash_dist) //it's safe ..not danger of crashing
      {
        int8_t last_value =take_measurement(slist,"in2"); //color sensor in input2
        /********|calculate turn_factor,aka smoothness of turn|**********************/
        error=threshold_intensity-last_value;
        integral+=error;
        dirivative=error - last_error;
        last_error=error;
        /**test and try to keep turn_factor<1,because you don't want to overpower motors*/
        turn_factor=(error*Kp + integral*Ki + dirivative*Kd)/threshold_intensity;
        /******************************************************************************/
        if((last_value>=left_thres)&&(last_value<threshold_intensity))//out of line from left
        {
          //calculate turn_factor
          //make the turn
          Mr=turn_factor*PWM_max;
          run(m,Mr,-Ml,dc_addr);

        }
        if( (last_value>=right_thres)&&(last_value<left_thres)) //out of line from right
        {
          //calculate turn_factor
          //make turn
          Ml=turn_factor*PWM_max;
          run(m,Mr,-Ml,dc_addr);
        }
        if(last_value>=threshold_intensity) //in line
        {
          //move forward
          Mr=Ml=PWM_max; //just to be sure
          run(m,Mr,-Ml,dc_addr);
        }
      }
      else
      {
        //obstacle_avoidance
      }
    }

}

void obstacle_avoidance(dc_m *m,servo *s,sensor *slist)
{
  //set gyroscope value..first of all callibrate
  
}
float pid_controll(int8_t value)
{

  int8_t error=threshold_intensity-value;
  integral+=error;
  dirivative=error-last_error;
  last_error=error;

  turn_factor=(error*Kp+integral*Ki+dirivative*Kd)/threshold_intensity;

  return turn_factor;

}
/**basicly it updates the value of the need sensor**/
int8_t take_measurement(sensor *slist,char *input_name)
{
    int8_t value;
    sensor *node=NULL;
    node=search4sensor(slist,input_name);
    if(node!=NULL)
    {
      update_sensor_value(node);
      return (node->data);
    }
    else
    {
      printf("Wrong input_name..\n");
      return(error_code); //error code
    }
}
