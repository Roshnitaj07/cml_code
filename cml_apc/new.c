#ifndef CML_AUDIOPLAYER_INTERFACES_H_

#define CML_AUDIOPLAYER_INTERFACES_H_

#include"CML_types.h"


CML_RetType cml_audioplayer_init(UINT32 iNoOfargs,CML_CHAR *pacargslist[])
{   CML_UINT32 ishuffleflag; 
    if(ishuffleflag=Checkinput(iNoOfargs,pacargslist)<0)
        printf("INVALID ARGUMENTS");
    if(cml_myplaylist(iNoOfargs,pacargslist)<0)
        printf("ERROR CREATING PLAYLIST");
    if(1==ishuffleflag)
    {
        if(cml_shuffle()<0)
            printf("ERROR IN SHUFFLE");
    }
    cml_setalsa_config();
    pthread_create(&sthreadid.playbacktid,NULL,cml_playbackthread,sfd);




}


#endif/*CML AudioPlayer Interfaces*/
