/***testR.c is a demo test for checking dc-motors functionality
**for more infos about registers' data and values check
**hitechnic controller's manual
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int main()
{

        printf("Main runsssss....\n");
	//i2c-6 =i2c-(port_number+2)...in this case we have input4 ,so 4+2=6..changes depends on how you connected your controler
        int8_t fd = open("/dev/i2c-6",O_RDWR); //open device file ..(hitechnic controller connected to input4 on ev3 brick)
        printf("FILE discriptor : fd=%d\n",fd); 
        if(fd>0)
        {
                ioctl(fd,I2C_SLAVE,0x01);
                unsigned char buf[5]={0x44,0x00,0x00,0x00,0x00}; //initialize controller [register's address,motor1's mode,motor1's_pwm,motor2's_pwm,motor2's_pwm]
              	int w1= write(fd,buf,5);
		 // int w1=i2c_smbus_write_block_data(fd,0x45,1,buf);
                printf("Init write...w1=%d\n",w1); //check if write accomplished
		//close(fd);
                
		
                unsigned char buf2[3]={0x45,0x9,-0x9}; //moving backwards.. [register's address,motor1's_pwm,motor2's_pwm]
                int w2=write(fd,buf2,3);
                printf("FIRST MOTOR write...w2=%d\n",w2); //check if write accomplished
               /* unsigned char buf3[2]={0x46,-0x20};
                int w3=write(fd,buf3,2);
                printf("SECOND MOTOR write..w3=%d\n",w3);*/
        }

	close(fd);
        getchar();
        return 0;
}


