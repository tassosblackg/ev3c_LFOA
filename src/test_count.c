#include "../include/ev3_sensor.h"
#include "ev3_sensor.c"
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("STarts here \n...#sens=%d",numbOfSen);
	printf("..{calling...\n");
	//char p[];
	//p=sensor_driver_path;
	
	int8_t filesN=countSensors(sensor_driver_path);
	printf("There %d sensors in this path\n",filesN);

	getchar( );

	return 0; 


}
