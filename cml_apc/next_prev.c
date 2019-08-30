#include<stdio.h>
 int main()
{
FILE *fp;
 char filename[50];
fp=fopen("play1.txt","r");
 if(fp==NULL)
 {
  printf("failed to open:\n");
  exit(0);
 }
 while(fp!=EOF)
  {
  fgets(fp,10,filename);
   printf("%s",filename);
   fp++;
 }
 
return 0;
}

