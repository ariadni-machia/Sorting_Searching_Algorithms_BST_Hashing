#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

const int n=1000;

void BinaryInterpolationSearching (int BISlist[] ,int left, int right, int w);
void BinaryInterpolationImprovedSearching (int BISlist[] ,int left ,int right, int w);

int main()
{ 	
	int i=0;
	char line[10];
    clock_t time, time1,time2;
    double BIStime,BISIMPtime;
     
    FILE *fptr;
    fptr = fopen("list.txt","r");
    
    if (fptr == NULL)
    {
        fprintf(stderr, "\n An Error occurred while opening the file. \n");
        return -1;
    }
	
	int *list =(int*) malloc((n+1)*sizeof(int)); 
	for(i=1;i<=n;i++)
	{
		fscanf(fptr,"%d\n",&list[i]);
		//printf("%d\n",list[i]);
	}
	
	int left=1,right=n;
	int w;
	printf("Please type the number for the BinaryInterpolationSearching: ");
    scanf("%d", &w);
	
	time = clock();
    BinaryInterpolationSearching(list,left,right,w);
    time = clock() - time;
	
	printf("The time measurement of the BinaryInterpolationSearching has been completed. \n");
    printf("The time needed for the BinaryInterpolationSearching is: %d\n", time);
    BIStime = ((double)time)/CLOCKS_PER_SEC;
    
    printf("\nPlease type the number for the BinaryInterpolationImprovedSearching: ");
    scanf("%d", &w);
    
    time1 = clock();
    BinaryInterpolationImprovedSearching(list ,left , right, w);
    time2 = clock() ;
	
	printf("The time measurement of the BinaryInterpolationImprovedSearching has been completed. \n");
    printf("The time needed for the BinaryInterpolationImprovedSearching is: %d\n", time);
    BISIMPtime = (double)(time2-time1) /CLOCKS_PER_SEC;
    
  	printf("\nTIME(Seconds) \n for the BinaryInterpolationSearching is: %lf \n for the BinaryInterpolationImprovedSearching is: %lf \n ",BIStime,BISIMPtime );

	fclose(fptr);
	
	return 0;
}

void BinaryInterpolationSearching (int BISlist[] ,int left ,int right, int w) {
	
	int i; 
	long long int middle,first,last,size;
	first = left;
	last = right;
    
    printf("The process for the BinaryInterpolationSearching has started...\n");
    if(w<BISlist[left]){
		printf("The wanted number %d is not present in this BISlist.\n" ,w);	
		return;
	}
	else if(w>BISlist[right]){
		printf("The wanted number %d is not present in this BISlist.\n" ,w);	
		return;
	}
    size = last-first+1;
    middle =(long long int) size *(w - BISlist[first]) / (BISlist[last] - BISlist[first]) + 1;
    
    while(w!=BISlist[middle] ) 
	{
		//printf("WHILEEEEEE\n");
		int i=0;
		size=last-first+1;
    	if(size<=10) // Linear
		{	
			int j=0;
			for (j = first; j <= last; j++)
    		{
      			if (BISlist[j] == w)     
      			{
         			printf("The wanted number %d is present at location %d.\n" ,w,j);
         			return;
      			}
    		}    
   			if (j == last+1){
				printf("The wanted number %d is not present in this BISlist.\n" ,w);	
				return;
			 }
      			
		}

		else//if(size>3) // Binary - Interpolation
		{
			if(w>=BISlist[middle])
			{
				long long int a=(long long int) (middle + i*sqrt(size) - 1);				
				if(a>last) // an 3eperasei to de3i akro toy upopinaka
					a=last;
				else if(a<first)
					a=first;
    			while(w>BISlist[a] ) 
				{
                	i=i+1;
                	a=(long long int) (middle + i*sqrt(size) - 1);
					if(a>=right)
						a=right;
					else if(a<=left)
						a=left;
            	}
           		last =(long long int) (middle + i *sqrt(size) );
            	first = (long long int) (middle  + (i - 1) *sqrt(size) );
       		}
        
        	else
			{
				long long int b=(long long int)(middle - i *sqrt(size) + 1);
				if(b<left) // an 3keprasei to aristero akro toy upopinaka
					b=left;
				else if(b>right)
					b=right;
            	while(w < BISlist[b] ) //&& sqrt(size)<n && w<=BISlist[n]
				{			
					//printf("jk01\tb=%lld\n",b);
                	i=i+1;
                	b=(long long int)(middle - i *sqrt(size) + 1);
            		if(b<left) // an 3keprasei to aristero akro toy upopinaka
						b=left;
					else if(b>right)
						b=right;
            	}
            	last =(long long int) (middle - (i - 1) * sqrt(size) );
            	first =(long long int) ( middle - i * sqrt(size) );
        	}        		
			
		}
		middle = first + ((last - first + 1) * ((w -  BISlist[first]) / (BISlist[last] - BISlist[first]))) -1;	
	}
		
	if(w == BISlist[middle])
	{
		printf("The wanted number %d found at location %lld.\n",w,middle);
	}
	else
	{
		printf("The wanted number %d is not found because it is not present in this BISlist.\n" ,w);
	}

}

