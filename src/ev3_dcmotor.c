/**ev3_dcmotor.c main functionality ---functions bodies' code
**part of ev3c_LFOA project
**author: soylisK <soylis.k@gmail.com>
**/
#include "../include/ev3_dcmotor.h"


void init_m(dc_m **m,char controller)
{
		(*m)->fd=open(dev_path,O_RDWR); //file descriptor open for read/write
		if( ((*m)->fd) >0)
		{
				ioctl((*m)->fd,I2C_SLAVE,controller);
				(*m)->motors[0]=0x44;
				(*m)->motors[1]=0x47;
				//set mode for 1st motor
				(*m)->buf[0]=(*m)->motors[0];
				(*m)->buf[1]=0x00;
				(*m)->buf[2]=(*m)->motors[1];
				(*m)->buf[3]=0x00;
				write((*m)->fd,(*m)->buf,4);

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
		m->buf[2]=m->motors[1];
		m->buf[3]=value2;
		write(m->fd,m->buf,4);
		//close(m->fd);

}

void stop(dc_m *m,char controller)
{
		ioctl(m->fd,I2C_SLAVE,controller);
		//set 1st motor value
		m->buf[0]=m->motors[0];
		m->buf[1]=PWM_brake;

		//set 2nd motor value
		m->buf[2]=m->motors[1];
		m->buf[3]=PWM_brake;
		write(m->fd,m->buf,4);

}

void delete(dc_m *m)
{
		free(m);
}
