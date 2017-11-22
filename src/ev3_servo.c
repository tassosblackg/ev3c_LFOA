/**ev3_servo.c functions' body code
**part of ev3c_LFOA project..main functionality of gyroscope servo-motor
**author: soylisK <soylis.k@gmail.com>
**/
#include "../include/ev3_servo.h"


void init_s(servo **s,int8_t numbOfservos,char controller)
{
    if(numbOfservos>6)
        printf("Error:Servos' init()...numbOfservos mustn't be above 6/per controller..\n");
    else
    {
        (*s)->fd=open(dev_path,O_RDWR);
        if( ((*s)->fd)>0 )
        {
            ioctl((*s)->fd,I2C_SLAVE,controller);
            int8_t i;
            for(i=0;i<numbOfservos/2;i++)
            {
                (*s)->chanel_address[i]=(0x42)+i;
                (*s)->value[i]=PWM_en_ton;

                (*s)->buf[i+i]=(*s)->chanel_address[i]; //write address in the write position of buf
                (*s)->buf[i+(i+1)]=(*s)->value[i];      //set the value in right position of buf

                //each servo has 2 chars in buf {address,value}--so the length of the write buf-data it
                //depends on the number of servos
                write((*s)->fd,(*s)->buf,numbOfservos*2);

            }
        }
        else
            printf("ERROR:fileDiscriptor i servos' inti() doesn't exists..");

    }
}

void turn(servo *s,int8_t chanel_i,char postion,char controller)
{
    ioctl(s->fd,I2C_SLAVE,controller);
    s->value[chanel_i]=postion;
    s->buf[chanel_i+chanel_i]=s->chanel_address[chanel_i];
    s->buf[chanel_i+chanel_i+1]=s->value[chanel_i];
    write(s->fd,s->buf,2);
}

void delete(servo *s)
{
    free(s);
}
