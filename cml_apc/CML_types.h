#ifndef CML_TYPES_H_
#define CML_TYPES_H_

#include<stdio.h>
#include <stddef.h>
#include<pthread.h>
#include<alsa/asoundlib.h>
#define CML_TRUE 1
#define CML_FALSE 0

typedef char CML_CHAR;
typedef unsigned char CML_UCHAR;
typedef unsigned char CML_BYTE;
typedef signed char CML_INT8;
typedef unsigned char CML_UINT8;
typedef signed short CML_INT16;
typedef unsigned short CML_UINT16;
typedef unsigned int CML_UINT32;
typedef int CML_INT32;
typedef signed long  CML_INT64;
typedef unsigned long CML_UINT64;
/*typedef signed long long CML_INT64;
/*typedef unsigned long long CML_UINT64;*/
typedef signed long CML_LONG;
typedef unsigned char CML_BOOL;
typedef float CML_FLOAT;
typedef double CML_DOUBLE;
typedef void CML_VOID;
typedef size_t CML_SIZE_T;
typedef FILE CML_FILE;

struct CML_alsaconifg
{
  snd_pcm_t *pcm_handle;
  snd_pcm_hw_params_t *params;
  snd_pcm_uframes_t frames;
  CML_CHAR *buffer;
}salsaconfig;

struct CML_headerinfo
{
 CML_UINT32 isamplerate;
 CML_UINT16 uwchannel;
 CML_UINT32 isize;
 CML_UINT32 iduaration;
 CML_UINT32 ibyterate;
 CML_UINT32 ibitspersample;
}swavheaderinfo;

struct CML_myplaylist
{

 CML_CHAR *pfilepath;

}samyplaylist[10000];

struct CML_currentfile
{
 CML_UINT32 icurfile;

}sCurFile;

typedef enum 
{

  STOP_STATE = 101,
  PLAY_STATE = 102,
  PAUSED_STATE = 103

}CML_playerstate;

struct CML_threadid
{
 pthread_t playbacktid;
 pthread_t timertid;
}sthreadid;

struct CML_checkstate
{
 CML_UINT32 icurstate;
}ssetcurstate; 

struct time
 {
  int h,m,s;
}stime;

#endif /*CML_types_h*/



