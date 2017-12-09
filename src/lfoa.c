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
#define crash_dist 230   //minimum distance in(mm) to avoid Obstacle
#define threshold_intensity 77 //color of line to follow --white (*)
#define left_thres 32 //greater than 32 but way less than 70 (*)
#define right_thres 26 // less than that                      (*)
#define true 1
#define false 0


#include "../include/ev3_all.h"

/*fuctions headers*/
void line_follow(dc_m *m,servo *s,sensor *slist);
void obstacle_avoidance(dc_m *m,servo *s,sensor *slist);
int8_t take_measurement(sensor *slist,char *input_name);
void avoid_circle(dc_m *m, servo *s,sensor *slist, char side); // side arg :=>'L':for left turn side,'R':for right
int8_t movement_side(dc_m *m,servo *s,sensor *slist,int8_t pos,int8_t chanel_i,int8_t Mr,int8_t Ml);

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
        turn(servo_node,0,init_pos,servo_addr);
        //line_follow(motors_node,servo_node,sensor_list);
        sensor *s2;
	      s2=search4sensor(sensor_list,"in3");
	      printf("@s2=%d\n",s2);
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
    int8_t error=0,integral=0,dirivative=0,last_error=0;
    while (1)
    {

      int8_t distance =take_measurement(slist,"in3");  //sonar sensor
      if(distance==error_code) //read new value from sensor fails
        printf("Error in line_follow() distance=take_measurement\n");
      else//e2
      {
          if(distance>crash_dist) //it's safe ..not danger of crashing
          {//ifd
            int8_t last_value =take_measurement(slist,"in2"); //color sensor in input2
            if(last_value==error_code)
              printf("Error in line_follow() last_value=take_measurement\n");
            else //e3
            {
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
                else
                {
                  //obstacle_avoidance
                  obstacle_avoidance(m,s,slist);
                }
              }//e3
          }//ifd


        }//e2
    }//while

}

void obstacle_avoidance(dc_m *m,servo *s,sensor *slist)
{
  //stop vehicle
  stop(m,dc_addr);
  //set gyroscope value..first of all callibrate
  //check distance
  int8_t distance=take_measurement(slist,"in3");
  int8_t init_angle=take_measurement(slist,"in3"); //what's your direction
  if((distance ==error_code)||(init_angle==error_code))
    printf("Error in obstacle_avoidance() --take_measurement..\n");
  else
  {
      //1st turn right move forward
      avoid_circle(m,s,slist,'R');
      //2nd turn left and move forward
      avoid_circle(m,s,slist,'L');
      //3d turn left again
      avoid_circle(m,s,slist,'R');
      //4th turn right again
      avoid_circle(m,s,slist,'L');
  }

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

/***tell me if i can go from that side*/
int8_t movement_side(dc_m *m,servo *s,sensor *slist,int8_t pos,int8_t chanel_i,int8_t Mr,int8_t Ml)
{
    int8_t rv=false; //return value
    turn(s,chanel_i,pos,servo_addr);
    int8_t distance=take_measurement(slist,"in3"); //take measurement from sonar
    if(distance==error_code)
        printf("Error in movement_side() take_measurement..\n");
    else
    {
        if(distance>crash_dist)
        {

          run(m,Mr,-Ml,dc_addr); //turn vehicle to that position..right
          turn(s,chanel_i,init_pos,servo_addr); //turn servo straight forward
          rv=true;
        }
        else
        {
          printf("I can't turn to that side..\n");
          rv=false;
        }
      }
    return(rv);
}

void avoid_circle(dc_m *m, servo *s,sensor *slist, char side)
{
    if (side=='R')
    {
      /* code */
      int8_t flag = movement_side(m,s,slist,turn_r,0,PWM_max/2,PWM_max); //1st servo chanel is 0
      if(flag) //i can go so move forward
        run(m,PWM_max,-PWM_max,dc_addr);
      else
        stop(m,dc_addr);
    }
    else if(side=='L')
    {
      int8_t flag = movement_side(m,s,slist,turn_l,0,PWM_max,PWM_max/2); //1st servo chanel is 0
      if(flag) //i can go so move forward
        run(m,PWM_max,-PWM_max,dc_addr);
      else
        stop(m,dc_addr);
    }
    else
      printf("error:invalid side argument, side='L'or'R'..check avoid_circle() call\n ");

}
