#include <stdio.h>
#include <stdlib.h>

int main()
{
    float Kp,Kd,Ki;
    int target=80;
    int max=79;
    int min=5;
    int array[25];
    Kp=0.6;
    Kd=0.5;
    Ki=0.013;
    printf("main start\n");
    printf("[ ");
    int i;
    for (i=0;i<25;i++)
    {
        array[i] = (rand() % (max + 1 - min)) + min;
        printf("%d|",array[i]);
     
    }
    printf(" ]\n\n");
    //calculate turn factor
    int integral=0;
    int last_error=0;
    int error=0;
    int dir=0;
    float turn_factor=0;
    printf("\n#{ ");
    int j;
    for(j=0;j<25;j++)
    {
      error=(target-array[j]);
      integral=integral+error;
      dir=error-last_error;
      turn_factor=((error*Kp) + (integral*Ki) +(dir*Kd))/(max-min); //kanonikopoihsh gyrw apo to 1
      printf("%.3f |",turn_factor);
      turn_factor=0;
      error=0;
      last_error=error;
    }
    printf(" }#\n");
    
    printf("endddd...\n");
	system("PAUSE");
    return 0;
}
