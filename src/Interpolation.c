#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void InterpolationSearching (int ISlist[] , int n);

int main()
{ 
	int n=100000; //
	int i=0;

    FILE *fptr;
    fptr = fopen("list.txt","r");
    
    if (fptr == NULL)
    {
        fprintf(stderr, "\n An Error occurred while opening the file. \n");
        return -1;
    }
	int *list =(int*) malloc(n*sizeof(int)); 
	for(i=0;i<n;i++){
        fscanf(fptr, "%d", &list[i]);
    }
	InterpolationSearching(list,n);
	return 0;
}

void InterpolationSearching (int ISlist[] , int n)
{
	int w;
	long long int middle,first,last;
	clock_t start,end;
	double IStime;
	int is=0; //counter
	printf("\nPlease type the number for the InterpolationSearching: ");
        scanf("%d", &w);
    
	printf("The process for the InterpolationSearching of the wanted number %d between the %d numbers has started...\n", w,n);
	
	start = clock();	
	printf("start time=%ld\n",start);
	
	first = 0;
        last = n-1;
    
        middle =(last - first)* ( (w - ISlist[first]) / (ISlist[last] - ISlist[first]) )+ first;
	printf("middle=%lld\n",middle);
	printf("ISlist[last]=%lld\tlast=%lld\tISlist[first]=%lld\tfirst=%lld\tmiddle=%lld\n",ISlist[last],last,ISlist[first],first,middle);
 	while (first <= last) {
  		if ( ISlist[middle] == w ){ 	        {
         		printf("The wanted number %d found at location %d.\n",w,middle+1);
         		break;
      	        }
 			
      		if ( ISlist[middle] < w ){
      			first = middle + 1;   
			is++;
		}		   	
      		else{
      			last = middle - 1;
      			is++;
		}
        
   		middle =(long long int) (last - first)* ( (w - ISlist[first]) / (ISlist[last] - ISlist[first])  )+ first;	
   		printf("last=%lld\tfirst=%lld\tmiddle=%lld\n",last,first,middle);
 	}
 	end = clock();
 	printf("end time=%ld\n",end);
	if ( first > last )
      		printf("The wanted number %d is not found because it is not present in this ISlist.\n",w);
	printf("Counter =%d\tw=%d \n",is,w);
	printf("The time measurement of the InterpolationSearching has been completed. \n");
        printf("The time needed for the InterpolationSearching is: %ld\n",end-start);
        IStime = (double)(end-start)/ (double)CLOCKS_PER_SEC;
    

  	printf("\n_____TIME(Seconds)_____\nInterpolationSearching is: %f\n",IStime );
  

	return;
}
