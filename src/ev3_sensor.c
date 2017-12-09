/**ev3_sensor.c here there are all functions' bodies
**author:soylisK
**/



#include "ev3_sensor.h"


/****-----------------|functions|------------------------------------------------------------------------**/
int8_t  countSensors()
{
  int8_t file_count = 0;
  DIR *d;
  struct dirent *dir;
  /**sensor_driver_path is define in header(.h) file**/
  d = opendir(sensor_driver_path);
  if (d)
  {


     while ((dir = readdir(d)) != NULL)
     {
	      if (strncmp(dir->d_name, filesName ,strlen(filesName)) == 0)  //filesName is define in (.h)
	         file_count++;
      }
      closedir(d);
      //printf("rats#files=%d\n",count);
   }

    return file_count;

}

char *chpath(char *init_path,int8_t lenght_up,char *str_add)
{
    printf("path=%s\n",init_path);
    int8_t str_size = strlen(init_path)+lenght_up+1;//set the right size of string
    printf("str-size=%d\n",str_size);
    char *strR =(char*)malloc(str_size);
    strcpy(strR,init_path);
    strcat(strR,str_add);

    return strR;
}

void load_sensor(uint8_t fn,sensor **sensor_node)
{


    printf("sensor_nod=%d\n",(*sensor_node) );
    int8_t name_s=strlen(fullpath)+2;
    char *sensor_name=(char*)malloc(name_s);
    char *itoa=(char*)malloc(sizeof(int8_t));
    sprintf(itoa,"%d",fn);          //int to string
    strcpy(sensor_name,fullpath);  //copy fullpath string to a new variable
    strcat(sensor_name,itoa);     //concat fullpath with sensor name
    free(itoa);
    char *filep=NULL;
    /*read driver_name*/
    filep=chpath(sensor_name,strlen(driverf),driverf);
    printf("1chpath=%s\n",filep);
    (*sensor_node)->driver =readData(filep); //<-okk ****DEBUG
    printf("DRIVERPathlen=%d\n",strlen(filep));
    printf("PORT_len=%d\n",strlen(portf));
    /*set_identifier*/
    /*filep=chpath(sensor_name,stlen(driverf),strlen(),);
    (*sensor_node)->id=get_sensor_id(readData(filep));*/
    /*set port*/
    filep=chpath(sensor_name,strlen(portf),portf);
    (*sensor_node)->port=readData(filep);
    printf("2chpath=%s\n",filep);
    /*set fd*/
		filep=chpath(sensor_name,strlen(dataf),dataf);
		(*sensor_node)->fd=filep;
    printf("3chpath=%s\n",filep);
    (*sensor_node)->data=atoi(readData(filep));
    printf("4chpath=%s\n",filep);
    /*set poll time*/
    //filep=chpath(sensor_name,strlen(pollf),pollf);
    //(*sensor_node)->poll_time=atoi(readData(filep));
    printf("5chpath=%s\n",filep);
    /*set mode*/
    filep=chpath(sensor_name,strlen(modef),modef);
    (*sensor_node)->mode= readData(filep);
    printf("6chpath=%s\n",filep);

    /*set next node's pointer*/
    (*sensor_node)->next=NULL; //init state
    printf("NNext=%d",(*sensor_node)->next);
    free(sensor_name);
    printf("free is ok..in load sensor");


}

void append2list(sensor **slist)
{
		numbOfSen=countSensors(); //number of coonected sensors
    printf("There are %d sensors connected..\n",numbOfSen);
    (*slist)=(sensor *)malloc(sizeof(sensor)*numbOfSen); //allocate the right size of memory
    sensor *tmp=NULL;
    if((*slist)==NULL)
      printf("error sensor_list allocation in append..\n");
		uint8_t i;
    printf("before for...\n");
		for(i=0;i<numbOfSen;i++)
		{

        printf("in for..i=%d\n",i);
				// sensor *node=(sensor*)malloc(sizeof(sensor)); //alocate mem for a sensor node
        //checkare pws metavaineis apo enan komvo ston kainourgio??
        //prepei na dhmiourgeis kainourgio node kai na to prostheteis sthn lista
        sensor *node=(sensor *)malloc(sizeof(sensor)); //create a sensor node
        if(node==NULL)
          printf("error durin node allocation...in append\n");
				load_sensor(i,&node);    //add sensor data in the node
        printf("NN=%d\n",node);
				if(i==0)
				{
            printf("II0\n");
            (*slist)=node;	//head of list
            printf("slist=%d\n",(*slist) );
						tmp=node;
            printf("tmp=%d\n",tmp);
				}
				else
				{
            printf("II>0\n");
            printf("tmpII>0=%d\n",tmp);
            tmp->next=node;
            printf("ddddsss\ntmp=%d\n",tmp->next);
						tmp=node;
            printf("new tmp=%d\n",tmp);
				}
        //free(node); //free space for node..so it's can be reallocate
        printf("telos epanalh4hs\n");
		}

}

void update_sensor_value(sensor *s)
{
		s->data=atoi(readData(s->fd)); //read from file where is the value data
}

sensor *search4sensor(sensor *slist,char *port_name)
{
		sensor *node=NULL,*tmp=slist;
		uint8_t i;
		for( i=1;i<=numbOfSen;i++) ///checkkk i=0 h 1
		{
				if(strcmp(tmp->port,port_name)==0 )
				{
						node=tmp;
						break;
				}
				else
						tmp=tmp->next;
		}
		return node;
}

void deleteAsensor(sensor *slist,sensor *s)
{
		sensor *tmp1,*tmp2;
		tmp1=tmp2=slist; //set tmp1,2 to the head of list
		while( (tmp2!=NULL) ) //look in list until hit the node
		{
				if((tmp2->next)==s)
				{
						tmp1=tmp2;
						tmp2=tmp2->next;
						tmp1->next=tmp2;
						free(s);
						break;
				}
				else
						tmp2=tmp2->next;

		}
}


void removeAll(sensor *slist)
{
		sensor *tmp=slist;
		uint8_t i;
		for( i=0;i<numbOfSen;i++)
		{
				tmp=tmp->next;
				free(slist);
				slist=tmp;
		}
}
