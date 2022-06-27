#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int numofFrames;
char algorithm[500];
int pagerequests[5000];
int usebit[5000];
int arrayofindexes[500];
int framesofprocess[5000];
int framesofprocess1[5000];
int my_index;//=0;
int pnumber;
int pageindexLRU[5000];
//int fullFrames=0;
int index_of_LRUavailability;


int availableinframes(int x)
{
	int z;
	int available=0;
    // int fullframes=0;
	for(z=0;z<numofFrames;z++)
	{
      if (framesofprocess[z]==x)
      {
      	available=1;
      }
	}
	return available;
}

void FIFO()
{
	int i; //iterate on page requests 
	int fullframes=0;
	int numberofpagefaults=0;
	//int y=0;
    int replacement_position=0;
	int position=0; // iterate on frames 
	for(i=0;i<my_index;i++) //index is number of page requests
	{
		if(availableinframes(pagerequests[i]))
		{
			 if(pagerequests[i]<10)
			{
				printf("0%d     ", pagerequests[i]);
			}
			else 
			{
				printf("%d     ", pagerequests[i]);
			}
		}
		else if(!availableinframes(pagerequests[i]) && fullframes<numofFrames)
		{
			framesofprocess[fullframes]=pagerequests[i];
			fullframes++;
			//y++;
			position++;

			if(pagerequests[i]<10)
			{
				printf("0%d     ", pagerequests[i]);
			}
			else 
			{
				printf("%d     ", pagerequests[i]);
			}
            // printf("\n");
		    position=position%numofFrames;
		}
		else if(!availableinframes(pagerequests[i]) && fullframes==numofFrames)
		{
			//page fault
			numberofpagefaults++;
            framesofprocess[replacement_position]=pagerequests[i];
			//y++;
            if(pagerequests[i]<10)
			{
				printf("0%d F   ", pagerequests[i]);
			}
			else 
			{
				printf("%d F   ", pagerequests[i]);
			}
            // printf("\n");
			replacement_position++;
			position++;
			position=position%numofFrames;
			replacement_position=replacement_position%numofFrames;
		}
		if(fullframes==numofFrames)
		{
			for(int t=0;t<fullframes;t++)
		    {
			if(framesofprocess[t]<10)
				printf("0%d ", framesofprocess[t]);
			else 
				printf("%d ", framesofprocess[t]);
         
		    }
         printf("\n");
		}
		else 
		{
			for(int t=0;t<fullframes;t++)
		    {
			if(framesofprocess[t]<10)
				printf("0%d ", framesofprocess[t]);
			else 
				printf("%d ", framesofprocess[t]);
         
		    }
		     printf("\n");
		}


		/*for(int t=0;t<numofFrames;t++)
		{
			if(framesofprocess[t]<10)
				printf("0%d   ", framesofprocess[t]);
			else 
				printf("%d    ", framesofprocess[t]);
         
		}
         printf("\n");*/
   
	}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",numberofpagefaults);

}

