#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct myplaylist
{
   char audio_name[256];
}p[10000];

int main(int argc,char *argv[])
{
     FILE *fptr;
     struct myplaylist p[10000];
     char str[256]; 
     int i,count=0;
     for(i=1;i<argc;i++)
     {
          
            char *str1=strrchr(argv[i],'.');
            if(strcmp(str1,".wav")==0)
            {
               
               strcpy(p[count++].audio_name,argv[i]);
            }
            else if(strcmp(str1,".txt")==0)
            {
     	           
                     fptr=fopen(argv[i],"r");
		     if(fptr==NULL)
		     {
		       printf("Unable to open file.\n");
			exit(EXIT_FAILURE);
		     }
		     else
		     { 
			  while(fgets(str,256,fptr)!=NULL)
                         {
                                 str[strlen(str)-1]='\0';
                                 
                               char *str2=strrchr(str,'.');
                              
                                if(strcmp(str2,".wav")==0)
                                   strcpy(p[count++].audio_name,str);
		         }
			
	             }
		fclose(fptr);
	     } 
             else 
             printf("invalid file extension at %d position\n",i);
    
     }
     
      for(i=0;i<count;i++)
      {
           printf("%s\n",p[i].audio_name);
      }
        

  
    return 0;
}
