/**demoS.c is a test for servo motor functionallity
**for more infos check hitechnic controller's manual-doc\
**/
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
                ioctl(fd,I2C_SLAVE,0x02);
                unsigned char buf[2]={0x48,0xAA}; //initiallize servo mode
                int w1= write(fd,buf,2);
                printf("Init write...w1=%d\n");
                /*unsigned char readb[200];
		read(fd,readb,200);
		int i;
		for(i=0;i<200;i++)
			printf("read[%d]=%c\n",i,readb[i]);*/ //read data to see if everything is fine
		//close(fd);
		printf("******\n");
		unsigned char buf2[2]={0x42,0x37}; //set value(0x37) to servo at channel 1 ->0x42
		int w2=write(fd,buf2,2);
                printf("w2=%d\n",w2); //checks if write accomplished
                
        }

        close(fd);
        getchar();
        return 0;
}

