/**ev3_servo.c functions' body code
**part of ev3c_LFOA project..main functionality of gyroscope servo-motor
**author: soylisK <soylis.k@gmail.com>
**
**/
#include "ev3_servo.h"


void init_s(servo **s,int8_t numbOfservos,char mode,char controller)
{
    if(numbOfservos>6)
        printf("Error:Servos' init()...number Of servos mustn't be above 6/per controller..\n");
    else
    {
        (*s)->fd=open(dev_path,O_RDWR);
        if( ((*s)->fd)>0 )
        {
            ioctl((*s)->fd,I2C_SLAVE,controller);
            unsigned char init_buf[2];
            init_buf[0]=PWM_addr;
            init_buf[1]=mode;
            int8_t wr=write((*s)->fd,init_buf,2); //init set servo mode
            if(wr<0)
              printf("ERROR during writing in init_s() function-servos..\n");
            int8_t i,j;
            for(i=0;i<numbOfservos;i++)
            {
                (*s)->chanel_address[i]=(0x42)+i;
                //(*s)->value[i]=;

            }

        }
        else
            printf("ERROR:fileDiscriptor i servos' inti() doesn't exists..");

    }
}

void turn(servo *s,int8_t chanel_i,char position,char controller)
{
    ioctl(s->fd,I2C_SLAVE,controller);
    s->value[chanel_i]=position;
    s->buf[0]=s->chanel_address[chanel_i];
    s->buf[1]=position;
    int8_t wr=write(s->fd,s->buf,2);
    if(wr<0)
      printf("@ERROR during writing in turn() function-servos..\n");
}

void delete_s(servo *s)
{
    free(s);
}
