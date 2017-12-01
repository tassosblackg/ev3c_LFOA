#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int main()
{

        printf("Main runsssss....\n");
        int8_t fd = open("/dev/i2c-6",O_RDWR);
        printf("FILE discriptor : fd=%d\n",fd);
        if(fd>0)
        {
                ioctl(fd,I2C_SLAVE,0x01);
                unsigned char buf[2]={0x48,0xAA};
                int w1= write(fd,buf,2);
                printf("Init write...w1=%d\n");
                unsigned char readb[200];
		read(fd,readb,200);
		int i;
		for(i=0;i<200;i++)
			printf("read[%d]=%c\n",i,readb[i]);
		//close(fd);
		printf("******\n");
		unsigned char buf2[2]={0x42,0x37};
		int w2=write(fd,buf2,2);
                printf("w2=%d\n",w2);
                
        }

        close(fd);
        getchar();
        return 0;
}

