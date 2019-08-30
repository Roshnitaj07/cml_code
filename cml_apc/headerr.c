#include<stdio.h>
#include"CML_types.h"

int main(int argc,char *argv[])
{
    CML_UINT32 iheader;
    CML_CHAR *cheader;
    cheader=(CML_CHAR*)malloc(44);
    
    iheader=open(argv[1],O_RDONLY);
    if(read(iheader,cheader,44)!=44)
        printf("Unable to read header data\n");
    swavheaderinfo.isize=(*(CML_UINT32 *)(cheader+4));
	printf("Overall Size=%u\n",swavheaderinfo.isize);
			   /*no of channels*/
	swavheaderinfo.uwchannel=(*(CML_UINT32 *)(cheader+22));
	printf("channels=%u\n", swavheaderinfo.uwchannel);
			  /*Sample Rate*/
	swavheaderinfo.isamplerate=(*(CML_UINT32 *)(cheader+24));
	printf("SampleRate=%u\n",swavheaderinfo.isamplerate); 
			    /*BYTE RATE*/
	swavheaderinfo.ibyterate=(*(CML_UINT32 *)(cheader+28));
	printf("byterate=%u\n",swavheaderinfo.ibyterate);
			     /*Time*/
	swavheaderinfo.iduaration= (int)(swavheaderinfo.isize)/(swavheaderinfo.ibyterate);
	printf("time=%d\n",swavheaderinfo.iduaration);



}
