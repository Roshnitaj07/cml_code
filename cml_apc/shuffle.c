#include<string.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
//extern struct file_path f1[];
struct myplaylist
{
   char audio_name[256];
}p[10000];

void shuffle (struct myplaylist p[]) 
{ 
   int k,n;
   struct myplaylist temp;
    srand ( time(NULL) ); 
    for (i = n-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap arr[i] with the element at random index 
        strcpy(temp.audio_name,p[i].audio_name);
	 strcpy(p[i].audio_name,p[j].audio_name);
	 strcpy(p[j].audio_name,temp.audio_name);
	
    }
} 
 int main()
  {
 printf("before shuffle algorithm\n");
   for(i=0;i<count;i++)
      {
           printf("%s\n",p[i].audio_name);
      }
        printf("after shuffle algo\n");
shuffle(struct myplaylist);
 for(i=0;i<count;i++)
      {
           printf("%s\n",p[i].audio_name);
      }
return 0;
}
