/**ev3_dcmotor.c main functionality ---functions bodies' code
**part of ev3c_LFOA project
**author: soylisK <soylis.k@gmail.com>
**/
#include "ev3_dcmotor.h"


void init_m(dc_m **m,char controller)
{
		(*m)->fd=open(dev_path,O_RDWR); //file descriptor open for read/write
		if( ((*m)->fd) >0)
		{
				ioctl((*m)->fd,I2C_SLAVE,controller);
				(*m)->mode_motor[0]=0x44; //motor1's mode address
				(*m)->mode_motor[1]=0x47; //motor2's mode address
				//motors' pwm addresses
				(*m)->motors[0]=0x45; //motor1
				(*m)->motors[1]=0x46; //motor2
				//set mode for 1st motor
				(*m)->buf[0]=(*m)->mode_motor[0];
				(*m)->buf[1]=0x00; //mode motor1
				(*m)->buf[2]=0x00; //pwm motor1
				(*m)->buf[3]=0x00; //pwm motor2
				(*m)->buf[4]=0x00; //mode motor2
				write((*m)->fd,(*m)->buf,5);

				//close(m->fd);
		}
		else
			printf("ERROR:DC_MOTOR init()...file not found!!!\n" );
}


void run(dc_m *m,char value1,char value2,char controller)
{
		ioctl(m->fd,I2C_SLAVE,controller);
		//set 1st motor value
		m->buf[0]=m->motors[0];
		m->buf[1]=value1;
		//set 2nd motor value
		m->buf[2]=value2;
		write(m->fd,m->buf,3);
		//close(m->fd);

}

void stop(dc_m *m,char controller)
{
		ioctl(m->fd,I2C_SLAVE,controller);
		//set 1st motor value
		m->buf[0]=m->motors[0];// motor1 pwm address
		m->buf[1]=PWM_brake;
		//set 2nd motor value
		m->buf[2]=PWM_brake;
		write(m->fd,m->buf,3);

}

void delete_m(dc_m *m)
{
		free(m);
}
