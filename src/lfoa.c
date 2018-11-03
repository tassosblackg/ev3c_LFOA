/**Main programm of Line Following & Obstacle Avoidance  (aka lfoa ) project
**is based on ev3dev os developed by ev3dev.org
**it implements basic functionallity of different components(color sensor,servo,dc-motors)
** testing for white line Following ...if you change color line you must change conditions in line_follow()
** change thresholds so to fit in your case see (*) points in code
**author:soylisK <soylis.k@gmail.com>
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
#define PWM_max 9        //Pulse Width Modulation ,dc-motors value
#define error_code -127  //error return value
#define crash_dist 230   //minimum distance in(mm) to avoid Obstacle
#define threshold_intensity 72 //color of line to follow --white (*)
#define left_thres 32 //greater than 32 but way less than 70 (*)
#define right_thres 28 // less than that                      (*)
#define out_line 8 //completly out of line
#define true 1
#define false 0
#define sonar_in "in3"
#define color_in "in2"
#define gyro_in "in1"

#include "../include/ev3_all.h"

/*fuctions headers*/
void line_follow(dc_m *m,servo *s,sensor *slist);
void obstacle_avoidance(dc_m *m,servo *s,sensor *slist);
int take_measurement(sensor *slist,char *input_name);
void avoid_circle(dc_m *m, servo *s,sensor *slist, char side); // side arg :=>'L':for left turn side,'R':for right
int8_t movement_side(dc_m *m,servo *s,sensor *slist,int8_t pos,int8_t chanel_i,int Mr,int Ml);

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
        line_follow(motors_node,servo_node,sensor_list);
        //int dist=take_measurement(sensor_list,sonar_in);
        //printf("#dist=%d\n",dist);

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
    Kp=0.6;        //(*)
    Ki=0.02;       //(*)
    Kd=0.7;    //(*)
    int error=0,integral=0,dirivative=0,last_error=0;
    int8_t i=0;
    while (1)
    {

      int distance =take_measurement(slist,sonar_in);  //sonar sensor
      if(distance==error_code) //read new value from sensor fails
        printf("Error in line_follow() distance=take_measurement\n");
      else//e2
      {
          if(distance>crash_dist) //it's safe ..not danger of crashing
          {//ifd
            int last_value =take_measurement(slist,color_in); //color sensor in input2
            if(last_value==error_code)
              printf("Error in line_follow() last_value=take_measurement\n");
            else //e3
            {
                /********|calculate turn_factor,aka smoothness of turn|**********************/ //turn_factor =0.85 perfect
                last_error=error;
                error=threshold_intensity-last_value;
                integral+=error;
                dirivative=error - last_error;

                /**test and try to keep turn_factor<1,because you don't want to overpower motors*/
                turn_factor=(error*Kp + integral*Ki + dirivative*Kd)/threshold_intensity;
               // turn_factor=0.85;
		            /******************************************************************************/
                if(last_value>=threshold_intensity) //forward
                {
                  int Mr=turn_factor*PWM_max;
		              int Ml=turn_factor*PWM_max;
		              run(m,Mr,Ml,dc_addr);

                }
                if((last_value<left_thres) &&(last_value>out_line)) //right out
                {
                  run(m,turn_factor*PWM_max,-PWM_max,dc_addr);

                }
                if( (last_value>=left_thres)&&(last_value<threshold_intensity) ) //left out
                {
                  float sub=turn_factor*PWM_max;
                  run(m,PWM_max,(-sub),dc_addr);

                }
                if(last_value<out_line) //completly out of line case
                {
                    if(last_error==0) //you start out of line
                    {
                      run(m,PWM_max,-PWM_max,dc_addr);
                    }
                    else if ((last_error>=left_thres)&&(last_error<threshold_intensity)) //out from left
                    {
                      //turn to the right
                      run(m,turn_factor*PWM_max,-PWM_max,dc_addr);
                    }
                    else if ((last_error>out_line)&&(last_error<=right_thres)) //out from right
                    {
                      float Ml=turn_factor*PWM_max;
                      //turn to the left
                      run(m,PWM_max,-Ml,dc_addr);
                    }
                    else if(last_error>=threshold_intensity) //was on the line moving straight frwd, but now I'm not
                    {
                      //random turn ..in our case left turn is our need..left turn
		                  float sub=PWM_max*turn_factor;
                      run(m,turn_factor*PWM_max,-PWM_max,dc_addr); //90 dgr rotation to left
                    }
                    else
                      printf("ERROR YOU ARE OUT of line intensity=%d\n",last_value);
                }
            }//e3
          }//ifd
          else
          {
            stop(m,dc_addr);
	          //obstacle_avoidance(m,s,slist);
          }


        }//e2
    }//while

}

void obstacle_avoidance(dc_m *m,servo *s,sensor *slist)
{
  //stop vehicle
  stop(m,dc_addr);
  //set gyroscope value..first of all callibrate
  //check distance
  int distance=take_measurement(slist,sonar_in);
  int init_angle=take_measurement(slist,gyro_in); //what's your direction
  if((distance ==error_code)||(init_angle==error_code))
    printf("Error in obstacle_avoidance() --take_measurement..\n");
  else
  {
      //1st turn right move forward
      //avoid_circle(m,s,slist,'R');
      //2nd turn left and move forward
     // avoid_circle(m,s,slist,'L');
      //3d turn left again
     // avoid_circle(m,s,slist,'R');
      //4th turn right again
     // avoid_circle(m,s,slist,'L');
      //-----------------------------
      run(m,PWM_max-2,-PWM_max,dc_addr); //turn a little to the right
      stop(m,dc_addr);
      run(m,PWM_max-1,-PWM_max+1,dc_addr); //mv forward a little
      stop(m,dc_addr);
      run(m,PWM_max+1,-PWM_max+1,dc_addr); //turn a lot to the left
      stop(m,dc_addr);
      run(m,PWM_max-1,-PWM_max+1,dc_addr); //mv forward a little
      stop(m,dc_addr);
      //hope that I avoid obstacle
      int intens=0;
  do{
 		 run(m,PWM_max,-PWM_max,dc_addr); //move forward --hope to find line
     intens=take_measurement(slist,color_in);
	}while(intens!=threshold_intensity); //till found line back

  }
}

/**basicly it updates the value of the need sensor**/
int take_measurement(sensor *slist,char *input_name)
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
int8_t movement_side(dc_m *m,servo *s,sensor *slist,int8_t pos,int8_t chanel_i,int Mr,int Ml)
{
    int rv=false; //return value
    turn(s,chanel_i,pos,servo_addr);
    int distance=take_measurement(slist,sonar_in); //take measurement from sonar
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
