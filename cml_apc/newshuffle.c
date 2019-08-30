#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "CML_types.h"
#include  <time.h>
void file_operation(int argc,char *argv[]);
static int count=0;
void swap (struct CML_myplaylist *a, struct  CML_myplaylist *b)  
{  
  struct  CML_myplaylist temp = *a;  
    *a = *b; 
    *b = temp;  
}
void random1()
{
  srand (time(NULL));  
  for (int i = count - 1; i >= 0; i--)  
    {
   int j = rand() % (i + 1); 
          swap(&samyplaylist[i], &samyplaylist[j]);  
    }   
}

void display()
{
int i;
for(i=0;i<count;i++)
{
printf("%s\n",samyplaylist[i].pfilepath);
}
}

int main(int argc,char *argv[])
{
    file_operation(argc,argv);
return 0;
}

void file_operation(int argc,char *argv[])
{
FILE *fh;
int line_size=50,i,k=1;
char* line = (char *)malloc(line_size);
char *ptr;
//samyplaylist=(struct CML_myplaylist *)malloc(sizeof(struct CML_myplaylist)*100);

for(i=1;i<argc;i++)
{
 
	char *end = strrchr(argv[i], '.');

    if(strcmp(end, ".wav") == 0)
    {
           
       strcpy(samyplaylist[count].pfilepath,argv[i]);
	   
	   count++;
	   }

    else if(strcmp(end,".txt")==0)
    {
    	fh=fopen(argv[i],"r");
        	if(fh==NULL)
        		{
        		printf("unable to open the file\n");
        		exit(0);
        	}
        	while (fgets(line, line_size, fh) != NULL)
 	        {
                   
 	             line[strlen(line)-1]=' ';
		     ptr = strtok(line," ");
		     strcpy(samyplaylist[count++].pfilepath,ptr);
          
	       }
	      
	}
        
}
display();
printf("after shuffle\n");
random1();
display();
}
