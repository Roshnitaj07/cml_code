#include <stdio.h>
#include <getopt.h>

int main ( int argc, char **argv) {
 int option_index = 0;
 char *user_name = NULL;

 while (( option_index = getopt(argc, argv, "WwPpSsNnBbHhJj+-:")) != -1){
   switch (option_index) {
     case 'W':
     case 'w':
      user_name = optarg;
       printf("W or w play audiofile\n");
       printf("Audio file=%s is playing\n",user_name);
       break;

     case 'h':
     case 'H':
    printf("==============CML_AUDIO_PLAYER COMMANDS=======================\n");
    printf("\nW|w:start the playback\n P|p:pause and resume\n S|s:stop the playback\n N|n:play the next track\n B|b:play the prevoius track\n   j+J+:seekforward\n +:increase the volume\n -:decrease the volume\n");
     break;

     case 'P':
     case 'p':
       user_name = optarg;
         printf("%s is paused\n",user_name);
         printf("P or p pause and resume\n");
       break;
    case 'S':
     case 's':
         user_name = optarg;
         printf("%s is Stopped\n",user_name);
         printf("S or s stop the playback\n");
       break;
     case 'N':
     case 'n':
         user_name = optarg;
        printf("%s is playing\n",user_name);
        printf("N or n to play next song\n");
       break;
     case 'B':
     case 'b':
          user_name = optarg;
        printf("%s is playing\n",user_name);
         printf("B or b play the prev song\n");
       break;
   /*  case 'j':
     case 'J':
         // user_name = optarg;
          printf("seek_forward by 10sec");
         printf("J+ or j+ seekforward\n");
       break;*/
     case 'j':
     case 'J':
         // user_name = optarg;
          printf("seek_backward by 10sec\n");
         printf("J- or j- seekbackward\n");
       break;
      
     case '+':
        
         printf("+ increase the volume by 10%\n");
       break;
case '-':
        
         printf("- decrease the volume by 10%\n");
       break;
     default:
      printf("Option incorrect\n");
      return 1;
     } //end block for switch
   }  //end block for while
 return 0;
} // end main block

