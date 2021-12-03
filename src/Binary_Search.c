#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void BinarySearching (int BSlist[] , int n);

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
	BinarySearching(list,n);
	return 0;
}

void BinarySearching (int BSlist[] , int n) {
	
	int w,first,middle,last;
	int bs=0;
	double BStime;
	clock_t start,end;
	
	printf("\nPlease type the number for the BinarySearching: ");
    scanf("%d", &w);
    
	printf("The process for the BinarySearching has started...\n");
	start = clock();
	printf("start time=%ld\n",start);
	first = 0;
    last = n-1;
    middle =(int) (first + last)/2;
	//printf("middle=%d\n",middle);
   	while( first <= last ) {
   		if ( BSlist[middle] == w ) {
         	printf("The wanted number %d found at location %d.\n",w,middle+1);
         	break;
      	}
      	
      	if ( BSlist[middle] < w ){
      		first = middle + 1;
      		//printf("IF first=%d\n",first);
      		bs++;
		  }
         	
      	
		  else{
		  	last = middle - 1;
		  	//printf("ELSE last=%d\n",last);
		  	bs++;
		  }
         	
         	
        middle =(int) (first + last)/2;
		printf("middle=%d\n",middle);
   	}
   	end= clock();
   	printf("end time=%ld\n",end);
   	if ( first > last )
      printf("The wanted number %d is not found because it is not present in this BSlist.\n",w);
    printf("Counter =%d\tw=%d \n",bs,w);
	
	printf("The time measurement of the BinarySearching has been completed. \n");
    printf("The time needed for the BinarySearching is: %lf\n", (double)end-start);
    BStime = (double)(end-start)/CLOCKS_PER_SEC;
    printf("\n_____TIME(Seconds)_____\nBinarySearching is: %f\n",BStime );
}