void BinaryInterpolationImprovedSearching (int BISIMPlist[] ,int left ,int right, int w)
{
	int i,j;
	unsigned long long int first,middle,last,size;
	first=left;
	last=right;
    
    printf("The process for the BinaryInterpolationImprovedSearching of the wanted number %d between the %d numbers has started...", w,n);
  	if(w<BISIMPlist[left]){
		printf("The wanted number %d is not present in this BISlist.\n" ,w);	
		return;
	}
	else if(w>BISIMPlist[right]){
		printf("The wanted number %d is not present in this BISlist.\n" ,w);	
		return;
	}
  
    size = last-first+1;
    middle = size *(w - BISIMPlist[first]) / (BISIMPlist[last] - BISIMPlist[first])+ 1;
    while(w!=BISIMPlist[middle]) 
	{
		i=0;
		size=last-first+1;
		
    	if(size<=10) // Linear
		{	
			j=0;
			for (j = first; j <= last; j++)
    		{
      			if (BISIMPlist[j] == w)     
      			{
         			printf("The wanted number %d is present at location %d.\n" ,w,j);
         			return;
      			}
    		}
    		if (j == last+1){
				printf("The wanted number %d is not present in this BISIMPlist.\n" ,w);	
				return;
			 }

		}

		else // Interpolation
		{
			if(w>=BISIMPlist[middle])
			{
				unsigned long int a= (unsigned long long int) (middle + i*sqrt(size) - 1);
				if(a>right) // an 3keprasei to de3i akro toy upopinaka
					a=right;
				else if(a<left)
					a=left; 
    			while(w>BISIMPlist[a]  ) 
				{
                	i=pow(2,i); 
					j++;
                	//printf("BISIMP[%llu]=%d\n",a,BISIMPlist[a]);
                	a= (unsigned long long int) (middle + i*sqrt(size) - 1);
                	if(a>=right) // an 3keprasei to de3i akro toy upopinaka
						a=right;
					else if(a<=left)
						a=left;
            	}
           		last = (unsigned long int) (middle + i *sqrt(size) );
            	first =(unsigned long int) (middle  + (i - 1) *sqrt(size));
       		}
        
        	else if (w<BISIMPlist[middle]) //// else
			{
				unsigned long long int b=(unsigned long int) (middle - i *sqrt(size) + 1);				
				if(b<left) // an 3keprasei to aristero akro toy upopinaka
					b=left;
				else if(b>right)
					b=right;
            	while(w < BISIMPlist[b] ) 
				{
                	i=pow(2,i);
                	b=(unsigned long long int) (middle - i *(int)sqrt(size) + 1);                	
					if(b<left) // an 3keprasei to aristero akro toy upopinaka
						b=left;
					else if(b>right)
						b=right;
            	}
            }
            unsigned long long int a= (unsigned long long int) (middle + i*sqrt(size) - 1); /////
            	if(a>right) // an 3keprasei to de3i akro toy upopinaka
					a=right;
				else if(a<left)
					a=left;
			unsigned long long int b=(unsigned long long int) (middle - i *sqrt(size) + 1);   /////             	
					if(b<left) // an 3keprasei to aristero akro toy upopinaka
						b=left;
					else if(b>right)
						b=right;
            
            if(BISIMPlist[b]<=w && w<= BISIMPlist[a]) // Binary //BISIMPlist[c]<w && w<= BISIMPlist[d]
			{
    			middle = (first + last)/2;

   				while( first <= last )
   				{
   					if ( BISIMPlist[middle] == w )
      				{
         				printf("The wanted number %d found at location %llu.\n",w,middle);
         				return;
      				}
      				if ( BISIMPlist[middle] < w )
         				first = middle + 1;
      	
      				else
         				last = middle - 1;
         	
        			middle = (first + last)/2;

   				}
   				if ( first > last ){
   					printf("The wanted number %d is not found because it is not present in this BISIMPlist.\n",w);
   					return;
				}      				
			
			}
        	j++;
			middle =(unsigned long long int) ( first + ((last - first + 1) * ((w -  BISIMPlist[first]) / (BISIMPlist[last] - BISIMPlist[first]))) -1  );
		}	// end of Interpoaltion	
	}
			
	if(w == BISIMPlist[middle])
	{
		printf("The wanted number %d found at location %llu.\n",w,middle);
	}
	else
	{
		printf("The wanted number %d is not found because it is not present in this BISIMPlist.\n",w);
	}
		
}

