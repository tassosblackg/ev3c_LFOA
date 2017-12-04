#include "ev3_file.h"
#define line_length 20

char *readData(char *fname)
{
    FILE *fp;
    char *line=NULL;
    ssize_t len=0;
    fp=fopen(fname,"r");
    if(fp!=NULL)
    {
      ssize_t error_n=getline(&line,&len,fp);
      printf("lineR=%s\n",line);
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
