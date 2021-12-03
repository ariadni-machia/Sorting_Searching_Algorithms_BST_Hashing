#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 100000;

int main()
{
   
    int c=0;
    int i=0;
    
    clock_t time;
    double istime;

    char line[10];
	FILE *fptr; 
	// Open file for reading 
	fptr = fopen ("integers.txt", "r"); 
	if (fptr == NULL) 
	{ 
	    fprintf(stderr, "\nError opening file\n"); 
	    return -1; 
	} 
	int *array = malloc(sizeof(int)*n); 	// n= total	
	for(i=0;i<n;i++){
		fgets(line,10,fptr);
		array[i]=atoi(line);
		//printf("%d) %d\n", i, list[i]); //check   
	}
    
    time= clock();
	printf("The progress for %d elements has started.\nPlease wait :) \n..........\n", n);

	int j,temp;
    float ci=0;
    for (i = 1 ; i <= n - 1; i++)
    {
        j = i;

        while ( j > 0 && array[j] < array[j-1])
        {
            temp      = array[j];
            array[j]   = array[j-1];
            array[j-1] = temp;

            j--;
            
            ci++;
        }
    }
	printf("Insertion Sort Counter= %f\n", ci);


    time= clock()-time;
    istime= ((double)time)/CLOCKS_PER_SEC;
	/*
	printf(" insertion sorted list: \n");
    for ( c = 0 ; c < n ; c++ )
        printf("%d\n", list[c]);
	*/
	printf("The measurement of Insertion Sort has been completed.\n..........\n");
	printf("----- TIMES (Seconds) -----\nInsertion Sort= %lf\n", istime);
    
    
	
	
	return 0;
}
