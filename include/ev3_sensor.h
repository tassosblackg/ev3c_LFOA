/**ev3_ sensor header file for sensors' functions
** header -function for ev3dev --see ev3dev.org
**----------------------------------------------
**author:soylisK
**/

//double inclusion guards
#ifndef __EV3_SENSOR
#define __EV3_SENSOR

#include <inttypes.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ev3_file.h"

#define str_len 15
#define sensor_driver_path "/sys/class/lego-sensor"
#define filesName "sensor" //files' name in sensor_driver_path
#define fullpath "/sys/class/lego-sensor/sensor"
#define driverf "/driver_name" //sensor's driver's name file
#define portf  "/address" //port name
#define modef   "/mode"   //mode of sensor
#define pollf   "/poll_ms" //polling time file
#define dataf  "/value0"  //useful sensors data
uint8_t numbOfSen;  //how many sensors are connected to the brick



/**union*/


/**|sensor data structor|*/
typedef struct sens_struct{
  char *driver;		//sensor's driver name
  char* port; 		//in which port is bounded its sensor
  char* fd;	//filename where the data from sensor are stored
  int8_t data;		//data read from file value0

  int32_t poll_time; 	//polling time
  char *mode; 		//using mode of sensor
  struct sens_struct *next; 	//next sensor bound in the list


}sensor;

/* create a pointer to a struct of type sensor*/
//sensor *sensor_ptr;

/**------|FUNCTIONS|------------------------------------------------------------*/

/** function for checking what sensors are connected to the brick
**args:fileNumber--how many sensors?
**REturns : a pointer to a linked list
**/
sensor *load_sensor(uint8_t fn);
/**append2list
** append a sensor node to a list
** Args: sl -> address of sensor's nodes list
**/
void append2list(sensor **slist);
/*open sensor*/
void open_sensor(sensor *s);

/**close a sensor if it's not useful
**
**/
void close_sensor(sensor *s);

/**search for a sensor node in the list, by portname
**Return: a pointer to a sensor node of the list
**/
sensor *search4sensor(sensor *slist,char *port_name);

/**delete a specific sensor by its port name
**args:portname
**
**/
void deleteAsensor(sensor *slist,sensor *s);

/**count subfolders in the path
**|Search in <sensor_driver_path directory> to find
**|files that they have in their name the <fileName> substring
**|so, in this way I count how many sensors are connected!!
**/
int8_t countSensor();

/**changing path to files that want to read
**Args: |-init_path :initial path(directory) to expand
**      |-length_dn :down size malloc char* pointer to reset strlen() of path
**      |-lenght_up :increase size of new file name
**      |-str_add   :file's name to concat to the init path
**Returns: a string of file's (to read) fullpath
**/
char *chpath(char *init_path,int8_t lenght_up,char *str_add);

/**read sensors new value0**/
void update_sensor_value(sensor *s);

/**remove all sensors--delete the list and free memory
**/
void removeAll(sensor *slist);


#endif
