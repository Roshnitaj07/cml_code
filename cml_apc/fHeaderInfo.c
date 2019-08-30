
#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
//#include<ftypes.h>
#define MAXCHAR 100
 void file_info(char *audio_file)
 {
  FILE *fp;
  char *header;
  int hdec;
  header=((char*)malloc(44));
  if(header==-1)
   {
    printf("mem error\n");
    exit(0);
   }
 hdec=open(audio_file,O_RDONLY);
 if(read(hdec,header,44)==44)
 {
  long int sample_rate=(*(int*)(header+24));
  long int data=(*(int*)(header+40));
  int channel=(*(int*)(header+22));
  int duration=(data/sample_rate);
  printf("file name=%s",*audio_file);
  printf("sample_rate=%d\n",sample_rate);
  printf("channel=%d\n",channel);
  printf("duration=%d",duration);
 }}

 int main(int argc,char *argv[]) {
    FILE *fp;
    char str[MAXCHAR];
    char* filename;
    int i; 
    
   
    if (argc < 2) {
	printf("No wave file specified\n");
	return 0;
   }
	     
for(i=1;i<argc;i++)
{
    char str[1000];
    filename=argv[i];
    char *end = strrchr(filename, '.');
    if(strcmp(end, ".wav") == 0)
    {
	printf("wav\n");
	file_info(filename);
    }
    else if(strcmp(end,".txt")==0)
    {
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str,MAXCHAR, fp) != NULL)
    {
  
        char file[1000];
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]=='\n')
			str[i]='\0';
  		file[i]=str[i];
		
         }
      
	 printf("%s\n",file);
	 char *end = strrchr(str, '.');
        if(strcmp(end, ".wav") == 0)
	          file_info(str);
}
    fclose(fp);
}

 
}
    return 0;

}
