#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
//test I2C comm between dc-motors
int main()
{

        printf("Main runsssss....\n");
        int8_t fd = open("/dev/i2c-6",O_RDWR);
        printf("FILE discriptor : fd=%d\n",fd);
        if(fd>0)
        {
                ioctl(fd,I2C_SLAVE,0x01);
                unsigned char buf[4]={0x44,0x00,0x47,0x00};
                write(fd,buf,4);
                printf("Init write...\n");
		            //close(fd);

		            /*int8_t fd = open("/dev/i2c-6",O_RDWR);
		            ioctl(fd,I2C_SLAVE,0x01);*/
                unsigned char buf2[4]={0x45,0x30,0x46,0x30};
                write(fd,buf2,4);
                printf("FIRST MOTOR write...\n");
               /* unsigned char buf3[2]={0x46,0x60};
                write(fd,buf3,2);
                printf("SECOND MOTOR write..\n");*/
        }

	close(fd);
        getchar();
        return 0;
}
