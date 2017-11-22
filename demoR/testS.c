#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

//test- chk I2C comm servo

int main()
{

        printf("Main runsssss....\n");
        int8_t fd = open("/dev/i2c-6",O_RDWR);
        printf("FILE discriptor : fd=%d\n",fd);
        if(fd>0)
        {
                ioctl(fd,I2C_SLAVE,0x02);
                unsigned char buf[2]={0x48,0x00};
                write(fd,buf,2);
                printf("Init write...\n");
                //close(fd);
		unsigned char buf2[2]={0x42,0x7F};
                write(fd,buf2,2);
                /*int8_t fd = open("/dev/i2c-6",O_RDWR);
                ioctl(fd,I2C_SLAVE,0x01);
                unsigned char buf2[4]={0x45,0x30,0x46,0x30};
                write(fd,buf2,4);
                printf("FIRST MOTOR write...\n");*/
               /* unsigned char buf3[2]={0x46,0x60};
                write(fd,buf3,2);
                printf("SECOND MOTOR write..\n");*/
        }

        close(fd);
        getchar();
        return 0;
}

