
#define "CML_types.h"
 for(i=1;i<argc;i++)
     {
           
            pfext=strrchr(argv[i],'.');
            if(strcmp(pfext,".wav")==0)
            {
               
               strcpy(cml_plist[pcount++].pfilepath,argv[i]);
            }
            else if(strcmp(pfext,".txt")==0)
            {
     	      if((fp=fopen(argv[i],"r"))!=NULL)
		   {
		   while(fgets ( fline, sizeof (fline), fp ) != NULL)
		         {
			 if(strcmp( fline,"\n")!=0)
			{
			  pfext=strrchr(fline, '.');
		   	  if(strcmp(pfext, ".wav\n") == 0)
		   		  {
				   fline[strlen(fline)-1]='\0';
		    		  strcpy(cml_plist[pcount++].pfilepath, fline);
				  pcount+=1;
		   		  }
			 }
			 }
		    }
		   } 
             else 
             printf("invalid file extension at %d position\n",i);
    
     }
 fclose(fp);
}
