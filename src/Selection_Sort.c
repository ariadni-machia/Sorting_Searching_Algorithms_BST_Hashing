#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 100000;

int main()
{
   
    int c=0;
    int i=0;
    
    clock_t time;
    double sstime;

    char line[10];
    FILE *fptr; 
    // Open file for reading 
    fptr = fopen ("integers.txt", "r"); //C:\\Users\\Ariadni\\Desktop\\integers.txt
    if (fptr == NULL) { 
	    fprintf(stderr, "\nError opening file\n"); 
	    return -1; 
    } 
    int *array = malloc(sizeof(int)*n); 	// n= total	
    for(i=0;i<n;i++){
	fgets(line,10,fptr);
	array[i]=atoi(line);
    }
    
    
    printf("The progress for %d elements has started.\nPlease wait :) \n..........\n", n);
    time= clock(); // begin time
    int j,swap,position;
    float cs=0;
    for ( i = 0 ; i < ( n - 1 ) ; i++ )
    {
        position = i;

        for ( j = i + 1 ; j < n ; j++ )
        {
            if ( array[position] > array[j] )
                position = j;
            cs++;    
        }
        if ( position != i )
        {
        	swap = array[i];
            array[i] = array[position];
            array[position] = swap;
            
        }
    }
    printf("Selection Sort Counter= %f\n", cs);
	

    time= clock()-time; // end time
    sstime= ((double)time)/CLOCKS_PER_SEC;
	 
    printf("The measurement of Selection Sort has been completed.\n..........\n");
    printf("----- TIMES (Seconds) -----\nSelection Sort= %lf\n",sstime );
    free(array);
    return 0;
}
