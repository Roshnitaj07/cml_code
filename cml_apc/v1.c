#include <stdio.h>
#include<string.h>
#include <alsa/asoundlib.h>
#include<pthread.h>
#include <unistd.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#define PCM_DEVICE "default"	
#define MAXCHAR 1000
snd_pcm_t *handle;
void func(char *str);


int toggle=0;	
int headec;
void SetAlsaMasterVolume(long volume)
{
    long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "Master";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(handle);
}
void stop()
{
//printf("handle= %ld",handle);
snd_pcm_drop(handle);

}
void pauseorplay()
{
if(toggle)
{
snd_pcm_pause(handle,0);
toggle=0;
}
else
{
snd_pcm_pause(handle,1);
toggle=1;
}

}



//playback commands
void *playback()
{
 while(1)
{
int ch;
 printf("Enter your choice\n");
 scanf("%d",&ch);
 switch(ch)
  {
  
   case 1:stop();
   break;
   case 2:pauseorplay();
   break;
   case 3:SetAlsaMasterVolume(40);
   break;
   case 4:lseek(headec,10000000,SEEK_CUR);
   break;
   
  }

}
}


//application program
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
	func(filename);
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
	          func(str);
}
    fclose(fp);
}

 
}
    return 0;
}

//==============================================================================
void func(char *str)
{      
        char *header;
        int headec;
	header=(char *)malloc(44);
        headec=open(str,O_RDONLY);
	printf("%d\n",headec);
	 
        if(read(headec,header,44) == 44)
  	     printf("Header\n");
{
   /* long int sample_rate=(*(int*)(header+24));
  long int data=(*(int*)(header+40));
  int channel=(*(int*)(header+22));
  int duration=(data/sample_rate)/4;
  printf("file name=%s",*str);
  printf("sample_rate=%d\n",sample_rate);
  printf("channel=%d\n",channel);
  printf("duration=%d",duration);*/
        printf("Sample %d\n",*(int *)(header+24));
        printf("data %d\n",*(int *)(header+40));
	long int sample=(*(int *)(header+24));
	long int data=(*(int *)(header+40));
	int time=(data/sample)/4;
	printf("time %d\n", time);
}}
//=================alsa=================================================



long loops;
  int rc;
  int size;
  snd_pcm_hw_params_t *params;
  unsigned int val;
  int dir;
  snd_pcm_uframes_t frames;
  char *buffer;

  /* Open PCM device for playback. */
  rc = snd_pcm_open(&handle, "default",
                    SND_PCM_STREAM_PLAYBACK, 0);
  if (rc < 0) {
    fprintf(stderr,
            "unable to open pcm device: %s\n",
            snd_strerror(rc));
    exit(1);
  }

   
  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_alloca(&params);

  /* Fill it in with default values. */
  snd_pcm_hw_params_any(handle, params);

  /* Set the desired hardware parameters. */

  /* Interleaved mode */
  snd_pcm_hw_params_set_access(handle, params,
                      SND_PCM_ACCESS_RW_INTERLEAVED);

  /* Signed 16-bit little-endian format */
  snd_pcm_hw_params_set_format(handle, params,
                              SND_PCM_FORMAT_S16_LE);

  /* Two channels (stereo) */
  snd_pcm_hw_params_set_channels(handle, params, 2);

  /* 44100 bits/second sampling rate (CD quality) */
  val = sample;
  snd_pcm_hw_params_set_rate_near(handle, params,
                                  &val, &dir);

  /* Set period size to 32 frames. */
  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle,
                              params, &frames, &dir);

  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(handle, params);
  if (rc < 0) {
    fprintf(stderr,
            "unable to set hw parameters: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(params, &frames,
                                    &dir);
  size = frames * 4; /* 2 bytes/sample, 2 channels */
  buffer = (char *) malloc(size);

  /* We want to loop for song duration */
  snd_pcm_hw_params_get_period_time(params,
                                    &val, &dir); 


  /* duration in microseconds divided by
   * period time */
  loops = (time*1000000) / val;

  /*multithreading
    pthread_t pth; 
    printf("Before Thread\n"); 
    pthread_create(&pth, NULL,playback,NULL);*/
     

while (loops > 0) {
    loops--;
    rc = read(headec, buffer, size);
    if (rc == 0) {
      fprintf(stderr, "end of file on input\n");
      break;
    } else if (rc != size) {
      fprintf(stderr,
              "short read: read %d bytes\n", rc);
    }
    rc = snd_pcm_writei(handle, buffer, frames);
    if (rc == -EPIPE) {
      /* EPIPE means underrun */
      fprintf(stderr, "underrun occurred\n");
      snd_pcm_prepare(handle);
    } else if (rc < 0) {
      fprintf(stderr,
              "error from writei: %s\n",
              snd_strerror(rc));
    }  else if (rc != (int)frames) {
      fprintf(stderr,
              "short write, write %d frames\n", rc);
    }
  }

  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);

}
