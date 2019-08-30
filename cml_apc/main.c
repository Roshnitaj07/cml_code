#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
struct file_path
{
char file[128];
};

 int main(int argc,char *argv[])
 {
 int i=0,j=0,k;
 size_t len = 0,read;
 char *p;
 FILE *fp;
 char line[128];
 struct file_path f1[10000];
 if(argv[1]!='"-s")
{
  for(i=1;i<argc;i++)
   {
	p=strrchr(argv[i], '.');
	if (p)
        {
            if(strcmp(p, ".wav") == 0)
	        {
		   strcpy(f1[j].f,argv[i]);
		   j++;	
		}
	    else if(strcmp(p, ".txt")==0)
		 {
		   if((fp=fopen(argv[i],"r"))!=NULL)
		   {
		   while(fgets ( line, sizeof (line), fp ) != NULL)
		         {
			 if(strcmp(line,"\n")!=0)
			{
			  p=strrchr(line, '.');
		   	  if(strcmp(p, ".wav\n") == 0)
		   		  {
				  line[strlen(line)-1]='\0';
		    		  strcpy(f1[j].f,line);
				  j+=1;
		   		  }
			 }//if(line!=\n)
			 }//while
		    }//if
		  else
		    {
		    printf("file doesn't exist\n");
		    }   

       		}//elseif

         }//if
     }//for
}//if

return(0);
}
