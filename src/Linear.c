#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void LinearSearching (int LSlist[] , int n);

int main()
{ 
    int n=100000; 
    int i=0, temp=0;
    char line[10];
    clock_t time;
    double LStime,BStime,IStime;

    FILE *fptr;
    fptr = fopen("list.txt","r");
    
    if (fptr == NULL){
        fprintf(stderr, "\n An Error occurred while opening the file. \n");
        return -1;
    }
    int *list =(int*) malloc(n*sizeof(int)); 
    for(i=0;i<n;i++){
       	fscanf(fptr, "%d", &list[i]);
    }
    LinearSearching(list,n);
    return 0;
}

void LinearSearching (int LSlist[] , int n) {
	
    int i,w;
    int ls=0;
    double LStime=0;
    clock_t start,end;
    printf("Please type the number for the LinearSearching: ");
    scanf("%d", &w);
    
    printf("The process for the LinearSearching between %d numbers has started...\n",n);
    start = clock();
    printf("start time=%ld\n",start);
    for (i = 0; i < n; i++) {
      if (LSlist[i] == w) {
       	printf("%d is at %d position.\n",w,i+1);
      	break;
      }
      ls++;
    }
    end = clock();
    printf("end time=%ld\n",end);
    if(i==n)
    	printf("The number %d was not found\n",w);
    printf("The time measurement of the LinearSearching has been completed. \n");
    printf("The time needed for the LinearSearching is: %f\n", (float) end-start);
    printf("Counter =%d",ls);
    LStime = (double)(end-start)/CLOCKS_PER_SEC;
    printf("\n_____TIME(Seconds)_____\n for the LinearSearching is: %f\n",LStime);
    return;
}
