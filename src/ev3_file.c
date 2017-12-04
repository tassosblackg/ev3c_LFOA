#include "ev3_file.h"


char *readData(char *fname)
{
    FILE *fp;
    char *line=NULL;
    fp=fopen(fname,"r");
    if(fp!=NULL)
    {
      int8_t error_n=fscanf(fp,"%s",line);
      if(error_n<0)
        printf("@error during reading file...\n");
    }
    else
      printf("ERROR FILE %s COULDN'T BE OPEN\n",fname);
    fclose(fp);
    return line;
}


void writeData(char *fname,char *data)
{
    FILE *fp;

    fp=fopen(fname,"w");
    if(fp!=NULL)
    {
      fprintf(fp,"%s",data);
    }
    else
      printf("ERROR FILE %s COULDN'T BE OPEN\n",fname);
    fclose(fp);
}
