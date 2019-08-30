#include <alsa/asoundlib.h>
#include <stdio.h>
#include <pthread.h>
int status=0;
struct FileDetails {
    unsigned int rrate;
    snd_pcm_uframes_t frames;
void *ptr;
void (*PlayStatus)(int status);
};

void *PlaybackThread(void *args)
{
    int err;
    snd_pcm_t *handler;
    snd_pcm_hw_params_t *hw_param;
    char *buffer;
    int size;
    unsigned int val;
    long loop;
    int fp;
    struct FileDetails *Pfd = (struct FileDetails *)args;

    /* Open the device*/
    err = snd_pcm_open(&handler, "default", SND_PCM_STREAM_PLAYBACK, 0);

    /* Error check */
    if (err < 0) {
        fprintf (stderr, "cannot open audio device %s (%s)\n", "default", snd_strerror (err));
        handler = NULL;
        exit(1);
    }

    /*set hardware parameters*/
    snd_pcm_hw_params_malloc(&hw_param);
    snd_pcm_hw_params_any(handler, hw_param);
    snd_pcm_hw_params_set_access(handler, hw_param, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handler, hw_param, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_rate_near(handler, hw_param, &Pfd->rrate, 0); //dir value is 0
    snd_pcm_hw_params_set_channels(handler, hw_param, 1);
    snd_pcm_hw_params_set_period_size_near(handler, hw_param, &Pfd->frames, 0);  //dir value is 0

    /*Write the parameters to the driver*/
    err = snd_pcm_hw_params(handler, hw_param);

    /*Check Error*/
    if(err < 0){
        fprintf(stderr, "unable to set hardware parametr : %s\n", snd_strerror(err));
        exit(1);
    }

    /*Use a buffer large enough to hold one period*/
    snd_pcm_hw_params_get_period_size(hw_param, &Pfd->frames, 0);  // dir value is 0
    size = Pfd->frames * 2;
    buffer = (char *) malloc(size);

    /*Get the time required to execute one period*/
    snd_pcm_hw_params_get_period_time(hw_param, &val, 0);	// dir value is 0

    /* Opening a audio file */
    fp = open("friends.wav", O_RDWR);
    Pfd->PlayStatus(0);
    /*5 seconds in microseconds divided by period time*/
    loop = 15000000 / val;
   
    while(loop > 0){
        loop--;
        /*Read the data first*/
        err = read(fp, buffer, size);
        if(err == 0){
            fprintf(stderr, "End of file on input\n");
            break;
        }
        else if(err !=size){
            fprintf(stderr, "short read: read %d bytes\n", err);
        }
        err = snd_pcm_writei(handler, buffer, Pfd->frames);
        if(err == -EPIPE){
            /*EPIPE means underrun*/
            fprintf(stderr, "underrun occurred\n");
            snd_pcm_prepare(handler);
        } else if(err < 0){
            fprintf(stderr, "error from writei : %s\n", snd_strerror(err));
        }
        else if(err != (int)Pfd->frames){
            fprintf(stderr, "short write, write %d frames\n", err);
        }

    }
 Pfd->PlayStatus(1);
    snd_pcm_drain(handler);
    snd_pcm_close(handler);
    free(buffer);
    close(fp);
    return NULL;
}

void Playstatus(int Status)
{
switch(Status)
{
case 0:
//printf("Play success\n");
status=1;
break;
case 1:
printf("Play completed\n");
break;
}
return;
}

int main()
{
    int errno;
    pthread_t thread_id;
    struct FileDetails *fd;
    fd = (struct FileDetails *) malloc(sizeof(struct FileDetails));
    fd->rrate = 22200;
    fd->frames = 24;
fd ->PlayStatus = Playstatus;
    if(pthread_create(&thread_id, NULL, PlaybackThread, fd)){
        fprintf(stderr, "pthread_create failed with errno = %d, %s\n", errno, strerror(errno));
    };
    do
    {
    if(status==1)
     printf("playing song success\n"); 
    }while(status!=1);

    pthread_join(thread_id, NULL);
    free(fd);
    exit(0);
}
