#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

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