void CLOCK()
{
    //printf("NADA 1 ");
    int positionCLOCK=0;
    int fullframesCLOCK=0;
    int numberofpagefaultsCLOCK=0;
    for(int m=0;m<my_index;m++)
    {
        //printf("NADA 2");
        if(availableinframes(pagerequests[m]))
        {
        	int frame_index =0;
        	for (int mm=0;mm<numofFrames;mm++)
        	{
        		if(framesofprocess[mm]==pagerequests[m])
        		{
        			frame_index=mm;
        			break;
        		}

        	}
            usebit[frame_index]=1;
            if(pagerequests[m]<10)
            {
                printf("0%d     ", pagerequests[m]);
            }
            else
            {
                printf("%d     ", pagerequests[m]);
            }

        }
        else if(!availableinframes(pagerequests[m]) && fullframesCLOCK<numofFrames)
        {
            framesofprocess[fullframesCLOCK]=pagerequests[m];
            usebit[positionCLOCK%numofFrames]=1;
            fullframesCLOCK++;
            //y++;
            positionCLOCK++;

            if(pagerequests[m]<10)
            {
                printf("0%d     ", pagerequests[m]);
            }
            else
            {
                printf("%d     ", pagerequests[m]);
            }
            // printf("\n");
        }
        else if(!availableinframes(pagerequests[m]) && fullframesCLOCK==numofFrames)
        {
            //page fault
            ///printf("Nada 7");
            numberofpagefaultsCLOCK++;
            while(usebit[positionCLOCK%numofFrames]==1)
            {
                //printf("Nada 8");
                usebit[positionCLOCK%numofFrames]=0;
                positionCLOCK++;
            }
            framesofprocess[positionCLOCK%numofFrames]=pagerequests[m];
            usebit[positionCLOCK%numofFrames]=1;
            positionCLOCK++;
            if(pagerequests[m]<10)
            {
                printf("0%d F   ", pagerequests[m]);
            }
            else
            {
                printf("%d F   ", pagerequests[m]);
            }
            // printf("\n");
            //replacement_position++;
            //position++;
            //position=position%numofFrames;
            //replacement_position=replacement_position%numofFrames;
        }
        if(fullframesCLOCK==numofFrames)
        {
            for(int t=0;t<fullframesCLOCK;t++)
            {
                if(framesofprocess[t]<10)
                    printf("0%d ", framesofprocess[t]);
                else
                    printf("%d ", framesofprocess[t]);

            }
            printf("\n");
        }
        else
        {
            for(int t=0;t<fullframesCLOCK;t++)
            {
                if(framesofprocess[t]<10)
                    printf("0%d ", framesofprocess[t]);
                else
                    printf("%d ", framesofprocess[t]);

            }
            printf("\n");
        }

    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",numberofpagefaultsCLOCK);
}

int replaced_index()
{
   int x=0;
   for(int u=1;u<numofFrames;u++)
   {
   	if(pageindexLRU[u]<pageindexLRU[x])
   		x=u;
   }
   return x;
}


int whereavailable(int constant)
{   
	int index_required;

	for(int f=0;f<numofFrames;f++)
	{
      if (framesofprocess[f]==constant)
      {
      	index_required=f;
      }
	}
	return index_required;
	//printf("%d", constant);
}
void LRU()
{
	int numberofpagefaultsLRU=0;
	int fullframesLRU=0;
	int positionLRU=0;
	for(int z=0;z<my_index;z++)
    {
        if(availableinframes(pagerequests[z]))
		{
			index_of_LRUavailability=whereavailable(pagerequests[z]);
			pageindexLRU[index_of_LRUavailability]=z;
			if(pagerequests[z]<10)
			{
				printf("0%d     ", pagerequests[z]);
			}
			else 
			{
				printf("%d     ", pagerequests[z]);
			}

         
		}
		else if(!availableinframes(pagerequests[z]) && fullframesLRU<numofFrames)
		{
			//if(positionLRU==numofFrames)
			//	positionLRU=0;
			framesofprocess[fullframesLRU]=pagerequests[z];
			pageindexLRU[fullframesLRU]=z;
			fullframesLRU++;
			//y++;
			//positionLRU++;

			 if(pagerequests[z]<10)
			{
				printf("0%d     ", pagerequests[z]);
			}
			else 
			{
				printf("%d     ", pagerequests[z]);
			}
            // printf("\n");
		    //positionLRU=positionLRU%numofFrames;
		}
		else if(!availableinframes(pagerequests[z]) && fullframesLRU==numofFrames)
		{
			int replacement_positionLRU=replaced_index();
            framesofprocess[replacement_positionLRU]=pagerequests[z];
            pageindexLRU[replacement_positionLRU]=z;
			//usebit[positionCLOCK]=1;
			//positionLRU++;
			//positionLRU=positionLRU%numofFrames;
            if(pagerequests[z]<10)
			{
				printf("0%d F   ", pagerequests[z]);
			}
			else 
			{
				printf("%d F   ", pagerequests[z]);
			}
			numberofpagefaultsLRU++;
            
		}
       if(fullframesLRU==numofFrames)
		{
			for(int t=0;t<fullframesLRU;t++)
		    {
			if(framesofprocess[t]<10)
				printf("0%d ", framesofprocess[t]);
			else 
				printf("%d ", framesofprocess[t]);
         
		    }
         printf("\n");
		}
		else 
		{
			for(int t=0;t<fullframesLRU;t++)
		    {
			if(framesofprocess[t]<10)
				printf("0%d ", framesofprocess[t]);
			else 
				printf("%d ", framesofprocess[t]);
         
		    }
		     printf("\n");
		}
	}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",numberofpagefaultsLRU);
}

int maxindexOPT()
{
	int x=0;
	for(int d=1;d<numofFrames;d++)
	{
		if(arrayofindexes[d]>arrayofindexes[x])
		{
			x=d;
		}
    }
    return x;
}
void OPTIMAL()
{
	int i;
	int replacement_indexOPT;
	int numberofpagefaultsOPT=0;
	int positionOPT=0;
	int fullframesOPTIMAL=0;
    for(i=0;i<my_index;i++)
	{
		if(availableinframes(pagerequests[i]))
		{
			if(positionOPT==numofFrames)
				positionOPT=0;
			if(pagerequests[i]<10)
			{
				printf("0%d     ", pagerequests[i]);
			}
			else 
			{
				printf("%d     ", pagerequests[i]);
			}

		}
		else if(!availableinframes(pagerequests[i]) && fullframesOPTIMAL<numofFrames)
        {
        	if(positionOPT==numofFrames)
				positionOPT=0;
        	framesofprocess[fullframesOPTIMAL]=pagerequests[i];
        	fullframesOPTIMAL++;
            positionOPT++;
            if(pagerequests[i]<10)
			{
				printf("0%d     ", pagerequests[i]);
			}
			else 
			{
				printf("%d     ", pagerequests[i]);
			}
        }
        else if(!availableinframes(pagerequests[i]) && fullframesOPTIMAL==numofFrames)
		{
			for(int n=0;n<numofFrames;n++)
			{
				arrayofindexes[n]=9999;
			}
			for(int g=0;g<numofFrames;g++)
			{
				for(int h=i+1;h<my_index;h++)
				{
					if(framesofprocess[g]==pagerequests[h])
					{	arrayofindexes[g]=h;
					    break;
				    }
				}
			}
			numberofpagefaultsOPT++;
			replacement_indexOPT= maxindexOPT();
			//printf("\n replacement index is %d\n", replacement_indexOPT);
			framesofprocess[replacement_indexOPT]=pagerequests[i];
			if(pagerequests[i]<10)
			{
				printf("0%d F   ", pagerequests[i]);
			}
			else 
			{
				printf("%d F   ", pagerequests[i]);
			}
		}
		if(fullframesOPTIMAL==numofFrames)
		{
			for(int t=0;t<fullframesOPTIMAL;t++)
		    {
			if(framesofprocess[t]<10)
				printf("0%d ", framesofprocess[t]);
			else 
				printf("%d ", framesofprocess[t]);
         
		    }
         printf("\n");
		}
		else 
		{
			for(int t=0;t<fullframesOPTIMAL;t++)
		    {
			if(framesofprocess[t]<10)
				printf("0%d ", framesofprocess[t]);
			else 
				printf("%d ", framesofprocess[t]);
         
		    }
		     printf("\n");
		}
	}


    printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",numberofpagefaultsOPT);

}
	
int main()
{
	my_index=0;
	scanf("%d",&numofFrames);
	scanf("\n");
	//algorithm=(char *)malloc(20*sizeof(char));
	scanf("%s",algorithm);
	//printf("your alg is %s",algorithm);
	int pnumber;
	scanf("%d",&pnumber); 
	//pagerequests=(int*)malloc(200*sizeof(int));
	while(pnumber!=-1)
	{
		//scanf("%d",&pnumber)
		pagerequests[my_index]=pnumber;
		my_index++;
		scanf("\n");
		scanf("%d",&pnumber);
	}
    
    if(strcmp(algorithm, "FIFO")==0)
    {
    	printf("Replacement Policy = FIFO\n");
    	printf("-------------------------------------\n");
    	printf("Page   Content of Frames\n");
    	printf("----   -----------------\n");
    	//framesofprocess=(int*)malloc(pnumber*sizeof(int));
    	FIFO();
    }
    if(strcmp(algorithm, "CLOCK")==0)
    {
    	printf("Replacement Policy = CLOCK\n");
    	printf("-------------------------------------\n");
    	printf("Page   Content of Frames\n");
    	printf("----   -----------------\n");
    	//framesofprocess=(int*)malloc(pnumber*sizeof(int));
    	CLOCK();
    }
    if(strcmp(algorithm, "LRU")==0)
    {
    	printf("Replacement Policy = LRU\n");
    	printf("-------------------------------------\n");
    	printf("Page   Content of Frames\n");
    	printf("----   -----------------\n");
    	//framesofprocess=(int*)malloc(pnumber*sizeof(int));
    	LRU();
    }
    if(strcmp(algorithm, "OPTIMAL")==0)
    {
    	printf("Replacement Policy = OPTIMAL\n");
    	printf("-------------------------------------\n");
    	printf("Page   Content of Frames\n");
    	printf("----   -----------------\n");
    	//framesofprocess=(int*)malloc(pnumber*sizeof(int));
    	OPTIMAL();
    }
   
}